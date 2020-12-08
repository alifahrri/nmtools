#ifndef NMTOOLS_ARRAY_UTILITY_CAST_HPP
#define NMTOOLS_ARRAY_UTILITY_CAST_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/clone.hpp"
#include "nmtools/array/utility/zeros_like.hpp" // apply_resize
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/mutable_flatten.hpp"

#include "nmtools/utils/isequal.hpp"

namespace nmtools
{
    namespace detail
    {
        template <typename element_t, typename return_t, typename array_t, typename size_type>
        constexpr auto cast_impl(return_t &ret, const array_t& a, size_type n) {
            for (size_t i=0; i<n; i++)
                at(ret,i) = static_cast<element_t>(at(a,i));
        } // cast_impl
    } // namespace detail

    /**
     * @brief cast array of type srt_t to array of type dst_t
     * 
     * @tparam dst_t destination type
     * @tparam src_t source type
     * @param array array to be casted
     * @return constexpr auto 
     */
    template <typename dst_t, typename src_t>
    constexpr auto cast(const src_t& array)
    {
        static_assert (meta::is_ndarray_v<src_t>);
        static_assert (meta::is_ndarray_v<dst_t>);

        using detail::cast_impl;

        auto ret = dst_t{};
        if constexpr (meta::is_resizeable_v<dst_t>) {
            auto shape = ::nmtools::shape(array);
            ret = detail::apply_resize(ret, shape);
        }
        else if constexpr (meta::is_fixed_size_ndarray_v<dst_t> && meta::is_fixed_size_ndarray_v<src_t>) {
            constexpr auto src_shape = meta::fixed_ndarray_shape_v<src_t>;
            constexpr auto dst_shape = meta::fixed_ndarray_shape_v<dst_t>;
            static_assert (utils::isequal(src_shape,dst_shape)
                , "mismatched shape for cast"
            );
        }
        using element_t = meta::get_element_type_t<dst_t>;
        auto ret_view = view::mutable_flatten(ret);
        auto arr_view = view::flatten(array);
        auto n = vector_size(arr_view);
        cast_impl<element_t>(ret_view,arr_view,n);
        return ret;
    } // cast
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_CAST_HPP