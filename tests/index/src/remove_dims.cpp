#include "nmtools/index/remove_dims.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"

#include "nmtools/testing/data/index/remove_dims.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define REMOVE_DIMS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, remove_dims, case_name) \
    using namespace args; \
    auto result = ::nmtools::index::remove_dims(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("remove_dims(case1)" * doctest::test_suite("index::remove_dims"))
{
    REMOVE_DIMS_SUBCASE( case1, shape, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_a, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_v, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_f, axis );
    REMOVE_DIMS_SUBCASE( case1, shape_h, axis );
}

TEST_CASE("remove_dims(case2)" * doctest::test_suite("index::remove_dims"))
{
    REMOVE_DIMS_SUBCASE( case2, shape, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_a, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_v, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_f, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case2, shape_h, axis, keepdims );
}

TEST_CASE("remove_dims(case3)" * doctest::test_suite("index::remove_dims"))
{
    REMOVE_DIMS_SUBCASE( case3, shape, axis );
    REMOVE_DIMS_SUBCASE( case3, shape_a, axis );
    REMOVE_DIMS_SUBCASE( case3, shape_v, axis );
    REMOVE_DIMS_SUBCASE( case3, shape_f, axis );
    REMOVE_DIMS_SUBCASE( case3, shape_h, axis );
}

TEST_CASE("remove_dims(case4)" * doctest::test_suite("index::remove_dims"))
{
    REMOVE_DIMS_SUBCASE( case4, shape, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case4, shape_a, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case4, shape_v, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case4, shape_f, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case4, shape_h, axis, keepdims );
}

TEST_CASE("remove_dims(case5)" * doctest::test_suite("index::remove_dims"))
{
    REMOVE_DIMS_SUBCASE( case5, shape, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case5, shape_a, axis, keepdims );
    // REMOVE_DIMS_SUBCASE( case5, shape_v, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case5, shape_f, axis, keepdims );
    REMOVE_DIMS_SUBCASE( case5, shape_h, axis, keepdims );
}