#include "nmtools/array/functional/ufuncs/clip.hpp"
#include "nmtools/testing/data/array/clip.hpp"
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

TEST_CASE("clip(case1)" * doctest::test_suite("functional::clip"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, clip, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::clip, a, amin, amax );
    FUNCTIONAL_SUBCASE( "case1", fn::clip, a_a, amin_a, amax_a );
    FUNCTIONAL_SUBCASE( "case1", fn::clip, a_f, amin_f, amax_f );
    FUNCTIONAL_SUBCASE( "case1", fn::clip, a_h, amin_h, amax_h );
    FUNCTIONAL_SUBCASE( "case1", fn::clip, a_d, amin_d, amax_d );
}

TEST_CASE("clip(case2)" * doctest::test_suite("functional::clip"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, clip, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::clip, a, amin, amax );
    FUNCTIONAL_SUBCASE( "case2", fn::clip, a_a, amin_a, amax_a );
    FUNCTIONAL_SUBCASE( "case2", fn::clip, a_f, amin_f, amax_f );
    FUNCTIONAL_SUBCASE( "case2", fn::clip, a_h, amin_h, amax_h );
    FUNCTIONAL_SUBCASE( "case2", fn::clip, a_d, amin_d, amax_d );
}

TEST_CASE("clip(case3)" * doctest::test_suite("functional::clip"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, clip, case3);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case3", fn::clip, a, amin, amax );
    FUNCTIONAL_SUBCASE( "case3", fn::clip, a_a, amin_a, amax );
    FUNCTIONAL_SUBCASE( "case3", fn::clip, a_f, amin_f, amax );
    FUNCTIONAL_SUBCASE( "case3", fn::clip, a_h, amin_h, amax );
    FUNCTIONAL_SUBCASE( "case3", fn::clip, a_d, amin_d, amax );
}