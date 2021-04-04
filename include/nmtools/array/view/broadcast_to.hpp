#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP

#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/array/index/logical_not.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_offset.hpp"

namespace nmtools::view
{
    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct broadcast_to_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;
        using shape_type = shape_t;
        using origin_axes_type = origin_axes_t;

        array_type array;
        shape_type shape_; // broadcasted shape
        origin_axes_type origin_axes; // origin axes axes

        constexpr broadcast_to_t(array_type array, shape_type shape, origin_axes_type origin_axes)
            : array(array), shape_(shape), origin_axes(origin_axes) {}
        
        constexpr decltype(auto) shape() const noexcept
        {
            return shape_;
        } // shape

        constexpr decltype(auto) dim() const noexcept
        {
            return index::tuple_size(shape_);
        } // shape

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            using ::nmtools::detail::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            auto origin_shape   = index::gather(shape_,origin_axes);
            auto origin_strides = index::compute_strides(origin_shape);
            auto origin_indices = index::gather(indices_,origin_axes);
            auto offset = index::compute_offset(origin_indices,origin_strides);

            auto tf_indices = index::compute_indices(offset,::nmtools::shape(array));
            return tf_indices;
        } // index
    }; // broadcast_to

    /**
     * @brief broadcast array to a new shape
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array The array to be broadcasted
     * @param shape The desired shape of the array
     * @return constexpr auto 
     */
    template <typename array_t, typename shape_t>
    constexpr auto broadcast_to(const array_t& array, shape_t shape)
    {
        auto ashape = ::nmtools::shape(array);
        auto [success, shape_, free] = index::broadcast_to(ashape,shape);
        assert (success
            // , "cannot broadcast shape"
        );
        auto not_free    = index::logical_not(free);
        auto origin_axes = index::nonzero(not_free);
        using origin_axes_t = decltype(origin_axes);
        // NOTE:
        // the array view itself cannot be called with constexpr directly (because it use reference)
        // but can be evaluated in constexpr
        // see also https://en.cppreference.com/w/cpp/language/constant_expression
        // Seems like constexpr variable can't hold reference.
        // clang complains with:
        //      note: reference to 'x' is not a constant expression
        // where 'x' is array
        // but this function itself (and the broadcast_to_t constructor) are still marked as constexpr
        // to let the view evaluated in constexpr context.
        return decorator_t<broadcast_to_t,array_t,shape_t,origin_axes_t>{{array,shape,origin_axes}};
    } // broadcast_to

} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct is_ndarray< view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t >>
        : is_ndarray<array_t> {};
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP