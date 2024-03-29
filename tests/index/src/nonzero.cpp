#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

NMTOOLS_TESTING_DECLARE_CASE(nonzero)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int x[6] = {0,1,2,3,4,5};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        auto x_ct = nmtools_tuple{0_ct,1_ct,2_ct,3_ct,4_ct,5_ct};
        auto x_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct,"4:[4]"_ct,"5:[5]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[5] = {1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int x[6] = {1,2,0,3,5,6};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        auto x_ct = nmtools_tuple{1_ct,2_ct,0_ct,3_ct,5_ct,6_ct};
        auto x_cl = nmtools_tuple{"1:[1]"_ct,"2:[2]"_ct,"0:[1]"_ct,"3:[3]"_ct,"5:[5]"_ct,"6:[6]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[5] = {0,1,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        bool x[6] = {true,true,false,true,true,true};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
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
    NONZERO_SUBCASE( case1, x_ct );
    NONZERO_SUBCASE( case1, x_cl );
}

TEST_CASE("nonzero(case2)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case2, x_a );
    NONZERO_SUBCASE( case2, x_v );
    NONZERO_SUBCASE( case2, x_h );
    NONZERO_SUBCASE( case2, x_ct );
    NONZERO_SUBCASE( case2, x_cl );
}

TEST_CASE("nonzero(case3)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case3, x_a );
    NONZERO_SUBCASE( case3, x_v );
    NONZERO_SUBCASE( case3, x_h );
}