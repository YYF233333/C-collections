#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../export/result.h"

void *cl(char *message) {
    int *a = malloc(sizeof(int));
    *a = 0;
    return a;
}

void *map_cl(void *val) {
    printf("map: get val: %d\n", *(int *)val);
    return "something new";
}

int main(void) {
    int a = 10;
    int d = 114514;
    Result res = Ok(&a);
    assert(is_ok(res));
    printf("unwrap: %d\n", *(int *)unwrap(res));
    printf("unwrap_or: %d\n", *(int *)unwrap_or(res, &d));
    printf("unwrap_or_else: %d\n", *(int *)unwrap_or_else(res, cl));
    printf("map: %s\n", unwrap(map(res, map_cl)));

    res = Err("No num");
    assert(is_err(res));
    printf("unwrap_err: %s\n", unwrap_err(res));
    printf("unwrap_or: %d\n", *(int *)unwrap_or(res, &d));
    printf("unwrap_or_else: %d\n", *(int *)unwrap_or_else(res, cl));
}