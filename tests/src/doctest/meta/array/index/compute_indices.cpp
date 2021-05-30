#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
using nm::index::compute_indices_t;

TEST_CASE("compute_indices" * doctest::test_suite("index"))
{
    SUBCASE("pair")
    {
        using offset_t   = size_t;
        using shape_t    = std::pair<size_t,size_t>;
        using strides_t  = std::pair<size_t,size_t>;
        using result_t   = meta::resolve_optype_t<compute_indices_t, offset_t, shape_t, strides_t>;
        using expected_t = std::array<size_t,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    SUBCASE("array")
    {
        using offset_t = size_t;
        using shape_t  = std::array<size_t,1>;
        using stride_t = std::array<size_t,1>;
        using result_t = meta::resolve_optype_t<compute_indices_t, offset_t, shape_t, stride_t>;
        using expected_t = std::array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
    SUBCASE("tuple")
    {
        using offset_t = size_t;
        using shape_t  = std::tuple<size_t>;
        using stride_t = std::array<size_t,1>;
        using result_t = meta::resolve_optype_t<compute_indices_t, offset_t, shape_t, stride_t>;
        using expected_t = std::array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }

    SUBCASE("integral_constant")
    {
        using offset_t = size_t;
        using shape_t  = std::tuple<std::integral_constant<size_t,10>>;
        using stride_t = std::array<size_t,1>;
        using result_t = meta::resolve_optype_t<compute_indices_t, offset_t, shape_t, stride_t>;
        using expected_t = std::array<size_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expected_t );
    }
}