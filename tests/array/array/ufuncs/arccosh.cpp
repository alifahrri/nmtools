#include "nmtools/array/ufuncs/arccosh.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/arccosh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define ARCCOSH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arccosh, case_name); \
    using namespace args; \
    auto result = nm::arccosh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arccosh(case1)" * doctest::test_suite("array::arccosh"))
{
    ARCCOSH_SUBCASE( case1,   a);
    ARCCOSH_SUBCASE( case1, a_a);
    ARCCOSH_SUBCASE( case1, a_f);
    ARCCOSH_SUBCASE( case1, a_d);
    ARCCOSH_SUBCASE( case1, a_h);
}
