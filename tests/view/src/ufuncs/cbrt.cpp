#include "nmtools/array/ufuncs/cbrt.hpp"
#include "nmtools/testing/data/array/cbrt.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define CBRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, cbrt, case_name); \
    using namespace args; \
    auto result = view::cbrt(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cbrt(case1)" * doctest::test_suite("view::cbrt"))
{
    CBRT_SUBCASE( case1,   a);
    CBRT_SUBCASE( case1, a_a);
    CBRT_SUBCASE( case1, a_f);
    CBRT_SUBCASE( case1, a_d);
    CBRT_SUBCASE( case1, a_h);
}