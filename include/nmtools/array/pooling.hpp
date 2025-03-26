#ifndef NMTOOLS_ARRAY_VIEW_POOLING_HPP
#define NMTOOLS_ARRAY_VIEW_POOLING_HPP

#include "nmtools/index/pooling.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/array/slice.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/array/mean.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/tiling_window.hpp"
#include "nmtools/array/sliding_window.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    template <typename src_shape_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t=meta::false_type>
    constexpr auto pool_slice(const src_shape_t& src_shape, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        [[maybe_unused]]
        auto m_kernel_size = [&](){
            if constexpr (meta::is_index_v<kernel_size_t>) {
                return nmtools_tuple{kernel_size,kernel_size};
            } else {
                using m_kernel_size_t = nmtools_array<nm_size_t,2>;
                return m_kernel_size_t{
                    static_cast<nm_size_t>(at(kernel_size,meta::ct_v<0>))
                    , static_cast<nm_size_t>(at(kernel_size,meta::ct_v<1>))
                };
            }
        }();
        [[maybe_unused]]
        auto m_stride = [&](){
            if constexpr (is_none_v<stride_t>) {
                return m_kernel_size;
            } else if constexpr (meta::is_index_v<stride_t>) {
                return nmtools_tuple{stride,stride};
            } else {
                using m_stride_t = nmtools_array<nm_size_t,2>;
                return m_stride_t{
                    static_cast<nm_size_t>(at(stride,meta::ct_v<0>))
                    , static_cast<nm_size_t>(at(stride,meta::ct_v<1>))
                };
            }
        }();
        [[maybe_unused]]
        auto remainders = [&](){
            using remainders_t = nmtools_array<nm_size_t,2>;
            return remainders_t{
                static_cast<nm_size_t>(at(src_shape,meta::ct_v<-2>) % at(m_kernel_size,0))
                , static_cast<nm_size_t>(at(src_shape,meta::ct_v<-1>) % at(m_kernel_size,1))
            };
        }();

        using result_t = nmtools_tuple<ellipsis_t,nmtools_tuple<none_t,none_t,nm_size_t>,nmtools_tuple<none_t,none_t,nm_size_t>>;
        auto result = result_t {};

        nmtools::get<1>(result) = nmtools_tuple{None,None,at(m_stride,meta::ct_v<0>)};
        nmtools::get<2>(result) = nmtools_tuple{None,None,at(m_stride,meta::ct_v<1>)};
        if (ceil_mode) {
            if (at(m_kernel_size,0) * at(m_stride,0) >= at(src_shape,meta::ct_v<-2>)) {
                nmtools::get<1>(result) = nmtools_tuple{None,None,1};
            }
            if (at(m_kernel_size,1) * at(m_stride,1) >= at(src_shape,meta::ct_v<-1>)) {
                nmtools::get<2>(result) = nmtools_tuple{None,None,1};
            }
        }
        return result;
    } // pool_slice
    
    struct slice_poolnd_t {};

    template <typename nd_t, typename src_shape_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    constexpr auto slice_poolnd(nd_t, const src_shape_t& src_shape, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        using result_t = meta::resolve_optype_t<slice_poolnd_t,nd_t,src_shape_t,kernel_size_t,stride_t,ceil_mode_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            auto kernel_dim = len(kernel_size);

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(kernel_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)kernel_dim; i++) {
                at(result,i) = 1;
            }

            constexpr auto N = nd_t::value;
            auto axis = meta::template_reduce<N>([](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                return utility::tuple_append(init,meta::ct_v<-(N-I)>);
            },nmtools_tuple{});

            for (nm_size_t i=0; i<(nm_size_t)N; i++) {
                auto ai = at(axis,i);
                if (ceil_mode) {
                    auto d = at(src_shape,ai) / at(kernel_size,i);
                    at(result,i) = d;
                } else {
                    at(result,i) = at(stride,i);
                }
            }
        }

        return result;
    }
}

