#ifndef NMTOOLS_UTL_STRING_HPP
#define NMTOOLS_UTL_STRING_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/either.hpp"
#include "nmtools/utl/vector.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_size.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_string.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"
#include "nmtools/meta/bits/transform/max_len.hpp"

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

        template <typename num_t, enable_if_t<is_integer_v<num_t>,int> = 0>
        static auto to_string(num_t num)
        {
            string_base result;
            if (is_nullable_num_v<num_t> && !static_cast<bool>(num)) {
                result = "?";
                return result;
            }
            if (num == 0) {
                result.push_back('0');
                result.push_back('\0');
                return result;
            }
            auto is_negative = (num < 0);
            // assume integer for now
            nm_index_t m_num = is_negative ? (nm_index_t)-num : (nm_index_t)num;
            string_base tmp;
            while (m_num > 0) {
                auto digit = m_num % 10;
                tmp.push_back(digit + '0');
                m_num = m_num / 10;
            }
            if (is_negative) {
                result.push_back('-');
            }
            auto n_digits = tmp.size();
            auto offset = is_negative ? 1 : 0;
            result.resize(result.size()+n_digits);
            for (nm_size_t i=0; i<n_digits; i++) {
                result[i+offset] = tmp[n_digits-i-1];
            }
            result.push_back('\0');
            return result;
        }

        template <typename array_t, enable_if_t<(has_size_v<array_t> > 0),int> = 0>
        static constexpr auto to_string(const array_t& a, const string_base& separator=string_base(","))
        {
            constexpr nm_index_t N = max_len_v<array_t>;
            // TODO: add utl::small_vector?
            using strings_t  = conditional_t<(N > 0)
                , utl::static_vector<string_base,(N > 0 ? N : 1)>
                , utl::vector<string_base>>;
            auto strings = strings_t{};
            if constexpr (is_tuple_v<array_t>) {
                template_for<N>([&](auto I){
                    constexpr auto i = decltype(I)::value;
                    strings.push_back(to_string(nmtools::get<i>(a)));
                });
            } else {
                for (nm_size_t i=0; i<(nm_size_t)a.size(); i++) {
                    strings.push_back(to_string(a[i]));
                }
            }
            auto result = separator.join(strings);
            result.insert(0,"{");
            result += "}";
            return result;
        }

        static constexpr auto to_string(none_t)
        {
            return string_base("None");
        }

        static constexpr auto to_string(ellipsis_t)
        {
            return string_base("...");
        }

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

        // TODO: parametrize Capacity
        string_base& operator=(const string_base& other)
        {
            this->buffer_ = other.buffer_;
            return *this;
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

        template <typename str_list_t>
        constexpr auto join(const str_list_t& str_list) const noexcept
        {
            // TODO: customizeable capacity
            string_base result;

            auto insert_str = [&](const auto& str){
                for (nm_size_t i=0; i<str.size()-1; i++) {
                    result.push_back(str.at(i));
                }
            };

            if (str_list.size() == 0) {
                return result;
            } else {
                insert_str(str_list.at(0));
                for (nm_size_t i=1; i<str_list.size(); i++) {
                    insert_str(*this);
                    insert_str(str_list.at(i));
                }
                result.push_back('\0');
                return result;
            }
        }

        auto c_str() const
        {
            return this->data();
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

        template <nm_size_t OtherCapacity>
        constexpr auto operator+=(const string_base<OtherCapacity,T>& other)
        {
            auto N = other.size();
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
            count = (count == npos ? this->size() - pos : count);
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
} // namespace nmtools::utl

namespace nmtools::meta
{
    template <nm_size_t Capacity, typename T>
    struct is_string<utl::string_base<Capacity,T>> : true_type {};
}

#if __has_include(<iostream>)
#include <iostream>

template <nm_size_t Capacity, typename T>
std::ostream& operator << (std::ostream& os, const nmtools::utl::string_base<Capacity,T>& string)
{
    os << string.c_str();
    return os;
}

#endif // <iostream>

#endif // NMTOOLS_UTL_STRING_HPP