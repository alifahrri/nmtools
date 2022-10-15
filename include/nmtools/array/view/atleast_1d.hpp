#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_1D_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_1D_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/atleast_nd.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/apply_at.hpp"

namespace nmtools::view
{
    template <typename array_t>
    struct atleast_1d_t
    {
        // TODO: consider to copy when array_t is simply arithmetic type
        using array_type = resolve_array_type_t<array_t>;

        using nd_type = meta::ct<1ul>;

        using src_shape_type = decltype(nmtools::shape<true>(meta::declval<array_t>()));
        using dst_shape_type = const meta::resolve_optype_t<index::shape_atleast_nd_t, src_shape_type, nd_type>;

        array_type     array_;
        dst_shape_type shape_;

        constexpr atleast_1d_t(const array_t& array)
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
            // TODO: move to "index" member function
            // TODO: check shape
            if constexpr (meta::is_num_v<array_t>) {
                return array_;
            } else {
                auto indices_ = pack_indices(indices...);
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_at(*array_, indices_);
                } else {
                    return apply_at(array_, indices_);
                }
            }
        } // operator()
    }; // atleast_1d_t

    /**
     * @brief Create a atleast_1d_t view to a given array.
     * 
     * Views array with at least 1 dimension. Also accept scalar value.
     *
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto atleast_1d(const array_t& array)
    {
        using view_t = decorator_t<atleast_1d_t, array_t>;
        return view_t{{array}};
    } // atleast_1d
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t>
    struct get_element_type< view::decorator_t<view::atleast_1d_t, array_t> >
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
    struct bounded_size<
        view::decorator_t< view::atleast_1d_t, array_t >
    >
    {
        static constexpr auto value = bounded_size_v<array_t>;
    }; // bounded_size

    template <typename array_t>
    struct is_ndarray< view::decorator_t< view::atleast_1d_t, array_t >>
    {
        static constexpr auto value = is_num_v<array_t> || is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_1D_HPP