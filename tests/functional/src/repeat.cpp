#include "nmtools/array/functional/repeat.hpp"
#include "nmtools/testing/data/array/repeat.hpp"
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


TEST_CASE("repeat(case1)" * doctest::test_suite("functional::repeat"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, repeat, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::repeat[repeats][axis], array );
    FUNCTIONAL_SUBCASE( "case1", fn::repeat[repeats][axis], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::repeat[repeats][axis], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::repeat[repeats][axis], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::repeat[repeats][axis], array_d );
}