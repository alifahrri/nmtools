#ifndef NMTOOLS_ARRAY_VIEW_REPEAT_HPP
#define NMTOOLS_ARRAY_VIEW_REPEAT_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/array/index/repeat.hpp"
#include "nmtools/array/index/shape_repeat.hpp"

namespace nmtools::view
{
    template <typename array_t, typename repeats_t, typename axis_t>
    struct repeat_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        using array_type   = resolve_array_type_t<array_t>;
        using repeats_type = resolve_attribute_type_t<repeats_t>;
        using axis_type    = resolve_attribute_type_t<axis_t>;

        array_type array;
        repeats_type repeats;
        axis_type axis;

        constexpr repeat_t(const array_t& array, const repeats_t& repeats, const axis_t& axis)
            : array(initialize(array, meta::as_value_v<array_type>))
            , repeats(init_attribute(repeats, meta::as_value_v<repeats_type>))
            , axis(init_attribute(axis, meta::as_value_v<axis_type>)) {}
        
        constexpr decltype(auto) shape() const
        {
            auto shape_ = detail::shape(array);
            return index::shape_repeat(shape_,repeats,axis);
        } // shape

        constexpr decltype(auto) dim() const
        {
            if constexpr (is_none_v<axis_type>)
                return 1;
            else
                return detail::dim(array);
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            auto shape_   = detail::shape(array);
            return index::repeat(shape_,indices_,repeats,axis);
        } // index
    }; // repeat_t

    /**
     * @brief Repeats elements of an array
     * 
     * @tparam array_t 
     * @tparam repeats_t integral type or array1d
     * @tparam axis_t integral type or none_t
     * @param array Input array
     * @param repeats The number of repetitions for each element
     * @param axis The axis along which to repeat values. If None, use the flattened input array.
     * @return constexpr auto 
     */
    template <typename array_t, typename repeats_t, typename axis_t>
    constexpr auto repeat(const array_t& array, const repeats_t& repeats, const axis_t& axis)
    {
        return decorator_t<repeat_t,array_t,repeats_t,axis_t>{{array,repeats,axis}};
    } // repeat
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Infer fixed ndarray shape at compile-time for repeat view.
     * 
     * @tparam array_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename repeats_t, typename axis_t>
    struct fixed_ndarray_shape< view::decorator_t<view::repeat_t,array_t,repeats_t,axis_t> >
    {
        static constexpr auto value = [](){
            if constexpr (
                   is_fixed_size_ndarray_v<array_t>
                && (is_constant_index_array_v<repeats_t> || is_constant_index_v<repeats_t>)
                && (is_constant_index_v<axis_t> || is_none_v<axis_t>)
            ) {
                constexpr auto shape   = fixed_ndarray_shape_v<array_t>;
                constexpr auto repeats = repeats_t{};
                constexpr auto axis    = axis_t{};
                return index::shape_repeat(shape,repeats,axis);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the dimension of repeat view at compile-time.
     * 
     * @tparam array_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename repeats_t, typename axis_t>
    struct fixed_dim<
        view::decorator_t<view::repeat_t,array_t,repeats_t,axis_t>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_none_v<axis_t>) {
                return 1;
            } else if constexpr (is_fixed_dim_ndarray_v<array_t>) {
                return fixed_dim_v<array_t>;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: don't convert fail to void type
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_dim

    template <typename array_t, typename repeats_t, typename axis_t>
    struct is_ndarray< view::decorator_t<view::repeat_t,array_t,repeats_t,axis_t> >
        : is_ndarray<array_t> {};
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_REPEAT_HPP