#ifndef NMTOOLS_UTIL_STATIC_STACK_HPP
#define NMTOOLS_UTIL_STATIC_STACK_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/array.hpp"

namespace nmtools::utl
{
    template <typename T, nm_size_t N>
    struct static_stack
    {
        using buffer_type = utl::array<T,N>;
        using size_type   = nm_size_t;

        buffer_type buffer_;
        size_type size_;

        constexpr static_stack()
            : buffer_{}
            , size_{0}
        {}

        constexpr auto& top() const noexcept
        {
            auto idx = (nm_index_t)size_-1;
            idx = (idx >= 0 ? idx : 0);
            return buffer_[idx];
        }

        constexpr auto size() const noexcept
        {
            return size_;
        }

        constexpr auto empty() const noexcept
        {
            return size_ == 0;
        }

        constexpr auto push(const T& t)
        {
            nmtools_assert( size_ < N
                , "static_stack already full");
            
            size_ += 1;
            buffer_[size_-1] = t;
        }

        constexpr auto pop()
        {
            size_ -= 1;
            auto res = buffer_[size_];
            return res;
        }
    };
}

#endif // NMTOOLS_UTIL_STATIC_STACK_HPP