#include "nmtools/array/view/softmax.hpp"
#include "nmtools/testing/data/array/softmax.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_softmax_impl(...) \
nmtools::view::softmax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs softmax fn to callable lambda
#define RUN_softmax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::softmax-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_softmax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_softmax(case_name, ...) \
RUN_softmax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SOFTMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, softmax, case_name); \
    using namespace args; \
    auto result = RUN_softmax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softmax(case1)" * doctest::test_suite("view::softmax"))
{
    SOFTMAX_SUBCASE( case1, input, dim );
    SOFTMAX_SUBCASE( case1, input_a, dim );
    SOFTMAX_SUBCASE( case1, input_f, dim );
    SOFTMAX_SUBCASE( case1, input_h, dim );
    SOFTMAX_SUBCASE( case1, input_d, dim );
}

TEST_CASE("softmax(case2)" * doctest::test_suite("view::softmax"))
{
    SOFTMAX_SUBCASE( case2, input, dim );
    SOFTMAX_SUBCASE( case2, input_a, dim );
    SOFTMAX_SUBCASE( case2, input_f, dim );
    SOFTMAX_SUBCASE( case2, input_h, dim );
    SOFTMAX_SUBCASE( case2, input_d, dim );
}

TEST_CASE("softmax(case3)" * doctest::test_suite("view::softmax"))
{
    SOFTMAX_SUBCASE( case3, input, dim );
    SOFTMAX_SUBCASE( case3, input_a, dim );
    SOFTMAX_SUBCASE( case3, input_f, dim );
    SOFTMAX_SUBCASE( case3, input_h, dim );
    SOFTMAX_SUBCASE( case3, input_d, dim );
}

TEST_CASE("softmax(case4)" * doctest::test_suite("view::softmax"))
{
    SOFTMAX_SUBCASE( case4, input, dim );
    SOFTMAX_SUBCASE( case4, input_a, dim );
    SOFTMAX_SUBCASE( case4, input_f, dim );
    SOFTMAX_SUBCASE( case4, input_h, dim );
    SOFTMAX_SUBCASE( case4, input_d, dim );
}

TEST_CASE("softmax(case5)" * doctest::test_suite("view::softmax"))
{
    SOFTMAX_SUBCASE( case5, input, dim );
    SOFTMAX_SUBCASE( case5, input_a, dim );
    SOFTMAX_SUBCASE( case5, input_f, dim );
    SOFTMAX_SUBCASE( case5, input_h, dim );
    SOFTMAX_SUBCASE( case5, input_d, dim );
}