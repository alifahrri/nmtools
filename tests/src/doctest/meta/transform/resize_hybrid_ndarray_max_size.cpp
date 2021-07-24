#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("resize_hybrid_ndarray_max_size" * doctest::test_suite("resize_hybrid_ndarray_max_size"))
{
    {
        constexpr auto MAX = 5;
        using array_t    = na::hybrid_ndarray<int,3,1>;
        using resized_t  = meta::resize_hybrid_index_array_max_size_t<array_t,MAX>;
        using expected_t = na::hybrid_ndarray<int,MAX,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t);
    }
}