#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb);
#endif

#include "nmtools/array/array/atleast_1d.hpp"
#include "nmtools/testing/data/constexpr/atleast_1d.hpp"
#include "nmtools/testing/doctest.hpp"

namespace view = nmtools::view;
namespace meta = nmtools::meta;

#define CONSTEXPR_ATLEAST_1D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, constexpr_atleast_1d, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::array::atleast_1d(__VA_ARGS__); \
    NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_1d(case1)" * doctest::test_suite("array::constexpr_atleast_1d"))
{
    CONSTEXPR_ATLEAST_1D_SUBCASE( case1, a );
}

TEST_CASE("atleast_1d(case2)" * doctest::test_suite("array::constexpr_atleast_1d"))
{
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_a );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_f );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_h );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_cs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_cs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_fs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_fs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_hs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_hs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_ls_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case2, a_ls_hb );

    {
        NMTOOLS_TESTING_DECLARE_NS(array, constexpr_atleast_1d, case2);
        using namespace args;

        static_assert( meta::is_fixed_size_v<decltype(a_hs_fb)> );
        
        using view_type = meta::remove_cvref_t<decltype(*view::atleast_1d(a_hs_fb))>;
        static_assert( meta::is_fixed_size_v<view_type> );
        static_assert( meta::is_bounded_dim_v<view_type> );
    }

    #endif
}

TEST_CASE("atleast_1d(case3)" * doctest::test_suite("array::constexpr_atleast_1d"))
{
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_a );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_f );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_h );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_cs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_cs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_fs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_fs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_hs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_hs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_ls_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case3, a_ls_hb );
    #endif
}

TEST_CASE("atleast_1d(case4)" * doctest::test_suite("array::constexpr_atleast_1d"))
{
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_a );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_f );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_h );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_cs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_cs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_fs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_fs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_hs_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_hs_hb );

    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_ls_fb );
    CONSTEXPR_ATLEAST_1D_SUBCASE( case4, a_ls_hb );

    #endif
}