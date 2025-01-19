#include "nmtools/array/ufuncs/ceil.hpp"
#include "nmtools/testing/data/array/ceil.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define CEIL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, ceil, case_name); \
    using namespace args; \
    auto result = view::ceil(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("ceil(case1)" * doctest::test_suite("view::ceil"))
{
    CEIL_SUBCASE( case1,   a);
    CEIL_SUBCASE( case1, a_a);
    CEIL_SUBCASE( case1, a_f);
    CEIL_SUBCASE( case1, a_d);
    CEIL_SUBCASE( case1, a_h);
}