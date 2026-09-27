#ifndef NMTOOLS_RUNTIME_CPU_CBRT_HPP
#define NMTOOLS_RUNTIME_CPU_CBRT_HPP

#include "nmtools/runtime/context.hpp"
#include "nmtools/runtime/ndarray.hpp"
#include "nmtools/array/ufuncs/cbrt.hpp"

namespace nmtools::runtime
{
    class cpu_cbrt : public base_functor
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
        cpu_cbrt(DType dtype);
        auto operator()(const nmtools_list<ndarray>& operands) -> ndarray override;
        auto graph() const noexcept -> Graph override;
        auto hash() const noexcept -> nm_size_t override;
    };
}

#ifdef NMTOOLS_RUNTIME_CPU_CBRT_IMPLEMENTATION

#include "nmtools/context/default.hpp"
#include "nmtools/kernel/ufuncs/unary.hpp"
#include "nmtools/core/computational_graph.hpp"
#include "nmtools/core/computational_tree.hpp"
#include "nmtools/core/transform/cse.hpp"
// TODO: vectorize
#include "nmtools/tilekit/scalar.hpp"

namespace nmtools::runtime
{
    cpu_cbrt::cpu_cbrt(DType dtype)
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
                auto v = unwrap(view::cbrt(input.view(dtype)));
                auto tree = fn::get_computational_tree(v);
                graph_ = rt::to_value(tree);
            }
        });

        auto gvn = functional::gvn(graph_,false,false);
        hash_ = gvn.at(output_id(graph_));
    }

    auto cpu_cbrt::operator()(const nmtools_list<ndarray>& operands) -> ndarray
    {
        nmtools_panic( operands.size() == 1
            , "invalid number of operand for cbrt, expect 1"
        );

        auto input = operands.at(0);

        nmtools_panic( input.dtype() == dtype_
            , "invalid input type"
        );

        // TODO: default constructor
        auto array = ndarray(IndexType{},DType::UNKNOWN);

        auto cbrt = kernel::unary_t<view::cbrt_t>{};

        constexpr auto N = len_v<decltype(types)>;
        template_for<N>([&](auto i){
            const auto dtype = at(types,i);
            if (dtype == input.dtype()) {
                using namespace literals;

                auto v = unwrap(view::cbrt(input.view(dtype)));

                auto rtype = type(v);
                auto result = ndarray(shape(v),rtype);

                auto ctx        = tilekit::Scalar;
                auto tile_shape = nmtools_tuple{1_ct,4_ct};
                auto output     = result.mutable_view(rtype);
                // auto padding    = True;

                cbrt(ctx,output,input.view(dtype),tile_shape);

                array = result;
            }
        });

        return array;
    }

    auto cpu_cbrt::graph() const noexcept -> Graph
    {
        return graph_;
    }

    auto cpu_cbrt::hash() const noexcept -> nm_size_t
    {
        return hash_;
    }
}

#endif // NMTOOLS_RUNTIME_CPU_CBRT_IMPLEMENTATION

#endif // NMTOOLS_RUNTIME_CPU_CBRT_HPP
