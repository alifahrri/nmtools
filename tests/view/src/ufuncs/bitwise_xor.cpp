#include "nmtools/array/view/ufuncs/bitwise_xor.hpp"
#include "nmtools/testing/data/array/bitwise_xor.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define BITWISE_XOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, bitwise_xor, case_name); \
    using namespace args; \
    auto result = view::bitwise_xor(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("bitwise_xor(case1)" * doctest::test_suite("view::bitwise_xor"))
{
    BITWISE_XOR_SUBCASE( case1,   a,   b );
    BITWISE_XOR_SUBCASE( case1, a_a, b_a );
    BITWISE_XOR_SUBCASE( case1, a_f, b_f );
    BITWISE_XOR_SUBCASE( case1, a_d, b_d );
    BITWISE_XOR_SUBCASE( case1, a_h, b_h );
}

TEST_CASE("bitwise_xor(case2)" * doctest::test_suite("view::bitwise_xor"))
{
    BITWISE_XOR_SUBCASE( case2,   a, b );
    BITWISE_XOR_SUBCASE( case2, a_a, b );
    BITWISE_XOR_SUBCASE( case2, a_f, b );
    BITWISE_XOR_SUBCASE( case2, a_d, b );
    BITWISE_XOR_SUBCASE( case2, a_h, b );
}