#include "nmtools/array/functional/conv.hpp"
#include "nmtools/testing/data/array/conv.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;

#define CONV2D_SUBCASE(subcase_name, function, input, weight) \
SUBCASE(subcase_name) \
{ \
    auto result = function(input,weight); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CURRY_CONV2D_SUBCASE(subcase_name, function, input, weight) \
SUBCASE(subcase_name) \
{ \
    auto result = function(input)(weight); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CONV2D_BIAS_SUBCASE(subcase_name, function, input, weight, bias) \
SUBCASE(subcase_name) \
{ \
    auto result = function(input,weight,bias); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define CURRY_CONV2D_BIAS_SUBCASE(subcase_name, function, input, weight, bias) \
SUBCASE(subcase_name) \
{ \
    auto result = function(input)(weight)(bias); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("conv2d(case1)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case1);
    using namespace args;

    CONV2D_SUBCASE( "case1", fn::conv2d, input, weight );
    CONV2D_SUBCASE( "case1", fn::conv2d, input_a, weight_a );
    CONV2D_SUBCASE( "case1", fn::conv2d, input_f, weight_f );
    CONV2D_SUBCASE( "case1", fn::conv2d, input_h, weight_h );
    CONV2D_SUBCASE( "case1", fn::conv2d, input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case1", fn::conv2d, input, weight );
    CURRY_CONV2D_SUBCASE( "case1", fn::conv2d, input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case1", fn::conv2d, input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case1", fn::conv2d, input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case1", fn::conv2d, input_d, weight_d );
}

TEST_CASE("conv2d(case2)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case2);
    using namespace args;

    CONV2D_SUBCASE( "case2", fn::conv2d, input, weight );
    CONV2D_SUBCASE( "case2", fn::conv2d, input_a, weight_a );
    CONV2D_SUBCASE( "case2", fn::conv2d, input_f, weight_f );
    CONV2D_SUBCASE( "case2", fn::conv2d, input_h, weight_h );
    CONV2D_SUBCASE( "case2", fn::conv2d, input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case2", fn::conv2d, input, weight );
    CURRY_CONV2D_SUBCASE( "case2", fn::conv2d, input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case2", fn::conv2d, input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case2", fn::conv2d, input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case2", fn::conv2d, input_d, weight_d );
}

TEST_CASE("conv2d(case3)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case3);
    using namespace args;

    CONV2D_SUBCASE( "case3", fn::conv2d, input, weight );
    CONV2D_SUBCASE( "case3", fn::conv2d, input_a, weight_a );
    CONV2D_SUBCASE( "case3", fn::conv2d, input_f, weight_f );
    CONV2D_SUBCASE( "case3", fn::conv2d, input_h, weight_h );
    CONV2D_SUBCASE( "case3", fn::conv2d, input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case3", fn::conv2d, input, weight );
    CURRY_CONV2D_SUBCASE( "case3", fn::conv2d, input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case3", fn::conv2d, input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case3", fn::conv2d, input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case3", fn::conv2d, input_d, weight_d );
}

using nmtools::None;

TEST_CASE("conv2d(case4)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case4);
    using namespace args;

    CONV2D_SUBCASE( "case4", fn::conv2d, input, weight );
    CONV2D_SUBCASE( "case4", fn::conv2d, input_a, weight_a );
    CONV2D_SUBCASE( "case4", fn::conv2d, input_f, weight_f );
    CONV2D_SUBCASE( "case4", fn::conv2d, input_h, weight_h );
    CONV2D_SUBCASE( "case4", fn::conv2d, input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d, input, weight );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d, input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d, input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d, input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d, input_d, weight_d );

    CONV2D_SUBCASE( "case4", fn::conv2d[stride], input, weight );
    CONV2D_SUBCASE( "case4", fn::conv2d[stride_a], input_a, weight_a );
    CONV2D_SUBCASE( "case4", fn::conv2d[stride_f], input_f, weight_f );
    CONV2D_SUBCASE( "case4", fn::conv2d[stride_h], input_h, weight_h );
    CONV2D_SUBCASE( "case4", fn::conv2d[stride_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d[stride], input, weight );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d[stride_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d[stride_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d[stride_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case4", fn::conv2d[stride_v], input_d, weight_d );
}

TEST_CASE("conv2d(case5)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case5);
    using namespace args;

    CONV2D_SUBCASE( "case5", fn::conv2d[stride], input, weight );
    CONV2D_SUBCASE( "case5", fn::conv2d[stride_a], input_a, weight_a );
    CONV2D_SUBCASE( "case5", fn::conv2d[stride_f], input_f, weight_f );
    CONV2D_SUBCASE( "case5", fn::conv2d[stride_h], input_h, weight_h );
    CONV2D_SUBCASE( "case5", fn::conv2d[stride_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case5", fn::conv2d[stride], input, weight );
    CURRY_CONV2D_SUBCASE( "case5", fn::conv2d[stride_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case5", fn::conv2d[stride_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case5", fn::conv2d[stride_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case5", fn::conv2d[stride_v], input_d, weight_d );
}

TEST_CASE("conv2d(case6)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case6);
    using namespace args;

    CONV2D_SUBCASE( "case6", fn::conv2d[stride], input, weight );
    CONV2D_SUBCASE( "case6", fn::conv2d[stride_a], input_a, weight_a );
    CONV2D_SUBCASE( "case6", fn::conv2d[stride_f], input_f, weight_f );
    CONV2D_SUBCASE( "case6", fn::conv2d[stride_h], input_h, weight_h );
    CONV2D_SUBCASE( "case6", fn::conv2d[stride_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case6", fn::conv2d[stride], input, weight );
    CURRY_CONV2D_SUBCASE( "case6", fn::conv2d[stride_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case6", fn::conv2d[stride_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case6", fn::conv2d[stride_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case6", fn::conv2d[stride_v], input_d, weight_d );
}

TEST_CASE("conv2d(case7)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case7);
    using namespace args;

    CONV2D_SUBCASE( "case7", fn::conv2d[stride], input, weight );
    CONV2D_SUBCASE( "case7", fn::conv2d[stride_a], input_a, weight_a );
    CONV2D_SUBCASE( "case7", fn::conv2d[stride_f], input_f, weight_f );
    CONV2D_SUBCASE( "case7", fn::conv2d[stride_h], input_h, weight_h );
    CONV2D_SUBCASE( "case7", fn::conv2d[stride_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case7", fn::conv2d[stride], input, weight );
    CURRY_CONV2D_SUBCASE( "case7", fn::conv2d[stride_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case7", fn::conv2d[stride_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case7", fn::conv2d[stride_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case7", fn::conv2d[stride_v], input_d, weight_d );
}

TEST_CASE("conv2d(case8)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case8);
    using namespace args;

    CONV2D_SUBCASE( "case8", fn::conv2d[stride], input, weight );
    CONV2D_SUBCASE( "case8", fn::conv2d[stride_a], input_a, weight_a );
    CONV2D_SUBCASE( "case8", fn::conv2d[stride_f], input_f, weight_f );
    CONV2D_SUBCASE( "case8", fn::conv2d[stride_h], input_h, weight_h );
    CONV2D_SUBCASE( "case8", fn::conv2d[stride_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case8", fn::conv2d[stride], input, weight );
    CURRY_CONV2D_SUBCASE( "case8", fn::conv2d[stride_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case8", fn::conv2d[stride_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case8", fn::conv2d[stride_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case8", fn::conv2d[stride_v], input_d, weight_d );
}

TEST_CASE("conv2d(case9)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case9);
    using namespace args;

    CONV2D_SUBCASE( "case9", fn::conv2d[stride], input, weight );
    CONV2D_SUBCASE( "case9", fn::conv2d[stride_a], input_a, weight_a );
    CONV2D_SUBCASE( "case9", fn::conv2d[stride_f], input_f, weight_f );
    CONV2D_SUBCASE( "case9", fn::conv2d[stride_h], input_h, weight_h );
    CONV2D_SUBCASE( "case9", fn::conv2d[stride_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case9", fn::conv2d[stride], input, weight );
    CURRY_CONV2D_SUBCASE( "case9", fn::conv2d[stride_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case9", fn::conv2d[stride_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case9", fn::conv2d[stride_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case9", fn::conv2d[stride_v], input_d, weight_d );
}

TEST_CASE("conv2d(case10)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case10);
    using namespace args;

    CONV2D_SUBCASE( "case10", fn::conv2d[stride], input, weight );
    CONV2D_SUBCASE( "case10", fn::conv2d[stride_a], input_a, weight_a );
    CONV2D_SUBCASE( "case10", fn::conv2d[stride_f], input_f, weight_f );
    CONV2D_SUBCASE( "case10", fn::conv2d[stride_h], input_h, weight_h );
    CONV2D_SUBCASE( "case10", fn::conv2d[stride_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case10", fn::conv2d[stride], input, weight );
    CURRY_CONV2D_SUBCASE( "case10", fn::conv2d[stride_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case10", fn::conv2d[stride_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case10", fn::conv2d[stride_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case10", fn::conv2d[stride_v], input_d, weight_d );
}

TEST_CASE("conv2d(case11)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case11);
    using namespace args;

    CONV2D_SUBCASE( "case11", fn::conv2d[stride][padding], input, weight );
    CONV2D_SUBCASE( "case11", fn::conv2d[stride_a][padding_a], input_a, weight_a );
    CONV2D_SUBCASE( "case11", fn::conv2d[stride_f][padding_f], input_f, weight_f );
    CONV2D_SUBCASE( "case11", fn::conv2d[stride_h][padding_h], input_h, weight_h );
    CONV2D_SUBCASE( "case11", fn::conv2d[stride_v][padding_v], input_d, weight_d );

    CURRY_CONV2D_SUBCASE( "case11", fn::conv2d[stride][padding], input, weight );
    CURRY_CONV2D_SUBCASE( "case11", fn::conv2d[stride_a][padding_a], input_a, weight_a );
    CURRY_CONV2D_SUBCASE( "case11", fn::conv2d[stride_f][padding_f], input_f, weight_f );
    CURRY_CONV2D_SUBCASE( "case11", fn::conv2d[stride_h][padding_h], input_h, weight_h );
    CURRY_CONV2D_SUBCASE( "case11", fn::conv2d[stride_v][padding_v], input_d, weight_d );
}

TEST_CASE("conv2d(case16)" * doctest::test_suite("functional::conv2d"))
{
    NMTOOLS_TESTING_DECLARE_NS(array,conv2d,case16);
    using namespace args;

    CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input, weight, bias );
    CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_a, weight_a, bias_a );
    CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_f, weight_f, bias_f );
    CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_h, weight_h, bias_h );
    CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_d, weight_d, bias_d );

    CURRY_CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input, weight, bias );
    CURRY_CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_a, weight_a, bias_a );
    CURRY_CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_f, weight_f, bias_f );
    CURRY_CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_h, weight_h, bias_h );
    CURRY_CONV2D_BIAS_SUBCASE( "case16", fn::conv2d_bias[stride][padding], input_d, weight_d, bias_d );
}