#ifndef NMTOOLS_ARRAY_VIEW_POOLING_HPP
#define NMTOOLS_ARRAY_VIEW_POOLING_HPP

#include "nmtools/index/product.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/array/pad.hpp"
#include "nmtools/array/slice.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/tiling_window.hpp"
#include "nmtools/array/sliding_window.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/platform/math/constexpr.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    struct poolnd_normalize_arg_t {};

    template <typename nd_t, typename arg_t>
    constexpr auto poolnd_normalize_arg(nd_t nd, const arg_t& arg)
    {
        if constexpr (meta::is_maybe_v<arg_t>) {
            using result_t = decltype(poolnd_normalize_arg(nd,unwrap(arg)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(arg)
                ? return_t(poolnd_normalize_arg(nd,unwrap(arg)))
                : return_t(meta::Nothing)
            );
        } else {
            using result_t = meta::resolve_optype_t<poolnd_normalize_arg_t,nd_t,arg_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                auto dst_dim = nd;
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }

                for (nm_size_t i=0; i<(nm_size_t)nd; i++) {
                    if constexpr (meta::is_index_v<arg_t>) {
                        at(result,i) = arg;
                    } else {
                        at(result,i) = at(arg,i);
                    }
                }
            }

            return result;
        }
    } // poolnd_normalize_arg

    struct poolnd_normalize_stride_t {};

    template <typename nd_t, typename kernel_size_t, typename stride_t>
    constexpr auto poolnd_normalize_stride(nd_t nd
        , [[maybe_unused]] const kernel_size_t& kernel_size
        , [[maybe_unused]] const stride_t& stride)
    {
        if constexpr (meta::is_maybe_v<kernel_size_t>
            || meta::is_maybe_v<stride_t>
        ) {
            using result_t = decltype(poolnd_normalize_stride(nd,unwrap(kernel_size),unwrap(stride)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(kernel_size) && has_value(stride)
                ? return_t(poolnd_normalize_stride(nd,unwrap(kernel_size),unwrap(stride)))
                : return_t(meta::Nothing)
            );
        } else {
            using result_t = meta::resolve_optype_t<poolnd_normalize_stride_t,nd_t,kernel_size_t,stride_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                auto dst_dim = nd;
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }

                // TODO: check if len(stride) == nd if is_index_array
                // and other validation

                for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                    if constexpr (meta::is_index_array_v<stride_t>) {
                        at(result,i) = at(stride,i);
                    } else if constexpr (meta::is_index_v<stride_t>) {
                        at(result,i) = stride;
                    } else if constexpr (meta::is_index_array_v<kernel_size_t>) {
                        at(result,i) = at(kernel_size,i);
                    } else /* if constexpr (meta::is_index_v<kernel_size_t>) */ {
                        at(result,i) = kernel_size;
                    }
                }
            }

            return result;
        }
    }

    struct pool_padding_t {};

    template <typename src_shape_t, typename padding_t>
    constexpr auto pool_padding(
        [[maybe_unused]] const src_shape_t& src_shape
        , [[maybe_unused]] const padding_t& padding)
    {
        if constexpr (meta::is_maybe_v<src_shape_t> || meta::is_maybe_v<padding_t>) {
            using result_t = decltype(pool_padding(unwrap(src_shape),unwrap(padding)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(padding)
                ? return_t{pool_padding(unwrap(src_shape),unwrap(padding))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<pool_padding_t,src_shape_t,padding_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                auto src_dim = len(src_shape);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(2*src_dim);
                }

                // fill with zero
                for (nm_size_t i=0; i<(nm_size_t)src_dim*2; i++) {
                    at(result,i) = 0;
                }

                auto pad_dim = [&](){
                    if constexpr (meta::is_index_array_v<padding_t>) {
                        return len(padding);
                    } else {
                        return 1;
                    }
                }();
                for (nm_size_t i=0; i<(nm_size_t)pad_dim; i++) {
                    // pad_dim = 2, src_dim = 4
                    // i=0 -> (2,3)
                    // i=1 -> (0,1)
                    // auto idx = -nm_index_t(i+1);
                    auto idx = i;
                    auto pad_i = [&](){
                        if constexpr (meta::is_index_array_v<padding_t>) {
                            return at(padding,-nm_index_t(i+1));
                        } else {
                            return padding;
                        }
                    }();
                    at(result,idx*2) = pad_i;
                    at(result,(idx*2)+1) = pad_i;
                }
            }

            return result;
        }
    } // pool_padding

    struct pool_pad_t {};

    template <typename src_shape_t, typename kernel_size_t, typename stride_t, typename dilation_t=none_t>
    constexpr auto pool_pad(const src_shape_t& src_shape
        , const kernel_size_t& kernel_size
        , const stride_t& stride
        , [[maybe_unused]] const dilation_t& dilation=dilation_t{})
    {
        if constexpr (meta::is_maybe_v<src_shape_t>
            || meta::is_maybe_v<kernel_size_t>
            || meta::is_maybe_v<stride_t>
            || meta::is_maybe_v<dilation_t>
        ) {
            using result_t = decltype(pool_pad(unwrap(src_shape)
                , unwrap(kernel_size)
                , unwrap(stride)
                , unwrap(dilation))
            );
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape)
                && has_value(kernel_size)
                && has_value(stride)
                && has_value(dilation)
                ? return_t{pool_pad(unwrap(src_shape)
                    , unwrap(kernel_size)
                    , unwrap(stride)
                    , unwrap(dilation))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<pool_pad_t,src_shape_t,kernel_size_t,stride_t,dilation_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_fail_v<result_t>
            ) {
                auto src_dim = len(src_shape);
                auto kernel_dim = len(kernel_size);

                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(src_dim,2);
                }

                for (nm_size_t i=0; i<src_dim; i++) {
                    apply_at(result,nmtools_tuple{i,0}) = 0;
                }
                for (nm_size_t i=0; i<(nm_size_t)(src_dim-kernel_dim); i++) {
                    apply_at(result,nmtools_tuple{i,1}) = 0;
                }
                auto kd = (src_dim-kernel_dim);
                for (nm_size_t i=0; i<(nm_size_t)kernel_dim; i++) {
                    nm_index_t src_i = at(src_shape,i+kd);
                    nm_index_t stride_i = [&](){
                        if constexpr (meta::is_index_v<stride_t>) {
                            return stride;
                        } else {
                            return at(stride,i);
                        }
                    }();
                    nm_index_t kernel_i = at(kernel_size,i);
                    float idx = float(src_i - kernel_i) / stride_i;
                    nm_index_t ceil_idx = math::constexpr_ceil(idx);
                    nm_index_t floor_idx = math::constexpr_floor(idx);
                    nm_index_t f_idx = ((ceil_idx * stride_i) < src_i ? ceil_idx : floor_idx);
                    nm_index_t pad_i = f_idx * stride_i + kernel_i - src_i;
                    // when stride i is 1, all element can be covered by window, so no need to pad
                    apply_at(result,nmtools_tuple{i+kd,1}) = (pad_i > 0 ? pad_i : 0);
                }
            }

            return result;
        }
    } // pool_pad
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct POOLND_NORMALIZE_ARG_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct POOLND_NORMALIZE_STRIDE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct POOL_PADDING_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct POOL_PAD_UNSUPPORTED : detail::fail_t {};
    }

    template <typename nd_t, typename arg_t>
    struct resolve_optype<
        void, index::poolnd_normalize_arg_t, nd_t, arg_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_constant_index_v<nd_t>
                || !(is_index_v<arg_t> || is_index_array_v<arg_t>)
            ) {
                using type = error::POOLND_NORMALIZE_ARG_UNSUPPORTED<nd_t,arg_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<arg_t> || is_constant_index_v<arg_t>) {
                constexpr auto arg = to_value_v<arg_t>;
                constexpr auto result = index::poolnd_normalize_arg(nd_t{},arg);
                // TODO: check for maybe type
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                using type = nmtools_array<nm_size_t,nd_t::value>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // poolnd_normalize_arg_t

    template <typename nd_t, typename kernel_size_t, typename stride_t>
    struct resolve_optype<
        void, index::poolnd_normalize_stride_t, nd_t, kernel_size_t, stride_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_constant_index_v<nd_t>
                || !(is_index_array_v<kernel_size_t> || is_index_v<kernel_size_t>)
                || !(is_index_array_v<stride_t> || is_index_v<stride_t> || is_none_v<stride_t>)
            ) {
                using type = error::POOLND_NORMALIZE_STRIDE_UNSUPPORTED<nd_t,kernel_size_t,stride_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<kernel_size_t> || is_constant_index_v<kernel_size_t>)
                && (is_constant_index_array_v<stride_t> || is_constant_index_v<stride_t> || is_none_v<stride_t>)
            ) {
                constexpr auto kernel_size = to_value_v<kernel_size_t>;
                constexpr auto stride = to_value_v<stride_t>;
                constexpr auto result = index::poolnd_normalize_stride(nd_t{},kernel_size,stride);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = nd_t::value;
                using type = nmtools_array<nm_size_t,DIM>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // poolnd_normalize_stride_t

    template <typename src_shape_t, typename padding_t>
    struct resolve_optype<
        void, index::pool_padding_t, src_shape_t,  padding_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !(is_index_array_v<padding_t> || is_index_v<padding_t>)
            ) {
                using type = error::POOL_PADDING_UNSUPPORTED<src_shape_t,padding_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<src_shape_t>
                && (is_constant_index_array_v<padding_t> || is_constant_index_v<padding_t>)
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto padding = to_value_v<padding_t>;
                constexpr auto result = index::pool_padding(src_shape,padding);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto SRC_DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto SRC_B_DIM = bounded_size_v<src_shape_t>;
                if constexpr (SRC_DIM > 0) {
                    constexpr auto DST_DIM = SRC_DIM * 2;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)>) {
                    constexpr auto DST_B_DIM = SRC_B_DIM * 2;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // pool_padding_t

    template <typename src_shape_t, typename kernel_size_t, typename stride_t, typename dilation_t>
    struct resolve_optype<
        void, index::pool_pad_t, src_shape_t, kernel_size_t, stride_t, dilation_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_array_v<kernel_size_t>
                || !(is_index_array_v<stride_t> || is_index_v<stride_t>)
                || !(is_none_v<dilation_t> || is_index_v<dilation_t> || is_index_array_v<dilation_t>)
            ) {
                using type = error::POOL_PAD_UNSUPPORTED<src_shape_t,kernel_size_t,stride_t>;
                return as_value_v<type>;
            } else {
                constexpr auto SRC_DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto SRC_B_DIM = bounded_size_v<src_shape_t>;
                if constexpr (SRC_DIM > 0) {
                    constexpr auto DST_SIZE = SRC_DIM * 2;
                    using buffer_t = nmtools_array<nm_size_t,DST_SIZE>;
                    using shape_buffer_t = nmtools_tuple<ct<SRC_DIM>,ct<2>>;
                    using type = array::ndarray_t<buffer_t,shape_buffer_t>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(SRC_B_DIM)>) {
                    constexpr auto DST_B_SIZE = SRC_B_DIM * 2;
                    using buffer_t = nmtools_static_vector<nm_size_t,DST_B_SIZE>;
                    // doesn't support mixed shape yet
                    // TODO: support mixed shape
                    using shape_buffer_t = nmtools_array<nm_size_t,2>;
                    using type = array::ndarray_t<buffer_t,shape_buffer_t>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using buffer_t = nmtools_list<nm_size_t>;
                    using shape_buffer_t = nmtools_array<nm_size_t,2>;
                    using type = array::ndarray_t<buffer_t,shape_buffer_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

namespace nmtools::view
{
    template <typename nd_t
        , typename array_t
        , typename kernel_size_t
        , typename stride_t=none_t
        , typename padding_t=none_t
        , typename dilation_t=none_t
        , typename ceil_mode_t=meta::false_type>
    constexpr auto max_poolnd([[maybe_unused]] nd_t nd
        , const array_t& array
        , const kernel_size_t& kernel_size
        , const stride_t& stride=stride_t{}
        , [[maybe_unused]] const padding_t& padding=padding_t{}
        , [[maybe_unused]] const dilation_t& dilation=dilation_t{}
        , [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        auto n_kernel_size = index::poolnd_normalize_arg(nd,kernel_size);
        if constexpr (!meta::is_constant_index_v<ceil_mode_t>) {
            using left_t = decltype(view::max_poolnd(nd,array,n_kernel_size,stride,padding,dilation,True));
            using right_t = decltype(view::max_poolnd(nd,array,n_kernel_size,stride,padding,dilation,False));
            using result_t = nmtools_either<left_t,right_t>;
            if (ceil_mode) {
                return result_t{view::max_poolnd(nd,array,n_kernel_size,stride,padding,dilation,True)};
            } else {
                return result_t{view::max_poolnd(nd,array,n_kernel_size,stride,padding,dilation,False)};
            }
        } else if constexpr (!is_none_v<padding_t>) {
            using T = meta::get_element_type_t<array_t>;
            auto n_padding = index::poolnd_normalize_arg(nd,padding);
            auto src_shape = shape<true>(array);
            auto pad       = index::pool_padding(src_shape,n_padding);
            auto padded    = view::pad3(array,pad,meta::numeric_limits<T>::min());
            return view::max_poolnd(nd,padded,n_kernel_size,stride,None,dilation,ceil_mode);
        } else {
            auto axis = [](){
                constexpr auto N = nd_t::value;
                return meta::template_reduce<N>([](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    constexpr auto i = -(nm_index_t)(nd_t::value-I);
                    return utility::tuple_append(init,meta::ct_v<i>);
                }, nmtools_tuple{});
            }();
            if constexpr (!ceil_mode_t::value) {
                auto n_stride = index::poolnd_normalize_stride(nd,kernel_size,stride);
                auto tiled   = view::sliding_window(array,n_kernel_size,axis,n_stride,dilation);
                auto reduced = view::reduce_maximum(tiled,axis);
                return reduced;
            } else {
                auto n_stride = index::poolnd_normalize_stride(nd,kernel_size,stride);
                auto src_shape = shape<true>(array);
                using T = meta::get_element_type_t<array_t>;

                auto pad_width = index::pool_pad(src_shape,n_kernel_size,n_stride,dilation);
                auto padded    = view::pad(array,pad_width,meta::numeric_limits<T>::min());
                auto tiled     = view::sliding_window(padded,n_kernel_size,axis,n_stride,dilation);
                auto reduced   = view::reduce_maximum(tiled,axis);
                return reduced;
            }
        }
    }

    template <typename array_t
        , typename kernel_size_t
        , typename stride_t=none_t
        , typename padding_t=none_t
        , typename dilation_t=none_t
        , typename ceil_mode_t=meta::false_type>
    constexpr auto max_pool2d(const array_t& array
        , const kernel_size_t& kernel_size
        , const stride_t& stride=stride_t{}
        , [[maybe_unused]] const padding_t& padding=padding_t{}
        , [[maybe_unused]] const dilation_t& dilation=dilation_t{}
        , [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        auto nd = meta::ct_v<2>;
        return view::max_poolnd(nd,array,kernel_size,stride,padding,dilation,ceil_mode);
    }

    template <typename array_t
        , typename kernel_size_t
        , typename stride_t=none_t
        , typename padding_t=none_t
        , typename dilation_t=none_t
        , typename ceil_mode_t=meta::false_type>
    constexpr auto max_pool1d(const array_t& array
        , const kernel_size_t& kernel_size
        , const stride_t& stride=stride_t{}
        , [[maybe_unused]] const padding_t& padding=padding_t{}
        , [[maybe_unused]] const dilation_t& dilation=dilation_t{}
        , [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        auto nd = meta::ct_v<1>;
        return view::max_poolnd(nd,array,kernel_size,stride,padding,dilation,ceil_mode);
    }

    template <typename array_t
        , typename kernel_size_t
        , typename stride_t=none_t
        , typename padding_t=none_t
        , typename dilation_t=none_t
        , typename ceil_mode_t=meta::false_type>
    constexpr auto max_pool3d(const array_t& array
        , const kernel_size_t& kernel_size
        , const stride_t& stride=stride_t{}
        , [[maybe_unused]] const padding_t& padding=padding_t{}
        , [[maybe_unused]] const dilation_t& dilation=dilation_t{}
        , [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        auto nd = meta::ct_v<3>;
        return view::max_poolnd(nd,array,kernel_size,stride,padding,dilation,ceil_mode);
    }

    template <typename array_t
        , typename kernel_size_t
        , typename stride_t=none_t
        , typename padding_t=none_t
        , typename dilation_t=none_t
        , typename ceil_mode_t=meta::false_type>
    constexpr auto avg_pool2d(const array_t& array
        , const kernel_size_t& kernel_size
        , const stride_t& stride=stride_t{}
        , [[maybe_unused]] const padding_t& padding=padding_t{}
        , [[maybe_unused]] const dilation_t& dilation=dilation_t{}
        , [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        if constexpr (!meta::is_constant_index_v<ceil_mode_t>) {
            using left_t = decltype(view::avg_pool2d(array,kernel_size,stride,padding,dilation,True));
            using right_t = decltype(view::avg_pool2d(array,kernel_size,stride,padding,dilation,False));
            using result_t = nmtools_either<left_t,right_t>;
            if (ceil_mode) {
                return result_t{view::avg_pool2d(array,kernel_size,stride,padding,dilation,True)};
            } else {
                return result_t{view::avg_pool2d(array,kernel_size,stride,padding,dilation,False)};
            }
        } else if constexpr (!is_none_v<padding_t>) {
            using T = meta::get_element_type_t<array_t>;
            auto src_shape = shape<true>(array);
            auto pad       = index::pool_padding(src_shape,padding);
            auto padded    = view::pad3(array,pad,meta::numeric_limits<T>::min());
            return view::avg_pool2d(padded,kernel_size,stride,None,dilation,ceil_mode);
        } else {
            auto axis = nmtools_tuple{meta::ct_v<-2>,meta::ct_v<-1>};
            if constexpr (!ceil_mode_t::value) {
                auto tiled   = view::sliding_window(array,kernel_size,axis,stride);
                auto reduced = view::mean(tiled,axis);
                return reduced;
            } else {
                auto src_shape = shape<true>(array);
                auto pad_width = index::pool_pad(src_shape,kernel_size,stride);
                auto padded    = view::pad(array,pad_width,0);
                auto tiled     = view::sliding_window(padded,kernel_size,axis,stride);
                // TODO: generate divisor
                auto reduced = view::mean(tiled,axis);
                return reduced;
            }
        }
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_POOLING_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/pooling.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct avg_pool2d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::avg_pool2d(args...);
            }
        };

        struct max_pool2d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::max_pool2d(args...);
            }
        };
    }
    constexpr inline auto avg_pool2d = functor_t{unary_fmap_t<fun::avg_pool2d_t>{}};

    constexpr inline auto max_pool2d = functor_t{unary_fmap_t<fun::max_pool2d_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_POOLING_HPP
#define NMTOOLS_ARRAY_ARRAY_POOLING_HPP

#include "nmtools/array/pooling.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    // TODO: implement padding
    // TODO: implement dilation
    /**
     * @brief Eagerly applies a max pooling on 2D window.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param array         input array
     * @param kernel_size   the size of the window to take max
     * @param stride        the stride of the window
     * @param ceil_mode 
     * @param context       optional evaluation context
     * @param output        optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t
        , typename context_t=none_t
        , typename resolver_t=eval_result_t<>
        , typename array_t
        , typename kernel_size_t
        , typename stride_t=none_t
        , typename padding_t=none_t
        , typename dilation_t=none_t
        , typename ceil_mode_t=meta::false_type>
    constexpr auto max_pool2d(const array_t& array
        , const kernel_size_t& kernel_size
        , const stride_t& stride=stride_t{}
        , const padding_t& padding=padding_t{}
        , const dilation_t& dilation=dilation_t{}
        , ceil_mode_t ceil_mode=ceil_mode_t{}
        , context_t&& context=context_t{}
        , output_t&& output=output_t{}
        , meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto pool = view::max_pool2d(array,kernel_size,stride,padding,dilation,ceil_mode);
        return eval(pool
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // max_pool

    // TODO: implement padding
    // TODO: implement dilation
    /**
     * @brief Eagerly applies a average pooling with 2D window.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param array         input array
     * @param kernel_size   the size of the window to take average
     * @param stride        the stride of the window
     * @param ceil_mode 
     * @param context       optional evaluation context
     * @param output        optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t
        , typename context_t=none_t
        , typename resolver_t=eval_result_t<>
        , typename array_t
        , typename kernel_size_t
        , typename stride_t=none_t
        , typename padding_t=none_t
        , typename dilation_t=none_t
        , typename ceil_mode_t=meta::false_type>
    constexpr auto avg_pool2d(const array_t& array
        , const kernel_size_t& kernel_size
        , const stride_t& stride=stride_t{}
        , const padding_t& padding=padding_t{}
        , const dilation_t& dilation=dilation_t{}
        , ceil_mode_t ceil_mode=ceil_mode_t{}
        , context_t&& context=context_t{}
        , output_t&& output=output_t{}
        , meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto pool = view::avg_pool2d(array,kernel_size,stride,padding,dilation,ceil_mode);
        return eval(pool
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // avg_pool
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_POOLING_HPP