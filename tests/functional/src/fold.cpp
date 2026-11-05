#include "nmtools/core/fold.hpp"
#include "nmtools/core/function_composition.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufuncs/cos.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/tanh.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/context/gpu.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm  = nmtools;
namespace na  = nmtools;
namespace fn  = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

using nmtools::unwrap;
using nmtools::None;
using nmtools::True;

using namespace nm::literals;


TEST_CASE("fold(multiply)" * doctest::test_suite("functional::fold"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto y = view::multiply(lhs_array,rhs_array);

    auto folded = nm::unwrap(fn::fold(y));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    // single ufunc over two leaves: function is the ufunc functor alone,
    // identical to what the (proven) composition path derives
    auto expect_function = nm::unwrap(fn::get_function_composition(y));
    NMTOOLS_ASSERT_EQUAL( function, expect_function );

    // two leaves, arrays kept as the wrapped pointers (device operand contract)
    CHECK_MESSAGE( nm::len(operands) == 2, "\nprogram: " << utils::to_string(function,utils::Compact) );
    CHECK( nmtools::at(operands,0_ct) == &*lhs_array );
    CHECK( nmtools::at(operands,1_ct) == &*rhs_array );

    // applying the folded program rebuilds the (lazy) view expression
    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), y );
}

TEST_CASE("fold(exp)" * doctest::test_suite("functional::fold"))
{
    // minimal chain: single unary over a leaf
    auto shape  = nmtools_array{3,4};
    auto buffer = na::arange(12);
    auto a      = na::reshape(buffer,shape);

    auto y = view::exp(a);

    auto folded   = nm::unwrap(fn::fold(y));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    CHECK_MESSAGE( nm::len(operands) == 1, "\nprogram: " << utils::to_string(function,utils::Compact) );
    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), y );
}

TEST_CASE("fold(multiply_tanh)" * doctest::test_suite("functional::fold"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto x = view::multiply(lhs_array,rhs_array);
    auto y = view::tanh(x);

    auto folded = nm::unwrap(fn::fold(y));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    // chain: structural parity with the proven composition path
    NMTOOLS_ASSERT_EQUAL( function, nm::unwrap(fn::get_function_composition(y)) );
    CHECK_MESSAGE( nm::len(operands) == 2, "\nprogram: " << utils::to_string(function,utils::Compact) );

    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), y );
}

TEST_CASE("fold(softmax)" * doctest::test_suite("functional::fold"))
{
    // softmax-shaped tree: divide(exp(sub(m,lhs)), reduce_add(exp(sub(m,lhs))))
    // - two view operands on the root (the bury path)
    // - the exp-sub-reduce_max subtree appears twice (no dedup, behavior-preserving)
    // - an aliased operand (transparent decorator)
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);
    auto lhs        = view::alias(lhs_array,0_ct);

    auto axis = 0;

    auto m = nm::unwrap(view::reduce_maximum(lhs,axis,None,None,True));
    auto b = view::subtract(m,lhs);
    auto c = view::exp(b);
    auto d = nm::unwrap(view::reduce_add(c,axis,None,None,True));
    auto e = view::divide(c,d);

    auto folded = nm::unwrap(fn::fold(e));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    // leaves: the aliased array, collected once per syntactic occurrence
    // (d's subtree: max+sub leaves; c's subtree: max+sub leaves) => 4 occurrences
    CHECK_MESSAGE( nm::len(operands) == 4, "\nprogram: " << utils::to_string(function,utils::Compact) );
    // the aliased array is peeled to the wrapped pointer (device operand contract)
    CHECK( nmtools::at(operands,0_ct) == &*lhs_array );

    // arity of the program must match the collected leaves
    using function_t = nm::remove_cvref_t<decltype(function)>;
    static_assert( function_t::arity == 4 );
    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), e );
}

TEST_CASE("fold(shared_operand)" * doctest::test_suite("functional::fold"))
{
    auto shape  = nmtools_array{3,4};
    auto buffer = na::arange(12);
    auto x      = na::reshape(buffer,shape);

    // both operands are view subtrees sharing the leaf x
    auto y = view::add(view::cos(x),view::cos(x));

    auto folded = nm::unwrap(fn::fold(y));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    CHECK_MESSAGE( nm::len(operands) == 2, "\nprogram: " << utils::to_string(function,utils::Compact) );

    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), y );
}

TEST_CASE("fold(leaf_first)" * doctest::test_suite("functional::fold"))
{
    // direct leaf at operand position 0, view subtree at position 1
    // (exercises bury for a leaf that must end up above the sub-result)
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{3,4};
    auto rhs_buffer = na::arange(12);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto y = view::subtract(lhs_array,view::exp(rhs_array));

    auto folded = nm::unwrap(fn::fold(y));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    CHECK_MESSAGE( nm::len(operands) == 2, "\nprogram: " << utils::to_string(function,utils::Compact) );

    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), y );
}

TEST_CASE("fold(scalar_operand)" * doctest::test_suite("functional::fold"))
{
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto y = view::multiply(lhs_array,3);

    auto folded = nm::unwrap(fn::fold(y));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    CHECK_MESSAGE( nm::len(operands) == 2, "\nprogram: " << utils::to_string(function,utils::Compact) );

    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), y );
}

