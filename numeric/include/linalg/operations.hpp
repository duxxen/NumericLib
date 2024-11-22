#pragma once
#include "../types.hpp"
#include "../types/complex.hpp"
#include "../types/vector.hpp"
#include "../types/matrix.hpp"

namespace nm
{
	namespace linalg
	{
		template <typename T, typename... Rest>
		auto multidot(const nm::tybase::vector_base<T> vct, const Rest&... rest);
	}
}