#include "nmtools/array/view/ufuncs/exp2.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, exp2)
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
            {std::exp2(0.f),std::exp2(1.f),std::exp2(2.f)},
            {std::exp2(3.f),std::exp2(4.f),std::exp2(5.f)},
            {std::exp2(6.f),std::exp2(7.f),std::exp2(8.f)},
        };
    }
}

#define RUN_exp2_impl(...) \
nm::view::exp2(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs exp2 fn to callable lambda
#define RUN_exp2(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("exp2-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_exp2_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_exp2(case_name, ...) \
RUN_exp2_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define EXP2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, exp2, case_name); \
    using namespace args; \
    auto result = RUN_exp2(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("exp2(case1)" * doctest::test_suite("view::exp2"))
{
    EXP2_SUBCASE( case1,   a);
    EXP2_SUBCASE( case1, a_a);
    EXP2_SUBCASE( case1, a_v);
    EXP2_SUBCASE( case1, a_f);
    EXP2_SUBCASE( case1, a_d);
    EXP2_SUBCASE( case1, a_h);
}