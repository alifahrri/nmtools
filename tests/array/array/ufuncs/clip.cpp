#include "nmtools/array/array/ufuncs/clip.hpp"
#include "nmtools/testing/data/array/clip.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_clip_impl(...) \
nm::array::clip(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs clip fn to callable lambda
#define RUN_clip(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("clip-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_clip_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_clip(case_name, ...) \
RUN_clip_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, clip, case_name); \
    using namespace args; \
    auto result = RUN_clip(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("clip(case1)" * doctest::test_suite("array::clip"))
{
    CLIP_SUBCASE( case1,   a,   amin,   amax);
    CLIP_SUBCASE( case1, a_a, amin_a, amax_a);
    // TODO: remove support for nested vector as ndarray
    // CLIP_SUBCASE( case1, a_v, amin_v, amax_v);
    CLIP_SUBCASE( case1, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case1, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case1, a_h, amin_h, amax_h);
}

TEST_CASE("clip(case2)" * doctest::test_suite("array::clip"))
{
    CLIP_SUBCASE( case2,   a,   amin,   amax);
    CLIP_SUBCASE( case2, a_a, amin_a, amax_a);
    // TODO: remove support for nested vector as ndarray
    // CLIP_SUBCASE( case2, a_v, amin_v, amax_v);
    CLIP_SUBCASE( case2, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case2, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case2, a_h, amin_h, amax_h);
}

TEST_CASE("clip(case3)" * doctest::test_suite("array::clip"))
{
    CLIP_SUBCASE( case3,   a,   amin, amax);
    CLIP_SUBCASE( case3, a_a, amin_a, amax);
    // TODO: remove support for nested vector as ndarray
    // CLIP_SUBCASE( case3, a_v, amin_v, amax);
    CLIP_SUBCASE( case3, a_f, amin_f, amax);
    CLIP_SUBCASE( case3, a_d, amin_d, amax);
    CLIP_SUBCASE( case3, a_h, amin_h, amax);
}