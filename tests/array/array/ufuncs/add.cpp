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

#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

using nm::None;
using nm::False;
using nm::True;

#define RUN_add_impl(...) \
na::add(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add fn to callable lambda
#define RUN_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_add(case_name, ...) \
RUN_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, add, case_name); \
    using namespace args; \
    auto result = RUN_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("array::add"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ADD_SUBCASE( case1,   a,   b );
    ADD_SUBCASE( case1, a_a, b_a );
    ADD_SUBCASE( case1, a_f, b_f );
    ADD_SUBCASE( case1, a_d, b_d );
    ADD_SUBCASE( case1, a_h, b_h );

    #else
    // ADD_SUBCASE( case1, a_cs_fb, b_cs_fb );
    // ADD_SUBCASE( case1, a_cs_hb, b_cs_hb );
    // ADD_SUBCASE( case1, a_cs_db, b_cs_db );

    ADD_SUBCASE( case1, a_fs_fb, b_fs_fb );
    ADD_SUBCASE( case1, a_fs_hb, b_fs_hb );
    ADD_SUBCASE( case1, a_fs_db, b_fs_db );

    // ADD_SUBCASE( case1, a_hs_fb, b_hs_fb );
    // ADD_SUBCASE( case1, a_hs_hb, b_hs_hb );
    // ADD_SUBCASE( case1, a_hs_db, b_hs_db );

    // ADD_SUBCASE( case1, a_ds_fb, b_ds_fb );
    // ADD_SUBCASE( case1, a_ds_hb, b_ds_hb );
    // ADD_SUBCASE( case1, a_ds_db, b_ds_db );


    // ADD_SUBCASE( case1, a_fs_fb, b_cs_fb );
    // ADD_SUBCASE( case1, a_fs_hb, b_cs_hb );
    // ADD_SUBCASE( case1, a_fs_db, b_cs_db );

    // ADD_SUBCASE( case1, a_hs_fb, b_cs_fb );
    // ADD_SUBCASE( case1, a_hs_hb, b_cs_hb );
    // ADD_SUBCASE( case1, a_hs_db, b_cs_db );

    // ADD_SUBCASE( case1, a_ds_fb, b_cs_fb );
    // ADD_SUBCASE( case1, a_ds_hb, b_cs_hb );
    // ADD_SUBCASE( case1, a_ds_db, b_cs_db );


    // ADD_SUBCASE( case1, a_cs_fb, b_fs_fb );
    // ADD_SUBCASE( case1, a_cs_hb, b_fs_hb );
    // ADD_SUBCASE( case1, a_cs_db, b_fs_db );

    // ADD_SUBCASE( case1, a_hs_fb, b_fs_fb );
    // ADD_SUBCASE( case1, a_hs_hb, b_fs_hb );
    // ADD_SUBCASE( case1, a_hs_db, b_fs_db );

    // ADD_SUBCASE( case1, a_ds_fb, b_fs_fb );
    // ADD_SUBCASE( case1, a_ds_hb, b_fs_hb );
    // ADD_SUBCASE( case1, a_ds_db, b_fs_db );


    // ADD_SUBCASE( case1, a_cs_fb, b_hs_fb );
    // ADD_SUBCASE( case1, a_cs_hb, b_hs_hb );
    // ADD_SUBCASE( case1, a_cs_db, b_hs_db );

    // ADD_SUBCASE( case1, a_fs_fb, b_hs_fb );
    // ADD_SUBCASE( case1, a_fs_hb, b_hs_hb );
    // ADD_SUBCASE( case1, a_fs_db, b_hs_db );

    // ADD_SUBCASE( case1, a_ds_fb, b_hs_fb );
    // ADD_SUBCASE( case1, a_ds_hb, b_hs_hb );
    // ADD_SUBCASE( case1, a_ds_db, b_hs_db );


    // ADD_SUBCASE( case1, a_cs_fb, b_ds_fb );
    // ADD_SUBCASE( case1, a_cs_hb, b_ds_hb );
    // ADD_SUBCASE( case1, a_cs_db, b_ds_db );

    // ADD_SUBCASE( case1, a_fs_fb, b_ds_fb );
    // ADD_SUBCASE( case1, a_fs_hb, b_ds_hb );
    // ADD_SUBCASE( case1, a_fs_db, b_ds_db );

    // ADD_SUBCASE( case1, a_hs_fb, b_ds_fb );
    // ADD_SUBCASE( case1, a_hs_hb, b_ds_hb );
    // ADD_SUBCASE( case1, a_hs_db, b_ds_db );
    #endif
}

