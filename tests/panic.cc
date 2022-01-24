#include <gtest/gtest.h>
#include "../export/core.h"

TEST(Panic, Normal) {
    EXPECT_DEATH(panic(""), "");
}

TEST(Panic, Format) {
    EXPECT_DEATH(panic("%d %f %s", 114514, 1919810.0, "string"), "");
}

TEST(Panic, Unreachable) {
    EXPECT_DEATH(unreachable(), "");
}

TEST(Panic, Unimplemented) {
    EXPECT_DEATH(unimplemented(), "");
}

TEST(Panic, Todo) {
    EXPECT_DEATH(todo(), "");
}