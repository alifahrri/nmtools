#ifndef NMTOOLS_PROFILING_HPP
#define NMTOOLS_PROFILING_HPP

#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"

#define nmtools_tracy_zone_scoped(...) \
    ZoneScopedN(__VA_ARGS__)

#else // TRACY_ENABLE

#define nmtools_tracy_zone_scoped(...)

#endif // TRACY_ENABLE

#endif // NMTOOLS_PROFILING_HPP