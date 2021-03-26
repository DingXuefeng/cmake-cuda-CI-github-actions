#ifndef functions_H
#define functions_H
struct saxpy_functor
{
    const float a;

    saxpy_functor(float _a);

    __host__ __device__
	float operator()(const float& x, const float& y) const;
};
#endif
