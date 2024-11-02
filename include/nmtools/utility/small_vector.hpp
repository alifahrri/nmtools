#ifndef NMTOOLS_UTILITY_SMALL_VECTOR_HPP
#define NMTOOLS_UTILITY_SMALL_VECTOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/stl.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/utility/get.hpp"
#include "nmtools/utility/get_if.hpp"
#include "nmtools/utility/shape.hpp"

#ifndef NMTOOLS_SMALL_VECTOR_DEFAULT_DIM
#define NMTOOLS_SMALL_VECTOR_DEFAULT_DIM 6
#endif

namespace nmtools
{
    template <typename T, auto DIM=NMTOOLS_SMALL_VECTOR_DEFAULT_DIM
        , template<typename...>typename either_t=nmtools_either
        , template<typename,auto>typename static_vector_t=nmtools_static_vector
        , template<typename...>typename vector_t=nmtools_list
    >
    struct small_vector
    {
        using static_vector_type = static_vector_t<T,DIM>;
        using vector_type = vector_t<T>;
        using either_type = either_t<static_vector_type,vector_type>;

        using value_type = T;
        using pointer    = T*;
        using reference  = T&;
        using size_type  = nm_size_t;
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

            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                static_ptr->resize(N);
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                vector_ptr->resize(N);
            }
        }

        template <typename A, typename B, typename...Ts>
        small_vector(const A& t, const B& u, const Ts&...ts)
        {
            constexpr auto n = sizeof...(Ts) + 2;
            resize(n);
            const auto& tuple = nmtools_tuple{t,u,ts...};
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                at(i) = nmtools::get<i>(tuple);
            });
        }

        void resize(size_type new_size)
        {
            auto prev_size = size();
            if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                if (new_size <= DIM) {
                    static_ptr->resize(new_size);
                } else {
                    // dumb copy
                    auto new_buffer = small_vector(new_size);
                    for (size_type i=0; i<(size_type)prev_size; i++) {
                        new_buffer.at(i) = static_ptr->at(i);
                    }
                    new_buffer.resize(new_size);
                    buffer_ = new_buffer.buffer_;
                }
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                vector_ptr->resize(new_size);
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

        auto push_back(const T& t)
        {
            auto old_size = size();
            if (old_size == DIM) {
                resize(old_size+1);
                at(old_size) = t;
            } else if (auto static_ptr = nmtools::get_if<static_vector_type>(&buffer_)) {
                return static_ptr->push_back(t);
            } else {
                auto vector_ptr = nmtools::get_if<vector_type>(&buffer_);
                return vector_ptr->push_back(t);
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
    }; // small_vector

    // NOTE: use additional U to not confusing with single arg constructor
    // TODO: fix initialization
    template <typename T, typename U, typename...Ts>
    small_vector(const T&, const U&, const Ts&...) -> small_vector<meta::common_type_t<T,U,Ts...>,sizeof...(Ts)+2>;

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
} // namespace nmtools

namespace nmtools::impl
{
    template <typename T, auto DIM>
    struct len_t<small_vector<T,DIM>>
    {
        using array = small_vector<T,DIM>;
        using const_array = const array&;
        using type  = typename array::size_type;

        constexpr type operator()(const_array a) const noexcept
        {
            return a.size();
        }
    };
}

namespace nmtools::meta
{
    template <typename T, auto DIM>
    struct is_dynamic_index_array<small_vector<T,DIM>>
    {
        static constexpr auto value = is_index_v<T>;
    };

    template <typename T, auto DIM>
    struct is_ndarray<small_vector<T,DIM>> : is_num<T> {};

    template <typename T, auto DIM>
    struct is_list<small_vector<T,DIM>> : true_type {};
}

#endif // NMTOOLS_UTILITY_SMALL_VECTOR_HPP