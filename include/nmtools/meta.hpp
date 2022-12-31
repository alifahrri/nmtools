#ifndef NMTOOLS_META_HPP
#define NMTOOLS_META_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/meta/def.hpp"

// use stl as default implementation for various type
// such as maybe (meta::make_maybe_type...)

// must include first, prefer stl
#ifndef NMTOOLS_DISABLE_STL
#include "nmtools/meta/stl.hpp"
#endif // NMTOOLS_DISABLE_STL

// TODO: prioritize boost as default
#include "nmtools/meta/utl.hpp"

#ifdef NMTOOLS_ENABLE_BOOST
#include "nmtools/meta/boost.hpp"
#endif

#include "nmtools/meta/traits.hpp"
#include "nmtools/meta/transform.hpp"
#include "nmtools/meta/array.hpp"

namespace nmtools::meta
{
    // quick workaround to support fixed_shape for raw array.
    // defined here to avoid compiler error about implicit instantiation on undeclared type (make_array_type)
    // TODO: remove, cleanup fixed shape design
    template <typename T, size_t N>
    struct nested_array_size<T[N]>
    {
        static constexpr auto value = N;
    };
}

// TODO: do not include top level utility in top level meta
#include "nmtools/utility.hpp"

#endif // NMTOOLS_META_HPP