#ifndef NMTOOLS_UTL_SMALL_VECTOR_HPP
#define NMTOOLS_UTL_SMALL_VECTOR_HPP

#include "nmtools/def.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/variant.hpp"
#include "nmtools/utl/vector.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/tuple.hpp"
#include "nmtools/meta/loop.hpp"
#include "nmtools/meta/bits/transform/common_type.hpp"

#ifndef NMTOOLS_SMALL_VECTOR_DEFAULT_DIM
#define NMTOOLS_SMALL_VECTOR_DEFAULT_DIM 6
#endif

namespace nmtools::utl
{
    // small vector that stores its elements in a static (stack) buffer
    // as long as size does not exceed DIM,
    // falls back to a dynamically allocated vector when growing beyond DIM
    template <typename T, auto DIM=NMTOOLS_SMALL_VECTOR_DEFAULT_DIM>
    struct small_vector
    {
        using static_vector_type = utl::static_vector<T,DIM>;
        using vector_type = utl::vector<T>;
        using either_type = variant<static_vector_type,vector_type>;

        using value_type = T;
        using pointer    = T*;
        using reference  = T&;
        using size_type  = nm_utl_size_t;
        using const_pointer   = const T*;
        using const_reference = const T&;

        protected:
        either_type buffer_ = {};

        public:

        small_vector() {}

        small_vector(size_type N)
        {
            if (N < DIM) {
                buffer_ = static_vector_type{};
            } else {
                buffer_ = vector_type{};
            }

            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                static_ptr->resize(N);
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                vector_ptr->resize(N);
            }
        }

        template <typename A, typename B, typename...Ts>
        small_vector(const A& t, const B& u, const Ts&...ts)
        {
            constexpr auto n = sizeof...(Ts) + 2;
            resize(n);
            const auto& tuple = utl::tuple{t,u,ts...};
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                at(i) = utl::get<i>(tuple);
            });
        }

        void resize(size_type new_size)
        {
            auto prev_size = size();
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                if (new_size <= DIM) {
                    static_ptr->resize(new_size);
                } else {
                    // dumb copy
                    auto new_buffer = small_vector(new_size);
                    for (size_type i=0; i<(size_type)prev_size; i++) {
                        new_buffer.at(i) = static_ptr->at(i);
                    }
                    buffer_ = new_buffer.buffer_;
                }
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                vector_ptr->resize(new_size);
            }
        }

        auto size() const noexcept
        {
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                return static_ptr->size();
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                return vector_ptr->size();
            }
        }

        void push_back(const T& t)
        {
            auto old_size = size();
            if (old_size == DIM) {
                resize(old_size+1);
                at(old_size) = t;
            } else if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                static_ptr->push_back(t);
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                vector_ptr->push_back(t);
            }
        }

        reference at(size_type i)
        {
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                return static_ptr->at(i);
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                return vector_ptr->at(i);
            }
        }

        const_reference at(size_type i) const
        {
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                return static_ptr->at(i);
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                return vector_ptr->at(i);
            }
        }

        pointer data()
        {
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                return static_ptr->data();
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                return vector_ptr->data();
            }
        }

        const_pointer data() const
        {
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                return static_ptr->data();
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                return vector_ptr->data();
            }
        }

        reference operator[](size_type i)
        {
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                return (*static_ptr)[i];
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                return (*vector_ptr)[i];
            }
        }

        const_reference operator[](size_type i) const
        {
            if (auto static_ptr = buffer_.template get_if<static_vector_type>()) {
                return (*static_ptr)[i];
            } else {
                auto vector_ptr = buffer_.template get_if<vector_type>();
                return (*vector_ptr)[i];
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
            auto static_ptr = buffer_.template get_if<static_vector_type>();
            return static_cast<bool>(static_ptr);
        }
    }; // small_vector

    // NOTE: use additional U to not confusing with single arg constructor
    template <typename T, typename U, typename...Ts>
    small_vector(const T&, const U&, const Ts&...) -> small_vector<meta::common_type_t<T,U,Ts...>,sizeof...(Ts)+2>;

    // currently some index function use free function "size", the following is to provide adl

    template <typename T, auto N>
    auto size(const small_vector<T,N>& v)
    {
        return v.size();
    }

    template <typename T, auto N>
    auto begin(const small_vector<T,N>& a)
    {
        return a.begin();
    }

    template <typename T, auto N>
    auto begin(small_vector<T,N>& a)
    {
        return a.begin();
    }

    template <typename T, auto N>
    auto end(const small_vector<T,N>& a)
    {
        return a.end();
    }

    template <typename T, auto N>
    auto end(small_vector<T,N>& a)
    {
        return a.end();
    }
} // namespace nmtools::utl

#endif // NMTOOLS_UTL_SMALL_VECTOR_HPP
