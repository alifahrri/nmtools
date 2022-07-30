#include "nmtools/array/array/where.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/where.hpp"

#include <array>
#include <vector>

#define RUN_impl(...) \
nm::array::where(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs where fn to callable lambda
#define RUN_where(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("where-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_where(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define WHERE_SUBCASE(case_name,condition,x,y) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( view, where, case_name ); \
    auto array_array = RUN_where( case_name, args::condition, args::x, args::y ); \
    NMTOOLS_ASSERT_EQUAL( nm::dim(array_array), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_array), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_array, expect::result ); \
}

TEST_CASE("where(case1)" * doctest::test_suite("array::where"))
{
    WHERE_SUBCASE(case1, condition,   x,   y  );
    WHERE_SUBCASE(case1, condition_a, x_a, y_a);
    WHERE_SUBCASE(case1, condition_f, x_f, y_f);
    WHERE_SUBCASE(case1, condition_d, x_d, y_d);
    WHERE_SUBCASE(case1, condition_h, x_h, y_h);
}

TEST_CASE("where(case2)" * doctest::test_suite("array::where"))
{
    WHERE_SUBCASE(case2, condition,   x,   y  );
    WHERE_SUBCASE(case2, condition_a, x_a, y_a);
    WHERE_SUBCASE(case2, condition_f, x_f, y_f);
    WHERE_SUBCASE(case2, condition_d, x_d, y_d);
    WHERE_SUBCASE(case2, condition_h, x_h, y_h);
}

TEST_CASE("where(case3)" * doctest::test_suite("array::where"))
{
    WHERE_SUBCASE(case3, condition,   x,   y  );
    WHERE_SUBCASE(case3, condition_a, x_a, y_a);
    // TODO: remove support for nested vector
    WHERE_SUBCASE(case3, condition_f, x_f, y_f);
    WHERE_SUBCASE(case3, condition_d, x_d, y_d);
    WHERE_SUBCASE(case3, condition_h, x_h, y_h);
}