#include "../export/panic.h"

int main(void) {
    char *s = "some specified error";
    panic(s);
}