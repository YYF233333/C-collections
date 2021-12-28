#ifndef RESULT_H_
#define RESULT_H_

typedef struct Result Result;

struct Result {
    //  flag == 0 -> Ok, flag == 1 -> Err
    int flag;
    /*  8 bytes space to store an int(or pointer) val
     *  no float point number support
     *  heap items lifetime should be managed by user
     *  Err message should be a C string(with \0 ending)
     *  string literals are recommanded
    */
    unsigned long long val;
};

#define Ok(val) new_Ok(val)
#define Err(val) new_Err(val)

extern Result new_Ok(unsigned long long val);
extern Result new_Err(unsigned long long val);
extern int is_ok(Result res);
extern int is_err(Result res);
extern unsigned long long unwrap(Result res);
extern unsigned long long unwrap_or(Result res, unsigned long long default_val);
extern unsigned long long unwrap_or_else(Result res, unsigned long long (* closure)(char *message));
extern char *unwrap_err(Result res);
extern Result map(Result res, unsigned long long (* map)(unsigned long long val));

#endif /* Not RESULT_H_ */