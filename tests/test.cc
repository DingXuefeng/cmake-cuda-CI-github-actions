#include "gtest/gtest.h"
#include "functions.h"
#include "executor.h"

TEST (MyTest, FirstTest) { 
    EXPECT_EQ (145, calculate());
}

TEST (MyTest, SecondTest) { 
    const saxpy_functor &op = saxpy_functor(4);
    EXPECT_EQ (190, calculate2(op));
}
