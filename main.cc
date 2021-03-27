#include "executor.h"
#include "functions.h"
#include <iostream>

int main(void)
{
    int sum = calculate();
    std::cout<<"sum is "<<sum<<std::endl;

    const saxpy_functor &op = saxpy_functor(4);
    sum = calculate2(op);
    std::cout<<"sum is "<<sum<<std::endl;

    return 0;
}
