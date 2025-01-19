#include "nmtools/array/softmin.hpp"
#include "nmtools/testing/data/array/softmin.hpp"
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


TEST_CASE("softmin(case1)" * doctest::test_suite("functional::softmin"))
{
    NMTOOLS_TESTING_USE_CASE(array, softmin, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::softmin[dim], input );
    FUNCTIONAL_SUBCASE( "case1", fn::softmin[dim], input_a );
    FUNCTIONAL_SUBCASE( "case1", fn::softmin[dim], input_f );
    FUNCTIONAL_SUBCASE( "case1", fn::softmin[dim], input_h );
    FUNCTIONAL_SUBCASE( "case1", fn::softmin[dim], input_d );
}