#ifndef transform_reduce_H
#define transform_reduce_H
#include <thrust/sequence.h>

#include "functions.h"
template<typename S,class T>
int transform_reduce(const thrust::device_vector<S>& a,thrust::device_vector<S>& b,const T &op)
{
    thrust::transform(a.begin(), a.end(), b.begin(), b.begin(), op);
    return thrust::reduce(b.begin(), b.end(), (int) 0, thrust::plus<int>());
}
#endif
