#ifndef NMTOOLS_EXCEPTION_HPP
#define NMTOOLS_EXCEPTION_HPP

#include <stdexcept>

namespace nmtools
{
    class exception : public ::std::runtime_error
    {
        public:
        exception(const std::string& message)
            : std::runtime_error(message)
        {}
    };
}
#endif // NMTOOLS_EXCEPTION_HPP