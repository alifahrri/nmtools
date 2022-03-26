#include "nmtools/array/view/ufuncs/log1p.hpp"
#include "nmtools/testing/data/array/log1p.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_log1p_impl(...) \
nm::view::log1p(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs log1p fn to callable lambda
#define RUN_log1p(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("log1p-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_log1p_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_log1p(case_name, ...) \
RUN_log1p_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOG1P_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, log1p, case_name); \
    using namespace args; \
    auto result = RUN_log1p(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log1p(case1)" * doctest::test_suite("view::log1p"))
{
    LOG1P_SUBCASE( case1,   a);
    LOG1P_SUBCASE( case1, a_a);
    LOG1P_SUBCASE( case1, a_v);
    LOG1P_SUBCASE( case1, a_f);
    LOG1P_SUBCASE( case1, a_d);
    LOG1P_SUBCASE( case1, a_h);
}

#define LOG1P_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_log1p(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("log1p(fixed_shape)" * doctest::test_suite("view::log1p"))
{
    namespace meta = nmtools::meta;
    {
        constexpr auto expected_shape = std::array{3};
        int A[3] = {1,2,3};
        LOG1P_FIXED_SHAPE_SUBCASE( raw, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = std::array{1,2,3};
        LOG1P_FIXED_SHAPE_SUBCASE( array, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = na::fixed_ndarray{{1,2,3}};
        LOG1P_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A );
    }
}