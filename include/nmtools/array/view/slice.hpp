#ifndef NMTOOLS_ARRAY_VIEW_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_SLICE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/slice.hpp"

namespace nmtools::view
{
    template <typename array_t, typename slices_t>
    struct slice_t
    {
        using array_type  = resolve_array_type_t<array_t>;
        using slices_type = meta::remove_address_space_t<slices_t>;
        using src_shape_type = meta::remove_cvref_t<decltype(nmtools::shape(meta::declval<array_t>()))>;
        using dst_shape_type = meta::remove_cvref_t<decltype(index::apply_shape_slice(meta::declval<src_shape_type>(),meta::declval<slices_t>()))>;

        array_type array;
        slices_type slices;
        dst_shape_type shape_;

        constexpr slice_t(const array_t& array_, const slices_t& slices)
            : array(initialize<array_type>(array_))
            , slices(slices)
            , shape_(index::apply_shape_slice(nmtools::shape(array_),slices))
        {}

        constexpr auto shape() const
        {
            return shape_;
        } // shape

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            auto shape_ = detail::shape(array);
            auto tf_indices = index::apply_slice(indices_,shape_,slices);
            return tf_indices;
        } // index
    }; // slice_t

    template <typename array_t, typename...slices_t>
    constexpr auto slice(const array_t& array, slices_t...slices)
    {
        using slices_type = nmtools_tuple<slices_t...>;
        using view_t = decorator_t<slice_t,array_t,slices_type>;
        return view_t{{array, slices_type{slices...}}};
    } // slice

    template <typename array_t, typename slices_t>
    constexpr auto apply_slice(const array_t& array, const slices_t& slices)
    {
        using view_t = decorator_t<slice_t,array_t,slices_t>;
        return view_t{{array, slices}};
    } // apply_slice
} // namespace nmtools::view

namespace nmtools::meta
{
    // TODO: remove, use newer deduction pattern
    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename array_t, typename...slices_t>
    struct fixed_ndarray_shape< view::slice_t<array_t,slices_t...> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    // TODO: remove, do not provide as metafunction, use newer deduction pattern
    template <typename array_t, typename...slices_t>
    struct fixed_size< view::decorator_t< view::slice_t, array_t,slices_t...> >
    {
        using view_type = view::decorator_t< view::slice_t, array_t,slices_t... >;
        static inline constexpr auto value = error::FIXED_SIZE_UNSUPPORTED<view_type>{};
    }; // fixed_ndarray_shape

    // TODO: remove, do not provide as metafunction, use newer deduction pattern
    template <typename array_t, typename...slices_t>
    struct bounded_size< view::decorator_t< view::slice_t, array_t,slices_t...> >
    {
        using view_type = view::decorator_t< view::slice_t, array_t,slices_t...>;

        static inline constexpr auto value = [](){
            using array_type = typename view_type::array_type;
            // bounded size of slice view can't exceed the array size
            constexpr auto bounded_size = bounded_size_v<array_type>;
            if constexpr (!is_fail_v<decltype(bounded_size)>) {
                return bounded_size;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED{};
            }
        }();
    }; // fixed_ndarray_shape

    template <typename array_t, typename...slices_t>
    struct is_ndarray< view::decorator_t< view::slice_t, array_t, slices_t... >>
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_SLICE_HPP