#include "nmtools/array/view/ufuncs/positive.hpp"
#include "nmtools/testing/data/array/positive.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_positive_impl(...) \
nm::view::positive(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs positive fn to callable lambda
#define RUN_positive(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("positive-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_positive_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_positive(case_name, ...) \
RUN_positive_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define POSITIVE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, positive, case_name); \
    using namespace args; \
    auto result = RUN_positive(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("positive(case1)" * doctest::test_suite("view::positive"))
{
    POSITIVE_SUBCASE( case1,   a);
    POSITIVE_SUBCASE( case1, a_a);
    POSITIVE_SUBCASE( case1, a_f);
    POSITIVE_SUBCASE( case1, a_d);
    POSITIVE_SUBCASE( case1, a_h);
}