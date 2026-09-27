#ifndef NMTOOLS_RUNTIME_CPU_EXP_HPP
#define NMTOOLS_RUNTIME_CPU_EXP_HPP

#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/ndarray.hpp"

namespace nmtools::runtime
{
    class cpu_exp : public base_functor
    {
    public:
        static constexpr auto types = nmtools_tuple{
            float32
        };
    private:
        DType dtype_;
        nm_size_t hash_ = {};
        Graph graph_;
    public:
        cpu_exp(DType dtype);
        auto operator()(const nmtools_list<ndarray>& operands) -> ndarray override;
        auto graph() const noexcept -> Graph override;
        auto hash() const noexcept -> nm_size_t override;
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_EXP_IMPLEMENTATION

#include "nmtools/context/default.hpp"
#include "nmtools/kernel/ufuncs/unary.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"
// TODO: vectorize
#include "nmtools/tilekit/scalar.hpp"

namespace nmtools::runtime
{
    cpu_exp::cpu_exp(DType dtype)
        : dtype_(dtype)
    {
        namespace rt = runtime;
        namespace fn = functional;

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto dtype = at(types,i);

            if (dtype == this->dtype_) {
                // dim/shape & address are not hashed
                auto input = ndarray(IndexType{1,1},dtype);
                auto v = unwrap(view::exp(input.view(dtype)));
                auto tree = fn::get_computational_tree(v);
                graph_ = rt::to_value(tree);
            }
        });

        auto gvn = functional::gvn(graph_,false,false);
        hash_ = gvn.at(output_id(graph_));
    }

    auto cpu_exp::operator()(const nmtools_list<ndarray>& operands) -> ndarray
    {
        nmtools_panic( operands.size() == 1
            , "invalid number of operand for exp, expect 1"
        );

        auto input = operands.at(0);

        nmtools_panic( input.dtype() == dtype_
            , "invalid input type"
        );

        // TODO: default constructor
        auto array = ndarray(IndexType{},DType::UNKNOWN);

        auto exp = kernel::unary_t<view::exp_t>{};

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto dtype = at(types,i);
            if (dtype == input.dtype()) {
                using namespace literals;

                auto v = unwrap(view::exp(input.view(dtype)));

                auto rtype = type(v);
                auto result = ndarray(shape(v),rtype);

                auto ctx        = tilekit::Scalar;
                auto tile_shape = nmtools_tuple{1_ct,4_ct};
                auto output     = result.mutable_view(rtype);
                // auto padding    = True;

                exp(ctx,output,input.view(dtype),tile_shape);

                array = result;
            }
        });

        return array;
    }

    auto cpu_exp::graph() const noexcept -> Graph
    {
        return graph_;
    }

    auto cpu_exp::hash() const noexcept -> nm_size_t
    {
        return hash_;
    }
}

#endif // NMTOOLS_RUNTIME_CPU_EXP_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_CPU_EXP_HPP
