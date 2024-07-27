#ifndef NMTOOLS_ARRAY_VIEW_CONV1D_HPP
#define NMTOOLS_ARRAY_VIEW_CONV1D_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::index
{
    struct conv_reshape_t {};

    template <typename src_shape_t, typename groups_t, typename n_planes_t>
    constexpr auto conv_reshape(const src_shape_t& src_shape, groups_t groups, [[maybe_unused]] n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_reshape_t,src_shape_t,groups_t,n_planes_t>;

        auto result = result_t{};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            [[maybe_unused]]
            auto dst_dim = src_dim + 1;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            auto dst_conv_axis = -nm_index_t(src_dim);
            auto src_conv_axis = dst_conv_axis+1;

            at(result,dst_conv_axis)   = groups;
            at(result,dst_conv_axis+1) = at(src_shape,src_conv_axis) / groups;

            for (nm_index_t i=0; i<nm_index_t(dst_dim-2); i++) {
                at(result,-i) = at(src_shape,-i);
            }
        }
        
        return result;
    }

    struct conv_kernel_size_t {};

    template <typename weight_shape_t, typename n_planes_t>
    constexpr auto conv_kernel_size(const weight_shape_t& weight_shape, n_planes_t n_planes)
    {
        using result_t = meta::resolve_optype_t<conv_kernel_size_t,weight_shape_t,n_planes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(n_planes);
            }

            for (nm_index_t i=0; i<n_planes; i++) {
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
            for (nm_index_t i=0; i<n_planes; i++) {
                at(result,i) = -(i+1);
            }
        }

        return result;
    }

    struct conv1d_pad_t {};

    template <typename src_dim_t, typename padding_t>
    constexpr auto conv1d_pad(const src_dim_t& src_dim, const padding_t& padding)
    {
        using result_t = meta::resolve_optype_t<conv1d_pad_t,src_dim_t,padding_t>;

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
            if constexpr (meta::is_index_v<padding_t>) {
                auto pad_axis = src_dim - 1;
                at(result,pad_axis) = padding;
                at(result,pad_axis+src_dim) = padding;
            } else {
                // TODO: implement
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
        struct CONV_RESHAPE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV1D_PAD_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_KERNEL_SIZE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct CONV_WINDOW_AXIS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename groups_t, typename n_planes_t>
    struct resolve_optype<void,index::conv_reshape_t,src_shape_t,groups_t,n_planes_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                   !is_index_array_v<src_shape_t>
                || !is_index_v<groups_t>
                || !is_index_v<n_planes_t>
            ) {
                using type = error::CONV_RESHAPE_UNSUPPORTED<src_shape_t,groups_t,n_planes_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_constant_index_array_v<src_shape_t>
                && is_constant_index_v<groups_t>
                && is_constant_index_v<n_planes_t>
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto groups    = to_value_v<groups_t>;
                constexpr auto n_planes  = to_value_v<n_planes_t>;
                constexpr auto result    = index::conv_reshape(src_shape,groups,n_planes);
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
    }; // conv_reshape_t

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
                constexpr auto n_planes = to_value_v<n_planes_t>;
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
                    using type = nmtools_static_vector<nm_index_t,n_planes_t::max_value>;
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
                constexpr auto n_planes = to_value_v<n_planes_t>;
                constexpr auto result = index::conv_window_axis(n_planes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_clipped_integer_v<n_planes_t>) {
                using type = nmtools_static_vector<nm_index_t,n_planes_t::max_value>;
                return as_value_v<type>;
            } else {
                // TODO; support small vector
                using type = nmtools_list<nm_index_t>;
                return as_value_v<type>;
            }
        }();
    };

    template <typename src_dim_t, typename padding_t>
    struct resolve_optype<void,index::conv1d_pad_t,src_dim_t,padding_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_v<src_dim_t>
                || !(is_index_v<padding_t> || is_index_array_v<padding_t>)
            ) {
                using type = error::CONV1D_PAD_UNSUPPORTED<src_dim_t,padding_t>;
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
    }; // conv1d_pad_t
}

/*=====================================================================*/

#include "nmtools/array/view/alias.hpp"
#include "nmtools/array/view/sliding_window.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/array/view/expand_dims.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/expand.hpp"
#include "nmtools/array/view/pad.hpp"

namespace nmtools::view
{
    template <typename input_t, typename weight_t, typename bias_t=none_t
        , typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t, typename groups_t=meta::ct<1>>
    constexpr auto conv1d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}
        , const stride_t& stride=stride_t{}, const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{}, groups_t groups=groups_t{})
    {
        auto aliased  = [&](){
            if constexpr (is_none_v<bias_t>) {
                return view::aliased(input,weight);
            } else {
                return view::aliased(input,weight,bias);
            }
        }();
        auto a_weight = [&](){
            if constexpr (is_none_v<dilation_t>) {
                return nmtools::get<1>(aliased);
            } else {
                return view::expand(nmtools::get<1>(aliased),/*axis=*/-1,/*spacing=*/dilation-1);
            }
        }();

        constexpr auto n_planes = meta::ct_v<1>;

        auto input_shape  = shape<true>(input);
        auto weight_shape = shape<true>(a_weight);
        auto window_axis  = meta::ct_v<-1>;
        auto kernel_size  = at(weight_shape,meta::ct_v<-1>);
        auto group_shape  = index::conv_reshape(input_shape,groups,n_planes);

        auto a_input = [&](){
            if constexpr (is_none_v<padding_t>) {
                return view::reshape(nmtools::get<0>(aliased),group_shape);
            } else {
                // TODO: error handling
                auto reshaped  = view::reshape(nmtools::get<0>(aliased),group_shape);
                auto src_dim   = unwrap(dim<true>(reshaped));
                auto pad_width = index::conv1d_pad(src_dim,padding);
                return view::pad(unwrap(reshaped),pad_width);
            }
        }();

        auto weight_window = view::sliding_window(a_weight,kernel_size,window_axis);
        auto input_window  = view::sliding_window(a_input,kernel_size,window_axis);

        auto sum_axes = nmtools_tuple{meta::ct_v<-3>, meta::ct_v<-1>};
        auto dtype    = None;
        auto initial  = None;
        auto keepdims = False;

        auto sum_result = view::sum(view::multiply(input_window,weight_window)
            , sum_axes
            , dtype
            , initial
            , keepdims
        );
        auto add_result = [&](){
            if constexpr (!is_none_v<bias_t>) {
                auto a_bias = nmtools::get<2>(aliased);
                auto m_bias = view::expand_dims(a_bias,meta::ct_v<-1>);
                return view::add(sum_result,m_bias);
            } else {
                return sum_result;
            }
        }();
        auto slice_result = [&](){
            if constexpr (!is_none_v<stride_t>) {
                auto slice_args = nmtools_tuple{None,None,stride};
                return view::slice(add_result,Ellipsis,slice_args);
            } else {
                return add_result;
            }
        }();
        return slice_result;
    }
}

#endif // NMTOOLS_ARRAY_VIEW_CONV1D_HPP