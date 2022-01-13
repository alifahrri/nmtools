#ifndef NMTOOLS_ARRAY_UTILITY_APPLY_RESIZE_HPP
#define NMTOOLS_ARRAY_UTILITY_APPLY_RESIZE_HPP

#include "nmtools/meta.hpp"

namespace nmtools
{
    namespace detail 
    {
        template <typename array_t, typename size_type, typename...size_types>
        constexpr auto resize(array_t& array, size_type size_0, size_types...size_n) -> array_t&
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

        template <template <auto...> typename index_sequence, typename array_t, typename shape_t, size_t...Is>
        constexpr auto apply_resize(array_t& array, const shape_t& shape, index_sequence<Is...>) -> array_t&
        {
            return resize(array, nmtools::get<Is>(shape)...);
        } // apply_resize

        template <typename array_t, typename shape_t>
        constexpr auto apply_resize(array_t& array, const shape_t& shape) -> array_t&
        {
            constexpr auto n = meta::len_v<shape_t>;
            if constexpr (n > 0) {
                return apply_resize(array,shape,meta::make_index_sequence<n>{});
            }
            else {
                array.resize(shape);
                return array;
            }
        } // apply_resize
    } // namespace detail
}

#endif // NMTOOLS_ARRAY_UTILITY_APPLY_RESIZE_HPP