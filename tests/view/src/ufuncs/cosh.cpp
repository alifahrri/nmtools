#include "nmtools/array/view/ufuncs/cosh.hpp"
#include "nmtools/testing/data/array/cosh.hpp"
#include "nmtools/testing/doctest.hpp"

// lower testing precision for cosh
#undef NMTOOLS_TESTING_OUTPUT_PRECISION
#define NMTOOLS_TESTING_OUTPUT_PRECISION 1e-5

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define COSH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, cosh, case_name); \
    using namespace args; \
    auto result = view::cosh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cosh(case1)" * doctest::test_suite("view::cosh"))
{
    COSH_SUBCASE( case1,   a);
    COSH_SUBCASE( case1, a_a);
    COSH_SUBCASE( case1, a_f);
    COSH_SUBCASE( case1, a_d);
    COSH_SUBCASE( case1, a_h);
}