// nvcc -x cu nvcc-1.cpp -I/workspace/nmtools/include/ -std=c++17 --gpu-architecture=sm_80
// clang -x cuda nvcc-1.cpp -I/workspace/nmtools/include/ -std=c++17 --cuda-gpu-arch=sm_80
#include <type_traits>
#include <array>

namespace testing
{
    template <typename T, auto Min, auto Max>
    struct clipped_integer_t
    {
        using value_type = T;

        static constexpr auto min = Min;
        static constexpr auto max = Max;

        static_assert( (min < max), "invalid value for Min and Max, expect Min < Max" );

        constexpr clipped_integer_t() {}

        constexpr clipped_integer_t(const clipped_integer_t& other)
            : value(other.value)
        {}

        constexpr clipped_integer_t(T other)
            : value(other > Max ? Max : (other < Min ? Min : other))
        {}

        constexpr operator T() const noexcept
        {
            return value;
        }

        constexpr clipped_integer_t& operator=(clipped_integer_t other)
        {
            // from same type with same Min Max
            value = other.value;

            return *this;
        }

        constexpr clipped_integer_t& operator=(T other)
        {
            *this = clipped_integer_t{other};

            return *this;
        }

        template <auto OtherMin, auto OtherMax>
        constexpr clipped_integer_t& operator=(clipped_integer_t<T,OtherMin,OtherMax> other)
        {
            *this = {(T)other};
            return *this;
        }

        template <typename U, auto OtherMin, auto OtherMax>
        constexpr clipped_integer_t& operator=(clipped_integer_t<U,OtherMin,OtherMax> other)
        {
            *this = {(T)other};
            return *this;
        }

        private:
        T value = Min;
    }; // clipped_integer_t

    template <typename>
    struct is_tuple : std::false_type {};

    template <typename ...Args>
    inline constexpr bool is_tuple_v = is_tuple<Args...>::value;

    namespace error
    {
        template <typename...>
        struct CLIPPED_MAX_UNSUPPORTED {};
    }

    template <typename T, typename=void>
    struct clipped_max
    {
        using type = error::CLIPPED_MAX_UNSUPPORTED<T>;
        static constexpr auto value = type{};
    }; // clipped_max

    template <typename T, auto Min, auto Max>
    struct clipped_max<
        clipped_integer_t<T,Min,Max>
    >
    {
        static constexpr auto value = Max;
    }; // clipped_max

    template <typename T>
    constexpr inline auto clipped_max_v = clipped_max<T>::value;

    template <template<typename...>typename Tuple, typename...Ts, auto...Min, auto...Max>
    struct clipped_max<
        Tuple<clipped_integer_t<Ts,Min,Max>...>,
        std::enable_if_t< is_tuple_v<Tuple<clipped_integer_t<Ts,Min,Max>...>> >
    >
    {
        using index_t = std::common_type_t<Ts...>;
        #if 1
        static constexpr auto value = std::array{index_t(Max)...};
        #else
        // This is the fix:
        static constexpr auto value = std::array<index_t,sizeof...(Max)>{Max...};
        #endif
    };
}

int main()
{
    return 0;
}