#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

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
            using ::nmtools::array::detail::compute_indices;
            auto shape_ = ::nmtools::shape(array);
            auto indices = compute_indices(i,shape_);
            return indices;
        } // index
    }; // mutable_flatten_t

    template <typename array_t>
    constexpr auto mutable_flatten(array_t& array)
    {
        // @note using aggregate initialization
        // since decorator_t doesn't provide constructor
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

    /**
     * @brief mutable_flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array2d<view::decorator_t<view::mutable_flatten_t,array_t>> : std::false_type {};

    /**
     * @brief mutable_flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array3d<view::decorator_t<view::mutable_flatten_t,array_t>> : std::false_type {};
} // namespace nmtools::meta

namespace nmtools
{
    template <typename array_t>
    struct meta::fixed_vector_size< view::mutable_flatten_t<array_t>
        , std::enable_if_t<
            meta::is_fixed_size_ndarray_v<meta::remove_cvref_t<array_t>>
        >
    > {
        static constexpr auto _get()
        {
            constexpr auto shape_ = meta::fixed_ndarray_shape_v<meta::remove_cvref_t<array_t>>;
            constexpr auto shape  = ::nmtools::detail::make_array<std::array>(shape_);
            // compute product
            auto identity = 1;
            for (size_t i=0; i<shape.size(); i++)
                identity *= shape[i];
            // flattened array is strictly 1D
            return identity;
        } // get

        static constexpr auto value = _get();
        using value_type = decltype(_get());
    };

    template <typename array_t>
    struct meta::fixed_ndarray_shape< view::mutable_flatten_t<array_t>
        , std::enable_if_t<
            meta::is_fixed_size_ndarray_v<meta::remove_cvref_t<array_t>>
        > 
    >
    {
        static constexpr auto _get()
        {
            constexpr auto N = meta::fixed_vector_size_v<view::mutable_flatten_t<array_t>>;
            // pack integer as tuple
            return std::tuple{N};
        } // _get()

        static constexpr auto value = _get();
        using value_type = decltype(_get());
    };
} // nmtools

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_FLATTEN_HPP