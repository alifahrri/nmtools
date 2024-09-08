#ifndef NMTOOLS_ARRAY_VIEW_GROUP_NORM_HPP
#define NMTOOLS_ARRAY_VIEW_GROUP_NORM_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/array/view/mean.hpp"
#include "nmtools/array/view/var.hpp"
#include "nmtools/array/view/atleast_nd.hpp"
#include "nmtools/array/view/moveaxis.hpp"

#include "nmtools/array/index/product.hpp"

namespace nmtools::index
{
    struct group_norm_reshape_t {};
    struct group_norm_axis_t {};
    // for weight & bias
    struct group_norm_args_reshape_t {};

    template <typename src_shape_t, typename num_groups_t>
    constexpr auto group_norm_reshape(const src_shape_t& src_shape, num_groups_t num_groups)
    {
        using result_t = meta::resolve_optype_t<group_norm_reshape_t,src_shape_t,num_groups_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            [[maybe_unused]]
            auto dst_dim = src_dim + 1;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            auto group_axis   = meta::ct_v<2>;
            auto channel_axis = meta::ct_v<1>;

            // TODO: error handling
            auto channel_per_group = at(src_shape,channel_axis) / num_groups;

            at(result,group_axis) = channel_per_group;
            at(result,channel_axis) = num_groups;

            // TODO: parametrize number of independent dims
            for (nm_index_t i=0; i<=nm_index_t(src_dim-2); i++) {
                at(result,-i) = at(src_shape,-i);
            }
        }

        return result;
    } // group_norm_reshape

    template <typename src_shape_t>
    constexpr auto group_norm_axis(const src_shape_t& src_shape)
    {
        using result_t = meta::resolve_optype_t<group_norm_axis_t,src_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            auto dst_dim = src_dim - 1;
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }
            for (size_t i=0; i<dst_dim; i++) {
                at(result,i) = i+2; // +2 because of reshaped input
            }
        }

        return result;
    }

    template <typename src_shape_t, typename wb_shape_t>
    constexpr auto group_norm_args_reshape(const src_shape_t& src_shape, const wb_shape_t& wb_shape)
    {
        using result_t = meta::resolve_optype_t<group_norm_args_reshape_t,src_shape_t,wb_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(src_dim);
            }

            for (nm_size_t i=0; i<src_dim; i++) {
                at(result,i) = 1;
            }

            // TODO: support num wb
            // assume wb is 1D
            auto wb_size = index::product(wb_shape);
            at(result,1) = wb_size;
        }

        return result;
    }

} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct GROUP_NORM_RESHAPE_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct GROUP_NORM_AXIS_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct GROUP_NORM_ARGS_RESHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename num_groups_t>
    struct resolve_optype<void,index::group_norm_reshape_t,src_shape_t,num_groups_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_num_v<num_groups_t>
            ) {
                using type = error::GROUP_NORM_RESHAPE_UNSUPPORTED<src_shape_t,num_groups_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && is_constant_index_v<num_groups_t>
            ) {
                constexpr auto src_shape  = to_value_v<src_shape_t>;
                constexpr auto num_groups = to_value_v<num_groups_t>;
                constexpr auto result = index::group_norm_reshape(src_shape,num_groups);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using result_t = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<result_t>;
                },as_value_v<nmtools_tuple<>>);
                // TODO: infer bounded shape
            } else {
                constexpr auto DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM+1>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM+1>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename src_shape_t>
    struct resolve_optype<void,index::group_norm_axis_t,src_shape_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>) {
                using type = error::GROUP_NORM_AXIS_UNSUPPORTED<src_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<src_shape_t>) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto result = index::group_norm_axis(src_shape);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
                // TODO: infer bounded shape
            } else {
                constexpr auto DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM-1>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM-1>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename src_shape_t, typename wb_shape_t>
    struct resolve_optype<void,index::group_norm_args_reshape_t,src_shape_t,wb_shape_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_array_v<wb_shape_t> // TODO: support num wb
            ) {
                using type = error::GROUP_NORM_ARGS_RESHAPE_UNSUPPORTED<src_shape_t,wb_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<src_shape_t>
                && is_constant_index_array_v<wb_shape_t>
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto wb_shape  = to_value_v<wb_shape_t>;
                constexpr auto result = index::group_norm_args_reshape(src_shape,wb_shape);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
                // TODO: infer bounded shape
                // TODO: support num wb
            } else {
                constexpr auto DIM = len_v<src_shape_t>;
                constexpr auto B_DIM = bounded_size_v<wb_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

namespace nmtools::view
{
    template <typename input_t, typename num_groups_t, typename weight_t, typename bias_t, typename epsilon_t=float>
    constexpr auto group_norm(const input_t& input, num_groups_t num_groups, const weight_t& weight, const bias_t& bias, epsilon_t epsilon=epsilon_t{1e-5})
    {
        auto src_shape = shape<true>(input);
        auto grouped_shape = index::group_norm_reshape(src_shape,num_groups);

        // assume bias has the same shape as weight
        // TODO: check and handle error
        auto wb_shape  = shape<true>(weight);
        auto wb_reshape_args = index::group_norm_args_reshape(src_shape,wb_shape);

        auto aliased  = view::aliased(input, weight, bias);
        auto a_input  = view::reshape(nmtools::get<0>(aliased),grouped_shape);
        auto a_weight = view::reshape(nmtools::get<1>(aliased),wb_reshape_args);
        auto a_bias   = view::reshape(nmtools::get<2>(aliased),wb_reshape_args);

        auto axis  = index::group_norm_axis(src_shape);
        auto dtype = None;
        auto ddof  = 0;
        auto keepdims = True;

        auto mean  = view::mean(a_input,axis,dtype,keepdims);
        auto shift = view::subtract(a_input,mean);

        auto var  = view::var(a_input,axis,dtype,ddof,keepdims);
        auto std  = view::sqrt(view::add(var,epsilon));
        auto norm = view::divide(shift,std);
        return view::add(view::multiply(view::reshape(norm,src_shape),a_weight),a_bias);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_GROUP_NORM_HPP