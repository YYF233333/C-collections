#ifndef PAIR_H_
#define PAIR_H_

#define Generic unsigned long long

typedef struct Pair Pair;

//  flag == 0 -> Some, flag == 1 -> None
typedef Pair Option;

//  flag == 0 -> Ok, flag == 1 -> Err
typedef Pair Result;

struct Pair {
    //  flag == 0 -> first type, flag == 1 -> second type
    int flag;
    /*  8 bytes space to store an int(or pointer) val
     *  no float point number support
     *  heap items lifetime should be managed by user
     *  for Result, Err message should be a C string(with \0 ending)
     *  string literals are recommanded
     *  for Option, val at second type is unbounded, do not rely on it
    */
    Generic val;
};

/* ---------------------------------
 *            Generic API
 * ---------------------------------
*/

extern Generic unwrap(Pair opt);
extern Generic unwrap_or(Pair opt, Generic default_val);
extern Generic unwrap_or_else(Pair opt, Generic (* closure)());
extern Pair    map(Pair res, Generic (* map)(Generic val));

/* ---------------------------------
 *            Result API
 * ---------------------------------
*/

#define Ok(val)  new_Ok(val)
#define Err(val) new_Err(val)

extern Result new_Ok(Generic val);
extern Result new_Err(Generic val);
extern int    is_ok(Result res);
extern int    is_err(Result res);
extern char  *unwrap_err(Result res);
extern Result map_err(Result res, Generic (* map)(char *message));

/* ---------------------------------
 *            Option API
 * ---------------------------------
*/

#define Some(val) new_Some(val)
#define None      new_None()

extern Option new_Some(Generic val);
extern Option new_None();
extern int    is_some(Option opt);
extern int    is_none(Option opt);

#undef Generic

#endif /* Not PAIR_H_ */