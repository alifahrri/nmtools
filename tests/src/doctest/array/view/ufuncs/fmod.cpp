#include "nmtools/array/view/ufuncs/fmod.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, fmod)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {1.0,2.1,3.2},
            {1.3,2.4,3.5},
            {1.6,2.7,3.8},
        };
        float b[3] = {1.f,2.f,3.f};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::fmod(1.0f,1.f),std::fmod(2.1f,2.f),std::fmod(3.2f,3.f)},
            {std::fmod(1.3f,1.f),std::fmod(2.4f,2.f),std::fmod(3.5f,3.f)},
            {std::fmod(1.6f,1.f),std::fmod(2.7f,2.f),std::fmod(3.8f,3.f)},
        };
    }
}

#define RUN_fmod_impl(...) \
nm::view::fmod(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmod fn to callable lambda
#define RUN_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmod(case_name, ...) \
RUN_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, fmod, case_name); \
    using namespace args; \
    auto result = RUN_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmod(case1)" * doctest::test_suite("view::fmod"))
{
    FMOD_SUBCASE( case1,   a,   b );
    FMOD_SUBCASE( case1, a_a, b_a );
    FMOD_SUBCASE( case1, a_v, b_v );
    FMOD_SUBCASE( case1, a_f, b_f );
    FMOD_SUBCASE( case1, a_d, b_d );
    FMOD_SUBCASE( case1, a_h, b_h );
}