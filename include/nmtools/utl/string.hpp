#ifndef NMTOOLS_UTL_STRING_HPP
#define NMTOOLS_UTL_STRING_HPP

#include "nmtools/def.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/utl/either.hpp"
#include "nmtools/utl/vector.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_size.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"
#include "nmtools/meta/bits/traits/is_string.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/conditional.hpp"
#include "nmtools/meta/bits/transform/max_len.hpp"
#include "nmtools/meta/bits/transform/numeric_limits.hpp"
#include "nmtools/utl/math.hpp"

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
        static constexpr auto capacity = Capacity;

        template <typename num_t, enable_if_t<is_integer_v<num_t> || is_integral_constant_v<num_t>,int> = 0>
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

        template <typename num_t, enable_if_t<is_floating_point_v<num_t>,int> = 0>
        static auto to_string(num_t num)
        {
            // fixed-point formatting similar to std::to_string, with 6 decimal digits
            constexpr auto num_decimals = 6;
            constexpr auto scale = utl::pow(num_t(10), num_decimals);
            string_base result;
            // handle nan
            if (num != num) {
                result = "nan";
                return result;
            }
            // handle inf
            // note: meta::numeric_limits<num_t>::max() returns infinity for float/double
            if constexpr (sizeof(num_t) == sizeof(float)) {
                constexpr auto max_finite = (num_t)3.4028234663852886e38;
                if (num > max_finite) {
                    result = "inf";
                    return result;
                }
                if (num < -max_finite) {
                    result = "-inf";
                    return result;
                }
            } else {
                constexpr auto max_finite = (num_t)1.7976931348623157e308;
                if (num > max_finite) {
                    result = "inf";
                    return result;
                }
                if (num < -max_finite) {
                    result = "-inf";
                    return result;
                }
            }
            // handle sign
            auto negative = (num < 0) || ((num == 0) && utl::signbit(num));
            if (negative) {
                num = -num;
            }
            // scaled value as integer units of 10^-6, rounded
            // fallback to integer-only when the scaled value would overflow
            auto scaled = num * scale;
            auto use_scaled = (scaled < meta::numeric_limits<num_t>::max());
            auto int_part = (num_t)0;
            auto num_frac_digits = 0;
            if (use_scaled) {
                if (scaled < (num_t)9.2233720368547758e18) {
                    // round half away from zero, safe below 2^63
                    int_part = (num_t)(int64_t)(scaled + (num_t)0.5);
                } else {
                    // too large for int64, but already integral
                    int_part = scaled;
                }
                num_frac_digits = num_decimals;
            } else {
                int_part = num;
            }
            // extract digits of int_part, reversed
            string_base rev_digits;
            if (int_part == 0) {
                rev_digits.push_back('0');
            } else if (int_part < (num_t)9.2233720368547758e18) {
                auto m = (int64_t)int_part;
                while (m > 0) {
                    rev_digits.push_back((char)('0' + (m % 10)));
                    m /= 10;
                }
            } else {
                while (int_part > 0) {
                    auto digit = utl::fmod(int_part, num_t(10));
                    rev_digits.push_back((char)('0' + (nm_index_t)digit));
                    int_part = (int_part - digit) / num_t(10);
                }
            }
            auto n_total = rev_digits.size();
            // number of integer digits
            auto n_int = (nm_index_t)n_total - num_frac_digits;
            if (negative) {
                result.push_back('-');
            }
            if (n_int <= 0) {
                // value < 1, print leading zero
                result.push_back('0');
                result.push_back('.');
                // pad leading fraction zeros
                for (nm_size_t i=0; i<((nm_size_t)num_frac_digits - n_total); i++) {
                    result.push_back('0');
                }
                for (nm_size_t i=0; i<n_total; i++) {
                    result.push_back(rev_digits[n_total-i-1]);
                }
            } else {
                // print integer digits
                for (nm_size_t i=0; i<(nm_size_t)n_int; i++) {
                    result.push_back(rev_digits[n_total-i-1]);
                }
                result.push_back('.');
                // print fraction digits from the least significant part
                for (nm_size_t i=0; i<(nm_size_t)num_frac_digits; i++) {
                    result.push_back(rev_digits[num_frac_digits-i-1]);
                }
                // pad remaining fraction zeros for the huge-magnitude path
                for (nm_size_t i=(nm_size_t)num_frac_digits; i<num_decimals; i++) {
                    result.push_back('0');
                }
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

        auto operator==(const string_base& other) const noexcept
        {
            auto init = this->size() == other.size();
            for (nm_size_t i=0; (i<(nm_size_t)other.size()) && init; i++) {
                init = init && (this->at(i) == other.at(i));
            }
            return init;
        }

        template <nm_size_t OtherCapacity>
        auto operator==(const string_base<OtherCapacity,T>& other) const noexcept
        {
            auto init = this->size() == other.size();
            auto N = this->size();
            for (nm_size_t i=0; (i<(nm_size_t)N) && init; i++) {
                init = init && (this->at(i) == other.at(i));
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

        template <nm_size_t OtherCapacity>
        auto operator+(const string_base<OtherCapacity,T>& other) const
        {
            using result_t = string_base<Capacity+OtherCapacity>;

            auto result = result_t{};

            nm_index_t size = this->size();
            size = (size == 0 ? 0 : size - 1);
            for (nm_size_t i=0; i<(nm_size_t)size; i++) {
                result.push_back(this->at(i));
            }
            auto N = other.size();
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

        constexpr decltype(auto) operator+=(const T &other)
        {
            if (this->size() <= 1) {
                this->resize(2);
                this->at(0) = other;
                this->at(1) = 0;
            } else {
                auto size = this->size();
                auto init = size - 1;
                this->resize(size+1);
                this->at(init) = other;
                this->at(init+1) = 0;
            }
            return *this;
        }

        template <nm_size_t OtherCapacity>
        constexpr auto operator+=(const string_base<OtherCapacity,T>& other)
        {
            auto N = other.size();
            nm_index_t size = this->size();
            nm_index_t init = (size == 0 ? 0 : size - 1);
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
        constexpr auto find(const T (&other)[N], size_type start=0) const
        {
            auto result = npos;

            auto idx = size_type{0};
            T to_find = other[idx++];
            for (nm_size_t i=start; i<this->size(); i++) {
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

        constexpr auto find(const string_base& other, size_type start=0) const
        {
            auto result = npos;

            auto N = other.size();
            auto idx = size_type{0};
            T to_find = other[idx++];
            for (nm_size_t i=start; i<this->size(); i++) {
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

            auto idx = size_type{0};
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
            using result_t = vector<string_base>;

            auto result = result_t {};

            auto r_idx = 0;
            result.push_back(string_base{});
            for (nm_size_t i=0; i<this->size(); i++) {
                auto chr = this->at(i);
                if (chr == separator) {
                    result[r_idx].push_back('\0');
                    result.push_back(string_base{});
                    r_idx++;
                    continue;
                }
                result[r_idx].push_back(chr);
            }

            return result;
        }
    };

    using string = string_base<>;

    template <typename T, nm_size_t Capacity, typename U>
    constexpr auto stoint(const string_base<Capacity,U>& str)
    {
        // similar to std::stoi, parses a signed integer
        // size may include '\0'
        auto sign = 1;
        auto n = str.size();
        auto i = (nm_size_t)0;
        // skip leading whitespace
        while ((i < (nm_size_t)n)
            && ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || (str[i] == '\r'))) {
            i++;
        }
        // handle sign
        if (i < (nm_size_t)n) {
            auto s = str[i];
            if (s == '-') {
                sign = -1;
                i++;
            } else if (s == '+') {
                i++;
            }
        }
        // accumulate as magnitude to detect overflow
        auto max_magnitude = (sign > 0)
            ? (uint64_t)meta::numeric_limits<T>::max()
            : (uint64_t)meta::numeric_limits<T>::max() + 1;
        uint64_t magnitude = 0;
        auto has_digit = false;
        for (; i < (nm_size_t)n; i++) {
            auto s = str[i];
            if ((s >= '0') && (s <= '9')) {
                auto digit = s - '0';
                if (magnitude > (max_magnitude - digit) / 10) {
                    nmtools_panic( false
                        , "invalid string for stoint" );
                }
                magnitude = magnitude * 10 + digit;
                has_digit = true;
            } else {
                // stop at first non-digit, similar to std::stoi
                break;
            }
        }
        if (!has_digit) {
            nmtools_panic( false
                , "invalid string for stoint" );
        }
        T result = 0;
        if (sign > 0) {
            result = (T)magnitude;
        } else if (magnitude == 0) {
            result = 0;
        } else {
            result = (T)(-(T)(magnitude - 1) - 1);
        }
        return result;
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stoi(const string_base<Capacity,T>& str)
    {
        return stoint<int32_t>(str);
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stoll(const string_base<Capacity,T>& str)
    {
        return stoint<int64_t>(str);
    }

    template <typename T, nm_size_t Capacity, typename U>
    constexpr auto stouint(const string_base<Capacity,U>& str)
    {
        // similar to std::stoul, parses an unsigned integer
        // size may include '\0'
        auto n = str.size();
        auto i = (nm_size_t)0;
        // skip leading whitespace
        while ((i < n)
            && ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || (str[i] == '\r'))) {
            i++;
        }
        // handle sign
        if (i < n) {
            auto s = str[i];
            if (s == '+') {
                i++;
            } else if (s == '-') {
                nmtools_panic( false
                    , "invalid string for stouint" );
            }
        }
        // accumulate as magnitude to detect overflow
        auto max_magnitude = (uint64_t)meta::numeric_limits<T>::max();
        uint64_t magnitude = 0;
        auto has_digit = false;
        for (; i < n; i++) {
            auto s = str[i];
            if ((s >= '0') && (s <= '9')) {
                auto digit = s - '0';
                if (magnitude > (max_magnitude - digit) / 10) {
                    nmtools_panic( false
                        , "invalid string for stouint" );
                }
                magnitude = magnitude * 10 + digit;
                has_digit = true;
            } else {
                // stop at first non-digit, similar to std::stoul
                break;
            }
        }
        if (!has_digit) {
            nmtools_panic( false
                , "invalid string for stouint" );
        }
        return (T)magnitude;
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stoul(const string_base<Capacity,T>& str)
    {
        return stouint<uint32_t>(str);
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stoull(const string_base<Capacity,T>& str)
    {
        return stouint<uint64_t>(str);
    }

    template <typename T, nm_size_t Capacity, typename U>
    constexpr auto stofloat(const string_base<Capacity,U>& str)
    {
        // similar to std::stof, parses a floating point number
        // size may include '\0'
        auto n = str.size();
        auto i = (nm_size_t)0;
        // skip leading whitespace
        while ((i < n)
            && ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || (str[i] == '\r'))) {
            i++;
        }
        // handle sign
        auto sign = T(1);
        if (i < n) {
            auto s = str[i];
            if (s == '-') {
                sign = -T(1);
                i++;
            } else if (s == '+') {
                i++;
            }
        }
        // accumulate digits into the target type to avoid integer overflow
        auto value = T(0);
        auto has_digit = false;
        auto seen_dot = false;
        nm_index_t frac_digits = 0;
        for (; i < n; i++) {
            auto s = str[i];
            if ((s >= '0') && (s <= '9')) {
                value = value * T(10) + T(s - '0');
                if (seen_dot) {
                    frac_digits++;
                }
                has_digit = true;
            } else if (s == '.') {
                if (seen_dot) {
                    // stop at second dot, similar to std::stof
                    break;
                }
                seen_dot = true;
            } else {
                // stop at first non-digit, similar to std::stof
                break;
            }
        }
        if (!has_digit) {
            nmtools_panic( false
                , "invalid string for stofloat" );
        }
        // handle exponent
        nm_index_t exp = 0;
        if (i < n && ((str[i] == 'e') || (str[i] == 'E'))) {
            i++;
            auto exp_sign = 1;
            if (i < n) {
                auto s = str[i];
                if (s == '-') {
                    exp_sign = -1;
                    i++;
                } else if (s == '+') {
                    i++;
                }
            }
            auto exp_has_digit = false;
            for (; i < n; i++) {
                auto s = str[i];
                if ((s >= '0') && (s <= '9')) {
                    exp = exp * 10 + (s - '0');
                    exp_has_digit = true;
                } else {
                    break;
                }
            }
            if (!exp_has_digit) {
                nmtools_panic( false
                    , "invalid string for stofloat" );
            }
            exp *= exp_sign;
        }
        // combine value with 10^(exp - frac_digits)
        // NOTE: for large negative exponent (e.g. 1e-40f), pow(10,k) may overflow to inf,
        // so the result rounds to zero instead of a subnormal value.
        auto scale = exp - frac_digits;
        if (scale >= 0) {
            value = value * utl::pow(T(10), (nm_size_t)scale);
        } else {
            value = value / utl::pow(T(10), (nm_size_t)(-scale));
        }
        return sign * value;
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stof(const string_base<Capacity,T>& str)
    {
        return stofloat<float32_t>(str);
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stod(const string_base<Capacity,T>& str)
    {
        return stofloat<float64_t>(str);
    }
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