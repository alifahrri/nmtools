#include "nmtools/array/ufuncs/arcsin.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/arcsin.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define ARCSIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, arcsin, case_name); \
    using namespace args; \
    auto result = nm::arcsin(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("arcsin(case1)" * doctest::test_suite("array::arcsin"))
{
    ARCSIN_SUBCASE( case1,   a);
    ARCSIN_SUBCASE( case1, a_a);
    ARCSIN_SUBCASE( case1, a_f);
    ARCSIN_SUBCASE( case1, a_d);
    ARCSIN_SUBCASE( case1, a_h);
}
