#include "nmtools/array/view/ufuncs/arctan.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, arctan)
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
            {std::atan(0.0f),std::atan(0.1f),std::atan(0.2f)},
            {std::atan(0.3f),std::atan(0.4f),std::atan(0.5f)},
            {std::atan(0.6f),std::atan(0.7f),std::atan(0.8f)},
        };
    }
}

#define RUN_arctan_impl(...) \
nm::view::arctan(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arctan fn to callable lambda
#define RUN_arctan(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arctan-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arctan_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arctan(case_name, ...) \
RUN_arctan_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCTAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, arctan, case_name); \
    using namespace args; \
    auto result = RUN_arctan(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctan(case1)" * doctest::test_suite("view::arctan"))
{
    ARCTAN_SUBCASE( case1,   a);
    ARCTAN_SUBCASE( case1, a_a);
    ARCTAN_SUBCASE( case1, a_v);
    ARCTAN_SUBCASE( case1, a_f);
    ARCTAN_SUBCASE( case1, a_d);
    ARCTAN_SUBCASE( case1, a_h);
}