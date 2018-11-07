//
// Created by darin on 07.11.18.
//

#include <gtest/gtest.h>
#include <solution.h>

TEST(TestIDFoo, test1) {
    for (int i = -1000; i < 1000; ++i) {
        ASSERT_EQ(i, foo(i));
    }
}

TEST(TestIDFoo, test2) {
    for (int i = -1000; i < -0; ++i) {
        ASSERT_EQ(i, foo(i));
    }
}


TEST(TEST_TASK, asdf) {
    
}