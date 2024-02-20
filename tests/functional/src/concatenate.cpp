#include "nmtools/array/functional/concatenate.hpp"
#include "nmtools/testing/data/array/concatenate.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/array/arange.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;
namespace na = nmtools::array;
namespace view = nm::view;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#define CURRY_BINARY_SUBCASE(subcase_name, function, lhs, rhs ) \
SUBCASE(subcase_name) \
{ \
    auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#define CONSTEXPR_FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#define CONSTEXPR_CURRY_BINARY_SUBCASE(subcase_name, function, lhs, rhs ) \
SUBCASE(subcase_name) \
{ \
    auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("concatenate(case1)" * doctest::test_suite("functional::concatenate"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, concatenate, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs, rhs );
    FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs_a, rhs_a );
    FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs_f, rhs_f );
    FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs_h, rhs_h );
    FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs_d, rhs_d );

    CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs, rhs );
    CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs_a, rhs_a );
    CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs_f, rhs_f );
    CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs_h, rhs_h );
    CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs_d, rhs_d );
}

TEST_CASE("constexpr_concatenate(case1)" * doctest::test_suite("functional::concatenate"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, constexpr_concatenate, case3);
    using namespace args;

    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs, rhs );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs_a, rhs_a );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs_f, rhs_f );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::concatenate[axis], lhs_h, rhs_h );

    CONSTEXPR_CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs, rhs );
    CONSTEXPR_CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs_a, rhs_a );
    CONSTEXPR_CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs_f, rhs_f );
    CONSTEXPR_CURRY_BINARY_SUBCASE( "case1", fn::concatenate[axis], lhs_h, rhs_h );
}

TEST_CASE("concatenate" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, concatenate, case1);
    using namespace args;

    auto a = view::concatenate(lhs,rhs,axis);

    auto function = fn::get_function_composition(a);
    auto expect = fn::concatenate[axis];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}