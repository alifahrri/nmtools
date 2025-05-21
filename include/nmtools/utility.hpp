#ifndef NMTOOLS_UTILITY_HPP
#define NMTOOLS_UTILITY_HPP

// may decide ro use stl or not, on arduino for example
#include "nmtools/platform.hpp"

#include "nmtools/stl.hpp"

// collection of utility functions
// that may be depends on type and value,
// in contrast to metafunctions which only depends on type

#include "nmtools/utility/get.hpp"
#include "nmtools/utility/get_if.hpp"

// including platform hpp may disable stl
#ifndef NMTOOLS_DISABLE_STL
#include "nmtools/utility/stl/get.hpp"
#include "nmtools/utility/stl/get_if.hpp"
#endif // NMTOOLS_DISABLE_STL

#include "nmtools/utility/utl/get.hpp"
#include "nmtools/utility/utl/get_if.hpp"

#include "nmtools/utility/tuple_cat.hpp"

#ifdef NMTOOLS_ENABLE_BOOST
#include "nmtools/utility/boost/get.hpp"
#endif

#include "nmtools/utility/random_engine.hpp"

#endif // NMTOOLS_UTILITY_HPP

// TODO: move to include guard above

#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/apply_isequal.hpp"
#include "nmtools/utility/apply_isequal.hpp"
#include "nmtools/utility/apply_resize.hpp"

#include "nmtools/utility/as_static.hpp"
#include "nmtools/utility/at.hpp"
// #include "nmtools/utility/cast.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/utility/ct_map.hpp"
#include "nmtools/utility/data.hpp"
#include "nmtools/utility/flatten_either.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/get_if.hpp"
#include "nmtools/utility/get.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/small_vector.hpp"
#include "nmtools/utility/to_string.hpp"
#include "nmtools/utility/tuple_cat.hpp"
#include "nmtools/utility/tuple_slice.hpp"
#include "nmtools/utility/unwrap.hpp"