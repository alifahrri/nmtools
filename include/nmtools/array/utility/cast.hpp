#ifndef NMTOOLS_ARRAY_UTILITY_CAST_HPP
#define NMTOOLS_ARRAY_UTILITY_CAST_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/apply_resize.hpp"
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
     * @brief tag to resolve return type of cast op
     * 
     */
    struct cast_t {};
    
    /**
     * @brief specialization for cast_t tag
     * 
     * @tparam dst_t destination type
     * @tparam src_t source type
     */
    template <typename dst_t, typename src_t>
    struct meta::resolve_optype<void,cast_t,dst_t,src_t>
    {
        using source_t = meta::transform_bounded_array_t<src_t>;
        using array_type = std::conditional_t<
            std::is_arithmetic_v<dst_t>,
            meta::replace_element_type_t<source_t,dst_t>,
            dst_t
        >;
        using type = meta::transform_bounded_array_t<array_type>;
    }; // resolve_optype

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
        static_assert (meta::is_ndarray_v<src_t> || std::is_arithmetic_v<src_t>
            , "unsupported cast, expects source type to be ndarray or arithmetic"
        );
        static_assert (meta::is_ndarray_v<dst_t> || std::is_arithmetic_v<dst_t>
            , "unsupported cast, expects destination type to be ndarray or arithmetic"
        );
        static_assert ((std::is_arithmetic_v<src_t> == std::is_arithmetic_v<dst_t>) || (meta::is_ndarray_v<src_t>)
            , "unsupported cast, expects destination type to be arithmetic when source type is arithmetic"
        );

        if constexpr (std::is_arithmetic_v<src_t> && std::is_arithmetic_v<dst_t>)
            return static_cast<dst_t>(array);
        else {
            using detail::cast_impl;
            using return_t = meta::resolve_optype_t<cast_t,dst_t,src_t>;

            auto ret = return_t{};
            if constexpr (meta::is_resizeable_v<return_t>) {
                auto shape = ::nmtools::shape(array);
                ret = detail::apply_resize(ret, shape);
            }
            else if constexpr (meta::is_fixed_size_ndarray_v<return_t> && meta::is_fixed_size_ndarray_v<src_t>) {
                constexpr auto src_shape = meta::fixed_ndarray_shape_v<src_t>;
                constexpr auto dst_shape = meta::fixed_ndarray_shape_v<return_t>;
                static_assert (utils::isequal(src_shape,dst_shape)
                    , "unsupported cast, mismatched shape for cast"
                );
            }
            using element_t = meta::get_element_type_t<return_t>;
            auto ret_view = view::mutable_flatten(ret);
            auto arr_view = view::flatten(array);
            auto n = vector_size(arr_view);
            cast_impl<element_t>(ret_view,arr_view,n);
            return ret;
        }
    } // cast
} // namespace nmtools

#endif // NMTOOLS_ARRAY_UTILITY_CAST_HPP