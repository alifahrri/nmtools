#include "nmtools/array/view/ufuncs/floor.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, floor)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {1.0,2.1,3.2},
            {1.3,2.4,3.5},
            {1.6,2.7,3.8},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::floor(1.0f),std::floor(2.1f),std::floor(3.2f)},
            {std::floor(1.3f),std::floor(2.4f),std::floor(3.5f)},
            {std::floor(1.6f),std::floor(2.7f),std::floor(3.8f)},
        };
    }
}

#define RUN_floor_impl(...) \
nm::view::floor(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs floor fn to callable lambda
#define RUN_floor(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("floor-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_floor_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_floor(case_name, ...) \
RUN_floor_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FLOOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, floor, case_name); \
    using namespace args; \
    auto result = RUN_floor(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("floor(case1)" * doctest::test_suite("view::floor"))
{
    FLOOR_SUBCASE( case1,   a);
    FLOOR_SUBCASE( case1, a_a);
    FLOOR_SUBCASE( case1, a_v);
    FLOOR_SUBCASE( case1, a_f);
    FLOOR_SUBCASE( case1, a_d);
    FLOOR_SUBCASE( case1, a_h);
}