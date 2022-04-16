#include "nmtools/array/functional/mean.hpp"
#include "nmtools/testing/data/array/mean.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


TEST_CASE("mean(case1)" * doctest::test_suite("functional::mean"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::mean[axis], a );
    FUNCTIONAL_SUBCASE( "case1", fn::mean[axis], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::mean[axis], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::mean[axis], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::mean[axis], a_d );
}

TEST_CASE("mean(case2)" * doctest::test_suite("functional::mean"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::mean[axis], a );
    FUNCTIONAL_SUBCASE( "case2", fn::mean[axis], a_a );
    FUNCTIONAL_SUBCASE( "case2", fn::mean[axis], a_f );
    FUNCTIONAL_SUBCASE( "case2", fn::mean[axis], a_h );
    FUNCTIONAL_SUBCASE( "case2", fn::mean[axis], a_d );
}

TEST_CASE("mean(case6)" * doctest::test_suite("functional::mean"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case6);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case6", fn::mean[axis][nm::None][keepdims], a );
    FUNCTIONAL_SUBCASE( "case6", fn::mean[axis][nm::None][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case6", fn::mean[axis][nm::None][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case6", fn::mean[axis][nm::None][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case6", fn::mean[axis][nm::None][keepdims], a_d );
}

TEST_CASE("mean(case7)" * doctest::test_suite("functional::mean"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case7);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case7", fn::mean[axis][nm::None][keepdims], a );
    FUNCTIONAL_SUBCASE( "case7", fn::mean[axis][nm::None][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case7", fn::mean[axis][nm::None][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case7", fn::mean[axis][nm::None][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case7", fn::mean[axis][nm::None][keepdims], a_d );
}

TEST_CASE("mean(case9)" * doctest::test_suite("functional::mean"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case9);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case9", fn::mean[axis][nm::None][keepdims], a );
    FUNCTIONAL_SUBCASE( "case9", fn::mean[axis][nm::None][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case9", fn::mean[axis][nm::None][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case9", fn::mean[axis][nm::None][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case9", fn::mean[axis][nm::None][keepdims], a_d );
}

TEST_CASE("mean(case12)" * doctest::test_suite("functional::mean"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case12);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case12", fn::mean[axis][nm::None][keepdims], a );
    FUNCTIONAL_SUBCASE( "case12", fn::mean[axis][nm::None][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case12", fn::mean[axis][nm::None][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case12", fn::mean[axis][nm::None][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case12", fn::mean[axis][nm::None][keepdims], a_d );
}

TEST_CASE("mean(case21)" * doctest::test_suite("functional::mean"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case21);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case21", fn::mean[axis][nm::None][keepdims], a );
    FUNCTIONAL_SUBCASE( "case21", fn::mean[axis][nm::None][keepdims], a_a );
    FUNCTIONAL_SUBCASE( "case21", fn::mean[axis][nm::None][keepdims], a_f );
    FUNCTIONAL_SUBCASE( "case21", fn::mean[axis][nm::None][keepdims], a_h );
    FUNCTIONAL_SUBCASE( "case21", fn::mean[axis][nm::None][keepdims], a_d );
}