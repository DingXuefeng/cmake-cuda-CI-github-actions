#include "functions.h"

saxpy_functor::saxpy_functor(float _a) : a(_a) {}

__device__
int saxpy_functor::operator()(const int& x, const int& y) const { 
    return a * x + y;
}
