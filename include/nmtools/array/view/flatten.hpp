#ifndef NMTOOLS_ARRAY_VIEW_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_FLATTEN_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/product.hpp"

#include "nmtools/array/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/index.hpp"

#include <cassert>

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    template <typename array_t>
    struct flatten_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;

        array_type array;

        constexpr flatten_t(const array_t& array)
            : array(initialize<array_type>(array)) {}

        constexpr auto dim() const noexcept
        {
            // flattened array is strictly 1D
            return 1;
        } // dim

        constexpr auto shape() const noexcept
        {
            auto shape_ = detail::shape(array);
            auto N = index::product(shape_);
            // flattened array is strictly 1D
            return std::tuple{N};
        } // shape

        template <typename size_type>
        constexpr auto index(size_type i) const
        {
            using ::nmtools::array::detail::compute_indices;
            using index_t = meta::get_index_type_t<array_t>;
            auto shape_   = detail::shape(array);
            auto indices  = compute_indices(static_cast<index_t>(i),shape_);
            return indices;
        } // index
    }; // flatten_t

    template <typename array_t>
    constexpr auto flatten(const array_t& array)
    {
        // @note using aggregate initialization
        // since decorator_t doesn't provide constructor
        return decorator_t<flatten_t,array_t>{array};
    } // flatten

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array1d<view::decorator_t<view::flatten_t,array_t>> : std::true_type {};

    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array2d<view::decorator_t<view::flatten_t,array_t>> : std::false_type {};

    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array3d<view::decorator_t<view::flatten_t,array_t>> : std::false_type {};
} // namespace nmtools::meta

namespace nmtools
{
    /**
     * @brief Infer the shape of flatten view at compile time.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct meta::fixed_ndarray_shape< view::flatten_t<array_t> >
    {
        static constexpr auto value = [](){
            if constexpr (meta::is_fixed_size_ndarray_v<array_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto N     = index::product(shape);
                return std::tuple{N};
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the dimension of flatten view at compile-time.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct meta::fixed_dim < view::decorator_t<view::flatten_t, array_t> >
    {
        static constexpr auto value = 1ul;
        using value_type = size_t;
    }; // fixed_dim
} // nmtools

#endif // NMTOOLS_ARRAY_VIEW_FLATTEN_HPP