#include "nmtools/array/view/ufuncs/fmin.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

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

NMTOOLS_TESTING_DECLARE_CASE(view, fmin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        float b[3] = {0.F,1,NAN};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::fmin(0.f,0.F),std::fmin(1.f,1.f),std::fmin(2.f,NAN)},
            {std::fmin(3.f,0.F),std::fmin(4.f,1.f),std::fmin(5.f,NAN)},
            {std::fmin(6.f,0.F),std::fmin(7.f,1.f),std::fmin(8.f,NAN)},
        };
    }
}

#define RUN_fmin_impl(...) \
nm::view::fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmin fn to callable lambda
#define RUN_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmin(case_name, ...) \
RUN_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, fmin, case_name); \
    using namespace args; \
    auto result = RUN_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmin(case1)" * doctest::test_suite("view::fmin"))
{
    FMIN_SUBCASE( case1,   a,   b );
    FMIN_SUBCASE( case1, a_a, b_a );
    FMIN_SUBCASE( case1, a_v, b_v );
    FMIN_SUBCASE( case1, a_f, b_f );
    FMIN_SUBCASE( case1, a_d, b_d );
    FMIN_SUBCASE( case1, a_h, b_h );
}