#include "nmtools/array/softmax.hpp"
#include "nmtools/testing/data/array/softmax.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;

#define SOFTMAX_SUBCASE(subcase_name, function, attribute, operand) \
SUBCASE(subcase_name) \
{ \
    auto result = function[attribute](operand); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softmax(case1)" * doctest::test_suite("functional::softmax"))
{
    NMTOOLS_TESTING_USE_CASE(array,softmax,case1);
    using namespace args;

    SOFTMAX_SUBCASE("case1", fn::softmax, dim, input );
    SOFTMAX_SUBCASE("case1", fn::softmax, dim, input_a );
    SOFTMAX_SUBCASE("case1", fn::softmax, dim, input_f );
    SOFTMAX_SUBCASE("case1", fn::softmax, dim, input_d );
    SOFTMAX_SUBCASE("case1", fn::softmax, dim, input_h );
}

TEST_CASE("softmax(case2)" * doctest::test_suite("functional::softmax"))
{
    NMTOOLS_TESTING_USE_CASE(array,softmax,case2);
    using namespace args;

    SOFTMAX_SUBCASE("case2", fn::softmax, dim, input );
    SOFTMAX_SUBCASE("case2", fn::softmax, dim, input_a );
    SOFTMAX_SUBCASE("case2", fn::softmax, dim, input_f );
    SOFTMAX_SUBCASE("case2", fn::softmax, dim, input_d );
    SOFTMAX_SUBCASE("case2", fn::softmax, dim, input_h );
}

TEST_CASE("softmax(case3)" * doctest::test_suite("functional::softmax"))
{
    NMTOOLS_TESTING_USE_CASE(array,softmax,case3);
    using namespace args;

    SOFTMAX_SUBCASE("case3", fn::softmax, dim, input );
    SOFTMAX_SUBCASE("case3", fn::softmax, dim, input_a );
    SOFTMAX_SUBCASE("case3", fn::softmax, dim, input_f );
    SOFTMAX_SUBCASE("case3", fn::softmax, dim, input_d );
    SOFTMAX_SUBCASE("case3", fn::softmax, dim, input_h );
}

TEST_CASE("softmax(case4)" * doctest::test_suite("functional::softmax"))
{
    NMTOOLS_TESTING_USE_CASE(array,softmax,case4);
    using namespace args;

    SOFTMAX_SUBCASE("case4", fn::softmax, dim, input );
    SOFTMAX_SUBCASE("case4", fn::softmax, dim, input_a );
    SOFTMAX_SUBCASE("case4", fn::softmax, dim, input_f );
    SOFTMAX_SUBCASE("case4", fn::softmax, dim, input_d );
    SOFTMAX_SUBCASE("case4", fn::softmax, dim, input_h );
}

TEST_CASE("softmax(case5)" * doctest::test_suite("functional::softmax"))
{
    NMTOOLS_TESTING_USE_CASE(array,softmax,case5);
    using namespace args;

    SOFTMAX_SUBCASE("case5", fn::softmax, dim, input );
    SOFTMAX_SUBCASE("case5", fn::softmax, dim, input_a );
    SOFTMAX_SUBCASE("case5", fn::softmax, dim, input_f );
    SOFTMAX_SUBCASE("case5", fn::softmax, dim, input_d );
    SOFTMAX_SUBCASE("case5", fn::softmax, dim, input_h );
}