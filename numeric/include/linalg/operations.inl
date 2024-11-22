#pragma once
#include "operations.hpp"

namespace nm
{
	namespace linalg
	{

	}

	template<typename T, typename V>
	auto dot(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2)
	{
		using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
		assert(vct1.size() == vct2.size());

		RT product = 0;
		for (int i = 0; i < vct1.size(); i++)
			product += vct1[i] * vct2[i];
		return product;
	}

	template<typename T, typename V>
	auto cross(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2)
	{
		using RT = tycomp::conditional_t<tycomp::is_stronger<T, V>::value, T, V>;
		assert(vct1.size() == vct2.size() && vct1.size() == 3);

		return tybase::vector_base<RT>({
			vct1[1] * vct2[2] - vct1[2] * vct2[1],
			vct1[2] * vct2[0] - vct1[0] * vct2[2],
			vct1[0] * vct2[1] - vct1[1] * vct2[0]
		});
	}

	template<typename T, typename V>
	auto dot(const tybase::matrix_base<T>& mtr1, const tybase::matrix_base<V>& mtr2)
	{
	}

	template<typename T, typename V>
	auto dot(const tybase::matrix_base<T>& mtr, const tybase::vector_base<V>& vct)
	{
	}

	template<typename T, typename V>
	auto dot(const tybase::vector_base<T>& vct, const tybase::matrix_base<V>& mtr)
	{
	}
}