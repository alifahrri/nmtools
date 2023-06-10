#ifndef NMTOOLS_PLATFORM_HPP
#define NMTOOLS_PLATFORM_HPP

// try to automatically detect platform
// the included file(s) is adding some definitions,
// such as preventing to include stl

// when using platformio arduino, ARDUINO macro is defined
#ifdef ARDUINO
#include "nmtools/platform/arduino.hpp"
#elif defined(__CUDA__)
#include "nmtools/platform/cuda.hpp"
#elif defined(__OPENCL_VERSION__)
#include "nmtools/platform/opencl.hpp"
#endif // ARDUINO

#include "nmtools/attributes.hpp"

#endif // NMTOOLS_PLATFORM_HPP