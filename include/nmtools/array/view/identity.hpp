#ifndef NMTOOLS_ARRAY_VIEW_IDENTITY_HPP
#define NMTOOLS_ARRAY_VIEW_IDENTITY_HPP

#include "nmtools/array/view/eye.hpp"

namespace nmtools::view
{
    template <typename n_t, typename T=float>
    constexpr auto identity(n_t n, dtype_t<T> dtype=dtype_t<T>{})
    {
        auto a = view::eye(n,None,0,dtype);
        return a;
    }
}

#endif // NMTOOLS_ARRAY_VIEW_IDENTITY_HPP