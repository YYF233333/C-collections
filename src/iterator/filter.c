#include <stdlib.h>
#include "../../include/iterator.h"
#include "../../include/iterator_inner.h"

Option Filter_next(Filter self) {
    Option inner_item;
    while (true) {
        switch (self->inner_iter_type) {
            case _Iterator: {
                inner_item = Iterator_next((Iterator)self->iter);
                break;
            }
            case _Map: {
                inner_item = Map_next((Map)self->iter);
                break;
            }
            case _Filter: {
                inner_item = Filter_next((Filter)self->iter);
                break;
            }
            default: unreachable();
        }
        if (is_none(inner_item)) {
            return None;
        } else if (self->predicate(unwrap(inner_item)) == true) {
            return inner_item;
        }
    }
}

Map Filter_map(Filter self, void *(*f)(void *)) {
    Map map = malloc(sizeof(Map));
    map->inner_iter_type = _Filter;
    map->iter = self;
    map->f = f;
    return map;
}

Filter Filter_filter(Filter self, bool (*predicate)(void *)) {
    Filter filter = malloc(sizeof(Filter));
    filter->inner_iter_type = _Filter;
    filter->iter = self;
    filter->predicate = predicate;
    return filter;
}