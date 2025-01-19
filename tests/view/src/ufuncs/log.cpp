#include "nmtools/array/ufuncs/log.hpp"
#include "nmtools/testing/data/array/log.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define LOG_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, log, case_name); \
    using namespace args; \
    auto result = view::log(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("log(case1)" * doctest::test_suite("view::log"))
{
    LOG_SUBCASE( case1,   a);
    LOG_SUBCASE( case1, a_a);
    LOG_SUBCASE( case1, a_f);
    LOG_SUBCASE( case1, a_d);
    LOG_SUBCASE( case1, a_h);
}