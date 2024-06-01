#include "nmtools/array/view/ufuncs/logical_not.hpp"
#include "nmtools/testing/data/array/logical_not.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define LOGICAL_NOT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, logical_not, case_name); \
    using namespace args; \
    auto result = view::logical_not( __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_not(case1)" * doctest::test_suite("view::logical_not"))
{
    LOGICAL_NOT_SUBCASE( case1,   a );
    LOGICAL_NOT_SUBCASE( case1, a_a );
    LOGICAL_NOT_SUBCASE( case1, a_f );
    LOGICAL_NOT_SUBCASE( case1, a_d );
    LOGICAL_NOT_SUBCASE( case1, a_h );
}