TEST_CASE("add(case2)" * doctest::test_suite("array::add"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ADD_SUBCASE( case2,   a, b );
    ADD_SUBCASE( case2, a_a, b );
    ADD_SUBCASE( case2, a_f, b );
    ADD_SUBCASE( case2, a_d, b );
    ADD_SUBCASE( case2, a_h, b );

    #else
    ADD_SUBCASE( case2, a_cs_fb, b );
    ADD_SUBCASE( case2, a_cs_hb, b );
    ADD_SUBCASE( case2, a_cs_db, b );

    ADD_SUBCASE( case2, a_fs_fb, b );
    ADD_SUBCASE( case2, a_fs_hb, b );
    ADD_SUBCASE( case2, a_fs_db, b );

    ADD_SUBCASE( case2, a_hs_fb, b );
    ADD_SUBCASE( case2, a_hs_hb, b );
    ADD_SUBCASE( case2, a_hs_db, b );

    ADD_SUBCASE( case2, a_ds_fb, b );
    ADD_SUBCASE( case2, a_ds_hb, b );
    ADD_SUBCASE( case2, a_ds_db, b );
    #endif
}

TEST_CASE("add(case3)" * doctest::test_suite("array::add"))
{
    ADD_SUBCASE(case3, a, b);
}

TEST_CASE("add(case4)" * doctest::test_suite("array::add"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ADD_SUBCASE(case4, a, b);
    ADD_SUBCASE(case4, a_a, b);
    ADD_SUBCASE(case4, a_f, b);
    ADD_SUBCASE(case4, a_d, b);
    ADD_SUBCASE(case4, a_h, b);

    #else
    ADD_SUBCASE( case4, a_cs_fb, b );
    ADD_SUBCASE( case4, a_cs_hb, b );
    ADD_SUBCASE( case4, a_cs_db, b );

    ADD_SUBCASE( case4, a_fs_fb, b );
    ADD_SUBCASE( case4, a_fs_hb, b );
    ADD_SUBCASE( case4, a_fs_db, b );

    ADD_SUBCASE( case4, a_hs_fb, b );
    ADD_SUBCASE( case4, a_hs_hb, b );
    ADD_SUBCASE( case4, a_hs_db, b );

    ADD_SUBCASE( case4, a_ds_fb, b );
    ADD_SUBCASE( case4, a_ds_hb, b );
    ADD_SUBCASE( case4, a_ds_db, b );
    #endif
}

// skip constexpr test for emscripten
// NOTE: temporarily disable constexpr test,
// latest changes to support view composition makes it not possible for the current implementaion,
// gcc complains about ref wrapper to broadcast to can't be used in constexpr context
// possible fixes are don't take pointer for evaluation
// TODO: fixe constexpr support
// #if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__) && !defined(__arm__) && !defined(__MINGW32__)
// TEST_CASE("add(constexpr)"  * doctest::test_suite("array::add"))
// {
//     NMTOOLS_TESTING_DECLARE_NS(view, constexpr_add, case1);
//     constexpr auto output = meta::as_value<int[3][3]>{};
//     constexpr auto result = na::add(args::a,args::b,None,output);
//     NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); 
// }
// #endif

#define RUN_reduce_add_impl(...) \
na::fn::add::reduce(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add.reduce fn to callable lambda
#define RUN_reduce_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add.reduce-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_add(case_name, ...) \
RUN_reduce_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_add, case_name); \
    using namespace args; \
    auto result = RUN_reduce_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_add(case1)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case1,   a, axis );
    REDUCE_ADD_SUBCASE( case1, a_a, axis );
    REDUCE_ADD_SUBCASE( case1, a_f, axis );
    REDUCE_ADD_SUBCASE( case1, a_d, axis );
    REDUCE_ADD_SUBCASE( case1, a_h, axis );

    #else
    REDUCE_ADD_SUBCASE( case1, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case1, a_cs_hb, axis );
    REDUCE_ADD_SUBCASE( case1, a_cs_db, axis );

    REDUCE_ADD_SUBCASE( case1, a_fs_fb, axis );
    REDUCE_ADD_SUBCASE( case1, a_fs_hb, axis );
    REDUCE_ADD_SUBCASE( case1, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case1, a_hs_fb, axis );
    REDUCE_ADD_SUBCASE( case1, a_hs_hb, axis );
    REDUCE_ADD_SUBCASE( case1, a_hs_db, axis );

    REDUCE_ADD_SUBCASE( case1, a_ds_fb, axis );
    REDUCE_ADD_SUBCASE( case1, a_ds_hb, axis );
    REDUCE_ADD_SUBCASE( case1, a_ds_db, axis );
    #endif
}

