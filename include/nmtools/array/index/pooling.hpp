#ifndef NMTOOLS_ARRAY_INDEX_POOLING_HPP
#define NMTOOLS_ARRAY_INDEX_POOLING_HPP

#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/assert.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/math.hpp"

#include "nmtools/array/index/ref.hpp"

namespace nmtools::index
{
    struct shape_pool2d_t {};

    // TODO: implement dilation
    /**
     * @brief Compute the resulting shape of pool2d operation
     * 
     * @tparam shape_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param shape         original array shape
     * @param kernel_size   size of pooling operation
     * @param stride        stride of pooling operation
     * @param ceil_mode     when true, use ceil instead of floor to compute shape
     * @return constexpr auto 
     */
    template <typename shape_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t=meta::false_type>
    constexpr auto shape_pool2d(const shape_t& shape, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        using result_t = meta::resolve_optype_t<shape_pool2d_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        // TODO: shape_pool2d error handling
        auto res = result_t {};

        auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<result_t>) {
            res.resize(dim);
        }

        // TODO: shape_pool2d generalize to arbitrary value
        constexpr auto spatial_dim   = nmtools_array{-2,-1};
        constexpr auto n_spatial_dim = len(spatial_dim);
        constexpr auto dilations = 1;
        constexpr auto pad = 0;

        auto n_batch = (dim-n_spatial_dim);
        for (size_t i=0; i<n_batch; i++) {
            // TODO: do not use i, check for batch_dim (that is not on spatial dim)
            at(res,i) = at(shape,i);
        }

        // quick workaround to support fixed index array
        auto kernel_size_ = [&](){
            if constexpr (meta::is_constant_index_array_v<kernel_size_t>) {
                return meta::to_value_v<kernel_size_t>;
            } else {
                return index::ref(kernel_size);
            }
        }();
        auto stride_ = [&](){
            if constexpr (meta::is_constant_index_array_v<stride_t>) {
                return meta::to_value_v<stride_t>;
            } else {
                return index::ref(stride);
            }
        }();
        for (size_t i=0; i<n_spatial_dim; i++) {
            auto spatial_i = at(spatial_dim,i);
            auto r_shape_i = float(at(shape,spatial_i) + pad - ((at(kernel_size_,spatial_i) - 1) * dilations + 1)) / at(stride_,spatial_i) + 1;
            if (static_cast<bool>(ceil_mode)) {
                at(res,spatial_i) = math::ceil(r_shape_i);
            } else {
                at(res,spatial_i) = math::floor(r_shape_i);
            }
        }

        return res;
    } // shape_pool2d

    struct slice_pool2d_t {};

    /**
     * @brief Compute slicing args for pooling arguments
     * 
     * @tparam indices_t 
     * @tparam shape_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param indices       indices with respect to dst shape
     * @param shape         original array shape
     * @param kernel_size 
     * @param stride 
     * @param ceil_mode 
     * @return constexpr auto 
     */
    template <typename indices_t, typename shape_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t=meta::false_type>
    constexpr auto slice_pool2d(const indices_t& indices, const shape_t& shape, const kernel_size_t& kernel_size, const stride_t& stride, [[maybe_unused]] ceil_mode_t ceil_mode=ceil_mode_t{})
    {
        using result_t = meta::resolve_optype_t<slice_pool2d_t,indices_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
        // TODO: index pool2d error handling
        // nmtools_cassert( len(shape) == len(dim), "len(indices) must be equal to len(shape)" );

        auto res = result_t {};

        auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<result_t>) {
            res.resize(dim);
        }

        // TODO: shape_pool2d generalize to arbitrary value
        constexpr auto spatial_dim   = nmtools_array{-2,-1};
        constexpr auto n_spatial_dim = len(spatial_dim);
        [[maybe_unused]] constexpr auto dilations = 1;
        [[maybe_unused]] constexpr auto pad = 0;

        using idx_t = meta::get_element_type_t<meta::remove_cvref_t<decltype(at(res,0))>>;

        auto n_batch = (dim-n_spatial_dim);
        for (size_t i=0; i<n_batch; i++) {
            // TODO: do not use i, check for batch_dim (that is not on spatial dim)
            // start,stop,step tuple
            // for batch dimension this is just "select only this element"
            at(res,i) = {(idx_t)at(indices,i),(idx_t)at(indices,i)+1,(idx_t)1};
        }

        // quick workaround to support fixed index array
        auto kernel_size_ = [&](){
            if constexpr (meta::is_constant_index_array_v<kernel_size_t>) {
                return meta::to_value_v<kernel_size_t>;
            } else {
                return index::ref(kernel_size);
            }
        }();
        auto stride_ = [&](){
            if constexpr (meta::is_constant_index_array_v<stride_t>) {
                return meta::to_value_v<stride_t>;
            } else {
                return index::ref(stride);
            }
        }();

        for (size_t i=0; i<n_spatial_dim; i++) {
            auto spatial_i = at(spatial_dim,i);
            auto start = at(stride_,spatial_i) * at(indices,spatial_i);
            auto stop  = at(stride_,spatial_i) * at(indices,spatial_i) + at(kernel_size_,spatial_i);
            at(res,spatial_i) = {(idx_t)start,(idx_t)stop,(idx_t)1};
        }

        return res;
    } // slice_pool2d
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_POOL2D_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct STRIDE_POOL2D_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename shape_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    struct resolve_optype<void,index::shape_pool2d_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                   is_index_array_v<shape_t>
                && is_index_array_v<kernel_size_t>
                && is_index_array_v<stride_t>
            ) {
                using type = transform_bounded_array_t<shape_t>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_POOL2D_UNSUPPORTED<shape_t,kernel_size_t,stride_t,ceil_mode_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename indices_t, typename shape_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    struct resolve_optype<void,index::slice_pool2d_t,indices_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (
                   is_index_array_v<indices_t>
                && is_index_array_v<shape_t>
                && is_index_array_v<kernel_size_t>
                && is_index_array_v<stride_t>
            ) {
                // TODO: consider to use index_type/similar instead of int
                using slice_t = nmtools_array<int,3>;
                if constexpr (is_fixed_index_array_v<shape_t>) {
                    constexpr auto DIM = len_v<shape_t>;
                    using type = nmtools_array<slice_t,DIM>;
                    return as_value_v<type>;
                } else {
                    // don't know the length until runtime
                    using type = nmtools_list<slice_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::STRIDE_POOL2D_UNSUPPORTED<indices_t,shape_t,kernel_size_t,stride_t,ceil_mode_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_POOLING_HPP