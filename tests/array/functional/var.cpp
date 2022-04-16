#include "nmtools/array/functional/var.hpp"
#include "nmtools/testing/data/array/var.hpp"
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


TEST_CASE("var(case1)" * doctest::test_suite("functional::var"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, var, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::var[axis], array );
    FUNCTIONAL_SUBCASE( "case1", fn::var[axis], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::var[axis], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::var[axis], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::var[axis], array_d );
}

TEST_CASE("var(case6)" * doctest::test_suite("functional::var"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, var, case6);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case6", fn::var[axis][nm::None][ddof][keepdims], array );
    FUNCTIONAL_SUBCASE( "case6", fn::var[axis][nm::None][ddof][keepdims], array_a );
    FUNCTIONAL_SUBCASE( "case6", fn::var[axis][nm::None][ddof][keepdims], array_f );
    FUNCTIONAL_SUBCASE( "case6", fn::var[axis][nm::None][ddof][keepdims], array_h );
    FUNCTIONAL_SUBCASE( "case6", fn::var[axis][nm::None][ddof][keepdims], array_d );
}