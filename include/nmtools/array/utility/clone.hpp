#ifndef NMTOOLS_ARRAY_UTILITY_CLONE_HPP
#define NMTOOLS_ARRAY_UTILITY_CLONE_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"

#include "nmtools/array/utility/at.hpp"         // at
#include "nmtools/array/shape.hpp"      // vector_size, matrix_size
#include "nmtools/array/utility/zeros_like.hpp" // zeros_like
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/mutable_flatten.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    namespace detail
    {
        template <typename return_t, typename array_t, typename size_type>
        constexpr auto clone_impl(return_t &ret, const array_t& a, size_type rows, size_type cols){
            for (size_t i=0; i<rows; i++)
                for (size_t j=0; j<cols; j++)
                    at(ret,i,j) = at(a,i,j);
        } // clone_impl

        template <typename return_t, typename array_t, typename size_type>
        constexpr auto clone_impl(return_t &ret, const array_t& a, size_type n) {
            for (size_t i=0; i<n; i++)
                at(ret,i) = at(a,i);
        } // clone_impl
    } // namespace detail

    struct clone_t {};

    template <typename array_t>
    struct meta::resolve_optype<void,clone_t,array_t>
    {
        using type = meta::transform_bounded_array_t<array_t>;
    }; // resolve_optype

    /**
     * @brief clone matrix/vector 
     * 
     * @tparam Array 
     * @param a matrix/vector/arithmetic
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto clone(const Array& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            meta::is_array1d_v<Array>
            || meta::is_array2d_v<Array>
            || std::is_arithmetic_v<Array>,
            "unsupported type for clone"
        );
        using detail::clone_impl;
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<Array>)
            return a;
        /* ret is conteiner, for each elements call zeros_like */
        else {
            using return_t = meta::resolve_optype_t<clone_t,Array>;
            auto ret = return_t{};
            if constexpr (meta::is_resizeable_v<return_t>) {
                auto shape = ::nmtools::shape(a);
                ret = detail::apply_resize(ret, shape);
            }
            auto ret_view = view::mutable_flatten(ret);
            auto arr_view = view::flatten(a);
            auto n = vector_size(arr_view);
            clone_impl(ret_view,arr_view,n);
            return ret;
        }
    } // constexpr auto clone(const Array& a)
} // namespace clone

#endif // NMTOOLS_ARRAY_UTILITY_CLONE_HPP