#ifndef NMTOOLS_ARRAY_VIEW_ONES_HPP
#define NMTOOLS_ARRAY_VIEW_ONES_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    template <typename shape_t, typename T>
    struct ones_t
    {
        using shape_type   = resolve_attribute_type_t<shape_t>;
        using element_type = T;

        using array_type = none_t;

        shape_type shape_;

        constexpr ones_t(const shape_t& shape)
            : shape_(init_attribute<shape_type>(shape)) {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape_);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types.../*indices*/) const
        {
            // TODO: assert if indices < shape

            return static_cast<element_type>(1);
        } // operator()
    }; // ones_t

    /**
     * @brief Creates a ones view with given shape and dtype.
     * 
     * All elements in the view has value of 1.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto ones(const shape_t& shape, dtype_t<T>)
    {
        using view_t = decorator_t<ones_t, shape_t, T>;
        return view_t{{shape}};
    } // ones
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename shape_t, typename T>
    struct get_element_type< view::decorator_t<view::ones_t, shape_t, T> >
    {
        using type = T;
    };

    template <typename shape_t, typename T>
    struct is_ndarray< view::decorator_t< view::ones_t, shape_t, T >>
    {
        static constexpr auto value = is_num_v<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ONES_HPP