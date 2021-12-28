#ifndef PAIR_H_
#define PAIR_H_

typedef struct Pair Pair;

struct Pair {
    //  flag == 0 -> first type, flag == 1 -> second type
    int flag;
    /*  8 bytes space to store an int(or pointer) val
     *  no float point number support
     *  heap items lifetime should be managed by user
    */
    unsigned long long val;
};

extern Pair new_first(unsigned long long val);
extern Pair new_second(unsigned long long val);
extern int is_first(Pair p);
extern int is_second(Pair p);
extern unsigned long long unwrap_first(Pair p);
extern unsigned long long unwrap_second(Pair p);
extern Pair map_first(Pair p, unsigned long long (* map)(unsigned long long val));
extern Pair map_second(Pair p, unsigned long long (* map)(unsigned long long val));
extern unsigned long long replace(Pair p, unsigned long long val);

#endif /* Not PAIR_H_ */