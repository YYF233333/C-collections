#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"

TEST(Pair, Unwrap) {
    Pair p = Ok(1);
    EXPECT_EQ(unwrap(p), 1);
}

TEST(Pair, UnwrapFail) {
    Pair p = Err("err");
    EXPECT_DEATH(unwrap(p), "");
}

TEST(Pair, UnwrapOr) {
    Pair p = Ok(1);
    Pair q = Err("err");
    EXPECT_EQ(unwrap_or(p, 0), 1);
    EXPECT_EQ(unwrap_or(q, 0), 0);
}

unsigned long long cl() { return 123; }

TEST(Pair, UnwrapOrElse) {
    Pair p = Ok(1);
    Pair q = Err("err");
    EXPECT_EQ(unwrap_or_else(p, cl), 1);
    EXPECT_EQ(unwrap_or_else(q, cl), 123);
}

unsigned long long map_cl(unsigned long long val) { return val + 1; }

TEST(Pair, Map) {
    Pair p = Ok(1);
    Pair q = Err("err");
    EXPECT_EQ(unwrap(map(p, map_cl)), 2);
    EXPECT_STREQ(unwrap_err(map(q, map_cl)), "err");
}

char *err_cl(char *message) { return "message processed"; }

TEST(Pair, MapErr) {
    Result err = Err("message");
    EXPECT_STREQ(unwrap_err(map_err(err, err_cl)), "message processed");
}