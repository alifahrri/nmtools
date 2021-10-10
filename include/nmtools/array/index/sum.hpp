#ifndef NMTOOLS_ARRAY_INDEX_SUM_HPP
#define NMTOOLS_ARRAY_INDEX_SUM_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

namespace nmtools::index
{
    // TODO: cleanup index functions
    /**
     * @brief compute sum of 1D array
     *
     * Useful to compute number of elements.
     * 
     * @tparam array_t 
     * @param vec 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto sum(const array_t& vec)
    {
        using element_t = meta::get_element_type_t<array_t>;
        using common_t  = std::conditional_t<
            std::is_void_v<element_t>,
            meta::apply_t<std::common_type,array_t>,
            element_t
        >;
        // handle type vector
        if constexpr (meta::is_constant_index_array_v<array_t>) {
            // TODO: move constant index handling at higher level, see remove_dims for example
            constexpr auto vec_ = meta::to_value_v<array_t>;
            constexpr auto ret  = sum(vec_);
            // TODO: convert back to type
            return ret;
        }
        else {
            auto ret = common_t{0};
            if constexpr (meta::has_tuple_size_v<array_t>) {
                constexpr auto n = std::tuple_size_v<array_t>;
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    ret += std::get<i>(vec);
                });
                return ret;
            }
            else
                for (size_t i=0; i<len(vec); i++)
                    ret += at(vec,i);
            return ret;
        }
    } // sum
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_SUM_HPP