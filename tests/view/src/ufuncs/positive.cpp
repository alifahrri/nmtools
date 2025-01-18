#include "nmtools/array/ufuncs/positive.hpp"
#include "nmtools/testing/data/array/positive.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define POSITIVE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, positive, case_name); \
    using namespace args; \
    auto result = view::positive(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("positive(case1)" * doctest::test_suite("view::positive"))
{
    POSITIVE_SUBCASE( case1,   a);
    POSITIVE_SUBCASE( case1, a_a);
    POSITIVE_SUBCASE( case1, a_f);
    POSITIVE_SUBCASE( case1, a_d);
    POSITIVE_SUBCASE( case1, a_h);
}