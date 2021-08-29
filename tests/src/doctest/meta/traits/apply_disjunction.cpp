#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>

namespace meta = nmtools::meta;

TEST_CASE("apply_disjunction" * doctest::test_suite("traits"))
{
    using vector_t   = std::array<double,3>;
    using array_t    = std::array<std::array<double,3>,5>;
    using fmatrix_t  = nmtools::array::fixed_matrix<double,5,3>;
    using ndarray_t  = nmtools::array::fixed_ndarray<double,5,3>;
    using ndarray3_t = nmtools::array::fixed_ndarray<double,5,3,1>;
    using dndarray_t = nmtools::array::dynamic_ndarray<double>;

    {
        using type_list_t = std::tuple<array_t,fmatrix_t>;
        // any type in type_list_t satisfy is_array2d
        STATIC_CHECK(( meta::apply_disjunction_v<meta::is_array2d,type_list_t> ));
    }
    {
        using type_list_t = std::tuple<ndarray_t,ndarray3_t,dndarray_t>;
        // any type in type_list_t satisfy is_ndarray
        STATIC_CHECK(( meta::apply_disjunction_v<meta::is_ndarray,type_list_t> ));
    }
}