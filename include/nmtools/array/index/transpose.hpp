#ifndef NMTOOLS_ARRAY_INDEX_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_INDEX_TRANSPOSE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/ref.hpp"

namespace nmtools::index
{
    struct shape_transpose_t {};

    template <typename shape_t, typename axes_t>
    constexpr auto shape_transpose(const shape_t& shape, const axes_t& axes)
    {
        using result_t = meta::resolve_optype_t<shape_transpose_t,shape_t,axes_t>;

        auto res = result_t {};

        if constexpr (! meta::is_constant_index_array_v<result_t>) {
            auto N = (size_t)len(shape);
            if constexpr (meta::is_resizable_v<result_t>) {
                res.resize(N);
            }
            if constexpr (is_none_v<axes_t>) {
                // simply reverse
                if constexpr (meta::is_tuple_v<shape_t>) {
                    constexpr auto N = meta::len_v<shape_t>;
                    meta::template_for<N>([&](auto i){
                        constexpr auto I = meta::ct_v<(N-1)-decltype(i)::value>;
                        at(res,i) = at(shape,I);
                    });
                } else {
                    for (size_t i=0; i<N; i++) {
                        at(res,i) = at(shape,(N-1)-i);
                    }
                }
            } else {
                // TODO: support partial index
                if constexpr (meta::is_tuple_v<result_t>) {
                    constexpr auto N = meta::len_v<result_t>;
                    meta::template_for<N>([&](auto i){
                        at(res,i) = at(shape,at(axes,i));
                    });
                } else {
                    for (size_t i=0; i<N; i++) {
                        at(res,i) = at(shape,at(axes,i));
                    }
                }
            }
        }

        return res;
    } // shape_transpose
} // namespace nmtools::index

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct SHAPE_TRANSPOSE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename axes_t>
    struct resolve_optype<
        void, index::shape_transpose_t, shape_t, axes_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                (is_constant_index_array_v<shape_t> || is_clipped_index_array_v<shape_t>)
                && (is_constant_index_array_v<axes_t> || is_none_v<axes_t>)
            ) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto axes  = [](){
                    if constexpr (is_none_v<axes_t>) {
                        return axes_t {};
                    } else {
                        return to_value_v<axes_t>;
                    }
                }();
                constexpr auto result = index::shape_transpose(shape,axes);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_type  = type_t<decltype(init)>;
                    constexpr auto I = at(result,index);
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        using type = append_type_t<init_type,ct<I>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_type,clipped_size_t<I>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (
                (is_constant_index_array_v<shape_t> || is_clipped_index_array_v<shape_t>)
                && (is_index_array_v<axes_t> || is_none_v<axes_t>)
            ) {
                return as_value_v<decltype(to_value_v<shape_t>)>;
            } else if constexpr (is_index_array_v<shape_t> && (is_index_array_v<axes_t> || is_none_v<axes_t>)) {
                return as_value_v<shape_t>;
            } else {
                return as_value_v<error::SHAPE_TRANSPOSE_UNSUPPORTED<shape_t,axes_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
    
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_TRANSPOSE_HPP