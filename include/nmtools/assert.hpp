#ifndef NMTOOLS_ASSERT_HPP
#define NMTOOLS_ASSERT_HPP

#ifdef ARDUINO
#include "nmtools/platform/assert/arduino.hpp"
#else 
#include "nmtools/platform/assert/stl.hpp"
#endif

#endif // NMTOOLS_ASSERT_HPP