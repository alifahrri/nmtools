#include "nmtools/array/cumprod.hpp"
#include "nmtools/testing/data/array/multiply.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace array = nmtools;

#define CUMPROD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from accumulate_add since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_multiply, case_name); \
    using namespace args; \
    auto result = nmtools::cumprod(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cumprod(case1)" * doctest::test_suite("array::cumprod"))
{
    CUMPROD_SUBCASE( case1,   a, axis );
    CUMPROD_SUBCASE( case1, a_a, axis );
    CUMPROD_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMPROD_SUBCASE( case1, a_d, axis );
    CUMPROD_SUBCASE( case1, a_h, axis );
}

TEST_CASE("cumprod(case2)" * doctest::test_suite("array::cumprod"))
{
    CUMPROD_SUBCASE( case2,   a, axis );
    CUMPROD_SUBCASE( case2, a_a, axis );
    CUMPROD_SUBCASE( case2, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMPROD_SUBCASE( case2, a_d, axis );
    CUMPROD_SUBCASE( case2, a_h, axis );
}

TEST_CASE("cumprod(case3)" * doctest::test_suite("array::cumprod"))
{
    CUMPROD_SUBCASE( case3,   a, axis );
    CUMPROD_SUBCASE( case3, a_a, axis );
    CUMPROD_SUBCASE( case3, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // CUMPROD_SUBCASE( case3, a_d, axis );
    CUMPROD_SUBCASE( case3, a_h, axis );
}