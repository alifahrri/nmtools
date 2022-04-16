#include "nmtools/array/functional/ufuncs/isfinite.hpp"
#include "nmtools/testing/data/array/isfinite.hpp"
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

TEST_CASE("isfinite(case1)" * doctest::test_suite("functional::isfinite"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, isfinite, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::isfinite, a );
    FUNCTIONAL_SUBCASE( "case1", fn::isfinite, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::isfinite, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::isfinite, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::isfinite, a_d );
}