#ifndef NMTOOLS_ARRAY_VIEW_LAYER_NORM_HPP
#define NMTOOLS_ARRAY_VIEW_LAYER_NORM_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/array/var.hpp"

namespace nmtools::index
{
    struct layer_norm_axis_t {};

    template <typename wb_shape_t>
    constexpr auto layer_norm_axis(const wb_shape_t& wb_shape)
    {
        using result_t = meta::resolve_optype_t<layer_norm_axis_t,wb_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto dst_dim = len(wb_shape);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            for (nm_size_t i=0; i<dst_dim; i++) {
                at(result,i) = -(int)dst_dim + i;
            }
        }
        
        return result;
    }
}

namespace nmtools::meta
{
    namespace error {
        template<typename...>
        struct LAYER_NORM_AXIS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename wb_shape_t>
    struct resolve_optype<void,index::layer_norm_axis_t,wb_shape_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<wb_shape_t>) {
                using type = error::LAYER_NORM_AXIS_UNSUPPORTED<wb_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<wb_shape_t>) {
                constexpr auto wb_shape = to_value_v<wb_shape_t>;
                constexpr auto result = index::layer_norm_axis(wb_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<wb_shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<wb_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_index_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_index_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

namespace nmtools::view
{
    template <typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto layer_norm(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5})
    {
        auto aliased  = view::aliased(input,weight,bias);
        auto a_input  = nmtools::get<0>(aliased);
        auto a_weight = nmtools::get<1>(aliased);
        auto a_bias   = nmtools::get<2>(aliased);

        // assume weight & bias has the same shape
        // TODO: error handling
        auto wb_shape = shape<true>(weight);

        auto axis  = index::layer_norm_axis(wb_shape);
        auto dtype = None;
        auto ddof  = 0;
        auto keepdims = True;

        auto mean  = view::mean(a_input,axis,dtype,keepdims);
        auto shift = view::subtract(a_input,mean);

        auto var  = view::var(a_input,axis,dtype,ddof,keepdims);
        auto std  = view::sqrt(view::add(var,epsilon));
        auto norm = view::divide(shift,std);
        return view::add(view::multiply(norm,a_weight),a_bias);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_LAYER_NORM_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LAYER_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_LAYER_NORM_HPP

#include "nmtools/array/layer_norm.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename input_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto layer_norm(const input_t& input, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto layer_norm = view::layer_norm(input,weight,bias,epsilon);
        return eval(layer_norm
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // layer_norm
}

#endif // NMTOOLS_ARRAY_ARRAY_LAYER_NORM_HPP