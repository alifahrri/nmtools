#include "nmtools/utl.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace utl = nm::utl;
namespace meta = nm::meta;

TEST_CASE("resize_fixed_ndarray" * doctest::test_suite("utl"))
{
    {
        using arg_t = utl::array<int,2>;
        using ref_t = int[2][3][2];
        using resized_t = meta::resize_fixed_ndarray_t<arg_t,ref_t>;
        using expected_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }
    {
        using arg_t = utl::array<int,2>;
        using ref_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        using resized_t = meta::resize_fixed_ndarray_t<arg_t,ref_t>;
        using expected_t = utl::array<utl::array<utl::array<int,2>,3>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }
    {
        using array_t = na::fixed_ndarray<int,3>;
        using ref_t   = utl::array<int,5>;
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = na::fixed_ndarray<int,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
        static_assert( std::is_same_v<resized_t, expected_t> );
    }
}