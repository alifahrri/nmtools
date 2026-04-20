#include "nmtools/array/ufuncs/sin.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/sin.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define SIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sin, case_name); \
    using namespace args; \
    auto result = nm::sin(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sin(case1)" * doctest::test_suite("array::sin"))
{
    SIN_SUBCASE( case1,   a);
    SIN_SUBCASE( case1, a_a);
    SIN_SUBCASE( case1, a_f);
    SIN_SUBCASE( case1, a_d);
    SIN_SUBCASE( case1, a_h);
}
