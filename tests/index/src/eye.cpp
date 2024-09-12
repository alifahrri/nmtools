#include "nmtools/array/view/eye.hpp"
#include "nmtools/testing/data/index/eye.hpp"
#include "nmtools/testing/doctest.hpp"

#define EYE_SUBCASE( case_name, ... ) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,eye,case_name); \
    using namespace args; \
    auto result = nmtools::index::eye(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("eye(case4a)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4a, dst_shape, indices, k );
    EYE_SUBCASE( case4a, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4a, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4a, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4a, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4b)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4b, dst_shape, indices, k );
    EYE_SUBCASE( case4b, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4b, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4b, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4b, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4c)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4c, dst_shape, indices, k );
    EYE_SUBCASE( case4c, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4c, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4c, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4c, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4d)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4d, dst_shape, indices, k );
    EYE_SUBCASE( case4d, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4d, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4d, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4d, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4e)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4e, dst_shape, indices, k );
    EYE_SUBCASE( case4e, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4e, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4e, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4e, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4f)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4f, dst_shape, indices, k );
    EYE_SUBCASE( case4f, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4f, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4f, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4f, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4g)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4g, dst_shape, indices, k );
    EYE_SUBCASE( case4g, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4g, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4g, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4g, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4h)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4h, dst_shape, indices, k );
    EYE_SUBCASE( case4h, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4h, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4h, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4h, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4i)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4i, dst_shape, indices, k );
    EYE_SUBCASE( case4i, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4i, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4i, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4i, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4j)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4j, dst_shape, indices, k );
    EYE_SUBCASE( case4j, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4j, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4j, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4j, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4k)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4k, dst_shape, indices, k );
    EYE_SUBCASE( case4k, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4k, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4k, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4k, dst_shape_h, indices_h, k );
}

TEST_CASE("eye(case4l)" * doctest::test_suite("index::eye"))
{
    EYE_SUBCASE( case4l, dst_shape, indices, k );
    EYE_SUBCASE( case4l, dst_shape_a, indices_a, k );
    EYE_SUBCASE( case4l, dst_shape_v, indices_v, k );
    EYE_SUBCASE( case4l, dst_shape_f, indices_f, k );
    EYE_SUBCASE( case4l, dst_shape_h, indices_h, k );
}