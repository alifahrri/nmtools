#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/testing/data/array/divide.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define DIVIDE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, divide, case_name); \
    using namespace args; \
    auto result = view::divide(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("divide(case1)" * doctest::test_suite("view::divide"))
{
    DIVIDE_SUBCASE( case1,   a,   b );
    DIVIDE_SUBCASE( case1, a_a, b_a );
    DIVIDE_SUBCASE( case1, a_f, b_f );
    DIVIDE_SUBCASE( case1, a_d, b_d );
    DIVIDE_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("divide(case2)" * doctest::test_suite("view::divide"))
{
    DIVIDE_SUBCASE( case2,   a, b );
    DIVIDE_SUBCASE( case2, a_a, b );
    DIVIDE_SUBCASE( case2, a_f, b );
    DIVIDE_SUBCASE( case2, a_d, b );
    DIVIDE_SUBCASE( case2, a_h, b );
}