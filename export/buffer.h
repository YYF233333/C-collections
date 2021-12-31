#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

typedef struct Vec Vec;

struct Buffer {
    void *ptr;
    uint32_t capacity;
};

struct Vec {
    struct Buffer buf;
    uint32_t len;
};

#define capacity_from_bytes()

#endif /* BUFFER_H_ */