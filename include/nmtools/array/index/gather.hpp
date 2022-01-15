#ifndef NMTOOLS_ARRAY_INDEX_GATHER_HPP
#define NMTOOLS_ARRAY_INDEX_GATHER_HPP

#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools
{
    namespace index
    {
        /**
         * @brief specific tag to resolve return type
         * 
         */
        struct gather_t {};
    
        // TODO: cleanup index functions, handling constant index array
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
            // get the size of indices
            [[maybe_unused]] auto m = len(indices);

            // convert to array, avoid tuple_at
            [[maybe_unused]] auto vec = [&](){
                if constexpr (meta::is_constant_index_array_v<vector_t>) {
                    return meta::to_value_v<vector_t>;
                } else if constexpr (meta::is_fixed_index_array_v<vector_t>) {
                    using element_t  = meta::get_element_or_common_type_t<vector_t>;
                    constexpr auto N = meta::fixed_index_array_size_v<vector_t>;
                    using type = meta::make_array_type_t<element_t,N>;
                    auto vec   = type{};
                    meta::template_for<N>([&](auto i){
                        at(vec,i) = at(vector,i);
                    });
                    return vec;
                } else {
                    return vector;
                }
            }();

            using return_t = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
            auto ret = return_t{};

            if constexpr (meta::is_resizeable_v<return_t>)
                ret.resize(m);
            
            [[maybe_unused]] auto gather_impl = [&](auto& ret, const auto& vec, const auto& indices, auto i){
                auto idx   = at(indices,i);
                // TODO: drop tuple w/ runtime value, do not use tuple_at
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
                    for (size_t i=0; i<m; i++)
                        gather_impl(ret, vec, indices, i);
            }

            return ret;
        } // gather
    } // namespace index
} // namespace nmtools

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct GATHER_UNSUPPORTED : detail::fail_t {};
    }

    // TODO: cleanup index metafunctions, handling constant index array
    template <typename vector_t, typename indices_t>
    struct resolve_optype<
        void, index::gather_t, vector_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            constexpr auto element_vtype = [](){
                using element_t = remove_cvref_t<get_element_or_common_type_t<vector_t>>;
                if constexpr (is_integral_constant_v<element_t>) {
                    return as_value_v<typename element_t::value_type>;
                } else {
                    return as_value_v<element_t>;
                }
            }();
            using element_t = type_t<decltype(element_vtype)>;
            if constexpr (is_constant_index_array_v<vector_t>
                && is_constant_index_array_v<indices_t>
            ) {
                constexpr auto vector  = to_value_v<vector_t>;
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto result  = index::gather(vector,indices);
                // assuming len(result) > 0
                // transform back to type
                using init_type = make_tuple_type_t<ct<at(result,0)>>;
                return template_reduce<nmtools::len(result)-1>([&](auto init, auto index){
                    using init_t   = type_t<decltype(init)>;
                    using result_i = ct<at(result,index+1)>;
                    using result_t = append_type_t<init_t,result_i>;
                    return as_value_v<result_t>;
                }, as_value_v<init_type>);
            } else if constexpr (
                is_dynamic_index_array_v<indices_t>
            ) // whenever indices is dynamic, chose it
                return as_value_v<replace_element_type_t<indices_t,element_t>>;
            // some index array is not ndarray (integral_constant)
            else if constexpr (
                is_constant_index_array_v<vector_t> && is_hybrid_index_array_v<indices_t>
            ) /* exactly follow indices */ {
                using type = replace_element_type_t<indices_t,element_t>;
                return as_value_v<type>;
            }
            else if constexpr (
                is_dynamic_ndarray_v<vector_t> && is_hybrid_index_array_v<indices_t>
            ) /* vector is dynamic resizeable */ {
                constexpr auto max_size = hybrid_index_array_max_size_v<indices_t>;
                using return_t = resize_hybrid_ndarray_max_size_t<indices_t,max_size>;
                return as_value_v<replace_element_type_t<return_t,element_t>>;
            }
            else if constexpr (
                is_hybrid_ndarray_v<vector_t> && is_dynamic_index_array_v<indices_t>
            ) /* indices is dynamic resizeable */
                return as_value_v<replace_element_type_t<indices_t,element_t>>;
            else if constexpr (
                is_hybrid_ndarray_v<vector_t> && is_hybrid_index_array_v<indices_t>
            ) /* both are hybrid, prefer indices */ {
                constexpr auto max_size = hybrid_index_array_max_size_v<indices_t>;
                using return_t = resize_hybrid_ndarray_max_size_t<indices_t,max_size>;
                return as_value_v<replace_element_type_t<return_t,element_t>>;
            }
            else if constexpr (
                is_hybrid_ndarray_v<vector_t> && is_fixed_index_array_v<indices_t>
            ) /* prefer indices */ {
                constexpr auto max_size = hybrid_index_array_max_size_v<indices_t>;
                using return_t = resize_hybrid_ndarray_max_size_t<indices_t,max_size>;
                return as_value_v<replace_element_type_t<return_t,element_t>>;
            }
            else if constexpr (
                is_fixed_size_ndarray_v<vector_t> && is_hybrid_index_array_v<indices_t>
            ) /* prefer indices */ {
                constexpr auto max_size = hybrid_index_array_max_size_v<indices_t>;
                using return_t = resize_hybrid_ndarray_max_size_t<indices_t,max_size>;
                return as_value_v<replace_element_type_t<return_t,element_t>>;
            }
            else if constexpr (
                is_dynamic_ndarray_v<vector_t> && is_fixed_index_array_v<indices_t>
            ) /* prefer indices */ {
                using type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
                return as_value_v<replace_element_type_t<type,element_t>>;
            }
            else if constexpr (
                is_fixed_size_ndarray_v<vector_t> && is_dynamic_index_array_v<indices_t>
            ) /* prefer indices */ {
                return as_value_v<replace_element_type_t<indices_t,element_t>>;
            }
            else if constexpr (
                is_fixed_size_ndarray_v<vector_t> && is_fixed_index_array_v<indices_t>
            ) /* prefer indices */ {
                constexpr auto size = fixed_index_array_size_v<indices_t>;
                using type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
                using return_t = resize_fixed_vector_t<type,size>;
                return as_value_v<replace_element_type_t<return_t,element_t>>;
            }
            else {
                return as_value_v<error::GATHER_UNSUPPORTED<vector_t,indices_t>>;
            }
        }();

        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_GATHER_HPP