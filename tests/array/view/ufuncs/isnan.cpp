#include "nmtools/array/view/ufuncs/isnan.hpp"
#include "nmtools/testing/data/array/isnan.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_isnan_impl(...) \
nm::view::isnan(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs isnan fn to callable lambda
#define RUN_isnan(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("isnan-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_isnan_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_isnan(case_name, ...) \
RUN_isnan_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ISNAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, isnan, case_name); \
    using namespace args; \
    auto result = RUN_isnan(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isnan(case1)" * doctest::test_suite("view::isnan"))
{
    ISNAN_SUBCASE( case1,   a );
    ISNAN_SUBCASE( case1, a_a );
    ISNAN_SUBCASE( case1, a_f );
    ISNAN_SUBCASE( case1, a_d );
    ISNAN_SUBCASE( case1, a_h );
}