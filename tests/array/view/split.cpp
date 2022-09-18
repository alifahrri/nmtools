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

#include "nmtools/array/view/split.hpp"
#include "nmtools/testing/doctest.hpp"

#include "nmtools/testing/data/array/split.hpp"
#include "nmtools/utils/apply_to_string.hpp"
#include "nmtools/utils/apply_isequal.hpp"


#define RUN_split_args_impl(...) \
nm::view::detail::split_args(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs split_args fn to callable lambda
#define RUN_split_args(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("split_args-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_split_args_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_split_args(case_name, ...) \
RUN_split_args_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SPLIT_ARGS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(index, split_args, case_name); \
    using namespace args; \
    auto result = RUN_split_args(case_name, __VA_ARGS__); \
    auto msg1 = std::string("Expected:\n") + nm::utils::to_string(expect::result); \
    auto msg2 = std::string("Actual:\n") + nm::utils::to_string(result); \
    auto msg = msg1 + "\n" + msg2; \
    CHECK_MESSAGE(( nmtools::utils::apply_isequal(result, expect::result) ), msg); \
}

TEST_CASE("split_args(case1)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case1, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case1, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case1, shape_v, indices_or_sections, axis );
    #endif // NMTOOLS_DISABLE_STL
}

TEST_CASE("split_args(case2)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case2, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case2, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case2, shape_v, indices_or_sections, axis );
    #endif // NMTOOLS_DISABLE_STL
}

// TEST_CASE("split_args(case3)" * doctest::test_suite("index::split_args"))
// {
//     SPLIT_ARGS_SUBCASE( case3, shape_v, indices_or_sections, axis );
// }

TEST_CASE("split_args(case4)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case4, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case4, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case4, shape_v, indices_or_sections, axis );
    #endif // NMTOOLS_DISABLE_STL
}

TEST_CASE("split_args(case5)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case5, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case5, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case5, shape_v, indices_or_sections, axis );
    #endif
}

// TEST_CASE("split_args(case6)" * doctest::test_suite("index::split_args"))
// {
//     SPLIT_ARGS_SUBCASE( case6, shape_v, indices_or_sections, axis );
// }

TEST_CASE("split_args(case7)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case7, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case7, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case7, shape_v, indices_or_sections, axis );
    #endif
}

TEST_CASE("split_args(case8)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case8, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case8, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case8, shape_v, indices_or_sections, axis );
    #endif
}

TEST_CASE("split_args(case9)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case9, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case9, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case9, shape_v, indices_or_sections, axis );
    #endif
}

TEST_CASE("split_args(case10)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case10, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case10, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case10, shape_v, indices_or_sections, axis );
    #endif
}

TEST_CASE("split_args(case11)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case11, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case11, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case11, shape_v, indices_or_sections, axis );
    #endif
}

TEST_CASE("split_args(case12)" * doctest::test_suite("index::split_args"))
{
    SPLIT_ARGS_SUBCASE( case12, shape, indices_or_sections, axis );
    SPLIT_ARGS_SUBCASE( case12, shape_a, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_ARGS_SUBCASE( case12, shape_v, indices_or_sections, axis );
    #endif
}

#define RUN_split_impl(...) \
nm::view::split(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs split fn to callable lambda
#define RUN_split(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("split-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_split_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_split(case_name, ...) \
RUN_split_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SPLIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, split, case_name); \
    using namespace args; \
    auto result = RUN_split(case_name, __VA_ARGS__); \
    auto msg1 = std::string("Expected:\n") + nm::utils::apply_to_string(expect::result); \
    auto msg2 = std::string("Actual:\n") + nm::utils::apply_to_string(result); \
    auto msg = msg1 + "\n" + msg2; \
    CHECK_MESSAGE(( nmtools::utils::apply_isequal(result, expect::result) ), msg); \
}

// TODO: fix utl vector
/*
error: use of deleted function ‘nmtools::view::decorator_t<nmtools::view::slice_t, int [9], nmtools::utl::array<nmtools::utl::array<long unsigned int, 2>, 1> >& nmtools::view::decorator_t<nmtools::view::slice_t, int [9], nmtools::utl::array<nmtools::utl::array<long unsigned int, 2>, 1> >::operator=(const nmtools::view::decorator_t<nmtools::view::slice_t, int [9], nmtools::utl::array<nmtools::utl::array<long unsigned int, 2>, 1> >&)’
  172 |             buffer_[size_] = t;
*/
#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("split(case1)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case1, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_h, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_d, indices_or_sections, axis );

    #else
    SPLIT_SUBCASE( case1, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case1, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_fs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case1, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_hs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case1, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case1, a_ds_db, indices_or_sections, axis );
    #endif
}
#endif

