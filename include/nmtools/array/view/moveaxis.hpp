#ifndef NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP

#include "nmtools/array/index/argsort.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/array/index/moveaxis.hpp"
#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view::detail
{
    using nmtools::index::moveaxis_to_transpose;
}

namespace nmtools::view
{
    /**
     * @brief Move axes of an array to a new postions.
     * 
     * Under the hood, this creates transpose view.
     * 
     * @tparam array_t 
     * @tparam source_t 
     * @tparam destination_t 
     * @param array         input array
     * @param source        original postions of axes to be moved
     * @param destination   desired position for each original axes
     * @return constexpr auto 
     */
    template <typename array_t, typename source_t, typename destination_t>
    constexpr auto moveaxis(const array_t& array, const source_t& source, const destination_t& destination)
    {
        auto shape_ = shape<true>(array);
        auto order  = index::moveaxis_to_transpose(shape_,source,destination);
        // order should be maybe type
        using result_t = meta::remove_cvref_t<decltype(view::transpose(array,*order))>;
        nmtools_assert_prepare_type( return_t, result_t );
        nmtools_assert( order, "unsupported moveaxis arguments", return_t );

        return return_t{view::transpose(array,*order)};
    } // moveaxis
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP