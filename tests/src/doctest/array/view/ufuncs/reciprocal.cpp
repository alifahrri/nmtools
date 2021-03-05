#include "nmtools/array/view/ufuncs/reciprocal.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, reciprocal)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {1,1,2},
            {3,4,5},
            {6,7,8},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {1/1.f,1/1.f,1/2.f},
            {1/3.f,1/4.f,1/5.f},
            {1/6.f,1/7.f,1/8.f},
        };
    }
}

#define RUN_reciprocal_impl(...) \
nm::view::reciprocal(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reciprocal fn to callable lambda
#define RUN_reciprocal(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reciprocal-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reciprocal_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reciprocal(case_name, ...) \
RUN_reciprocal_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RECIPROCAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reciprocal, case_name); \
    using namespace args; \
    auto result = RUN_reciprocal(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reciprocal(case1)" * doctest::test_suite("view::reciprocal"))
{
    RECIPROCAL_SUBCASE( case1,   a);
    RECIPROCAL_SUBCASE( case1, a_a);
    RECIPROCAL_SUBCASE( case1, a_v);
    RECIPROCAL_SUBCASE( case1, a_f);
    RECIPROCAL_SUBCASE( case1, a_d);
    RECIPROCAL_SUBCASE( case1, a_h);
}