TEST_CASE("split(case2)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case2, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_h, indices_or_sections, axis );
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case2, a_d, indices_or_sections, axis );
    #endif // NMTOOLS_DISABLE_STL

    #else
    SPLIT_SUBCASE( case2, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case2, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_fs_db, indices_or_sections, axis );

    // TODO: fix "realloc(): invalid old size"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case2, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_hs_db, indices_or_sections, axis );
    #endif

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case2, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case2, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}

TEST_CASE("split(case3)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case3, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_h, indices_or_sections, axis );
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case3, a_d, indices_or_sections, axis );
    #endif // NMTOOLS_DISABLE_STL

    #else
    SPLIT_SUBCASE( case3, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case3, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_fs_hb, indices_or_sections, axis );
    // TODO: fix utl vector null
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case3, a_fs_db, indices_or_sections, axis );
    #endif

    // TODO: fix utl vector segfault
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case3, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_hs_db, indices_or_sections, axis );
    #endif

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case3, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case3, a_ds_db, indices_or_sections, axis );
    #endif
    #endif
}

TEST_CASE("split(case4)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case4, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_h, indices_or_sections, axis );
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case4, a_d, indices_or_sections, axis );
    #endif // NMTOOLS_DISABLE_STL

    #else
    SPLIT_SUBCASE( case4, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case4, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_fs_hb, indices_or_sections, axis );
    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case4, a_fs_db, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_hs_db, indices_or_sections, axis );
    #endif

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case4, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case4, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}

TEST_CASE("split(case5)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case5, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_h, indices_or_sections, axis );
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case5, a_d, indices_or_sections, axis );
    #endif

    #else
    SPLIT_SUBCASE( case5, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case5, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_fs_db, indices_or_sections, axis );

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case5, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_hs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case5, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case5, a_ds_db, indices_or_sections, axis );
    #endif
    #endif
}

TEST_CASE("split(case6)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case6, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_h, indices_or_sections, axis );
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case6, a_d, indices_or_sections, axis );
    #endif

    #else
    SPLIT_SUBCASE( case6, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case6, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_fs_db, indices_or_sections, axis );

    // TODO: fix segfault
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case6, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_hs_db, indices_or_sections, axis );
    #endif

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case6, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case6, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("split(case7)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case7, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_h, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_d, indices_or_sections, axis );

    #else
    SPLIT_SUBCASE( case7, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case7, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_fs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case7, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_hs_db, indices_or_sections, axis );

    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case7, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case7, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}

TEST_CASE("split(case8)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case8, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_h, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_d, indices_or_sections, axis );

    #else
    SPLIT_SUBCASE( case8, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case8, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_fs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case8, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_hs_db, indices_or_sections, axis );

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case8, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case8, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}
#endif

// TODO: fix runtime
TEST_CASE("split(case9)" * doctest::test_suite("view::split") * doctest::skip(true))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case9, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_h, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_d, indices_or_sections, axis );

    #else
    SPLIT_SUBCASE( case9, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case9, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_fs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case9, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_hs_db, indices_or_sections, axis );

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case9, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case9, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}

TEST_CASE("split(case10)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case10, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_h, indices_or_sections, axis );
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case10, a_d, indices_or_sections, axis );
    #endif

    #else
    SPLIT_SUBCASE( case10, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case10, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_fs_db, indices_or_sections, axis );

    // TODO: fix segfault
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case10, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_hs_db, indices_or_sections, axis );
    #endif

    // TODO: fix utl vector
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case10, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case10, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("split(case11)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case11, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_h, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_d, indices_or_sections, axis );

    #else
    SPLIT_SUBCASE( case11, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case11, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_fs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case11, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_hs_db, indices_or_sections, axis );

    // TODO: fix utl vector "realloc(): invalid pointer"
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case11, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case11, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}
#endif // NMTOOLS_DISABLE_STL

TEST_CASE("split(case12)" * doctest::test_suite("view::split"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SPLIT_SUBCASE( case12, a, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_a, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_f, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_h, indices_or_sections, axis );
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case12, a_d, indices_or_sections, axis );
    #endif

    #else
    SPLIT_SUBCASE( case12, a_cs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_cs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_cs_db, indices_or_sections, axis );

    SPLIT_SUBCASE( case12, a_fs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_fs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_fs_db, indices_or_sections, axis );

    // TODO: fix realloc(): invalid pointer
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case12, a_hs_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_hs_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_hs_db, indices_or_sections, axis );
    #endif

    // TODO: fix utl vector
    #ifndef NMTOOLS_DISABLE_STL
    SPLIT_SUBCASE( case12, a_ds_fb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_ds_hb, indices_or_sections, axis );
    SPLIT_SUBCASE( case12, a_ds_db, indices_or_sections, axis );
    #endif

    #endif
}