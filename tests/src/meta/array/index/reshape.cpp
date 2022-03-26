#include "nmtools/array/index/reshape.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/testing/doctest.hpp"

namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace meta = nmtools::meta;

using namespace nmtools::literals;

#define declval(type) meta::declval<type>()

TEST_CASE("shape_reshape" * doctest::test_suite("index"))
{
    {
        using src_shape_t = int[2];
        using dst_shape_t = int[3];
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = nmtools_array<uint32_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_shape_t = nmtools_array<int,2>;
        using dst_shape_t = nmtools_array<int,3>;
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = nmtools_array<uint32_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_shape_t = nmtools_list<int>;
        using dst_shape_t = nmtools_list<int>;
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = nmtools_list<uint32_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_shape_t = na::fixed_ndarray<int,2>;
        using dst_shape_t = na::fixed_ndarray<int,3>;
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = na::fixed_ndarray<uint32_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_shape_t = na::hybrid_ndarray<int,2,1>;
        using dst_shape_t = na::hybrid_ndarray<int,3,1>;
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = na::hybrid_ndarray<uint32_t,3,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_shape_t = na::dynamic_ndarray<int>;
        using dst_shape_t = na::dynamic_ndarray<int>;
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = meta::error::SHAPE_RESHAPE_UNSUPPORTED<src_shape_t,dst_shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_shape_t = decltype(nmtools_tuple{12_ct});
        using dst_shape_t = decltype(nmtools_tuple{12_ct,1_ct});
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = decltype(nmtools_tuple{12_ct,1_ct});
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_shape_t = decltype(nmtools_tuple{12_ct});
        using dst_shape_t = decltype(nmtools_tuple{12_ct,12_ct});
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = meta::error::SHAPE_RESHAPE_INVALID<src_shape_t,dst_shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    #ifdef __clang__
    {
        using src_shape_t = decltype(nmtools_tuple{12_ct});
        using dst_shape_t = decltype(nmtools_tuple{12_ct,"-1"_ct});
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = nmtools_tuple<meta::ct<12u>,meta::ct<1u>>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    #else
    {
        using src_shape_t = decltype(nmtools_tuple{12_ct});
        using dst_shape_t = decltype(nmtools_tuple{12_ct,"-1"_ct});
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = nmtools_array<unsigned int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    #endif
    {
        using src_shape_t = int[2];
        using dst_shape_t = decltype(nmtools_tuple{12_ct,1_ct});
        using result_t = meta::resolve_optype_t<ix::shape_reshape_t,src_shape_t,dst_shape_t>;
        using expect_t = nmtools_maybe<decltype(nmtools_tuple{12_ct,1_ct})>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    #if 1
    {
        using src_shape_t = int[2];
        using dst_shape_t = nmtools_array<size_t,1>;
        using result_t = decltype(ix::shape_reshape(declval(src_shape_t),declval(dst_shape_t)));
        using expect_t = nmtools_maybe<dst_shape_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    #endif
}