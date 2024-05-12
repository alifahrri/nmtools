#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_ND_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_ND_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/array/index/atleast_nd.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/as_static.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/view/reshape.hpp"

namespace nmtools::view
{
    template <typename array_t, typename nd_t>
    constexpr auto atleast_nd(const array_t& array, nd_t nd)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_atleast_nd(src_shape,nd);
        return view::reshape(array,dst_shape);
    }

    template <typename array_t>
    constexpr auto atleast_1d(const array_t& array)
    {
        return atleast_nd(array,meta::ct_v<1>);
    }

    template <typename array_t>
    constexpr auto atleast_2d(const array_t& array)
    {
        return atleast_nd(array,meta::ct_v<2>);
    }

    template <typename array_t>
    constexpr auto atleast_3d(const array_t& array)
    {
        return atleast_nd(array,meta::ct_v<3>);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_ND_HPP