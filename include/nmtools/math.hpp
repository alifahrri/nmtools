#ifndef NMTOOLS_MATH_HPP
#define NMTOOLS_MATH_HPP

// Most Arduino doesn't have stl, and no math available from std:: namespace
// ARDUINO macro is defined at least when using PlatformIO
#if defined(__OPENCL_VERSION__)
#include "nmtools/platform/math/opencl.hpp"
#elif (defined(ARDUINO) || (!__has_include(<cmath>)))
#include "nmtools/platform/math/arduino.hpp"
#else
#include "nmtools/platform/math/stl.hpp"
#endif

#endif // NMTOOLS_MATH_HPP