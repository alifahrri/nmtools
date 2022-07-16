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

#include "nmtools/array/view/conv.hpp"
#include "nmtools/testing/data/array/conv.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_conv2d_impl(...) \
nmtools::view::conv2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs conv2d fn to callable lambda
#define RUN_conv2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::conv2d-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_conv2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_conv2d(case_name, ...) \
RUN_conv2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, conv2d, case_name); \
    using namespace args; \
    auto result = RUN_conv2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using nmtools::None;

TEST_CASE("conv2d(case1)" * doctest::test_suite("view::conv2d"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(array, conv2d, case1);
        using namespace args;
        [[maybe_unused]] auto result = RUN_conv2d(case_name, input, weight);
    }
    CONV2D_SUBCASE( case1, input, weight );
    CONV2D_SUBCASE( case1, input_a, weight_a );
    CONV2D_SUBCASE( case1, input_f, weight_f );
    CONV2D_SUBCASE( case1, input_h, weight_h );
    CONV2D_SUBCASE( case1, input_d, weight_d );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_fs_db );

    // TODO: fix
    // CONV2D_SUBCASE( case1, input_hs_fb, weight_hs_fb );
    // CONV2D_SUBCASE( case1, input_hs_hb, weight_hs_hb );
    // CONV2D_SUBCASE( case1, input_hs_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_ds_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_cs_db );

    // CONV2D_SUBCASE( case1, input_hs_fb, weight_cs_fb );
    // CONV2D_SUBCASE( case1, input_hs_hb, weight_cs_hb );
    // CONV2D_SUBCASE( case1, input_hs_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_cs_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_cs_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_cs_db );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_fs_db );

    // CONV2D_SUBCASE( case1, input_hs_fb, weight_fs_fb );
    // CONV2D_SUBCASE( case1, input_hs_hb, weight_fs_hb );
    // CONV2D_SUBCASE( case1, input_hs_db, weight_fs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_fs_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_fs_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_fs_db );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_ds_fb, weight_hs_fb );
    CONV2D_SUBCASE( case1, input_ds_hb, weight_hs_hb );
    CONV2D_SUBCASE( case1, input_ds_db, weight_hs_db );

    CONV2D_SUBCASE( case1, input_cs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_cs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_cs_db, weight_ds_db );

    CONV2D_SUBCASE( case1, input_fs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case1, input_fs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case1, input_fs_db, weight_ds_db );

    // CONV2D_SUBCASE( case1, input_hs_fb, weight_ds_fb );
    // CONV2D_SUBCASE( case1, input_hs_hb, weight_ds_hb );
    // CONV2D_SUBCASE( case1, input_hs_db, weight_ds_db );
}

TEST_CASE("conv2d(case2)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case2, input, weight );
    CONV2D_SUBCASE( case2, input_a, weight_a );
    CONV2D_SUBCASE( case2, input_f, weight_f );
    CONV2D_SUBCASE( case2, input_h, weight_h );
    CONV2D_SUBCASE( case2, input_d, weight_d );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_fs_db );

    // CONV2D_SUBCASE( case2, input_hs_fb, weight_hs_fb );
    // CONV2D_SUBCASE( case2, input_hs_hb, weight_hs_hb );
    // CONV2D_SUBCASE( case2, input_hs_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_ds_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_cs_db );

    // CONV2D_SUBCASE( case2, input_hs_fb, weight_cs_fb );
    // CONV2D_SUBCASE( case2, input_hs_hb, weight_cs_hb );
    // CONV2D_SUBCASE( case2, input_hs_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_cs_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_cs_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_cs_db );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_fs_db );

    // CONV2D_SUBCASE( case2, input_hs_fb, weight_fs_fb );
    // CONV2D_SUBCASE( case2, input_hs_hb, weight_fs_hb );
    // CONV2D_SUBCASE( case2, input_hs_db, weight_fs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_fs_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_fs_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_fs_db );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_ds_fb, weight_hs_fb );
    CONV2D_SUBCASE( case2, input_ds_hb, weight_hs_hb );
    CONV2D_SUBCASE( case2, input_ds_db, weight_hs_db );

    CONV2D_SUBCASE( case2, input_cs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_cs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_cs_db, weight_ds_db );

    CONV2D_SUBCASE( case2, input_fs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case2, input_fs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case2, input_fs_db, weight_ds_db );

    // CONV2D_SUBCASE( case2, input_hs_fb, weight_ds_fb );
    // CONV2D_SUBCASE( case2, input_hs_hb, weight_ds_hb );
    // CONV2D_SUBCASE( case2, input_hs_db, weight_ds_db );
}

