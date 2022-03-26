#include "nmtools/array/view/squeeze.hpp"
#include "nmtools/testing/data/array/squeeze.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::view::squeeze(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs squeeze fn to callable lambda
#define RUN_squeeze(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("squeeze-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_squeeze(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SQUEEZE_SUBCASE(case_name, array) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(squeeze, case_name) \
    auto array_ref = RUN_squeeze(case_name, args::array); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("squeeze(case1)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case1, array );
    SQUEEZE_SUBCASE( case1, array_a );
    SQUEEZE_SUBCASE( case1, array_v );
    SQUEEZE_SUBCASE( case1, array_f );
    SQUEEZE_SUBCASE( case1, array_d );
    SQUEEZE_SUBCASE( case1, array_h );
}

TEST_CASE("squeeze(case2)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case2, array );
    SQUEEZE_SUBCASE( case2, array_a );
    SQUEEZE_SUBCASE( case2, array_v );
    SQUEEZE_SUBCASE( case2, array_f );
    SQUEEZE_SUBCASE( case2, array_d );
    SQUEEZE_SUBCASE( case2, array_h );
}

TEST_CASE("squeeze(case3)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case3, array );
    SQUEEZE_SUBCASE( case3, array_a );
    SQUEEZE_SUBCASE( case3, array_v );
    SQUEEZE_SUBCASE( case3, array_f );
    SQUEEZE_SUBCASE( case3, array_d );
    SQUEEZE_SUBCASE( case3, array_h );
}

TEST_CASE("squeeze(case4)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case4, array );
    SQUEEZE_SUBCASE( case4, array_a );
    SQUEEZE_SUBCASE( case4, array_v );
    SQUEEZE_SUBCASE( case4, array_f );
    SQUEEZE_SUBCASE( case4, array_d );
    SQUEEZE_SUBCASE( case4, array_h );
}

TEST_CASE("squeeze(case5)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case5, array );
    SQUEEZE_SUBCASE( case5, array_a );
    SQUEEZE_SUBCASE( case5, array_v );
    SQUEEZE_SUBCASE( case5, array_f );
    SQUEEZE_SUBCASE( case5, array_d );
    SQUEEZE_SUBCASE( case5, array_h );
}

TEST_CASE("squeeze(case6)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case6, array );
    SQUEEZE_SUBCASE( case6, array_a );
    SQUEEZE_SUBCASE( case6, array_v );
    SQUEEZE_SUBCASE( case6, array_f );
    SQUEEZE_SUBCASE( case6, array_d );
    SQUEEZE_SUBCASE( case6, array_h );
}