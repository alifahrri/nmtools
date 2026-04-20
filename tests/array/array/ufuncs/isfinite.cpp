#include "nmtools/array/ufuncs/isfinite.hpp"
#include "nmtools/testing/data/array/isfinite.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define ISFINITE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, isfinite, case_name); \
    using namespace args; \
    auto result = nm::isfinite(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isfinite(case1)" * doctest::test_suite("array::isfinite"))
{
    ISFINITE_SUBCASE( case1,   a );
    ISFINITE_SUBCASE( case1, a_a );
    ISFINITE_SUBCASE( case1, a_f );
    // TODO: drop support for vector of bool
    #if 0
    ISFINITE_SUBCASE( case1, a_d );
    ISFINITE_SUBCASE( case1, a_h );
    #endif
}