TEST_CASE("reduce_add(case2)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case2,   a, axis );
    REDUCE_ADD_SUBCASE( case2, a_a, axis );
    REDUCE_ADD_SUBCASE( case2, a_f, axis );
    REDUCE_ADD_SUBCASE( case2, a_d, axis );
    REDUCE_ADD_SUBCASE( case2, a_h, axis );

    #else
    REDUCE_ADD_SUBCASE( case2, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case2, a_cs_hb, axis );
    REDUCE_ADD_SUBCASE( case2, a_cs_db, axis );

    REDUCE_ADD_SUBCASE( case2, a_fs_fb, axis );
    REDUCE_ADD_SUBCASE( case2, a_fs_hb, axis );
    REDUCE_ADD_SUBCASE( case2, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case2, a_hs_fb, axis );
    REDUCE_ADD_SUBCASE( case2, a_hs_hb, axis );
    REDUCE_ADD_SUBCASE( case2, a_hs_db, axis );

    REDUCE_ADD_SUBCASE( case2, a_ds_fb, axis );
    REDUCE_ADD_SUBCASE( case2, a_ds_hb, axis );
    REDUCE_ADD_SUBCASE( case2, a_ds_db, axis );
    #endif
}

TEST_CASE("reduce_add(case3)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case3,   a, axis );
    REDUCE_ADD_SUBCASE( case3, a_a, axis );
    REDUCE_ADD_SUBCASE( case3, a_f, axis );
    REDUCE_ADD_SUBCASE( case3, a_d, axis );
    REDUCE_ADD_SUBCASE( case3, a_h, axis );

    #else
    REDUCE_ADD_SUBCASE( case3, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case3, a_cs_hb, axis );
    REDUCE_ADD_SUBCASE( case3, a_cs_db, axis );

    REDUCE_ADD_SUBCASE( case3, a_fs_fb, axis );
    REDUCE_ADD_SUBCASE( case3, a_fs_hb, axis );
    REDUCE_ADD_SUBCASE( case3, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case3, a_hs_fb, axis );
    REDUCE_ADD_SUBCASE( case3, a_hs_hb, axis );
    REDUCE_ADD_SUBCASE( case3, a_hs_db, axis );

    REDUCE_ADD_SUBCASE( case3, a_ds_fb, axis );
    REDUCE_ADD_SUBCASE( case3, a_ds_hb, axis );
    REDUCE_ADD_SUBCASE( case3, a_ds_db, axis );
    #endif
}

