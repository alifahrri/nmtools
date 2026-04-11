#include "nmtools/core/context/unroll.hpp"
#include "nmtools/array/full.hpp"
#include "nmtools/array/zeros.hpp"
#include "nmtools/array/ones.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace view = nm::view;

using namespace nmtools::literals;

TEST_CASE("unroll_context(case1)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using buffer_t = nmtools_array<float,8>;
    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto buffer_vtype = nm::as_value_v<buffer_t>;
    auto shape_vtype  = nm::as_value_v<shape_t>;

    static_assert( nm::is_context_v<decltype(ctx)> );
    static_assert( !nm::is_context_v<nm::none_t> );

    {
        auto a = ctx.create(buffer_vtype,shape_vtype);

        static_assert( nm::is_ndarray_v<decltype(a)> );
    }
    {
        auto a = ctx.disable_broadcast().create(buffer_vtype,shape_vtype);

        static_assert( nm::is_ndarray_v<decltype(a)> );
    }
}

TEST_CASE("unroll_context(case2)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using buffer_t = nmtools_array<float,8>;
    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto buffer_vtype = nm::as_value_v<buffer_t>;
    auto shape = shape_t{};

    {
        auto a = ctx.create(buffer_vtype,shape);

        static_assert( nm::is_ndarray_v<decltype(a)> );

        NMTOOLS_ASSERT_EQUAL( nm::shape(a), shape );
    }
    {
        auto a = ctx.disable_broadcast().create(buffer_vtype,shape);

        static_assert( nm::is_ndarray_v<decltype(a)> );

        NMTOOLS_ASSERT_EQUAL( nm::shape(a), shape );
    }
}

TEST_CASE("unroll_context(case3)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto value = 3.0f;
    auto a = ctx.full(shape, value);
    NMTOOLS_ASSERT_CLOSE( a, nm::full(shape, value) );
}

TEST_CASE("unroll_context(case4)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.zeros(shape);
    NMTOOLS_ASSERT_CLOSE( a, nm::zeros(shape,nm::float32) );
}

TEST_CASE("unroll_context(case5)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.ones(shape);
    NMTOOLS_ASSERT_CLOSE( a, nm::ones(shape,nm::float32) );
}

TEST_CASE("unroll_context(case6)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.create(nm::float32,shape);
    static_assert( nm::is_ndarray_v<decltype(a)> );
    NMTOOLS_ASSERT_EQUAL( nm::shape(a), shape );
}

TEST_CASE("unroll_context(case7)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    auto a = ctx.row_major();
    auto b = ctx.col_major();

    static_assert( nm::is_context_v<decltype(a)> );
    static_assert( nm::is_context_v<decltype(b)> );
}

TEST_CASE("unroll_context(case8)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    auto a = ctx.enable_broadcast();
    auto b = ctx.disable_broadcast();

    static_assert( nm::is_context_v<decltype(a)> );
    static_assert( nm::is_context_v<decltype(b)> );
}

TEST_CASE("unroll_context(case9)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using buffer_t = nmtools_array<float,24>;
    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<3>,nm::ct<4>>;
    auto buffer_vtype = nm::as_value_v<buffer_t>;
    auto shape_vtype  = nm::as_value_v<shape_t>;

    auto a = ctx.create(buffer_vtype,shape_vtype);
    static_assert( nm::is_ndarray_v<decltype(a)> );
    NMTOOLS_ASSERT_EQUAL( nm::shape(a), shape_t{} );
}

TEST_CASE("unroll_context(case10)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<3>,nm::ct<4>>;
    auto shape = shape_t{};

    auto value = 5.0f;
    auto a = ctx.full(shape, value);

    static_assert( nm::is_ndarray_v<decltype(a)> );
    NMTOOLS_ASSERT_CLOSE( a, nm::full(shape, value) );
}

TEST_CASE("unroll_context(case11)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<3>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.zeros(shape);
    NMTOOLS_ASSERT_CLOSE( a, nm::zeros(shape,nm::float32) );
}

TEST_CASE("unroll_context(case12)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<3>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.ones(shape);
    NMTOOLS_ASSERT_CLOSE( a, nm::ones(shape,nm::float32) );
}

TEST_CASE("unroll_context(case13)" * doctest::test_suite("unroll_context"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto a = ctx.ones(shape);
    NMTOOLS_ASSERT_CLOSE( a, nm::ones(shape,nm::float32) );
}

TEST_CASE("unroll_context(case14)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto result = ctx.create(nm::float32,shape);
    ctx.eval(result,view::ones(shape,nm::float32));

    NMTOOLS_ASSERT_CLOSE( result, nm::ones(shape,nm::float32) );
}

TEST_CASE("unroll_context(case15)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto result = ctx.eval(view::ones(shape,nm::float32));

    NMTOOLS_ASSERT_CLOSE( result, nm::ones(shape,nm::float32) );
}

TEST_CASE("unroll_context(case16)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto result = ctx.eval(view::zeros(shape,nm::float32));

    NMTOOLS_ASSERT_CLOSE( result, nm::zeros(shape,nm::float32) );
}

TEST_CASE("unroll_context(case17)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<4>>;
    auto shape = shape_t{};

    auto result = ctx.eval(view::full(shape, 3.0f));

    static_assert( nm::is_ndarray_v<decltype(result)> );
}

TEST_CASE("unroll_context(case18)" * doctest::test_suite("eval"))
{
    auto ctx = nm::Unroll;

    using shape_t  = nmtools_tuple<nm::ct<2>,nm::ct<3>,nm::ct<4>>;
    auto shape = shape_t{};

    auto result = ctx.eval(view::ones(shape,nm::float32));

    NMTOOLS_ASSERT_CLOSE( result, nm::ones(shape,nm::float32) );
}
