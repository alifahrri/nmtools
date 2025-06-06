#ifndef NMTOOLS_UTL_QUEUE_HPP
#define NMTOOLS_UTL_QUEUE_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/vector.hpp"

namespace nmtools::utl
{
    template <typename T, typename allocator_t=nmtools_allocator<T>>
    struct queue
    {
        using buffer_type = utl::vector<T,allocator_t>;
        using size_type = nm_size_t;

        buffer_type buffer_;
        size_type size_;

        queue()
            : buffer_{}
            , size_{0}
        {}

        auto front() const noexcept
        {
            return buffer_[0];
        }

        auto back() const noexcept
        {
            return buffer_[size_-1];
        }

        auto size() const noexcept
        {
            return size_;
        }

        auto empty() const noexcept
        {
            return size_ == 0;
        }

        auto push(const T& t)
        {
            size_ += 1;
            buffer_.push_back(t);
        }

        auto pop()
        {
            // dumb implementation
            // TODO: optimize
            size_ -= 1;
            auto res = buffer_[0];
            auto new_buffer = buffer_type{};
            new_buffer.resize(size_);
            for (nm_size_t i=0; i<(nm_size_t)size_; i++) {
                new_buffer[i] = buffer_[i+1];
            }
            buffer_ = new_buffer;
            return res;
        }
    };
}

#endif // NMTOOLS_UTL_QUEUE_HPP