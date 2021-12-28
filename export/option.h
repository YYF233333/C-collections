#ifndef OPTION_H_
#define OPTION_H_

typedef struct Option Option;

struct Option {
    //  flag == 0 -> Some, flag == 1 -> None
    int flag;
    /*  8 bytes space to store an int(or pointer) val
     *  no float point number support
     *  heap items lifetime should be managed by user
    */
    unsigned long long val;
};

#define Some(val) new_Some(val)
#define None new_None()

extern Option new_Some(unsigned long long val);
extern Option new_None();
extern int is_some(Option opt);
extern int is_none(Option opt);
extern unsigned long long unwrap(Option opt);
extern unsigned long long unwrap_or(Option opt, unsigned long long default_val);
extern unsigned long long unwrap_or_else(Option opt, unsigned long long (* closure)());
extern Option map(Option opt, unsigned long long (* map)(unsigned long long val));

#endif /* Not OPTION_H_ */