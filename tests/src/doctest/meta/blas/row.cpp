#include "nmtools/array/utility/row.hpp"
#include "nmtools/array/matrix.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm   = nmtools;
namespace meta = nmtools::meta;

TEST_CASE("row_t" * doctest::test_suite("utility"))
{
    {
        using array_t    = double[2][3];
        using return_t   = meta::resolve_optype_t<nm::row_t,array_t>;
        using expected_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using array_t    = std::array<std::array<double,3>,2>;
        using return_t   = meta::resolve_optype_t<nm::row_t,array_t>;
        using expected_t = std::array<double,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using array_t    = std::vector<std::vector<double>>;
        using return_t   = meta::resolve_optype_t<nm::row_t,array_t>;
        using expected_t = std::vector<double>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using array_t    = nm::array::fixed_matrix<double,2,3>;
        using return_t   = meta::resolve_optype_t<nm::row_t,array_t>;
        using expected_t = nm::array::fixed_vector<double,3>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
    {
        using array_t    = nm::array::dynamic_matrix<double>;
        using return_t   = meta::resolve_optype_t<nm::row_t,array_t>;
        using expected_t = nm::array::dynamic_vector<double>;
        STATIC_CHECK_IS_SAME( return_t, expected_t );
    }
}