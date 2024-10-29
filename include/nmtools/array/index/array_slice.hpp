#ifndef NMTOOLS_ARRAY_INDEX_ARRAY_SLICE_HPP
#define NMTOOLS_ARRAY_INDEX_ARRAY_SLICE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/index/ref.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"

namespace nmtools::index
{
    struct shape_array_slice_t {};

    /**
     * @brief Compute the shape of array_slice view.
     * 
     * @tparam shape_t 
     * @tparam slice0_t 
     * @tparam slices_t 
     * @param shape     original array shape
     * @param slice     first slice array
     * @param slices    the rest of slice arrays
     * @return constexpr auto 
     */
    template <typename shape_t, typename slice0_t, typename...slices_t>
    constexpr auto shape_array_slice(const shape_t& shape, const slice0_t& slice, const slices_t&...slices)
    {
        using result_t = meta::resolve_optype_t<shape_array_slice_t,shape_t,slice0_t,slices_t...>;
        if constexpr (!meta::is_fail_v<result_t>) {
            using return_t = nmtools_maybe<result_t>;

            auto result = result_t {};

            auto src_dim  = len(shape);
            constexpr auto n_slices = sizeof...(slices_t) + 1;

            auto dim = [&]()->size_t{ // quick workaround for error: inconsistent types
                if (src_dim == n_slices) {
                    auto dims = nmtools_array{(size_t)len(slice),(size_t)len(slices)...};
                    auto max  = at(dims,0);
                    for (size_t i=1; i<(size_t)dims.size(); i++) {
                        auto dim = at(dims,i);
                        max = (dim > max ? dim : max);
                    }
                    return max;
                } else {
                    // NOTE: assume single slicing
                    // 2 + 3 - 2
                    // 1 + 2 - 1
                    return len(slice) + len(shape) - (n_slices);
                }
            }();

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dim);
            }

            const auto bcast_result = [&](){
                if constexpr (n_slices > 1) {
                    return broadcast_shape(slice,slices...);
                } else {
                    return nmtools_maybe{ref(slice)};
                }
            }();

            const auto success = static_cast<bool>(bcast_result);

            if (success) {
                const auto& broadcasted = *bcast_result;
                // simply return broadcasted
                auto bdim = len(broadcasted);
                for (size_t i=0; i<bdim; i++) {
                    at(result,i) = at(broadcasted,i);
                }
                // fill the rest with src shape
                auto diff = dim - bdim;
                for (size_t i=0; i<(size_t)diff; i++) {
                    at(result,bdim+i) = at(shape,i+n_slices);
                }
                return return_t{result};
            } else {
                return return_t{}; // Nothing
            }
        } else {
            // let the caller what to do with the error type
            return result_t {};
        }
    } // shape_array_slice

    template <typename indices_t, typename slices_t, template<auto...>typename sequence, auto...Is>
    constexpr auto array_slice(const indices_t& indices, const slices_t& slices, sequence<Is...>)
    {
        return nmtools_array{apply_at(at(slices,meta::ct_v<Is>),indices)...};
    }

    /**
     * @brief Construct the indices for array_slice.
     * 
     * @tparam indices_t 
     * @tparam tuple_t 
     * @tparam slices_t 
     * @param indices   indices in dst_shape
     * @param slices    tuple of slicing arrays
     * @return constexpr auto 
     */
    template <typename indices_t, template<typename...>typename tuple_t, typename...slices_t>
    constexpr auto array_slice(const indices_t& indices, const tuple_t<slices_t...>& slices)
    {
        return array_slice(indices, slices, meta::make_index_sequence_v<sizeof...(slices_t)>);
    } // array_slice
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        // we can't understand the type
        template <typename...>
        struct SHAPE_ARRAY_SLICE_UNSUPPORTED : detail::fail_t {};

        // index error, n slices > src dim
        template <typename...>
        struct SHAPE_ARRAY_SLICE_INDEX_ERROR : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename slice0_t, typename...slices_t>
    struct resolve_optype<void, index::shape_array_slice_t
        , shape_t, slice0_t, slices_t...>
    {
        static constexpr auto vtype = [](){
            auto index_vtype = [](){
                using index_t = get_element_or_common_type_t<shape_t>;
                if constexpr (is_constant_index_v<index_t>) {
                    // force to runtime type
                    return as_value_v<typename index_t::value_type>;
                } else {
                    return as_value_v<index_t>;
                }
            }();
            using index_t [[maybe_unused]] = type_t<decltype(index_vtype)>;
            if constexpr (is_fixed_index_array_v<shape_t>
                && is_fixed_index_array_v<slice0_t>
                && (is_fixed_index_array_v<slices_t> && ...)
            ) {
                constexpr auto DIM = len_v<shape_t>;
                constexpr auto n_slices = sizeof...(slices_t) + 1;
                using types_t = type_list<slice0_t,slices_t...>;
                if constexpr (DIM == n_slices) {
                    // NOTE: for array_slice, full indexing
                    // will results on array where the resuling dim are the higest,
                    // since the slices will be broadcasted together
                    constexpr auto max_dim = template_reduce<n_slices>([](auto max, auto index){
                        constexpr auto i = decltype(index)::value;
                        using type_i = type_list_at_t<i,types_t>;
                        constexpr auto n = len_v<type_i>;
                        return (max > n ? max : n);
                    }, len_v<slice0_t>);
                    // TODO: try to deduce from shape_t
                    using type = nmtools_array<index_t,max_dim>;
                    return as_value_v<type>;
                } else if constexpr (n_slices < DIM) {
                    // on the other hand, with partial indexing,
                    // the resulting dim will depends on the shape of src array.
                    // here we can oly defer to runtime
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                } else {
                    // too many indices
                    using type = error::SHAPE_ARRAY_SLICE_INDEX_ERROR<shape_t,slice0_t,slices_t...>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                    is_index_array_v<shape_t>
                &&  is_index_array_v<slice0_t>
                && (is_index_array_v<slices_t> && ...)
            ) {
                using type = nmtools_list<index_t>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_ARRAY_SLICE_UNSUPPORTED<shape_t,slice0_t,slices_t...>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_ARRAY_SLICE_HPP