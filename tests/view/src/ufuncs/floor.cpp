#include "nmtools/array/ufuncs/floor.hpp"
#include "nmtools/testing/data/array/floor.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define FLOOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, floor, case_name); \
    using namespace args; \
    auto result = view::floor(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("floor(case1)" * doctest::test_suite("view::floor"))
{
    FLOOR_SUBCASE( case1,   a);
    FLOOR_SUBCASE( case1, a_a);
    FLOOR_SUBCASE( case1, a_f);
    FLOOR_SUBCASE( case1, a_d);
    FLOOR_SUBCASE( case1, a_h);
}