TEST_CASE("conv2d(case3)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case3, input, weight );
    CONV2D_SUBCASE( case3, input_a, weight_a );
    CONV2D_SUBCASE( case3, input_f, weight_f );
    CONV2D_SUBCASE( case3, input_h, weight_h );
    CONV2D_SUBCASE( case3, input_d, weight_d );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_fs_db );

    // CONV2D_SUBCASE( case3, input_hs_fb, weight_hs_fb );
    // CONV2D_SUBCASE( case3, input_hs_hb, weight_hs_hb );
    // CONV2D_SUBCASE( case3, input_hs_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_ds_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_cs_db );

    // CONV2D_SUBCASE( case3, input_hs_fb, weight_cs_fb );
    // CONV2D_SUBCASE( case3, input_hs_hb, weight_cs_hb );
    // CONV2D_SUBCASE( case3, input_hs_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_cs_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_cs_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_cs_db );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_fs_db );

    // CONV2D_SUBCASE( case3, input_hs_fb, weight_fs_fb );
    // CONV2D_SUBCASE( case3, input_hs_hb, weight_fs_hb );
    // CONV2D_SUBCASE( case3, input_hs_db, weight_fs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_fs_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_fs_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_fs_db );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_ds_fb, weight_hs_fb );
    CONV2D_SUBCASE( case3, input_ds_hb, weight_hs_hb );
    CONV2D_SUBCASE( case3, input_ds_db, weight_hs_db );

    CONV2D_SUBCASE( case3, input_cs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_cs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_cs_db, weight_ds_db );

    CONV2D_SUBCASE( case3, input_fs_fb, weight_ds_fb );
    CONV2D_SUBCASE( case3, input_fs_hb, weight_ds_hb );
    CONV2D_SUBCASE( case3, input_fs_db, weight_ds_db );

    // CONV2D_SUBCASE( case3, input_hs_fb, weight_ds_fb );
    // CONV2D_SUBCASE( case3, input_hs_hb, weight_ds_hb );
    // CONV2D_SUBCASE( case3, input_hs_db, weight_ds_db );
}

TEST_CASE("conv2d(case4)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case4, input, weight );
    CONV2D_SUBCASE( case4, input_a, weight_a );
    CONV2D_SUBCASE( case4, input_f, weight_f );
    CONV2D_SUBCASE( case4, input_h, weight_h );
    CONV2D_SUBCASE( case4, input_d, weight_d );

    CONV2D_SUBCASE( case4, input, weight, None, stride );
    CONV2D_SUBCASE( case4, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case4, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case4, input_h, weight_h, None, stride_h );
    // NOTE: stride must be index array
    // CONV2D_SUBCASE( case4, input_d, weight_d, stride_d );
    CONV2D_SUBCASE( case4, input_d, weight_d, None, stride_v );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case4, input_hs_fb, weight_hs_fb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_hb, weight_hs_hb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_cs_db, None, stride_a );

    // CONV2D_SUBCASE( case4, input_hs_fb, weight_cs_fb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_hb, weight_cs_hb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case4, input_hs_fb, weight_fs_fb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_hb, weight_fs_hb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case4, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case4, input_fs_db, weight_ds_db, None, stride_a );

    // CONV2D_SUBCASE( case4, input_hs_fb, weight_ds_fb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_hb, weight_ds_hb, None, stride_a );
    // CONV2D_SUBCASE( case4, input_hs_db, weight_ds_db, None, stride_a );
}

TEST_CASE("conv2d(case5)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case5, input, weight, None, stride );
    CONV2D_SUBCASE( case5, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case5, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case5, input_h, weight_h, None, stride_h );
    // NOTE: stride must be index array
    // CONV2D_SUBCASE( case5, input_d, weight_d, stride_d );
    CONV2D_SUBCASE( case5, input_d, weight_d, None, stride_v );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case5, input_hs_fb, weight_hs_fb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_hb, weight_hs_hb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_cs_db, None, stride_a );

    // CONV2D_SUBCASE( case5, input_hs_fb, weight_cs_fb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_hb, weight_cs_hb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case5, input_hs_fb, weight_fs_fb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_hb, weight_fs_hb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_ds_db, None, stride_a );

    // CONV2D_SUBCASE( case5, input_hs_fb, weight_ds_fb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_hb, weight_ds_hb, None, stride_a );
    // CONV2D_SUBCASE( case5, input_hs_db, weight_ds_db, None, stride_a );
}

