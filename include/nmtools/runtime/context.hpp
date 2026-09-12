#ifndef NMTOOLS_RUNTIME_CONTEXT_HPP
#define NMTOOLS_RUNTIME_CONTEXT_HPP

#include "nmtools/runtime/def.hpp"
#include "nmtools/runtime/ndarray.hpp"
#include <memory>

namespace nmtools::runtime
{
    class base_functor
    {
        public:
        virtual ~base_functor() = default;
        virtual auto operator()(const nmtools_list<ndarray>& operands) -> ndarray = 0;
        virtual auto graph() const noexcept -> Graph = 0;
        virtual auto hash() const noexcept -> nm_size_t = 0;
    };

    class base_context
    {
        public:
        virtual auto functors() const noexcept -> nmtools_list<::std::shared_ptr<base_functor>> = 0;
        virtual auto eval(const ndarray&) -> ndarray = 0;
    };
}

#endif // NMTOOLS_RUNTIME_CONTEXT_HPP