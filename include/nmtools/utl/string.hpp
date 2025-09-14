#ifndef NMTOOLS_UTL_STRING_HPP
#define NMTOOLS_UTL_STRING_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/either.hpp"
#include "nmtools/utl/vector.hpp"

#ifndef NMTOOLS_DEFAULT_STRING_STATIC_SIZE
#define NMTOOLS_DEFAULT_STRING_STATIC_SIZE (16)
#endif

namespace nmtools::utl
{
    template <nm_size_t Capacity=NMTOOLS_DEFAULT_STRING_STATIC_SIZE, typename T=char>
    struct string_base
    {
        using static_vector_type = utl::static_vector<T,Capacity>;
        using vector_type = utl::vector<T>;
        using either_type = utl::either<static_vector_type,vector_type>;

        using value_type = T;
        using pointer    = T*;
        using reference  = T&;
        using size_type  = nm_size_t;
        using const_pointer   = const T*;
        using const_reference = const T&;

        static constexpr auto npos = size_type(-1);

        protected:
        either_type buffer_ = {};

        public:

        string_base() {}

        template <auto N>
        string_base(const T(&other)[N])
        {
            if (N < Capacity) {
                buffer_ = static_vector_type();
            } else {
                buffer_ = vector_type();
            }

            auto fill = [&](auto ptr){
                for (nm_size_t i=0; i<N; i++) {
                    ptr->at(i) = other[i];
                }
            };

            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                static_ptr->resize(N);
                fill(static_ptr);
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                vector_ptr->resize(N);
                fill(vector_ptr);
            }
        }

        string_base(const string_base& other)
        {
            buffer_ = other.buffer_;
        }

        void resize(size_type new_size)
        {
            auto prev_size = size();
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                if (new_size <= Capacity) {
                    static_ptr->resize(new_size);
                } else {
                    static_vector_type tmp = *static_ptr;

                    // change type
                    buffer_ = either_type{vector_type()};
                    auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                    vector_ptr->resize(new_size);

                    auto dst_size = (prev_size < new_size ? prev_size : new_size);
                    for (size_type i=0; i<(size_type)dst_size; i++) {
                        vector_ptr->at(i) = tmp.at(i);
                    }
                }
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                vector_ptr->resize(new_size);
            }
        }

        auto push_back(const T& t)
        {
            auto old_size = size();
            if (old_size == Capacity) {
                resize(old_size+1);
                at(old_size) = t;
            } else if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return static_ptr->push_back(t);
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return vector_ptr->push_back(t);
            }
        }

        auto size() const noexcept
        {
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return static_ptr->size();
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return vector_ptr->size();
            }
        }

        reference at(size_type i)
        {
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return static_ptr->at(i);
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return vector_ptr->at(i);
            }
        }

        const_reference at(size_type i) const
        {
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return static_ptr->at(i);
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return vector_ptr->at(i);
            }
        }

        pointer data()
        {
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return static_ptr->data();
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return vector_ptr->data();
            }
        }

        const_reference operator[](size_type i) const
        {
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return (*static_ptr)[i];
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return (*vector_ptr)[i];
            }
        }

        reference operator[](size_type i)
        {
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return (*static_ptr)[i];
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return (*vector_ptr)[i];
            }
        }

        const_pointer data() const
        {
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return static_ptr->data();
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return vector_ptr->data();
            }
        }

        pointer begin()
        {
            return data();
        }

        const_pointer begin() const
        {
            return data();
        }

        pointer end()
        {
            return data() + size();
        }

        const_pointer end() const
        {
            return data() + size();
        }

        auto is_static()
        {
            auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_);
            return static_cast<bool>(static_ptr);
        }

        template <auto N>
        decltype(auto) operator=(const T (&other)[N])
        {
            this->resize(N);
            for (nm_size_t i=0; i<(nm_size_t)N; i++) {
                this->at(i) = other[i];
            }
            return *this;
        }

        template <auto N>
        auto operator==(const T (&other)[N]) const
        {
            auto init = this->size() == N;
            for (nm_size_t i=0; (i<(nm_size_t)N) && (init); i++) {
                init = init && (this->at(i) == other[i]);
            }
            return init;
        }

        template <auto N>
        auto operator+(const T (&other)[N]) const
        {
            auto result = string_base();

            nm_index_t size = this->size();
            size = (size == 0 ? 0 : size - 1);
            for (nm_size_t i=0; i<(nm_size_t)size; i++) {
                result.push_back(this->at(i));
            }
            for (nm_size_t i=0; i<N; i++) {
                result.push_back(other[i]);
            }

            return result;
        }

        template <auto N>
        constexpr decltype(auto) operator+=(const T (&other)[N])
        {
            nm_index_t init = this->size();
            init = (init == 0 ? 0 : init - 1);
            this->resize(init + N);
            for (nm_size_t i=0; i<N; i++) {
                this->at(init++) = other[i];
            }
            return *this;
        }

        constexpr auto substr(size_type pos, size_type count=npos) const
        {
            auto substring = string_base();
            count = (count = npos ? this->size() - pos : count);
            substring.resize(count);
            for (nm_size_t i=0; i<(nm_size_t)count; i++) {
                substring[i] = this->at(pos+i);
            }
            return substring;
        }

        template <auto N>
        constexpr decltype(auto) insert(size_type index, const T (&other)[N])
        {
            auto substr = this->substr(index);
            this->resize(this->size()+(N-1));
            for (nm_size_t i=0; i<N; i++) {
                this->at(index++) = other[i];
            }
            for (nm_size_t i=0; i<substr.size(); i++) {
                this->at((index-1)+i) = substr[i];
            }
            return *this;
        }

        template <auto N>
        constexpr auto find(const T (&other)[N])
        {
            auto result = npos;

            auto idx = 0;
            T to_find = other[idx++];
            for (nm_size_t i=0; i<this->size(); i++) {
                auto chr = this->at(i);
                if ((chr == to_find) && (result == npos)) {
                    result = i;
                    to_find = other[idx++];
                } else if (chr == to_find) {
                    to_find = other[idx++];
                } else {
                    result = npos;
                }
                if (idx == N) {
                    break;
                }
            }

            return result;
        }
    };

    using string = string_base<>;
}

#endif // NMTOOLS_UTL_STRING_HPP