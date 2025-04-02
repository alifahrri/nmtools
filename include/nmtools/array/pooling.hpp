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
    struct pool_pad_t {};

    template <typename src_shape_t, typename kernel_size_t, typename stride_t>
    constexpr auto pool_pad(const src_shape_t& src_shape, const kernel_size_t& kernel_size, const stride_t& stride)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>
            || meta::is_maybe_v<kernel_size_t>
            || meta::is_maybe_v<stride_t>
        ) {
            using result_t = decltype(pool_pad(unwrap(src_shape),unwrap(kernel_size),unwrap(stride)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(kernel_size) && has_value(stride)
                ? return_t{pool_pad(unwrap(src_shape),unwrap(kernel_size),unwrap(stride))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<pool_pad_t,src_shape_t,kernel_size_t,stride_t>;

            auto result = result_t {};

            if constexpr (!meta::is_constant_index_array_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
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
                    nm_index_t stride_i = at(stride,i);
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
        struct POOL_PAD_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename kernel_size_t, typename stride_t>
    struct resolve_optype<
        void, index::pool_pad_t, src_shape_t, kernel_size_t, stride_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_array_v<kernel_size_t>
                || !is_index_array_v<stride_t>
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
    template <typename array_t, typename kernel_size_t, typename stride_t=none_t, typename ceil_mode_t=meta::false_type>
    constexpr auto max_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride=stride_t{}, [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        if constexpr (!meta::is_constant_index_v<ceil_mode_t>) {
            using left_t = decltype(view::max_pool2d(array,kernel_size,stride,True));
            using right_t = decltype(view::max_pool2d(array,kernel_size,stride,False));
            using result_t = nmtools_either<left_t,right_t>;
            if (ceil_mode) {
                return result_t{view::max_pool2d(array,kernel_size,stride,True)};
            } else {
                return result_t{view::max_pool2d(array,kernel_size,stride,False)};
            }
        } else {
            auto axis = nmtools_tuple{meta::ct_v<-2>,meta::ct_v<-1>};
            if constexpr (!ceil_mode_t::value) {
                auto tiled   = view::sliding_window(array,kernel_size,axis,stride);
                auto reduced = view::reduce_maximum(tiled,axis);
                return reduced;
            } else {
                auto src_shape = shape<true>(array);
                using T = meta::get_element_type_t<array_t>;

                auto pad_width = index::pool_pad(src_shape,kernel_size,stride);
                auto padded    = view::pad(array,pad_width,meta::numeric_limits<T>::min());
                auto tiled     = view::sliding_window(padded,kernel_size,axis,stride);
                auto reduced   = view::reduce_maximum(tiled,axis);
                return reduced;
            }
        }
    }

    template <typename array_t, typename kernel_size_t, typename stride_t=none_t, typename ceil_mode_t=meta::false_type>
    constexpr auto avg_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride=stride_t{}, [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        if constexpr (!meta::is_constant_index_v<ceil_mode_t>) {
            using left_t = decltype(view::avg_pool2d(array,kernel_size,stride,True));
            using right_t = decltype(view::avg_pool2d(array,kernel_size,stride,False));
            using result_t = nmtools_either<left_t,right_t>;
            if (ceil_mode) {
                return result_t{view::avg_pool2d(array,kernel_size,stride,True)};
            } else {
                return result_t{view::avg_pool2d(array,kernel_size,stride,False)};
            }
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
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t=meta::false_type>
    constexpr auto max_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode=ceil_mode_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto pool = view::max_pool2d(array,kernel_size,stride,ceil_mode);
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
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    constexpr auto avg_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto pool = view::avg_pool2d(array,kernel_size,stride,ceil_mode);
        return eval(pool
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // avg_pool
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_POOLING_HPP