/*  
 * core part of the collections, should be guranteed malloc free
 *  
 * inner struct in these libs are usually exported, in order to 
 * avoid heap memory allocation, but please do **NOT** access their field
 * directly(use the API instead)
*/
#ifndef CORE_H_
#define CORE_H_

#include "panic.h"
#include "pair.h"

#endif /* Not CORE_H_ */