TEST_CASE("reduce_add(case4)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case4,   a,   axis );
    REDUCE_ADD_SUBCASE( case4, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case4, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_d, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_h, axis_h );

    #else
    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case4, a_cs_hb, axis );
    REDUCE_ADD_SUBCASE( case4, a_cs_db, axis );

    REDUCE_ADD_SUBCASE( case4, a_fs_fb, axis );
    REDUCE_ADD_SUBCASE( case4, a_fs_hb, axis );
    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case4, a_hs_fb, axis );
    REDUCE_ADD_SUBCASE( case4, a_hs_hb, axis );
    REDUCE_ADD_SUBCASE( case4, a_hs_db, axis );

    REDUCE_ADD_SUBCASE( case4, a_ds_fb, axis );
    REDUCE_ADD_SUBCASE( case4, a_ds_hb, axis );
    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis );

    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_cs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_cs_db, axis_f );

    REDUCE_ADD_SUBCASE( case4, a_fs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_fs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_f );

    REDUCE_ADD_SUBCASE( case4, a_hs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_hs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_hs_db, axis_f );

    REDUCE_ADD_SUBCASE( case4, a_ds_fb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_ds_hb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_f );

    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_cs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_cs_db, axis_h );

    REDUCE_ADD_SUBCASE( case4, a_fs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_fs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_h );

    REDUCE_ADD_SUBCASE( case4, a_hs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_hs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_hs_db, axis_h );

    REDUCE_ADD_SUBCASE( case4, a_ds_fb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_ds_hb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_h );

    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_cs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_cs_db, axis_v );

    REDUCE_ADD_SUBCASE( case4, a_fs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_fs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_v );

    REDUCE_ADD_SUBCASE( case4, a_hs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_hs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_hs_db, axis_v );

    REDUCE_ADD_SUBCASE( case4, a_ds_fb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_ds_hb, axis_v );
    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_v );
    #endif
}

TEST_CASE("reduce_add(case5)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case5,   a,   axis );
    REDUCE_ADD_SUBCASE( case5, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case5, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_d, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_h, axis_h );

    #else
    REDUCE_ADD_SUBCASE( case5, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case5, a_cs_hb, axis );
    REDUCE_ADD_SUBCASE( case5, a_cs_db, axis );

    REDUCE_ADD_SUBCASE( case5, a_fs_fb, axis );
    REDUCE_ADD_SUBCASE( case5, a_fs_hb, axis );
    REDUCE_ADD_SUBCASE( case5, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case5, a_hs_fb, axis );
    REDUCE_ADD_SUBCASE( case5, a_hs_hb, axis );
    REDUCE_ADD_SUBCASE( case5, a_hs_db, axis );

    REDUCE_ADD_SUBCASE( case5, a_ds_fb, axis );
    REDUCE_ADD_SUBCASE( case5, a_ds_hb, axis );
    REDUCE_ADD_SUBCASE( case5, a_ds_db, axis );

    REDUCE_ADD_SUBCASE( case5, a_cs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_cs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_cs_db, axis_f );

    REDUCE_ADD_SUBCASE( case5, a_fs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_fs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_fs_db, axis_f );

    REDUCE_ADD_SUBCASE( case5, a_hs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_hs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_hs_db, axis_f );

    REDUCE_ADD_SUBCASE( case5, a_ds_fb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_ds_hb, axis_f );
    REDUCE_ADD_SUBCASE( case5, a_ds_db, axis_f );

    REDUCE_ADD_SUBCASE( case5, a_cs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_cs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_cs_db, axis_h );

    REDUCE_ADD_SUBCASE( case5, a_fs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_fs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_fs_db, axis_h );

    REDUCE_ADD_SUBCASE( case5, a_hs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_hs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_hs_db, axis_h );

    REDUCE_ADD_SUBCASE( case5, a_ds_fb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_ds_hb, axis_h );
    REDUCE_ADD_SUBCASE( case5, a_ds_db, axis_h );

    REDUCE_ADD_SUBCASE( case5, a_cs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_cs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_cs_db, axis_v );

    REDUCE_ADD_SUBCASE( case5, a_fs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_fs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_fs_db, axis_v );

    REDUCE_ADD_SUBCASE( case5, a_hs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_hs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_hs_db, axis_v );

    REDUCE_ADD_SUBCASE( case5, a_ds_fb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_ds_hb, axis_v );
    REDUCE_ADD_SUBCASE( case5, a_ds_db, axis_v );
    #endif
}

