#include <limits.h>
#include "../../export/core.h"

Rc Rc_new(void (*free)(const Rc *)) {
    Rc rc = {free, 1};
    return rc;
}

unsigned Rc_count(Rc self) {
    return self.count;
}

void Rc_inc_count(Rc *self) {
    assert(self);
    if (self->count < UINT_MAX) {
        self->count++;
    } else {
        panic("reference count overflow");
    }
}

void Rc_dec_count(Rc *self) {
    assert(self);
    if (self->count == 0) panic("reference count underflow");
    self->count--;
    if (self->count == 0) self->free(self);
}