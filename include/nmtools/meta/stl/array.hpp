#ifndef NMTOOLS_META_STL_ARRAY_HPP
#define NMTOOLS_META_STL_ARRAY_HPP

#include "nmtools/meta/array.hpp"

namespace nmtools::meta
{
    // TODO: cleanup
    /**
     * @brief specialization of nested_array_size for type that has tuple_size and value_type.
     * 
     * @tparam T type tot check
     */
    template <typename T>
    struct nested_array_size<T
        , enable_if_t<has_tuple_size_v<T> && has_value_type_v<T>>
    > {
        static constexpr auto value = std::tuple_size_v<T>;
    }; // nested_array_size

    template <typename T, size_t N>
    struct len<std::array<T,N>>
    {
        static constexpr auto value = N;
    };

    template <typename...Ts>
    struct len<std::tuple<Ts...>>
    {
        static constexpr auto value = sizeof...(Ts);
    };

    // TODO: move to primary template
    template <typename T>
    struct fixed_ndarray_shape<T,enable_if_t<is_bounded_array_v<T>>>
    {
        static constexpr auto value = [](){
            constexpr auto rank = std::rank_v<T>;
            using array_t = typename make_array_type<size_t,rank>::type;
            auto shape = array_t{};
            template_for<rank>([&](auto index) {
                constexpr auto i = decltype(index)::value;
                constexpr auto n = std::extent_v<T,i>;
                shape[i] = n;
            });
            return shape;
        }();
        using value_type = decltype(value);
    };
} // namespace nmtools::meta

#endif 