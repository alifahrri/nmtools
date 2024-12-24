#ifndef NMTOOLS_UTL_STATIC_QUEUE_HPP
#define NMTOOLS_UTL_STATIC_QUEUE_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/meta/bits/array/resize_bounded_size.hpp"

namespace nmtools::utl
{
    template <typename T, nm_size_t N>
    struct static_queue
    {
        using buffer_type = utl::array<T,N>;
        using size_type   = nm_size_t;

        buffer_type buffer_;
        size_type size_;

        constexpr static_queue()
            : buffer_{}
            , size_{0}
        {}

        constexpr auto front() const noexcept
        {
            return buffer_[0];
        }

        constexpr auto back() const noexcept
        {
            return buffer_[size_-1];
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
                , "static_queue already full");
            
            size_ += 1;
            buffer_[size_-1] = t;
        }

        constexpr auto pop()
        {
            size_ -= 1;
            auto res = buffer_[0];
            // simply move all elements
            for (nm_size_t i=0; i<(nm_size_t)size_; i++) {
                buffer_[i] = buffer_[i+1];
            }
            return res;
        }
    };
}

#endif // NMTOOLS_UTL_STATIC_QUEUE_HPP