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
    using function_t = meta::remove_cvref_t<decltype(function)>;
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

// ============================================================================
// mock GPU context: exercise the switched `gpu_base_context_t::eval` (fold
// based) end-to-end on the host. "Device arrays" are plain host arrays, the
// mapped program materializes lazily like `fn::apply`.
// ============================================================================


struct mock_gpu_context_t
    : nmtools::base_context_t<mock_gpu_context_t>
    , nmtools::gpu_base_context_t<mock_gpu_context_t>
{
    using gpu_base_type = nmtools::gpu_base_context_t<mock_gpu_context_t>;
    using gpu_base_type::create_buffer;
    using gpu_base_type::run;
    using gpu_base_type::eval;

    // "device arrays" are plain host arrays
    template <typename array_t>
    auto create_array(const array_t& array) const
    {
        return array;
    }

    template <typename T, typename shape_t, typename size_type>
    auto create(nmtools::dtype_t<T>, const shape_t&, size_type) const
    {
        return nmtools::dynamic_ndarray<T>{};
    }

    // apply the (mapped) program to the device operands, materialize on "device".
    // all operands are passed at once (as the device kernel does): the composition
    // is a stack machine whose intermediate states hold maybe-wrapped views, and
    // partial (one-by-one) application would surface them as maybe-wrapped curried
    // compositions which can't be called further.
    template <typename output_t, typename functor_t, typename operands_t, nm_size_t...Is>
    auto run_(output_t& output, const functor_t& fn, const operands_t& operands, meta::index_sequence<Is...>) const
    {
        auto default_ctx = nmtools::default_context_t<true,false,false>{};
        auto program_result = fn(nmtools::get<Is>(operands)...);
        // the program result may be maybe-wrapped (view ctors return maybes);
        // the default context's eval handles maybe-wrapped views, evaluating
        // to a maybe-wrapped result
        auto eval_result = nm::eval(program_result,default_ctx);
        using element_t = typename output_t::value_type;
        if constexpr (meta::is_maybe_v<meta::remove_cvref_t<decltype(eval_result)>>) {
            output = nmtools::dynamic_ndarray<element_t>(nm::unwrap(eval_result));
        } else {
            output = nmtools::dynamic_ndarray<element_t>(eval_result);
        }
    }
};

TEST_CASE("fold(gpu_eval_mock)" * doctest::test_suite("functional::fold"))
{
    // softmax-shaped expression, same as fold(softmax)
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

    // the switched gpu eval path, exercised end-to-end on host
    auto mock_ctx = mock_gpu_context_t{};
    auto result   = nm::eval(e,mock_ctx);

    // compare against the default (CPU) context
    auto default_ctx = nmtools::default_context_t<true,false,false>{};
    auto expect      = nm::eval(e,default_ctx);

    NMTOOLS_ASSERT_CLOSE( result, expect );
}
