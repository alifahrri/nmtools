#include "nmtools/array/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/data/index/matmul.hpp"
#include "nmtools/testing/data/index/split.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/utility/apply_isequal.hpp"

#define SHAPE_MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, shape_matmul, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_matmul(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_matmul(case1)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case1, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case1, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_a, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_v, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_f, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_h, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_ct, rshape_cl );

    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_a );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_v );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_f );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_h );;
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case1, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case2)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case2, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case2, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case2, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case2, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case2, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case2, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case2, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case2, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case3)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case3, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case3, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case3, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case3, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case3, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case3, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case3, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case3, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case4)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case4, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case4, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case4, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case4, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case4, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case4, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case4, lshape_ct, rshape_ct );
    SHAPE_MATMUL_SUBCASE( case4, lshape_cl, rshape_cl );
}

TEST_CASE("shape_matmul(case5)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case5, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case5, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case5, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case5, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case5, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case5, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case5, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case5, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case6)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case6, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case6, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case6, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case6, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case6, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case6, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case6, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case6, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case7)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case7, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case7, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case7, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case7, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case7, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case7, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case7, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case7, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case8)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case8, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case8, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case8, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case8, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case8, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case8, lshape_d, rshape_d );

    SHAPE_MATMUL_SUBCASE( case8, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case8, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case9)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case9, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case9, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case9, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case9, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case9, lshape_h, rshape_h );
    // SHAPE_MATMUL_SUBCASE( case9, lshape_d, rshape_d );

    // SHAPE_MATMUL_SUBCASE( case9, lshape_cl, rshape_cl );
    // SHAPE_MATMUL_SUBCASE( case9, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case10)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case10, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case10, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case10, lshape_v, rshape_v );
    SHAPE_MATMUL_SUBCASE( case10, lshape_f, rshape_f );
    SHAPE_MATMUL_SUBCASE( case10, lshape_h, rshape_h );

    SHAPE_MATMUL_SUBCASE( case10, lshape_cl, rshape_cl );
    SHAPE_MATMUL_SUBCASE( case10, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case11)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case11, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case11, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case11, lshape_f, rshape_f );

    SHAPE_MATMUL_SUBCASE( case11, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case12)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case12, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case12, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case12, lshape_f, rshape_f );

    SHAPE_MATMUL_SUBCASE( case12, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case13)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case13, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case13, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case13, lshape_f, rshape_f );

    SHAPE_MATMUL_SUBCASE( case13, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case14)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case14, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case14, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case14, lshape_f, rshape_f );

    SHAPE_MATMUL_SUBCASE( case14, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case15)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case15, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case15, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case15, lshape_f, rshape_f );

    SHAPE_MATMUL_SUBCASE( case15, lshape_ct, rshape_ct );
}

TEST_CASE("shape_matmul(case16)" * doctest::test_suite("index::shape_matmul"))
{
    SHAPE_MATMUL_SUBCASE( case16, lshape, rshape );
    SHAPE_MATMUL_SUBCASE( case16, lshape_a, rshape_a );
    SHAPE_MATMUL_SUBCASE( case16, lshape_f, rshape_f );

    SHAPE_MATMUL_SUBCASE( case16, lshape_ct, rshape_ct );
}

#define INDEX_MATMUL_SUBCASE(case_name, res_left, res_right, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, matmul, case_name); \
    using namespace args; \
    auto result = nmtools::index::matmul(__VA_ARGS__); \
    auto left   = nmtools::get<0>(result); \
    auto right  = nmtools::get<1>(result); \
    NMTOOLS_ASSERT_APPLY_EQUAL( left, expect::res_left ); \
    NMTOOLS_ASSERT_APPLY_EQUAL( right, expect::res_right ); \
}

// TODO: check value
// NOTE: isequal can't handle list with either
#define DYNAMIC_INDEX_MATMUL_SUBCASE(case_name, res_left, res_right, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, matmul, case_name); \
    using namespace args; \
    auto result = nmtools::index::matmul(__VA_ARGS__); \
    auto left   = nmtools::get<0>(result); \
    auto right  = nmtools::get<1>(result); \
    NMTOOLS_ASSERT_EQUAL( nmtools::dim(left), nmtools::dim(expect::res_left) ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::dim(right), nmtools::dim(expect::res_right) ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::len(left), nmtools::len(expect::res_left) ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::len(right), nmtools::len(expect::res_right) ); \
    NMTOOLS_ASSERT_APPLY_EQUAL( right, expect::res_right ); \
    NMTOOLS_ASSERT_APPLY_EQUAL( left, expect::res_left ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("index::matmul"))
{
    INDEX_MATMUL_SUBCASE(case1, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case1, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case1, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case1, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    // NOTE: isequal can't handle list with either
    DYNAMIC_INDEX_MATMUL_SUBCASE(case1, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case2)" * doctest::test_suite("index::matmul"))
{
    INDEX_MATMUL_SUBCASE(case2, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case2, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case2, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case2, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case2, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case3)" * doctest::test_suite("index::matmul"))
{
    INDEX_MATMUL_SUBCASE(case3, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case3, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case3, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case3, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case3, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case4)" * doctest::test_suite("index::matmul"))
{
    INDEX_MATMUL_SUBCASE(case4, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case4, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case4, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case4, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case4, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case5)" * doctest::test_suite("index::matmul"))
{
    INDEX_MATMUL_SUBCASE(case5, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case5, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case5, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case5, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case5, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}

TEST_CASE("matmul(case6)" * doctest::test_suite("index::matmul"))
{
    INDEX_MATMUL_SUBCASE(case6, left, right, indices, lshape, rshape, shape);
    INDEX_MATMUL_SUBCASE(case6, left, right, indices_a, lshape_a, rshape_a, shape_a);
    INDEX_MATMUL_SUBCASE(case6, left, right, indices_f, lshape_f, rshape_f, shape_f);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case6, left_v, right_v, indices_h, lshape_h, rshape_h, shape_h);
    DYNAMIC_INDEX_MATMUL_SUBCASE(case6, left_v, right_v, indices_v, lshape_v, rshape_v, shape_v);
}