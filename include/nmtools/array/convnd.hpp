#ifndef NMTOOLS_ARRAY_VIEW_CONVND_HPP
#define NMTOOLS_ARRAY_VIEW_CONVND_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct conv_reshape_input_t {};

    template <typename src_shape_t, typename groups_t, typename n_planes_t>
    constexpr auto conv_reshape_input([[maybe_unused]] const src_shape_t& src_shape, [[maybe_unused]] groups_t groups, [[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_reshape_input_t,src_shape_t,groups_t,n_planes_t>;

        auto result = result_t{};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            [[maybe_unused]]
            auto dst_dim = src_dim + 2; // 1 (n_output bcast), groups

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            auto batch_axis = meta::ct_v<0>;
            auto outch_axis = meta::ct_v<2>;
            auto group_axis = meta::ct_v<1>;
            auto dst_inp_ch_axis = meta::ct_v<3>;
            auto src_inp_ch_axis = meta::ct_v<1>;
            at(result,batch_axis) = at(src_shape,batch_axis);
            at(result,outch_axis) = 1;
            at(result,group_axis) = groups;
            at(result,dst_inp_ch_axis) = at(src_shape,src_inp_ch_axis) / groups;

            for (nm_size_t i=1; i<=(nm_size_t)n_planes; i++) {
                at(result,i+dst_inp_ch_axis) = at(src_shape,i+src_inp_ch_axis);
            }
        }
        
        return result;
    }

    struct conv_reshape_weight_t {};

    template <typename src_shape_t, typename n_planes_t, typename groups_t>
    constexpr auto conv_reshape_weight([[maybe_unused]] const src_shape_t& src_shape, [[maybe_unused]] groups_t groups, [[maybe_unused]] n_planes_t n_planes)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>
            || meta::is_maybe_v<groups_t>
            || meta::is_maybe_v<n_planes_t>
        ) {
            using result_t = decltype(conv_reshape_weight(unwrap(src_shape),unwrap(groups),unwrap(n_planes)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(groups) && has_value(n_planes)
                ? return_t{conv_reshape_weight(unwrap(src_shape),unwrap(groups),unwrap(n_planes))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<conv_reshape_weight_t,src_shape_t,n_planes_t,groups_t>;

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

                // initialize with 1s
                for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                    at(result,i) = 1;
                }

                for (nm_index_t i=1; i<=nm_index_t(src_dim-1); i++) {
                    at(result,-i) = at(src_shape,-i);
                }
                auto group_axis = meta::ct_v<0>;
                auto dst_outch_axis = meta::ct_v<1>;
                auto src_outch_axis = meta::ct_v<0>;
                at(result,group_axis) = groups;
                at(result,dst_outch_axis) = at(src_shape,src_outch_axis) / groups;
            }

            return result;
        }
    }

    struct conv_reshape_reduce_t {};

    template <typename src_shape_t, typename n_planes_t, typename groups_t>
    constexpr auto conv_reshape_reduce([[maybe_unused]] const src_shape_t& src_shape, [[maybe_unused]] groups_t groups, [[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_reshape_reduce_t,src_shape_t,n_planes_t,groups_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            [[maybe_unused]]
            auto dst_dim = src_dim - 1;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            // fill spatial axis
            for (nm_index_t i=0; i<=nm_index_t(n_planes); i++) {
                at(result,-i) = at(src_shape,-i);
            }
            
            auto group_axis = meta::ct_v<2>;
            auto outch_axis = meta::ct_v<1>;
            auto batch_axis = meta::ct_v<0>;
            at(result,batch_axis) = at(src_shape,batch_axis);
            at(result,outch_axis) = at(src_shape,outch_axis) * at(src_shape,group_axis);
        }

        return result;
    }

    struct conv_reshape_bias_t {};

    template <typename src_shape_t, typename n_planes_t>
    constexpr auto conv_reshape_bias([[maybe_unused]] const src_shape_t& src_shape, [[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_reshape_bias_t,src_shape_t,n_planes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            auto dst_dim = src_dim + n_planes;
            
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                at(result,i) = at(src_shape,i);
            }

            for (nm_size_t i=1; i<(nm_size_t)dst_dim; i++) {
                at(result,i) = 1;
            }
        }

        return result;
    }

    struct conv_kernel_size_t {};

    template <typename weight_shape_t, typename n_planes_t>
    constexpr auto conv_kernel_size([[maybe_unused]] const weight_shape_t& weight_shape, [[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_kernel_size_t,weight_shape_t,n_planes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(n_planes);
            }

            for (nm_index_t i=0; i<(nm_index_t)n_planes; i++) {
                at(result,i) = at(weight_shape,-(i+1));
            }
        }

        return result;
    }

    struct conv_window_axis_t {};

    template <typename n_planes_t>
    constexpr auto conv_window_axis([[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_window_axis_t,n_planes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(n_planes);
            }
            for (nm_index_t i=0; i<(nm_index_t)n_planes; i++) {
                at(result,i) = -(i+1);
            }
        }

        return result;
    }

    struct conv_sum_axes_t {};

    template <typename n_planes_t>
    constexpr auto conv_sum_axes([[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_sum_axes_t,n_planes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto n_axes = n_planes + 1;
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(n_axes);
            }

            for (nm_size_t i=0; i<(nm_size_t)n_planes; i++) {
                at(result,i) = -(i+1);
            }

            at(result,n_axes-1) = 3;
        }

        return result;
    }

    struct conv_sum_reshape_t {};

    template <typename src_shape_t, typename n_planes_t>
    constexpr auto conv_sum_reshape(const src_shape_t&, n_planes_t)
    {
        using result_t [[maybe_unused]] = meta::resolve_optype_t<conv_sum_reshape_t,src_shape_t,n_planes_t>;
        // TODO: implement
    }

    template <typename stride_t, typename n_planes_t>
    constexpr auto conv_slices([[maybe_unused]] const stride_t& stride, n_planes_t)
    {
        // TODO: use resolve_optype, provide better support for slice index array
        if constexpr (meta::is_num_v<stride_t>) {
            // assume constant index
            constexpr auto N_PLANES = n_planes_t::value;
            return meta::template_reduce<N_PLANES>([&](auto init, auto){
                return utility::tuple_append(init,nmtools_tuple{None,None,stride});
            },nmtools_tuple{Ellipsis});
        } else {
            // assume dim == n_planes
            constexpr auto N_PLANES = n_planes_t::value;
            return meta::template_reduce<N_PLANES>([&](auto init, auto index){
                return utility::tuple_append(init,nmtools_tuple{None,None,at(stride,index)});
            },nmtools_tuple{Ellipsis});
        }
    }

    struct conv_expand_spacing_t {};

    template <typename dilation_t, typename n_planes_t>
    constexpr auto conv_expand_spacing([[maybe_unused]] const dilation_t& dilation, [[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_expand_spacing_t,dilation_t,n_planes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(n_planes);
            }

            for (nm_size_t i=0; i<(nm_size_t)n_planes; i++) {
                if constexpr (meta::is_index_array_v<dilation_t>) {
                    // assume same length as n_planes
                    at(result,i) = at(dilation,i) - 1;
                } else {
                    at(result,i) = dilation - 1;
                }
            }
        }

        return result;
    }

    struct conv_pad_t {};

    template <typename src_dim_t, typename padding_t, typename n_planes_t>
    constexpr auto conv_pad([[maybe_unused]] const src_dim_t& src_dim, [[maybe_unused]] const padding_t& padding, [[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_pad_t,src_dim_t,padding_t,n_planes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(src_dim*2);
            }

            for (nm_size_t i=0; i<src_dim; i++) {
                at(result,i) = 0;
                at(result,i+src_dim) = 0;
            }

            // axis = -1
            auto pad_axis = src_dim - n_planes;
            if constexpr (meta::is_index_v<padding_t>) {
                for (nm_size_t i=0; i<(nm_size_t)n_planes; i++) {
                    at(result,i+pad_axis) = padding;
                    at(result,i+pad_axis+src_dim) = padding;
                }
            } else {
                for (nm_size_t i=0; i<(nm_size_t)len(padding); i++) {
                    at(result,i+pad_axis) = at(padding,i);
                    at(result,i+pad_axis+src_dim) = at(padding,i);
                }
            }
        }

        return result;
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct CONV_RESHAPE_INPUT_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_RESHAPE_WEIGHT_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_RESHAPE_REDUCE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_RESHAPE_BIAS_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_PAD_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_KERNEL_SIZE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_WINDOW_AXIS_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_SUM_AXES_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_EXPAND_SPACING_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename groups_t, typename n_planes_t>
    struct resolve_optype<void,index::conv_reshape_input_t,src_shape_t,groups_t,n_planes_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                   !is_index_array_v<src_shape_t>
                || !is_index_v<groups_t>
                || !is_index_v<n_planes_t>
            ) {
                using type = error::CONV_RESHAPE_INPUT_UNSUPPORTED<src_shape_t,groups_t,n_planes_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_constant_index_array_v<src_shape_t>
                && is_constant_index_v<groups_t>
                && is_constant_index_v<n_planes_t>
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto groups    = to_value_v<groups_t>;
                constexpr auto n_planes  = n_planes_t{};
                constexpr auto result    = index::conv_reshape_input(src_shape,groups,n_planes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM   = len_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM+2>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM+2>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // conv_reshape_input_t

    template <typename src_shape_t, typename n_planes_t, typename groups_t>
    struct resolve_optype<
        void, index::conv_reshape_weight_t, src_shape_t, n_planes_t, groups_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_v<n_planes_t>
            ) {
                using type = error::CONV_RESHAPE_WEIGHT_UNSUPPORTED<src_shape_t,n_planes_t,groups_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && is_constant_index_v<n_planes_t>
                && is_constant_index_v<groups_t>
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto n_planes  = n_planes_t{};
                constexpr auto groups    = groups_t::value;
                constexpr auto result = index::conv_reshape_weight(src_shape,groups,n_planes);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto i){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,i)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM = len_v<src_shape_t>;
                if constexpr ((DIM > 0) && is_constant_index_v<n_planes_t>) {
                    using type = nmtools_array<nm_size_t,DIM+1>;
                    return as_value_v<type>;
                } else if constexpr (DIM > 0 && is_clipped_integer_v<n_planes_t>) {
                    using type = nmtools_static_vector<nm_size_t,DIM+1>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)> && is_constant_index_v<n_planes_t>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM+1>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)> && is_clipped_integer_v<n_planes_t>) {
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

    template <typename src_shape_t, typename n_planes_t, typename groups_t>
    struct resolve_optype<
        void, index::conv_reshape_reduce_t, src_shape_t, n_planes_t, groups_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_v<n_planes_t>
            ) {
                using type = error::CONV_RESHAPE_REDUCE_UNSUPPORTED<src_shape_t,n_planes_t,groups_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && is_constant_index_v<n_planes_t>
                && is_constant_index_v<groups_t>
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto n_planes  = n_planes_t{};
                constexpr auto groups    = groups_t::value;
                constexpr auto result = index::conv_reshape_reduce(src_shape,groups,n_planes);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto i){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,i)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM = len_v<src_shape_t>;
                if constexpr ((DIM > 0) && is_constant_index_v<n_planes_t>) {
                    using type = nmtools_array<nm_size_t,DIM-1>;
                    return as_value_v<type>;
                } else if constexpr (DIM > 0 && is_clipped_integer_v<n_planes_t>) {
                    using type = nmtools_static_vector<nm_size_t,DIM-1>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)> && is_constant_index_v<n_planes_t>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM-1>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)> && is_clipped_integer_v<n_planes_t>) {
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

    template <typename src_shape_t, typename n_planes_t>
    struct resolve_optype<
        void, index::conv_reshape_bias_t, src_shape_t, n_planes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_v<n_planes_t>
            ) {
                using type = error::CONV_RESHAPE_BIAS_UNSUPPORTED<src_shape_t,n_planes_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && is_constant_index_v<n_planes_t>
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto n_planes  = n_planes_t{};
                constexpr auto result = index::conv_reshape_bias(src_shape,n_planes);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto i){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,i)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto N_PLANES = to_value_v<n_planes_t>;
                if constexpr ((DIM > 0) && is_constant_index_v<n_planes_t>) {
                    using type = nmtools_array<nm_size_t,DIM+n_planes_t::value>;
                    return as_value_v<type>;
                } else if constexpr ((DIM > 0) && (!is_fail_v<decltype(N_PLANES)>)) {
                    using type = nmtools_static_vector<nm_size_t,DIM+N_PLANES>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)> && (!is_fail_v<decltype(N_PLANES)>)) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM+N_PLANES>;
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

    template <typename weight_shape_t, typename n_planes_t>
    struct resolve_optype<
        void, index::conv_kernel_size_t, weight_shape_t, n_planes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<weight_shape_t>
                || !is_index_v<n_planes_t>
            ) {
                using type = error::CONV_KERNEL_SIZE_UNSUPPORTED<weight_shape_t,n_planes_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<weight_shape_t>
                && is_constant_index_v<n_planes_t>
            ) {
                constexpr auto weight_shape = to_value_v<weight_shape_t>;
                constexpr auto n_planes = n_planes_t{};
                constexpr auto result   = index::conv_kernel_size(weight_shape,n_planes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                if constexpr (is_constant_index_v<n_planes_t>) {
                    using type = nmtools_array<nm_index_t,n_planes_t::value>;
                    return as_value_v<type>;
                } else if constexpr (is_clipped_integer_v<n_planes_t>) {
                    using type = nmtools_static_vector<nm_index_t,n_planes_t::max>;
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

    template <typename n_planes_t>
    struct resolve_optype<
        void, index::conv_window_axis_t, n_planes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<n_planes_t>) {
                using type = error::CONV_WINDOW_AXIS_UNSUPPORTED<n_planes_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<n_planes_t>) {
                constexpr auto n_planes = clipped_size_t<n_planes_t::value>(n_planes_t::value);
                constexpr auto result = index::conv_window_axis(n_planes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_clipped_integer_v<n_planes_t>) {
                using type = nmtools_static_vector<nm_index_t,n_planes_t::max>;
                return as_value_v<type>;
            } else {
                // TODO: support small vector
                using type = nmtools_list<nm_index_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename n_planes_t>
    struct resolve_optype<
        void, index::conv_sum_axes_t, n_planes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<n_planes_t>) {
                using type = error::CONV_SUM_AXES_UNSUPPORTED<n_planes_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<n_planes_t>) {
                constexpr auto n_planes   = clipped_size_t<n_planes_t::value>(n_planes_t::value);
                constexpr auto result     = index::conv_sum_axes(n_planes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_clipped_integer_v<n_planes_t>) {
                using type = nmtools_static_vector<nm_index_t,n_planes_t::max+1>;
                return as_value_v<type>;
            } else {
                // TODO: support small vector
                using type = nmtools_list<nm_index_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename dilation_t, typename n_planes_t>
    struct resolve_optype<
        void, index::conv_expand_spacing_t, dilation_t, n_planes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<n_planes_t>
                || !(is_index_array_v<dilation_t> || is_num_v<dilation_t>)
            ) {
                using type = error::CONV_EXPAND_SPACING_UNSUPPORTED<dilation_t,n_planes_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<n_planes_t>
                && (is_constant_index_array_v<dilation_t> || is_constant_index_v<dilation_t>)
            ) {
                constexpr auto dilation = to_value_v<dilation_t>;
                constexpr auto result   = index::conv_expand_spacing(dilation,n_planes_t{});
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_constant_index_v<n_planes_t>) {
                using type = nmtools_array<nm_index_t,n_planes_t::value>;
                return as_value_v<type>;
            } else if constexpr (is_clipped_integer_v<n_planes_t>) {
                using type = nmtools_static_vector<nm_index_t,n_planes_t::max>;
                return as_value_v<type>;
            } else {
                // TODO: support small vector
                using type = nmtools_list<nm_index_t>;
                return as_value_v<type>;
            }

        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename src_dim_t, typename padding_t, typename n_planes_t>
    struct resolve_optype<void,index::conv_pad_t,src_dim_t,padding_t, n_planes_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_v<src_dim_t>
                || !(is_index_v<padding_t> || is_index_array_v<padding_t>)
                || !(is_index_v<n_planes_t>)
            ) {
                using type = error::CONV_PAD_UNSUPPORTED<src_dim_t,padding_t,n_planes_t>;
                return as_value_v<type>;
            } else {
                if constexpr (is_constant_index_v<src_dim_t>) {
                    constexpr auto DIM = to_value_v<src_dim_t>;
                    using type = nmtools_array<nm_size_t,DIM*2>;
                    return as_value_v<type>;
                } else if constexpr (is_clipped_integer_v<src_dim_t>) {
                    constexpr auto DIM = to_value_v<src_dim_t>;
                    using type = nmtools_static_vector<nm_size_t,DIM*2>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // conv_pad_t
}

/*=====================================================================*/

#include "nmtools/core/alias.hpp"
#include "nmtools/array/sliding_window.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/slice.hpp"
#include "nmtools/array/expand.hpp"
#include "nmtools/array/pad.hpp"

namespace nmtools::view
{
    template <typename n_planes_t, typename input_t, typename weight_t, typename bias_t=none_t
        , typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t, typename groups_t=meta::ct<1>>
    constexpr auto convnd(n_planes_t n_planes, const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , const stride_t& stride=stride_t{}, const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}, groups_t groups=groups_t{})
    {
        auto aliased = [&](){
            if constexpr (is_none_v<bias_t>) {
                return view::aliased(input,weight);
            } else {
                return view::aliased(input,weight,bias);
            }
        }();
        auto a_weight = [&](){
            auto src_shape = shape<true>(weight);
            auto dst_shape = index::conv_reshape_weight(src_shape,groups,n_planes);
            // TODO:: error handling
            auto reshaped_weight = unwrap(view::reshape(nmtools::get<1>(aliased),dst_shape));
            if constexpr (is_none_v<dilation_t>) {
                return reshaped_weight;
            } else {
                // same as window axis
                auto axis    = index::conv_window_axis(n_planes);
                auto spacing = index::conv_expand_spacing(dilation,n_planes);
                return view::expand(reshaped_weight,axis,spacing);
            }
        }();

        auto input_shape  = shape<true>(input);
        auto weight_shape = shape<true>(a_weight);
        auto window_axis  = index::conv_window_axis(n_planes);
        auto kernel_size  = index::conv_kernel_size(weight_shape,n_planes);

        auto a_input = [&](){
            auto dst_shape = index::conv_reshape_input(input_shape,groups,n_planes);
            if constexpr (is_none_v<padding_t>) {
                return view::reshape(nmtools::get<0>(aliased),dst_shape);
            } else {
                auto reshaped  = view::reshape(nmtools::get<0>(aliased),dst_shape);
                // TODO: error handling
                auto src_dim   = unwrap(dim<true>(reshaped));
                // TODO: parametrize padding args to n_planes
                auto pad_width = index::conv_pad(src_dim,padding,n_planes);
                return view::pad(unwrap(reshaped),pad_width);
            }
        }();

        auto weight_window = view::sliding_window(a_weight,kernel_size,window_axis);
        auto input_window  = view::sliding_window(a_input,kernel_size,window_axis);

        [[maybe_unused]]
        auto weight_window_shape = nmtools::shape<true>(weight_window);
        [[maybe_unused]]
        auto input_window_shape  = nmtools::shape<true>(input_window);

        auto multiply_result = view::multiply(input_window,weight_window);

        [[maybe_unused]]
        auto multiply_shape = nmtools::shape<true>(multiply_result);
        [[maybe_unused]]
        auto multiply_dim   = nmtools::dim<true>(multiply_result);

        auto sum_axes = index::conv_sum_axes(n_planes);
        auto dtype    = None;
        auto initial  = None;
        auto keepdims = False;

        auto sum_result = view::sum(multiply_result
            , sum_axes
            , dtype
            , initial
            , keepdims
        );

        auto sum_src_shape = shape<true>(sum_result);
        // TODO: propagate error handling
        auto sum_dst_shape = index::conv_reshape_reduce(unwrap(sum_src_shape),groups,n_planes);
        auto reshaped_sum  = view::reshape(sum_result,sum_dst_shape);

        auto add_result = [&](){
            if constexpr (!is_none_v<bias_t>) {
                auto src_shape = shape<true>(bias);
                auto dst_shape = index::conv_reshape_bias(src_shape,n_planes);
                auto a_bias = nmtools::get<2>(aliased);
                auto r_bias = view::reshape(a_bias,dst_shape);
                return view::add(reshaped_sum,r_bias);
            } else {
                return reshaped_sum;
            }
        }();
        auto result = [&](){
            if constexpr (!is_none_v<stride_t>) {
                auto slice_args = index::conv_slices(stride,n_planes);
                return view::apply_slice(add_result,slice_args);
            } else {
                return add_result;
            }
        }();
        [[maybe_unused]]
        auto result_shape = nmtools::shape<true>(result);
        return result;
    }
}

#endif // NMTOOLS_ARRAY_VIEW_CONVND_HPP