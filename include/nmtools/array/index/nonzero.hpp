#ifndef NMTOOLS_ARRAY_INDEX_NONZERO_HPP
#define NMTOOLS_ARRAY_INDEX_NONZERO_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/ndarray/hybrid.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct nonzero_t {};

    /**
     * @brief return indices of array a which are nonzero
     * 
     * @tparam index_array_t 
     * @param a 
     * @return constexpr auto 
     */
    template <typename index_array_t>
    constexpr auto nonzero(const index_array_t& a)
    {
        using return_t = meta::resolve_optype_t<nonzero_t,index_array_t>;

        if constexpr (meta::is_maybe_v<return_t>) {
            if (static_cast<bool>(a)) {
                auto result = nonzero(*a);
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        } else {
            auto ret = return_t{};

            if constexpr (!meta::is_constant_index_array_v<return_t>) {
                ret.resize(len(a));
            
                auto n = nm_size_t{0}; // number of nonzero elements
                auto i = nm_size_t{0};

                auto nonzero_impl = [&](auto idx){
                    if (static_cast<bool>(at(a,idx))) {
                        at(ret,i) = idx;
                        n++; i++;
                    }
                }; // nonzero_impl
                
                if constexpr (meta::is_tuple_v<index_array_t>) {
                    constexpr auto N = meta::len_v<index_array_t>;
                    meta::template_for<N>(nonzero_impl);
                } else {
                    for (nm_size_t idx=0; idx<len(a); idx++)
                        nonzero_impl(idx);
                }
            
                ret.resize(n);
            }

            return ret;
        }
    } // nonzero
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_NONZERO_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief resolve return type for index::nonzero op
     * 
     * @tparam index_array_t 
     */
    template <typename index_array_t>
    struct resolve_optype<
        void, index::nonzero_t, index_array_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_maybe_v<index_array_t>) {
                using index_array_type = get_maybe_type_t<index_array_t>;
                using result_type = resolve_optype_t<index::nonzero_t,index_array_type>;
                using type = nmtools_maybe<result_type>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<index_array_t>) {
                constexpr auto index_array = to_value_v<index_array_t>;
                constexpr auto result = index::nonzero(index_array);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_index_array_v<index_array_t>) {
                constexpr auto element_vtype = [](){
                    using element_t = get_index_element_type_t<index_array_t>;
                    if constexpr (is_boolean_v<element_t>) {
                        return as_value_v<nm_size_t>;
                    } else {
                        return as_value_v<make_unsigned_t<element_t>>;
                    }
                }();
                using element_t = type_t<decltype(element_vtype)>;
                constexpr auto fixed_size   = fixed_size_v<index_array_t>;
                [[maybe_unused]]
                constexpr auto bounded_size = bounded_size_v<index_array_t>;
                if constexpr (!is_fail_v<decltype(fixed_size)>) {
                    using type = array::static_vector<element_t,fixed_size>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(bounded_size)>) {
                    using type = array::static_vector<element_t,bounded_size>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::INDEX_NONZERO_UNSUPPORTED<index_array_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_NONZERO_HPP