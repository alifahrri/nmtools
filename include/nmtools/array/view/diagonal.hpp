#ifndef NMTOOLS_ARRAY_VIEW_DIAGONAL_HPP
#define NMTOOLS_ARRAY_VIEW_DIAGONAL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    struct shape_diagonal_t {};

    template <typename src_shape_t, typename offset_t, typename axis1_t, typename axis2_t>
    constexpr auto shape_diagonal([[maybe_unused]] const src_shape_t& src_shape, [[maybe_unused]] offset_t offset, [[maybe_unused]] axis1_t axis1, [[maybe_unused]] axis2_t axis2)
    {
        using result_t = meta::resolve_optype_t<shape_diagonal_t,src_shape_t,offset_t,axis1_t,axis2_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);
            auto dst_dim = src_dim - 1;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            // TODO: propagate error handling
            auto n_axis1 = unwrap(normalize_axis(axis1,src_dim));
            auto n_axis2 = unwrap(normalize_axis(axis2,src_dim));

            nm_size_t r_idx = 0;
            for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                if ((i == n_axis1) || (i == n_axis2)) {
                    continue;
                }
                at(result,r_idx++) = at(src_shape,i);
            }
            auto src_1 = at(src_shape,n_axis1);
            auto src_2 = at(src_shape,n_axis2);
            at(result,r_idx) = (src_1 < src_2 ? src_1 : src_2) - (offset >= 0 ? offset : -offset);
        }
        
        return result;
    } // shape_diagonal

    struct diagonal_t {};

    template <typename src_shape_t, typename indices_t, typename offset_t, typename axis1_t, typename axis2_t>
    constexpr auto diagonal(const src_shape_t& src_shape, const indices_t& indices, offset_t offset, axis1_t axis1, axis2_t axis2)
    {
        using result_t = meta::resolve_optype_t<diagonal_t,src_shape_t,indices_t,offset_t,axis1_t,axis2_t>;

        auto result = result_t {};

        auto src_dim = len(src_shape);

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(src_dim);
        }

        return result;
    }
    
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_DIAGONAL_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename offset_t, typename axis1_t, typename axis2_t>
    struct resolve_optype<
        void, index::shape_diagonal_t, src_shape_t, offset_t, axis1_t, axis2_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_v<offset_t>
                || !is_index_v<axis1_t>
                || !is_index_v<axis2_t>
            ) {
                using type = error::SHAPE_DIAGONAL_UNSUPPORTED<src_shape_t,offset_t,axis1_t,axis2_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && is_constant_index_v<offset_t>
                && is_constant_index_v<axis1_t>
                && is_constant_index_v<axis2_t>
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto offset = to_value_v<offset_t>;
                constexpr auto axis1  = to_value_v<axis1_t>;
                constexpr auto axis2  = to_value_v<axis2_t>;
                constexpr auto result = index::shape_diagonal(src_shape,offset,axis1,axis2);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type   = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                },as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM   = len_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM-1>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM-1>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::shape_diagonal_t
} // nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_DIAGONAL_HPP