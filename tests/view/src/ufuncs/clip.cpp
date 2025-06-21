#include "nmtools/array/ufuncs/clip.hpp"
#include "nmtools/testing/data/array/clip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nmtools::view;

#define CLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, clip, case_name); \
    using namespace args; \
    auto result = view::clip(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("clip(case1)" * doctest::test_suite("view::clip"))
{
    CLIP_SUBCASE( case1,   a,   amin,   amax);
    CLIP_SUBCASE( case1, a_a, amin_a, amax_a);
    CLIP_SUBCASE( case1, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case1, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case1, a_h, amin_h, amax_h);
}

TEST_CASE("clip(case2)" * doctest::test_suite("view::clip"))
{
    CLIP_SUBCASE( case2,   a,   amin,   amax);
    CLIP_SUBCASE( case2, a_a, amin_a, amax_a);
    CLIP_SUBCASE( case2, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case2, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case2, a_h, amin_h, amax_h);
}

TEST_CASE("clip(case3)" * doctest::test_suite("view::clip"))
{
    CLIP_SUBCASE( case3,   a,   amin, amax);
    CLIP_SUBCASE( case3, a_a, amin_a, amax);
    CLIP_SUBCASE( case3, a_f, amin_f, amax);
    CLIP_SUBCASE( case3, a_d, amin_d, amax);
    CLIP_SUBCASE( case3, a_h, amin_h, amax);
}