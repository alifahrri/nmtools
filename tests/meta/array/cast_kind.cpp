#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

TEST_CASE("cast_kind" * doctest::test_suite("meta"))
{
    {
        using src_t  = int[2];
        using kind_t = kind::fixed_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::fixed_ndarray<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_t  = int[2][3][2];
        using kind_t = kind::fixed_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::fixed_ndarray<int,2,3,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using src_t  = int[2];
        using kind_t = kind::hybrid_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::hybrid_ndarray<int,2,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_t  = int[2][3][2];
        using kind_t = kind::hybrid_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::hybrid_ndarray<int,2*3*2,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using src_t  = int[2];
        using kind_t = kind::nested_array_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = nmtools_array<int,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_t  = int[2][3][2];
        using kind_t = kind::nested_array_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = nmtools_array<nmtools_array<nmtools_array<int,2>,3>,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    {
        using src_t  = int[2];
        using kind_t = kind::dynamic_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_t  = int[2][3][2];
        using kind_t = kind::dynamic_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::dynamic_ndarray<int>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    // uint8
    {
        using src_t  = unsigned char[2];
        using kind_t = kind::fixed_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::fixed_ndarray<unsigned char,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
    {
        using src_t  = unsigned char[2][3][2];
        using kind_t = kind::fixed_t;
        using result_t = meta::resolve_optype_t<nm::cast_kind_t,src_t,kind_t>;
        using expect_t = na::fixed_ndarray<unsigned char,2,3,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}