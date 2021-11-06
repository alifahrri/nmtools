#ifndef NMTOOLS_META_HPP
#define NMTOOLS_META_HPP

#include "nmtools/meta/traits.hpp"
#include "nmtools/meta/transform.hpp"
#include "nmtools/meta/array.hpp"

// use stl as default implementation for various type
// such as maybe (meta::make_maybe_type...)

#include "nmtools/meta/stl/traits.hpp"
#include "nmtools/meta/stl/array.hpp"
#include "nmtools/meta/stl/transform.hpp"

#endif // NMTOOLS_META_HPP