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
 * Also this file defines namespace 'tycomp' which is used to compare
 * different types by different features such as: (sizeof, is_float, etc.)
 * 
 *
 ***********************************************************************/

namespace nm
{
	// **************************************************************************************** STD FUNCTIONS

	using std::abs;
	using std::pow;
	using std::sqrt;

	// **************************************************************************************** TYPE DEFENITIONS

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

	typedef uint128_t						size1D_t;
	typedef std::pair<size1D_t, size1D_t>   size2D_t;

	#ifdef BASIC_COMP_TYPE_FLOAT32
	typedef float32_t float_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT64
	typedef float64_t float_t;
	#endif
	#ifdef BASIC_COMP_TYPE_FLOAT128
	typedef float128_t float_t;
	#endif

	// **************************************************************************************** TYPE COMPARING

	namespace tycomp
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