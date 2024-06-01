#include "nmtools/array/functional/matmul.hpp"
#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/array/functional/flatten.hpp"
#include "nmtools/array/functional/ufuncs/add.hpp"
#include "nmtools/array/view/full.hpp"
#include "nmtools/array/array/flatten.hpp"

#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace view = nm::view;
namespace meta = nm::meta;

#define FUNCTIONAL_SUBCASE(subcase_name, expect, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define CURRY_BINARY_FUNCTIONAL_SUBCASE(subcase_name, expect, function, lhs, rhs) \
SUBCASE(subcase_name) \
{ \
    auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define CONSTEXPR_FUNCTIONAL_SUBCASE(subcase_name, expect, function, ...) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define CONSTEXPR_CURRY_BINARY_FUNCTIONAL_SUBCASE(subcase_name, expect, function, lhs, rhs) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function (lhs) (rhs); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("flatten_add(case1)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,add,case1);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::add;
        static_assert( decltype(f)::arity == 2 );
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a, b);
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_a, b_a);
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_f, b_f);
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_h, b_h);
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_d, b_d);

        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_a, b_a);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_f, b_f);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_h, b_h);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_d, b_d);
    }
    {
        FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a)), b);
        FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a_a)), b_a);
        FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a_f)), b_f);
        FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a_h)), b_h);
        FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a_d)), b_d);
    }
}

TEST_CASE("flatten_add(case2)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,add,case2);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::add;
        static_assert( decltype(f)::arity == 2 );
        FUNCTIONAL_SUBCASE( "case2", flattened, f, a, b);
        FUNCTIONAL_SUBCASE( "case2", flattened, f, a_a, b);
        FUNCTIONAL_SUBCASE( "case2", flattened, f, a_f, b);
        FUNCTIONAL_SUBCASE( "case2", flattened, f, a_h, b);
        FUNCTIONAL_SUBCASE( "case2", flattened, f, a_d, b);

        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case2", flattened, f, a, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case2", flattened, f, a_a, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case2", flattened, f, a_f, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case2", flattened, f, a_h, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case2", flattened, f, a_d, b);
    }
    {
        FUNCTIONAL_SUBCASE( "case2", flattened, (fn::flatten * fn::add (a)), b);
        FUNCTIONAL_SUBCASE( "case2", flattened, (fn::flatten * fn::add (a_a)), b);
        FUNCTIONAL_SUBCASE( "case2", flattened, (fn::flatten * fn::add (a_f)), b);
        FUNCTIONAL_SUBCASE( "case2", flattened, (fn::flatten * fn::add (a_h)), b);
        FUNCTIONAL_SUBCASE( "case2", flattened, (fn::flatten * fn::add (a_d)), b);
    }
}

// NOTE: flattening a num is not supporte (yet?)
#if 0
TEST_CASE("flatten_add(case3)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,add,case3);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::add;
        static_assert( decltype(f)::arity == 2 );
        FUNCTIONAL_SUBCASE( "case3", flattened, f, a, b);

        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case3", flattened, f, a, b);
    }
    {
        FUNCTIONAL_SUBCASE( "case3", flattened, (fn::flatten * fn::add (a)), b);
    }
}
#endif

TEST_CASE("flatten_add(case4)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,add,case4);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::add;
        static_assert( decltype(f)::arity == 2 );
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a, b);
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_a, b);
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_f, b);
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_h, b);
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_d, b);

        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case4", flattened, f, a, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case4", flattened, f, a_a, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case4", flattened, f, a_f, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case4", flattened, f, a_h, b);
        CURRY_BINARY_FUNCTIONAL_SUBCASE( "case4", flattened, f, a_d, b);
    }
    {
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::add (a)), b);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::add (a_a)), b);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::add (a_f)), b);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::add (a_h)), b);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::add (a_d)), b);
    }
}

