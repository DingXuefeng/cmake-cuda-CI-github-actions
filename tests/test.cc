#include "gtest/gtest.h"
#include "executor.h"

TEST (MyTest, FirstTest) { 
    EXPECT_EQ (145, calculate());
}

TEST (MyTest, SecondTest) { 
    EXPECT_EQ (190, calculate2());
}
