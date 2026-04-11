#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/exp.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define EXP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, exp, case_name); \
    using namespace args; \
    auto result = nm::exp(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("exp(case1)" * doctest::test_suite("array::exp"))
{
    EXP_SUBCASE( case1,   a);
    EXP_SUBCASE( case1, a_a);
    EXP_SUBCASE( case1, a_f);
    EXP_SUBCASE( case1, a_d);
    EXP_SUBCASE( case1, a_h);
}
