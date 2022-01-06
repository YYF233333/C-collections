// TODO: add doc
#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <stdbool.h>
#include "../export/core.h"

typedef struct Iterator *Iterator;
typedef struct Map *Map;
typedef struct Filter *Filter;

// TODO: compile time polymorphism and generic type

Iterator Iterator_new(void *head, void *(*next)(void *));
Option Iterator_next(Iterator self);
Map Iterator_map(Iterator self, void *(*f)(void *));
Filter Iterator_filter(Iterator self, bool (*predicate)(void *));

Option Map_next(Map self);
Map Map_map(Map self, void *(*f)(void *));
Filter Map_filter(Map self, bool (*predicate)(void *));

Option Filter_next(Filter self);
Map Filter_map(Filter self, void *(*f)(void *));
Filter Filter_filter(Filter self, bool (*predicate)(void *));

#endif /* Not ITERATOR_H_ */