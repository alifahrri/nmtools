#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/slice.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/array/index/ndenumerate.hpp"

namespace nmtools::view
{
    /**
     * @brief View type for mutable_slice.
     * 
     * Like slice but allow assignment.
     * 
     * @tparam array_t 
     * @tparam slices_t 
     */
    template <typename array_t, typename slices_t>
    struct mutable_slice_t
    {
        using array_type  = resolve_mutable_array_type_t<array_t>;
        // NOTE: assume tuple type / list
        using slices_type = slices_t;
        using src_shape_type = decltype(detail::shape(meta::declval<array_type>()));
        using dst_shape_type = decltype(index::apply_shape_slice(meta::declval<src_shape_type>(),meta::declval<slices_type>()));

        array_type  array;
        slices_type slices;
        src_shape_type src_shape;
        dst_shape_type dst_shape;

        constexpr mutable_slice_t(array_t& array, const slices_t& slices)
            : array(initialize<array_type>(array))
            , slices(slices)
            , src_shape(detail::shape(this->array))
            , dst_shape(index::apply_shape_slice(this->src_shape,this->slices))
        {}

        constexpr auto shape() const noexcept
        {
            return dst_shape;
        }

        constexpr auto dim() const noexcept
        {
            return len(dst_shape);
        }

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            return index::apply_slice(indices_,src_shape,slices);
        } // index

        template <typename other_t, meta::enable_if_t< meta::is_ndarray_v<other_t>, int> =0>
        constexpr auto operator=(const other_t& other)
        {
            // TODO: support broadcasting with broadcast_to (unidirectional broadcasting)
            // TODO: consider to differentiate error handling for mutable op, i.e. nmtools_mutable_cassert macro
            // TODO: perform shape check at compile time when possible
            nmtools_cassert(( utils::isequal(dst_shape, ::nmtools::shape(other)) ));
            for (const auto& [indices, value] : index::ndenumerate(other)) {
                auto src_indices = index::apply_slice(indices,src_shape,slices);
                detail::apply_at(array,src_indices) = value;
            }
            return *this;
        } // operator=
    }; // mutable_slice_t

    /**
     * @brief Like slice but allow operator=.
     * 
     * @tparam array_t 
     * @tparam slices_t 
     * @param array     input array
     * @param slices    desired slices
     * @return constexpr auto 
     */
    template <typename array_t, typename...slices_t>
    constexpr auto mutable_slice(array_t& array, slices_t...slices)
    {
        // TODO: better error handling, by checking if resulting shape is valid
        using slices_type = nmtools_tuple<slices_t...>;
        using view_t = decorator_t<mutable_slice_t,array_t,slices_type>;
        return view_t{{array, slices_type{slices...}}};
    } // slice

    template <typename array_t, typename slices_t>
    constexpr auto apply_mutable_slice(array_t& array, const slices_t& slices)
    {
        // TODO: better error handling, by checking if resulting shape is valid
        using view_t = decorator_t<mutable_slice_t,array_t,slices_t>;
        return view_t{{array, slices}};
    } // apply_slice
} // namespace nmtools::view

namespace nmtools::meta
{
    // NOTE: doesn't support fixed size for now
    // TODO: fix for fixed size
    template <typename array_t, typename slices_t>
    struct fixed_ndarray_shape< view::mutable_slice_t<array_t,slices_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename array_t, typename slices_t>
    struct is_ndarray< view::decorator_t< view::mutable_slice_t, array_t, slices_t>>
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_SLICE_HPP