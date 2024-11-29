#pragma once
#include "decomposion.hpp"

namespace nm
{
	namespace linalg
	{
		template<typename T>
		decres::resLU_t<T> lu(const tybase::matrix_base<T>& mtr)
		{
			assert(mtr.is_square());

			auto n = mtr.rows();

			tybase::matrix_base<T> umtr(mtr);
			tybase::matrix_base<T> lmtr(n, n, T(0));

			for (int i = 0; i < n; i++)
				for (int j = i; j < n; j++)
					lmtr(j, i) = umtr(j, i) / umtr(i, i);

			for (int k = 1; k < n; k++)
			{
				for (int i = k - 1; i < n; i++)
					for (int j = i; j < n; j++)
						lmtr(j, i) = umtr(j, i) / umtr(i, i);

				for (int i = k; i < n; i++)
					for (int j = k-1; j < n; j++)
						umtr(i, j) = umtr(i, j) - lmtr(i, k-1)*umtr(k-1, j);
			}


			return decres::resLU_t<T>(lmtr, umtr);
		}
	}
}