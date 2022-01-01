/*  
 * panic support of the core part
 *  
 * provide a convenient way to end the program and print error message
 * arg err should be a C style string(with '\0' ending), could be format
 * string with va_args
*/
#ifndef PANIC_H_
#define PANIC_H_

#define panic(err, ...) _panic(__FILE__, __LINE__, err, ##__VA_ARGS__)

extern void _panic(const char *const file, unsigned line, const char *const format, ...);

#endif /* Not PANIC_H_ */