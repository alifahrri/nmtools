#include "nmtools/array/ufuncs/arctan2.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/arctan2.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define ARCTAN2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arctan2, case_name); \
    using namespace args; \
    auto result = nm::arctan2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctan2(case1)" * doctest::test_suite("array::arctan2"))
{
    ARCTAN2_SUBCASE( case1,   a,   b );
    ARCTAN2_SUBCASE( case1, a_a, b_a );
    ARCTAN2_SUBCASE( case1, a_f, b_f );
    ARCTAN2_SUBCASE( case1, a_d, b_d );
    ARCTAN2_SUBCASE( case1, a_h, b_h );
}