TEST_CASE("conv2d(case6)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case6, input, weight, None, stride );
    CONV2D_SUBCASE( case6, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case6, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case6, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case6, input_d, weight_d, None, stride_v );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case6, input_hs_fb, weight_hs_fb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_hb, weight_hs_hb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_cs_db, None, stride_a );

    // CONV2D_SUBCASE( case6, input_hs_fb, weight_cs_fb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_hb, weight_cs_hb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case6, input_hs_fb, weight_fs_fb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_hb, weight_fs_hb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_ds_db, None, stride_a );

    // CONV2D_SUBCASE( case6, input_hs_fb, weight_ds_fb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_hb, weight_ds_hb, None, stride_a );
    // CONV2D_SUBCASE( case6, input_hs_db, weight_ds_db, None, stride_a );
}

TEST_CASE("conv2d(case7)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case7, input, weight, None, stride );
    CONV2D_SUBCASE( case7, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case7, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case7, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case7, input_d, weight_d, None, stride_v );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case7, input_hs_fb, weight_hs_fb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_hb, weight_hs_hb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_cs_db, None, stride_a );

    // CONV2D_SUBCASE( case7, input_hs_fb, weight_cs_fb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_hb, weight_cs_hb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case7, input_hs_fb, weight_fs_fb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_hb, weight_fs_hb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_ds_db, None, stride_a );

    // CONV2D_SUBCASE( case7, input_hs_fb, weight_ds_fb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_hb, weight_ds_hb, None, stride_a );
    // CONV2D_SUBCASE( case7, input_hs_db, weight_ds_db, None, stride_a );
}

TEST_CASE("conv2d(case8)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case8, input, weight, None, stride );
    CONV2D_SUBCASE( case8, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case8, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case8, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case8, input_d, weight_d, None, stride_v );
}

TEST_CASE("conv2d(case9)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case9, input, weight, None, stride );
    CONV2D_SUBCASE( case9, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case9, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case9, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case9, input_d, weight_d, None, stride_v );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case9, input_hs_fb, weight_hs_fb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_hb, weight_hs_hb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_cs_db, None, stride_a );

    // CONV2D_SUBCASE( case9, input_hs_fb, weight_cs_fb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_hb, weight_cs_hb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case9, input_hs_fb, weight_fs_fb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_hb, weight_fs_hb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_ds_db, None, stride_a );

    // CONV2D_SUBCASE( case9, input_hs_fb, weight_ds_fb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_hb, weight_ds_hb, None, stride_a );
    // CONV2D_SUBCASE( case9, input_hs_db, weight_ds_db, None, stride_a );
}

TEST_CASE("conv2d(case10)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case10, input, weight, None, stride );
    CONV2D_SUBCASE( case10, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case10, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case10, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case10, input_d, weight_d, None, stride_v );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case10, input_hs_fb, weight_hs_fb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_hb, weight_hs_hb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_cs_db, None, stride_a );

    // CONV2D_SUBCASE( case10, input_hs_fb, weight_cs_fb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_hb, weight_cs_hb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_fs_db, None, stride_a );

    // CONV2D_SUBCASE( case10, input_hs_fb, weight_fs_fb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_hb, weight_fs_hb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_ds_db, None, stride_a );

    // CONV2D_SUBCASE( case10, input_hs_fb, weight_ds_fb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_hb, weight_ds_hb, None, stride_a );
    // CONV2D_SUBCASE( case10, input_hs_db, weight_ds_db, None, stride_a );
}

TEST_CASE("conv2d(case11)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case11, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case11, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case11, input_h, weight_h, None, stride_h, padding_h );
    CONV2D_SUBCASE( case11, input_d, weight_d, None, stride_v, padding_v );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_fs_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case11, input_hs_fb, weight_hs_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_hb, weight_hs_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_cs_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case11, input_hs_fb, weight_cs_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_hb, weight_cs_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_fs_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case11, input_hs_fb, weight_fs_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_hb, weight_fs_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_ds_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case11, input_hs_fb, weight_ds_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_hb, weight_ds_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case11, input_hs_db, weight_ds_db, None, stride_a, padding_a );
}

