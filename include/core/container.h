#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <stddef.h>

#define container_of(ptr, type, member)                                        \
    ({                                                                         \
        const typeof(((type *)0)->member) *__mptr = (ptr);                     \
        (type *)((char *)__mptr - offsetof(type, member));                     \
    })

#endif /* NOT CONTAINER_H_ */