#ifndef NMTOOLS_ARRAY_UTILITY_APPLY_RESIZE_HPP
#define NMTOOLS_ARRAY_UTILITY_APPLY_RESIZE_HPP

#include "nmtools/meta.hpp"

#include <utility>

namespace nmtools
{
    namespace detail 
    {
        template <typename array_t, typename size_type, typename...size_types>
        auto resize(array_t& array, size_type size_0, size_types...size_n) -> array_t&
        {
            if constexpr (meta::is_resizeable_nd_v<array_t,size_type,size_types...>)
                array.resize(size_0,size_n...);
            else {
                array.resize(size_0);
                for (auto& a : array)
                    a = resize(a,size_n...);
            }
            return array;
        } // resize

        template <typename array_t, typename shape_t, size_t...Is>
        auto apply_resize(array_t& array, const shape_t& shape, std::index_sequence<Is...>) -> array_t&
        {
            return resize(array, std::get<Is>(shape)...);
        } // apply_resize

        template <typename array_t, typename shape_t>
        auto apply_resize(array_t& array, const shape_t& shape) -> array_t&
        {
            if constexpr (meta::has_tuple_size_v<shape_t>) {
                constexpr auto n = std::tuple_size_v<shape_t>;
                return apply_resize(array,shape,std::make_index_sequence<n>{});
            }
            else {
                array.resize(shape);
                return array;
            }
        } // apply_resize
    } // namespace detail
}

#endif // NMTOOLS_ARRAY_UTILITY_APPLY_RESIZE_HPP