#pragma once
#include "dependencies.hpp"

namespace numeric
{
	typedef signed char			int8;
	typedef signed short		int16;
	typedef signed int			int32;
	typedef signed long			int64;
	typedef	signed long long	int128;

	typedef unsigned char		uint8;
	typedef unsigned short		uint16;
	typedef unsigned int		uint32;
	typedef unsigned long		uint64;
	typedef	unsigned long long	uint128;

	typedef float				float32;
	typedef double				float64;
	typedef long double			float128;

	typedef std::pair<float32, float32>		complex32;
	typedef std::pair<float64, float64>		complex64;
	typedef std::pair<float128, float128>	complex128;

	template <typename T = float64> using vect = std::vector<T>;
	template <typename T = float64> using matr = std::vector<vect<T>>;

	typedef vect<uint32>	vect32u;
	typedef vect<int32>		vect32i;
	typedef vect<float64>	vect64f;

	typedef vect<uint32>	matr32u;
	typedef vect<int32>		matr32i;
	typedef matr<float64>	matr64f;

	enum class op
	{
		neg,		// unary	-
		add,		// binary	+
		sub,		// binary	-
		mult,		// binary	*
		div,		// binary	/
		pow,		// unary	^x
		root,		// unary	^1/x
	};
}