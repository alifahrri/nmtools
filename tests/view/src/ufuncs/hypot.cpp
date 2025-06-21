#include "nmtools/array/ufuncs/hypot.hpp"
#include "nmtools/testing/data/array/hypot.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define HYPOT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, hypot, case_name); \
    using namespace args; \
    auto result = view::hypot(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("hypot(case1)" * doctest::test_suite("view::hypot"))
{
    HYPOT_SUBCASE( case1,   a,   b );
    HYPOT_SUBCASE( case1, a_a, b_a );
    HYPOT_SUBCASE( case1, a_f, b_f );
    HYPOT_SUBCASE( case1, a_d, b_d );
    HYPOT_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("hypot(case2)" * doctest::test_suite("view::hypot"))
{
    HYPOT_SUBCASE( case2,   a, b );
    HYPOT_SUBCASE( case2, a_a, b );
    HYPOT_SUBCASE( case2, a_f, b );
    HYPOT_SUBCASE( case2, a_d, b );
    HYPOT_SUBCASE( case2, a_h, b );
}