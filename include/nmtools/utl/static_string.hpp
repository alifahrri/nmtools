#ifndef NMTOOLS_UTL_STATIC_STRING_HPP
#define NMTOOLS_UTL_STATIC_STRING_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/static_vector.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_size.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"
#include "nmtools/meta/bits/traits/is_nullable_num.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_string.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/transform/max_len.hpp"
#include "nmtools/meta/bits/transform/numeric_limits.hpp"
#include "nmtools/utl/math.hpp"

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

        template <typename array_t, enable_if_t<(has_size_v<array_t> > 0),int> = 0>
        static constexpr auto to_string(const array_t& a, const static_string_base& separator=static_string_base(","))
        {
            constexpr nm_index_t N = max_len_v<array_t>;
            // use compile-time size if available, otherwise fallback to capacity
            constexpr nm_index_t num_strings = (N > 0 ? N : Capacity);
            auto strings = static_vector<static_string_base,num_strings>{};
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

        constexpr auto is_static() const
        {
            return true;
        }

        constexpr auto begin()
        {
            return this->data();
        }

        constexpr auto begin() const
        {
            return this->data();
        }

        constexpr auto end()
        {
            return this->data() + this->size();
        }

        constexpr auto end() const
        {
            return this->data() + this->size();
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

        template <nm_size_t OtherCapacity>
        constexpr auto find(const static_string_base<OtherCapacity,T>& other, size_type start=0) const
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

    template <typename T, nm_size_t Capacity, typename U>
    constexpr auto stoint(const static_string_base<Capacity,U>& str)
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
    constexpr auto stoi(const static_string_base<Capacity,T>& str)
    {
        return stoint<int32_t>(str);
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stoll(const static_string_base<Capacity,T>& str)
    {
        return stoint<int64_t>(str);
    }

    template <typename T, nm_size_t Capacity, typename U>
    constexpr auto stouint(const static_string_base<Capacity,U>& str)
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
    constexpr auto stoul(const static_string_base<Capacity,T>& str)
    {
        return stouint<uint32_t>(str);
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stoull(const static_string_base<Capacity,T>& str)
    {
        return stouint<uint64_t>(str);
    }

    template <typename T, nm_size_t Capacity, typename U>
    constexpr auto stofloat(const static_string_base<Capacity,U>& str)
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
    constexpr auto stof(const static_string_base<Capacity,T>& str)
    {
        return stofloat<float32_t>(str);
    }

    template <nm_size_t Capacity, typename T>
    constexpr auto stod(const static_string_base<Capacity,T>& str)
    {
        return stofloat<float64_t>(str);
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

    template <typename T, typename U>
    constexpr auto to_string_impl(U num)
    {
        // fixed-point formatting similar to std::to_string, with 6 decimal digits
        constexpr auto num_decimals = 6;
        constexpr auto scale = utl::pow(U(10), num_decimals);
        T result;
        // handle nan
        if (num != num) {
            result = "nan";
            return result;
        }
        // handle inf
        // note: meta::numeric_limits<U>::max() returns infinity for float/double
        if constexpr (sizeof(U) == sizeof(float)) {
            constexpr auto max_finite = (U)3.4028234663852886e38;
            if (num > max_finite) {
                result = "inf";
                return result;
            }
            if (num < -max_finite) {
                result = "-inf";
                return result;
            }
        } else {
            constexpr auto max_finite = (U)1.7976931348623157e308;
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
        auto use_scaled = (scaled < meta::numeric_limits<U>::max());
        auto int_part = (U)0;
        auto num_frac_digits = 0;
        if (use_scaled) {
            if (scaled < (U)9.2233720368547758e18) {
                // round half away from zero, safe below 2^63
                int_part = (U)(int64_t)(scaled + (U)0.5);
            } else {
                // too large for int64, but already integral
                int_part = scaled;
            }
            num_frac_digits = num_decimals;
        } else {
            int_part = num;
        }
        // extract digits of int_part, reversed
        T rev_digits;
        if (int_part == 0) {
            rev_digits.push_back('0');
        } else if (int_part < (U)9.2233720368547758e18) {
            auto m = (int64_t)int_part;
            while (m > 0) {
                rev_digits.push_back((char)('0' + (m % 10)));
                m /= 10;
            }
        } else {
            while (int_part > 0) {
                auto digit = utl::fmod(int_part, U(10));
                rev_digits.push_back((char)('0' + (nm_index_t)digit));
                int_part = (int_part - digit) / U(10);
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

    template <typename T=static_string_base<NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE,char>, typename num_t, enable_if_t<is_floating_point_v<num_t>,int> = 0>
    constexpr auto to_string(num_t num)
    {
        return to_string_impl<T>(num);
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