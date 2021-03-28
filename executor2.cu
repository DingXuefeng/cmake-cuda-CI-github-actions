#include <thrust/device_vector.h>
#include "functions.h"
#include "transform_reduce.h"

int calculate2() {
    thrust::device_vector<int> A(10);
    thrust::sequence(A.begin(), A.end());
    thrust::device_vector<int> B(10, 1);
    const saxpy_functor op(4);
    return transform_reduce(A,B,op);
}
