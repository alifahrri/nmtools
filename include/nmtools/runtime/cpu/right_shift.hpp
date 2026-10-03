#ifndef NMTOOLS_RUNTIME_CPU_RIGHT_SHIFT_HPP
#define NMTOOLS_RUNTIME_CPU_RIGHT_SHIFT_HPP

#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/ndarray.hpp"

namespace nmtools::runtime
{
    class cpu_right_shift : public base_functor
    {
    public:
        // NOTE: left shift is only valid for integer operands,
        // so unlike fmax/fmin only int32 is registered here.
        // The outer tuple type is written explicitly to avoid CTAD flattening
        // a single nested tuple into the outer tuple.
        static constexpr auto types = nmtools_tuple<nmtools_tuple<decltype(int32),decltype(int32)>>{
            nmtools_tuple{int32,int32},
        };
    private:
        // useful to enable/disable
        DType lhs_dtype;
        DType rhs_dtype;
        nm_size_t hash_ = {};
        Graph graph_;
    public:
        cpu_right_shift(DType lhs_dtype, DType rhs_dtype);
        auto operator()(const nmtools_list<ndarray>& operands) -> ndarray override;
        auto graph() const noexcept -> Graph override;
        auto hash() const noexcept -> nm_size_t override;
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_RIGHT_SHIFT_IMPLEMENTATION

#include "nmtools/context/default.hpp"
#include "nmtools/kernel/ufuncs/binary.hpp"
#include "nmtools/array/ufuncs/right_shift.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"
// TODO: vectorize
#include "nmtools/tilekit/scalar.hpp"

namespace nmtools::runtime
{
    cpu_right_shift::cpu_right_shift(DType lhs_dtype, DType rhs_dtype)
        : lhs_dtype(lhs_dtype)
        , rhs_dtype(rhs_dtype)
    {
        // TODO: initialize graph and hash
        // TODO: check if lhs_dtype and rhs_dtype is in the allowed types

        namespace rt = runtime;
        namespace fn = functional;

        // NOTE: what available from runtime description may not be available/enabled for eval context
        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto [lhs_dtype,rhs_dtype] = at(types,i);

            auto lhs_rtype = to_value_v<decltype(lhs_dtype)>;
            auto rhs_rtype = to_value_v<decltype(rhs_dtype)>;

            if ((lhs_rtype == this->lhs_dtype) && (rhs_rtype == this->rhs_dtype)) {
                // NOTE: build the graph from dummy ndarray views so node attributes
                // (e.g. "op", "indexer") are preserved, matching the graph built by
                // runtime::right_shift for real operands (shape/address are not hashed)
                auto lhs = ndarray(IndexType{1,1},this->lhs_dtype);
                auto rhs = ndarray(IndexType{1,1},this->rhs_dtype);
                auto v = unwrap(view::right_shift(lhs.view(lhs_dtype),rhs.view(rhs_dtype)));
                auto tree = fn::get_computational_tree(v);
                graph_ = rt::to_value(tree);
            }
        });

        // take the gvn hash of the output node
        auto gvn = functional::gvn(graph_,false,false);
        hash_ = gvn.at(output_id(graph_));
    }

    auto cpu_right_shift::operator()(const nmtools_list<ndarray>& operands) -> ndarray
    {
        nmtools_panic( operands.size() == 2
            , "invalid number of operand for right_shift, expect 2"
        );

        auto lhs = operands.at(0);
        auto rhs = operands.at(1);

        // should not happened
        nmtools_panic( lhs.dtype() == lhs_dtype
            , "invalid lhs type"
        );
        nmtools_panic( rhs.dtype() == rhs_dtype
            , "invalid rhs type"
        );

        auto array = ndarray(IndexType{},DType::UNKNOWN);

        auto right_shift = kernel::binary_t<view::right_shift_t<>>{};

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto [lhs_dtype,rhs_dtype] = at(types,i);
            if ((lhs_dtype == this->lhs_dtype)
                && (rhs_dtype == this->rhs_dtype)
            ) {
                using namespace literals;
                auto v = unwrap(view::right_shift(lhs.view(lhs_dtype),rhs.view(rhs_dtype)));

                auto rtype  = type(v);
                auto result = ndarray(shape(v),rtype);

                // TODO: vectorize
                // TODO: parametrize/specialize tile shape
                auto ctx        = tilekit::Scalar;
                auto padding    = True;
                auto tile_shape = nmtools_tuple{1_ct,4_ct};
                auto output     = result.mutable_view(rtype);

                // TODO: handle broadcast
                right_shift(ctx,output,lhs.view(lhs_dtype),rhs.view(rhs_dtype),tile_shape,padding);
                array = result;
            }
        });

        return array;
    }

    auto cpu_right_shift::graph() const noexcept -> Graph
    {
        return graph_;
    }

    auto cpu_right_shift::hash() const noexcept -> nm_size_t
    {
        return hash_;
    }
}
#endif // NMTOOLS_RUNTIME_CPU_RIGHT_SHIFT_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_CPU_RIGHT_SHIFT_HPP
