#include "nmtools/array/ufuncs/trunc.hpp"
#include "nmtools/testing/data/array/trunc.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define TRUNC_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, trunc, case_name); \
    using namespace args; \
    auto result = nm::trunc(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("trunc(case1)" * doctest::test_suite("array::trunc"))
{
    TRUNC_SUBCASE( case1,   a);
    TRUNC_SUBCASE( case1, a_a);
    TRUNC_SUBCASE( case1, a_f);
    TRUNC_SUBCASE( case1, a_d);
    TRUNC_SUBCASE( case1, a_h);
}