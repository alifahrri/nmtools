#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/meta.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"

#include <cassert>

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
        using array_type = array_t&;

        array_type array;

        constexpr mutable_flatten_t(array_type array) : array(array) {}

        constexpr auto dim() const noexcept
        {
            // flattened array is strictly 1D
            return 1;
        } // dim

        constexpr auto shape() const noexcept
        {
            // assuming fixed dim array
            auto shape_ = ::nmtools::shape(array);
            // compute product
            auto identity = 1;
            if constexpr (meta::is_specialization_v<decltype(shape_),std::tuple> || meta::is_specialization_v<decltype(shape_),std::pair>)
            {
                constexpr auto n = std::tuple_size_v<decltype(shape_)>;
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    identity *= std::get<i>(shape_);
                });
            }
            else
                for (size_t i=0; i<shape_.size(); i++)
                    identity *= shape_[i];
            // flattened array is strictly 1D
            return std::tuple{identity};
        } // shape

        template <typename size_type>
        constexpr auto index(size_type i) const
        {
            using ::nmtools::index::compute_indices;
            auto shape_  = ::nmtools::shape(array);
            auto indices = compute_indices(i,shape_);
            return indices;
        } // index
    }; // mutable_flatten_t

    template <typename array_t>
    constexpr auto mutable_flatten(array_t& array)
    {
        return decorator_t<mutable_flatten_t,array_t>{array};
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
    struct is_array1d<view::decorator_t<view::mutable_flatten_t,array_t>> : std::true_type {};
} // namespace nmtools::meta

namespace nmtools
{
    template <typename array_t>
    struct meta::fixed_ndarray_shape< view::mutable_flatten_t<array_t>
        , std::enable_if_t<
            meta::is_fixed_size_ndarray_v<meta::remove_cvref_t<array_t>>
        > 
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<array_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto N = index::product(shape);
                // TODO: wrap metafunction to create array type
                return std::array{N};
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