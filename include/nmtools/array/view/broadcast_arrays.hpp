#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP

#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::view::detail::fn
{
    /**
     * @brief Compile time version of index::broadcast_shape.
     * 
     * @tparam arrays_t 
     * @return constexpr auto 
     */
    template <typename...arrays_t>
    constexpr auto broadcast_shape(meta::as_value<arrays_t>...)
    {
        // map type to value, and actually call broadcast_shape implementation
        constexpr auto result  = index::broadcast_shape(meta::fixed_ndarray_shape_v<arrays_t>...);
        constexpr auto success = std::get<0>(result);
        if constexpr (success) {
            // then map back to type
            constexpr auto bshape = std::get<1>(result);
            constexpr auto shape  = meta::template_map<len(bshape)>([&](auto i){
                constexpr auto ts = at(bshape,i);
                return std::integral_constant<size_t,ts>{};
            });
            return shape;
        }
        // since this value is expected to be called at compile time,
        // return fail type when fail
        else return meta::detail::Fail;
    } // broadcast_shape
} // namespace nmtools::view::detail::fn

namespace nmtools::view
{
    /**
     * @brief broadcast arrays against each other.
     * 
     * @tparam arrays_t 
     * @param arrays 
     * @return constexpr auto 
     */
    template <typename...arrays_t>
    constexpr auto broadcast_arrays(const arrays_t&...arrays)
    {
        static_assert( sizeof...(arrays_t) >= 2
            , "please provide at least two arrays for broadcast_arrays");

        // when all arrays' shapes are known at compile time, perform checks at compile time
        // the return type is not wrapped, and should be noexcept ready
        if constexpr ((meta::is_fixed_size_ndarray_v<arrays_t> && ...)) {
            constexpr auto bshape = detail::fn::broadcast_shape(meta::as_value_v<arrays_t>...);
            static_assert( !meta::is_fail_v<decltype(bshape)>
                , "cannot broadcast arrays together" );
            return std::tuple{broadcast_to(arrays,bshape)...};
        }
        // otherwise call runtime version,
        // the return type can be maybe type, and may throw if not maybe type
        else {
            auto [success, broadcasted_shape] = index::broadcast_shape(::nmtools::shape(arrays)...);

            // easiest way to get result type
            using result_t = decltype(std::tuple{broadcast_to(arrays,broadcasted_shape)...});
            nmtools_assert_prepare_type (return_t, result_t);
            nmtools_assert (success, "cannot broadcast arrays together", return_t);

            return return_t{std::tuple{broadcast_to(arrays,broadcasted_shape)...}};
        }
    } // broadcast_arrays
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_ARRAYS_HPP