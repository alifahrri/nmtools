#include "nmtools/array/view/ufuncs/less_equal.hpp"
#include "nmtools/testing/data/array/less_equal.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define LESS_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, less_equal, case_name); \
    using namespace args; \
    auto result = view::less_equal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("less_equal(case1)" * doctest::test_suite("view::less_equal"))
{
    LESS_EQUAL_SUBCASE( case1,   a,   b );
    LESS_EQUAL_SUBCASE( case1, a_a, b_a );
    LESS_EQUAL_SUBCASE( case1, a_f, b_f );
    LESS_EQUAL_SUBCASE( case1, a_d, b_d );
    LESS_EQUAL_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("less_equal(case1)" * doctest::test_suite("view::less_equal"))
{
    LESS_EQUAL_SUBCASE( case2,   a, b );
    LESS_EQUAL_SUBCASE( case2, a_a, b );
    LESS_EQUAL_SUBCASE( case2, a_f, b );
    LESS_EQUAL_SUBCASE( case2, a_d, b );
    LESS_EQUAL_SUBCASE( case2, a_h, b );
}