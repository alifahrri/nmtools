#include "nmtools/array/functional/atleast_nd.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/testing/data/array/atleast_1d.hpp"
#include "nmtools/testing/data/array/atleast_2d.hpp"
#include "nmtools/testing/data/array/atleast_3d.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;
namespace na = nm::array;
namespace view = nmtools::view;

using namespace nm::literals;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_1d(case1)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_1d, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::atleast_nd[1_ct], a );
}

TEST_CASE("atleast_1d(case2)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_1d, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[1_ct], a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[1_ct], a_a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[1_ct], a_f );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[1_ct], a_h );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[1_ct], a_d );
}

TEST_CASE("atleast_1d(case3)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_1d, case3);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[1_ct], a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[1_ct], a_a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[1_ct], a_f );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[1_ct], a_h );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[1_ct], a_d );
}

TEST_CASE("atleast_1d(case4)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_1d, case4);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[1_ct], a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[1_ct], a_a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[1_ct], a_f );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[1_ct], a_h );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[1_ct], a_d );
}

TEST_CASE("atleast_2d(case1)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_2d, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::atleast_nd[2_ct], a );
}

TEST_CASE("atleast_2d(case2)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_2d, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[2_ct], a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[2_ct], a_a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[2_ct], a_f );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[2_ct], a_h );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[2_ct], a_d );
}

TEST_CASE("atleast_2d(case3)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_2d, case3);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[2_ct], a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[2_ct], a_a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[2_ct], a_f );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[2_ct], a_h );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[2_ct], a_d );
}

TEST_CASE("atleast_2d(case4)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_2d, case4);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[2_ct], a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[2_ct], a_a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[2_ct], a_f );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[2_ct], a_h );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[2_ct], a_d );
}

TEST_CASE("atleast_3d(case1)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_3d, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::atleast_nd[3_ct], a );
}

TEST_CASE("atleast_3d(case2)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_3d, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[3_ct], a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[3_ct], a_a );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[3_ct], a_f );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[3_ct], a_h );
    FUNCTIONAL_SUBCASE( "case2", fn::atleast_nd[3_ct], a_d );
}

TEST_CASE("atleast_3d(case3)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_3d, case3);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[3_ct], a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[3_ct], a_a );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[3_ct], a_f );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[3_ct], a_h );
    FUNCTIONAL_SUBCASE( "case3", fn::atleast_nd[3_ct], a_d );
}

TEST_CASE("atleast_3d(case4)" * doctest::test_suite("functional::atleast_nd"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, atleast_3d, case4);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[3_ct], a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[3_ct], a_a );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[3_ct], a_f );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[3_ct], a_h );
    FUNCTIONAL_SUBCASE( "case4", fn::atleast_nd[3_ct], a_d );
}

TEST_CASE("atleast_1d" * doctest::test_suite("functional::get_function_composition"))
{
    auto array = na::arange(10);
    auto a = view::atleast_nd(array,1_ct);

    [[maybe_unused]]
    auto function = fn::get_function_composition(a);
    // auto expect = fn::atleast_nd[1_ct];

    // NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("atleast_2d" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    auto array = na::arange(10);
    auto a = view::atleast_nd(array,2_ct);

    [[maybe_unused]]
    auto function = fn::get_function_composition(a);
    // auto expect = fn::atleast_nd[2_ct];

    // NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("atleast_3d" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    auto array = na::arange(10);
    auto a = view::atleast_nd(array,3_ct);

    [[maybe_unused]]
    auto function = fn::get_function_composition(a);
    // auto expect = fn::atleast_nd[3_ct];

    // NMTOOLS_ASSERT_EQUAL( function, expect );
}