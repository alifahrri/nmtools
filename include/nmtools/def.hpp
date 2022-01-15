#ifndef NMTOOLS_DEF_HPP
#define NMTOOLS_DEF_HPP

// this file may be used to resolve size_t
// for example, avr gcc should include <stddef.h>
// c++ for opencl can't include but already have size_t
// https://godbolt.org/z/d3vsh5T49
// https://godbolt.org/z/qEGc6orGb

#ifdef ARDUINO

#include <stddef.h>
#include <stdint.h>

namespace nmtools
{
    using size_t = ::size_t;
    using float32_t = float;
    using float64_t = double;
    using int8_t    = ::int8_t;
    using int16_t   = ::int16_t;
    using int32_t   = ::int32_t;
    using int64_t   = ::int64_t;
    using uint8_t   = ::uint8_t;
    using uint16_t  = ::uint16_t;
    using uint32_t  = ::uint32_t;
    using uint64_t  = ::uint64_t;
} // namespace nmtools

#else // (not ARDUINO)
#include <cstddef>
#include <cstdint>

namespace nmtools
{
    using size_t = std::size_t;
    using float32_t = float;
    using float64_t = double;
    using int8_t    = std::int8_t;
    using int16_t   = std::int16_t;
    using int32_t   = std::int32_t;
    using int64_t   = std::int64_t;
    using uint8_t   = std::uint8_t;
    using uint16_t  = std::uint16_t;
    using uint32_t  = std::uint32_t;
    using uint64_t  = std::uint64_t;
}
#endif // ARDUINO

#endif // NMTOOLS_DEF_HPP