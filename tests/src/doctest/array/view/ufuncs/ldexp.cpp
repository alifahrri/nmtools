#include "nmtools/array/view/ufuncs/ldexp.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::ldexp

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, ldexp)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        int b[3] = {0,1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::ldexp(0.f,0.f),std::ldexp(1.f,1.f),std::ldexp(2.f,2.f)},
            {std::ldexp(3.f,0.f),std::ldexp(4.f,1.f),std::ldexp(5.f,2.f)},
            {std::ldexp(6.f,0.f),std::ldexp(7.f,1.f),std::ldexp(8.f,2.f)},
        };
    }
}

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