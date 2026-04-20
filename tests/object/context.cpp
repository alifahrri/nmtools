#include "nmtools/context/default.hpp"
#include "nmtools/array/full.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nm::view;

using namespace nmtools::literals;

TEST_CASE("context(case1)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using buffer_t = nmtools_array<float,8>;
    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto buffer_vtype = nm::as_value_v<buffer_t>;
    auto shape_vtype  = nm::as_value_v<shape_t>;

    static_assert( nm::is_context_v<decltype(ctx)> );
    static_assert( !nm::is_context_v<nm::none_t> );

    {
        auto a = ctx.create(buffer_vtype,shape_vtype);

        static_assert( nm::is_ndarray_v<decltype(a)> );
        static_assert( decltype(a)::broadcasting );
        static_assert( nm::is_object_ndarray_v<decltype(a)> );
    }
    {
        auto a = ctx.disable_broadcast().create(buffer_vtype,shape_vtype);

        static_assert( nm::is_ndarray_v<decltype(a)> );
        static_assert( !decltype(a)::broadcasting );
        static_assert( nm::is_object_ndarray_v<decltype(a)> );
    }
}

TEST_CASE("context(case2)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using buffer_t = nmtools_array<float,8>;
    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto buffer_vtype = nm::as_value_v<buffer_t>;
    auto shape = shape_t{};

    {
        auto a = ctx.create(buffer_vtype,shape);

        static_assert( nm::is_ndarray_v<decltype(a)> );
        static_assert( decltype(a)::broadcasting );

        NMTOOLS_ASSERT_EQUAL( nm::shape(a), shape );
    }
    {
        auto a = ctx.disable_broadcast().create(buffer_vtype,shape);

        static_assert( nm::is_ndarray_v<decltype(a)> );
        static_assert( !decltype(a)::broadcasting );

        NMTOOLS_ASSERT_EQUAL( nm::shape(a), shape );
    }
}

TEST_CASE("context(case3)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto value = 3.0f;
    auto a = ctx.full(shape, value);
    NMTOOLS_ASSERT_CLOSE( a, nm::full(shape, value) );
}

TEST_CASE("context(case4)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.zeros(shape);
    NMTOOLS_ASSERT_CLOSE( a, nm::zeros(shape,nm::float32) );
}

TEST_CASE("context(case5)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.ones(shape);
    NMTOOLS_ASSERT_CLOSE( a, nm::ones(shape,nm::float32) );
}

TEST_CASE("context(case6)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto result = ctx.create(nm::float32,shape);
    ctx.eval(result,view::ones(shape,nm::float32));

    NMTOOLS_ASSERT_CLOSE( result, nm::ones(shape,nm::float32) );
}

TEST_CASE("context(case7)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto result = ctx.eval(view::ones(shape,nm::float32));

    NMTOOLS_ASSERT_CLOSE( result, nm::ones(shape,nm::float32) );
}

TEST_CASE("context(case8)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Object;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.ones(shape);
    auto b = ctx.ones(shape);

    auto c = a + b;
    auto expected = ctx.full(shape, 2.f);
    NMTOOLS_ASSERT_CLOSE( c, expected );
}