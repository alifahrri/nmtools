#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/array/tile.hpp"
#include "nmtools/array/transpose.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/var.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace utl = nmtools::utl;
namespace utils = nmtools::utils;
namespace utility = nmtools::utility;

using namespace nmtools::literals;

using nmtools_array, nmtools_tuple, nmtools::unwrap;

// matmul
TEST_CASE("linearize(case1a)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::unwrap(na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape));
    auto rhs = nm::unwrap(na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape));

    auto res = view::matmulv2(lhs,rhs);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

// softmax
TEST_CASE("linearize(case2a)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

    auto axis = -1;

    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}

// var
TEST_CASE("linearize(case3a)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

    auto axis = -1;

    auto res = view::var(unwrap(input),axis);

    auto graph = fn::get_compute_graph(unwrap(res));

    auto result = fn::linearize(graph);

    // TODO: compare graph

    CHECK_MESSAGE( true, utils::to_string(result,utils::Graphviz) );
}


TEST_CASE("apply_graph(case1a)" * doctest::test_suite("functional"))
{
    auto lhs_shape = array{3,4};
    auto rhs_shape = array{4,3};

    auto lhs = nm::unwrap(na::reshape(na::arange(ix::product(lhs_shape)),lhs_shape));
    auto rhs = nm::unwrap(na::reshape(na::arange(ix::product(rhs_shape)),rhs_shape));

    auto res = view::matmulv2(lhs,rhs);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));

    auto function = fn::get_function(graph);
    auto operands = fn::get_operands(graph);

    auto f = function.functor;
    static_assert( meta::len_v<decltype(operands)> == 2 );

    auto result = fn::apply(f,operands);

    auto expected = res;

    NMTOOLS_ASSERT_EQUAL( decltype(f)::arity, 2 );
    NMTOOLS_ASSERT_CLOSE( result, expected );
}

#if 0
TEST_CASE("apply_graph(case2a)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

    auto axis = -1;
    auto res = view::softmax(unwrap(input),axis);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));

    auto function = fn::get_function(graph);
    auto operands = fn::get_operands(graph);

    auto f = function.functor;

    // auto result = fn::apply(function.functor,operands);

    auto expected = res;

    static_assert( meta::len_v<decltype(operands)> == 1 );
    NMTOOLS_ASSERT_EQUAL( decltype(f)::arity, 1 );

    // NMTOOLS_ASSERT_CLOSE( result, expected );
}
#endif

#if 0
TEST_CASE("apply_graph(case3a)" * doctest::test_suite("functional"))
{
    auto input_shape = array{3,4};
    auto input = na::reshape(na::arange(ix::product(input_shape)),input_shape);

    auto axis = -1;
    auto res = view::var(unwrap(input),axis);

    auto graph = fn::linearize(fn::get_compute_graph(unwrap(res)));

    auto function = fn::get_function(graph);
    auto operands = fn::get_operands(graph);

    auto f = function.functor;

    auto result = fn::apply(function.functor,operands);

    auto expected = res;

    // static_assert( meta::len_v<decltype(operands)> == 1 );
    // NMTOOLS_ASSERT_EQUAL( decltype(f)::arity, 1 );

    NMTOOLS_ASSERT_CLOSE( result, expected );
}
#endif