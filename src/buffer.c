#include "buffer.h"
#include <stdlib.h>
#include "core.h"

#define CapacityOverflow "capacity overflow"
#define AllocError "failed to alloc enough memory"

enum AllocInit { Uninitialized, Zeroed };
enum GrowType { Amortized, Exact };

Buffer Buf_new() {
    // `cap: 0` means "unallocated"
    return Buf_from_raw(NULL, 0);
}

Buffer Buf_with_capacity(uint32_t capacity) {
    Buf_allocate(capacity, Uninitialized);
}

Buffer Buf_with_capacity_zeroed(uint32_t capacity) {
    Buf_allocate(capacity, Zeroed);
}

// unsafe API
Buffer Buf_from_raw(void *ptr, uint32_t capacity) {
    Buffer buf = { ptr, capacity };
    return buf;
}

static Buffer Buf_allocate(uint32_t capacity, enum AllocInit init) {
    // since the capacity is an u32, which has a maximum of 4G,
    // there is no way to trigger capacity overflow
    void *ptr;
    switch (init) {
        case Uninitialized:
            ptr = malloc(capacity);
            break;
        case Zeroed:
            ptr = calloc(capacity, 1);
            break;
        default:
            panic("Undefined AllocInit Type");
    }

    if (ptr == NULL) panic(AllocError);
    return Buf_from_raw(ptr, capacity);
}

/// Ensures that the buffer contains at least enough space to hold `len +
/// additional` elements. If it doesn't already have enough capacity, will
/// reallocate enough space plus comfortable slack space to get amortized
/// *O*(1) behavior.
void reserve(Buffer *self, uint32_t len, uint32_t additional) {
    handle_reserve(try_reserve_in(self, len, additional, Amortized));
}

/// Ensures that the buffer contains at least enough space to hold `len +
/// additional` elements. If it doesn't already, will reallocate the
/// minimum possible amount of memory necessary. Generally this will be
/// exactly the amount of memory necessary, but in principle the allocator
/// is free to give back more than we asked for.
void reserve_exact(Buffer *self, uint32_t len, uint32_t additional) {
    handle_reserve(try_reserve_in(self, len, additional, Exact));
}

/// The same as `reserve`, but returns on errors instead of panicking or
/// aborting.
Result try_reserve(Buffer *self, uint32_t len, uint32_t additional) {
    return try_reserve_in(self, len, additional, Amortized);
}

/// The same as `reserve_exact`, but returns on errors instead of panicking or
/// aborting.
Result try_reserve_exact(Buffer *self, uint32_t len, uint32_t additional) {
    return try_reserve_in(self, len, additional, Exact);
}

static Result try_reserve_in(Buffer *self, uint32_t len, uint32_t additional,
                             enum GrowType type) {
    if (self->capacity < len) return Err(CapacityOverflow);
    if (additional > self->capacity - len) {
        return grow(self, len, additional, type);
    } else {
        return Ok(NULL);
    }
}

void shrink_to(Buffer *self, uint32_t amount) {
    // Tried to shrink to a larger capacity
    assert(amount <= self->capacity);

    if (self->ptr == NULL) {
        // no memory allocated, capacity is already zero
        return Ok(NULL);
    }

    void *ptr = realloc(self->ptr, amount);
    if (ptr == NULL) handle_reserve(Err(AllocError));

    self->ptr = ptr;
    self->capacity = amount;
}

#define MAX(a, b) ((a) >= (b) ? (a) : (b))
static Result grow(Buffer *self, uint32_t len, uint32_t additional,
                   enum GrowType type) {
    // This is ensured by the calling contexts.
    assert(additional > 0);
    assert(type == Amortized || type == Exact);

    // check if len plus additional overflow u32
    if (UINT32_MAX - len < additional) return Err(CapacityOverflow);
    uint32_t required_cap = len + additional;

    uint32_t cap;
    if (type == Amortized) {
        // This guarantees exponential growth.
        cap =
            (self->capacity > UINT32_MAX / 2) ? UINT32_MAX : self->capacity * 2;
        cap = MAX(cap, required_cap);
    } else {
        cap = required_cap;
    }

    void *memory = (self->ptr == NULL) ? malloc(cap) : realloc(self->ptr, cap);

    if (memory == NULL) return Err(AllocError);
    self->ptr = memory;
    self->capacity = cap;
    return Ok(NULL);
}
#undef MAX

static void Buffer_Drop(Buffer buf) {
    if (buf.ptr != NULL) {
        free(buf.ptr);
    }
}

// Central function for reserve error handling.
static void handle_reserve(Result result) {
    if (is_err(result)) {
        // the two kind of error defined above:
        //      CapacityOverflow and AllocError
        // are both unrecoverable(in an platform independent view),
        // so I just simply panic them
        panic(unwrap_err(result));
    }
}