TEST_CASE("reduce_add(case6)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case6,   a,   axis );
    REDUCE_ADD_SUBCASE( case6, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case6, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_d, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_h, axis_h );

    #else
    REDUCE_ADD_SUBCASE( case6, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case6, a_cs_hb, axis );
    REDUCE_ADD_SUBCASE( case6, a_cs_db, axis );

    REDUCE_ADD_SUBCASE( case6, a_fs_fb, axis );
    REDUCE_ADD_SUBCASE( case6, a_fs_hb, axis );
    REDUCE_ADD_SUBCASE( case6, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case6, a_hs_fb, axis );
    REDUCE_ADD_SUBCASE( case6, a_hs_hb, axis );
    REDUCE_ADD_SUBCASE( case6, a_hs_db, axis );

    REDUCE_ADD_SUBCASE( case6, a_ds_fb, axis );
    REDUCE_ADD_SUBCASE( case6, a_ds_hb, axis );
    REDUCE_ADD_SUBCASE( case6, a_ds_db, axis );

    REDUCE_ADD_SUBCASE( case6, a_cs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_cs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_cs_db, axis_f );

    REDUCE_ADD_SUBCASE( case6, a_fs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_fs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_fs_db, axis_f );

    REDUCE_ADD_SUBCASE( case6, a_hs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_hs_hb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_hs_db, axis_f );

    REDUCE_ADD_SUBCASE( case6, a_ds_fb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_ds_hb, axis_f );
    REDUCE_ADD_SUBCASE( case6, a_ds_db, axis_f );

    REDUCE_ADD_SUBCASE( case6, a_cs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_cs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_cs_db, axis_h );

    REDUCE_ADD_SUBCASE( case6, a_fs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_fs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_fs_db, axis_h );

    REDUCE_ADD_SUBCASE( case6, a_hs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_hs_hb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_hs_db, axis_h );

    REDUCE_ADD_SUBCASE( case6, a_ds_fb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_ds_hb, axis_h );
    REDUCE_ADD_SUBCASE( case6, a_ds_db, axis_h );

    REDUCE_ADD_SUBCASE( case6, a_cs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_cs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_cs_db, axis_v );

    REDUCE_ADD_SUBCASE( case6, a_fs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_fs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_fs_db, axis_v );

    REDUCE_ADD_SUBCASE( case6, a_hs_fb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_hs_hb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_hs_db, axis_v );

    REDUCE_ADD_SUBCASE( case6, a_ds_fb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_ds_hb, axis_v );
    REDUCE_ADD_SUBCASE( case6, a_ds_db, axis_v );
    #endif
}

TEST_CASE("reduce_add(case7)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case7,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_d, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_h, axis, dtype );

    #else
    REDUCE_ADD_SUBCASE( case7, a_cs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_cs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_cs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case7, a_fs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_fs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_fs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case7, a_hs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_hs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_hs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case7, a_ds_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_ds_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_ds_db, axis, dtype );
    #endif
}

TEST_CASE("reduce_add(case8)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_d, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_h, axis, dtype, initial );

    #else
    REDUCE_ADD_SUBCASE( case8, a_cs_fb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_cs_hb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_cs_db, axis, dtype, initial );

    REDUCE_ADD_SUBCASE( case8, a_fs_fb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_fs_hb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_fs_db, axis, dtype, initial );

    REDUCE_ADD_SUBCASE( case8, a_hs_fb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_hs_hb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_hs_db, axis, dtype, initial );

    REDUCE_ADD_SUBCASE( case8, a_ds_fb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_ds_hb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_ds_db, axis, dtype, initial );
    #endif
}

