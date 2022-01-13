#ifndef NMTOOLS_UTILITY_HPP
#define NMTOOLS_UTILITY_HPP

// may decide ro use stl or not, on arduino for example
#include "nmtools/platform.hpp"

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

#endif // NMTOOLS_UTILITY_HPP