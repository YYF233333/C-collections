#include <assert.h>
#include "../export/result.h"

typedef unsigned long long generic;

static Result Result_new(int flag, generic val) {
    Result res;
    res.flag = flag;
    res.val = val;
    return res;
}

Result new_Ok(generic val) {
    return Result_new(0, val);
}

Result new_Err(generic val) {
    return Result_new(1, val);
}

int is_ok(Result res) {
    return res.flag == 0;
}

int is_err(Result res) {
    return res.flag == 1;
}

generic unwrap(Result res) {
    // figure out another way to abort in release env
    assert(res.flag == 0);
    return res.val;
}

generic unwrap_or(Result res, generic default_val) {
    return res.flag == 0 ? res.val : default_val;
}

generic unwrap_or_else(Result res, generic (* closure)(char *message)) {
    return res.flag == 0 ? res.val : closure((char *)res.val);
}

char *unwrap_err(Result res) {
    assert(res.flag == 1);
    return (char *)res.val;
}

Result map(Result res, generic (* map)(generic val)) {
    if (res.flag == 0) {
        res.val = map(res.val);
    }
    return res;
}