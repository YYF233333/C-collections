/*  
 * intrusive reference counting library
 *  
 * add struct Rc to the object you want to manage with ref count.
 * 
 * Rc_new and Rc_count method are added for convenience, direct
 * construct and field access are ok.
 * 
 * Rc_inc_count and Rc_dec_count are recommanded, since they apply
 * bound check and will abort at over/underflow.  If this overhead is
 * unbearable, manage the count yourself.
 * 
 * free method should be provided by user. Because the function only
 * receive pointer to Rc, you probably need container_of macro, which is
 * provided in "container.h".
 * 
 * NOTE: This library **DO NOT** ensure your object will be managed properly,
 *  counting reference correctly rely on the user.
*/
#ifndef RC_H_
#define RC_H_

#include <stdbool.h>
#include "container.h"
#include "pair.h"

typedef struct Rc {
    void (*free)(const struct Rc *);
    unsigned count;
} Rc;

extern Rc Rc_new(void (*free)(const Rc *));
extern unsigned Rc_count(Rc self);
extern void Rc_inc_count(Rc *self);
extern void Rc_dec_count(Rc *self);

#endif /* NOT RC_H_ */