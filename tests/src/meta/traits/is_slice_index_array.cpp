#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

#include "nmtools/array/ndarray.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace meta = nm::meta;

TEST_CASE("is_slice_index_array" * doctest::test_suite("meta::is_slice_index_array"))
{
    SUBCASE("case1")
    {
        using T = int;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case2")
    {
        using T = float;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case3")
    {
        using T = nm::ellipsis_t;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case4")
    {
        using T = nm::none_t;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case5")
    {
        using T = nmtools_either<int,nm::ellipsis_t>;
        // not directly considered as slice index
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }

    SUBCASE("case6")
    {
        using T = nmtools_array<int,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case6")
    {
        using T = nmtools_array<nmtools_either<int,size_t>,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case7")
    {
        using T = nmtools_array<float,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case8")
    {
        using T = nmtools_array<nm::ellipsis_t,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case9")
    {
        using T = nmtools_array<nmtools_either<int,float>,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case10")
    {
        using T = nmtools_array<nmtools_either<int,nm::ellipsis_t>,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }

    SUBCASE("case11")
    {
        using T = nmtools_list<int>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case12")
    {
        using T = nmtools_list<nmtools_either<int,size_t>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case13")
    {
        using T = nmtools_list<float>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case14")
    {
        using T = nmtools_list<nm::ellipsis_t>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case15")
    {
        using T = nmtools_list<nmtools_either<int,float>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case16")
    {
        using T = nmtools_list<nmtools_either<int,nm::ellipsis_t>>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }

    SUBCASE("case17")
    {
        using T = na::fixed_ndarray<int,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case18")
    {
        using T = na::fixed_ndarray<nmtools_either<int,size_t>,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case19")
    {
        using T = na::fixed_ndarray<float,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case20")
    {
        using T = na::fixed_ndarray<nm::ellipsis_t,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case21")
    {
        using T = na::fixed_ndarray<nmtools_either<int,float>,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case22")
    {
        using T = na::fixed_ndarray<nmtools_either<int,nm::ellipsis_t>,3>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case22")
    {
        using T = na::fixed_ndarray<nmtools_either<int,nm::ellipsis_t>,3,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case23")
    {
        using T = na::hybrid_ndarray<nmtools_either<int,nm::ellipsis_t>,3,3>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case22")
    {
        using T = na::dynamic_ndarray<nmtools_either<int,nm::ellipsis_t>>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }

    SUBCASE("case23")
    {
        using T = na::hybrid_ndarray<int,3,1>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case24")
    {
        using T = na::hybrid_ndarray<nmtools_either<int,size_t>,3,1>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case25")
    {
        using T = na::hybrid_ndarray<float,3,1>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case26")
    {
        using T = na::hybrid_ndarray<nm::ellipsis_t,3,1>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
    SUBCASE("case27")
    {
        using T = na::hybrid_ndarray<nmtools_either<int,float>,3,1>;
        NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_slice_index_array, T );
    }
    SUBCASE("case28")
    {
        using T = na::hybrid_ndarray<nmtools_either<int,nm::ellipsis_t>,3,1>;
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_slice_index_array, T );
    }
}