#ifndef NMTOOLS_ARRAY_VIEW_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_FLATTEN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/flatten.hpp"

#include "nmtools/utils/isequal/isequal.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/as_static.hpp"
#include "nmtools/utils/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename src_size_t>
    struct flatten_t
        : base_indexer_t<flatten_t<src_shape_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using src_size_type  = meta::fwd_attribute_t<src_size_t>;

        using dst_shape_type = meta::resolve_optype_t<
            index::shape_flatten_t,src_shape_type,src_size_type>;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const src_size_type  src_size;
        const dst_shape_type dst_shape;

        constexpr flatten_t(const src_shape_t& src_shape
            , const src_size_t& src_size
        )
            : src_shape(fwd_attribute(src_shape))
            , src_size(fwd_attribute(src_size))
            , dst_shape(index::shape_flatten(src_shape,src_size))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            if constexpr (is_none_v<src_shape_type>) {
                return None;
            } else {
                auto i = at(indices,meta::ct_v<0>);
                auto src_indices = index::compute_indices(i,src_shape);
                return src_indices;
            }
        }

        template <typename...args_t>
        constexpr auto operator==(flatten_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
            ;
        }
    }; // flatten_t

    template <typename array_t>
    constexpr auto make_flatten(const array_t& array)
    {
        auto src_shape = shape<true>(array);
        auto src_size  = size<true>(array);
        auto indexer   = flatten_t{src_shape,src_size};
        return indexing(array,indexer);
    }

    template <typename array_t>
    constexpr auto flatten(const array_t& array)
    {
        auto f = [](const auto&...args){
            return make_flatten(args...);
        };
        return lift_indexing(f,array);
    } // flatten
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_FLATTEN_HPP