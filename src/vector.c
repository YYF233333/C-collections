#include <stdlib.h>
#include "../export/core.h"
#include "../export/buffer.h"

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