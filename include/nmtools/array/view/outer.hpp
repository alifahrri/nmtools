#ifndef NMTOOLS_ARRAY_VIEW_OUTER_HPP
#define NMTOOLS_ARRAY_VIEW_OUTER_HPP

#include "nmtools/array/core/alias.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t>
    constexpr auto outer(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto aliased = view::aliased(lhs,rhs);
        auto flat_lhs = view::flatten(nmtools::get<0>(aliased));
        auto flat_rhs = view::flatten(nmtools::get<1>(aliased));

        return view::multiply(
            view::reshape(flat_lhs,nmtools_tuple{meta::ct_v<-1>,meta::ct_v<1>})
            , flat_rhs
        );
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_OUTER_HPP