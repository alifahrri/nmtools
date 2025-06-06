#ifndef NMTOOLS_UTL_STACK_HPP
#define NMTOOLS_UTL_STACK_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/vector.hpp"

namespace nmtools::utl
{
    template <typename T, typename allocator_t=nmtools_allocator<T>>
    struct stack
    {
        using buffer_type = utl::vector<T,allocator_t>;
        using size_type   = nm_size_t;

        buffer_type buffer_;
        size_type size_;

        stack()
            : buffer_{}
            , size_{0}
        {}

        const auto& top() const noexcept
        {
            auto idx = (nm_index_t)size_ - 1;
            idx = (idx > 0 ? idx : 0);
            return buffer_[idx];
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
            if (buffer_.size() < size_) {
                buffer_.push_back(t);
            } else {
                buffer_[size_-1] = t;
            }
        }

        auto pop()
        {
            size_ -= 1;
            auto res = buffer_[size_];
            return res;
        }
    };
}

#endif // NMTOOLS_UTL_STACK_HPP