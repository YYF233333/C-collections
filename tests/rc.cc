#include <stdlib.h>
#include <gtest/gtest.h>
#include "../export/core.h"

struct Dummy {
    int *some_data;
    Rc counter;
    bool free_is_called;
};

void myfree(const Rc *counter) {
    struct Dummy *dum = container_of(counter, struct Dummy, counter);
    free(dum->some_data);
    dum->free_is_called = true;
}

class RcTest : public ::testing::Test {
    protected:
        void SetUp() override {
            int *data = (int *)malloc(sizeof(int) * 10);
            this->dummy.some_data = data;
            this->dummy.counter = Rc_new(myfree);
            this->dummy.free_is_called = false;
        }
        struct Dummy dummy;
        bool free_is_called;
};

TEST_F(RcTest, New) {
    EXPECT_EQ(Rc_count(this->dummy.counter), 1);
}

TEST_F(RcTest, Inc) {
    Rc_inc_count(&this->dummy.counter);
    EXPECT_EQ(Rc_count(this->dummy.counter), 2);
}

TEST_F(RcTest, Dec) {
    Rc_dec_count(&this->dummy.counter);
    EXPECT_EQ(Rc_count(this->dummy.counter), 0);
    EXPECT_EQ(this->dummy.free_is_called, true);
}

TEST_F(RcTest, Overflow) {
    this->dummy.counter.count = UINT32_MAX;
    EXPECT_DEATH({Rc_inc_count(&this->dummy.counter);}, "");
}

TEST_F(RcTest, Underflow) {
    Rc_dec_count(&this->dummy.counter);
    EXPECT_DEATH({Rc_dec_count(&this->dummy.counter);}, "");
}