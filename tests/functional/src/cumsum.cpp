#include "nmtools/array/functional/cumsum.hpp"
#include "nmtools/testing/data/array/add.hpp"
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


TEST_CASE("cumsum(case1)" * doctest::test_suite("functional::cumsum"))
{
    NMTOOLS_TESTING_USE_CASE(view, accumulate_add, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::cumsum[axis], a );
    FUNCTIONAL_SUBCASE( "case1", fn::cumsum[axis], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::cumsum[axis], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::cumsum[axis], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::cumsum[axis], a_d );
}