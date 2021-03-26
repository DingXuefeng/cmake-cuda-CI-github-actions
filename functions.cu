#include "functions.h"

saxpy_functor::saxpy_functor(float _a) : a(_a) {}

__host__ __device__
float saxpy_functor::operator()(const float& x, const float& y) const { 
    return a * x + y;
}
