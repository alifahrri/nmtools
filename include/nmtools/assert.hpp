#ifndef NMTOOLS_ASSERT_HPP
#define NMTOOLS_ASSERT_HPP

#if defined(NMTOOLS_NOASSERT)
#include "nmtools/platform/assert/noassert.hpp"
#elif defined(ARDUINO)
#include "nmtools/platform/assert/arduino.hpp"
#elif defined(__CUDA__)
#include "nmtools/platform/assert/cuda.hpp"
#elif defined(__HIP__)
#include "nmtools/platform/assert/hip.hpp"
#elif defined(__OPENCL_VERSION__)
#include "nmtools/platform/assert/opencl.hpp"
#else 
#include "nmtools/platform/assert/stl.hpp"
#endif

#endif // NMTOOLS_ASSERT_HPP