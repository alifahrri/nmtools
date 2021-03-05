#include "nmtools/array/view/ufuncs/isinf.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

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

NMTOOLS_TESTING_DECLARE_CASE(view, isinf)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        double a[3][3] = {
            { 0.1, INFINITY, 0.3 },
            { NAN,    NAN,   NAN },
            { 0.1, INFINITY, 0.3 },
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        bool result[3][3] = {
            { std::isinf(0.1), std::isinf(INFINITY), std::isinf(0.3) },
            { std::isinf(NAN), std::isinf(   NAN  ), std::isinf(NAN) },
            { std::isinf(0.1), std::isinf(INFINITY), std::isinf(0.3) },
        };
    }
}

#define RUN_isinf_impl(...) \
nm::view::isinf(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs isinf fn to callable lambda
#define RUN_isinf(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("isinf-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_isinf_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_isinf(case_name, ...) \
RUN_isinf_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ISINF_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, isinf, case_name); \
    using namespace args; \
    auto result = RUN_isinf(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isinf(case1)" * doctest::test_suite("view::isinf"))
{
    ISINF_SUBCASE( case1,   a );
    ISINF_SUBCASE( case1, a_a );
    ISINF_SUBCASE( case1, a_v );
    ISINF_SUBCASE( case1, a_f );
    ISINF_SUBCASE( case1, a_d );
    ISINF_SUBCASE( case1, a_h );
}