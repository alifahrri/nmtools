#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/testing/data/array/fabs.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define FABS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, fabs, case_name); \
    using namespace args; \
    auto result = view::fabs(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fabs(case1)" * doctest::test_suite("view::fabs"))
{
    FABS_SUBCASE( case1,   a);
    FABS_SUBCASE( case1, a_a);
    FABS_SUBCASE( case1, a_f);
    FABS_SUBCASE( case1, a_d);
    FABS_SUBCASE( case1, a_h);
}