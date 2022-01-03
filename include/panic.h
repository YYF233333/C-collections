/*  
 * panic support of the core part
 *  
 * provide a convenient way to end the program and print error message
 * arg err should be a C style string(with '\0' ending), could be format
 * string followed by va_args
*/
#ifndef PANIC_H_
#define PANIC_H_

#define panic(err, ...) _panic(__FILE__, __LINE__, err, ##__VA_ARGS__)
#define unreachable() panic("internal error: entered unreachable code")
#define unimplemented() panic("not implemented")
#define todo() panic("not yet implemented")

extern void _panic(const char *const file, unsigned line, const char *const format, ...);

#endif /* Not PANIC_H_ */