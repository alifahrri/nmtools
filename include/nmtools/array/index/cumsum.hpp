#ifndef NMTOOLS_ARRAY_INDEX_CUMSUM_HPP
#define NMTOOLS_ARRAY_INDEX_CUMSUM_HPP

#include "nmtools/meta.hpp"

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of cumsum
     * 
     */
    struct cumsum_t {};

    // TODO: cleanup index functions, handling constant index array
    /**
     * @brief compute cumulative sum or 1D array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto cumsum(const array_t& array)
    {
        using return_t = meta::resolve_optype_t<cumsum_t,array_t>;
        auto ret = return_t {};
        if constexpr (meta::is_resizable_v<return_t>)
            ret.resize(len(array));
        
        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            using namespace literals;
            at(ret,0_ct) = at(array,0_ct);
            if constexpr (meta::is_tuple_v<return_t>) {
                constexpr auto N = meta::len_v<return_t>;
                meta::template_for<N-1>([&](auto I){
                    constexpr auto I_plus_1 = meta::ct_v<(size_t)I+1>;
                    at(ret,I_plus_1) = at(ret,I) + at(array,I_plus_1);
                });
            } else {
                for (size_t i=1; i<(size_t)len(ret); i++)
                    at(ret,i) = at(ret,i-1) + at(array,i);
            }
        }
        
        return ret;
    } // cumsum
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct INDEX_CUMSUM_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief resolve return type of index::cumsum
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct resolve_optype< void, index::cumsum_t, array_t >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_constant_index_array_v<array_t>
                || is_clipped_index_array_v<array_t>
            ) {
                constexpr auto array = to_value_v<array_t>;
                constexpr auto result = index::cumsum(array);
                return template_reduce<nmtools::len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    constexpr auto I = nmtools::at(result,index);
                    if constexpr (is_constant_index_array_v<array_t>) {
                        using type = append_type_t<init_type,ct<I>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_type,clipped_size_t<I>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_index_array_v<array_t>) {
                constexpr auto N = len_v<array_t>;
                [[maybe_unused]]
                constexpr auto b_dim = bounded_size_v<array_t>;
                using index_t = get_index_element_type_t<array_t>;
                if constexpr (N > 0) {
                    using type = nmtools_array<index_t,N>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_dim)>) {
                    using type = array::static_vector<index_t,b_dim>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::INDEX_CUMSUM_UNSUPPORTED<array_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_CUMSUM_HPP