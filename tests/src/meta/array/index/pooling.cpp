#include "nmtools/array/index/pooling.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace meta = nm::meta;
namespace view = nm::view;

TEST_CASE("shape_pool2d" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using shape_t       = int[4];
        using kernel_size_t = int[2];
        using stride_t      = int[2];
        using ceil_mode_t   = bool;
        using result_t = meta::resolve_optype_t<ix::shape_pool2d_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        using expect_t = nmtools_array<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME(result_t,expect_t);
    }

    SUBCASE("case2")
    {
        using shape_t       = nmtools_array<int,4>;
        using kernel_size_t = int[2];
        using stride_t      = int[2];
        using ceil_mode_t   = bool;
        using result_t = meta::resolve_optype_t<ix::shape_pool2d_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        using expect_t = nmtools_array<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME(result_t,expect_t);
    }

    SUBCASE("case3")
    {
        using shape_t       = nmtools_list<int>;
        using kernel_size_t = int[2];
        using stride_t      = int[2];
        using ceil_mode_t   = bool;
        using result_t = meta::resolve_optype_t<ix::shape_pool2d_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME(result_t,expect_t);
    }

    SUBCASE("case4")
    {
        using shape_t       = na::fixed_ndarray<int,4>;
        using kernel_size_t = int[2];
        using stride_t      = int[2];
        using ceil_mode_t   = bool;
        using result_t = meta::resolve_optype_t<ix::shape_pool2d_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        using expect_t = na::fixed_ndarray<int,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME(result_t,expect_t);
    }

    SUBCASE("case5")
    {
        using shape_t       = na::hybrid_ndarray<int,4,1>;
        using kernel_size_t = int[2];
        using stride_t      = int[2];
        using ceil_mode_t   = bool;
        using result_t = meta::resolve_optype_t<ix::shape_pool2d_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        using expect_t = na::hybrid_ndarray<int,4,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME(result_t,expect_t);
    }
}

TEST_CASE("slice_pool2d" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using indices_t = int[4];
        using shape_t   = int[4];
        using kernel_size_t = int[2];
        using stride_t      = int[2];
        using ceil_mode_t   = bool;
        using result_t = meta::resolve_optype_t<ix::slice_pool2d_t,indices_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        using slice_t  = nmtools_array<int,3>;
        using expect_t = nmtools_array<slice_t,4>;
        NMTOOLS_STATIC_CHECK_IS_SAME(result_t,expect_t);
    }

    SUBCASE("case1")
    {
        using indices_t = int[3];
        using shape_t   = int[3];
        using kernel_size_t = int[2];
        using stride_t      = int[2];
        using ceil_mode_t   = bool;
        using result_t = meta::resolve_optype_t<ix::slice_pool2d_t,indices_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        using slice_t  = nmtools_array<int,3>;
        using expect_t = nmtools_array<slice_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME(result_t,expect_t);
    }
}