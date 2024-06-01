#include "nmtools/array/view/ufuncs/bitwise_or.hpp"
#include "nmtools/testing/data/array/bitwise_or.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define BITWISE_OR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, bitwise_or, case_name); \
    using namespace args; \
    auto result = view::bitwise_or(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("bitwise_or(case1)" * doctest::test_suite("view::bitwise_or"))
{
    BITWISE_OR_SUBCASE( case1,   a,   b );
    BITWISE_OR_SUBCASE( case1, a_a, b_a );
    BITWISE_OR_SUBCASE( case1, a_f, b_f );
    BITWISE_OR_SUBCASE( case1, a_d, b_d );
    BITWISE_OR_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("bitwise_or(case2)" * doctest::test_suite("view::bitwise_or"))
{
    BITWISE_OR_SUBCASE( case2,   a, b );
    BITWISE_OR_SUBCASE( case2, a_a, b );
    BITWISE_OR_SUBCASE( case2, a_f, b );
    BITWISE_OR_SUBCASE( case2, a_d, b );
    BITWISE_OR_SUBCASE( case2, a_h, b );
}