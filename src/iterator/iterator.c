#include <stdlib.h>
#include "../../include/iterator.h"
#include "../../include/iterator_inner.h"

Map Iterator_map(Iterator self, void *(*f)(void *)) {
    Map map = malloc(sizeof(Map));
    map->inner_iter_type = _Iterator;
    map->iter = self;
    map->f = f;
    return map;
}

Filter Iterator_filter(Iterator self, bool (*predicate)(void *)) {
    Filter filter = malloc(sizeof(Filter));
    filter->inner_iter_type = _Iterator;
    filter->iter = self;
    filter->predicate = predicate;
    return filter;
}

Option Iterator_next(Iterator self) {
    return self->next(&self->cur);
}

Iterator Iterator_new(void *head, void *(*next)(void *)) {
    Iterator self = malloc(sizeof(Iterator));
    self->inner_iter_type = _Iterator;
    self->cur = head;
    self->next = next;
    return self;
}

