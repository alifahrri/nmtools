#include "nmtools/array/view/ufuncs/sinh.hpp"
#include "nmtools/testing/data/array/sinh.hpp"
#include "nmtools/testing/doctest.hpp"

// lower testing precision for sinh
#undef  NMTOOLS_TESTING_OUTPUT_PRECISION
#define NMTOOLS_TESTING_OUTPUT_PRECISION 7e-5

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define SINH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, sinh, case_name); \
    using namespace args; \
    auto result = view::sinh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sinh(case1)" * doctest::test_suite("view::sinh"))
{
    SINH_SUBCASE( case1,   a);
    SINH_SUBCASE( case1, a_a);
    SINH_SUBCASE( case1, a_f);
    SINH_SUBCASE( case1, a_d);
    SINH_SUBCASE( case1, a_h);
}