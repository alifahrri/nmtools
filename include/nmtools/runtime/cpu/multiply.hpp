#ifndef NMTOOLS_RUNTIME_CPU_MULTIPLY_HPP
#define NMTOOLS_RUNTIME_CPU_MULTIPLY_HPP

#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/ndarray.hpp"

namespace nmtools::runtime
{
    class cpu_multiply : public base_functor
    {
    public:
        static constexpr auto types = nmtools_tuple{
            nmtools_tuple{float32,float32},
            nmtools_tuple{float32,int32},
            nmtools_tuple{int32,int32},
        };
    private:
        // useful to enable/disable
        DType lhs_dtype;
        DType rhs_dtype;
        nm_size_t hash_ = {};
        Graph graph_;
    public:
        cpu_multiply(DType lhs_dtype, DType rhs_dtype);
        auto operator()(const nmtools_list<ndarray>& operands) -> ndarray override;
        auto graph() const noexcept -> Graph override;
        auto hash() const noexcept -> nm_size_t override;
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_MULTIPLY_IMPLEMENTATION

#include "nmtools/context/default.hpp"
#include "nmtools/kernel/multiply.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"
// TODO: vectorize
#include "nmtools/tilekit/scalar.hpp"

namespace nmtools::runtime
{
    cpu_multiply::cpu_multiply(DType lhs_dtype, DType rhs_dtype)
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
                // runtime::multiply for real operands (shape/address are not hashed)
                auto lhs = ndarray(IndexType{1,1},this->lhs_dtype);
                auto rhs = ndarray(IndexType{1,1},this->rhs_dtype);
                auto v = unwrap(view::multiply(lhs.view(lhs_dtype),rhs.view(rhs_dtype)));
                auto tree = fn::get_computational_tree(v);
                graph_ = rt::to_value(tree);
            }
        });

        // take the gvn hash of the output node
        auto gvn = functional::gvn(graph_,false,false);
        hash_ = gvn.at(output_id(graph_));
    }

    auto cpu_multiply::operator()(const nmtools_list<ndarray>& operands) -> ndarray
    {
        nmtools_panic( operands.size() == 2
            , "invalid number of operand for multiply, expect 2"
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

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto [lhs_dtype,rhs_dtype] = at(types,i);
            if ((lhs_dtype == this->lhs_dtype)
                && (rhs_dtype == this->rhs_dtype)
            ) {
                using namespace literals;
                auto v = unwrap(view::multiply(lhs.view(lhs_dtype),rhs.view(rhs_dtype)));

                auto rtype  = type(v);
                auto result = ndarray(shape(v),rtype);

                // TODO: vectorize
                // TODO: parametrize/specialize tile shape
                auto ctx        = tilekit::Scalar;
                auto padding    = True;
                auto tile_shape = nmtools_tuple{1_ct,4_ct};
                auto output     = result.mutable_view(rtype);

                // TODO: handle broadcast
                kernel::multiply(ctx,output,lhs.view(lhs_dtype),rhs.view(rhs_dtype),tile_shape,padding);
                array = result;
            }
        });

        return array;
    }

    auto cpu_multiply::graph() const noexcept -> Graph
    {
        return graph_;
    }

    auto cpu_multiply::hash() const noexcept -> nm_size_t
    {
        return hash_;
    }
}
#endif // NMTOOLS_RUNTIME_CPU_MULTIPLY_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_CPU_MULTIPLY_HPP