#ifndef NMTOOLS_INDEX_INDEX_OF_HPP
#define NMTOOLS_INDEX_INDEX_OF_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::index
{
    template <typename list_t, typename value_t>
    constexpr auto index_of(const list_t& list, value_t value)
    {
        if constexpr (meta::is_maybe_v<list_t>
            || meta::is_maybe_v<value_t>
        ) {
            using result_t = decltype(index_of(unwrap(list),unwrap(value)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(list) && has_value(value)
                ? return_t{index_of(unwrap(list),unwrap(value))}
                : return_t{meta::Nothing}
            );
        } else {
            // TODO: handle constant index array list with constant index value
            using result_t = nm_size_t;
            using return_t = nmtools_maybe<result_t>;

            auto size   = len(list);
            auto found  = false;
            auto result = result_t{};
            for (nm_size_t i=0; i<(nm_size_t)size; i++) {
                if ((value_t)at(list,i) == value) {
                    found = true;
                    result = i;
                    break;
                }
            }

            if (found) {
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        }
    }
}

#endif // NMTOOLS_INDEX_INDEX_OF_HPP