TEST_CASE("reduce_add(case9)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case9, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case9, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case9, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case9, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case10)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case10, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case10, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case10, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case10, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case10, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case11)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case11, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case11, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case11, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case11, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case11, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case12)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case12, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case12, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case12, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case12, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case12, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case13)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case13, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case13, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case13, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case13, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case13, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case14)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case14,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case14, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case14, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case14, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case14, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case14, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case15)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case15,   a, axis );
    REDUCE_ADD_SUBCASE( case15, a_a, axis );
    REDUCE_ADD_SUBCASE( case15, a_f, axis );
    REDUCE_ADD_SUBCASE( case15, a_d, axis );
    REDUCE_ADD_SUBCASE( case15, a_h, axis );

    #else
    REDUCE_ADD_SUBCASE( case15, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case15, a_cs_hb, axis );
    REDUCE_ADD_SUBCASE( case15, a_cs_db, axis );

    REDUCE_ADD_SUBCASE( case15, a_fs_fb, axis );
    REDUCE_ADD_SUBCASE( case15, a_fs_hb, axis );
    REDUCE_ADD_SUBCASE( case15, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case15, a_hs_fb, axis );
    REDUCE_ADD_SUBCASE( case15, a_hs_hb, axis );
    REDUCE_ADD_SUBCASE( case15, a_hs_db, axis );

    REDUCE_ADD_SUBCASE( case15, a_ds_fb, axis );
    REDUCE_ADD_SUBCASE( case15, a_ds_hb, axis );
    REDUCE_ADD_SUBCASE( case15, a_ds_db, axis );
    #endif
}

TEST_CASE("reduce_add(case16)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case16,   a, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_a, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_f, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_d, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_h, axis, nmtools::None, initial );

    #else
    REDUCE_ADD_SUBCASE( case16, a_cs_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_cs_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_cs_db, axis, nmtools::None, initial );

    REDUCE_ADD_SUBCASE( case16, a_fs_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_fs_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_fs_db, axis, nmtools::None, initial );

    REDUCE_ADD_SUBCASE( case16, a_hs_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_hs_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_hs_db, axis, nmtools::None, initial );

    REDUCE_ADD_SUBCASE( case16, a_ds_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_ds_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case16, a_ds_db, axis, nmtools::None, initial );
    #endif
}

TEST_CASE("reduce_add(case17)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case17,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_d, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case17, a_h, axis, nmtools::None, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case17, a_cs_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_cs_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_cs_db, axis, nmtools::None, initial );

    REDUCE_ADD_SUBCASE( case17, a_fs_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_fs_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_fs_db, axis, nmtools::None, initial );

    REDUCE_ADD_SUBCASE( case17, a_hs_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_hs_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_hs_db, axis, nmtools::None, initial );

    REDUCE_ADD_SUBCASE( case17, a_ds_fb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_ds_hb, axis, nmtools::None, initial );
    REDUCE_ADD_SUBCASE( case17, a_ds_db, axis, nmtools::None, initial );
    #endif
}

TEST_CASE("reduce_add(case18)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case18,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_d, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_h, axis, nmtools::None, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case18, a_cs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_cs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_cs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case18, a_fs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_fs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_fs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case18, a_hs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_hs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_hs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case18, a_ds_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_ds_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case18, a_ds_db, axis, nmtools::None, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case19)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case19,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_d, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_h, axis, nmtools::None, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case19, a_cs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_cs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_cs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case19, a_fs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_fs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_fs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case19, a_hs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_hs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_hs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case19, a_ds_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_ds_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case19, a_ds_db, axis, nmtools::None, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case20)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case20,   a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_a, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_f, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_d, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_h, axis, nmtools::None, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case20, a_cs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_cs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_cs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case20, a_fs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_fs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_fs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case20, a_hs_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_hs_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_hs_db, axis, nmtools::None, initial, keepdims );

    REDUCE_ADD_SUBCASE( case20, a_ds_fb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_ds_hb, axis, nmtools::None, initial, keepdims );
    REDUCE_ADD_SUBCASE( case20, a_ds_db, axis, nmtools::None, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case21)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case21,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_a, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_d, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_h, axis, dtype );

    #else
    REDUCE_ADD_SUBCASE( case21, a_cs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_cs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_cs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case21, a_fs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_fs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_fs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case21, a_hs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_hs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_hs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case21, a_ds_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_ds_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case21, a_ds_db, axis, dtype );
    #endif
}

