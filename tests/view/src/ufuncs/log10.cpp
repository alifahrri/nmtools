#include "nmtools/array/view/ufuncs/log10.hpp"
#include "nmtools/testing/data/array/log10.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define LOG10_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, log10, case_name); \
    using namespace args; \
    auto result = view::log10(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log10(case1)" * doctest::test_suite("view::log10"))
{
    LOG10_SUBCASE( case1,   a);
    LOG10_SUBCASE( case1, a_a);
    LOG10_SUBCASE( case1, a_f);
    LOG10_SUBCASE( case1, a_d);
    LOG10_SUBCASE( case1, a_h);
}