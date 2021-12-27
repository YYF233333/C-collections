#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../export/result.h"

static Result Result_new(int flag, void *val, size_t size) {
    Result res;
    res.flag = flag;
    res.val = malloc(size);
    assert(res.val);
    memcpy(res.val, val, size);
    return res;
}

Result new_Ok(void *val, size_t size) {
    return Result_new(0, val, size);
}

Result new_Err(void *val, size_t size) {
    return Result_new(1, val, size);
}

int is_ok(Result res) {
    return res.flag == 0;
}

int is_err(Result res) {
    return res.flag == 1;
}

void *unwrap(Result res) {
    // figure out another way to abort in release env
    assert(res.flag == 0);
    return res.val;
}

void *unwrap_or(Result res, void *default_val) {
    return res.flag == 0 ? res.val : default_val;
}

void *unwrap_or_else(Result res, void *(* closure)(char *message)) {
    if (res.flag == 0) {
        return res.val;
    } else {
        return closure((char *)res.val);
    }
}

char *unwrap_err(Result res) {
    assert(res.flag == 1);
    return (char *)res.val;
}

Result map(Result res, void *(* map)(void *val)) {
    if (res.flag == 0) {
        void *new_val = map(res.val);
        free(res.val);
        res.val = new_val;
    }
    return res;
}