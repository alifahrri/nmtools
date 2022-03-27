#include "nmtools/array/view/ufuncs/cbrt.hpp"
#include "nmtools/testing/data/array/cbrt.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_cbrt_impl(...) \
nm::view::cbrt(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs cbrt fn to callable lambda
#define RUN_cbrt(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("cbrt-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_cbrt_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_cbrt(case_name, ...) \
RUN_cbrt_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CBRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, cbrt, case_name); \
    using namespace args; \
    auto result = RUN_cbrt(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cbrt(case1)" * doctest::test_suite("view::cbrt"))
{
    CBRT_SUBCASE( case1,   a);
    CBRT_SUBCASE( case1, a_a);
    CBRT_SUBCASE( case1, a_v);
    CBRT_SUBCASE( case1, a_f);
    CBRT_SUBCASE( case1, a_d);
    CBRT_SUBCASE( case1, a_h);
}

#define CBRT_FIXED_SHAPE_SUBCASE(subcase_name, expected_shape, ...) \
SUBCASE(#subcase_name) \
{ \
    auto result = RUN_cbrt(subcase_name, __VA_ARGS__); \
    using result_t = decltype(result); \
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_size_ndarray, result_t ); \
    NMTOOLS_STATIC_ASSERT_EQUAL( meta::fixed_ndarray_shape_v<result_t>, expected_shape ); \
}

TEST_CASE("cbrt(fixed_shape)" * doctest::test_suite("view::cbrt"))
{
    namespace meta = nmtools::meta;
    {
        constexpr auto expected_shape = std::array{3};
        int A[3] = {1,2,3};
        CBRT_FIXED_SHAPE_SUBCASE( raw, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = std::array{1,2,3};
        CBRT_FIXED_SHAPE_SUBCASE( array, expected_shape, A );
    }
    {
        constexpr auto expected_shape = std::array{3};
        auto A = na::fixed_ndarray{{1,2,3}};
        CBRT_FIXED_SHAPE_SUBCASE( fixed_ndarray, expected_shape, A );
    }
}