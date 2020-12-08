#ifndef NMTOOLS_ARRAY_UTILITY_ZEROS_LIKE_HPP
#define NMTOOLS_ARRAY_UTILITY_ZEROS_LIKE_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"

#include "nmtools/array/utility/at.hpp"     // at
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/shape.hpp"  // matrix_size, vector_size

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

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
        auto apply_resize(array_t& array, shape_t& shape, std::index_sequence<Is...>) -> array_t&
        {
            return resize(array, std::get<Is>(shape)...);
        } // apply_resize

        template <typename array_t, typename shape_t>
        auto apply_resize(array_t& array, shape_t& shape) -> array_t&
        {
            if constexpr (meta::has_tuple_size_v<shape_t>) {
                constexpr auto n = std::tuple_size_v<shape_t>;
                return apply_resize(array,shape,std::make_index_sequence<n>{});
            }
            else return array.resize(shape);
        } // apply_resize
    } // namespace detail

    struct zeros_like_t {};

    template <typename array_t>
    struct meta::resolve_optype<void,zeros_like_t,array_t>
    {
        using type = meta::transform_bounded_array_t<array_t>;
    }; // resolve_optype

    /**
     * @brief create zero matrix/vector 
     * 
     * @tparam T matrix/vector/arithmetic
     * @param a example of existing matrix/vector
     * @return constexpr auto 
     */
    template <typename T>
    constexpr auto zeros_like(const T& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            meta::is_ndarray_v<T>
            || std::is_arithmetic_v<T>,
            "unsupported type for zeros_like"
        );
        using return_t = meta::resolve_optype_t<zeros_like_t,T>;
        /* TODO: check if return_t can be instantiated this way */
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return casted zero */
        if constexpr (std::is_arithmetic_v<T>)
            ret = static_cast<T>(0);
        /* ret is conteiner, for each elements call zeros_like */
        else if constexpr (meta::is_resizeable_v<T>) {
            auto shape = ::nmtools::shape(a);
            ret = detail::apply_resize(ret, shape);
        }
        return ret;
    } // constexpr auto zeros_like(const T& a)
} // namespace nmtools
#endif // NMTOOLS_ARRAY_UTILITY_ZEROS_LIKE_HPP