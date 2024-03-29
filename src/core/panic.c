#include "core/panic.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void _panic(const char *const file, unsigned line, const char *const format,
            ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "program panicked at \'");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\', %s:%d\n", file, line);
    exit(101);
}