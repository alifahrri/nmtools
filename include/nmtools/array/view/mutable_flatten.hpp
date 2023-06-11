#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    template <typename array_t>
    struct mutable_flatten_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_mutable_array_type_t<array_t>;

        array_type array;

        constexpr mutable_flatten_t(array_t& array)
            : array(initialize<array_type>(array))
        {}

        constexpr auto dim() const noexcept
        {
            // flattened array is strictly 1D
            return 1;
        } // dim

        constexpr auto shape() const noexcept
        {
            auto N = detail::size(array);
            // flattened array is strictly 1D
            return nmtools_tuple<size_t>{N};
        } // shape

        template <typename size_type>
        constexpr auto index(size_type i) const
        {
            using ::nmtools::index::compute_indices;
            auto shape_  = detail::shape(array);
            auto indices = compute_indices(i,shape_);
            return indices;
        } // index
    }; // mutable_flatten_t

    template <typename array_t>
    constexpr auto mutable_flatten(array_t& array)
    {
        // remove address space for better compatibility with existing stack
        using array_type = meta::remove_address_space_t<array_t>;
        return decorator_t<mutable_flatten_t,array_type>{array};
    } // mutable_flatten

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief mutable_flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array1d<view::decorator_t<view::mutable_flatten_t,array_t>> : meta::true_type {};
} // namespace nmtools::meta

namespace nmtools
{
    template <typename array_t>
    struct meta::fixed_ndarray_shape< view::mutable_flatten_t<array_t>
        , meta::enable_if_t<
            meta::is_fixed_size_ndarray_v<meta::remove_cvref_t<array_t>>
        > 
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<array_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto N = index::product(shape);
                return meta::make_array_type_t<size_t,1>{N};
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    };
} // nmtools

namespace nmtools::meta
{
    template <typename array_t>
    struct is_ndarray< view::decorator_t<view::mutable_flatten_t,array_t> >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
}

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP