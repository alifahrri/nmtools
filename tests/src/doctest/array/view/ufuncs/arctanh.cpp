#include "nmtools/array/view/ufuncs/arctanh.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, arctanh)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {.1f,.1f,.2f},
            {.3f,.4f,.5f},
            {.6f,.7f,.8f},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::atanh(.1f),std::atanh(.1f),std::atanh(.2f)},
            {std::atanh(.3f),std::atanh(.4f),std::atanh(.5f)},
            {std::atanh(.6f),std::atanh(.7f),std::atanh(.8f)},
        };
    }
}

#define RUN_arctanh_impl(...) \
nm::view::arctanh(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs arctanh fn to callable lambda
#define RUN_arctanh(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("arctanh-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_arctanh_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_arctanh(case_name, ...) \
RUN_arctanh_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ARCTANH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, arctanh, case_name); \
    using namespace args; \
    auto result = RUN_arctanh(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctanh(case1)" * doctest::test_suite("view::arctanh"))
{
    ARCTANH_SUBCASE( case1,   a);
    ARCTANH_SUBCASE( case1, a_a);
    ARCTANH_SUBCASE( case1, a_v);
    ARCTANH_SUBCASE( case1, a_f);
    ARCTANH_SUBCASE( case1, a_d);
    ARCTANH_SUBCASE( case1, a_h);
}