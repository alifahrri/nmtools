#include "nmtools/array/view/ufuncs/log1p.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, log1p)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::log1p(0.f),std::log1p(1.f),std::log1p(2.f)},
            {std::log1p(3.f),std::log1p(4.f),std::log1p(5.f)},
            {std::log1p(6.f),std::log1p(7.f),std::log1p(8.f)},
        };
    }
}

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