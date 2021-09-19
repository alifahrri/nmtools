#ifndef NMTOOLS_ARRAY_VIEW_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_SLICE_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/index/slice.hpp"

#include <cassert>

namespace nmtools::view
{
    template <typename array_t, typename...slices_t>
    struct slice_t
    {
        using array_type  = resolve_array_type_t<array_t>;
        using slices_type = std::tuple<meta::remove_cvref_t<slices_t>...>;

        array_type array;
        slices_type slices;

        constexpr slice_t(const array_t& array, slices_t...slices)
            : array(initialize<array_type>(array)), slices({slices...}) {}

        template <typename shape_t, size_t...Is>
        constexpr auto shape(const shape_t& ashape, std::index_sequence<Is...>) const
        {
            return ::nmtools::index::shape_slice(ashape, std::get<Is>(slices)...);
        } // shape_impl

        constexpr auto shape() const
        {
            using ::nmtools::index::make_array;
            auto shape_ = detail::shape(array);
            // TODO: no need to transform to array
            auto ashape = [&](){
                using index::make_array;
                using shape_t = meta::remove_cvref_t<decltype(shape_)>;
                // TODO: make proper generalization of `index_array`
                if constexpr (meta::is_specialization_v<shape_t, std::tuple> || meta::is_specialization_v<shape_t, std::pair>)
                    return make_array<std::array>(shape_);
                else return shape_;
            }();
            return shape(ashape, std::make_index_sequence<sizeof...(slices_t)>{});
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename indices_t, typename shape_t, size_t...Is>
        constexpr auto index_impl(const indices_t& indices_, const shape_t& ashape,std::index_sequence<Is...>) const
        {
            return ::nmtools::index::slice(indices_,ashape,std::get<Is>(slices)...);
        } // index_impl

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            auto shape_ = detail::shape(array);
            // TODO: no need to transform to array
            auto ashape = [&](){
                using index::make_array;
                using shape_t = meta::remove_cvref_t<decltype(shape_)>;
                // TODO: make proper generalization of `index_array`
                if constexpr (meta::is_specialization_v<shape_t, std::tuple> || meta::is_specialization_v<shape_t, std::pair>)
                    return make_array<std::array>(shape_);
                else return shape_;
            }();
            return index_impl(indices_,ashape,std::make_index_sequence<sizeof...(slices_t)>{});
        } // index
    }; // slice_t

    template <typename array_t, typename...slices_t>
    constexpr auto slice(const array_t& array, slices_t...slices)
    {
        using view_t = decorator_t<slice_t,array_t,slices_t...>;
        return view_t{{array, slices...}};
    } // slice

    template <typename array_t, typename slices_t, size_t...Is>
    constexpr auto apply_slice(const array_t& array, const slices_t& slices, std::index_sequence<Is...>)
    {
        return slice(array,at(slices,meta::ct_v<Is>)...);
    } // apply_slice

    template <typename array_t, typename slices_t>
    constexpr auto apply_slice(const array_t& array, const slices_t& slices)
    {
        constexpr auto N = std::tuple_size_v<slices_t>;
        return apply_slice(array, slices, std::make_index_sequence<N>{});
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