#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/testing/data/array/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define SQUARE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, square, case_name); \
    using namespace args; \
    auto result = view::square(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("square(case1)" * doctest::test_suite("view::square"))
{
    SQUARE_SUBCASE( case1,   a);
    SQUARE_SUBCASE( case1, a_a);
    SQUARE_SUBCASE( case1, a_f);
    SQUARE_SUBCASE( case1, a_d);
    SQUARE_SUBCASE( case1, a_h);
}