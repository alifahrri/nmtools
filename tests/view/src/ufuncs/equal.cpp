#include "nmtools/array/ufuncs/equal.hpp"
#include "nmtools/testing/data/array/equal.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, equal, case_name); \
    using namespace args; \
    auto result = view::equal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("equal(case1)" * doctest::test_suite("view::equal"))
{
    EQUAL_SUBCASE( case1,   a,   b );
    EQUAL_SUBCASE( case1, a_a, b_a );
    EQUAL_SUBCASE( case1, a_f, b_f );
    EQUAL_SUBCASE( case1, a_d, b_d );
    EQUAL_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("equal(case2)" * doctest::test_suite("view::equal"))
{
    EQUAL_SUBCASE( case2,   a, b );
    EQUAL_SUBCASE( case2, a_a, b );
    EQUAL_SUBCASE( case2, a_f, b );
    EQUAL_SUBCASE( case2, a_d, b );
    EQUAL_SUBCASE( case2, a_h, b );
}