#ifndef NMTOOLS_RUNTIME_CPU_BITWISE_AND_HPP
#define NMTOOLS_RUNTIME_CPU_BITWISE_AND_HPP

#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/ndarray.hpp"

namespace nmtools::runtime
{
    class cpu_bitwise_and : public base_functor
    {
    public:
        static constexpr auto types = nmtools_tuple<nmtools_tuple<decltype(int32),decltype(int32)>>{
            nmtools_tuple{int32,int32},
        };
    private:
        DType lhs_dtype;
        DType rhs_dtype;
        nm_size_t hash_ = {};
        Graph graph_;
    public:
        cpu_bitwise_and(DType lhs_dtype, DType rhs_dtype);
        auto operator()(const nmtools_list<ndarray>& operands) -> ndarray override;
        auto graph() const noexcept -> Graph override;
        auto hash() const noexcept -> nm_size_t override;
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_BITWISE_AND_IMPLEMENTATION

#include "nmtools/context/default.hpp"
#include "nmtools/kernel/ufuncs/binary.hpp"
#include "nmtools/array/ufuncs/bitwise_and.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"
#include "nmtools/tilekit/scalar.hpp"

namespace nmtools::runtime
{
    cpu_bitwise_and::cpu_bitwise_and(DType lhs_dtype, DType rhs_dtype)
        : lhs_dtype(lhs_dtype)
        , rhs_dtype(rhs_dtype)
    {
        namespace rt = runtime;
        namespace fn = functional;

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto [lhs_dtype,rhs_dtype] = at(types,i);

            auto lhs_rtype = to_value_v<decltype(lhs_dtype)>;
            auto rhs_rtype = to_value_v<decltype(rhs_dtype)>;

            if ((lhs_rtype == this->lhs_dtype) && (rhs_rtype == this->rhs_dtype)) {
                auto lhs = ndarray(IndexType{1,1},this->lhs_dtype);
                auto rhs = ndarray(IndexType{1,1},this->rhs_dtype);
                auto v = unwrap(view::bitwise_and(lhs.view(lhs_dtype),rhs.view(rhs_dtype)));
                auto tree = fn::get_computational_tree(v);
                graph_ = rt::to_value(tree);
            }
        });

        auto gvn = functional::gvn(graph_,false,false);
        hash_ = gvn.at(output_id(graph_));
    }

    auto cpu_bitwise_and::operator()(const nmtools_list<ndarray>& operands) -> ndarray
    {
        nmtools_panic( operands.size() == 2
            , "invalid number of operand for bitwise_and, expect 2"
        );

        auto lhs = operands.at(0);
        auto rhs = operands.at(1);

        nmtools_panic( lhs.dtype() == lhs_dtype
            , "invalid lhs type"
        );
        nmtools_panic( rhs.dtype() == rhs_dtype
            , "invalid rhs type"
        );

        auto array = ndarray(IndexType{},DType::UNKNOWN);

        auto bitwise_and = kernel::binary_t<view::bitwise_and_t>{};

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto [lhs_dtype,rhs_dtype] = at(types,i);
            if ((lhs_dtype == this->lhs_dtype)
                && (rhs_dtype == this->rhs_dtype)
            ) {
                using namespace literals;
                auto v = unwrap(view::bitwise_and(lhs.view(lhs_dtype),rhs.view(rhs_dtype)));

                auto rtype  = type(v);
                auto result = ndarray(shape(v),rtype);

                auto ctx        = tilekit::Scalar;
                auto padding    = True;
                auto tile_shape = nmtools_tuple{1_ct,4_ct};
                auto output     = result.mutable_view(rtype);

                bitwise_and(ctx,output,lhs.view(lhs_dtype),rhs.view(rhs_dtype),tile_shape,padding);
                array = result;
            }
        });

        return array;
    }

    auto cpu_bitwise_and::graph() const noexcept -> Graph
    {
        return graph_;
    }

    auto cpu_bitwise_and::hash() const noexcept -> nm_size_t
    {
        return hash_;
    }
}
#endif // NMTOOLS_RUNTIME_CPU_BITWISE_AND_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_CPU_BITWISE_AND_HPP
