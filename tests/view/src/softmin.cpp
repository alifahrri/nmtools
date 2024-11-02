#include "nmtools/array/view/softmin.hpp"
#include "nmtools/testing/data/array/softmin.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_softmin_impl(...) \
nmtools::view::softmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs softmin fn to callable lambda
#define RUN_softmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::softmin-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_softmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_softmin(case_name, ...) \
RUN_softmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SOFTMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, softmin, case_name); \
    using namespace args; \
    auto result = RUN_softmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softmin(case1)" * doctest::test_suite("view::softmin"))
{
    SOFTMIN_SUBCASE( case1, input, dim );
    SOFTMIN_SUBCASE( case1, input_a, dim );
    SOFTMIN_SUBCASE( case1, input_f, dim );
    SOFTMIN_SUBCASE( case1, input_h, dim );
    SOFTMIN_SUBCASE( case1, input_d, dim );
}

TEST_CASE("softmin(case2)" * doctest::test_suite("view::softmin"))
{
    SOFTMIN_SUBCASE( case2, input, dim );
    SOFTMIN_SUBCASE( case2, input_a, dim );
    SOFTMIN_SUBCASE( case2, input_f, dim );
    SOFTMIN_SUBCASE( case2, input_h, dim );
    SOFTMIN_SUBCASE( case2, input_d, dim );
}

TEST_CASE("softmin(case3)" * doctest::test_suite("view::softmin"))
{
    SOFTMIN_SUBCASE( case3, input, dim );
    SOFTMIN_SUBCASE( case3, input_a, dim );
    SOFTMIN_SUBCASE( case3, input_f, dim );
    SOFTMIN_SUBCASE( case3, input_h, dim );
    SOFTMIN_SUBCASE( case3, input_d, dim );
}

TEST_CASE("softmin(case4)" * doctest::test_suite("view::softmin"))
{
    SOFTMIN_SUBCASE( case4, input, dim );
    SOFTMIN_SUBCASE( case4, input_a, dim );
    SOFTMIN_SUBCASE( case4, input_f, dim );
    SOFTMIN_SUBCASE( case4, input_h, dim );
    SOFTMIN_SUBCASE( case4, input_d, dim );
}

TEST_CASE("softmin(case5)" * doctest::test_suite("view::softmin"))
{
    SOFTMIN_SUBCASE( case5, input, dim );
    SOFTMIN_SUBCASE( case5, input_a, dim );
    SOFTMIN_SUBCASE( case5, input_f, dim );
    SOFTMIN_SUBCASE( case5, input_h, dim );
    SOFTMIN_SUBCASE( case5, input_d, dim );
}