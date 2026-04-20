#include "nmtools/array/cumsum.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace array = nmtools;

#define CUMSUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from accumulate_add since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = nmtools::cumsum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cumsum(case1)" * doctest::test_suite("array::cumsum"))
{
    CUMSUM_SUBCASE( case1,   a, axis );
    CUMSUM_SUBCASE( case1, a_a, axis );
    CUMSUM_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMSUM_SUBCASE( case1, a_d, axis );
    CUMSUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("cumsum(case2)" * doctest::test_suite("array::cumsum"))
{
    CUMSUM_SUBCASE( case2,   a, axis );
    CUMSUM_SUBCASE( case2, a_a, axis );
    CUMSUM_SUBCASE( case2, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMSUM_SUBCASE( case2, a_d, axis );
    CUMSUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("cumsum(case3)" * doctest::test_suite("array::cumsum"))
{
    CUMSUM_SUBCASE( case3,   a, axis );
    CUMSUM_SUBCASE( case3, a_a, axis );
    CUMSUM_SUBCASE( case3, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMSUM_SUBCASE( case3, a_d, axis );
    CUMSUM_SUBCASE( case3, a_h, axis );
}