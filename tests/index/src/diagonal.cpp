#include "nmtools/array/diagonal.hpp"
#include "nmtools/testing/data/index/diagonal.hpp"
#include "nmtools/testing/doctest.hpp"

#define SHAPE_DIAGONAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,shape_diagonal,case_name) \
    using namespace args; \
    auto result = nmtools::index::shape_diagonal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define INDEX_DIAGONAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,diagonal,case_name); \
    using namespace args; \
    auto result = nmtools::index::diagonal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_diagonal(case1a)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case1b)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case1c)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case1d)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2a)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2b)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2c)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2d)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2e)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2f)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2g)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2g, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2g, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2g, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2g, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2g, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2g, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2h)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2h, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2h, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2h, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2h, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2h, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2h, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3a)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3b)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3c)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3c, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3c, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3c, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3c, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3c, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3c, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3d)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3d, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3d, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3d, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3d, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3d, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3d, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3e)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3e, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3e, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3e, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3e, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3e, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3e, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3f)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3f, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3f, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3f, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3f, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3f, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3f, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("diagonal(case1a)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case1a, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1a, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1a, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1a, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1a, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case1b)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case1b, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1b, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1b, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1b, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case1b, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case2a)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case2a, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case2a, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case2a, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case2a, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case2a, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case3a)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case3a, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3a, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3a, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3a, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3a, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case3b)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case3b, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3b, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3b, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3b, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3b, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case3c)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case3c, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3c, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3c, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3c, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3c, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case3d)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case3d, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3d, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3d, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3d, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case3d, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case4a)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case4a, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4a, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4a, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4a, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4a, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case4b)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case4b, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4b, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4b, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4b, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4b, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case4c)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case4c, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4c, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4c, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4c, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4c, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case4d)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case4d, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4d, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4d, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4d, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case4d, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case5a)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case5a, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5a, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5a, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5a, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5a, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case5b)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case5b, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5b, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5b, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5b, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5b, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case5c)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case5c, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5c, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5c, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5c, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5c, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case5d)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case5d, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5d, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5d, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5d, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5d, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case5e)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case5e, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5e, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5e, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5e, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5e, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case5f)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case5f, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5f, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5f, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5f, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case5f, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case7a)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case7a, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7a, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7a, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7a, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7a, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case7b)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case7b, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7b, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7b, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7b, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7b, src_shape_v, indices_v, offset, axis1, axis2 );
}

TEST_CASE("diagonal(case7c)" * doctest::test_suite("index::diagonal"))
{
    INDEX_DIAGONAL_SUBCASE( case7c, src_shape, indices, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7c, src_shape_a, indices_a, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7c, src_shape_f, indices_f, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7c, src_shape_h, indices_h, offset, axis1, axis2 );
    INDEX_DIAGONAL_SUBCASE( case7c, src_shape_v, indices_v, offset, axis1, axis2 );
}