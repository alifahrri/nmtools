#include "nmtools/array/functional/slice.hpp"
#include "nmtools/testing/data/array/slice.hpp"
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

// NOTE: somehow triggers error on libstdc++
// TODO: fix for libstdc++
#if not __GLIBCXX__
TEST_CASE("slice(case1)" * doctest::test_suite("functional::slice"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, slice, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::slice[slice0][slice1][slice2], array );
    FUNCTIONAL_SUBCASE( "case1", fn::slice[slice0][slice1][slice2], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::slice[slice0][slice1][slice2], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::slice[slice0][slice1][slice2], array_h );
    FUNCTIONAL_SUBCASE( "case1", fn::slice[slice0][slice1][slice2], array_d );
}
#endif


TEST_CASE("apply_slice(case1)" * doctest::test_suite("functional::apply_slice"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, slice, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE("case1", fn::apply_slice[dslices], array_d );
}
