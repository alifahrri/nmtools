#include "nmtools/array/ufuncs/rint.hpp"
#include "nmtools/testing/data/array/rint.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RINT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, rint, case_name); \
    using namespace args; \
    auto result = view::rint(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("rint(case1)" * doctest::test_suite("view::rint"))
{
    RINT_SUBCASE( case1,   a);
    RINT_SUBCASE( case1, a_a);
    RINT_SUBCASE( case1, a_f);
    RINT_SUBCASE( case1, a_d);
    RINT_SUBCASE( case1, a_h);
}