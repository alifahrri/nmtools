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

#include "nmtools/array/array/broadcast_arrays.hpp"
#include "nmtools/testing/data/array/broadcast_arrays.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_impl(...) \
nm::array::broadcast_arrays(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_arrays fn to callable lambda
#define RUN_broadcast_arrays(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_arrays-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    const auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_arrays(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BROADCAST_ARRAYS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_arrays, case_name); \
    using namespace args; \
    const auto results = RUN_broadcast_arrays(case_name, __VA_ARGS__); \
    constexpr auto N = std::tuple_size_v<decltype(results)>; \
    nm::meta::template_for<N>([&](auto index){ \
        constexpr auto i = decltype(index)::value; \
        const auto array       = nmtools::get<i>(results); \
        const auto expected    = nmtools::get<i>(expect::expected); \
        NMTOOLS_ASSERT_EQUAL( nmtools::shape(array), expect::shape ); \
        NMTOOLS_ASSERT_CLOSE( array, expected ); \
    }); \
}

#define CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(constexpr_broadcast_arrays, case_name); \
    using namespace args; \
    constexpr auto results = RUN_broadcast_arrays(case_name, __VA_ARGS__); \
    constexpr auto N = std::tuple_size_v<decltype(results)>; \
    nm::meta::template_for<N>([&](auto index){ \
        constexpr auto i = decltype(index)::value; \
        constexpr auto array       = nmtools::get<i>(results); \
        constexpr auto expected    = nmtools::get<i>(expect::expected); \
        NMTOOLS_STATIC_ASSERT_EQUAL( nmtools::shape(array), expect::shape ); \
        NMTOOLS_STATIC_ASSERT_CLOSE( array, expected ); \
    }); \
}

#ifndef NMTOOLS_BUILD_CONSTEXPR_TESTS

TEST_CASE("broadcast_arrays(case1)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_db, rhs_ls_db );



    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_ls_db );
    #endif
}

TEST_CASE("broadcast_arrays(case2)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_db, rhs_ls_db );



    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_db, rhs_ds_db );

    
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_ls_db );
    #endif
}

TEST_CASE("broadcast_arrays(case3)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_db, rhs_ls_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_db, rhs_ds_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_ls_db );
    #endif
}

TEST_CASE("broadcast_arrays(case4)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_db, rhs_ls_db );



    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_db, rhs_ds_db );


    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_ls_db );
    #endif
}

TEST_CASE("broadcast_arrays(case5)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case5, A_a, B_a, C_a );
    BROADCAST_ARRAYS_SUBCASE(case5, A_d, B_d, C_d );
    BROADCAST_ARRAYS_SUBCASE(case5, A_f, B_f, C_f );
    BROADCAST_ARRAYS_SUBCASE(case5, A_h, B_h, C_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_fb, B_fs_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_hb, B_fs_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_db, B_fs_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_fb, B_hs_fb, C_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_hb, B_hs_hb, C_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_db, B_hs_db, C_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_fb, B_ds_fb, C_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_hb, B_ds_hb, C_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_db, B_ds_db, C_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_fb, B_ls_fb, C_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_hb, B_ls_hb, C_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_db, B_ls_db, C_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_fs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_fs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_fs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_hs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_hs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_hs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_ds_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_ds_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_ds_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_ls_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_ls_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_ls_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_cs_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_cs_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_cs_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_fb, B_fs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_hb, B_fs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_db, B_fs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_fb, B_hs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_hb, B_hs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_db, B_hs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_fb, B_ds_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_hb, B_ds_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_db, B_ds_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_fb, B_ls_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_hb, B_ls_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ls_db, B_ls_db, C_cs_db );
    #endif
}

TEST_CASE("broadcast_arrays(case6)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_a, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_d, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_f, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_h, rhs );

    #else
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_db, rhs );

    BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_db, rhs );

    BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_db, rhs );

    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ds_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ds_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ds_db, rhs );

    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ls_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ls_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ls_db, rhs );
    #endif
}

TEST_CASE("broadcast_arrays(case7)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ls_db );
    #endif
}

TEST_CASE("broadcast_arrays(case8)" * doctest::test_suite("array::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case8, lhs, rhs);
}

TEST_CASE("broadcast_arrays(case9)" * doctest::test_suite("array::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_a, C_a );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_d, C_d );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_f, C_f );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_h, C_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_fb, C_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_hb, C_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_db, C_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_fb, C_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_hb, C_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_db, C_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_db, C_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_db, C_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_fb, C_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_hb, C_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_db, C_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_fb, C_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_hb, C_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_db, C_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_db, C_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_db, C_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_fb, C_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_hb, C_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_db, C_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_fb, C_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_hb, C_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_db, C_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_db, C_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_db, C_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_fb, C_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_hb, C_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_fs_db, C_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_fb, C_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_hb, C_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_hs_db, C_ls_db );

    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_fb, C_ls_fb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_hb, C_ls_hb );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_ds_db, C_ls_db );
    #endif
}

TEST_CASE("broadcast_arrays(case10)" * doctest::test_suite("array::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case10, A, B);
}

#else // NMTOOLS_BUILD_CONSTEXPR_TESTS

TEST_CASE("broadcast_arrays(case1)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_h, rhs_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_ls_hb );

    // can't be constexpr because can't infer bounded size of data buffer
    #if 0
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_hs_hb );
    #endif

    // can't be constexpr because contains 1 in constant-shape (lhs)
    #if 0
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_ls_hb );
    #endif
    #endif
}

TEST_CASE("broadcast_arrays(case2)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_h, rhs_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_ls_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case3)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_h, rhs_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_ls_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case4)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_h, rhs_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_ls_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case5)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_a, B_a, C_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_f, B_f, C_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_h, B_h, C_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_fb, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_hb, B_ls_hb, C_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_fb, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_hb, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_ls_hb, C_ls_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case6)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_a, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_f, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_h, rhs );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_hb, rhs );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_ls_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_ls_hb, rhs );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_hb, rhs );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_hb, rhs );
    #endif
}

TEST_CASE("broadcast_arrays(case7)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case8)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case8, lhs, rhs );
}

TEST_CASE("broadcast_arrays(case9)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_a, C_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_f, C_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_h, C_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_ls_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case10)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case10, A, B );
}

TEST_CASE("broadcast_arrays(case11)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_a, C_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_f, C_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_h, C_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_ls_hb );



    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_fs_hb );

    // NOTE: currently unsupported by index::broadcast_shape
    // mixed constant index vs runtime index when computing result
    #if 0
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_hs_hb );
    #endif

    #endif
}

TEST_CASE("broadcast_arrays(case12)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_h, rhs_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_hb, rhs_ls_hb );

    // rhs has max size info at compile time
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_hb, rhs_cs_hb );
    
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_hb, rhs_cs_hb );
    
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_hb, rhs_ls_hb );

    #endif
}

TEST_CASE("broadcast_arrays(case13)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_h, rhs_h );

    #else
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_ls_hb );

    // lhs has max size info at compile time
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_fs_hb );
    
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_hs_hb );

    #endif
}

#endif