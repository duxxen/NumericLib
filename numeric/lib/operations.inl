#include "../include/operations.hpp"

namespace nm
{
	template<typename T, typename V>
	auto dot(base_type::matrix_base<T> mtr1, base_type::matrix_base<T> mtr2)
	{
		return mtr1.dot(mtr2);
	}

	template<typename T, typename V>
	auto dot(base_type::vector_base<T> vct1, base_type::vector_base<T> vct2)
	{
		return vct1.dot(vct2);
	}

	template<typename T, typename V>
	auto dot(base_type::matrix_base<T> mtr, base_type::vector_base<T> vct)
	{
		return mtr.dot(vct);
	}

	template<typename T, typename V>
	auto dot(base_type::vector_base<T> vct, base_type::matrix_base<T> mtr)
	{
		return vct.dot(mtr);
	}

	template<typename T>
	T max(base_type::matrix_base<T> mtr)
	{
		return mtr.
	}

}