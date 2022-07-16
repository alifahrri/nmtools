#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(nonzero)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int x[6] = {0,1,2,3,4,5};
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_h = cast(x,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[5] = {1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int x[6] = {1,2,0,3,5,6};
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_h = cast(x,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[5] = {0,1,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        bool x[6] = {true,true,false,true,true,true};
        auto x_v = cast<std::vector<bool>>(x);
        auto x_a = cast<bool>(x);
        auto x_h = cast(x,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[5] = {0,1,3,4,5};
    }
}


#define RUN_impl(...) \
nm::index::nonzero(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs nonzero fn to callable lambda
#define RUN_nonzero(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("nonzero-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run<false>(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_nonzero(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define NONZERO_SUBCASE(case_name, x) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(nonzero, case_name); \
    auto result = RUN_nonzero(case_name, args::x); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
} \

TEST_CASE("nonzero(case1)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case1, x_a );
    NONZERO_SUBCASE( case1, x_v );
    NONZERO_SUBCASE( case1, x_h );
}

TEST_CASE("nonzero(case2)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case2, x_a );
    NONZERO_SUBCASE( case2, x_v );
    NONZERO_SUBCASE( case2, x_h );
}

TEST_CASE("nonzero(case3)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case3, x_a );
    NONZERO_SUBCASE( case3, x_v );
    NONZERO_SUBCASE( case3, x_h );
}