#ifndef NMTOOLS_DEF_HPP
#define NMTOOLS_DEF_HPP

// this file may be used to resolve size_t
// for example, avr gcc should include <stddef.h>
// c++ for opencl can't include but already have size_t
// https://godbolt.org/z/d3vsh5T49
// https://godbolt.org/z/qEGc6orGb

#include <cstddef>

namespace nmtools
{
    using size_t = std::size_t;
}

#endif // NMTOOLS_DEF_HPP