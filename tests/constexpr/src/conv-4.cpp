#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(...)

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

#include "nmtools/array/array/conv.hpp"
#include "nmtools/testing/data/array/conv.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, conv2d, case_name); \
    using namespace args; \
    auto result = nmtools::view::conv2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using nmtools::None;

#define CONSTEXPR_CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, constexpr_conv2d, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::array::conv2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

// NOTE: error on constexpr with nostl
// note: member call on member 'right' of union with active member 'left' is not allowed in a constant expression
//                self().right = other.self().right;
// TODO: fix for no-stl build
#ifndef NMTOOLS_DISABLE_STL

// note: constexpr evaluation hit maximum step limit; possible infinite loop?
#ifndef __clang__

// also hit contexpr eval limit on gcc (at least 11.4)
#if 0
TEST_CASE("constexpr_conv2d(case13)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case13, input, weight, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case13, input_a, weight_a, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case13, input_f, weight_f, None, stride_ct, padding_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case13, input_cs_fb, weight_cs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case13, input_cs_hb, weight_cs_hb, None, stride_ct, padding_ct );

    CONSTEXPR_CONV2D_SUBCASE( case13, input_ls_fb, weight_ls_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case13, input_ls_hb, weight_ls_hb, None, stride_ct, padding_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case14)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case14, input, weight, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case14, input_a, weight_a, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case14, input_f, weight_f, None, stride_ct, padding_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case14, input_cs_fb, weight_cs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case14, input_cs_hb, weight_cs_hb, None, stride_ct, padding_ct );

    CONSTEXPR_CONV2D_SUBCASE( case14, input_ls_fb, weight_ls_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case14, input_ls_hb, weight_ls_hb, None, stride_ct, padding_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case15)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case15, input, weight, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case15, input_a, weight_a, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case15, input_f, weight_f, None, stride_ct, padding_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case15, input_cs_fb, weight_cs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case15, input_cs_hb, weight_cs_hb, None, stride_ct, padding_ct );

    CONSTEXPR_CONV2D_SUBCASE( case15, input_ls_fb, weight_ls_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case15, input_ls_hb, weight_ls_hb, None, stride_ct, padding_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case16)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case16, input, weight, bias, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case16, input_a, weight_a, bias_a, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case16, input_f, weight_f, bias_f, stride_ct, padding_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case16, input_cs_fb, weight_cs_fb, bias_cs_fb, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case16, input_cs_hb, weight_cs_hb, bias_cs_hb, stride_ct, padding_ct );

    // TODO: fix constexpr conv2d with (clipped-shape) bias
    #if 0
    CONSTEXPR_CONV2D_SUBCASE( case16, input_ls_fb, weight_ls_fb, bias_ls_fb, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case16, input_ls_hb, weight_ls_hb, bias_ls_hb, stride_ct, padding_ct );
    #endif
    #endif
}
#endif

#endif // __clang__

#endif // NMTOOLS_DISABLE_STL