#ifndef NMTOOLS_UTL_VECTOR_HPP
#define NMTOOLS_UTL_VECTOR_HPP

// poor man's vector
// very simple, dumb implementation of vector, 
// not intended to match stl's vector, only inside nmtools usage
// may only handle numeric data type

#include "nmtools/meta/common.hpp"
// for variadic constructor
#include "nmtools/utl/tuple.hpp"
#include "nmtools/meta/loop.hpp"
#include "nmtools/meta/bits/transform/common_type.hpp"

namespace nmtools::error
{
    // dummy

    inline void no_calloc(size_t,size_t) {}

    inline void no_malloc(size_t) {}

    inline void no_realloc(void*,size_t) {}

    inline void no_free(void*) {}
} // namespace nmtools::error

#if __has_include(<malloc.h>)

#include <malloc.h>

#ifndef nmtools_calloc
#define nmtools_calloc ::calloc
#endif

#ifndef nmtools_malloc
#define nmtools_malloc ::malloc
#endif

#ifndef nmtools_realloc
#define nmtools_realloc ::realloc
#endif

#ifndef nmtools_free
#define nmtools_free ::free
#endif

#else // __has_include(<malloc.h>)

#ifndef nmtools_malloc
#define nmtools_malloc ::nmtools::error::no_calloc
#endif

#ifndef nmtools_malloc
#define nmtools_malloc ::nmtools::error::no_malloc
#endif

#ifndef nmtools_realloc
#define nmtools_realloc ::nmtools::error::no_realloc
#endif

#ifndef nmtools_free
#define nmtools_free ::nmtools::error::no_free
#endif

#endif

namespace nmtools::utl
{
    // dumb allocator
    template <typename T>
    struct allocator
    {
        using pointer   = T*;
        using size_type = size_t;

        static pointer allocate(size_type N)
        {
            #if 1
            return static_cast<pointer>(nmtools_malloc(sizeof(T) * N));
            #else
            return static_cast<pointer>(nmtools_calloc(N,sizeof(T)));
            #endif
        }

        static pointer realloc(pointer ptr, size_type new_size)
        {
            return static_cast<pointer>(nmtools_realloc(ptr,sizeof(T) * new_size));
        }

        static void free(pointer ptr)
        {
            nmtools_free(ptr);
        }
    };
} // namespace nmtools::utl

#ifndef nmtools_allocator
#define nmtools_allocator ::nmtools::utl::allocator
#endif

namespace nmtools::utl
{
    template <typename T, typename allocator_t=nmtools_allocator<T>>
    struct vector
    {
        using value_type  = T;
        using pointer     = T*;
        using reference   = T&;
        using size_type   = size_t;
        using allocator_type  = allocator_t;
        using const_pointer   = const T*;
        using const_reference = const T&;

        protected:
        pointer buffer_ = NULL;
        size_type size_ = 0;
        size_type buffer_size_ = 0;
        allocator_type allocator = {};

        template <typename type, typename allocator_type> friend auto begin(vector<type,allocator_type>&);
        template <typename type, typename allocator_type> friend auto begin(const vector<type,allocator_type>&);
        template <typename type, typename allocator_type> friend auto end(vector<type,allocator_type>&);
        template <typename type, typename allocator_type> friend auto end(const vector<type,allocator_type>&);

        public:

        vector() {}
        vector(size_type N)
        {
            resize(N);
        }
        vector(const vector& other)
        {
            resize(other.size_);
            // dumb copy
            for (size_type i=0; i<size_; i++) {
                buffer_[i] = other.buffer_[i];
            }
        }
        ~vector()
        {
            allocator.free(buffer_);
        }
        // NOTE: use additional U to not confusing with single arg constructor
        // TODO: fix initialization
        template <typename A, typename B, typename...Ts>
        vector(const A& t, const B& u, const Ts&...ts)
        {
            constexpr auto n = sizeof...(Ts) + 2;
            resize(n);
            const auto& tuple = utl::tuple{t,u,ts...};
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                at(i) = utl::get<i>(tuple);
            });
        }

        vector& operator=(const vector& other)
        {
            resize(other.size_);
            // dumb copy
            for (size_type i=0; i<size_; i++) {
                buffer_[i] = other.buffer_[i];
            }
            return *this;
        }

        void resize(size_type new_size)
        {
            size_ = new_size;
            if (buffer_size_ < new_size) {
                buffer_size_ = new_size;
                // TODO: error handling
                buffer_ = allocator.realloc(buffer_,buffer_size_);
            } else {
                // not invalidating the value, for now
            }
        }

        void push_back(const T& t)
        {
            if (buffer_size_ < (size_ + 1)) {
                resize(size_ + 1);
            } else {
                size_ = size_ + 1;
            }
            buffer_[size_-1] = t;
        }

        reference at(size_type i)
        {
            // TODO: assert/throw
            return buffer_[i];
        }

        const_reference at(size_type i) const
        {
            return buffer_[i];
        }

        auto size() const noexcept
        {
            return size_;
        }

        reference operator[](size_type i) noexcept
        {
            return buffer_[i];
        }

        const_reference operator[](size_type i) const noexcept
        {
            return buffer_[i];
        }

        pointer data()
        {
            return buffer_;
        }

        const_pointer data() const
        {
            return buffer_;
        }

        const_pointer begin() const
        {
            return buffer_;
        }

        pointer begin()
        {
            return buffer_;
        }

        const_pointer end() const
        {
            return buffer_ + size_;
        }

        pointer end()
        {
            return buffer_ + size_;
        }
    }; // vector

    // NOTE: use additional U to not confusing with single arg constructor
    // TODO: fix initialization
    template <typename T, typename U, typename...Ts>
    vector(const T&, const U&, const Ts&...) -> vector<meta::common_type_t<T,U,Ts...>>;

    // currently some index function use free function "size", the following is to provide adl

    template <typename T, typename allocator_t>
    auto size(const vector<T,allocator_t>& v)
    {
        return v.size();
    }

    template <typename T, typename allocator_t>
    auto begin(const vector<T,allocator_t>& a)
    {
        return a.buffer_;
    }

    template <typename T, typename allocator_t>
    auto begin(vector<T,allocator_t>& a)
    {
        return a.buffer_;
    }

    template <typename T, typename allocator_t>
    auto end(const vector<T,allocator_t>& a)
    {
        return a.buffer_ + a.size_;
    }

    template <typename T, typename allocator_t>
    auto end(vector<T,allocator_t>& a)
    {
        return a.buffer_ + a.size_;
    }
} // namespace nmtools::utl


#endif // NMTOOLS_UTL_VECTOR_HPP