// TODO: fix, maybe because add
#if 0
TEST_CASE("constexpr_flatten_add(case1)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(array,constexpr_add,case1);
    using namespace args;
    constexpr auto flattened = na::flatten(expect::result);

    {
        constexpr auto f = fn::flatten * fn::add;
        static_assert( decltype(f)::arity == 2 );
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, f, a, b);
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_a, b_a);
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_f, b_f);
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_h, b_h);

        CONSTEXPR_CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a, b);
        CONSTEXPR_CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_a, b_a);
        CONSTEXPR_CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_f, b_f);
        CONSTEXPR_CURRY_BINARY_FUNCTIONAL_SUBCASE( "case1", flattened, f, a_h, b_h);
    }
    {
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a)), b);
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a_a)), b_a);
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a_f)), b_f);
        CONSTEXPR_FUNCTIONAL_SUBCASE( "case1", flattened, (fn::flatten * fn::add (a_h)), b_h);
    }
}
#endif

TEST_CASE("flatten_reduce_add(case1)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case1);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::reduce_add[axis];
        static_assert( decltype(f)::arity == 1 );
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a );
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_a );
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_f );
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_h );
        FUNCTIONAL_SUBCASE( "case1", flattened, f, a_d );
    }
}

TEST_CASE("flatten_reduce_add(case4)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case4);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::reduce_add[axis];
        static_assert( decltype(f)::arity == 1 );
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a );
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_a );
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_f );
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_h );
        FUNCTIONAL_SUBCASE( "case4", flattened, f, a_d );
    }
    {
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::reduce_add[axis]), a);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::reduce_add[axis_a]), a_a);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::reduce_add[axis_f]), a_f);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::reduce_add[axis_h]), a_h);
        FUNCTIONAL_SUBCASE( "case4", flattened, (fn::flatten * fn::reduce_add[axis_v]), a_d);
    }
}

TEST_CASE("flatten_reduce_add(case9)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case9);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::reduce_add[axis][dtype][initial][keepdims];
        static_assert( decltype(f)::arity == 1 );
        FUNCTIONAL_SUBCASE( "case9", flattened, f, a );
        FUNCTIONAL_SUBCASE( "case9", flattened, f, a_a );
        FUNCTIONAL_SUBCASE( "case9", flattened, f, a_f );
        FUNCTIONAL_SUBCASE( "case9", flattened, f, a_h );
        FUNCTIONAL_SUBCASE( "case9", flattened, f, a_d );
    }
}

TEST_CASE("flatten_reduce_add(case14)" * doctest::test_suite("functional::composition"))
{

    // TODO: rename test case to array::add instead of view::add
    NMTOOLS_TESTING_USE_CASE(view,reduce_add,case14);
    using namespace args;
    auto flattened = na::flatten(expect::result);

    {
        auto f = fn::flatten * fn::reduce_add[axis][dtype][initial][keepdims];
        static_assert( decltype(f)::arity == 1 );
        FUNCTIONAL_SUBCASE( "case14", flattened, f, a );
        FUNCTIONAL_SUBCASE( "case14", flattened, f, a_a );
        FUNCTIONAL_SUBCASE( "case14", flattened, f, a_f );
        FUNCTIONAL_SUBCASE( "case14", flattened, f, a_h );
        // TODO: fix utl either
        #ifndef NMTOOLS_DISABLE_STL
        FUNCTIONAL_SUBCASE( "case14", flattened, f, a_d );
        #endif
    }
    {
        FUNCTIONAL_SUBCASE( "case14", flattened, (fn::flatten * fn::reduce_add[axis][dtype][initial][keepdims]), a);
        FUNCTIONAL_SUBCASE( "case14", flattened, (fn::flatten * fn::reduce_add[axis_a][dtype][initial][keepdims]), a_a);
        FUNCTIONAL_SUBCASE( "case14", flattened, (fn::flatten * fn::reduce_add[axis_f][dtype][initial][keepdims]), a_f);
        FUNCTIONAL_SUBCASE( "case14", flattened, (fn::flatten * fn::reduce_add[axis_h][dtype][initial][keepdims]), a_h);
        // TODO: fix utl vector
        #ifndef NMTOOLS_DISABLE_STL
        FUNCTIONAL_SUBCASE( "case14", flattened, (fn::flatten * fn::reduce_add[axis_v][dtype][initial][keepdims]), a_d);
        #endif
    }
}