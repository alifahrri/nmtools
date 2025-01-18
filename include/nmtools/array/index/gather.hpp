#ifndef NMTOOLS_ARRAY_INDEX_GATHER_HPP
#define NMTOOLS_ARRAY_INDEX_GATHER_HPP

#include "nmtools/meta.hpp"

#include "nmtools/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/stl.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct gather_t {};
    
    /**
     * @brief perform gather op
     *
     * perform the following op: `ret[i] = vec[idx[i]]`, reverse of scatter
     * 
     * @tparam vector_t type of vec
     * @tparam indices_t type of indices
     * @param vec 
     * @param indices 
     * @return constexpr auto 
     * @see scatter
     */
    template <typename vector_t, typename indices_t>
    constexpr auto gather(const vector_t& vector, const indices_t& indices)
    {
        using return_t = meta::resolve_optype_t<gather_t,vector_t,indices_t>;

        if constexpr (meta::is_maybe_v<vector_t>) {
            // assume return_t is also maybe type
            if (static_cast<bool>(vector)) {
                auto result = gather(*vector,indices);
                // TODO: handle nested optional
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        } else {
            [[maybe_unused]] auto m = len(indices);

            const auto& vec = vector;

            auto ret = return_t{};

            if constexpr (meta::is_resizable_v<return_t>)
                ret.resize(m);
            
            [[maybe_unused]] auto gather_impl = [&](auto& ret, const auto& vec, const auto& indices, auto i){
                auto idx   = at(indices,i);
                auto value = at(vec,idx);
                at(ret,i)  = value;
            }; // gather_impl

            // assume the result is computed at compile-time if its constant index array
            if constexpr (!meta::is_constant_index_array_v<return_t>) {
                if constexpr (meta::is_fixed_index_array_v<indices_t>)
                    meta::template_for<meta::len_v<indices_t>>([&](auto i){
                        gather_impl(ret, vec, indices, i);
                    });
                else
                    for (nm_size_t i=0; i<(nm_size_t)m; i++) {
                        gather_impl(ret, vec, indices, i);
                    }
            }

            return ret;
        }
    } // gather
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GATHER_UNSUPPORTED : detail::fail_t {};
    }

    template <typename vector_t, typename indices_t>
    struct resolve_optype<
        void, index::gather_t, vector_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            using element_t [[maybe_unused]] = remove_address_space_t<get_index_element_type_t<vector_t>>;
            if constexpr (is_maybe_v<vector_t>) {
                using vector_type = get_maybe_type_t<vector_t>;
                using result_type = resolve_optype_t<index::gather_t,vector_type,indices_t>;
                using type = nmtools_maybe<result_type>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<vector_t>
                && is_constant_index_array_v<indices_t>
            ) {
                constexpr auto vector  = to_value_v<vector_t>;
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto result  = index::gather(vector,indices);
                // assuming len(result) > 0
                // transform back to type
                using init_type = nmtools_tuple<ct<at(result,0)>>;
                return template_reduce<nmtools::len(result)-1>([&](auto init, auto index){
                    using init_t   = type_t<decltype(init)>;
                    using result_i = ct<at(result,index+1)>;
                    using result_t = append_type_t<init_t,result_i>;
                    return as_value_v<result_t>;
                }, as_value_v<init_type>);
            } else if constexpr (is_clipped_index_array_v<vector_t>
                && is_constant_index_array_v<indices_t>
            ) {
                constexpr auto vector  = to_value_v<vector_t>;
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto result  = index::gather(vector,indices);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t   = type_t<decltype(init)>;
                    using result_i = clipped_size_t<at(result,index)>;
                    using result_t = append_type_t<init_t,result_i>;
                    return as_value_v<result_t>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (
                is_clipped_index_array_v<vector_t>
            ) {
                using type = resolve_optype_t<index::gather_t,decltype(to_value_v<vector_t>),indices_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_clipped_index_array_v<indices_t>
            ) {
                using type = resolve_optype_t<index::gather_t,vector_t,decltype(to_value_v<indices_t>)>;
                return as_value_v<type>;
            }
            else if constexpr (is_index_array_v<indices_t>) {
                [[maybe_unused]] constexpr auto n_vec = len_v<vector_t>;
                [[maybe_unused]] constexpr auto n_idx = len_v<indices_t>;
                [[maybe_unused]] constexpr auto b_vec = bounded_size_v<vector_t>;
                [[maybe_unused]] constexpr auto b_idx = bounded_size_v<indices_t>;
                if constexpr (n_idx > 0) {
                    using type = nmtools_array<element_t,n_idx>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_idx)>) {
                    using type = nmtools_static_vector<element_t,b_idx>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            }
            else {
                return as_value_v<error::GATHER_UNSUPPORTED<vector_t,indices_t>>;
            }
        }();

        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_GATHER_HPP