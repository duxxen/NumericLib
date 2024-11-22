#pragma once
#include "../types/matrix.hpp"

namespace nm
{
	namespace linalg
	{
		namespace decres
		{
			template <typename T> using resLU_t = std::pair<tybase::matrix_base<T>, tybase::matrix_base<T>>;
			template <typename T> using resQR_t = std::pair<tybase::matrix_base<T>, tybase::matrix_base<T>>;
			template <typename T> using resLUP_t = std::pair<tybase::matrix_base<T>, tybase::matrix_base<T>>;
			template <typename T> using resSVD_t = std::pair<tybase::matrix_base<T>, tybase::matrix_base<T>>;
		}

		template <typename T>
		tybase::matrix_base<T> cholesky(const tybase::matrix_base<T>& mtr);

		template <typename T>
		decres::resSVD_t<T> svd(const tybase::matrix_base<T>& mtr);

		template <typename T>
		decres::resQR_t<T> qr(const tybase::matrix_base<T>& mtr);

		template <typename T> 
		decres::resLU_t<T> lu(const tybase::matrix_base<T>& mtr);

		template <typename T>
		decres::resLUP_t<T> lup(const tybase::matrix_base<T>& mtr);

		
	}
}