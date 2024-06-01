#include "nmtools/array/view/ufuncs/not_equal.hpp"
#include "nmtools/testing/data/array/not_equal.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define NOT_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, not_equal, case_name); \
    using namespace args; \
    auto result = view::not_equal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("not_equal(case1)" * doctest::test_suite("view::not_equal"))
{
    NOT_EQUAL_SUBCASE( case1,   a,   b );
    NOT_EQUAL_SUBCASE( case1, a_a, b_a );
    NOT_EQUAL_SUBCASE( case1, a_f, b_f );
    NOT_EQUAL_SUBCASE( case1, a_d, b_d );
    NOT_EQUAL_SUBCASE( case1, a_h, b_h );
}


TEST_CASE("not_equal(case2)" * doctest::test_suite("view::not_equal"))
{
    NOT_EQUAL_SUBCASE( case2,   a, b );
    NOT_EQUAL_SUBCASE( case2, a_a, b );
    NOT_EQUAL_SUBCASE( case2, a_f, b );
    NOT_EQUAL_SUBCASE( case2, a_d, b );
    NOT_EQUAL_SUBCASE( case2, a_h, b );
}