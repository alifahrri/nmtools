#include "nmtools/array/ufuncs/trunc.hpp"
#include "nmtools/testing/data/array/trunc.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define TRUNC_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, trunc, case_name); \
    using namespace args; \
    auto result = view::trunc(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("trunc(case1)" * doctest::test_suite("view::trunc"))
{
    TRUNC_SUBCASE( case1,   a);
    TRUNC_SUBCASE( case1, a_a);
    TRUNC_SUBCASE( case1, a_f);
    TRUNC_SUBCASE( case1, a_d);
    TRUNC_SUBCASE( case1, a_h);
}