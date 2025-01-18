#include "nmtools/array/ufuncs/tan.hpp"
#include "nmtools/testing/data/array/tan.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define TAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tan, case_name); \
    using namespace args; \
    auto result = view::tan(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tan(case1)" * doctest::test_suite("view::tan"))
{
    TAN_SUBCASE( case1,   a);
    TAN_SUBCASE( case1, a_a);
    TAN_SUBCASE( case1, a_f);
    TAN_SUBCASE( case1, a_d);
    TAN_SUBCASE( case1, a_h);
}