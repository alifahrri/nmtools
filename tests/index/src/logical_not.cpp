#include "nmtools/array/index/logical_not.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/index/logical_not.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define LOGICAL_NOT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(logical_not, case_name); \
    using namespace args; \
    auto result = ::nmtools::index::logical_not(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES(result, expect::x, __VA_ARGS__); \
}

TEST_CASE("logical_not(case1)" * doctest::test_suite("index::logical_not"))
{
    LOGICAL_NOT_SUBCASE(case1, x);
    LOGICAL_NOT_SUBCASE(case1, x_a);
    LOGICAL_NOT_SUBCASE(case1, x_v);
    LOGICAL_NOT_SUBCASE(case1, x_f);
    LOGICAL_NOT_SUBCASE(case1, x_h);

    LOGICAL_NOT_SUBCASE(case1, m_x_a);
    LOGICAL_NOT_SUBCASE(case1, m_x_v);
    LOGICAL_NOT_SUBCASE(case1, m_x_f);
    LOGICAL_NOT_SUBCASE(case1, m_x_h);
}