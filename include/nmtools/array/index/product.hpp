#ifndef NMTOOLS_ARRAY_INDEX_PRODUCT_HPP
#define NMTOOLS_ARRAY_INDEX_PRODUCT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

namespace nmtools::index
{
    /**
     * @brief compute product of 1D array
     *
     * Useful to compute number of elements.
     * 
     * @tparam array_t 
     * @param vec 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto product(const array_t& vec)
    {
        // handle constant index array,
        // for now, simply convert to value and recurse
        if constexpr (meta::is_constant_index_array_v<array_t>) {
            constexpr auto vec_ = meta::constant_to_value<array_t>::value;
            constexpr auto ret  = product(vec_);
            // @todo convert back to type
            return ret;
        }
        else {
            using element_t = meta::get_element_or_common_type_t<array_t>;
            auto ret = element_t{1};
            if constexpr (meta::has_tuple_size_v<array_t>) {
                constexpr auto n = std::tuple_size_v<array_t>;
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    ret *= std::get<i>(vec);
                });
            }
            else
                for (size_t i=0; i<len(vec); i++)
                    ret *= at(vec,i);
            return ret;
        }
    } // product
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_PRODUCT_HPP