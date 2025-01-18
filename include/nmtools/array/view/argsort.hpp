#ifndef NMTOOLS_ARRAY_VIEW_ARGSORT_HPP
#define NMTOOLS_ARRAY_VIEW_ARGSORT_HPP

#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/array/index/remove_dims.hpp"
#include "nmtools/array/index/insert_index.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/array/core/discrete.hpp"
#include "nmtools/array/core/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/mutable_slice.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/utility/apply_resize.hpp"

// for iota
#include <numeric>
// for sort
#include <algorithm>

namespace nmtools::view
{
    /**
     * @brief View type for argsort
     * 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename axis_t>
    struct argsort_t
    {
        using array_type = resolve_array_type_t<array_t>;
        using axis_type  = const axis_t;
        using shape_type = decltype(shape(meta::declval<array_t>()));

        array_type array;
        shape_type dst_shape;
        axis_type  axis;

        constexpr argsort_t(const array_t& array, axis_t axis)
            : array(initialize<array_type>(array))
            // the resulting shape is just the same as source array
            , dst_shape(shape(array))
            , axis(axis)
        {}

        template <typename output_t>
        constexpr auto eval(output_t& output) const
        {
            // TODO: check if element_type of output_t is index
            if constexpr (meta::is_resizable_v<output_t>) {
                ::nmtools::detail::apply_resize(output, dst_shape);
            }
            using index_t = meta::get_element_type_t<output_t>;

            auto success = true;
            auto batch_shape = [&](){
                constexpr auto dim = meta::len_v<shape_type>;
                if constexpr (dim == 1) {
                    return dst_shape;
                } else {
                    auto batch_shape = index::remove_dims(dst_shape,axis);
                    return batch_shape;
                }
            }();
            auto dst_indices = index::ndindex(batch_shape);
            auto sort_dims = at(dst_shape,axis);
            for (size_t i=0; i<dst_indices.size(); i++) {
                auto batch_indices = dst_indices[i];

                // on single dim array, select all,
                // otherwise insert ellipsis to select axis
                auto slice_indices = [&](){
                    constexpr auto dim = meta::len_v<shape_type>;
                    if constexpr (dim == 1) {
                        auto all = nmtools_array{nmtools_tuple{None,None}};
                        using all_t = decltype(all);
                        return nmtools_maybe<all_t>{all};
                    } else {
                        return index::insert_index(batch_indices,Ellipsis,axis);
                    }
                }();
                if (!slice_indices) {
                    success = false;
                    break;
                }
                auto batch_slice = view::apply_mutable_slice(output,*slice_indices);
                auto array_slice = [&](){
                    if constexpr (meta::is_pointer_v<array_type>) {
                        return unwrap(view::flatten(view::apply_slice(*array,*slice_indices)));
                    } else {
                        return unwrap(view::flatten(view::apply_slice(array,*slice_indices)));
                    }
                }();

                // TODO: support arduino, by implementing iota and sort in utl
                {
                    // TODO: support fixed size
                    // NOTE: assume constructor is also resize, see std::vector constructor
                    auto sort_indices = nmtools_list<index_t>(sort_dims);
                    std::iota(sort_indices.begin(), sort_indices.end(), 0);
                    std::sort(sort_indices.begin(), sort_indices.end(),
                        [&](auto left, auto right){
                            return (array_slice(left) < array_slice(right));
                    });
                    batch_slice = sort_indices;
                }
            }
            return success;
        } // eval
    }; // argsort_t

    /**
     * @brief Return the indices that would sort an array
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array input array to sort
     * @param axis  axis along which to sort
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t>
    constexpr auto argsort(const array_t& array, axis_t axis)
    {
        auto axis_ = index::normalize_axis(axis,dim(array));
        using normalized_axis_t = meta::get_maybe_type_t<decltype(axis_)>;
        using view_t   = discrete_t<argsort_t,array_t,normalized_axis_t>;
        // TODO: enable error handling using exception & cassert
        using return_t = nmtools_maybe<view_t>;
        if (static_cast<bool>(axis_)) {
            return return_t{view_t{{array,*axis_}}};
        } else {
            return return_t{}; // Nothing
        }
    } // argsort
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ARGSORT_HPP