TEST_CASE("reduce_add(case22)" * doctest::test_suite("array::add.reduce"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case22,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_a, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_d, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_h, axis, dtype );

    #else
    REDUCE_ADD_SUBCASE( case22, a_cs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_cs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_cs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case22, a_fs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_fs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_fs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case22, a_hs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_hs_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_hs_db, axis, dtype );

    REDUCE_ADD_SUBCASE( case22, a_ds_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_ds_hb, axis, dtype );
    REDUCE_ADD_SUBCASE( case22, a_ds_db, axis, dtype );
    #endif
}

TEST_CASE("reduce_add(case23)" * doctest::test_suite("array::add.reduce"))
{
    auto dtype   = nmtools::None;
    auto initial = nmtools::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case23,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case23, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case23, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case23, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case23, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case23, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

TEST_CASE("reduce_add(case24)" * doctest::test_suite("array::add.reduce"))
{
    auto dtype   = nmtools::None;
    auto initial = nmtools::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REDUCE_ADD_SUBCASE( case24,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_h, axis, dtype, initial, keepdims );

    #else
    REDUCE_ADD_SUBCASE( case24, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_cs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_cs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case24, a_fs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_fs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_fs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case24, a_hs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_hs_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_hs_db, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case24, a_ds_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_ds_hb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case24, a_ds_db, axis, dtype, initial, keepdims );
    #endif
}

#define RUN_accumulate_add_impl(...) \
na::add.accumulate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add.accumulate fn to callable lambda
#define RUN_accumulate_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add.accumulate-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_add(case_name, ...) \
RUN_accumulate_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add.accumulate(case1)" * doctest::test_suite("array::add.accumulate"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ACCUMULATE_ADD_SUBCASE( case1,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_f, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_h, axis );

    #else
    ACCUMULATE_ADD_SUBCASE( case1, a_cs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_cs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_cs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case1, a_fs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_fs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_fs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case1, a_hs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_hs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_hs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case1, a_ds_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_ds_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_ds_db, axis );
    #endif
}

