#include <assert.h>
#include <stdlib.h>
#include "../export/panic.h"
#include "../export/result.h"
#include "../export/option.h"
#include "../export/buffer.h"

#define CapacityOverflow "capacity overflow"
#define AllocError "failed to alloc enough memory"

#define MIN_NON_ZERO_CAP(T)         \
do {                                \
    int size;                       \
    if (sizeof(T) == 1) {           \
        size = 8;                   \
    } else if (sizeof(T) <= 1024) { \
        size = 4;                   \
    } else {                        \
        size = 1;                   \
    }                               \
    size                            \
}while(0)

typedef struct Buffer Buffer;

enum AllocInit {Uninitialized, Zeroed};

Buffer Buf_new() {
    // `cap: 0` means "unallocated"
    Buffer buf = {NULL, 0};
    return buf;
}

Buffer Buf_with_capacity(uint32_t capacity) {
    Buf_allocate_in(capacity, Uninitialized);
}

Buffer Buf_with_capacity_zeroed(uint32_t capacity) {
    Buf_allocate_in(capacity, Zeroed);
}

Buffer Buf_allocate_in(uint32_t capacity, enum AllocInit init) {
    // since the capacity is an u32, which has a maximum of 4G,
    // there is no way to trigger capacity overflow
    // however, we have no ability to detect arithmetic overflow,
    // so the allocated size may smaller than expected
    // arithmetic overflow is **UNDEFINED BEHAVIOR**, we do not guarantee anything about it
    void *ptr;
    if (init == Uninitialized) {
        ptr = malloc(capacity);
    } else if (init == Zeroed) {
        ptr = calloc(capacity, 1);
    } else {
        panic("Undefined AllocInit Type");
    }

    if (ptr == NULL) panic(AllocError);
    Buffer buf = {ptr, capacity};
    return buf;
}

Buffer Buf_from_raw(void *ptr, uint32_t capacity) {
    Buffer buf = {ptr, capacity};
    return buf;
}

/// Gets a raw pointer to the start of the allocation. Note that this is
/// NULL if capacity == 0. In the former case, you must be careful.
void *ptr(const Buffer self) { return self.ptr; }

/// Gets the capacity of the allocation.
uint32_t capacity(const Buffer self) { return self.capacity; }

static Option current_memory(const Buffer self) {
    if (self.capacity == 0) {
        return None;
    } else {
        return Some(self.ptr);
    }
}

/// Ensures that the buffer contains at least enough space to hold `len +
/// additional` elements. If it doesn't already have enough capacity, will
/// reallocate enough space plus comfortable slack space to get amortized
/// *O*(1) behavior.
void reserve(Buffer self, uint32_t len, uint32_t additional) {
    assert(self.capacity >= len);
    if (additional > self.capacity - len) {
        handle_reserve(grow_amortized(self, len, additional));
    }
}

/// The same as `reserve`, but returns on errors instead of panicking or aborting.
Result try_reserve(Buffer self, uint32_t len, uint32_t additional) {
    if (self.capacity >= len) return Err(CapacityOverflow);
    if (additional > self.capacity - len) {
        return grow_amortized(self, len, additional);
    } else {
        return Ok(NULL);
    }
}

/// Ensures that the buffer contains at least enough space to hold `len +
/// additional` elements. If it doesn't already, will reallocate the
/// minimum possible amount of memory necessary. Generally this will be
/// exactly the amount of memory necessary, but in principle the allocator
/// is free to give back more than we asked for.
void reserve_exact(Buffer self, uint32_t len, uint32_t additional) {
    handle_reserve(try_reserve_exact(self, len, additional));
}

/// The same as `reserve_exact`, but returns on errors instead of panicking or aborting.
Result try_reserve_exact(Buffer self, uint32_t len, uint32_t additional) {
    if (self.capacity >= len) return Err(CapacityOverflow);
    if (additional > self.capacity - len) {
        return grow_exact(self, len, additional);
    } else {
        return Ok(NULL);
    }
}

void shrink_to_fit(Buffer self, uint32_t amount) {
    handle_reserve(shrink(self, amount));
}

static Result grow_amortized(Buffer self, uint32_t len, uint32_t additional) {
    // This is ensured by the calling contexts.
    assert(additional > 0);

    // check if len plus additional overflow u32
    if (UINT32_MAX - len < additional) return Err(CapacityOverflow);
    uint32_t required_cap = len + additional;

    // This guarantees exponential growth.
    uint32_t cap = (self.capacity > UINT32_MAX/2) ? UINT32_MAX : self.capacity * 2;
    cap = (cap >= required_cap) ? cap : required_cap;

    void *ptr = finish_grow(cap, current_memory(self));
    self.ptr = ptr;
    self.capacity = cap;
    return Ok(NULL);
}

static Result grow_exact(Buffer self, uint32_t len, uint32_t additional) {
    // check if len plus additional overflow u32
    if (UINT32_MAX - len < additional) return Err(CapacityOverflow);
    uint32_t cap = len + additional;

    void *ptr = finish_grow(cap, current_memory(self));
    self.ptr = ptr;
    self.capacity = cap;
    return Ok(NULL);
}

static Result shrink(Buffer self, uint32_t amount) {
    // Tried to shrink to a larger capacity
    assert(amount <= self.capacity);

    Option mem = current_memory(self);
    if (is_none(mem)) {
        // no memory allocated, capacity is already zero
        return Ok(NULL);
    }

    void *ptr = unwrap(mem);

    
    ptr = realloc(ptr, amount);

    if (ptr == NULL) return Err(AllocError);
    
    self.ptr = ptr;
    self.capacity = amount;
    return Ok(NULL);
}

static Result finish_grow(uint32_t new_layout, Option current_memory) {
    void *memory;
    if (is_none(current_memory)) {
        memory = malloc(new_layout);
    } else {
        memory = realloc(unwrap(current_memory), new_layout);
    }
    return (memory == NULL) ? Err(AllocError) : Ok(NULL);
}

static void Buffer_Drop(Buffer buf) {
    if (buf.ptr != NULL) {
        free(buf.ptr);
    }
}

// Central function for reserve error handling.
static void handle_reserve(Result result) {
    if (is_err(result)) {
        // the two kind of error defined above
        // CapacityOverflow and AllocError
        // are both unrecoverable(in an platform independent view),
        // so I just simply panic it
        panic(unwrap_err(result));
    }
}
