#include "nmtools/array/view/ufuncs/greater.hpp"
#include "nmtools/testing/data/array/greater.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define GREATER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater, case_name); \
    using namespace args; \
    auto result = view::greater(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("greater(case1)" * doctest::test_suite("view::greater"))
{
    GREATER_SUBCASE( case1,   a,   b );
    GREATER_SUBCASE( case1, a_a, b_a );
    GREATER_SUBCASE( case1, a_f, b_f );
    GREATER_SUBCASE( case1, a_d, b_d );
    GREATER_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("greater(case2)" * doctest::test_suite("view::greater"))
{
    GREATER_SUBCASE( case2,   a, b );
    GREATER_SUBCASE( case2, a_a, b );
    GREATER_SUBCASE( case2, a_f, b );
    GREATER_SUBCASE( case2, a_d, b );
    GREATER_SUBCASE( case2, a_h, b );
}