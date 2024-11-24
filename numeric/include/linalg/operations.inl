#pragma once
#include "operations.hpp"

namespace nm
{
	namespace linalg
	{
		template<typename T>
		T abs(const tybase::vector_base<T>& vct)
		{
			return vct.abs();
		}

		template<typename T>
		auto norm1(const tybase::vector_base<T>& vct)
		{
			return vct.norm1();
		}

		template<typename T>
		auto norm2(const tybase::vector_base<T>& vct)
		{
			return vct.norm2();
		}

		template<typename T>
		auto normi(const tybase::vector_base<T>& vct)
		{
			return vct.normi();
		}

		template<typename T>
		auto norme(const tybase::vector_base<T>& vct)
		{
			return vct.norme();
		}

		template<typename T>
		auto normp(const uint128_t& p, const tybase::vector_base<T>& vct)
		{
			return vct.normp(p);
		}
	}

	template<typename T, typename V>
	auto dot(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2)
	{
		vct1.dot(vct2);
	}

	template<typename T, typename V>
	auto cross(const tybase::vector_base<T>& vct1, const tybase::vector_base<V>& vct2)
	{
		return vct1.cross(vct2);
	}

	template<typename T, typename V>
	auto dot(const tybase::matrix_base<T>& mtr1, const tybase::matrix_base<V>& mtr2)
	{
		return mtr1.dot(mtr2);
	}

	template<typename T, typename V>
	auto dot(const tybase::matrix_base<T>& mtr, const tybase::vector_base<V>& vct)
	{
		return mtr.dot(vct);
	}

	template<typename T, typename V>
	auto dot(const tybase::vector_base<T>& vct, const tybase::matrix_base<V>& mtr)
	{
		return vct.dot(mtr);
	}
}