#include <assert.h>
#include "../export/option.h"

typedef unsigned long long generic;

static Option Option_new(int flag, generic val) {
    Option opt;
    opt.flag = flag;
    opt.val = val;
    return opt;
}

Option new_Some(generic val) {
    return Option_new(0, val);
}

Option new_None() {
    return Option_new(1, 0);
}

int is_some(Option opt) {
    return opt.flag == 0;
}

int is_none(Option opt) {
    return opt.flag == 1;
}

generic unwrap(Option opt) {
    // figure out another way to abort in release env
    assert(opt.flag == 0);
    return opt.val;
}

generic unwrap_or(Option opt, generic default_val) {
    return opt.flag == 0 ? opt.val : default_val;
}

generic unwrap_or_else(Option opt, generic (* closure)()) {
    return opt.flag == 0 ? opt.val : closure();
}

Option map(Option opt, generic (* map)(generic val)) {
    if (opt.flag == 0) {
        opt.val = map(opt.val);
    }
    return opt;
}