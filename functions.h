#ifndef functions_H
#define functions_H
#include <thrust/detail/config.h>
struct saxpy_functor
{
    const float a;

    saxpy_functor(float _a);

    __device__
	int operator()(const int& x, const int& y) const ;
};
#endif
