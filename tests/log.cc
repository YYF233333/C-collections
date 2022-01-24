#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include "../export/core.h"

class Log : public ::testing::Test {
    protected:
        void SetUp() override {
            setenv("LOG_LEVEL", "WARN", 1);
            if (logger_state == Uninitialized) Logger_init(stdout);
        }
};

TEST_F(Log, Logging) {
    LOG(INFO, "test logging %d", 114514);
}

TEST_F(Log, Enabled) {
    ASSERT_EQ(LOG_ENABLED(WARN), true);
    ASSERT_EQ(LOG_ENABLED(DEBUG), false);
}

TEST_F(Log, Macros) {
    FATAL("this is %s", "FATAL");
    ERROR("this is %s", "ERROR");
    WARN("this is %s", "WARN");
    INFO("this is %s", "INFO");
    DEBUG("this is %s", "DEBUG");
}

TEST_F(Log, Reinit) {
    EXPECT_DEATH({Logger_init(stderr);}, "");
}