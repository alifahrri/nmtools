#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(...)

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::array::kind::ndarray_ls_db);
#endif

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY) && defined(NMTOOLS_BUILD_CONSTEXPR_TESTS)
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
    constexpr auto result = RUN_conv2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#ifndef NMTOOLS_BUILD_CONSTEXPR_TESTS

TEST_CASE("conv2d(case9)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case9, input, weight, None, stride );
    CONV2D_SUBCASE( case9, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case9, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case9, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case9, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case9, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}


TEST_CASE("conv2d(case10)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case10, input, weight, None, stride );
    CONV2D_SUBCASE( case10, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case10, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case10, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case10, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case10, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}


TEST_CASE("conv2d(case11)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case11, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case11, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case11, input_h, weight_h, None, stride_h, padding_h );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case11, input_d, weight_d, None, stride_v, padding_v );
    #endif // NMTOOLS_DISABLE_STL

    #else
    CONV2D_SUBCASE( case11, input_cs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_fs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    // TODO: fix fixed/bounded-size inference for utl
    //     (gdb) bt
    // #0  __memmove_avx_unaligned_erms () at ..
    // #1  0x0000555555808d78 in nmtools::utl::vector<... >::resize 
    // #2  0x0000555555999899 in nmtools::array::ndarray_t<nmtools::utl::vector<int, nmtools::utl::allocator<int> >, ... > const&)
    CONV2D_SUBCASE( case11, input_hs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_ds_db, None, stride_a, padding_a );
    #endif // NMTOOLS_DISABLE_STL

    CONV2D_SUBCASE( case11, input_ls_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_cs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case11, input_hs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_cs_db, None, stride_a, padding_a );
    #endif // NMTOOLS_DISABLE_STL

    CONV2D_SUBCASE( case11, input_ls_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_fs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case11, input_hs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_fs_db, None, stride_a, padding_a );
    #endif // NMTOOLS_DISABLE_STL

    CONV2D_SUBCASE( case11, input_ls_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_hs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case11, input_ds_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_hs_db, None, stride_a, padding_a );
    #endif // NMTOOLS_DISABLE_STL

    CONV2D_SUBCASE( case11, input_ls_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_ds_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case11, input_hs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_ds_db, None, stride_a, padding_a );
    #endif // NMTOOLS_DISABLE_STL

    CONV2D_SUBCASE( case11, input_ls_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_ls_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case11, input_hs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_ls_db, None, stride_a, padding_a );
    #endif // NMTOOLS_DISABLE_STL
    #endif
}


TEST_CASE("conv2d(case12)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case12, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case12, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case12, input_h, weight_h, None, stride_h, padding_h );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case12, input_d, weight_d, None, stride_v, padding_v );
    #endif // NMTOOLS_DISABLE_STL

    #else
    CONV2D_SUBCASE( case12, input_cs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_fs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    // TODO: fix fixed/bounded-size inference for utl
    //     (gdb) bt
    // #0  __memmove_avx_unaligned_erms () at ..
    // #1  0x0000555555808d78 in nmtools::utl::vector<... >::resize 
    // #2  0x0000555555999899 in nmtools::array::ndarray_t<nmtools::utl::vector<int, nmtools::utl::allocator<int> >, ... > const&)
    CONV2D_SUBCASE( case12, input_hs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_ds_db, None, stride_a, padding_a );
    #endif

    CONV2D_SUBCASE( case12, input_ls_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_cs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case12, input_hs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_cs_db, None, stride_a, padding_a );
    #endif

    CONV2D_SUBCASE( case12, input_ls_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_fs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case12, input_hs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_fs_db, None, stride_a, padding_a );
    #endif

    CONV2D_SUBCASE( case12, input_ls_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_hs_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case12, input_ds_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_hs_db, None, stride_a, padding_a );
    #endif

    CONV2D_SUBCASE( case12, input_ls_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_ds_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case12, input_hs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_ds_db, None, stride_a, padding_a );
    #endif

    CONV2D_SUBCASE( case12, input_ls_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_ls_db, None, stride_a, padding_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    CONV2D_SUBCASE( case12, input_hs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_ls_db, None, stride_a, padding_a );
    #endif
    #endif
}

#else // NMTOOLS_BUILD_CONSTEXPR_TESTS

// must increaset constexpr limit on gcc:
//  error: ‘constexpr’ evaluation operation count exceeds limit of 33554432 (use -fconstexpr-ops-limit= to increase the limit

// error on constexpr clang

#ifndef __clang__

TEST_CASE("constexpr_conv2d(case9)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case9, input, weight, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case9, input_a, weight_a, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case9, input_f, weight_f, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case9, input_h, weight_h, None, stride_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case9, input_cs_fb, weight_cs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case9, input_cs_hb, weight_cs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case9, input_fs_fb, weight_fs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case9, input_fs_hb, weight_fs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case9, input_hs_fb, weight_hs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case9, input_hs_hb, weight_hs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case9, input_ls_fb, weight_ls_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case9, input_ls_hb, weight_ls_hb, None, stride_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case10)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case10, input, weight, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case10, input_a, weight_a, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case10, input_f, weight_f, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case10, input_h, weight_h, None, stride_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case10, input_cs_fb, weight_cs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case10, input_cs_hb, weight_cs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case10, input_fs_fb, weight_fs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case10, input_fs_hb, weight_fs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case10, input_hs_fb, weight_hs_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case10, input_hs_hb, weight_hs_hb, None, stride_ct );

    CONSTEXPR_CONV2D_SUBCASE( case10, input_ls_fb, weight_ls_fb, None, stride_ct );
    CONSTEXPR_CONV2D_SUBCASE( case10, input_ls_hb, weight_ls_hb, None, stride_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case11)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case11, input, weight, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case11, input_a, weight_a, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case11, input_f, weight_f, None, stride_ct, padding_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case11, input_cs_fb, weight_cs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case11, input_cs_hb, weight_cs_hb, None, stride_ct, padding_ct );

    // NOTE: padding may increase the shape & size, can't know the upper bound if only src size is known
    #if 0
    CONSTEXPR_CONV2D_SUBCASE( case11, input_fs_fb, weight_fs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case11, input_fs_hb, weight_fs_hb, None, stride_ct, padding_ct );

    CONSTEXPR_CONV2D_SUBCASE( case11, input_hs_fb, weight_hs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case11, input_hs_hb, weight_hs_hb, None, stride_ct, padding_ct );
    #endif

    CONSTEXPR_CONV2D_SUBCASE( case11, input_ls_fb, weight_ls_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case11, input_ls_hb, weight_ls_hb, None, stride_ct, padding_ct );
    #endif
}

TEST_CASE("constexpr_conv2d(case12)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_CONV2D_SUBCASE( case12, input, weight, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case12, input_a, weight_a, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case12, input_f, weight_f, None, stride_ct, padding_ct );
    #else
    CONSTEXPR_CONV2D_SUBCASE( case12, input_cs_fb, weight_cs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case12, input_cs_hb, weight_cs_hb, None, stride_ct, padding_ct );

    // NOTE: padding may increase the shape & size, can't know the upper bound if only src size is known
    #if 0
    CONSTEXPR_CONV2D_SUBCASE( case12, input_fs_fb, weight_fs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case12, input_fs_hb, weight_fs_hb, None, stride_ct, padding_ct );

    CONSTEXPR_CONV2D_SUBCASE( case12, input_hs_fb, weight_hs_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case12, input_hs_hb, weight_hs_hb, None, stride_ct, padding_ct );
    #endif

    CONSTEXPR_CONV2D_SUBCASE( case12, input_ls_fb, weight_ls_fb, None, stride_ct, padding_ct );
    CONSTEXPR_CONV2D_SUBCASE( case12, input_ls_hb, weight_ls_hb, None, stride_ct, padding_ct );
    #endif
}

#endif // __clang__

#endif