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
            nm_index_t src_1 = at(src_shape,n_axis1);
            nm_index_t src_2 = at(src_shape,n_axis2);

            src_1 = offset < 0 ? src_1 + offset : src_1;
            src_2 = offset > 0 ? src_2 - offset : src_2;
            
            auto src_i = (src_1 < src_2 ? src_1 : src_2);

            at(result,r_idx) = src_i;
        }
        
        return result;
    } // shape_diagonal

    struct diagonal_t {};

    template <typename src_shape_t, typename indices_t, typename offset_t, typename axis1_t, typename axis2_t>
    constexpr auto diagonal(const src_shape_t& src_shape, const indices_t& indices, [[maybe_unused]] offset_t offset, axis1_t axis1, axis2_t axis2)
    {
        using result_t = meta::resolve_optype_t<diagonal_t,src_shape_t,indices_t,offset_t,axis1_t,axis2_t>;

        auto result = result_t {};

        auto src_dim = len(src_shape);

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(src_dim);
        }

        auto idx_i = 0;
        for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
            if ((i == (nm_size_t)axis1) || (i == (nm_size_t)axis2)) {
                continue;
            }
            auto idx = at(indices,idx_i++);
            at(result,i) = idx;
        }

        at(result,axis1) = at(indices,meta::ct_v<-1>);
        at(result,axis2) = at(indices,meta::ct_v<-1>) + offset;

        return result;
    }
    
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_DIAGONAL_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct INDEX_DIAGONAL_UNSUPPORTED : detail::fail_t {};
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

    template <typename src_shape_t, typename indices_t, typename offset_t, typename axis1_t, typename axis2_t>
    struct resolve_optype<
        void, index::diagonal_t, src_shape_t, indices_t, offset_t, axis1_t, axis2_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>
                || !is_index_array_v<indices_t>
                || !is_index_v<offset_t>
                || !is_index_v<axis1_t>
                || !is_index_v<axis2_t>
            ) {
                using type = error::INDEX_DIAGONAL_UNSUPPORTED<src_shape_t,indices_t,offset_t,axis1_t,axis2_t>;
                return as_value_v<type>;
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM   = len_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::diagonal_t
} // nmtools::meta

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utils/isequal/isequal.hpp"
#include "nmtools/utils/isclose/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename dst_shape_t, typename offset_t, typename axis1_t, typename axis2_t, typename src_size_t>
    struct diagonal_t
        : base_indexer_t<diagonal_t<src_shape_t,dst_shape_t,offset_t,axis1_t,axis2_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using src_size_type  = meta::fwd_attribute_t<src_size_t>;

        using dst_shape_type = meta::fwd_attribute_t<dst_shape_t>;
        using dst_size_type  = meta::conditional_t<
            !meta::is_constant_index_array_v<dst_shape_type>
                && meta::is_clipped_integer_v<src_size_t>
            , src_size_type
            , decltype(index::product(meta::declval<dst_shape_type>()))
        >;

        using offset_type = offset_t;
        using axis1_type  = axis1_t;
        using axis2_type  = axis2_t;

        inline static constexpr auto n_inputs  = 1;
        inline static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const dst_shape_type dst_shape;
        const offset_type    offset;
        const axis1_type     axis1;
        const axis2_type     axis2;
        const src_size_type  src_size;
        const dst_size_type  dst_size;

        constexpr diagonal_t(const src_shape_t& src_shape
            , const dst_shape_t& dst_shape
            , offset_t offset
            , axis1_t axis1
            , axis2_t axis2
            , src_size_t src_size
        )
            : src_shape(fwd_attribute(src_shape))
            , dst_shape(fwd_attribute(dst_shape))
            , offset(offset)
            , axis1(axis1)
            , axis2(axis2)
            , src_size(src_size)
            , dst_size(index::product(dst_shape))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::diagonal(src_shape,indices,offset,axis1,axis2);
            return src_indices;
        }
    }; // diagonal_t

    template <typename src_shape_t, typename offset_t, typename axis1_t, typename axis2_t, typename src_size_t, typename src_dim_t>
    constexpr auto diagonal_indexer(const src_shape_t& src_shape, offset_t offset, axis1_t axis1, axis2_t axis2, src_size_t src_size, src_dim_t src_dim)
    {
        auto dst_shape = index::shape_diagonal(src_shape,offset,axis1,axis2);
        using dst_shape_t = decltype(dst_shape);
        if constexpr (meta::is_maybe_v<dst_shape_t> || meta::is_maybe_v<src_size_t> || meta::is_maybe_v<src_dim_t>) {
            using result_t = decltype(diagonal_indexer(unwrap(src_shape),offset,axis1,axis2,unwrap(src_size),unwrap(src_dim)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,result_t>;
            return (has_value(src_shape) && has_value(src_size)
                ? return_t{diagonal_indexer(unwrap(src_shape),offset,axis1,axis2,unwrap(src_size),unwrap(src_dim))}
                : return_t{meta::Nothing}
            );
        } else {
            // TODO: propagate error
            auto n_axis1 = unwrap(index::normalize_axis(axis1,src_dim));
            auto n_axis2 = unwrap(index::normalize_axis(axis2,src_dim));

            using n_axis1_t = decltype(n_axis1);
            using n_axis2_t = decltype(n_axis2);

            using result_t = diagonal_t<src_shape_t,dst_shape_t,offset_t,n_axis1_t,n_axis2_t,src_size_t>;
            return result_t{src_shape,dst_shape,offset,n_axis1,n_axis2,src_size};
        }
    } // diagonal_indexer

    template <typename array_t, typename offset_t=meta::ct<0>, typename axis1_t=meta::ct<0>, typename axis2_t=meta::ct<1>>
    constexpr auto diagonal(const array_t& array, offset_t offset=offset_t{}, axis1_t axis1=axis1_t{}, axis2_t axis2=axis2_t{})
    {
        auto src_shape = shape<true>(array);
        auto src_size  = size<true>(array);
        auto src_dim   = dim<true>(array);
        auto indexer   = diagonal_indexer(src_shape,offset,axis1,axis2,src_size,src_dim);
        return indexing(array,indexer);
    } // diagonal
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_DIAGONAL_HPP