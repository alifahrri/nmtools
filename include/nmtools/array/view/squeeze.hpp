#ifndef NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP
#define NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/array/index/squeeze.hpp"

namespace nmtools::view
{
    /**
     * @brief remove single dimensional entry from array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto squeeze(const array_t& array)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_squeeze(src_shape);
        return view::reshape(array,dst_shape);
    } // squeeze
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP