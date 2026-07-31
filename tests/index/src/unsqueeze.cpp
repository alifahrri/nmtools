#include "nmtools/array/unsqueeze.hpp"
#include "nmtools/testing/data/index/unsqueeze.hpp"
#include "nmtools/ndarray.hpp"

#include "nmtools/testing/doctest.hpp"

#define SHAPE_UNSQUEEZE_SUBCASE(case_name,shape,axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( shape_unsqueeze, case_name ); \
    auto result = nmtools::index::shape_unsqueeze( shape, axis ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define SHAPE_UNSQUEEZE_RESULT_SUBCASE(case_name,result,shape,axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( shape_unsqueeze, case_name ); \
    auto result = nmtools::index::shape_unsqueeze( shape, axis ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_unsqueeze(case1)" * doctest::test_suite("index::shape_unsqueeze"))
{
    SHAPE_UNSQUEEZE_SUBCASE( case1, shape, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case1, shape_a, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case1, shape_f, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case1, shape_h, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case1, shape_v, axis );

    SHAPE_UNSQUEEZE_SUBCASE( case1, shape_ct, axis_ct );
    
    SHAPE_UNSQUEEZE_RESULT_SUBCASE( case1, result_nl1, shape_nl1, axis );
    SHAPE_UNSQUEEZE_RESULT_SUBCASE( case1, result_nl2, shape_nl2, axis );

    SHAPE_UNSQUEEZE_SUBCASE( case1, shape_mx1, axis_ct );
    SHAPE_UNSQUEEZE_SUBCASE( case1, shape_mx2, axis_ct );
}

TEST_CASE("shape_unsqueeze(case2)" * doctest::test_suite("index::shape_unsqueeze"))
{
    SHAPE_UNSQUEEZE_SUBCASE( case2, shape, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case2, shape_a, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case2, shape_f, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case2, shape_h, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case2, shape_v, axis );

    SHAPE_UNSQUEEZE_SUBCASE( case2, shape_ct, axis_ct );

    SHAPE_UNSQUEEZE_RESULT_SUBCASE( case2, result_nl1, shape_nl1, axis );
    SHAPE_UNSQUEEZE_RESULT_SUBCASE( case2, result_nl2, shape_nl2, axis );

    SHAPE_UNSQUEEZE_SUBCASE( case2, shape_mx1, axis_ct );
    SHAPE_UNSQUEEZE_SUBCASE( case2, shape_mx2, axis_ct );
}

TEST_CASE("shape_unsqueeze(case3)" * doctest::test_suite("index::shape_unsqueeze"))
{
    SHAPE_UNSQUEEZE_SUBCASE( case3, shape, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case3, shape_a, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case3, shape_f, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case3, shape_h, axis );
    SHAPE_UNSQUEEZE_SUBCASE( case3, shape_v, axis );

    SHAPE_UNSQUEEZE_SUBCASE( case3, shape_ct, axis_ct );

    SHAPE_UNSQUEEZE_RESULT_SUBCASE( case3, result_nl1, shape_nl1, axis );
    SHAPE_UNSQUEEZE_RESULT_SUBCASE( case3, result_nl2, shape_nl2, axis );

    SHAPE_UNSQUEEZE_SUBCASE( case3, shape_mx1, axis_ct );
    SHAPE_UNSQUEEZE_SUBCASE( case3, shape_mx2, axis_ct );
}