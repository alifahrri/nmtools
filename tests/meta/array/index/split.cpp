#include "nmtools/array/split.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/ndarray.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;
namespace view = nm::view;

using namespace nm::literals;

TEST_CASE("split_args" * doctest::test_suite("index"))
{
    SUBCASE("case1")
    {
        using shape_t   = int[1];
        using indices_t = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        // start,stop pair
        // axis=1
        using slice_t   = nmtools_array<nmtools_array<int,2>,1>;
        // don't know how many split will be produces (indices is runtime)
        using expect_t  = nmtools_list<slice_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case2")
    {
        using shape_t   = nmtools_array<int,2>;
        using indices_t = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,2>;
        using expect_t  = nmtools_list<slice_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case3")
    {
        using shape_t   = nmtools_list<int>;
        using indices_t = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_list<nmtools_array<int,2>>;
        using expect_t  = nmtools_list<slice_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case4")
    {
        using shape_t   = na::hybrid_ndarray<int,2,1>;
        using indices_t = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        // NOTE: hybrid ndarray doesn't support nesting
        using slice_t   = nmtools_list<nmtools_array<int,2>>;
        using expect_t  = nmtools_list<slice_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case5")
    {
        using shape_t   = na::fixed_ndarray<int,1>;
        using indices_t = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,1>;
        using expect_t  = nmtools_list<slice_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case6")
    {
        using shape_t   = int[3];
        using indices_t = int;
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,3>;
        using expect_t  = nmtools_list<slice_t>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case7")
    {
        using shape_t   = int[3];
        using indices_t = decltype(1_ct);
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,3>;
        using expect_t  = nmtools_array<slice_t,1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case8")
    {
        using shape_t   = int[1];
        using indices_t = decltype(3_ct);
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,1>;
        using expect_t  = nmtools_array<slice_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case9")
    {
        using shape_t   = int[1];
        using indices_t = decltype(9_ct);
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,1>;
        using expect_t  = nmtools_array<slice_t,9>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case10")
    {
        using shape_t   = int[1];
        using indices_t = decltype(nmtools_tuple{2_ct,4_ct});
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,1>;
        using expect_t  = nmtools_array<slice_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case11")
    {
        using shape_t   = int[2];
        using indices_t = decltype(2_ct);
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,2>;
        using expect_t  = nmtools_array<slice_t,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case12")
    {
        using shape_t   = int[2];
        using indices_t = decltype(nmtools_tuple{2_ct,4_ct});
        using axis_t    = int;
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using slice_t   = nmtools_array<nmtools_array<int,2>,2>;
        using expect_t  = nmtools_array<slice_t,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case13")
    {
        using shape_t   = decltype(nmtools_tuple{9_ct});
        using indices_t = decltype(3_ct);
        using axis_t    = decltype(0_ct);
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        // NOTE: doesn't work,
        // somehow nmtools_tuple{nmtools_tuple{0_ct,3_ct}} deduced to nmtools_tuple{0_ct,3_ct}
        // maybe copy constructor is selected
        // using split0    = decltype(nmtools_tuple{nmtools_tuple{0_ct,3_ct}});
        // using split1    = decltype(nmtools_tuple{nmtools_tuple{3_ct,6_ct}});
        // using split2    = decltype(nmtools_tuple{nmtools_tuple{6_ct,9_ct}});
        using split0    = nmtools_tuple<decltype(nmtools_tuple{0_ct,3_ct})>;
        using split1    = nmtools_tuple<decltype(nmtools_tuple{3_ct,6_ct})>;
        using split2    = nmtools_tuple<decltype(nmtools_tuple{6_ct,9_ct})>;
        using expect_t  = nmtools_tuple<split0,split1,split2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case14")
    {
        using shape_t   = decltype(nmtools_tuple{9_ct});
        using indices_t = decltype(9_ct);
        using axis_t    = decltype(0_ct);
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using split0    = nmtools_tuple<decltype(nmtools_tuple{0_ct,1_ct})>;
        using split1    = nmtools_tuple<decltype(nmtools_tuple{1_ct,2_ct})>;
        using split2    = nmtools_tuple<decltype(nmtools_tuple{2_ct,3_ct})>;
        using split3    = nmtools_tuple<decltype(nmtools_tuple{3_ct,4_ct})>;
        using split4    = nmtools_tuple<decltype(nmtools_tuple{4_ct,5_ct})>;
        using split5    = nmtools_tuple<decltype(nmtools_tuple{5_ct,6_ct})>;
        using split6    = nmtools_tuple<decltype(nmtools_tuple{6_ct,7_ct})>;
        using split7    = nmtools_tuple<decltype(nmtools_tuple{7_ct,8_ct})>;
        using split8    = nmtools_tuple<decltype(nmtools_tuple{8_ct,9_ct})>;
        using expect_t  = nmtools_tuple<split0,split1,split2,split3,split4,split5,split6,split7,split8>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }

    SUBCASE("case15")
    {
        using shape_t   = decltype(nmtools_tuple{2_ct,6_ct});
        using indices_t = decltype(2_ct);
        using axis_t    = decltype(1_ct);
        using result_t  = meta::resolve_optype_t<view::detail::split_args_t,shape_t,indices_t,axis_t>;
        using split0    = decltype(nmtools_tuple{nmtools_tuple{0_ct,2_ct},nmtools_tuple{0_ct,3_ct}});
        using split1    = decltype(nmtools_tuple{nmtools_tuple{0_ct,2_ct},nmtools_tuple{3_ct,6_ct}});
        using expect_t  = nmtools_tuple<split0,split1>;
        NMTOOLS_STATIC_CHECK_IS_SAME( result_t, expect_t );
    }
}