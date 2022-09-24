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
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#include "nmtools/array/array/atleast_1d.hpp"
#include "nmtools/testing/data/array/atleast_1d.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

#define RUN_atleast_1d_impl(...) \
nmtools::array::atleast_1d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs atleast_1d fn to callable lambda
#define RUN_atleast_1d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("atleast_1d-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_atleast_1d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_atleast_1d(case_name, ...) \
RUN_atleast_1d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ATLEAST_1D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_1d, case_name); \
    using namespace args; \
    auto result = RUN_atleast_1d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_1d(case1)" * doctest::test_suite("array::atleast_1d"))
{
    ATLEAST_1D_SUBCASE( case1, a );
}

TEST_CASE("atleast_1d(case2)" * doctest::test_suite("array::atleast_1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_1D_SUBCASE( case2, a );
    ATLEAST_1D_SUBCASE( case2, a_a );
    ATLEAST_1D_SUBCASE( case2, a_f );
    ATLEAST_1D_SUBCASE( case2, a_d );
    ATLEAST_1D_SUBCASE( case2, a_h );

    #else
    ATLEAST_1D_SUBCASE( case2, a_cs_fb );
    ATLEAST_1D_SUBCASE( case2, a_cs_hb );
    ATLEAST_1D_SUBCASE( case2, a_cs_db );

    ATLEAST_1D_SUBCASE( case2, a_fs_fb );
    ATLEAST_1D_SUBCASE( case2, a_fs_hb );
    ATLEAST_1D_SUBCASE( case2, a_fs_db );

    ATLEAST_1D_SUBCASE( case2, a_hs_fb );
    ATLEAST_1D_SUBCASE( case2, a_hs_hb );
    ATLEAST_1D_SUBCASE( case2, a_hs_db );

    ATLEAST_1D_SUBCASE( case2, a_ds_fb );
    ATLEAST_1D_SUBCASE( case2, a_ds_hb );
    ATLEAST_1D_SUBCASE( case2, a_ds_db );

    #endif
}

TEST_CASE("atleast_1d(case3)" * doctest::test_suite("array::atleast_1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_1D_SUBCASE( case3, a );
    ATLEAST_1D_SUBCASE( case3, a_a );
    ATLEAST_1D_SUBCASE( case3, a_f );
    ATLEAST_1D_SUBCASE( case3, a_d );
    ATLEAST_1D_SUBCASE( case3, a_h );

    #else
    ATLEAST_1D_SUBCASE( case3, a_cs_fb );
    ATLEAST_1D_SUBCASE( case3, a_cs_hb );
    ATLEAST_1D_SUBCASE( case3, a_cs_db );

    ATLEAST_1D_SUBCASE( case3, a_fs_fb );
    ATLEAST_1D_SUBCASE( case3, a_fs_hb );
    ATLEAST_1D_SUBCASE( case3, a_fs_db );

    ATLEAST_1D_SUBCASE( case3, a_hs_fb );
    ATLEAST_1D_SUBCASE( case3, a_hs_hb );
    ATLEAST_1D_SUBCASE( case3, a_hs_db );

    ATLEAST_1D_SUBCASE( case3, a_ds_fb );
    ATLEAST_1D_SUBCASE( case3, a_ds_hb );
    ATLEAST_1D_SUBCASE( case3, a_ds_db );
    #endif
}

TEST_CASE("atleast_1d(case4)" * doctest::test_suite("array::atleast_1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_1D_SUBCASE( case4, a );
    ATLEAST_1D_SUBCASE( case4, a_a );
    ATLEAST_1D_SUBCASE( case4, a_f );
    ATLEAST_1D_SUBCASE( case4, a_d );
    ATLEAST_1D_SUBCASE( case4, a_h );

    #else
    ATLEAST_1D_SUBCASE( case4, a_cs_fb );
    ATLEAST_1D_SUBCASE( case4, a_cs_hb );
    ATLEAST_1D_SUBCASE( case4, a_cs_db );

    ATLEAST_1D_SUBCASE( case4, a_fs_fb );
    ATLEAST_1D_SUBCASE( case4, a_fs_hb );
    ATLEAST_1D_SUBCASE( case4, a_fs_db );

    ATLEAST_1D_SUBCASE( case4, a_hs_fb );
    ATLEAST_1D_SUBCASE( case4, a_hs_hb );
    ATLEAST_1D_SUBCASE( case4, a_hs_db );

    ATLEAST_1D_SUBCASE( case4, a_ds_fb );
    ATLEAST_1D_SUBCASE( case4, a_ds_hb );
    ATLEAST_1D_SUBCASE( case4, a_ds_db );
    #endif
}


namespace array = nmtools::array;
namespace meta = nmtools::meta;

TEST_CASE("atleast_1d(traits)" * doctest::test_suite("array::atleast_1d"))
{
    SUBCASE("fixed_ndarray(int)")
    {
        int a = 1;
        auto array = array::atleast_1d(a);
        using array_t = decltype(array);
        constexpr auto is_fixed = meta::is_fixed_shape_v<array_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( is_fixed, true );
    }
    SUBCASE("!fixed_ndarray(std::vector)")
    {
        auto a = nmtools_list{1,2};
        auto array = array::atleast_1d(a);
        using array_t = decltype(array);
        constexpr auto is_fixed = meta::is_fixed_shape_v<array_t>;
        NMTOOLS_STATIC_ASSERT_EQUAL( is_fixed, false );
    }
}