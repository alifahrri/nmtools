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

        template <typename f_shape_t>
        static constexpr auto get_kernel_size(const f_shape_t& f_shape)
        {
            const auto k_width  = at(f_shape,meta::ct_v<-1>);
            const auto k_height = at(f_shape,meta::ct_v<-2>);
            if constexpr (meta::is_constant_index_v<decltype(k_width)>
                && meta::is_constant_index_v<decltype(k_height)>)
            {
                // prevent array with constant index as value type
                return nmtools_tuple{k_width,k_height};
            } else {
                return nmtools_array{k_width,k_height};   
            }
        }

        using input_shape_type  = decltype(nmtools::shape<true>(meta::declval<input_t>()));
        using input_size_type   = decltype(nmtools::size<true>(meta::declval<input_t>()));
        using filter_shape_type = decltype(nmtools::shape<true>(meta::declval<weight_t>()));
        using out_channels_type = decltype(nmtools::at(meta::declval<filter_shape_type>(),meta::ct_v<0>));
        using kernel_size_type  = decltype(get_kernel_size(meta::declval<filter_shape_type>()));

        using dst_shape_type = meta::resolve_optype_t<index::shape_conv2d_t
                                ,input_shape_type,out_channels_type
                                ,kernel_size_type,stride_type,none_t,dilation_type>;
        using dst_size_type = meta::resolve_optype_t<index::size_conv2d_t
                                ,dst_shape_type,input_size_type,input_shape_type,out_channels_type
                                ,kernel_size_type,stride_type,none_t,dilation_type>;
        
        // This controls the layout (CHW or HWC)
        // TODO: support for NHWC format
        static constexpr auto ch_idx = meta::ct_v<-3>;
        static constexpr auto out_ch_idx = meta::ct_v<-3>;

        // TODO: generalize to handle arbitrary "channel" axis
        using in_channels_type = decltype(nmtools::at(meta::declval<input_shape_type>(),ch_idx));
        using groups_type = decltype(nmtools::at(meta::declval<filter_shape_type>(),ch_idx) / meta::declval<in_channels_type>());


        input_type    input;
        weight_type   weight;
        stride_type   stride;
        dilation_type dilation;

        const input_shape_type  input_shape;
        const input_size_type   input_size;
        const filter_shape_type filter_shape;
        const kernel_size_type  kernel_size;
        const dst_shape_type    dst_shape;
        const dst_size_type     dst_size;
        const in_channels_type  in_channels;
        const groups_type       groups;

        constexpr conv2d_t(const input_t& input_, const weight_t& weight_, const stride_t& stride, const dilation_t& dilation)
            : input(initialize<input_type>(input_))
            , weight(initialize<weight_type>(weight_))
            , stride(init_attribute<stride_type>(stride))
            , dilation(init_attribute<dilation_type>(dilation))
            , input_shape(nmtools::shape<true>(input_))
            , input_size(nmtools::size<true>(input_))
            , filter_shape(nmtools::shape<true>(weight_))
            , kernel_size(get_kernel_size(filter_shape))
            , dst_shape(index::shape_conv2d(input_shape,nmtools::at(filter_shape,meta::ct_v<0>)
                , kernel_size,stride,None,dilation))
            , dst_size(index::size_conv2d(dst_shape,input_size,input_shape,nmtools::at(filter_shape,meta::ct_v<0>)
                , kernel_size,stride,None,dilation))
            , in_channels(nmtools::at(input_shape,ch_idx))
            , groups((nmtools::at(filter_shape,ch_idx) / in_channels))
        {}

        constexpr auto shape() const
        {
            return dst_shape;
        } // shape

        constexpr auto size() const
        {
            return dst_size;
        }

        constexpr auto dim() const
        {
            // TODO: consider to compute this at initialization, since view doesn't allow change shape anyway
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            const auto indices_ = pack_indices(indices...);

            const auto slice_args = index::slice_conv2d(indices_,input_shape,kernel_size,stride,dilation,groups);

            const auto sliced = [&](){
                if constexpr (meta::is_pointer_v<input_type>) {
                    return apply_slice(*input,slice_args);
                } else {
                    return apply_slice(input,slice_args);
                }
            }();

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
    template <typename input_t, typename weight_t, typename bias_t=none_t, typename stride_t=meta::ct<1ul>, typename padding_t=none_t, typename dilation_t=meta::ct<1ul>>
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
            if constexpr (meta::is_constant_index_v<stride_t>) {
                return nmtools_tuple{stride,stride};
            } else if constexpr (meta::is_num_v<stride_t>) {
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
            if constexpr (meta::is_constant_index_v<dilation_t>) {
                return nmtools_tuple{dilation,dilation};
            } else if constexpr (meta::is_num_v<dilation_t>) {
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
            auto C = at(shape<true>(bias),meta::ct_v<0>);
            auto bias_shape = [&](){
                using channel_axis_t = decltype(C);
                if constexpr (meta::is_constant_index_v<channel_axis_t>) {
                    return nmtools_tuple{C,meta::ct_v<1ul>,meta::ct_v<1ul>};
                } else if constexpr (meta::is_clipped_integer_v<channel_axis_t>) {
                    return nmtools_tuple{C,clipped_size_t<1ul>{1ul},clipped_size_t<1ul>{1ul}};
                } else {
                    return nmtools_array<size_t,3>{C,1,1};
                }
            }();
            auto bias_ = view::reshape(bias,bias_shape);
            return view::add(conv_,bias_); 
        } else if constexpr (is_none_v<padding_t>) {
            using view_t = decorator_t<conv2d_t,input_t,weight_t,stride_type,dilation_type>;
            return view_t{{input,weight,stride_,dilation_}};
        } else /* if constexpr (is_index_array_v<padding_t>) */ {
            auto padding_conv2d = index::padding_conv2d(nmtools::dim<true>(input),padding);

            auto input_ = pad(input,padding_conv2d);
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

    // TODO: remove, do not provide as metafunction, use newer deduction pattern
    template <typename input_t, typename weight_t, typename stride_t, typename dilation_t>
    struct fixed_size<
        decorator_t<conv2d_t,input_t,weight_t,stride_t,dilation_t>
    >
    {
        using view_type = decorator_t<conv2d_t,input_t,weight_t,stride_t,dilation_t>;
        using dst_shape_type = typename view_type::dst_shape_type;
        using dst_size_type  = typename view_type::dst_size_type;

        static inline constexpr auto value = [](){
            if constexpr (is_constant_index_v<dst_size_type>) {
                return to_value_v<dst_size_type>;
            } else if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(dst_shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    // TODO: remove, do not provide as metafunction, use newer deduction pattern
    template <typename input_t, typename weight_t, typename stride_t, typename dilation_t>
    struct bounded_size<
        decorator_t<conv2d_t,input_t,weight_t,stride_t,dilation_t>
    >
    {
        using view_type = decorator_t<conv2d_t,input_t,weight_t,stride_t,dilation_t>;
        using dst_shape_type = typename view_type::dst_shape_type;
        using dst_size_type  = typename view_type::dst_size_type;

        static inline constexpr auto value = [](){
            if constexpr (is_clipped_integer_v<dst_size_type>
                || is_constant_index_v<dst_size_type>
            ) {
                return to_value_v<dst_size_type>;
            } else if constexpr (is_clipped_index_array_v<dst_shape_type>
                || is_constant_index_array_v<dst_shape_type>
            ) {
                auto max_shape = to_value_v<dst_shape_type>;
                return index::product(max_shape);
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename input_t, typename weight_t, typename stride_t, typename dilation_t>
    struct is_ndarray<
        decorator_t<conv2d_t,input_t,weight_t,stride_t,dilation_t>
    >
    {
        static constexpr auto value = is_ndarray_v<input_t> && is_ndarray_v<weight_t>;
    };
} // nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_CONV_HPP