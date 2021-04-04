#include "nmtools/array/view/ufuncs/ldexp.hpp"
#include "nmtools/testing/data/array/ldexp.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::ldexp

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_ldexp_impl(...) \
nm::view::ldexp(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs ldexp fn to callable lambda
#define RUN_ldexp(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("ldexp-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_ldexp_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_ldexp(case_name, ...) \
RUN_ldexp_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LDEXP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, ldexp, case_name); \
    using namespace args; \
    auto result = RUN_ldexp(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("ldexp(case1)" * doctest::test_suite("view::ldexp"))
{
    LDEXP_SUBCASE( case1,   a,   b );
    LDEXP_SUBCASE( case1, a_a, b_a );
    LDEXP_SUBCASE( case1, a_v, b_v );
    LDEXP_SUBCASE( case1, a_f, b_f );
    LDEXP_SUBCASE( case1, a_d, b_d );
    LDEXP_SUBCASE( case1, a_h, b_h );
}