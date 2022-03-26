#include "nmtools/array/index/conv.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/ndarray.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace meta = nm::meta;

TEST_CASE("shape_conv2d" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using shape_t        = int[4];
        using out_channels_t = int;
        using kernel_size_t  = int[2];
        using padding_t      = int[2];
        using stride_t       = int[2];
        using dilations_t    = int[2];
        using result_t       = meta::resolve_optype_t<
            ix::shape_conv2d_t, shape_t, out_channels_t,
            kernel_size_t, padding_t, stride_t, dilations_t
        >;
        using expect_t = nmtools_array<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case2")
    {
        using shape_t        = nmtools_array<int,4>;
        using out_channels_t = int;
        using kernel_size_t  = nmtools_array<int,2>;
        using padding_t      = nmtools_array<int,2>;
        using stride_t       = nmtools_array<int,2>;
        using dilations_t    = nmtools_array<int,2>;
        using result_t       = meta::resolve_optype_t<
            ix::shape_conv2d_t, shape_t, out_channels_t,
            kernel_size_t, padding_t, stride_t, dilations_t
        >;
        using expect_t = nmtools_array<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case3")
    {
        using shape_t        = na::fixed_ndarray<int,4>;
        using out_channels_t = int;
        using kernel_size_t  = na::fixed_ndarray<int,2>;
        using padding_t      = na::fixed_ndarray<int,2>;
        using stride_t       = na::fixed_ndarray<int,2>;
        using dilations_t    = na::fixed_ndarray<int,2>;
        using result_t       = meta::resolve_optype_t<
            ix::shape_conv2d_t, shape_t, out_channels_t,
            kernel_size_t, padding_t, stride_t, dilations_t
        >;
        using expect_t = na::fixed_ndarray<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case4")
    {
        using shape_t        = na::hybrid_ndarray<int,4,1>;
        using out_channels_t = int;
        using kernel_size_t  = na::hybrid_ndarray<int,2,1>;
        using padding_t      = na::hybrid_ndarray<int,2,1>;
        using stride_t       = na::hybrid_ndarray<int,2,1>;
        using dilations_t    = na::hybrid_ndarray<int,2,1>;
        using result_t       = meta::resolve_optype_t<
            ix::shape_conv2d_t, shape_t, out_channels_t,
            kernel_size_t, padding_t, stride_t, dilations_t
        >;
        using expect_t = na::hybrid_ndarray<int,4,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case5")
    {
        using shape_t        = nmtools_list<int>;
        using out_channels_t = int;
        using kernel_size_t  = nmtools_list<int>;
        using padding_t      = nmtools_list<int>;
        using stride_t       = nmtools_list<int>;
        using dilations_t    = nmtools_list<int>;
        using result_t       = meta::resolve_optype_t<
            ix::shape_conv2d_t, shape_t, out_channels_t,
            kernel_size_t, padding_t, stride_t, dilations_t
        >;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}