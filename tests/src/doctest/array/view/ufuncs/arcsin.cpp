#include "nmtools/array/view/ufuncs/arcsin.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, arcsin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {0.0,0.1,0.2},
            {0.3,0.4,0.5},
            {0.6,0.7,0.8},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::asin(0.0f),std::asin(0.1f),std::asin(0.2f)},
            {std::asin(0.3f),std::asin(0.4f),std::asin(0.5f)},
            {std::asin(0.6f),std::asin(0.7f),std::asin(0.8f)},
        };
    }
}

#define RUN_arcsin_impl(...) \
nm::view::arcsin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arcsin fn to callable lambda
#define RUN_arcsin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arcsin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arcsin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arcsin(case_name, ...) \
RUN_arcsin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCSIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, arcsin, case_name); \
    using namespace args; \
    auto result = RUN_arcsin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arcsin(case1)" * doctest::test_suite("view::arcsin"))
{
    ARCSIN_SUBCASE( case1,   a);
    ARCSIN_SUBCASE( case1, a_a);
    ARCSIN_SUBCASE( case1, a_v);
    ARCSIN_SUBCASE( case1, a_f);
    ARCSIN_SUBCASE( case1, a_d);
    ARCSIN_SUBCASE( case1, a_h);
}