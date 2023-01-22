#ifndef NMTOOLS_ARRAY_INDEX_CONV_HPP
#define NMTOOLS_ARRAY_INDEX_CONV_HPP

#include "nmtools/meta.hpp"
#include "nmtools/math.hpp"

#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/array/index/ref.hpp"

namespace nmtools::index
{
    struct shape_conv2d_t {};

    /**
     * @brief Compute the resulting shape of conv2d op.
     * 
     * @tparam shape_t 
     * @tparam out_channels_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam padding_t 
     * @tparam dilation_t 
     * @param shape         input shape
     * @param out_channels  desired number of output channels
     * @param kernel_size   kernel size
     * @param stride        stride, can be None
     * @param padding       padding, can be None
     * @param dilation      dilation, can be None
     * @return constexpr auto 
     */
    template <typename shape_t, typename out_channels_t, typename kernel_size_t
        , typename stride_t, typename padding_t, typename dilation_t>
    constexpr auto shape_conv2d(const shape_t& shape, out_channels_t out_channels
        , const kernel_size_t& kernel_size, const stride_t& stride, const padding_t& padding, const dilation_t& dilation)
    {
        // TODO: shape_conv2d: remove padding, assume padded before compute
        using result_t = meta::resolve_optype_t<shape_conv2d_t,shape_t,out_channels_t,kernel_size_t,stride_t,padding_t,dilation_t>;
        auto res = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            // conv op doesn't change dimension
            auto dim = len(shape);
            if constexpr (meta::is_resizable_v<result_t>) {
                res.resize(dim);
            }

            // TODO: shape_conv2d generalize to arbitrary value
            constexpr auto spatial_dims   = nmtools_tuple{meta::ct_v<-2>,meta::ct_v<-1>};
            constexpr auto n_spatial_dims = meta::ct_v<len(spatial_dims)>;
            // This controls the layout (CHW or HWC)
            // TODO: shape_conv2d: generalize "channel" axis
            constexpr auto i_out_channel  = meta::ct_v<-3>;

            const auto padding_ = [&](){
                if constexpr (is_none_v<padding_t>) {
                    return nmtools_tuple{meta::ct_v<0>,meta::ct_v<0>};
                } else if constexpr (meta::is_bounded_array_v<padding_t>) {
                    return ref(padding);
                } else {
                    return padding;
                }
            }();
            const auto dilation_ = [&](){
                if constexpr (is_none_v<dilation_t>) {
                    return nmtools_tuple{meta::ct_v<1>,meta::ct_v<1>};
                } else if constexpr (meta::is_bounded_array_v<dilation_t>) {
                    return ref(dilation);
                } else {
                    return dilation;
                }
            }();
            const auto stride_ = [&](){
                if constexpr (is_none_v<stride_t>) {
                    return nmtools_tuple{meta::ct_v<1>,meta::ct_v<1>};
                } else if constexpr (meta::is_bounded_array_v<stride_t>) {
                    return ref(stride);
                } else {
                    return stride;
                }
            }();

            // TODO: shape_conv2d error handling
            // nmtools_assert( len(kernel_size)==n_spatial_dims );
            // nmtools_assert( len(stride)==n_spatial_dims );
            // nmtools_assert( len(dilation)==n_spatial_dims );
            // nmtools_assert( len(padding)==n_spatial_dims );

            // additional -1 is to represents out_channels 
            const auto n_batch = [&](){
                constexpr auto DIM = meta::len_v<shape_t>;
                if constexpr (DIM > 0) {
                    return meta::ct_v<(DIM-n_spatial_dims-1)>;
                } else {
                    return (dim-n_spatial_dims-1);
                }
            }();

            if constexpr (meta::is_constant_index_v<decltype(n_batch)>) {
                constexpr auto N_BATCH = decltype(n_batch)::value;
                meta::template_for<N_BATCH>([&](auto i){
                    at(res,i) = at(shape,i);
                });
            } else {
                for (size_t i=0; i<n_batch; i++) {
                    at(res,i) = at(shape,i);
                }
            }
            at(res,i_out_channel) = out_channels;

            auto fill_spatial_dim_impl = [&](auto i){
                auto spatial_i  = at(spatial_dims,i);
                auto padding_i  = at(padding_,i);
                auto kernel_    = at(kernel_size,i);
                auto stride_i   = at(stride_,i);
                auto dilation_i = at(dilation_,i);
                auto dim_res    = (at(shape,spatial_i) + 2 * padding_i - dilation_i * (kernel_ - 1) - 1) / stride_i + 1;
                at(res,spatial_i) = dim_res;
            };

            if constexpr (meta::is_constant_index_v<decltype(n_spatial_dims)>) {
                constexpr auto N_SPATIAL_DIMS = decltype(n_spatial_dims)::value;
                meta::template_for<N_SPATIAL_DIMS>([&](auto i){
                    fill_spatial_dim_impl(i);
                });
            } else {
                for (size_t i=0; i<(n_spatial_dims); i++) {
                    fill_spatial_dim_impl(i);
                }
            }
        }

