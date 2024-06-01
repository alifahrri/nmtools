#include "nmtools/array/array/ufuncs/invert.hpp"
#include "nmtools/testing/data/array/invert.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_invert_impl(...) \
nm::array::invert(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs invert fn to callable lambda
#define RUN_invert(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("invert-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_invert_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_invert(case_name, ...) \
RUN_invert_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define INVERT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, invert, case_name); \
    using namespace args; \
    auto result = RUN_invert(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("invert(case1)" * doctest::test_suite("array::invert"))
{
    INVERT_SUBCASE( case1,   a );
    INVERT_SUBCASE( case1, a_a );
    INVERT_SUBCASE( case1, a_f );
    INVERT_SUBCASE( case1, a_d );
    INVERT_SUBCASE( case1, a_h );
}