#include "nmtools/array/functional/broadcast_to.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;
namespace na = nmtools::array;
namespace view = nmtools::view;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#define CONSTEXPR_FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}


TEST_CASE("broadcast_to(case1)" * doctest::test_suite("functional::broadcast_to"))
{
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x_a );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x_f );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x_h );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x_d );

    // TODO: fix
    #if 0
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x_a );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x_f );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x_h );
    FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x_d );
    #endif
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("functional::broadcast_to"))
{
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case7);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x );
    FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x_a );
    FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x_f );
    FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x_h );
    FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x_d );
}

TEST_CASE("broadcast_to(case10)" * doctest::test_suite("functional::broadcast_to"))
{
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case10);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case10", fn::broadcast_to[shape], x );
}

#if 0
TEST_CASE("constexpr_broadcast_to(case1)" * doctest::test_suite("functional::broadcast_to"))
{
    NMTOOLS_TESTING_DECLARE_NS(constexpr_broadcast_to, case1);
    using namespace args;

    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x_a );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x_f );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape], x_h );

    // TODO: fix
    #if 0
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x_a );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x_f );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", fn::broadcast_to[shape_ct], x_h );
    #endif
}

TEST_CASE("constexpr_broadcast_to(case7)" * doctest::test_suite("functional::broadcast_to"))
{
    NMTOOLS_TESTING_DECLARE_NS(constexpr_broadcast_to, case7);
    using namespace args;

    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x_a );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x_f );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape], x_h );

    // TODO: fix
    #if 0
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape_ct], x );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape_ct], x_a );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape_ct], x_f );
    CONSTEXPR_FUNCTIONAL_SUBCASE( "case7", fn::broadcast_to[shape_ct], x_h );
    #endif
}

TEST_CASE("constexpr_broadcast_to(case10)" * doctest::test_suite("functional::broadcast_to"))
{
    NMTOOLS_TESTING_DECLARE_NS(constexpr_broadcast_to, case10);
    using namespace args;

    CONSTEXPR_FUNCTIONAL_SUBCASE( "case10", fn::broadcast_to[shape], x );
}
#endif

TEST_CASE("broadcast_to" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    auto array = na::arange(10);
    auto dst_shape = nmtools_array{2,10};
    auto bcast_size = nm::None;
    auto a = view::broadcast_to(array,dst_shape);

    auto function = fn::get_function_composition(a);
    auto expect = fn::broadcast_to[dst_shape][bcast_size];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("broadcast_to" * doctest::test_suite("functional::get_function_composition"))
{
    auto array = na::arange(10);
    auto dst_shape = nmtools_array{2,10};
    auto bcast_size = nm::None;
    auto a = view::broadcast_to(array,dst_shape);

    auto function = fn::get_function_composition(a);
    auto expect = fn::broadcast_to[dst_shape][bcast_size];

    NMTOOLS_ASSERT_CLOSE( unwrap(function) (array), expect (array) );
}