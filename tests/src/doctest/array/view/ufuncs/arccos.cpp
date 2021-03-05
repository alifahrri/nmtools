#include "nmtools/array/view/ufuncs/arccos.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, arccos)
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
            {std::acos(0.0f),std::acos(0.1f),std::acos(0.2f)},
            {std::acos(0.3f),std::acos(0.4f),std::acos(0.5f)},
            {std::acos(0.6f),std::acos(0.7f),std::acos(0.8f)},
        };
    }
}

#define RUN_arccos_impl(...) \
nm::view::arccos(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arccos fn to callable lambda
#define RUN_arccos(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arccos-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arccos_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arccos(case_name, ...) \
RUN_arccos_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCCOS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, arccos, case_name); \
    using namespace args; \
    auto result = RUN_arccos(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arccos(case1)" * doctest::test_suite("view::arccos"))
{
    ARCCOS_SUBCASE( case1,   a);
    ARCCOS_SUBCASE( case1, a_a);
    ARCCOS_SUBCASE( case1, a_v);
    ARCCOS_SUBCASE( case1, a_f);
    ARCCOS_SUBCASE( case1, a_d);
    ARCCOS_SUBCASE( case1, a_h);
}