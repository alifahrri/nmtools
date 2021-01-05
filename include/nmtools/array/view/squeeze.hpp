#ifndef NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP
#define NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/remove_single_dims.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    template <typename array_t>
    struct squeeze_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;

        array_type array;

        constexpr squeeze_t(array_type array)
            : array(array) {}
        
        constexpr auto shape() const noexcept
        {
            auto shape_   = ::nmtools::shape(array);
            auto squeezed = index::remove_single_dims(shape_);
            return squeezed;
        } // shape

        constexpr auto dim() const noexcept
        {
            auto shape_ = shape();
            auto dim_   = ::nmtools::shape(shape_);
            return at(dim_, 0);
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...Is) const
        {
            auto indices = [&](){
                if constexpr (meta::logical_and_v<std::is_integral<size_types>...>)
                    return std::tuple{Is...};
                else {
                    static_assert ( sizeof...(Is)==1
                        , "unsupported element access of squeeze"
                    );
                    return std::get<0>(std::tuple{Is...});
                }
            }();

            auto squeezed_shape   = shape();
            auto squeezed_strides = index::compute_strides(squeezed_shape);

            auto shape_     = ::nmtools::shape(array);
            auto offset     = index::compute_offset(indices,squeezed_strides);
            auto tf_indices = index::compute_indices(offset,shape_);

            return tf_indices;
        } // index
    }; // squeeze_t

    /**
     * @brief remove single dimensional entry from array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto squeeze(const array_t& array)
    {
        return decorator_t<squeeze_t,array_t>{{array}};
    } // squeeze
    /* @} */
} // namespace nmtools::view

namespace nmtools::meta
{
    using view::decorator_t;
    using view::squeeze_t;

    template <typename array_t>
    struct fixed_vector_size<  squeeze_t<array_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_vector_size

    template <typename array_t>
    struct fixed_matrix_size<  squeeze_t<array_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_matrix_size

    template <typename array_t>
    struct fixed_ndarray_shape<  squeeze_t<array_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename array_t>
    struct is_ndarray< decorator_t<squeeze_t,array_t> >
    {
        static inline constexpr auto value = true;
    }; // is_ndarray
}

#endif // NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP