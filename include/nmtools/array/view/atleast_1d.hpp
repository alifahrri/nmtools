#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_1D_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_1D_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view
{
    template <typename array_t>
    struct atleast_1d_t
    {
        // TODO: consider to copy when array_t is simply arithmetic type
        using array_type = resolve_array_type_t<array_t>;

        array_type array;

        constexpr atleast_1d_t(const array_t& array)
            : array(initialize(array, meta::as_value_v<array_type>)) {}
        
        constexpr auto shape() const
        {
            if constexpr (std::is_arithmetic_v<array_t>)
                return std::array{1};
            else return detail::shape(array);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // for now, assume indices is generated such that
            // they are within range
            // TODO: move to "index" member function
            // TODO: check shape
            if constexpr (std::is_arithmetic_v<array_t>) {
                return array;
            } else {
                auto indices_ = pack_indices(indices...);
                if constexpr (std::is_pointer_v<array_type>) {
                    return apply_at(*array, indices_);
                } else {
                    return apply_at(array, indices_);
                }
            }
        } // operator()
    }; // atleast_1d_t

    /**
     * @brief Create a atleast_1d_t view to a given array.
     * 
     * Views array with at least 1 dimension. Also accept scalar value.
     *
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto atleast_1d(const array_t& array)
    {
        using view_t = decorator_t<atleast_1d_t, array_t>;
        return view_t{{array}};
    } // atleast_1d
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t>
    struct get_element_type< view::decorator_t<view::atleast_1d_t, array_t> >
    {
        using type = std::conditional_t<
            std::is_arithmetic_v<array_t>, array_t,
            get_element_type_t<array_t>
        >;
    };

    template <typename array_t>
    struct fixed_ndarray_shape< view::atleast_1d_t<array_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (std::is_arithmetic_v<array_t>)
                return std::array{1};
            else return fixed_ndarray_shape_v<array_t>;
        }();
        using value_type = decltype(value);
    };

    template <typename array_t>
    struct fixed_dim<
        view::decorator_t< view::atleast_1d_t, array_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_num_v<array_t>) {
                return 1;
            } else if constexpr (is_fixed_dim_ndarray_v<array_t>) {
                return fixed_dim_v<array_t>;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_dim

    template <typename array_t>
    struct is_ndarray< view::decorator_t< view::atleast_1d_t, array_t >>
    {
        static constexpr auto value = std::is_arithmetic_v<array_t> || is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_1D_HPP