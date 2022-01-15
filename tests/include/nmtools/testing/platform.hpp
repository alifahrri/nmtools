#ifndef NMTOOLS_TESTING_PLATFORM_HPP
#define NMTOOLS_TESTING_PLATFORM_HPP

#include "nmtools/platform.hpp"

#if (defined(ARDUINO)) or (defined(PLATFORMIO))
#include "nmtools/testing/platform/arduino.hpp"
#endif // ARDUINO

#endif // NMTOOLS_TESTING_PLATFORM_HPP