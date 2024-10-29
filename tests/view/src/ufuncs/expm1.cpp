#include "nmtools/array/view/ufuncs/expm1.hpp"
#include "nmtools/testing/data/array/expm1.hpp"
#include "nmtools/testing/doctest.hpp"

// lower testing precision for expm1
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION 1e-5

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define EXPM1_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, expm1, case_name); \
    using namespace args; \
    auto result = view::expm1(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("expm1(case1)" * doctest::test_suite("view::expm1"))
{
    EXPM1_SUBCASE( case1,   a);
    EXPM1_SUBCASE( case1, a_a);
    EXPM1_SUBCASE( case1, a_f);
    EXPM1_SUBCASE( case1, a_d);
    EXPM1_SUBCASE( case1, a_h);
}