namespace nmtools::view
{
    /**
     * @brief Pool2D view implementation
     * 
     * @tparam reducer_t 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     */
    template <typename reducer_t, typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    struct pool2d_t
    {
        // must remove address space to handle error: field may not be qualified with an address space
        using reducer_type     = meta::remove_address_space_t<reducer_t>; // assume by value, copyable
        using array_type       = resolve_array_type_t<array_t>;
        using kernel_size_type = resolve_attribute_type_t<kernel_size_t>;
        using stride_type      = resolve_attribute_type_t<stride_t>;
        using ceil_mode_type   = resolve_attribute_type_t<ceil_mode_t>;
        using src_shape_type   = decltype(nmtools::shape(meta::declval<array_t>()));
        using dst_shape_type   = meta::resolve_optype_t<index::shape_pool2d_t,src_shape_type,kernel_size_t,stride_t,ceil_mode_t>;

        reducer_type     op;
        array_type       array;
        kernel_size_type kernel_size;
        stride_type      stride;
        ceil_mode_type   ceil_mode;
        src_shape_type   src_shape;
        dst_shape_type   dst_shape;

        constexpr pool2d_t(const reducer_t& op, const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode)
            : op(op), array(initialize<array_type>(array))
            , kernel_size(init_attribute<kernel_size_type>(kernel_size))
            , stride(init_attribute<stride_type>(stride))
            , ceil_mode(init_attribute<ceil_mode_type>(ceil_mode))
            , src_shape(nmtools::shape(array))
            , dst_shape(index::shape_pool2d(src_shape,kernel_size,stride,ceil_mode))
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto dim() const
        {
            return len(dst_shape);
        }

        constexpr auto shape() const
        {
            return dst_shape;
        }

        template <typename...size_types>
        constexpr auto operator()(const size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            auto slices = index::slice_pool2d(indices_,src_shape,kernel_size,stride,ceil_mode);
            if constexpr (meta::is_pointer_v<array_type>) {
                auto sliced = view::apply_slice(*array,slices);
                return op(sliced);
            } else {
                auto sliced = view::apply_slice(array,slices);
                return op(sliced);
            }
        } // operator()
    }; // pool2d_t

    struct max_reducer_t
    {
        template <typename sliced_t>
        constexpr auto operator()(const sliced_t& sliced) const
        {
            #if defined(NMTOOLS_OPENCL_BUILD_KERNELS)
            // #if 0
            using element_type = meta::get_element_type_t<sliced_t>;
            auto flat_slice = flatten(sliced);
            nm_size_t n = size(flat_slice);
            auto result = (element_type)nmtools::at(flat_slice,(nm_index_t)0);
            for (nm_size_t i=1; i<n; i++) {
                auto element_i = (element_type)nmtools::at(flat_slice,(nm_index_t)i);
                result = (result > element_i ? result : element_i);
            }
            return result;
            #else // NMTOOLS_OPENCL_BUILD_KERNELS
            return reduce_maximum(sliced,None,None,False);
            #endif // NMTOOLS_OPENCL_BUILD_KERNELS
        };
    };

    struct avg_reducer_t
    {
        // TODO: fix value_type inference
        using value_type = float;

        template <typename sliced_t>
        constexpr auto operator()(const sliced_t& sliced) const
        {
            return view::mean(sliced,None,None,False);
        };
    };

    // TODO: implement padding
    // TODO: implement dilation
    /**
     * @brief Generic pool2d operation
     * 
     * @tparam reducer_t 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param reducer       Callable on a slice
     * @param array 
     * @param kernel_size 
     * @param stride 
     * @param ceil_mode 
     * @return constexpr auto 
     */
    template <typename reducer_t, typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    nmtools_view_attribute
    constexpr auto pool2d(const reducer_t& reducer, const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode)
    {
        using view_t = decorator_t<pool2d_t, reducer_t, array_t, kernel_size_t, stride_t, ceil_mode_t>;
        return view_t{{reducer, array, kernel_size, stride, ceil_mode}};
    }

