#include "../types.hpp"
#include "../types/vector.hpp"
#include "../types/matrix.hpp"

namespace nm
{
	namespace linalg
	{
		template <typename MT, typename VT>
		auto gauss_solve(tybase::matrix_base<MT> mtr, tybase::vector_base<VT> vct);

		template <typename MT, typename VT>
		auto gauss_jordan_solve(tybase::matrix_base<MT> mtr, tybase::vector_base<VT> vct);

		template <typename MT, typename VT>
		auto tridiagonal_solve(tybase::matrix_base<MT> mtr, tybase::vector_base<VT> vct);

		template <typename MT, typename VT>
		auto solve(tybase::matrix_base<MT> mtr, tybase::vector_base<VT> vct);
	}
}