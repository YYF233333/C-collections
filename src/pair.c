#include <assert.h>
#include "../include/pair.h"

typedef unsigned long long generic;

static Pair Pair_new(int flag, generic val) {
    Pair p;
    p.flag = flag;
    p.val = val;
    return p;
}

Pair new_first(generic val) {
    return Pair_new(0, val);
}

Pair new_second(generic val) {
    return Pair_new(1, val);
}

int is_first(Pair p) {
    return p.flag == 0;
}

int is_second(Pair p) {
    return p.flag == 1;
}

generic unwrap_first(Pair p) {
    // figure out another way to abort in release env
    assert(p.flag == 0);
    return p.val;
}

generic unwrap_second(Pair p) {
    // figure out another way to abort in release env
    assert(p.flag == 1);
    return p.val;
}

Pair map_first(Pair p, generic (* map)(generic val)) {
    if (p.flag == 0) {
        p.val = map(p.val);
    }
    return p;
}

Pair map_second(Pair p, generic (* map)(generic val)) {
    if (p.flag == 1) {
        p.val = map(p.val);
    }
    return p;
}

generic replace(Pair p, generic val) {
    generic old = p.val;
    p.val = val;
    return old;
}