    // TODO: implement padding
    // TODO: implement dilation
    /**
     * @brief Construct a pool2d view with max operation.
     * 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param array         input array
     * @param kernel_size   the size of the window of pooling op
     * @param stride        the stride of the window
     * @param ceil_mode 
     * @return constexpr auto 
     */
    template <typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t=meta::false_type>
    nmtools_view_attribute
    constexpr auto max_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        return view::pool2d(max_reducer_t{},array,kernel_size,stride,ceil_mode);
    }

    // TODO: implement padding
    // TODO: implement dilation
    /**
     * @brief Construct a pool2d view with average op.
     * 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param array         input array
     * @param kernel_size   size of pooling region
     * @param stride        stride of pooling operation
     * @param ceil_mode 
     * @return constexpr auto 
     */
    template <typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    nmtools_view_attribute
    constexpr auto avg_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode)
    {
        return view::pool2d(avg_reducer_t{},array,kernel_size,stride,ceil_mode);
    }

    template <typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t=meta::false_type>
    constexpr auto max_pool2dv2(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t=ceil_mode_t{})
    {
        auto src_shape = shape<true>(array);
        auto axis = nmtools_tuple{meta::ct_v<-2>,meta::ct_v<-1>};
        auto tiled = view::sliding_window(array,kernel_size,axis);
        auto reduced = view::reduce_maximum(tiled,axis);
        // constexpr auto ceil_mode = ceil_mode_t::value;
        // if constexpr (!ceil_mode) {
            auto slice_args = index::pool_slice(src_shape,kernel_size,stride,ceil_mode_t{});
            return view::apply_slice(reduced,slice_args);
        // } else {
        //     return reduced;
        // }
    }

    template <typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t=meta::false_type>
    constexpr auto avg_pool2dv2(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t=ceil_mode_t{})
    {
        auto src_shape = shape<true>(array);
        auto axis = nmtools_tuple{meta::ct_v<-2>,meta::ct_v<-1>};
        auto tiled = view::sliding_window(array,kernel_size,axis);
        auto reduced = view::mean(tiled,axis);
        // constexpr auto ceil_mode = ceil_mode_t::value;
        // if constexpr (!ceil_mode) {
            auto slice_args = index::pool_slice(src_shape,kernel_size,stride,ceil_mode_t{});
            return view::apply_slice(reduced,slice_args);
        // } else {
        //     return reduced;
        // }
    }

    template <typename array_t, typename kernel_size_t, typename stride_t=none_t, typename ceil_mode_t=meta::false_type>
    constexpr auto pool2d(const array_t& array, const kernel_size_t& kernel_size, [[maybe_unused]] const stride_t& stride=stride_t{}, [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        auto axis = nmtools_tuple{meta::ct_v<-2>,meta::ct_v<-1>};
        if constexpr (is_none_v<stride_t>) {
            auto tiled = view::sliding_window(array,kernel_size,axis,kernel_size);
            return tiled;
        } else {
            auto tiled = view::sliding_window(array,kernel_size,axis,stride);
            return tiled;
        }
    }
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename reducer_t, typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    struct fixed_size<
        view::decorator_t< view::pool2d_t, reducer_t, array_t, kernel_size_t, stride_t, ceil_mode_t>
    >
    {
        using view_type  = view::pool2d_t< reducer_t, array_t, kernel_size_t, stride_t, ceil_mode_t>;
        using shape_type = typename view_type::dst_shape_type;

        static constexpr auto value = [](){
            // the size can only be known if shape is constant, since
            // kernel size, stride, and ceil mode change the resulting shape
            if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    template <typename reducer_t, typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    struct bounded_size<
        view::decorator_t< view::pool2d_t, reducer_t, array_t, kernel_size_t, stride_t, ceil_mode_t>
    > : fixed_size<
        view::decorator_t< view::pool2d_t, reducer_t, array_t, kernel_size_t, stride_t, ceil_mode_t>
    > {};

    template <typename reducer_t, typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    struct is_ndarray<
        view::decorator_t< view::pool2d_t, reducer_t, array_t, kernel_size_t, stride_t, ceil_mode_t>
    >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    }; // is_ndarray

    template <typename reducer_t, typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    struct get_element_type<
        view::decorator_t< view::pool2d_t, reducer_t, array_t, kernel_size_t, stride_t, ceil_mode_t>
    >
    {
        static inline constexpr auto vtype = [](){
            // TODO: use element_type instead of value_type!
            if  constexpr (has_value_type_v<reducer_t>) {
                using type = typename reducer_t::value_type;
                return as_value_v<type>;
            } else {
                using type = get_element_type_t<array_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // is_ndarray

    // TODO: fix compile-time shape inference
} // namespace nmtools::meta

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

    template <typename reducer_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::pool2d_t, reducer_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::pool2d_t, reducer_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            if constexpr (meta::is_same_v<reducer_t, view::max_reducer_t>) {
                return max_pool2d[view.kernel_size][view.stride][view.ceil_mode];
            } else {
                return avg_pool2d[view.kernel_size][view.stride][view.ceil_mode];
            }
        }
    };

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