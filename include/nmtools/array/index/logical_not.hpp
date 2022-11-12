#ifndef NMTOOLS_ARRAY_INDEX_LOGICAL_NOT_HPP
#define NMTOOLS_ARRAY_INDEX_LOGICAL_NOT_HPP

#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    struct logical_not_t {};

    // TODO: cleanup index functions
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
        using return_t  = meta::resolve_optype_t<logical_not_t,array_t>;
        using element_t = meta::get_element_or_common_type_t<array_t>;
        static_assert ( meta::is_boolean_v<element_t>
            , "unsupported index::logical_not"
        );
        auto res = return_t{};

        // only compute if not constant, otherwise assume already computed
        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            auto s = len(array);
            if constexpr (meta::is_resizable_v<return_t>)
                res.resize(s);
            for (size_t i=0; i<s; i++)
                at(res,i) = !at(array,i);
        }

        return res;
    } // logical_not
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_LOGICAL_NOT_UNSUPPORTED : detail::fail_t{};
    } // namespace error

    template <typename array_t>
    struct resolve_optype<
        void, index::logical_not_t, array_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<array_t>) {
                // transform to value, compute at compile-time, then tranform back to type
                // this simplify handling both runtime and compile time
                constexpr auto array  = to_value_v<array_t>;
                constexpr auto result = index::logical_not(array);
                // assuming len(result) > 0
                // transform back to type
                using init_type = make_tuple_type_t<ct<at(result,0)>>;
                return template_reduce<::nmtools::len(result)-1>([&](auto init, auto index){
                    using init_t   = type_t<decltype(init)>;
                    using result_i = ct<at(result,index+1)>;
                    using result_t = append_type_t<init_t,result_i>;
                    return as_value_v<result_t>;
                }, as_value_v<init_type>);
            } else if constexpr (is_fixed_index_array_v<array_t>) {
                using type = tuple_to_array_t<array_t>;
                return as_value_v<transform_bounded_array_t<type>>;
            } else if constexpr (is_index_array_v<array_t>) {
                return as_value_v<array_t>;
            } else {
                return as_value_v<error::INDEX_LOGICAL_NOT_UNSUPPORTED<array_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_LOGICAL_NOT_HPP