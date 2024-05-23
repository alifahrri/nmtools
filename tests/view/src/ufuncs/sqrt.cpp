#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/testing/data/array/sqrt.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define SQRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, sqrt, case_name); \
    using namespace args; \
    auto result = view::sqrt(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sqrt(case1)" * doctest::test_suite("view::sqrt"))
{
    SQRT_SUBCASE( case1,   a);
    SQRT_SUBCASE( case1, a_a);
    SQRT_SUBCASE( case1, a_f);
    SQRT_SUBCASE( case1, a_d);
    SQRT_SUBCASE( case1, a_h);
}