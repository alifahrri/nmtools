#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CONV_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CONV_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/conv.hpp"

namespace nmtools::functional
{
    struct conv2d_t
    {
        static constexpr auto arity = 2;

        template <template<auto...>typename sequence, auto...Is
            , template<typename...>typename attr_tuple, typename...attributes_t
            , template<typename...>typename operand_tuple, typename input_t, typename weight_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<input_t,weight_t>& operands) const
        {
            const auto& [input,weight] = operands;
            if constexpr (meta::is_pointer_v<input_t> && meta::is_pointer_v<weight_t>) {
                // NOTE: use fold expr to preserve default attributes
                // NOTE: this doesn't use bias
                return view::conv2d(*input,*weight,None,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<input_t>) {
                return view::conv2d(*input,weight,None,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<weight_t>) {
                return view::conv2d(input,*weight,None,nmtools::get<Is>(attributes)...);
            } else {
                return view::conv2d(input,weight,None,nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <template<typename...>typename attr_tuple
            , typename...attributes_t
            , template<typename...>typename operand_tuple, typename input_t, typename weight_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<input_t,weight_t>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>,attributes,operands);
        } // operator()
    }; // conv2d_t

    struct conv2d_bias_t
    {
        static constexpr auto arity = 3;

        template <template<auto...>typename sequence, auto...Is
            , template<typename...>typename attr_tuple, typename...attributes_t
            , template<typename...>typename operand_tuple, typename input_t, typename weight_t, typename bias_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<input_t,weight_t,bias_t>& operands) const
        {
            const auto& [input,weight,bias] = operands;
            // TODO: check if can simplify these
            if constexpr (meta::is_pointer_v<input_t> && meta::is_pointer_v<weight_t> && meta::is_pointer_v<bias_t>) {
                // NOTE: use fold expr to preserve default attributes
                // NOTE: this doesn't use bias
                return view::conv2d(*input,*weight,*bias,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<input_t> && meta::is_pointer_v<weight_t>) {
                return view::conv2d(*input,*weight,bias,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<input_t> && meta::is_pointer_v<bias_t>) {
                return view::conv2d(*input,weight,*bias,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<weight_t> && meta::is_pointer_v<bias_t>) {
                return view::conv2d(input,*weight,*bias,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<input_t>) {
                return view::conv2d(*input,weight,bias,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<weight_t>) {
                return view::conv2d(input,*weight,bias,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<bias_t>) {
                return view::conv2d(input,weight,*bias,nmtools::get<Is>(attributes)...);
            } else {
                return view::conv2d(input,weight,bias,nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <template<typename...>typename attr_tuple, typename...attributes_t
            , template<typename...>typename operand_tuple, typename input_t, typename weight_t, typename bias_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<input_t,weight_t,bias_t>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>,attributes,operands);
        } // operator()
    }; // conv2d_bias_t

    constexpr inline auto conv2d = functor_t(conv2d_t{});

    constexpr inline auto conv2d_bias = functor_t(conv2d_bias_t{});
    
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_CONV_HPP