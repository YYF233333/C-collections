#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include "pair.h"

typedef struct Buffer Buffer;

struct Buffer {
    void *ptr;
    uint32_t capacity;
};

extern Buffer Buf_new();
extern Buffer Buf_with_capacity(uint32_t capacity);
extern Buffer Buf_with_capacity_zeroed(uint32_t capacity);
extern Buffer Buf_from_raw(void *ptr, uint32_t capacity);
extern void   reserve(Buffer *self, uint32_t len, uint32_t additional);
extern void   reserve_exact(Buffer *self, uint32_t len, uint32_t additional);
extern Result try_reserve(Buffer *self, uint32_t len, uint32_t additional);
extern Result try_reserve_exact(Buffer *self, uint32_t len, uint32_t additional);
extern void   shrink_to(Buffer *self, uint32_t amount);

#endif /* BUFFER_H_ */