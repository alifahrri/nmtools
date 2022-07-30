#include "nmtools/array/array/mean.hpp"
#include "nmtools/testing/data/array/mean.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_mean_impl(...) \
nm::array::mean(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs mean fn to callable lambda
#define RUN_mean(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("mean-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_mean_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_mean(case_name, ...) \
RUN_mean_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MEAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case_name); \
    using namespace args; \
    auto result = RUN_mean(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


TEST_CASE("mean(case1)" * doctest::test_suite("array::mean"))
{
    MEAN_SUBCASE(case1, a, axis);
    MEAN_SUBCASE(case1, a_a, axis);
    MEAN_SUBCASE(case1, a_f, axis);
    MEAN_SUBCASE(case1, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case1, a_d, axis);
}

TEST_CASE("mean(case2)" * doctest::test_suite("array::mean"))
{
    MEAN_SUBCASE(case2, a, axis);
    MEAN_SUBCASE(case2, a_a, axis);
    MEAN_SUBCASE(case2, a_f, axis);
    MEAN_SUBCASE(case2, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case2, a_d, axis);
}

TEST_CASE("mean(case3)" * doctest::test_suite("array::mean"))
{
    MEAN_SUBCASE(case3, a, axis);
    MEAN_SUBCASE(case3, a_a, axis);
    MEAN_SUBCASE(case3, a_f, axis);
    MEAN_SUBCASE(case3, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case3, a_d, axis);
}

TEST_CASE("mean(case4)" * doctest::test_suite("array::mean"))
{
    MEAN_SUBCASE(case4, a, axis);
    MEAN_SUBCASE(case4, a_a, axis);
    MEAN_SUBCASE(case4, a_f, axis);
    MEAN_SUBCASE(case4, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case4, a_d, axis);
}

TEST_CASE("mean(case5)" * doctest::test_suite("array::mean"))
{
    MEAN_SUBCASE(case5, a, axis);
    MEAN_SUBCASE(case5, a_a, axis);
    MEAN_SUBCASE(case5, a_f, axis);
    MEAN_SUBCASE(case5, a_h, axis);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case4, a_d, axis);
}

TEST_CASE("mean(case6)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case6, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case6, a_d, axis, dtype, keepdims);
}

namespace meta = nm::meta;

TEST_CASE("mean(case7)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    {
        NMTOOLS_TESTING_DECLARE_NS(array, mean, case7);
        using namespace args;
        auto result = na::mean(a, axis, dtype, keepdims);
        using result_t = decltype(result);
        using left_t   = meta::get_either_left_t<result_t>;
        using right_t  = meta::get_either_right_t<result_t>;
        static_assert( meta::is_either_v<result_t> );
        static_assert( meta::is_num_v<left_t> );
        static_assert( meta::is_ndarray_v<right_t> );
        auto rptr = nmtools::get_if<right_t>(&result);
        CHECK( rptr );
        NMTOOLS_ASSERT_EQUAL( nm::shape(*rptr), expect::shape );
    }

    MEAN_SUBCASE(case7, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case7, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case8)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case8, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case8, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case9)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case9, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case9, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case10)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case10, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case10, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case11)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case11, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case11, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case12)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case12, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case12, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case12, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case12, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case12, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case13)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case13, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case13, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case14)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case14, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case14, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case15)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case15, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case15, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case16)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case16, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case16, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case17)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case17, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case17, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case18)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case18, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case18, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case19)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case19, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case19, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case20)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case20, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case20, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case21)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case21, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case21, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case22)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case22, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case22, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case23)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case23, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case23, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case24)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case24, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case24, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case25)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case25, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case25, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case26)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case26, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case26, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case27)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case27, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case27, a_d, axis, dtype, keepdims);
}

TEST_CASE("mean(case28)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case28, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_h, axis, dtype, keepdims);
    // NOTE: dynamic-size, dynamic-dim ndarray not supported yet, not supported by reducer
    // TODO: support dynamic-size, dynamic-dim ndarray, by generalizing reducer
    // MEAN_SUBCASE(case28, a_d, axis, dtype, keepdims);
}