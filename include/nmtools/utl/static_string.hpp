#ifndef NMTOOLS_UTL_STATIC_STRING_HPP
#define NMTOOLS_UTL_STATIC_STRING_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"
#include "nmtools/meta/bits/traits/is_string.hpp"
#include "nmtools/meta/bits/traits/is_nullable_num.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/max_len.hpp"

#ifndef NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE
#define NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE (128)
#endif // NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE

namespace nmtools::utl
{
    template <nm_size_t Capacity=NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE, typename T=char>
    struct static_string_base : static_vector<T,Capacity>
    {
        using base_type = static_vector<T,Capacity>;
        using size_type = nm_size_t;
        static constexpr auto npos = size_type(-1);
        static constexpr auto capacity = Capacity;

        constexpr static_string_base() = default;

        template <auto N>
        constexpr static_string_base(const T(&other)[N])
            : base_type([&](){
                base_type base;
                base.resize(N);
                for (nm_size_t i=0; i<N; i++) {
                    base[i] = other[i];
                }
                return base;
            }())
        {}

        template <typename num_t, enable_if_t<is_integer_v<num_t> || is_integral_constant_v<num_t>,int> = 0 >
        static constexpr auto to_string(num_t num)
        {
            static_string_base result;
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
            // TODO: use proper type
            nm_index_t m_num = is_negative ? (nm_index_t)-num : (nm_index_t)num;
            static_string_base tmp;
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

        template <typename array_t, enable_if_t<(max_len_v<array_t> > 0),int> = 0>
        static constexpr auto to_string(const array_t& a, const static_string_base& separator=static_string_base(","))
        {
            constexpr auto N = max_len_v<array_t>;
            auto strings = static_vector<static_string_base,N>{};
            if constexpr (is_tuple_v<array_t>) {
                template_for<N>([&](auto I){
                    constexpr auto i = decltype(I)::value;
                    strings.push_back(to_string(nmtools::get<i>(a)));
                });
            } else {
                for (nm_size_t i=0; i<(nm_size_t)N; i++) {
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
            return static_string_base("None");
        }

        static constexpr auto to_string(ellipsis_t)
        {
            return static_string_base("...");
        }

        template <nm_size_t OtherCapacity>
        constexpr static_string_base(const static_string_base<OtherCapacity,T>& other)
            : base_type([&](){
                base_type base;
                auto N = (Capacity < other.size() ? Capacity : other.size());
                if (Capacity < other.size()) {
                    nmtools_panic( (Capacity < other.size())
                        , "invalid construction of static_string from another static string" );
                }
                base.resize(N);
                for (nm_size_t i=0; i<N; i++) {
                    base[i] = other[i];
                }
                return base;
            }())
        {}

        template <nm_size_t OtherCapacity>
        constexpr static_string_base(const static_vector<T,OtherCapacity>& other)
            : base_type(other)
        {}

        template <typename...Ts>
        constexpr static_string_base(Ts...ts)
            : base_type(ts...)
        {}

        constexpr auto base() const
        {
            return static_cast<base_type>(*this);
        }

        constexpr auto c_str() const
        {
            return this->data();
        }

        template <typename str_list_t>
        constexpr auto join(const str_list_t& str_list) const noexcept
        {
            // TODO: customizeable capacity
            static_string_base result;

            auto insert_str = [&](const auto& str){
                for (nm_size_t i=0; i<str.size()-1; i++) {
                    result.push_back(str.at(i));
                }
            };

            if (str_list.size() == 0) {
                return result;
            } else {
                insert_str(str_list.at(0));
                for (nm_size_t i=1; i<(nm_size_t)str_list.size(); i++) {
                    insert_str(*this);
                    insert_str(str_list.at(i));
                }
                result.push_back('\0');
                return result;
            }
        }

        template <auto N>
        constexpr decltype(auto) operator=(const T (&other)[N])
        {
            // TODO: error handling, parametrize should assert or truncate
            this->resize(N);
            for (nm_size_t i=0; i<(nm_size_t)N; i++) {
                this->at(i) = other[i];
            }
            return *this;
        }

        template <auto N>
        constexpr auto operator==(const T (&other)[N]) const
        {
            auto init = this->size() == N;
            for (nm_size_t i=0; (i<(nm_size_t)N) && (init); i++) {
                init = init && (this->at(i) == other[i]);
            }
            return init;
        }

        template <nm_size_t OtherCapacity>
        constexpr auto operator==(const static_string_base<OtherCapacity,T>& other) const
        {
            auto init = this->size() == other.size();
            auto N = this->size();
            for (nm_size_t i=0; (i<(nm_size_t)N) && (init); i++) {
                init = init && (this->at(i) == other.at(i));
            }
            return init;
        }

        template <auto N>
        constexpr auto operator+(const T (&other)[N]) const
        {
            using result_t = static_string_base<Capacity+N>;

            auto result = result_t {};

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

        template <nm_size_t OtherCapacity>
        constexpr auto operator+(const static_string_base<OtherCapacity,T>& other) const
        {
            using result_t = static_string_base<Capacity+OtherCapacity>;

            auto result = result_t {};

            nm_index_t size = this->size();
            size = (size == 0 ? 0 : size - 1);
            for (nm_size_t i=0; i<(nm_size_t)size; i++) {
                result.push_back(this->at(i));
            }
            auto N = other.size();
            for (nm_size_t i=0; i<(nm_size_t)N; i++) {
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
        constexpr auto operator+=(const static_string_base<OtherCapacity,T>& other)
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
            auto substring = static_string_base{};
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
        constexpr auto find(const T (&other)[N]) const
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

        template <auto N>
        constexpr auto rfind(const T (&other)[N]) const
        {
            auto result = npos;

            auto idx = 0;
            T to_find = other[idx++];
            for (nm_index_t i=this->size()-1; i>=0; i--) {
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

        constexpr auto count(const T to_find) const
        {
            auto c = 0;
            for (nm_size_t i=0; i<this->size(); i++) {
                auto chr = this->at(i);
                if (chr == to_find) {
                    c++;
                }
            }
            return c;
        }

        constexpr auto split(const T separator) const
        {
            using result_t = static_vector<static_string_base,Capacity>;

            auto result = result_t {};

            auto r_idx = 0;
            result.push_back(static_string_base{});
            for (nm_size_t i=0; i<this->size(); i++) {
                auto chr = this->at(i);
                if (chr == separator) {
                    result[r_idx].push_back('\0');
                    result.push_back(static_string_base{});
                    r_idx++;
                    continue;
                }
                result[r_idx].push_back(chr);
            }

            return result;
        }
    };

    using static_string = static_string_base<>;

    template <nm_size_t Capacity, typename T>
    constexpr auto stoi(const static_string_base<Capacity,T>& str)
    {
        // quick hack
        // size may include '\0'
        nm_index_t result = {};
        auto sign = 1;
        if (str.size() > 1) {
            // TODO: fully implement stoi
            auto s = str[0];
            if (s == '-') {
                sign = -1;
                s = str[1];
            }
            if (!(s >= '0' && s <= '9')) {
                nmtools_panic( false
                    , "invalid string for stoi" );
            }
            result = s - '0';
        } else {
            nmtools_panic( false
                , "invalid string for stoi" );
        }
        return result * sign;
    }

    template <typename T=static_string_base<NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE,char>>
    constexpr auto to_string(nm_index_t num)
    {
        T result;
        auto condition = (num >= 0 && num <= 99);
        if (condition) {
            auto b = 10;
            if (num/b) {
                result.push_back('0'+(num/b));
            }
            result.push_back('0'+(num%b));
            result.push_back('\0');
        } else {
            nmtools_panic( false
                , "invalid to_string" );
        }
        return result;
    }
} // namespace nmtools::utl

namespace nmtools::meta
{
    template <nm_size_t Capacity, typename T>
    struct is_string<utl::static_string_base<Capacity,T>> : true_type {};
}

#if __has_include(<iostream>)
#include <iostream>

template <nm_size_t Capacity, typename T>
std::ostream& operator << (std::ostream& os, const nmtools::utl::static_string_base<Capacity,T>& string)
{
    os << string.c_str();
    return os;
}

#endif // <iostream>

#endif // NMTOOLS_UTL_STATIC_STRING_HPP