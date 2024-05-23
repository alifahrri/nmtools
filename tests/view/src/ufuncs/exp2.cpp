#include "nmtools/array/view/ufuncs/exp2.hpp"
#include "nmtools/testing/data/array/exp2.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define EXP2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, exp2, case_name); \
    using namespace args; \
    auto result = view::exp2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("exp2(case1)" * doctest::test_suite("view::exp2"))
{
    EXP2_SUBCASE( case1,   a);
    EXP2_SUBCASE( case1, a_a);
    EXP2_SUBCASE( case1, a_f);
    EXP2_SUBCASE( case1, a_d);
    EXP2_SUBCASE( case1, a_h);
}