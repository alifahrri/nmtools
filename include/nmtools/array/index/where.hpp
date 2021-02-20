#ifndef NMTOOLS_ARRAY_INDEX_WHERE_HPP
#define NMTOOLS_ARRAY_INDEX_WHERE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/index/tuple_at.hpp"

#include <type_traits>
#include <cstddef>
#include <utility>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve where op return type
     * 
     */
    struct where_t {};

    /**
     * @brief return indices of array that satisfy predicate f
     * 
     * @tparam F unary predicate
     * @tparam array_t 
     * @param f 
     * @param array 
     * @return constexpr auto 
     */
    template <typename index_t=size_t, typename F, typename array_t>
    constexpr auto where(const F& f, const array_t& array)
    {
        using return_t = meta::resolve_optype_t<where_t,array_t,index_t>;
        auto res = return_t{};
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(tuple_size(array));
        auto n = size_t{0};
        auto where_impl = [&](auto i){
            if (f(tuple_at(array,i)))
                at(res,n++) = static_cast<size_t>(i);
        };
        if constexpr (meta::has_tuple_size_v<array_t>)
            meta::template_for<std::tuple_size_v<array_t>>([&](auto i){
                where_impl(i);
            });
        else
            for (size_t i=0; i<size(array); i++)
                where_impl(i);
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(n);
        return res;
    } // where
} // namespace nmtools

namespace nmtools::meta
{
    /**
     * @brief resolve where return type for resizeable array type
     * 
     * @tparam array_t 
     * @tparam index_t 
     */
    template <typename array_t, typename index_t>
    struct resolve_optype<
        std::enable_if_t<
            meta::is_resizeable_v<array_t>
        >,
        index::where_t, array_t, index_t
    >
    {
        using type = meta::replace_element_type_t<array_t,index_t>;
    }; // resolve_optype where_t

    /**
     * @brief resolve where return type for fixed array type
     * 
     * @tparam array_t 
     * @tparam index_t 
     */
    template <typename array_t, typename index_t>
    struct resolve_optype<
        std::enable_if_t<
            !meta::is_resizeable_v<array_t>
            && has_tuple_size_v<array_t>
            && std::is_arithmetic_v<get_element_or_common_type_t<array_t>>
        >,
        index::where_t, array_t, index_t
    >
    {
        static constexpr auto N = std::tuple_size_v<array_t>;
        // need to use hybrid array1d since the size will depends on runtime value
        using type = array::hybrid_ndarray<index_t,N,1>;
    }; // resolve_optype where_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_WHERE_HPP