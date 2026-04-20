#include "nmtools/array/ufuncs/arctan.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/arctan.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define ARCTAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arctan, case_name); \
    using namespace args; \
    auto result = nm::arctan(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arctan(case1)" * doctest::test_suite("array::arctan"))
{
    ARCTAN_SUBCASE( case1,   a);
    ARCTAN_SUBCASE( case1, a_a);
    ARCTAN_SUBCASE( case1, a_f);
    ARCTAN_SUBCASE( case1, a_d);
    ARCTAN_SUBCASE( case1, a_h);
}
