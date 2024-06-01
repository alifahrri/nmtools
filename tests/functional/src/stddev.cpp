#include "nmtools/array/functional/stddev.hpp"
#include "nmtools/testing/data/array/stddev.hpp"
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


TEST_CASE("stddev(case1)" * doctest::test_suite("functional::stddev"))
{
    NMTOOLS_TESTING_USE_CASE(array, stddev, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::stddev[axis][nm::None][ddof][keepdims], array );
    FUNCTIONAL_SUBCASE( "case1", fn::stddev[axis][nm::None][ddof][keepdims], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::stddev[axis][nm::None][ddof][keepdims], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::stddev[axis][nm::None][ddof][keepdims], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::stddev[axis][nm::None][ddof][keepdims], array_d );
}