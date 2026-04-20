#include "nmtools/array/ufuncs/isinf.hpp"
#include "nmtools/testing/data/array/isinf.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define ISINF_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, isinf, case_name); \
    using namespace args; \
    auto result = nm::isinf(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("isinf(case1)" * doctest::test_suite("array::isinf"))
{
    ISINF_SUBCASE( case1,   a );
    ISINF_SUBCASE( case1, a_a );
    ISINF_SUBCASE( case1, a_f );
    // TODO: drop support for vector of bool
    #if 0
    ISINF_SUBCASE( case1, a_d );
    ISINF_SUBCASE( case1, a_h );
    #endif
}