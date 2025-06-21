#include "nmtools/array/ufuncs/invert.hpp"
#include "nmtools/testing/data/array/invert.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define INVERT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, invert, case_name); \
    using namespace args; \
    auto result = view::invert(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("invert(case1)" * doctest::test_suite("view::invert"))
{
    INVERT_SUBCASE( case1,   a );
    INVERT_SUBCASE( case1, a_a );
    INVERT_SUBCASE( case1, a_f );
    INVERT_SUBCASE( case1, a_d );
    INVERT_SUBCASE( case1, a_h );
}