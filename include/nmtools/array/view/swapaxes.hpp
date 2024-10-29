#ifndef NMTOOLS_ARRAY_VIEW_SWAPAXES_HPP
#define NMTOOLS_ARRAY_VIEW_SWAPAXES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    struct swapaxes_to_transpose_t {};

    template <typename src_dim_t, typename axis1_t, typename axis2_t>
    constexpr auto swapaxes_to_transpose([[maybe_unused]] const src_dim_t& src_dim, [[maybe_unused]] axis1_t axis1, [[maybe_unused]] axis2_t axis2)
    {
        using result_t = meta::resolve_optype_t<swapaxes_to_transpose_t,src_dim_t,axis1_t,axis2_t>;

        auto result = result_t {};
        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(src_dim);
            }
            
            for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                at(result,i) = i;
            }

            // TODO: propagate error handling
            auto m_axis1 = unwrap(normalize_axis(axis1,src_dim));
            auto m_axis2 = unwrap(normalize_axis(axis2,src_dim));

            auto tmp = at(result,m_axis1);
            at(result,m_axis1) = at(result,m_axis2);
            at(result,m_axis2) = tmp;
        }

        return result;
    } // swapaxes_to_transpose

} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SWAPAXES_TO_TRANSPOSE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_dim_t, typename axis1_t, typename axis2_t>
    struct resolve_optype<
        void, index::swapaxes_to_transpose_t, src_dim_t, axis1_t, axis2_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<src_dim_t>
                || !is_index_v<axis1_t>
                || !is_index_v<axis2_t>
            ) {
                using type = error::SWAPAXES_TO_TRANSPOSE_UNSUPPORTED<src_dim_t,axis1_t,axis2_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<src_dim_t>
                && is_constant_index_v<axis1_t>
                && is_constant_index_v<axis2_t>
            ) {
                constexpr auto axis1 = to_value_v<axis1_t>;
                constexpr auto axis2 = to_value_v<axis2_t>;
                constexpr auto result = index::swapaxes_to_transpose(src_dim_t{},axis1,axis2);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type   = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_constant_index_v<src_dim_t>) {
                constexpr auto N = to_value_v<src_dim_t>;
                using type = nmtools_array<nm_size_t,N>;
                return as_value_v<type>;
            } else if constexpr (is_clipped_integer_v<src_dim_t>) {
                constexpr auto N = to_value_v<src_dim_t>;
                using type = nmtools_static_vector<nm_size_t,N>;
                return as_value_v<type>;
            } else {
                // TODO: support small vector
                using type = nmtools_list<nm_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // nmtools::meta

#include "nmtools/array/view/transpose.hpp"

namespace nmtools::view
{
    template <typename array_t, typename axis1_t, typename axis2_t>
    constexpr auto swapaxes(const array_t& array, axis1_t axis1, axis2_t axis2)
    {
        auto src_dim = dim<true>(array);
        auto axes = index::swapaxes_to_transpose(src_dim,axis1,axis2);
        return view::transpose(array,axes);
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SWAPAXES_HPP