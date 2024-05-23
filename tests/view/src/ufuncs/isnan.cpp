#include "nmtools/array/view/ufuncs/isnan.hpp"
#include "nmtools/testing/data/array/isnan.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define ISNAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, isnan, case_name); \
    using namespace args; \
    auto result = view::isnan(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isnan(case1)" * doctest::test_suite("view::isnan"))
{
    ISNAN_SUBCASE( case1,   a );
    ISNAN_SUBCASE( case1, a_a );
    ISNAN_SUBCASE( case1, a_f );
    ISNAN_SUBCASE( case1, a_d );
    ISNAN_SUBCASE( case1, a_h );
}