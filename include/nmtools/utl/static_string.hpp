#ifndef NMTOOLS_UTL_STATIC_STRING_HPP
#define NMTOOLS_UTL_STATIC_STRING_HPP

#include "nmtools/def.hpp"
#include "nmtools/platform.hpp"
#include "nmtools/utl/common.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/static_vector.hpp"

#ifndef NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE
#define NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE (64)
#endif // NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE

namespace nmtools::utl
{
    template <nm_size_t Capacity=NMTOOLS_DEFAULT_STATIC_STRING_MAX_SIZE, typename T=char>
    struct static_string_base : static_vector<T,Capacity>
    {
        using base_type = static_vector<T,Capacity>;
        using size_type = nm_size_t;
        static constexpr auto npos = size_type(-1);

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

        constexpr auto base() const
        {
            return static_cast<base_type>(*this);
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
            auto substring = static_string_base{};
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

    using static_string = static_string_base<>;
}

#endif // NMTOOLS_UTL_STATIC_STRING_HPP