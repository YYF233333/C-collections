/*  
 * panic support of the core part
 *  
 * provide a convenient way to end the program and print error message
 * arg err should be a C style string(with '\0' ending), format string
 * is currently not supported
*/
#ifndef PANIC_H_
#define PANIC_H_

#define panic(err, ...) _panic("program panicked at \'" err "\', %s:%d\n", ##__VA_ARGS__, __FILE__, __LINE__)

extern void _panic(const char *const format, ...);

#endif /* Not PANIC_H_ */