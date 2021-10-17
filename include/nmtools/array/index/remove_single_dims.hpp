#ifndef NMTOOLS_ARRAY_INDEX_REMOVE_SINGLE_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_REMOVE_SINGLE_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/index/filter.hpp"

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct remove_single_dims_t {};

    /**
     * @brief remove single dimension entry from given shape
     * 
     * @tparam shape_t 
     * @param shape 
     * @return constexpr auto 
     */
    template <typename shape_t>
    constexpr auto remove_single_dims(const shape_t& shape)
    {
        using return_t = meta::resolve_optype_t<remove_single_dims_t, shape_t>;

        auto res = return_t{};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            constexpr auto f = [](auto a){
                return a > 1;
            };
            auto [arg, squeezed] = filter(f,shape);
            // manual assignment
            auto n = len(squeezed);

            if constexpr (meta::is_resizeable_v<return_t>) {
                res.resize(n);
            }

            for (size_t i=0; i<(size_t)n; i++) {
                at(res,i) = at(squeezed,i);
            }
        }

        return res;
    } // remove_single_dims
} // namespace index

namespace nmtools::meta
{
    namespace error {
        struct INDEX_REMOVE_SINGLE_DIMS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t>
    struct resolve_optype<
        void, index::remove_single_dims_t, shape_t
    >
    {
        static constexpr inline auto vtype = [](){
            if constexpr (is_constant_index_array_v<shape_t>) {
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto result = index::remove_single_dims(shape);
                // assuming len(result) > 0
                // transform back to type
                using init_type = make_tuple_t<ct<at(result,0)>>;
                return template_reduce<::nmtools::len(result)-1>([&](auto init, auto index){
                    using init_t   = type_t<decltype(init)>;
                    using result_i = ct<at(result,index+1)>;
                    using result_t = append_type_t<init_t,result_i>;
                    return as_value_v<result_t>;
                }, as_value_v<init_type>);
            } else if constexpr (is_fixed_index_array_v<shape_t>) {
                constexpr auto n = len_v<shape_t>;
                using index_t = get_element_type_t<shape_t>;
                using type = make_hybrid_ndarray_t<index_t,n,1>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<shape_t>) {
                return as_value_v<shape_t>;
            } else {
                return as_value_v<error::INDEX_REMOVE_SINGLE_DIMS_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REMOVE_SINGLE_DIMS_HPP