#ifndef NMTOOLS_ARRAY_INDEX_REVERSE_HPP
#define NMTOOLS_ARRAY_INDEX_REVERSE_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    namespace index
    {
        /**
         * @brief reverse array (of indices)
         * 
         * @tparam indices_t array of same type
         * @tparam Is index sequence
         * @param indices 
         * @return constexpr auto 
         */
        template <typename indices_t, size_t...Is>
        constexpr auto reverse(const indices_t& indices, std::index_sequence<Is...>)
        {
            // assuming same shape
            return indices_t{std::get<Is>(indices)...};
        } // reverse

        /**
         * @brief entrypoint for reversing array (of indices)
         * 
         * @tparam indices_t array of same type
         * @param indices 
         * @return constexpr auto 
         */
        template <typename indices_t>
        constexpr auto reverse(const indices_t& indices)
        {
            if constexpr (meta::has_tuple_size_v<indices_t>) {
                constexpr auto N = std::tuple_size_v<indices_t>;
                using reverse_t = meta::make_reversed_index_sequence<N>;
                return reverse(indices, reverse_t{});
            }
            else {
                auto ret = indices_t{};
                if constexpr (meta::is_resizeable_v<indices_t>)
                    ret.resize(indices.size());
                auto n = indices.size();
                for (size_t i=0; i<n; i++)
                    ret.at(i) = indices.at(n-1-i);
                return ret;
            }
        } // reverse
    } // namespace index
} // namespace nmtools

#endif // NMTOOLS_ARRAY_INDEX_REVERSE_HPP