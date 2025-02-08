#include "nmtools/core/combinator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/var.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace cb = nmtools::combinator;
namespace view = nmtools::view;

using nmtools_array, nmtools::unwrap;

TEST_CASE("composition(case1)" * doctest::test_suite("combinator"))
{
    auto f1 = cb::dup;
    NMTOOLS_ASSERT_EQUAL( f1.arity, 1 );
    NMTOOLS_ASSERT_EQUAL( f1.n_outputs, 2 );

    auto f2 = fn::sum[0] * cb::dup;
    NMTOOLS_ASSERT_EQUAL( fn::sum[0].arity, 1 );
    NMTOOLS_ASSERT_EQUAL( f2.arity, 1 );
    NMTOOLS_ASSERT_EQUAL( f2.n_outputs, 2 );
}

TEST_CASE("composition(case2)" * doctest::test_suite("combinator"))
{
    auto f = fn::sum[0] * cb::bury2 * cb::dup;
    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 3 );
}

TEST_CASE("composition(case3)" * doctest::test_suite("combinator"))
{
    auto f = fn::divide * fn::sum[0] * cb::bury2 * cb::dup;
    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 2 );
}

// var
TEST_CASE("composition(case1a)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( cb::dup.arity, 1 );
    NMTOOLS_ASSERT_EQUAL( cb::bury2.arity, 3 );
    NMTOOLS_ASSERT_EQUAL( cb::dup.n_outputs, 2 );
    NMTOOLS_ASSERT_EQUAL( cb::bury2.n_outputs, 3 );

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 3 );

    auto result = fn::apply(f,nmtools_tuple{&input,4});
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(result)>, 3 );
}

TEST_CASE("composition(case1b)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::sum[0] * cb::bury2;
    NMTOOLS_ASSERT_EQUAL( f.arity, 3 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 3 );

    [[maybe_unused]]
    auto result = fn::apply(f,nmtools_tuple{&input,&input,4});
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(result)>, 3 );
    auto expected = fn::sum[0](&input);
    auto sum_result = nmtools::get<0>(result);
    NMTOOLS_ASSERT_CLOSE( sum_result, expected );
}

TEST_CASE("composition(case1c)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 3 );

    [[maybe_unused]]
    auto result = fn::apply(f,nmtools_tuple{&input,4});
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(result)>, 3 );
    auto expected = fn::sum[0](&input);
    auto sum_result = nmtools::get<0>(result);
    NMTOOLS_ASSERT_CLOSE( sum_result, expected );
}

TEST_CASE("composition(case1d)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::divide * fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 2 );

    auto result = fn::apply(f,nmtools_tuple{&input,4});
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(result)>, 2 );

    auto expected = (fn::divide * fn::sum[0]) (&input) (4);

    auto fst_result = nmtools::get<0>(result);
    NMTOOLS_ASSERT_CLOSE( fst_result, expected );

    auto snd_result = nmtools::get<1>(result);
    NMTOOLS_ASSERT_CLOSE( *snd_result, input );
}

TEST_CASE("composition(case1e)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = cb::swap * fn::divide * fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 2 );

    auto result = fn::apply(f,nmtools_tuple{&input,4});
    NMTOOLS_ASSERT_EQUAL( meta::len_v<decltype(unwrap(result))>, 2 );

    auto expected = (fn::divide * fn::sum[0]) (&input) (4);

    auto fst_result = nmtools::get<0>(unwrap(result));
    NMTOOLS_ASSERT_CLOSE( *fst_result, input );

    auto snd_result = nmtools::get<1>(unwrap(result));
    NMTOOLS_ASSERT_CLOSE( snd_result, expected );

    CHECK( meta::is_tuple_v<decltype(unwrap(result))> );
}

TEST_CASE("composition(case1f)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::subtract * cb::swap * fn::divide * fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 1 );

    [[maybe_unused]]
    auto result = fn::apply(f,nmtools_tuple{&input,4});

    // auto expected = (fn::subtract * cb::swap * fn::divide * fn::sum[0]) (&input) (4) (&input);
    auto t0 = view::sum(input,0);
    auto t1 = view::divide(t0,4);
    auto t2 = view::subtract(input,t1);
    auto expected = t2;

    NMTOOLS_ASSERT_CLOSE( result, expected );
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, decltype(unwrap(result)) );
}

TEST_CASE("composition(case1g)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::fabs * fn::subtract * cb::swap * fn::divide * fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 1 );

    [[maybe_unused]]
    auto result = fn::apply(f,nmtools_tuple{&input,4});

    auto t0 = view::sum(input,0);
    auto t1 = view::divide(t0,4);
    auto t2 = view::subtract(input,t1);
    auto t3 = view::fabs(t2);
    auto expected = t3;

    NMTOOLS_ASSERT_CLOSE( result, expected );
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, decltype(unwrap(result)) );
}

TEST_CASE("composition(case1h)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::square * fn::fabs * fn::subtract * cb::swap * fn::divide * fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 1 );

    [[maybe_unused]]
    auto result = fn::apply(f,nmtools_tuple{&input,4});

    auto t0 = view::sum(input,0);
    auto t1 = view::divide(t0,4);
    auto t2 = view::subtract(input,t1);
    auto t3 = view::fabs(t2);
    auto t4 = view::square(t3);
    auto expected = t4;

    NMTOOLS_ASSERT_CLOSE( result, expected );
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, decltype(unwrap(result)) );
}

TEST_CASE("composition(case1i)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::sum[1] * fn::square * fn::fabs * fn::subtract * cb::swap * fn::divide * fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 2 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 1 );

    [[maybe_unused]]
    auto result = fn::apply(f,nmtools_tuple{&input,4});

    auto t0 = view::sum(input,0);
    auto t1 = view::divide(t0,4);
    auto t2 = view::subtract(input,t1);
    auto t3 = view::fabs(t2);
    auto t4 = view::square(t3);
    auto t5 = view::sum(t4,1);
    auto expected = t5;

    NMTOOLS_ASSERT_CLOSE( result, expected );
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, decltype(unwrap(result)) );
}

TEST_CASE("composition(case1j)" * doctest::test_suite("combinator"))
{
    auto input_shape = array{3,4};
    auto input = unwrap(na::reshape(na::arange(ix::product(input_shape)),input_shape));

    auto f = fn::divide * fn::sum[1] * fn::square * fn::fabs * fn::subtract * cb::swap * fn::divide * fn::sum[0] * cb::bury2 * cb::dup;

    NMTOOLS_ASSERT_EQUAL( f.arity, 3 );
    NMTOOLS_ASSERT_EQUAL( f.n_outputs, 1 );

    [[maybe_unused]]
    auto result = fn::apply(f,nmtools_tuple{&input,4,3});

    auto t0 = view::sum(input,0);
    auto t1 = view::divide(t0,4);
    auto t2 = view::subtract(input,t1);
    auto t3 = view::fabs(t2);
    auto t4 = view::square(t3);
    auto t5 = view::sum(t4,1);
    auto t6 = view::divide(t5,3);
    auto expected = t6;

    NMTOOLS_ASSERT_CLOSE( result, expected );
    NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, decltype(unwrap(result)) );
}