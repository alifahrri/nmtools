#ifndef NMTOOLS_ERROR_HPP
#define NMTOOLS_ERROR_HPP

// TODO: change all file that includes assert.hpp / exception.hpp to include this file instead

#include "nmtools/def.hpp"
#include "nmtools/assert.hpp"
#if __has_include(<stdexcept>)
#include "nmtools/exception.hpp"
#endif
#include "nmtools/stl.hpp"

namespace nmtools
{
    struct error_type
    {
        int64_t code = -1;
        nmtools_static_string message = {"unknown error"};
    };
}

#endif // NMTOOLS_ERROR_HPP