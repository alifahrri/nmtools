#ifndef NMTOOLS_PROFILING_HPP
#define NMTOOLS_PROFILING_HPP

#ifdef TRACY_ENABLE
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#include "tracy/Tracy.hpp"
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#define nmtools_tracy_zone_scoped(...) \
    ZoneScopedN(__VA_ARGS__)

#else // TRACY_ENABLE

#define nmtools_tracy_zone_scoped(...)

#endif // TRACY_ENABLE

#endif // NMTOOLS_PROFILING_HPP