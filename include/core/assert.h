/*
 * Asserts that a boolean expression is true at runtime.
 * This will invoke the panic macro if the provided expression cannot be
 * evaluated to true at runtime.
 *
 * This header is designed to be exchangeable with <assert.h> in C std
 */
#ifndef _ASSERT_H
#define _ASSERT_H

#include "panic.h"

#define assert(expr)                                                           \
    (void)((expr) ? (void *)0 : (panic("assertion failed: " #expr), (void *)0))

#endif /* Not _ASSERT_H */