#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

TEST_CASE("resize_fixed_ndarray" * doctest::test_suite("meta"))
{
    {
        using array_t = na::fixed_ndarray<int,3>;
        using ref_t   = std::array<int,5>;
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = na::fixed_ndarray<int,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
        static_assert( std::is_same_v<resized_t, expected_t> );
    }
    {
        using array_t = na::fixed_ndarray<int,3>;
        using ref_t   = na::fixed_ndarray<int,2,3,1>;
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = na::fixed_ndarray<int,2,3,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
        static_assert( std::is_same_v<resized_t, expected_t> );
    }
    {
        using array_t = std::array<int,3>;
        using ref_t   = std::array<int,5>;
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = std::array<int,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }
    {
        using array_t = int[3];
        using ref_t   = std::array<int,5>;
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = na::fixed_ndarray<int,5>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }
    {
        using array_t = std::array<int,3>;
        using ref_t   = int[2][3][1];
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = std::array<std::array<std::array<int,1>,3>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }
    {
        using array_t = std::array<int,3>;
        using ref_t   = na::fixed_ndarray<int,2,3,1>;
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = std::array<std::array<std::array<int,1>,3>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }
    {
        using array_t = std::array<int,3>;
        using ref_t   = int[2][3][4][1];
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = std::array<std::array<std::array<std::array<int,1>,4>,3>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }

    {
        using array_t = na::fixed_ndarray<unsigned char,1>;
        using ref_t   = unsigned char[2][3][2];
        using resized_t  = meta::resize_fixed_ndarray_t<array_t,ref_t>;
        using expected_t = na::fixed_ndarray<unsigned char,2,3,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( resized_t, expected_t );
    }
}