#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/tanh.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;

#define TANH_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, tanh, case_name); \
    using namespace args; \
    auto result = nm::tanh(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tanh(case1)" * doctest::test_suite("array::tanh"))
{
    TANH_SUBCASE( case1,   a);
    TANH_SUBCASE( case1, a_a);
    TANH_SUBCASE( case1, a_f);
    TANH_SUBCASE( case1, a_d);
    TANH_SUBCASE( case1, a_h);
}
