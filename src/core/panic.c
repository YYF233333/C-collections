#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../../include/panic.h"

void _panic(const char *const format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    exit(101);
}