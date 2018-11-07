//
// Created by darin on 07.11.18.
//

#include <gtest/gtest.h>

#include <solution.h>

TEST(TestFromList, test1) {
    std::string reg = "ab+c.aba.*.bac.+.+*";
    char x = 'a';
    int k = 4;
    ASSERT_EQ(1, stackFill(reg, x, k));
}

TEST(TestFromList, test2) {
    std::string reg = "acb..bab.c.*.ab.ba.+.+*a.";
    char x = 'b';
    int k = 2;
    ASSERT_EQ(0, stackFill(reg, x, k));
}

TEST(TestOnMistakesInRegExp, test1) {
    std::string reg = "a.";
    char x = 'a';
    int k = 2;
    ASSERT_EQ(-1, stackFill(reg, x, k));
}

TEST(TestOnMistakesInRegExp, test2) {
    std::string reg = "b+";
    char x = 'b';
    int k = 2;
    ASSERT_EQ(-1, stackFill(reg, x, k));
}

TEST(TestOnMistakesInRegExp, test3) {
    std::string reg = "a*a";
    char x = 'b';
    int k = 2;
    ASSERT_EQ(-1, stackFill(reg, x, k));
}

TEST(TestSituation, test1) {
    std::string reg = "baaa...ba.*aaab.....";
    char x = 'a';
    int k = 6;
    ASSERT_EQ(0, stackFill(reg, x, k));
}