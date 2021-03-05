#include "nmtools/array/view/ufuncs/logical_not.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, logical_not)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        bool a[3][3] = {
            { true, false,  true},
            {false,  true, false},
            { true, false,  true},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        bool result[3][3] = {
            { !true, !false,  !true},
            {!false,  !true, !false},
            { !true, !false,  !true},
        };
    }
}

#define RUN_logical_not_impl(...) \
nm::view::logical_not(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs logical_not fn to callable lambda
#define RUN_logical_not(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("logical_not-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_logical_not_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_logical_not(case_name, ...) \
RUN_logical_not_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOGICAL_NOT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, logical_not, case_name); \
    using namespace args; \
    auto result = RUN_logical_not(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_not(case1)" * doctest::test_suite("view::logical_not"))
{
    LOGICAL_NOT_SUBCASE( case1,   a );
    LOGICAL_NOT_SUBCASE( case1, a_a );
    LOGICAL_NOT_SUBCASE( case1, a_v );
    LOGICAL_NOT_SUBCASE( case1, a_f );
    LOGICAL_NOT_SUBCASE( case1, a_d );
    LOGICAL_NOT_SUBCASE( case1, a_h );
}