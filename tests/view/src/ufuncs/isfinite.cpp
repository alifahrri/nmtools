#include "nmtools/array/view/ufuncs/isfinite.hpp"
#include "nmtools/testing/data/array/isfinite.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define ISFINITE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, isfinite, case_name); \
    using namespace args; \
    auto result = view::isfinite(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isfinite(case1)" * doctest::test_suite("view::isfinite"))
{
    ISFINITE_SUBCASE( case1,   a );
    ISFINITE_SUBCASE( case1, a_a );
    ISFINITE_SUBCASE( case1, a_f );
    ISFINITE_SUBCASE( case1, a_d );
    ISFINITE_SUBCASE( case1, a_h );
}