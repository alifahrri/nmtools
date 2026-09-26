#ifndef NMTOOLS_RUNTIME_CPU_SUM_HPP
#define NMTOOLS_RUNTIME_CPU_SUM_HPP

#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/ndarray.hpp"

namespace nmtools::runtime
{
    class cpu_sum : public base_functor
    {
    public:
        static constexpr auto types = nmtools_tuple{
            float32,
            int32
        };
        static constexpr auto input_reduce_pairs = nmtools_tuple{
            nmtools_tuple{ct_v<2>,ct_v<1>,True},
            nmtools_tuple{ct_v<2>,ct_v<1>,False},
            // for 3D with single axis reduction, reshape to 2D (-1,inp_shape[-1])
            nmtools_tuple{ct_v<3>,ct_v<1>,True},
            nmtools_tuple{ct_v<3>,ct_v<1>,False},
        };
    private:
        nm_size_t hash_ = {};
        DType dtype_;
        Graph graph_;
        bool  keepdims_;
    public:
        cpu_sum(DType dtype, bool keepdims);
        auto operator()(const nmtools_list<ndarray>& operands) -> ndarray override;
        auto graph() const noexcept -> Graph override;
        auto hash() const noexcept -> nm_size_t override;
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_SUM_IMPLEMENTATION

#include "nmtools/context/default.hpp"
#include "nmtools/kernel/sum.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"
// TODO: vectorize
#include "nmtools/tilekit/scalar.hpp"
#include "nmtools/index/cast.hpp"

namespace nmtools::runtime
{
    cpu_sum::cpu_sum(DType dtype, bool keepdims)
        : dtype_(dtype)
        , keepdims_(keepdims)
    {
        namespace rt = runtime;
        namespace fn = functional;

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto dtype = at(types,i);

            if (dtype == this->dtype_) {
                // TODO: better initialization
                auto inp = ndarray(IndexType{1,1},dtype);
                auto initial = None;
                // TODO: generalize axis
                auto axis = nm_index_t{-1};
                if (keepdims) {
                    auto keepdims = True;
                    auto view     = unwrap(view::sum(inp.view(dtype),axis,None,initial,keepdims));
                    auto tree = fn::get_computational_tree(view);
                    auto rtree = rt::to_value(tree);
                    graph_    = fn::cse(rtree);
                } else {
                    auto keepdims = False;
                    auto view     = unwrap(view::sum(inp.view(dtype),axis,None,initial,keepdims));
                    auto tree = fn::get_computational_tree(view);
                    auto rtree = rt::to_value(tree);
                    graph_    = fn::cse(rtree);
                }
            }
        });

        auto gvn = fn::gvn(graph_,false,false);
        hash_ = gvn.at(output_id(graph_));
    }

    auto cpu_sum::operator()(const nmtools_list<ndarray>& operands) -> ndarray
    {
        nmtools_panic( operands.size() == 1
            , "invalid number of operand for sum, expect 1"
        );

        auto inp = operands.at(0);

        nmtools_panic( inp.dtype() == dtype_
            , "invalid input type"
        );

        // TODO: make ndarray default constructible
        auto array = ndarray(IndexType{},DType::UNKNOWN);
        auto initial = None;

        using namespace literals;
        // TODO: parametrize tile_shape
        auto tile_shape = tilekit::index(nmtools_tuple{1_ct,4_ct});
        // assume axis=-1
        // TODO: support general axis
        auto axis = nm_index_t{-1};
        auto ctx  = tilekit::Scalar;

        auto evaluated = false;

        constexpr auto N = len_v<decltype(types)>;
        constexpr auto M = len_v<decltype(input_reduce_pairs)>;
        template_for<N>([&](auto i){
            auto dtype = at(types,i);
            if (dtype == this->dtype_) {
                template_for<M>([&](auto j){
                    const auto [input_dims,reduce_dim,keepdims] = at(input_reduce_pairs,j);
                    using inp_shape_t = nmtools_array<nm_index_t,decltype(input_dims)::value>;
                    using k_shape_t   = nmtools_array<nm_index_t,decltype(reduce_dim)::value+1>;
                    if ((inp.dim() == nm_size_t{decltype(input_dims)::value}) && (keepdims == this->keepdims_)) {
                        auto inp_shape = index::cast<inp_shape_t>(inp.shape());
                        auto view      = view::sum(inp.view(dtype,inp_shape),axis,None,initial,keepdims);
                        auto rtype     = type(view);
                        auto out_shape = shape(view);

                        // kernel input follows the reduction dims instead
                        // kernel output dim should be k_inp_shape - reduce_dim
                        // this still hardcoded to 1 axis reduction
                        // TODO: generalize k_inp_shape & k_out_shape inference for N axis reduction
                        auto k_inp_shape = unwrap(index::shape_reshape(inp_shape,k_shape_t{-1,static_cast<nm_index_t>(at(inp_shape,-1))}));
                        auto k_out_shape = nmtools_array{index::product(out_shape)};
                        auto result      = ndarray(k_out_shape,rtype);
                        auto k_output    = result.mutable_view(rtype,k_out_shape);
                        kernel::sum(ctx,k_output,inp.reshape(k_inp_shape).view(dtype,k_inp_shape),tile_shape,-1_ct);
                        array = result.reshape(out_shape);
                        evaluated = true;
                    }
                });
            }
        });

        nmtools_panic( evaluated
            , "can't find kernel for this configuration"
        );

        return array;
    }

    auto cpu_sum::graph() const noexcept -> Graph
    {
        return graph_;
    }

    auto cpu_sum::hash() const noexcept -> nm_size_t
    {
        return hash_;
    }
}

#endif // NMTOOLS_RUNTIME_CPU_SUM_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_CPU_SUM_HPP