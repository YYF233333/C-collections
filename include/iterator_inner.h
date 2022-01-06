#ifndef ITERATOR_INNER_H_
#define ITERATOR_INNER_H_

#include "pair.h"

typedef enum IteratorType IteratorType;

enum IteratorType{_Iterator, _Map, _Filter};

struct Iterator {
    IteratorType inner_iter_type;
    void *cur;
    Option (*next)(void **cur);
};

struct Map {
    IteratorType inner_iter_type;
    void *iter;
    void *(*f)(void *);
};

struct Filter {
    IteratorType inner_iter_type;
    void *iter;
    void *(*predicate)(void *);
};

#endif /* Not ITERATOR_INNER_H_ */