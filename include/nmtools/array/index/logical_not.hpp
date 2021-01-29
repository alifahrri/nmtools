#ifndef NMTOOLS_ARRAY_INDEX_LOGICAL_NOT_HPP
#define NMTOOLS_ARRAY_INDEX_LOGICAL_NOT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"

namespace nmtools::index
{
    /**
     * @brief perform logical not on 1d array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto logical_not(const array_t& array)
    {
        using element_t = meta::get_element_type_t<array_t>;
        using return_t  = meta::tuple_to_array_t<array_t>;
        using result_t  = meta::get_element_type_t<return_t>;
        static_assert (
            meta::compose_logical_or_v<element_t,meta::is_boolean>
            && meta::compose_logical_or_v<result_t,meta::is_boolean>
            , "unsupported index::logical_not"
        );
        auto res = return_t{};

        auto s = tuple_size(array);

        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(s);

        for (size_t i=0; i<s; i++)
            at(res,i) = !at(array,i);

        return res;
    } // logical_not
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_LOGICAL_NOT_HPP