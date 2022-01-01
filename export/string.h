/*  
 * an immutable, copy-on-change string
 *  
 * attempt to manage memory automatically without too much change in
 * C string style and API
 * 
 * Strings are provided in thin pointer(char *) with read-only permissions,
 * any attempt to change the contents provided are **UNDEFINED BEHAVIOR**
 * and may crash the program, please modify string with provided API
 * 
 * API which has modify semantics consume the ownership of the string,
 * old string is dropped and new string provided in return value, the
 * previous pointer is now dangling, **DO NOT** dereference it.
 * 
 * Experimental:
 *  reference counting
 *      String_copy API is provided for shallow copy, which increment
 *      ref count, when consuming the string, ref count will be decremented
 *      actual drop only happens when ref count == 0
*/
#ifndef STRING_H_
#define STRING_H_

#endif /* Not STRING_H_ */