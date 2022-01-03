#include "../../include/panic.h"
#include "../../include/pair.h"

typedef unsigned long long generic;

static Pair Pair_new(int flag, generic val) {
    Pair p = {flag, val};
    return p;
}

#define new_first(val)  Pair_new(0, (val))
#define new_second(val) Pair_new(1, (val))
#define is_first(p)     ((p).flag == 0)
#define is_second(p)    ((p).flag == 1)

static generic unwrap_first(Pair p) {
    if (!is_first(p)) panic("called `unwrap` on Err/None value");
    return p.val;
}

static generic unwrap_second(Pair p) {
    if (!is_second(p)) panic("called Result::unwrap_err on Ok value");
    return p.val;
}

static Pair map_first(Pair p, generic (* map)(generic val)) {
    if (p.flag == 0) { p.val = map(p.val); }
    return p;
}

static Pair map_second(Pair p, generic (* map)(generic val)) {
    if (p.flag == 1) { p.val = map(p.val); }
    return p;
}

static generic replace(Pair p, generic val) {
    generic old = p.val;
    p.val = val;
    return old;
}

/* ---------------------------------
 *            Generic API
 * ---------------------------------
*/

generic unwrap(Pair p) {
    return unwrap_first(p);
}

generic unwrap_or(Pair p, generic default_val) {
    return is_first(p) ? p.val : default_val;
}

generic unwrap_or_else(Pair p, generic (* closure)()) {
    return is_first(p) ? p.val : closure();
}

Pair map(Pair p, generic (* map)(generic val)) {
    return map_first(p, map);
}

/* ---------------------------------
 *            Option API
 * ---------------------------------
*/

Option new_Some(generic val) { return new_first(val); }

Option new_None()            { return new_second(0); }

int is_some(Option opt)      { return is_first(opt); }

int is_none(Option opt)      { return is_second(opt); }

/* ---------------------------------
 *            Result API
 * ---------------------------------
*/

Result new_Ok(generic val)   { return new_first(val); }

Result new_Err(generic val)  { return new_second(val); }

int is_ok(Result res)        { return is_first(res); }

int is_err(Result res)       { return is_second(res); }

char *unwrap_err(Result res) { return (char *)unwrap_second(res); }

Result map_err(Result res, char *(* map)(char *message)) {
    return map_second(res, (generic (*)(generic))map);
}