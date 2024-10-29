#ifndef NMTOOLS_ARRAY_VIEW_POOLING_HPP
#define NMTOOLS_ARRAY_VIEW_POOLING_HPP

#include "nmtools/array/index/pooling.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/mean.hpp"
#include "nmtools/array/view/ufuncs/maximum.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/meta.hpp"

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
            return mean(sliced,None,None,False);
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
        return pool2d(max_reducer_t{},array,kernel_size,stride,ceil_mode);
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
        return pool2d(avg_reducer_t{},array,kernel_size,stride,ceil_mode);
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