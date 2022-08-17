/*
 * core part of the collections, should be guranteed malloc free
 *
 * inner struct in these libs are usually exported, in order to
 * avoid heap memory allocation, but please do **NOT** modify their field
 * directly(use the API instead)
 * read only access to the field is safe in principle, but the value may
 * out of your expectation, be careful
 */
#ifndef CORE_H_
#define CORE_H_

#include "../include/core/assert.h"
#include "../include/core/log.h"
#include "../include/core/pair.h"
#include "../include/core/panic.h"
#include "../include/core/rc.h"

#endif /* Not CORE_H_ */