TEST_CASE("conv2d(case12)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case12, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case12, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case12, input_h, weight_h, None, stride_h, padding_h );
    CONV2D_SUBCASE( case12, input_d, weight_d, None, stride_v, padding_v );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_fs_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case12, input_hs_fb, weight_hs_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_hb, weight_hs_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_cs_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case12, input_hs_fb, weight_cs_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_hb, weight_cs_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_fs_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case12, input_hs_fb, weight_fs_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_hb, weight_fs_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_ds_db, None, stride_a, padding_a );

    // CONV2D_SUBCASE( case12, input_hs_fb, weight_ds_fb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_hb, weight_ds_hb, None, stride_a, padding_a );
    // CONV2D_SUBCASE( case12, input_hs_db, weight_ds_db, None, stride_a, padding_a );
}

TEST_CASE("conv2d(case13)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case13, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case13, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case13, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case13, input_h, weight_h, None, stride, padding );
    CONV2D_SUBCASE( case13, input_d, weight_d, None, stride, padding );
}

TEST_CASE("conv2d(case14)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case14, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case14, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case14, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case14, input_h, weight_h, None, stride, padding );
    CONV2D_SUBCASE( case14, input_d, weight_d, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_fs_db, None, stride, padding );

    // CONV2D_SUBCASE( case14, input_hs_fb, weight_hs_fb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_hb, weight_hs_hb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_cs_db, None, stride, padding );

    // CONV2D_SUBCASE( case14, input_hs_fb, weight_cs_fb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_hb, weight_cs_hb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_fs_db, None, stride, padding );

    // CONV2D_SUBCASE( case14, input_hs_fb, weight_fs_fb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_hb, weight_fs_hb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_ds_db, None, stride, padding );

    // CONV2D_SUBCASE( case14, input_hs_fb, weight_ds_fb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_hb, weight_ds_hb, None, stride, padding );
    // CONV2D_SUBCASE( case14, input_hs_db, weight_ds_db, None, stride, padding );
}

TEST_CASE("conv2d(case15)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case15, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case15, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case15, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case15, input_h, weight_h, None, stride, padding );
    CONV2D_SUBCASE( case15, input_d, weight_d, None, stride, padding );

    CONV2D_SUBCASE( case15, input_cs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_fs_db, None, stride, padding );

    // CONV2D_SUBCASE( case15, input_hs_fb, weight_hs_fb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_hb, weight_hs_hb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_cs_db, None, stride, padding );

    // CONV2D_SUBCASE( case15, input_hs_fb, weight_cs_fb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_hb, weight_cs_hb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_cs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_fs_db, None, stride, padding );

    // CONV2D_SUBCASE( case15, input_hs_fb, weight_fs_fb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_hb, weight_fs_hb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_cs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_cs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_ds_db, None, stride, padding );

    // CONV2D_SUBCASE( case15, input_hs_fb, weight_ds_fb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_hb, weight_ds_hb, None, stride, padding );
    // CONV2D_SUBCASE( case15, input_hs_db, weight_ds_db, None, stride, padding );
}

TEST_CASE("conv2d(case16)" * doctest::test_suite("view::conv2d"))
{
    CONV2D_SUBCASE( case16, input, weight, bias, stride, padding );
    CONV2D_SUBCASE( case16, input_a, weight_a, bias_a, stride, padding );
    CONV2D_SUBCASE( case16, input_f, weight_f, bias_f, stride, padding );
    CONV2D_SUBCASE( case16, input_h, weight_h, bias_h, stride, padding );
    CONV2D_SUBCASE( case16, input_d, weight_d, bias_d, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_fs_db, bias_fs_db, stride, padding );

    // CONV2D_SUBCASE( case16, input_hs_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_ds_db, bias_ds_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_cs_db, bias_cs_db, stride, padding );

    // CONV2D_SUBCASE( case16, input_hs_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_fs_db, bias_fs_db, stride, padding );

    // CONV2D_SUBCASE( case16, input_hs_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_db, weight_fs_db, bias_fs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_fs_db, bias_fs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_ds_db, bias_ds_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_ds_db, bias_ds_db, stride, padding );

    // CONV2D_SUBCASE( case16, input_hs_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    // CONV2D_SUBCASE( case16, input_hs_db, weight_ds_db, bias_ds_db, stride, padding );
}