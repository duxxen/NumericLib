#pragma once
#include "dependencies.hpp"

/***********************************************************************
 * 
 *             NumericLib types declaration file
 * 
 * Declared types:
 *      (u)int8_t -   (un)signed char
 *      (u)int16_t -  (un)signed short
 *      (u)int32_t -  (un)signed int
 *      (u)int64_t -  (un)signed long
 *      (u)int128_t - (un)signed long long
 * 
 *      float32_t -  float
 *      float64_t -  double
 *      float128_t - long double
 * 
 * Basic comp type (config.hpp):
 *      float_t
 * 
 * This file defines all the base types used throughout the library.
 * 
 ***********************************************************************/

namespace nm
{
	typedef signed char			int8_t;
	typedef signed short		int16_t;
	typedef signed int			int32_t;
	typedef signed long			int64_t;
	typedef	signed long long	int128_t;

	typedef unsigned char		uint8_t;
	typedef unsigned short		uint16_t;
	typedef unsigned int		uint32_t;
	typedef unsigned long		uint64_t;
	typedef	unsigned long long	uint128_t;

	typedef float				float32_t;
	typedef double				float64_t;
	typedef long double			float128_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef float32_t float_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef float64_t float_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef float128_t float_t;
	#endif

	namespace typing
	{
		using std::remove_cv_t;
		using std::_Is_any_of_v;
		using std::bool_constant;
		using std::is_integral;
		using std::is_arithmetic;
		using std::is_floating_point;

		using std::enable_if_t;
		using std::conditional_t;
	}
}

