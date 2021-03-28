#include <thrust/sequence.h>

template<typename S,typename T>
int transform_reduce(const S& a,S& b,const T &op)
{
    thrust::transform(a.begin(), a.end(), b.begin(), b.begin(), op);
    return thrust::reduce(b.begin(), b.end(), (int) 0, thrust::plus<int>());
}
