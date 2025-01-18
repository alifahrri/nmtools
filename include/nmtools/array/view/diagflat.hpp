#ifndef NMTOOLS_ARRAY_VIEW_DIAGFLAT_HPP
#define NMTOOLS_ARRAY_VIEW_DIAGFLAT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct diagflat_t {};

    template <typename src_shape_t, typename indices_t, typename k_t>
    constexpr auto diagflat(const src_shape_t& src_shape, const indices_t& indices, k_t k)
    {
        using result_t = meta::resolve_optype_t<diagflat_t,src_shape_t,indices_t,k_t>;
        // TODO: change to either<src_indices_t,none_t>;
        using return_t = nmtools_maybe<result_t>;

        auto result = result_t {};

        [[maybe_unused]]
        auto src_dim = len(src_shape);
        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(src_dim);
        }

        nm_index_t index_0 = at(indices,meta::ct_v<-2>);
        nm_index_t index_1 = at(indices,meta::ct_v<-1>);

        if (index_1 == nm_index_t(index_0 + k)) {
            // if k > 0, taking index_0 is enough
            at(result,0) = index_0 + (k > 0 ? 0 : k);
            return return_t{result};
        } else {
            return return_t{meta::Nothing};
        }
    } // diagflat
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct DIAGFLAT_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t, typename indices_t, typename k_t>
    struct resolve_optype<
        void, index::diagflat_t, src_shape_t, indices_t, k_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t>
                || !is_index_array_v<src_shape_t>
                || !is_num_v<k_t>
            ) {
                using type = error::DIAGFLAT_UNSUPPORTED<src_shape_t,indices_t,k_t>;
                return as_value_v<type>;
            } else {
                constexpr auto DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
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
    }; // diagflat_t
} // nmtools::meta

/*===========================================================================*/

#include "nmtools/array/core/decorator.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/core/indexing.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/isclose/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename dst_shape_t, typename k_t>
    struct diagflat_t
        : base_indexer_t<diagflat_t<src_shape_t,dst_shape_t,k_t>>
    {
        using src_shape_type = nmtools_tuple<meta::fwd_attribute_t<src_shape_t>,none_t>;
        using src_size_type  = nmtools_tuple<decltype(index::product(nmtools::get<0>(meta::declval<src_shape_type>()))),none_t>;

        using dst_shape_type = meta::fwd_attribute_t<dst_shape_t>;
        using dst_size_type  = decltype(index::product(meta::declval<dst_shape_type>()));

        using k_type = meta::fwd_attribute_t<k_t>;

        inline static constexpr auto n_inputs  = 2;
        inline static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const dst_shape_type dst_shape;
        const src_size_type  src_size;
        const dst_size_type  dst_size;
        const k_type k;

        constexpr diagflat_t(const src_shape_t& src_shape
            , const dst_shape_t& dst_shape
            , k_t k
        )
            : src_shape(nmtools_tuple{src_shape,None})
            , dst_shape(fwd_attribute(dst_shape))
            , src_size(nmtools_tuple{index::product(nmtools::get<0>(this->src_shape)),None})
            , dst_size(index::product(dst_shape))
            , k(fwd_attribute(k))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::diagflat(nmtools::get<0>(src_shape),indices,k);
            using src_indices_t = meta::get_maybe_type_t<decltype(src_indices)>;
            // TODO: change index::diagflat to return either, or tagged L/R
            using result_t = nmtools_either<src_indices_t,none_t>;
            if (src_indices) {
                return result_t{unwrap(src_indices)};
            } else {
                return result_t{None};
            }
        }
    }; // diagflat_t

    template <typename src_shape_t, typename src_size_t, typename k_t>
    constexpr auto diagflat_indexer(const src_shape_t& src_shape, const src_size_t& src_size, k_t k)
    {
        if constexpr (meta::is_maybe_v<src_shape_t> || meta::is_maybe_v<src_size_t>) {
            using result_t = decltype(diagflat_indexer(unwrap(src_shape),unwrap(src_size),k));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(src_size)
                ? return_t{diagflat_indexer(unwrap(src_shape),unwrap(src_size),k)}
                : return_t{meta::Nothing}
            );
        } else {
            auto dst_shape = [&](){
                if constexpr (meta::is_constant_index_v<src_size_t>
                    && meta::is_constant_index_v<k_t>
                ) {
                    constexpr auto K = (k_t::value >= 0 ? k_t::value : -k_t::value);
                    constexpr nm_index_t size = src_size_t::value + K;
                    return nmtools_tuple{size,size};
                } else {
                    auto K = k >= 0 ? k : -k;
                    nm_index_t size = src_size + K;
                    return nmtools_array{size,size};
                }
            }();
            auto indexer = diagflat_t{src_shape,dst_shape,k};
            return indexer;
        }
    }

    template <typename array_t, typename k_t=nm_index_t>
    constexpr auto diagflat(const array_t& array, k_t k=k_t{0})
    {
        auto flat_array = view::flatten(array);
        auto src_shape  = shape<true>(flat_array);
        auto src_size   = size<true>(flat_array);
        auto indexer    = diagflat_indexer(src_shape,src_size,k);
        using element_t = meta::get_element_type_t<array_t>;
        auto operands   = pack_operands(flat_array,static_cast<element_t>(0));
        return indexing(operands,indexer);
    } // diagflat
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_DIAGFLAT_HPP