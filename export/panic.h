#ifndef PANIC_H_
#define PANIC_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#define panic(err) do{fprintf(stderr, "program panicked at %s, " __FILE__ ":%d\n", (err), __LINE__); abort();}while(0)
#else
#define panic(err) do{fprintf(stderr, "program panicked at %s, " __FILE__ ":%d\n", (err), __LINE__); exit(101);}while(0)
#endif

#endif /* Not PANIC_H_ */