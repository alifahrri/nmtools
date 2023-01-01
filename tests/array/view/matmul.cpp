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

#include "nmtools/array/view/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_matmul_impl(...) \
nmtools::view::matmul(__VA_ARGS__);

namespace nm = nmtools;
namespace meta = nm::meta;

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs matmul fn to callable lambda
#define RUN_matmul(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("matmul-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_matmul_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_matmul(case_name, ...) \
RUN_matmul_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, matmul, case_name); \
    using namespace args; \
    auto result = RUN_matmul(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("view::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case1, lhs, rhs );
    MATMUL_SUBCASE( case1, lhs_a, rhs_a );
    MATMUL_SUBCASE( case1, lhs_f, rhs_f );
    MATMUL_SUBCASE( case1, lhs_h, rhs_h );
    MATMUL_SUBCASE( case1, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_hs_db );
    #endif
}

TEST_CASE("matmul(case2)" * doctest::test_suite("view::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case2, lhs, rhs );
    MATMUL_SUBCASE( case2, lhs_a, rhs_a );
    MATMUL_SUBCASE( case2, lhs_f, rhs_f );
    MATMUL_SUBCASE( case2, lhs_h, rhs_h );
    MATMUL_SUBCASE( case2, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_hs_db );
    #endif
}

TEST_CASE("matmul(case3)" * doctest::test_suite("view::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case3, lhs, rhs );
    MATMUL_SUBCASE( case3, lhs_a, rhs_a );
    MATMUL_SUBCASE( case3, lhs_f, rhs_f );
    MATMUL_SUBCASE( case3, lhs_h, rhs_h );
    MATMUL_SUBCASE( case3, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case3, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case3, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case3, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case3, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case3, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case3, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case3, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case3, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case3, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case3, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case3, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case3, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case3, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case3, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case3, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case3, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case3, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case3, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case3, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case3, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case3, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case3, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case3, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case3, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case3, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case3, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case3, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case3, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case3, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case3, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case3, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case3, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case3, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case3, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case3, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case3, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case3, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case3, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case3, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case3, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case3, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case3, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case3, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case3, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case3, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case3, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case3, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case3, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case3, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case3, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case3, lhs_ls_db, rhs_hs_db );
    #endif
}

TEST_CASE("matmul(case4)" * doctest::test_suite("view::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case4, lhs, rhs );
    MATMUL_SUBCASE( case4, lhs_a, rhs_a );
    MATMUL_SUBCASE( case4, lhs_f, rhs_f );
    MATMUL_SUBCASE( case4, lhs_h, rhs_h );
    MATMUL_SUBCASE( case4, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case4, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case4, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case4, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case4, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case4, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case4, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case4, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case4, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case4, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case4, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case4, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case4, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case4, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case4, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case4, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case4, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case4, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case4, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case4, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case4, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case4, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case4, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case4, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case4, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case4, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case4, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case4, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case4, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case4, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case4, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case4, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case4, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case4, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case4, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case4, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case4, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case4, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case4, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case4, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case4, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case4, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case4, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case4, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case4, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case4, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case4, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case4, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case4, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case4, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case4, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case4, lhs_ls_db, rhs_hs_db );
    #endif
}

TEST_CASE("matmul(case5)" * doctest::test_suite("view::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case5, lhs, rhs );
    MATMUL_SUBCASE( case5, lhs_a, rhs_a );
    MATMUL_SUBCASE( case5, lhs_f, rhs_f );
    MATMUL_SUBCASE( case5, lhs_h, rhs_h );
    MATMUL_SUBCASE( case5, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case5, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case5, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case5, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case5, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case5, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case5, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case5, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case5, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case5, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case5, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case5, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case5, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case5, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case5, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case5, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case5, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case5, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case5, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case5, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case5, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case5, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case5, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case5, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case5, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case5, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case5, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case5, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case5, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case5, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case5, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case5, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case5, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case5, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case5, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case5, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case5, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case5, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case5, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case5, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case5, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case5, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case5, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case5, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case5, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case5, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case5, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case5, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case5, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case5, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case5, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case5, lhs_ls_db, rhs_hs_db );
    #endif
}

TEST_CASE("matmul(case6)" * doctest::test_suite("view::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case6, lhs, rhs );
    MATMUL_SUBCASE( case6, lhs_a, rhs_a );
    MATMUL_SUBCASE( case6, lhs_f, rhs_f );
    MATMUL_SUBCASE( case6, lhs_h, rhs_h );
    MATMUL_SUBCASE( case6, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case6, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case6, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case6, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case6, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case6, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case6, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case6, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case6, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case6, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case6, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case6, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case6, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case6, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case6, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case6, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case6, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case6, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case6, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case6, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case6, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case6, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case6, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case6, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case6, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case6, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case6, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case6, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case6, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case6, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case6, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case6, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case6, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case6, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case6, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case6, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case6, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case6, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case6, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case6, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case6, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case6, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case6, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case6, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case6, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case6, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case6, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case6, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case6, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case6, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case6, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case6, lhs_ls_db, rhs_hs_db );
    #endif
}

TEST_CASE("matmul(view_at)" * doctest::test_suite("view::matmul"))
{
    {
        using namespace nmtools::testing::data::array::matmul::case1::args;
        auto result = nmtools::view::matmul(lhs,rhs);
        auto at00   = result.view_at(0,0);
        using at00_t = decltype(at00);
        using elem_t = nmtools::meta::get_element_type_t<at00_t>;
        static_assert( std::is_same_v<elem_t,int> );
        NMTOOLS_ASSERT_EQUAL(at00, 20);
    }
    {
        using namespace nmtools::testing::data::array::matmul::case3::args;
        auto result = nmtools::view::matmul(lhs,rhs);
        auto at000  = result.view_at(0,0,0);
        using at000_t = decltype(at000);
        using elem_t  = nmtools::meta::get_element_type_t<at000_t>;
        static_assert( std::is_same_v<elem_t,int> );
        NMTOOLS_ASSERT_EQUAL(at000, 20);
    }
}