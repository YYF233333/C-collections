#include "../include/panic.h"

char *err() {
    return "error messgae in pointer format %s, %d";
}

int main(void) {
    char *s = "string";
    unimplemented();
    unreachable();
    panic(err(), s, 114514);
}