TEST_CASE("fold(broadcast_wrapper)" * doctest::test_suite("functional::fold"))
{
    // broadcast_to wrappers are transparent: the ufunc fmap broadcasts internally
    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto y = view::multiply(view::broadcast_to(rhs_array,lhs_shape),lhs_array);

    auto folded = nm::unwrap(fn::fold(y));
    auto function = nmtools::at(folded,meta::ct_v<0>);
    auto operands = nmtools::at(folded,meta::ct_v<1>);

    // the broadcast wrapper is peeled: leaves are the raw arrays
    CHECK_MESSAGE( nm::len(operands) == 2, "\nprogram: " << utils::to_string(function,utils::Compact) );
    CHECK( nmtools::at(operands,0_ct) == &*rhs_array );

    NMTOOLS_ASSERT_CLOSE( fn::apply(function,operands), y );
}

TEST_CASE("fold_operand(state)" * doctest::test_suite("functional::fold"))
{
    // unit test for the state threading in detail::fold_operand: one step per
    // branch, checking every slot after each step. the state is the accumulator
    // threaded by fold_view, a flat tuple:
    // 0. compositions, 1. sub_leaves, 2. depths, 3. direct_leaves, 4. n_leaves
    //
    // operands are fed the way fold_view feeds them: arrays as wrapped pointers,
    // views unwrapped (view ctors return maybes, so unwrap the calls below).

    auto lhs_shape  = nmtools_array{3,4};
    auto lhs_buffer = na::arange(12);
    auto lhs_array  = na::reshape(lhs_buffer,lhs_shape);

    auto rhs_shape  = nmtools_array{4};
    auto rhs_buffer = na::arange(4);
    auto rhs_array  = na::reshape(rhs_buffer,rhs_shape);

    auto state0 = nmtools_tuple{
        nmtools_tuple{}, nmtools_tuple{}, nmtools_tuple{}, nmtools_tuple{}
        , meta::ct_v<0>
    };

    // -- direct leaf: the wrapped array is collected as-is, counter untouched
    auto state1 = fn::detail::fold_operand(state0,&*rhs_array);
    CHECK( nm::len(nmtools::get<0>(state1)) == 0 );
    CHECK( nm::len(nmtools::get<1>(state1)) == 0 );
    CHECK( nm::len(nmtools::get<2>(state1)) == 0 );
    CHECK( nm::len(nmtools::get<3>(state1)) == 1 );
    CHECK( nmtools::get<0>(nmtools::get<3>(state1)) == &*rhs_array );
    static_assert( nm::remove_cvref_t<decltype(nmtools::get<4>(state1))>::value == 0 );

    // -- broadcast wrapper: transparent, peeled to the wrapped pointer
    auto state2 = fn::detail::fold_operand(state1
        , nm::unwrap(view::broadcast_to(rhs_array,lhs_shape)) );
    CHECK( nm::len(nmtools::get<0>(state2)) == 0 );
    CHECK( nm::len(nmtools::get<1>(state2)) == 0 );
    CHECK( nm::len(nmtools::get<2>(state2)) == 0 );
    CHECK( nm::len(nmtools::get<3>(state2)) == 2 );
    CHECK( nmtools::get<1>(nmtools::get<3>(state2)) == &*rhs_array );
    static_assert( nm::remove_cvref_t<decltype(nmtools::get<4>(state2))>::value == 0 );

    // -- alias: transparent, the aliased array is collected as a leaf
    auto state3 = fn::detail::fold_operand(state2
        , nm::unwrap(view::alias(rhs_array,0_ct)) );
    CHECK( nm::len(nmtools::get<0>(state3)) == 0 );
    CHECK( nm::len(nmtools::get<1>(state3)) == 0 );
    CHECK( nm::len(nmtools::get<2>(state3)) == 0 );
    CHECK( nm::len(nmtools::get<3>(state3)) == 3 );
    CHECK( nmtools::get<2>(nmtools::get<3>(state3)) == &*rhs_array );
    static_assert( nm::remove_cvref_t<decltype(nmtools::get<4>(state3))>::value == 0 );

    // -- view operand: subtree program + leaves + bury depth parked, one each;
    //    depth = leaves collected so far (they apply above the sub-result),
    //    counter advances by the subtree's leaf count
    auto sub    = nm::unwrap(view::exp(lhs_array));
    auto state4 = fn::detail::fold_operand(state3,sub);
    CHECK( nm::len(nmtools::get<0>(state4)) == 1 );
    CHECK( nm::len(nmtools::get<1>(state4)) == 1 );
    CHECK( nm::len(nmtools::get<2>(state4)) == 1 );
    static_assert( nm::remove_cvref_t<decltype(nmtools::get<0>(nmtools::get<2>(state4)))>::value == 3 );
    static_assert( nm::remove_cvref_t<decltype(nmtools::get<4>(state4))>::value == 1 );
    // the parked program is the subtree's own function composition
    auto expected_sub_fn = nm::unwrap(fn::get_function_composition(sub));
    NMTOOLS_ASSERT_EQUAL( nmtools::get<0>(nmtools::get<0>(state4)), expected_sub_fn );
    // the parked leaves are the subtree's leaves
    auto sub_leaves = nmtools::get<0>(nmtools::get<1>(state4));
    CHECK( nm::len(sub_leaves) == 1 );
    CHECK( nmtools::get<0>(sub_leaves) == &*lhs_array );
}