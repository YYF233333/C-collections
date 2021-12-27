#ifndef RESULT_H_
#define RESULT_H_

typedef struct Result Result;

struct Result {
    //  flag == 0 -> Ok, flag == 1 -> Err
    int flag;
    /*  a void * pointer to store actual data
     *  Err message should be a C string(with \0 ending)
     *  string literals are recommanded
    */
    void *val;
};

#define Ok(val) new_Ok(val, sizeof(*val))
#define Err(val) new_Err(val, sizeof(val))

extern Result new_Ok(void *val, size_t size);
extern Result new_Err(void *val, size_t size);
extern int is_ok(Result res);
extern int is_err(Result res);
extern void *unwrap(Result res);
extern void *unwrap_or(Result res, void *default_val);
extern void *unwrap_or_else(Result res, void *(* closure)(char *message));
extern char *unwrap_err(Result res);
extern Result map(Result res, void *(* map)(void *val));

#endif /* Not RESULT_H_ */