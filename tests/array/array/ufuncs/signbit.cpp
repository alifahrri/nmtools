#include "nmtools/array/ufuncs/signbit.hpp"
#include "nmtools/testing/data/array/signbit.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define SIGNBIT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, signbit, case_name); \
    using namespace args; \
    auto result = nm::signbit(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("signbit(case1)" * doctest::test_suite("array::signbit"))
{
    SIGNBIT_SUBCASE( case1,   a );
    SIGNBIT_SUBCASE( case1, a_a );
    SIGNBIT_SUBCASE( case1, a_f );
    // TODO: drop support for vector of bool
    #if 0
    SIGNBIT_SUBCASE( case1, a_d );
    SIGNBIT_SUBCASE( case1, a_h );
    #endif
}