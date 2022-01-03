#include <gtest/gtest.h>
#include "../include/assert.h"

TEST(Assert, Succeed) {
    assert(true);
}

TEST(Assert, Fail) {
    EXPECT_DEATH({assert(false);}, "");
}