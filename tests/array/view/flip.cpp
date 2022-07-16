#if 1
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

#include "nmtools/array/view/flip.hpp"
#include "nmtools/testing/data/array/flip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_flip_impl(...) \
nm::view::flip(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs flip fn to callable lambda
#define RUN_flip(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("flip-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_flip_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_flip(case_name, ...) \
RUN_flip_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(flip, case_name); \
    using namespace args; \
    auto result = RUN_flip(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("flip(case1)" * doctest::test_suite("view::flip"))
{
    FLIP_SUBCASE(case1,   array, axis );
    FLIP_SUBCASE(case1, array_a, axis );
    // FLIP_SUBCASE(case1, array_v, axis );
    FLIP_SUBCASE(case1, array_f, axis );
    FLIP_SUBCASE(case1, array_h, axis );
    // TODO: support flip for dynamic ndarray
    // FLIP_SUBCASE(case1, array_d, axis );

    FLIP_SUBCASE(case1, array_cs_fb, axis );
    FLIP_SUBCASE(case1, array_cs_hb, axis );
    FLIP_SUBCASE(case1, array_cs_db, axis );

    FLIP_SUBCASE(case1, array_fs_fb, axis );
    FLIP_SUBCASE(case1, array_fs_hb, axis );
    FLIP_SUBCASE(case1, array_fs_db, axis );

    // TODO: fix
    // FLIP_SUBCASE(case1, array_hs_fb, axis );
    // FLIP_SUBCASE(case1, array_hs_hb, axis );
    // FLIP_SUBCASE(case1, array_hs_db, axis );

    // TODO: fix compile
    // FLIP_SUBCASE(case1, array_ds_fb, axis );
    // FLIP_SUBCASE(case1, array_ds_hb, axis );
    // FLIP_SUBCASE(case1, array_ds_db, axis );
}

TEST_CASE("flip(case2)" * doctest::test_suite("view::flip"))
{
    FLIP_SUBCASE(case2,   array, axis );
    FLIP_SUBCASE(case2, array_a, axis );
    FLIP_SUBCASE(case2, array_v, axis );
    FLIP_SUBCASE(case2, array_f, axis );
    FLIP_SUBCASE(case2, array_h, axis );
    // FLIP_SUBCASE(case2, array_d, axis );

    FLIP_SUBCASE(case2, array_cs_fb, axis );
    FLIP_SUBCASE(case2, array_cs_hb, axis );
    FLIP_SUBCASE(case2, array_cs_db, axis );

    FLIP_SUBCASE(case2, array_fs_fb, axis );
    FLIP_SUBCASE(case2, array_fs_hb, axis );
    FLIP_SUBCASE(case2, array_fs_db, axis );

    // FLIP_SUBCASE(case2, array_hs_fb, axis );
    // FLIP_SUBCASE(case2, array_hs_hb, axis );
    // FLIP_SUBCASE(case2, array_hs_db, axis );

    // FLIP_SUBCASE(case2, array_ds_fb, axis );
    // FLIP_SUBCASE(case2, array_ds_hb, axis );
    // FLIP_SUBCASE(case2, array_ds_db, axis );
}

TEST_CASE("flip(case3)" * doctest::test_suite("view::flip"))
{
    FLIP_SUBCASE(case3,   array, axis );
    FLIP_SUBCASE(case3, array_a, axis );
    FLIP_SUBCASE(case3, array_v, axis );
    FLIP_SUBCASE(case3, array_f, axis );
    FLIP_SUBCASE(case3, array_h, axis );
    // FLIP_SUBCASE(case3, array_d, axis );

    FLIP_SUBCASE(case3, array_cs_fb, axis );
    FLIP_SUBCASE(case3, array_cs_hb, axis );
    FLIP_SUBCASE(case3, array_cs_db, axis );

    FLIP_SUBCASE(case3, array_fs_fb, axis );
    FLIP_SUBCASE(case3, array_fs_hb, axis );
    FLIP_SUBCASE(case3, array_fs_db, axis );

    // FLIP_SUBCASE(case3, array_hs_fb, axis );
    // FLIP_SUBCASE(case3, array_hs_hb, axis );
    // FLIP_SUBCASE(case3, array_hs_db, axis );

    // FLIP_SUBCASE(case3, array_ds_fb, axis );
    // FLIP_SUBCASE(case3, array_ds_hb, axis );
    // FLIP_SUBCASE(case3, array_ds_db, axis );
}

TEST_CASE("flip(case4)" * doctest::test_suite("view::flip"))
{
    FLIP_SUBCASE(case4,   array,   axis );
    FLIP_SUBCASE(case4, array_a, axis_a );
    FLIP_SUBCASE(case4, array_v, axis_v );
    FLIP_SUBCASE(case4, array_f, axis_f );
    FLIP_SUBCASE(case4, array_h, axis_h );
    // FLIP_SUBCASE(case4, array_d, axis_d );

    FLIP_SUBCASE(case4, array_cs_fb, axis );
    FLIP_SUBCASE(case4, array_cs_hb, axis );
    FLIP_SUBCASE(case4, array_cs_db, axis );

    FLIP_SUBCASE(case4, array_fs_fb, axis );
    FLIP_SUBCASE(case4, array_fs_hb, axis );
    FLIP_SUBCASE(case4, array_fs_db, axis );

    // FLIP_SUBCASE(case4, array_hs_fb, axis );
    // FLIP_SUBCASE(case4, array_hs_hb, axis );
    // FLIP_SUBCASE(case4, array_hs_db, axis );

    // FLIP_SUBCASE(case4, array_ds_fb, axis );
    // FLIP_SUBCASE(case4, array_ds_hb, axis );
    // FLIP_SUBCASE(case4, array_ds_db, axis );
}