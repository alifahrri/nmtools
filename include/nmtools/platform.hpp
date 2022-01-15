#ifndef NMTOOLS_PLATFORM_HPP
#define NMTOOLS_PLATFORM_HPP

// try to automatically detect platform
// the included file(s) is adding some definitions,
// such as preventing to include stl

// when using platformio arduino, ARDUINO macro is defined
#ifdef ARDUINO
#include "nmtools/platform/arduino.hpp"
#endif // ARDUINO

#endif // NMTOOLS_PLATFORM_HPP