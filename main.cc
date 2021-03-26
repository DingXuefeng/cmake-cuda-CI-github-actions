#include "executor.h"
#include <iostream>

int main(void)
{
    int sum = calculate();
    std::cout<<"sum is "<<sum<<std::endl;

    sum = calculate2();
    std::cout<<"sum is "<<sum<<std::endl;

    return 0;
}
