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
        using array_type = const array_t&;
        using repeats_type = repeats_t;
        using axis_type = axis_t;

        array_type array;
        repeats_type repeats;
        axis_type axis;

        constexpr repeat_t(array_type array, repeats_type repeats, axis_type axis)
            : array(array), repeats(repeats), axis(axis) {}
        
        constexpr decltype(auto) shape() const
        {
            auto shape_ = ::nmtools::shape(array);
            return index::shape_repeat(shape_,repeats,axis);
        } // shape

        constexpr decltype(auto) dim() const
        {
            if constexpr (is_none_v<axis_type>)
                return 1;
            else
                return ::nmtools::dim(array);
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            using ::nmtools::detail::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for transpose view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            auto shape_ = ::nmtools::shape(array);
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
    constexpr auto repeat(const array_t& array, repeats_t repeats, axis_t axis)
    {
        return decorator_t<repeat_t,array_t,repeats_t,axis_t>{{array,repeats,axis}};
    } // repeat
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename repeats_t, typename axis_t>
    struct is_ndarray< view::decorator_t<view::repeat_t,array_t,repeats_t,axis_t> >
    {
        static inline constexpr auto value = true;
    }; // is_ndarray
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_REPEAT_HPP