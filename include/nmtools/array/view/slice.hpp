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
        using slices_type = slices_t;

        array_type array;
        slices_type slices;

        constexpr slice_t(const array_t& array, const slices_t& slices)
            : array(initialize<array_type>(array))
            , slices(slices) {}

        constexpr auto shape() const
        {
            auto shape_ = detail::shape(array);
            return index::apply_shape_slice(shape_,slices);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            auto shape_ = detail::shape(array);
            return index::apply_slice(indices_,shape_,slices);
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
    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename array_t, typename...slices_t>
    struct fixed_ndarray_shape< view::slice_t<array_t,slices_t...> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename array_t, typename...slices_t>
    struct is_ndarray< view::decorator_t< view::slice_t, array_t, slices_t... >>
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_SLICE_HPP