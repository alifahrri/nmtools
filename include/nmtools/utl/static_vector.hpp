#ifndef NMTOOLS_UTL_STATIC_VECTOR_HPP
#define NMTOOLS_UTL_STATIC_VECTOR_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/array.hpp"

// poor man's static_vector,
// very simple and minimalistic implementation of static_vector

#ifndef NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE
#define NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE 8
#endif // NMTOOLS_DEFAULT_STATIC_VECTOR_MAX_SIZE

namespace nmtools::utl
{
    // TODO: fix utl::static_vector with tuple on C++forOpenCL
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
        using buffer_type = utl::array<T,Capacity>;
        using value_type  = T;
        using pointer     = T*;
        using reference   = T&;
        using size_type   = nm_utl_size_t;
        // NOTE: to avoid invalid cast on c++ for opencl kernel compilation
        using index_type  = nm_utl_index_t;
        using const_pointer   = const T*;
        using const_reference = const T&;

        protected:
        buffer_type buffer = {};
        size_type size_ = 0;

        // NOTE: broken on c++4opencl error: conflicting types for 'begin'
        #if 0
        template <typename type, size_t M> friend constexpr auto begin(static_vector<type,M>&);
        template <typename type, size_t M> friend constexpr auto begin(const static_vector<type,M>&);
        template <typename type, size_t M> friend constexpr auto end(static_vector<type,M>&);
        template <typename type, size_t M> friend constexpr auto end(const static_vector<type,M>&);
        #endif

        public:
        constexpr static_vector()
        {}
        constexpr static_vector(size_type n)
            : size_(n)
        {}

        constexpr static_vector(const static_vector& other)
            : buffer(other.buffer)
            , size_(other.size_)
        {}

        constexpr void resize(size_type new_size)
        {
            // TODO: assert/throw
            if (new_size <= Capacity) {
                size_ = new_size;
            }
        }

        constexpr static_vector& operator=(const static_vector& other)
        {
            resize(other.size_);
            // dumb copy
            for (size_type i=0; i<size_; i++) {
                buffer[(index_type)i] = other.buffer[(index_type)i];
            }
            return *this;
        }

        constexpr void push_back(const T& t)
        {
            if (size_+1 > Capacity) {
                return;
            }
            resize(size_ + 1);
            buffer[index_type(size_-1)] = t;
        }

        constexpr const T* data() const
        {
            return buffer.data();
        }

        constexpr T* data()
        {
            return buffer.data();
        }

        nmtools_index_attribute
        constexpr reference at(index_type i)
        {
            // TODO: assert/throw
            return buffer[i];
        }

        nmtools_index_attribute
        constexpr const_reference at(index_type i) const
        {
            // TODO: assert/throw
            return buffer[i];
        }

        constexpr auto size() const noexcept
        {
            return size_;
        }

        nmtools_index_attribute
        constexpr reference operator[](index_type i) noexcept
        {
            return buffer[i];
        }

        nmtools_index_attribute
        constexpr const_reference operator[](index_type i) const noexcept
        {
            return buffer[i];
        }

        template <size_t I>
        constexpr reference get()
        {
            static_assert( I<Capacity );
            return buffer[(index_type)I];
        }

        template <size_t I>
        constexpr const_reference get() const
        {
            static_assert( I<Capacity );
            return buffer[(index_type)I];
        }
    }; // static_vector

    template <typename T, typename U, typename...Ts>
    nmtools_func_attribute
    static_vector(const T&, const U&, const Ts&...) -> static_vector<meta::common_type_t<T,U,Ts...>,sizeof...(Ts)+2>;

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