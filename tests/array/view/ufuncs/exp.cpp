#include "nmtools/array/view/ufuncs/exp.hpp"
#include "nmtools/testing/data/array/exp.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_exp_impl(...) \
nm::view::exp(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs exp fn to callable lambda
#define RUN_exp(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("exp-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_exp_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_exp(case_name, ...) \
RUN_exp_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define EXP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, exp, case_name); \
    using namespace args; \
    auto result = RUN_exp(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("exp(case1)" * doctest::test_suite("view::exp"))
{
    EXP_SUBCASE( case1,   a);
    EXP_SUBCASE( case1, a_a);
    EXP_SUBCASE( case1, a_f);
    EXP_SUBCASE( case1, a_d);
    EXP_SUBCASE( case1, a_h);
}

#define EXP_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_exp(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("exp(fixed_shape)" * doctest::test_suite("view::exp"))
{
    namespace meta = nmtools::meta;
    {
        constexpr auto expected_shape = std::array{3};
        int A[3] = {1,2,3};
        EXP_FIXED_SHAPE_SUBCASE( raw, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = std::array{1,2,3};
        EXP_FIXED_SHAPE_SUBCASE( array, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = na::fixed_ndarray{{1,2,3}};
        EXP_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A );
    }
}