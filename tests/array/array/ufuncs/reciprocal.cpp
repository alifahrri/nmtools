#include "nmtools/array/ufuncs/reciprocal.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/reciprocal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define RECIPROCAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reciprocal, case_name); \
    using namespace args; \
    auto result = nm::reciprocal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reciprocal(case1)" * doctest::test_suite("array::reciprocal"))
{
    RECIPROCAL_SUBCASE( case1,   a);
    RECIPROCAL_SUBCASE( case1, a_a);
    RECIPROCAL_SUBCASE( case1, a_f);
    RECIPROCAL_SUBCASE( case1, a_d);
    RECIPROCAL_SUBCASE( case1, a_h);
}
