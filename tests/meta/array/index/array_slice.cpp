#include "nmtools/array/index/array_slice.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace meta = nm::meta;

TEST_CASE("shape_array_slice" * doctest::test_suite("index"))
{
    // fixed dim, runtime value
    {
        using shape_t  = int[2];
        using slice0_t = int[2];
        using slice1_t = int[2];
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = int[2];
        using slice0_t = int[2];
        using slice1_t = int[1];
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = int[2];
        using slice0_t = int[1];
        using slice1_t = int[1];
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_array<int,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = int[2];
        using slice0_t = int[1];
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        // partial array indexing, dimension depends on shape value
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = int[2];
        using slice0_t = int[2];
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        // partial array indexing, dimension depends on shape value
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    // std array
    {
        using shape_t  = nmtools_array<int,2>;
        using slice0_t = nmtools_array<int,2>;
        using slice1_t = nmtools_array<int,2>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<int,2>;
        using slice0_t = nmtools_array<int,2>;
        using slice1_t = nmtools_array<int,1>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<int,2>;
        using slice0_t = nmtools_array<int,1>;
        using slice1_t = nmtools_array<int,1>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_array<int,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<int,2>;
        using slice0_t = nmtools_array<int,1>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_array<int,2>;
        using slice0_t = nmtools_array<int,2>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    // fixed ndarray
    {
        using shape_t  = nmtools_fixed_ndarray<int,2>;
        using slice0_t = nmtools_fixed_ndarray<int,2>;
        using slice1_t = nmtools_fixed_ndarray<int,2>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        // TODO: deduce as fixed_ndarray
        using expect_t = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_fixed_ndarray<int,2>;
        using slice0_t = nmtools_fixed_ndarray<int,2>;
        using slice1_t = nmtools_fixed_ndarray<int,1>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        // TODO: deduce as fixed_ndarray
        using expect_t = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_fixed_ndarray<int,2>;
        using slice0_t = nmtools_fixed_ndarray<int,1>;
        using slice1_t = nmtools_fixed_ndarray<int,1>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        // TODO: deduce as fixed_ndarray
        using expect_t = nmtools_array<int,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_fixed_ndarray<int,2>;
        using slice0_t = nmtools_fixed_ndarray<int,1>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_fixed_ndarray<int,2>;
        using slice0_t = nmtools_fixed_ndarray<int,2>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using shape_t  = nmtools_list<int>;
        using slice0_t = nmtools_list<int>;
        using slice1_t = nmtools_list<int>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<int>;
        using slice0_t = nmtools_list<int>;
        using slice1_t = nmtools_list<int>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<int>;
        using slice0_t = nmtools_list<int>;
        using slice1_t = nmtools_list<int>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t,slice1_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<int>;
        using slice0_t = nmtools_list<int>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using shape_t  = nmtools_list<int>;
        using slice0_t = nmtools_list<int>;
        using result_t = meta::resolve_optype_t<ix::shape_array_slice_t,shape_t,slice0_t>;
        using expect_t = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}