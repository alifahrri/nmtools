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
            auto n = tuple_size(vec);
            // get the size of indices
            auto m = tuple_size(indices);
            // @todo static assert whenever possible
            assert (n == m
                // , "unsupported permute, mismatched dimension between vec and indices"
            );

            using std::tuple_size_v;
            // std::array type has value_type
            using element_t = meta::get_element_type_t<vector_t>;
            using common_t = std::conditional_t<
                std::is_void_v<element_t>,
                meta::apply_t<std::common_type,vector_t>,
                element_t
            >;

            // assume return type is same
            auto ret = vector_t{};
            if constexpr (meta::is_resizeable_v<vector_t>)
                ret.resize(vec.size()); // assuming indicesh has size
            
            auto gather_impl = [&](auto& ret, const auto& vec, const auto& indices, auto i){
                auto idx   = at(indices,i);
                auto value = tuple_at(vec,idx);
                at(ret,i)  = value;
            }; // gather_impl

            // handle tuple if it has common_type
            if constexpr (meta::has_tuple_size_v<vector_t> && !std::is_void_v<common_t>)
                meta::template_for<tuple_size_v<vector_t>>([&](auto i){
                    gather_impl(ret, vec, indices, i);
                });
            else
                for (size_t i=0; i<m; i++)
                    gather_impl(ret, vec, indices, i);
            return ret;
        } // gather
    } // namespace index
} // namespace nmtools

#endif // NMTOOLS_ARRAY_INDEX_GATHER_HPP