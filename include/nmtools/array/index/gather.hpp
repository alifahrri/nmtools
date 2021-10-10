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
        constexpr auto gather(const vector_t& vec, const indices_t& indices)
        {
            // get the size of indices
            [[maybe_unused]] auto m = len(indices);

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
    namespace error
    {
        struct GATHER_UNSUPPORTED : detail::fail_t {};
    }

    // TODO: cleanup index metafunctions, handling constant index array
    template <typename vector_t, typename indices_t>
    struct resolve_optype<
        void, index::gather_t, vector_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            using element_t = remove_cvref_t<get_element_or_common_type_t<vector_t>>;
            if constexpr (
                is_dynamic_index_array_v<indices_t>
            ) // whenever indices is dynamic, chose it
                return as_value_v<replace_element_type_t<indices_t,element_t>>;
            // some index array is not ndarray (integral_constant)
            else if constexpr (
                is_constant_index_array_v<vector_t> && is_hybrid_index_array_v<indices_t>
            ) /* exactly follow indices */ {
                return as_value_v<indices_t>;
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
            ) /* prefer indices */
                return as_value_v<replace_element_type_t<indices_t,element_t>>;
            else if constexpr (
                is_fixed_size_ndarray_v<vector_t> && is_fixed_index_array_v<indices_t>
            ) /* prefer indices */ {
                constexpr auto size = fixed_index_array_size_v<indices_t>;
                using type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
                using return_t = resize_fixed_vector_t<type,size>;
                return as_value_v<replace_element_type_t<return_t,element_t>>;
            }
            else {
                return as_value_v<error::GATHER_UNSUPPORTED>;
            }
        }();

        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_GATHER_HPP