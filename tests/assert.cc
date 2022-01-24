#include <gtest/gtest.h>
#include "../export/core.h"

TEST(Assert, Succeed) {
    assert(true);
}

TEST(Assert, Fail) {
    EXPECT_DEATH({assert(false);}, "");
}