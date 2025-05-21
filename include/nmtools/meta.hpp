#ifndef NMTOOLS_META_HPP
#define NMTOOLS_META_HPP


// stl.hpp define basic sctructure (array, tuple, vector, maybe...)
// using std:: if possible, auto fallback to utl::
#include "nmtools/stl.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/platform.hpp"

// must include first, prefer stl
#ifndef NMTOOLS_DISABLE_STL
#include "nmtools/meta/stl.hpp"
#endif // NMTOOLS_DISABLE_STL

// TODO: prioritize boost as default
#include "nmtools/meta/utl.hpp"

// TODO: prioritize boost as default
#ifdef NMTOOLS_ENABLE_BOOST
#include "nmtools/meta/boost.hpp"
#endif

#include "nmtools/meta/traits.hpp"
#include "nmtools/meta/transform.hpp"
#include "nmtools/meta/array.hpp"

// TODO: remove
namespace nmtools::meta
{
    // TODO: remove, cleanup fixed shape design
    template <typename T, size_t N>
    struct nested_array_size<T[N]>
    {
        static constexpr auto value = N;
    };
}

#endif // NMTOOLS_META_HPP