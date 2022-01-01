#include "../include/panic.h"

int main(void) {
    char *s = "string";
    panic("Some specified error: %s, %d", s, 114514);
}