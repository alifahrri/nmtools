#ifndef NMTOOLS_ARRAY_ARRAY_BROADCAST_ARRAYS_HPP
#define NMTOOLS_ARRAY_ARRAY_BROADCAST_ARRAYS_HPP

#include "nmtools/core/broadcast_arrays.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly broadcast arrays
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam resolver_t=eval_result_t 
     * @tparam arrays_t 
     * @param arrays arrays to be broadcasted together
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename...arrays_t>
    constexpr auto broadcast_arrays(const arrays_t&...arrays)
    {
        auto broadcasted_pack = view::broadcast_arrays(arrays...);
        return apply_eval(broadcasted_pack
            , context_t{}
            , output_t{}
            , meta::as_value_v<resolver_t>
        );
    } // broadcast_arrays
}

#endif // NMTOOLS_ARRAY_ARRAY_BROADCAST_ARRAYS_HPP