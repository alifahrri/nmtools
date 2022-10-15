#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/atleast_nd.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    template <typename array_t>
    struct atleast_2d_t
    {
        using array_type = resolve_array_type_t<array_t>;

        using nd_type = meta::ct<2ul>;

        using src_shape_type = decltype(nmtools::shape<true>(meta::declval<array_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_atleast_nd_t, src_shape_type, nd_type>;

        array_type     array_;
        dst_shape_type shape_;

        constexpr atleast_2d_t(const array_t& array)
            : array_(initialize(array, meta::as_value_v<array_type>))
            , shape_(index::shape_atleast_nd(nmtools::shape<true>(array),nd_type{}))
        {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // for now, assume indices is generated such that
            // they are within range
            // TODO: check shape
            // TODO: move to "index" member function
            if constexpr (meta::is_num_v<array_t>) {
                return array_;
            } else {
                auto indices_ = pack_indices(indices...);
                auto expanded_shape   = shape();
                auto squeezed_strides = index::compute_strides(expanded_shape);

                auto shape_     = detail::shape(array_);
                auto offset     = index::compute_offset(indices_,squeezed_strides);
                auto tf_indices = index::compute_indices(offset,shape_);
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_at(*array_,tf_indices);
                } else {
                    return apply_at(array_,tf_indices);
                }
            }
        } // operator()
    }; // atleast_2d_t

    /**
     * @brief Create a atleast_2d_t view to a given array.
     * 
     * Views array with at least 2 dimension. Also accept scalar value.
     *
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto atleast_2d(const array_t& array)
    {
        using view_t = decorator_t<atleast_2d_t, array_t>;
        return view_t{{array}};
    } // atleast_2d
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t>
    struct get_element_type< view::decorator_t<view::atleast_2d_t, array_t> >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_num_v<array_t>) {
                return as_value_v<array_t>;
            } else {
                return as_value_v<get_element_type_t<array_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename array_t>
    struct is_ndarray< view::decorator_t< view::atleast_2d_t, array_t >>
    {
        static constexpr auto value = meta::is_num_v<array_t> || is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP