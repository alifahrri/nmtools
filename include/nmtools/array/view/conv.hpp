#ifndef NMTOOLS_ARRAY_VIEW_CONV_HPP
#define NMTOOLS_ARRAY_VIEW_CONV_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/pad.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/index/conv.hpp"
#include "nmtools/array/index/ref.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view
{
    /**
     * @brief A lazy view describing conv2d operation.
     * 
     * @tparam input_t 
     * @tparam weight_t 
     * @tparam stride_t 
     * @tparam dilation_t 
     */
    template <typename input_t, typename weight_t, typename stride_t, typename dilation_t>
    struct conv2d_t
    {
        using input_type    = resolve_array_type_t<input_t>;
        using weight_type   = resolve_array_type_t<weight_t>;
        using array_type    = nmtools_tuple<input_type>;
        using stride_type   = resolve_attribute_type_t<stride_t>;
        using dilation_type = resolve_attribute_type_t<dilation_t>;

        input_type    input;
        weight_type   weight;
        stride_type   stride;
        dilation_type dilation;

        constexpr conv2d_t(const input_t& input, const weight_t& weight, const stride_t& stride, const dilation_t& dilation)
            : input(initialize<input_type>(input))
            , weight(initialize<weight_type>(weight))
            , stride(init_attribute<stride_type>(stride))
            , dilation(init_attribute<dilation_type>(dilation))
        {}

        constexpr auto shape() const
        {
            // TODO: consider to compute this at initialization, since view doesn't allow change shape anyway

            const auto i_shape = detail::shape(input);
            const auto f_shape = detail::shape(weight);
            const auto out_channels = at(f_shape,meta::ct_v<0>);
            const auto k_width  = at(f_shape,meta::ct_v<-1>);
            const auto k_height = at(f_shape,meta::ct_v<-2>);
            const auto kernel_size = nmtools_array{k_width,k_height};

            return index::shape_conv2d(i_shape,out_channels,kernel_size,stride,None,dilation);
        } // shape

        constexpr auto dim() const
        {
            // TODO: consider to compute this at initialization, since view doesn't allow change shape anyway
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // TODO: consider to compute this at initialization, since view doesn't allow change shape anyway
            const auto i_shape = detail::shape(input);
            const auto f_shape = detail::shape(weight);
            const auto k_width  = at(f_shape,meta::ct_v<-1>);
            const auto k_height = at(f_shape,meta::ct_v<-2>);
            const auto kernel_size = nmtools_array{k_width,k_height};
            // This controls the layout (CHW or HWC)
            constexpr auto ch_idx  = meta::ct_v<-3>;
            // TODO: generalize to handle arbitrary "channel" axis
            const auto in_channels = at(i_shape,ch_idx);
            const auto groups = at(f_shape,ch_idx) / in_channels;

            const auto indices_ = pack_indices(indices...);

            const auto slice_args = index::slice_conv2d(indices_,i_shape,kernel_size,stride,dilation,groups);

            const auto sliced = [&](){
                if constexpr (meta::is_pointer_v<input_type>) {
                    return apply_slice(*input,slice_args);
                } else {
                    return apply_slice(input,slice_args);
                }
            }();

            // TODO: support for NHWC format
            const auto out_ch_idx = meta::ct_v<-3>;
            const auto filter_i = at(indices_,out_ch_idx);

            // assume weight dim == 4, and output channel is at axis 0
            const auto filter = [&](){
                if constexpr (meta::is_pointer_v<weight_type>) {
                    return slice(*weight,filter_i,Ellipsis);
                } else {
                    return slice(weight,filter_i,Ellipsis);
                }
            }();
            const auto filtered = multiply(sliced,filter);

            return reduce_add(filtered,None);
        } // operator()
    }; // conv2d_t

    /**
     * @brief Create a conv2d view.
     * Applies 2D convolution over an input image composed of several input channels.
     * 
     * Currently only support NCHW format.
     * 
     * @tparam input_t 
     * @tparam weight_t 
     * @tparam bias_t 
     * @tparam stride_t 
     * @tparam padding_t 
     * @tparam dilation_t 
     * @param input     input array with format NCHW or CHW
     * @param weight    filters of shape with format (OutC,C,k_h,k_w)
     * @param bias      optional bias, can be either index array or num
     * @param stride    optional stride, can be either index array or num
     * @param padding   optional padding, can be either index array or num
     * @param dilation 
     * @return constexpr auto 
     */
    template <typename input_t, typename weight_t, typename bias_t=none_t, typename stride_t=none_t, typename padding_t=none_t, typename dilation_t=none_t>
    constexpr auto conv2d(const input_t& input, const weight_t& weight, const bias_t& bias=bias_t{}, const stride_t& stride=stride_t{}
        , [[maybe_unused]] const padding_t& padding=padding_t{}, const dilation_t& dilation=dilation_t{})
    {
        // TODO: constraint types:
        // - input_t should be array
        // - weight_t should be array
        // - stride_t can be either index array or none
        // - padding_t can be either index array or none
        // - dilation_t can be either index array or none

        // TODO: error handling for incompatible shape

        // handle index array or num
        auto stride_ = [&](){
            if constexpr (meta::is_num_v<stride_t>) {
                return nmtools_array{stride,stride};
            } else if constexpr (meta::is_bounded_array_v<stride_t>) {
                // prevent array decay to pointer
                return index::ref(stride);
            } else {
                return stride;
            }
        }();
        using stride_type = meta::remove_cvref_t<decltype(stride_)>;

        // handle index array or num
        auto dilation_ = [&](){
            if constexpr (meta::is_num_v<dilation_t>) {
                return nmtools_array{dilation,dilation};
            } else if constexpr (meta::is_bounded_array_v<dilation_t>) {
                // prevent array decay to pointer
                return index::ref(dilation);
            } else {
                return dilation;
            }
        }();
        using dilation_type = meta::remove_cvref_t<decltype(dilation_)>;

        if constexpr (!is_none_v<bias_t>) {
            auto conv_ = view::conv2d(input,weight,None,stride_,padding,dilation_);
            // assume NCHW
            // assume bias is 1D
            auto C = at(shape(bias),0);
            auto bias_ = view::reshape(bias,nmtools_array<size_t,3>{C,1,1});
            return view::add(conv_,bias_); 
        } else if constexpr (is_none_v<padding_t>) {
            using view_t = decorator_t<conv2d_t,input_t,weight_t,stride_type,dilation_type>;
            return view_t{{input,weight,stride_,dilation_}};
        } else /* if constexpr (is_index_array_v<padding_t>) */ {
            constexpr auto pad_vtype = [](){
                using index_t = meta::get_element_type_t<padding_t>;
                if constexpr (meta::is_fixed_dim_ndarray_v<input_t>) {
                    constexpr auto dim_ = meta::fixed_dim_v<input_t>;
                    using type = nmtools_array<index_t,dim_*2>;
                    return meta::as_value_v<type>;
                } else {
                    // dynamic ndarray, resized at runtime
                    using type = nmtools_list<index_t>;
                    return meta::as_value_v<type>;
                }
            }();
            using pad_type = meta::type_t<decltype(pad_vtype)>;
            auto padding_ = pad_type{};
            auto dim_ = dim(input);
            if constexpr (meta::is_resizeable_v<pad_type>) {
                padding_.resize(dim_*2);
            }
            // assuming NCHW, pad at axis [-1,-2]
            // TODO: support NHWC layout
            auto spatial_i = dim_ - 2;
            // handle index array or num
            auto [pad_h,pad_w] = [&](){
                if constexpr (meta::is_index_v<padding_t>) {
                    return nmtools_tuple{padding,padding};
                } else {
                    auto pad_h = at(padding,0);
                    auto pad_w = at(padding,1);
                    return nmtools_tuple{pad_h,pad_w};
                }
            }();
            at(padding_,spatial_i)   = pad_h;
            at(padding_,spatial_i+1) = pad_w;
            at(padding_,-2) = pad_h;
            at(padding_,-1) = pad_w;

            auto input_ = pad(input,padding_);
            using input_type = decltype(input_);
            using view_t = decorator_t<conv2d_t,input_type,weight_t,stride_type,dilation_type>;
            return view_t{{input_,weight,stride_,dilation_}};
        }
    } // conv2d

} // namespace nmtools::view

namespace nmtools::meta
{
    using view::decorator_t;
    using view::conv2d_t;

    template <typename input_t, typename weight_t, typename stride_t, typename dilation_t>
    struct get_element_type<
        decorator_t<conv2d_t,input_t,weight_t,stride_t,dilation_t>
    >
    {
        using input_elem_t  = get_element_type_t<input_t>;
        using weight_elem_t = get_element_type_t<weight_t>;
        using type = decltype(input_elem_t{} * weight_elem_t{});
    }; // get_element_type

    template <typename input_t, typename weight_t, typename stride_t, typename dilation_t>
    struct is_ndarray<
        decorator_t<conv2d_t,input_t,weight_t,stride_t,dilation_t>
    >
    {
        static constexpr auto value = is_ndarray_v<input_t> && is_ndarray_v<weight_t>;
    };
} // nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_CONV_HPP