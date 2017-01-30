#ifndef INPLACE_H
#define INPLACE_H

template <class T>
struct in_place_type_t
{
	explicit in_place_type_t() = default;
};

template <class T>
constexpr in_place_type_t< T > in_place_type{};

#endif // INPLACE_H