        return res;
    } // shape_conv2d

    struct slice_conv2d_t {};

    /**
     * @brief Compute slicing arguments to select active input for conv2d op.
     * 
     * @tparam indices_t 
     * @tparam shape_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam dilation_t 
     * @tparam groups_t 
     * @param indices 
     * @param shape 
     * @param kernel_size 
     * @param stride 
     * @param dilations 
     * @param groups 
     * @return constexpr auto 
     */
    template <typename indices_t, typename shape_t, typename kernel_size_t
        , typename stride_t, typename dilation_t, typename groups_t=none_t>
    constexpr auto slice_conv2d(const indices_t& indices, const shape_t& shape, const kernel_size_t& kernel_size
        , const stride_t& stride, const dilation_t& dilations, groups_t groups=groups_t{})
    {
        using result_t = meta::resolve_optype_t<slice_conv2d_t,indices_t,shape_t,kernel_size_t,stride_t,dilation_t,groups_t>;

        // assume element type of result_t is either (see resolve_optype)
        using element_t = meta::get_value_type_t<result_t>;
        using left_t    = meta::get_either_left_t<element_t>;
        using right_t   = meta::get_either_right_t<element_t>;

        auto make_array = [](const auto& start, const auto& stop, const auto& step){
            if constexpr (meta::is_index_array_v<left_t>) {
                using element_t = meta::get_element_type_t<left_t>;
                // assume len(array) is 3
                return left_t{(element_t)start,(element_t)stop,(element_t)step};
            } else /* if constexpr (meta::is_index_array_v<right_t>) */ {
                using element_t = meta::get_element_type_t<left_t>;
                return right_t{(element_t)start,(element_t)stop,(element_t)step};
            }
        };
        constexpr auto index_vtype = [](){
            if constexpr (meta::is_index_v<left_t>) {
                return meta::as_value_v<left_t>;
            } else {
                return meta::as_value_v<right_t>;
            }
        }();
        using index_t = meta::type_t<decltype(index_vtype)>;

        auto res = result_t {};

        auto dim = len(shape);
        if constexpr (meta::is_resizable_v<result_t>) {
            res.resize(dim);
        }

        // TODO: slice_conv2d generalize to arbitrary value
        constexpr auto spatial_dims   = nmtools_array{-2,-1};
        constexpr auto n_spatial_dims = len(spatial_dims);
        // This controls the layout (CHW or HWC)
        // TODO: slice_conv2d: generalize "channel" axis
        constexpr auto i_out_channel  = meta::ct_v<-3>;

        auto n_batch = (dim-n_spatial_dims-1);
        for (size_t i=0; i<n_batch; i++) {
            auto index_i = at(indices,i);
            // need explicit cast on wasm 
            at(res,i) = static_cast<index_t>(index_i);
        }
        // the slice at output channel axis depends on number of groups
        // currently only support depthwise or full conv
        // TODO: slice_conv2d: support other configuration of groups, e.g. C=4, groups=2
        auto groups_ = [&](){
            if constexpr (is_none_v<groups_t>) {
                return meta::ct_v<1>;
            } else {
                return groups;
            }
        }();
        if (groups_ == 1) {
            // "normal" conv
            at(res,i_out_channel) = make_array(0,at(shape,i_out_channel),1);
        } else {
            // "depth-wise" conv
            at(res,i_out_channel) = static_cast<index_t>(at(indices,i_out_channel));
        }
        auto dilations_ = [&](){
            if constexpr (is_none_v<dilation_t>) {
                return nmtools_array<size_t,2>{1,1};
            } else {
                return ref(dilations);
            }
        }();
        auto stride_ = [&](){
            if constexpr (is_none_v<stride_t>) {
                return nmtools_array<size_t,2>{1,1};
            } else {
                return ref(stride);
            }
        }();

        for (size_t i=0; i<(n_spatial_dims); i++)
        {
            [[maybe_unused]] auto dilation_i = at(dilations_,i);

            auto kernel_i  = at(kernel_size,i);
            auto spatial_i = at(spatial_dims,i);
            auto stride_i  = at(stride_,i);
            auto start_i   = at(indices,spatial_i) * stride_i;
            auto stop_i    = start_i + kernel_i;
            // TODO: implement dilation
            at(res,spatial_i) = make_array(start_i,stop_i,1);
        }

        return res;
    } // slice_conv2d

} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_CONV2D_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct SLICE_CONV2D_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename out_channels_t, typename kernel_size_t
        , typename stride_t, typename padding_t, typename dilation_t>
    struct resolve_optype<void, index::shape_conv2d_t, shape_t, out_channels_t, kernel_size_t
        , stride_t, padding_t, dilation_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                (is_constant_index_array_v<shape_t> || is_clipped_index_array_v<shape_t>)
                && is_constant_index_v<out_channels_t>
                && is_constant_index_array_v<kernel_size_t>
                && (is_constant_index_array_v<stride_t> || is_none_v<stride_t>)
                && (is_constant_index_array_v<padding_t> || is_none_v<padding_t>)
                && (is_constant_index_array_v<dilation_t> || is_none_v<dilation_t>)
            ) {
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto out_channels = to_value_v<out_channels_t>;
                constexpr auto kernel_size  = to_value_v<kernel_size_t>;
                constexpr auto stride   = to_value_v<stride_t>;
                constexpr auto padding  = to_value_v<padding_t>;
                constexpr auto dilation = to_value_v<dilation_t>;
                constexpr auto result = index::shape_conv2d(shape,out_channels,kernel_size,stride,padding,dilation);
                return meta::template_reduce<nmtools::len(result)>([&](auto init, auto index){
                    constexpr auto I = nmtools::at(result,index);
                    using init_t = type_t<decltype(init)>;
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        using type = append_type_t<init_t,ct<I>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,clipped_size_t<I>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_constant_index_array_v<shape_t> || is_clipped_index_array_v<shape_t>) {
                // TODO: try to deduce max size
                using shape_type = remove_cvref_t<decltype(to_value_v<shape_t>)>;
                using type = resolve_optype_t<index::shape_conv2d_t,shape_type,out_channels_t,kernel_size_t,stride_t,padding_t,dilation_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<kernel_size_t>) {
                using kernel_size_type = remove_cvref_t<decltype(to_value_v<kernel_size_t>)>;
                using type = resolve_optype_t<index::shape_conv2d_t,shape_t,out_channels_t,kernel_size_type,stride_t,padding_t,dilation_t>;
                return as_value_v<type>;
            } else if constexpr (
                    is_index_array_v<shape_t>
                &&  is_index_v<out_channels_t>
                &&  is_index_array_v<kernel_size_t>
                && (is_index_array_v<stride_t> || is_none_v<stride_t>)
                && (is_index_array_v<padding_t> || is_none_v<padding_t>)
                && (is_index_array_v<dilation_t> || is_none_v<dilation_t>)
            ) {
                using type = transform_bounded_array_t<shape_t>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_CONV2D_UNSUPPORTED<shape_t,out_channels_t,kernel_size_t,stride_t,padding_t,dilation_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename indices_t, typename shape_t, typename kernel_size_t
        , typename stride_t, typename dilation_t, typename groups_t>
    struct resolve_optype<void, index::slice_conv2d_t, indices_t, shape_t, kernel_size_t
        , stride_t, dilation_t, groups_t>
    {
        static constexpr auto vtype = [](){
            // TODO: compile-time compute when possible
            if constexpr (
                   is_index_array_v<shape_t>
                && is_index_array_v<shape_t>
                && is_index_array_v<kernel_size_t>
            ) {
                // array is useful for "spatial axis"
                // index if useful for "batch axis"
                // TODO: try to infer index type, instead of strictly size_t
                using array_t = nmtools_array<size_t,3>;
                using index_t = size_t;
                // TODO: allow array
                using type = nmtools_list<nmtools_either<index_t,array_t>>;
                return as_value_v<type>;
            } else {
                using type = error::SLICE_CONV2D_UNSUPPORTED<indices_t,shape_t,kernel_size_t,stride_t,dilation_t,groups_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_CONV_HPP