#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../export/core.h"
#include "../export/string.h"

#define TABLE_SIZE 4096
#define OVERFLOW_SIZE 256

static unsigned BKDRHash(char *str);

typedef struct String String;
typedef struct StringTable StringTable;

struct String {
    char *buf;
    unsigned len;
    unsigned ref;
    unsigned hash; // used for overflow area search
};

struct StringTable {
    unsigned num_of_string;
    unsigned (*hash_func)(char *);
    String *table;
    unsigned table_length;
    String *overflow;
    unsigned overflow_length;
};

StringTable strings = {
    .num_of_string = 0,
    .hash_func = BKDRHash,
    .table = NULL,
    .table_length = 0,
    .overflow = NULL,
    .overflow_length = 0
};

static unsigned BKDRHash(char *str) {
    unsigned seed = 131;
    unsigned hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

char *String_new() {
    // TODO: make it a const fn
    return calloc(1, sizeof(char));
}

char *String_from(char *str) {
    unsigned hash = strings.hash_func(str);
    if (strings.table == NULL) {
        strings.table = calloc(TABLE_SIZE, sizeof(String));
        strings.table_length = TABLE_SIZE;
    }
    String prev = strings.table[hash % TABLE_SIZE];
    if (prev.buf == NULL) {
        prev.ref = 1;
        prev.len = strlen(str);
        prev.buf = malloc(sizeof(char) * prev.len);
        strncpy(prev.buf, str, prev.len);
        return prev.buf;
    } else if (strcmp(prev.buf, str) == 0) {
        prev.ref++;
        // not just return str, for lifetime consider
        return prev.buf;
    } else {
        // collision
        if (strings.overflow == NULL) {
            strings.overflow = calloc(OVERFLOW_SIZE, sizeof(String));
            strings.overflow_length = OVERFLOW_SIZE;
        }
        for (int i = 0; i < strings.overflow_length; i++) {
            if (strings.overflow[i].buf == NULL) {
                String s;
                s.len = strlen(str);
                s.buf = malloc(sizeof(char) * s.len);
                s.hash = hash;
                strings.overflow[i] = s;
                return s.buf;
            }
        }
    }
    unreachable();
}

char *String_push(char *self, char c) {

}

char *String_pop(char *self) {

}

char *String_append(char *self, char *other) {

}

char *String_subString(char *self, unsigned start, unsigned end) {

}

void String_drop(char *str) {
    unsigned hash = strings.hash_func(str);
    String self = strings.table[hash % TABLE_SIZE];
    if (strcmp(self.buf, str) == 0) {
        self.ref--;
        if (self.ref == 0) {
            free(self.buf);
            memset(&strings.table[hash % TABLE_SIZE], 0, sizeof(String));
            assert(strings.table[hash % TABLE_SIZE].buf == NULL);
        }
        return;
    } else {
        // string in overflow area
        for (int i = 0; i < strings.overflow_length; i++) {
            String s = strings.overflow[i];
            if (hash == s.hash) {
                if (strcmp(s.buf, str) == 0) {
                    free(s.buf);
                    memset(&strings.overflow[i], 0, sizeof(String));
                    assert(strings.overflow[i].buf == NULL);
                    return;
                }
            }
        }
    }
    unreachable();
}
