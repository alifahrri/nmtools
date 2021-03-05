#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, sqrt)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        int b[3] = {0,1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::sqrt(0.f),std::sqrt(1.f),std::sqrt(2.f)},
            {std::sqrt(3.f),std::sqrt(4.f),std::sqrt(5.f)},
            {std::sqrt(6.f),std::sqrt(7.f),std::sqrt(8.f)},
        };
    }
}

#define RUN_sqrt_impl(...) \
nm::view::sqrt(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs sqrt fn to callable lambda
#define RUN_sqrt(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("sqrt-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_sqrt_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_sqrt(case_name, ...) \
RUN_sqrt_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SQRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, sqrt, case_name); \
    using namespace args; \
    auto result = RUN_sqrt(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sqrt(case1)" * doctest::test_suite("view::sqrt"))
{
    SQRT_SUBCASE( case1,   a);
    SQRT_SUBCASE( case1, a_a);
    SQRT_SUBCASE( case1, a_v);
    SQRT_SUBCASE( case1, a_f);
    SQRT_SUBCASE( case1, a_d);
    SQRT_SUBCASE( case1, a_h);
}