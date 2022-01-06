#include <stdlib.h>
#include "../../include/iterator.h"
#include "../../include/iterator_inner.h"

Option Map_next(Map self) {
    Option inner_item;
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
    if (is_none(inner_item)) return None;
    return map(inner_item, self->f);
}

Map Map_map(Map self, void *(*f)(void *)) {
    Map map = malloc(sizeof(Map));
    map->inner_iter_type = _Map;
    map->iter = self;
    map->f = f;
    return map;
}

Filter Map_filter(Map self, bool (*predicate)(void *)) {
    Filter filter = malloc(sizeof(Filter));
    filter->inner_iter_type = _Map;
    filter->iter = self;
    filter->predicate = predicate;
    return filter;
}