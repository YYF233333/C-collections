#ifndef	_ASSERT_H
#define _ASSERT_H

#include "panic.h"

#define assert(expr) ((expr) ? (void *)0 : {panic("asserttion failed: "#expr); (void *)0})

#endif /* Not _ASSERT_H */