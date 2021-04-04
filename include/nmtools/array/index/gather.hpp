#ifndef NMTOOLS_ARRAY_INDEX_GATHER_HPP
#define NMTOOLS_ARRAY_INDEX_GATHER_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/shape.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    namespace index
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
        constexpr auto gather(const vector_t& vec, const indices_t& indices)
        {
            constexpr auto indices_is_tuple = meta::is_specialization_v<vector_t,std::tuple> 
                || meta::is_specialization_v<vector_t,std::tuple>;
            constexpr auto order_is_tuple = meta::is_specialization_v<indices_t,std::tuple> 
                || meta::is_specialization_v<indices_t,std::tuple>;
            // get the size of vec
            auto n = len(vec);
            // get the size of indices
            auto m = len(indices);

            using std::tuple_size_v;
            using return_t = meta::resolve_optype_t<gather_t,vector_t,indices_t>;
            auto ret = return_t{};

            if constexpr (meta::is_resizeable_v<return_t>)
                ret.resize(m);
            
            auto gather_impl = [&](auto& ret, const auto& vec, const auto& indices, auto i){
                auto idx   = at(indices,i);
                auto value = tuple_at(vec,idx);
                at(ret,i)  = value;
            }; // gather_impl

            if constexpr (meta::has_tuple_size_v<indices_t>)
                meta::template_for<tuple_size_v<indices_t>>([&](auto i){
                    gather_impl(ret, vec, indices, i);
                });
            else
                for (size_t i=0; i<m; i++)
                    gather_impl(ret, vec, indices, i);
            return ret;
        } // gather
    } // namespace index
} // namespace nmtools

namespace nmtools::meta
{
    template <typename vector_t, typename indices_t>
    struct resolve_optype<
        void, index::gather_t, vector_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_dynamic_index_array_v<vector_t> && is_dynamic_index_array_v<indices_t>
            ) // both are dynamic resizeable
                return as_value<vector_t>{};
            else if constexpr (
                is_dynamic_index_array_v<vector_t> && is_hybrid_ndarray_v<indices_t>
            ) // vector is dynamic resizeable
                return as_value<vector_t>{};
            else if constexpr (
                is_hybrid_ndarray_v<vector_t> && is_dynamic_index_array_v<indices_t>
            ) // indices is dynamic resizeable
                return as_value<indices_t>{};
            else if constexpr (
                is_hybrid_ndarray_v<vector_t> && is_hybrid_ndarray_v<indices_t>
            ) // both are hybrid, prefer indices
                return as_value<indices_t>{};
            else if constexpr (
                is_hybrid_ndarray_v<vector_t> && is_fixed_index_array_v<indices_t>
            ) /* prefer indices */ {
                using type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
                return as_value<type>{};
            }
            else if constexpr (
                is_fixed_index_array_v<vector_t> && is_hybrid_ndarray_v<indices_t>
            ) /* prefer indices */
                return as_value<indices_t>{};
            else if constexpr (
                is_dynamic_index_array_v<vector_t> && is_fixed_index_array_v<indices_t>
            ) /* prefer indices */ {
                using type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
                return as_value<type>{};
            }
            else if constexpr (
                is_fixed_index_array_v<vector_t> && is_dynamic_index_array_v<indices_t>
            ) /* prefer indices */
                return as_value<indices_t>{};
            else if constexpr (
                is_fixed_index_array_v<vector_t> && is_fixed_index_array_v<indices_t>
            ) /* prefer indices */ {
                using type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
                return as_value<type>{};
            }
            else return as_value<void>{};
        }();

        using type = type_t<meta::remove_cvref_t<decltype(vtype)>>;

        // template <typename T>
        // struct is_resizeable_not_hybrid
        //     : logical_and<is_resizeable<T>,std::negation<is_hybrid_ndarray<T>>> {};

        // using type_list = std::tuple<vector_t,indices_t>;
        // static constexpr auto selection_kind = [](){
        //     if constexpr (apply_logical_or_v<is_resizeable_not_hybrid,type_list>)
        //         return select_resizeable_kind_t {};
        //     else if constexpr (apply_logical_or_v<is_hybrid_ndarray,type_list>)
        //         return select_hybrid_kind_t {};
        //     else return select_fixed_kind_t {};
        // }();
        // using selection_kind_t = remove_cvref_t<decltype(selection_kind)>;
        // // shape type must be arithmetic
        // using selection_t = select_array1d_t<
        //     size_policy_rhs_t, selection_kind_t, std::is_arithmetic, element_type_policy_lhs
        // >;
        // // final type
        // using type = resolve_optype_t<
        //     selection_t, vector_t, indices_t
        // >;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_GATHER_HPP