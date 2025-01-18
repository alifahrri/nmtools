#include "nmtools/array/take.hpp"
#include "nmtools/testing/data/array/take.hpp"
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


// TODO: fix runtime
TEST_CASE("take(case1)" * doctest::test_suite("functional::take") * doctest::skip())
{
    NMTOOLS_TESTING_USE_CASE(view, take, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::take[indices][axis], array );
    FUNCTIONAL_SUBCASE( "case1", fn::take[indices_a][axis], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::take[indices_f][axis], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::take[indices_h][axis], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::take[indices_d][axis], array_d );
}