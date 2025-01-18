#ifndef NMTOOLS_ARRAY_VIEW_COMPRESS_HPP
#define NMTOOLS_ARRAY_VIEW_COMPRESS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/compress.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/core/decorator.hpp"

namespace nmtools::view
{

    template <typename condition_t, typename array_t, typename axis_t>
    struct compress_t
    {
        using condition_type = resolve_attribute_type_t<condition_t>;
        using array_type = resolve_array_type_t<array_t>;
        using axis_type  = resolve_attribute_type_t<axis_t>;
        using src_shape_type = decltype(nmtools::shape</*force_index_array*/true>(meta::declval<array_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_compress_t,condition_t,src_shape_type,axis_t>;

        condition_type condition;
        array_type array;
        axis_type axis;
        dst_shape_type shape_;

        constexpr compress_t(const condition_t& condition_, const array_t& array_, const axis_t& axis_)
            : condition(init_attribute<condition_type>(condition_))
            , array(initialize<array_type>(array_))
            , axis(init_attribute<axis_type>(axis_))
            , shape_(index::shape_compress(condition_,nmtools::shape<true>(array_),axis_))
        {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            auto shape_ = detail::shape(array);
            return ::nmtools::index::compress(indices_,condition,shape_,axis);
        } // index
    }; // compress_t

    /**
     * @brief View selected slices of an array along given axis.
     * 
     * @tparam condition_t 1-D array of booleans
     * @tparam array_t 
     * @tparam axis_t 
     * @param condition array that selects which entries to return 
     * @param array array from which to extract
     * @param axis axis to take slices
     * @return constexpr auto 
     */
    template <typename condition_t, typename array_t, typename axis_t>
    constexpr auto compress(const condition_t& condition, const array_t& array, axis_t axis)
    {
        return decorator_t<compress_t,condition_t,array_t,axis_t>{{condition,array,axis}};
    } // compress
} // namespace nmtools::view

namespace nmtools::meta
{
    // compress view may change shape, so change size
    template <typename condition_t, typename array_t, typename axis_t>
    struct fixed_size<
        view::decorator_t<view::compress_t,condition_t,array_t,axis_t>
    >
    {
        using view_type = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;
        using dst_shape_type = typename view_type::dst_shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(dst_shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    template <typename condition_t, typename array_t, typename axis_t>
    struct bounded_size<
        view::decorator_t<view::compress_t,condition_t,array_t,axis_t>
    >
    {
        using view_type = view::decorator_t<view::compress_t,condition_t,array_t,axis_t>;

        static constexpr auto value = [](){
            constexpr auto fixed_size = fixed_size_v<view_type>;
            if constexpr (!is_fail_v<decltype(fixed_size)>) {
                return fixed_size;
            } else {
                return bounded_size_v<array_t>;
            }
        }();
    };

    template <typename condition_t, typename array_t, typename axis_t>
    struct is_ndarray< view::decorator_t< view::compress_t, condition_t, array_t, axis_t >>
    {
        static constexpr auto value = (is_ndarray_v<condition_t> || is_index_array_v<condition_t>) && is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_COMPRESS_HPP