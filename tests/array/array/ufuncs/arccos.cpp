#include "nmtools/array/ufuncs/arccos.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/arccos.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define ARCCOS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arccos, case_name); \
    using namespace args; \
    auto result = nm::arccos(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arccos(case1)" * doctest::test_suite("array::arccos"))
{
    ARCCOS_SUBCASE( case1,   a);
    ARCCOS_SUBCASE( case1, a_a);
    ARCCOS_SUBCASE( case1, a_f);
    ARCCOS_SUBCASE( case1, a_d);
    ARCCOS_SUBCASE( case1, a_h);
}
