#include "nmtools/array/ufuncs/negative.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/negative.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define NEGATIVE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, negative, case_name); \
    using namespace args; \
    auto result = nm::negative(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("negative(case1)" * doctest::test_suite("array::negative"))
{
    NEGATIVE_SUBCASE( case1,   a);
    NEGATIVE_SUBCASE( case1, a_a);
    NEGATIVE_SUBCASE( case1, a_f);
    NEGATIVE_SUBCASE( case1, a_d);
    NEGATIVE_SUBCASE( case1, a_h);
}
