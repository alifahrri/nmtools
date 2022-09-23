#ifndef NMTOOLS_ARRAY_VIEW_ZEROS_HPP
#define NMTOOLS_ARRAY_VIEW_ZEROS_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    template <typename shape_t, typename T>
    struct zeros_t
    {
        using shape_type = resolve_attribute_type_t<shape_t>;
        using element_type = T;

        using array_type = none_t;

        shape_type shape_;

        constexpr zeros_t(const shape_t& shape)
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

            return static_cast<element_type>(0);
        } // operator()
    }; // zeros_t

    /**
     * @brief Creates zeros view with given shape and dtype.
     *
     * All elements of this views has value of 0.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape 
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto zeros(const shape_t& shape, dtype_t<T>)
    {
        using view_t = decorator_t<zeros_t, shape_t, T>;
        return view_t{{shape}};
    } // zeros
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename shape_t, typename T>
    struct get_element_type< view::decorator_t<view::zeros_t, shape_t, T> >
    {
        using type = T;
    };

    template <typename shape_t, typename T>
    struct is_ndarray< view::decorator_t< view::zeros_t, shape_t, T >>
    {
        static constexpr auto value = is_num_v<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ZEROS_HPP