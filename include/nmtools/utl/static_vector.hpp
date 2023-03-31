#ifndef NMTOOLS_UTL_STATIC_VECTOR_HPP
#define NMTOOLS_UTL_STATIC_VECTOR_HPP

#include "nmtools/def.hpp"

// poor man's static_vector,
// very simple and minimalistic implementation of static_vector

#ifndef NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE
#define NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE 8
#endif // NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE

namespace nmtools::utl
{
    /**
     * @brief Poor man's static_vector type.
     * 
     * This structure doesn't aim to be fully STL-compatible,
     * only subset of that is used in nmtools.
     * 
     * @tparam T 
     * @tparam Capacity 
     */
    template <typename T, size_t Capacity=NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE>
    struct static_vector
    {
        using buffertype = T[Capacity];
        using value_type  = T;
        using pointer     = T*;
        using reference   = T&;
        using size_type   = size_t;
        using const_pointer   = const T*;
        using const_reference = const T&;

        protected:
        T buffer[Capacity];
        size_type size_ = 0;

        // NOTE: broken on c++4opencl error: conflicting types for 'begin'
        #if 0
        template <typename type, size_t M> friend constexpr auto begin(static_vector<type,M>&);
        template <typename type, size_t M> friend constexpr auto begin(const static_vector<type,M>&);
        template <typename type, size_t M> friend constexpr auto end(static_vector<type,M>&);
        template <typename type, size_t M> friend constexpr auto end(const static_vector<type,M>&);
        #endif

        public:
        static_vector() {}
        static_vector(size_type n)
        {
            resize(n);
        }
        static_vector(const static_vector& other)
        {
            resize(other.size_);
            // dumb copy
            for (size_type i=0; i<size_; i++) {
                buffer[i] = other.buffer[i];
            }
        }

        void resize(size_type new_size)
        {
            // TODO: assert/throw
            if (new_size <= Capacity)
                size_ = new_size;
        }

        static_vector& operator=(const static_vector& other)
        {
            resize(other.size_);
            // dumb copy
            for (size_type i=0; i<size_; i++) {
                buffer[i] = other.buffer[i];
            }
            return *this;
        }

        void push_back(const T& t)
        {
            if (size_+1 > Capacity) {
                return;
            }
            resize(size_ + 1);
            buffer[size_-1] = t;
        }

        const T* data() const
        {
            return buffer;
        }

        T* data()
        {
            return buffer;
        }

        constexpr reference at(size_t i)
        {
            // TODO: assert/throw
            return buffer[i];
        }

        constexpr const_reference at(size_t i) const
        {
            // TODO: assert/throw
            return buffer[i];
        }

        constexpr auto size() const noexcept
        {
            return size_;
        }

        constexpr reference operator[](size_t i) noexcept
        {
            return buffer[i];
        }

        constexpr const_reference operator[](size_t i) const noexcept
        {
            return buffer[i];
        }

        template <size_t I>
        constexpr reference get()
        {
            static_assert( I<Capacity );
            return buffer[I];
        }

        template <size_t I>
        constexpr const_reference get() const
        {
            static_assert( I<Capacity );
            return buffer[I];
        }
    };

    template <typename T, size_t Capacity>
    constexpr auto size(const static_vector<T,Capacity>& a)
    {
        return a.size();
    }

    template <typename T, size_t Capacity>
    constexpr auto begin(const static_vector<T,Capacity>& a)
    {
        return a.data();
    }

    template <typename T, size_t Capacity>
    constexpr auto begin(static_vector<T,Capacity>& a)
    {
        return a.data();
    }

    template <typename T, size_t Capacity>
    constexpr auto end(const static_vector<T,Capacity>& a)
    {
        return a.data() + a.size();
    }

    template <typename T, size_t Capacity>
    constexpr auto end(static_vector<T,Capacity>& a)
    {
        return a.data() + a.size();
    }
} // namespace nmtools::utl

#endif // NMTOOLS_UTL_STATIC_VECTOR_HPP