TEST_CASE("add.accumulate(case2)" * doctest::test_suite("array::add.accumulate"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ACCUMULATE_ADD_SUBCASE( case2,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_f, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_h, axis );

    #else
    ACCUMULATE_ADD_SUBCASE( case2, a_cs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_cs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_cs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case2, a_fs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_fs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_fs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case2, a_hs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_hs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_hs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case2, a_ds_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_ds_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case2, a_ds_db, axis );
    #endif
}

TEST_CASE("add.accumulate(case3)" * doctest::test_suite("array::add.accumulate"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ACCUMULATE_ADD_SUBCASE( case3,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_f, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_h, axis );

    #else
    ACCUMULATE_ADD_SUBCASE( case3, a_cs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_cs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_cs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case3, a_fs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_fs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_fs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case3, a_hs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_hs_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_hs_db, axis );

    ACCUMULATE_ADD_SUBCASE( case3, a_ds_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_ds_hb, axis );
    ACCUMULATE_ADD_SUBCASE( case3, a_ds_db, axis );
    #endif
}

#define RUN_outer_add_impl(...) \
na::add.outer(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs add.outer fn to callable lambda
#define RUN_outer_add(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("add.outer-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_add_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_add(case_name, ...) \
RUN_outer_add_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_add, case_name); \
    using namespace args; \
    auto result = RUN_outer_add(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add.outer(case1)" * doctest::test_suite("array::add.outer"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    OUTER_ADD_SUBCASE( case1,   a,   b );
    OUTER_ADD_SUBCASE( case1, a_a, b_a );
    OUTER_ADD_SUBCASE( case1, a_f, b_f );
    OUTER_ADD_SUBCASE( case1, a_d, b_d );
    OUTER_ADD_SUBCASE( case1, a_h, b_h );

    #else
    OUTER_ADD_SUBCASE( case1, a_cs_fb, b_cs_fb );
    OUTER_ADD_SUBCASE( case1, a_cs_hb, b_cs_hb );
    OUTER_ADD_SUBCASE( case1, a_cs_db, b_cs_db );

    OUTER_ADD_SUBCASE( case1, a_fs_fb, b_fs_fb );
    OUTER_ADD_SUBCASE( case1, a_fs_hb, b_fs_hb );
    OUTER_ADD_SUBCASE( case1, a_fs_db, b_fs_db );

    OUTER_ADD_SUBCASE( case1, a_hs_fb, b_hs_fb );
    OUTER_ADD_SUBCASE( case1, a_hs_hb, b_hs_hb );
    OUTER_ADD_SUBCASE( case1, a_hs_db, b_hs_db );

    OUTER_ADD_SUBCASE( case1, a_ds_fb, b_ds_fb );
    OUTER_ADD_SUBCASE( case1, a_ds_hb, b_ds_hb );
    OUTER_ADD_SUBCASE( case1, a_ds_db, b_ds_db );

    OUTER_ADD_SUBCASE( case1, a_fs_fb, b_cs_fb );
    OUTER_ADD_SUBCASE( case1, a_fs_hb, b_cs_hb );
    OUTER_ADD_SUBCASE( case1, a_fs_db, b_cs_db );

    OUTER_ADD_SUBCASE( case1, a_hs_fb, b_cs_fb );
    OUTER_ADD_SUBCASE( case1, a_hs_hb, b_cs_hb );
    OUTER_ADD_SUBCASE( case1, a_hs_db, b_cs_db );

    OUTER_ADD_SUBCASE( case1, a_ds_fb, b_cs_fb );
    OUTER_ADD_SUBCASE( case1, a_ds_hb, b_cs_hb );
    OUTER_ADD_SUBCASE( case1, a_ds_db, b_cs_db );

    OUTER_ADD_SUBCASE( case1, a_cs_fb, b_fs_fb );
    OUTER_ADD_SUBCASE( case1, a_cs_hb, b_fs_hb );
    OUTER_ADD_SUBCASE( case1, a_cs_db, b_fs_db );

    OUTER_ADD_SUBCASE( case1, a_hs_fb, b_fs_fb );
    OUTER_ADD_SUBCASE( case1, a_hs_hb, b_fs_hb );
    OUTER_ADD_SUBCASE( case1, a_hs_db, b_fs_db );

    OUTER_ADD_SUBCASE( case1, a_ds_fb, b_fs_fb );
    OUTER_ADD_SUBCASE( case1, a_ds_hb, b_fs_hb );
    OUTER_ADD_SUBCASE( case1, a_ds_db, b_fs_db );

    OUTER_ADD_SUBCASE( case1, a_cs_fb, b_hs_fb );
    OUTER_ADD_SUBCASE( case1, a_cs_hb, b_hs_hb );
    OUTER_ADD_SUBCASE( case1, a_cs_db, b_hs_db );

    OUTER_ADD_SUBCASE( case1, a_fs_fb, b_hs_fb );
    OUTER_ADD_SUBCASE( case1, a_fs_hb, b_hs_hb );
    OUTER_ADD_SUBCASE( case1, a_fs_db, b_hs_db );

    OUTER_ADD_SUBCASE( case1, a_ds_fb, b_hs_fb );
    OUTER_ADD_SUBCASE( case1, a_ds_hb, b_hs_hb );
    OUTER_ADD_SUBCASE( case1, a_ds_db, b_hs_db );

    OUTER_ADD_SUBCASE( case1, a_cs_fb, b_ds_fb );
    OUTER_ADD_SUBCASE( case1, a_cs_hb, b_ds_hb );
    OUTER_ADD_SUBCASE( case1, a_cs_db, b_ds_db );

    OUTER_ADD_SUBCASE( case1, a_fs_fb, b_ds_fb );
    OUTER_ADD_SUBCASE( case1, a_fs_hb, b_ds_hb );
    OUTER_ADD_SUBCASE( case1, a_fs_db, b_ds_db );

    OUTER_ADD_SUBCASE( case1, a_hs_fb, b_ds_fb );
    OUTER_ADD_SUBCASE( case1, a_hs_hb, b_ds_hb );
    OUTER_ADD_SUBCASE( case1, a_hs_db, b_ds_db );
    #endif
}