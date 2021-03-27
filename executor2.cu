#include "executor.h"
#include "functions.h"

#include <thrust/device_vector.h>
#include <thrust/sequence.h>

#include <iostream>

template<typename T>
int calculate2(const T &op)
{
    // initialize all ten integers of a device_vector to 1
    thrust::device_vector<int> A(10);
    thrust::sequence(A.begin(), A.end());
    thrust::device_vector<int> B(10, 1);

    thrust::transform(A.begin(), A.end(), B.begin(), B.begin(), op);

    return thrust::reduce(B.begin(), B.end(), (int) 0, thrust::plus<int>());
}

class saxpy_functor;
template int calculate2(const saxpy_functor &op);

