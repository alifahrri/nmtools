#include "nmtools/index/compute_indices.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
using nm::index::compute_indices_t;

#ifdef NMTOOLS_DISABLE_STL
using meta::integral_constant;
#else
using std::integral_constant;
#endif

TEST_CASE("compute_indices" * doctest::test_suite("index"))
{
    SUBCASE("array")
    {
        using offset_t = size_t;
        using shape_t  = nmtools_array<size_t,1>;
        using stride_t = nmtools_array<size_t,1>;
        using result_t = meta::resolve_optype_t<compute_indices_t, offset_t, shape_t, stride_t>;
        using expected_t = nmtools_array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    SUBCASE("tuple")
    {
        using offset_t = size_t;
        using shape_t  = nmtools_tuple<size_t>;
        using stride_t = nmtools_array<size_t,1>;
        using result_t = meta::resolve_optype_t<compute_indices_t, offset_t, shape_t, stride_t>;
        using expected_t = nmtools_array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }

    SUBCASE("integral_constant")
    {
        using offset_t = size_t;
        using shape_t  = nmtools_tuple<integral_constant<size_t,10>>;
        using stride_t = nmtools_array<size_t,1>;
        using result_t = meta::resolve_optype_t<compute_indices_t, offset_t, shape_t, stride_t>;
        using expected_t = nmtools_array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}