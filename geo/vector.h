#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

namespace geo
{
template< std::size_t N, typename Real >
struct point
{
	template< std::size_t I >
	Real& at()
	{
		static_assert(I < N, "Invalid coordinate");
		return v[I];
	}

	template< std::size_t I >
	const Real& at() const
	{
		static_assert(I < N, "Invalid coordinate");
		return v[I];
	}

	Real v[N];
};

template< std::size_t N, typename Real >
point< N, Real > operator+(const point< N, Real >& l, const point< N, Real >& r)
{
	point< N, Real > q;
	for (std::size_t i = 0; i < N; ++i)
		q.v[i] = l.v[i] + r.v[i];
	return q;
}

template< std::size_t N, typename Real >
point< N, Real > operator*(Real s, const point< N, Real >& p)
{
	point< N, Real > q;

	for (std::size_t i = 0; i < N; ++i)
		q.v[i] = s * p.v[i];
	return q;
}

template< std::size_t N, typename Real >
point< N, Real > operator*(const point< N, Real >& p, Real s)
{
	return s * p;
}

}

#endif // VECTOR_H
