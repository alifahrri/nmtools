#ifndef NMTOOLS_ARRAY_INDEX_REVERSE_HPP
#define NMTOOLS_ARRAY_INDEX_REVERSE_HPP

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    // tag to resolve index reverse type
    struct reverse_t {};

    /**
     * @brief entrypoint for reversing array (of indices)
     * 
     * @tparam indices_t array of same type
     * @param indices 
     * @return constexpr auto 
     */
    template <typename indices_t>
    constexpr auto reverse(const indices_t& indices)
    {
        using result_t = meta::resolve_optype_t<reverse_t,indices_t>;
        using size_type = size_t;
        auto ret = result_t{};
        // assume already reversed at meta::resolve if result_t is constant
        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            [[maybe_unused]] auto n = (size_type)len(indices);
            if constexpr (meta::is_resizable_v<result_t>)
                ret.resize(n);
            // some fn still allow tuple of runtime index, must be unrolled
            // TODO: consider to drop tuple of runtime index
            if constexpr (meta::is_fixed_index_array_v<indices_t>) {
                constexpr auto N = meta::len_v<indices_t>;
                meta::template_for<N>([&](auto index){
                    constexpr auto i = N-1-index;
                    at(ret,index) = at<i>(indices);
                });
            } else {
                for (size_type i=0; i<n; i++)
                    at(ret,i) = at(indices,n-1-i);
            }
        }
        return ret;
    } // reverse
} // namespace nmtools

namespace nmtools::meta
{

    namespace error
    {
        struct INDEX_REVERSE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename indices_t>
    struct resolve_optype<
        void, index::reverse_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<indices_t>) {
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto reversed = index::reverse(indices);
                using init_type = nmtools_tuple<ct<at(reversed,0)>>;
                // convert back to type
                return template_reduce<::nmtools::len(reversed)-1>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using result_t = append_type_t<init_t,ct<at(reversed,index+1)>>;
                    return as_value_v<result_t>;
                }, as_value_v<init_type>);
            } else if constexpr (is_index_array_v<indices_t>) {
                // may be array or tuple of (runtime) index
                // some fn allow tuple of runtime index
                // TODO: consider to drop tuple of runtime index
                using type = tuple_to_array_t<transform_bounded_array_t<indices_t>>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::INDEX_REVERSE_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REVERSE_HPP