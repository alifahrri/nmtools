#ifndef NMTOOLS_META_STL_ARRAY_HPP
#define NMTOOLS_META_STL_ARRAY_HPP

#include "nmtools/meta/array.hpp"
#include "nmtools/meta/traits.hpp"

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

    // TODO: remove
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

    template <typename T, size_t N>
    struct fixed_shape<
        std::array<T,N>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_num_v<T>) {
                return std::array<size_t,1>{N};
            } else if constexpr (is_ndarray_v<T>) {
                // To allow nested std::array
                constexpr auto shape = fixed_shape_v<T>;
                constexpr auto dim = shape.size() + 1;
                auto result = std::array<size_t,dim>{};
                result[0] = N;
                for (size_t i=0; i<(dim-1); i++) {
                    result[i+1] = shape[i];
                }
                return result;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<std::array<T,N>>{};
            }
        }();
    }; // fixed_shape

    template <typename...Ts>
    struct fixed_size<
        std::tuple<Ts...>
    >
    {
        static constexpr auto value = sizeof...(Ts);
        using value_type = decltype(value);
    }; // fixed_size

    template <typename T, size_t N, auto new_dim>
    struct resize_dim<
        std::array<T,N>, new_dim
    >
    {
        using array_type = std::array<T,N>;
        static constexpr auto vtype = [](){
            if constexpr (is_fixed_dim_v<array_type>) {
                constexpr auto dim = fixed_dim_v<array_type>;
                return template_reduce<new_dim-dim>([](auto init, [[maybe_unused]] auto index){
                    using type = type_t<decltype(init)>;
                    // simply unsqueeze on axis 0
                    return as_value_v<std::array<type,1>>;
                }, as_value_v<array_type>);
            } else {
                return as_value_v<error::RESIZE_DIM_UNSUPPORTED<array_type>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resize_dim

    template <typename T, size_t N, auto new_size>
    struct resize_size<
        std::array<T,N>, new_size
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_num_v<T>) {
                return as_value_v<std::array<T,new_size>>;
            } else {
                return as_value_v<error::RESIZE_SIZE_UNSUPPORTED<std::array<T,N>>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resize_size

    template <typename T, size_t N, auto...NewShape>
    struct resize_shape<
        std::array<T,N>, as_type<NewShape...>
    >
    {
        static constexpr auto vtype = [](){
            constexpr auto new_shape = std::array{NewShape...};
            constexpr auto DIM = new_shape.size();
            return template_reduce<DIM-1>([&](auto init, auto index){
                constexpr auto I = decltype(index)::value;
                using array_type = type_t<decltype(init)>;
                return as_value_v<std::array<array_type,new_shape.at(DIM-I-2)>>;
            }, as_value_v<std::array<T,new_shape.at(DIM-1)>>);
        }();
        using type = type_t<decltype(vtype)>;
    }; // resize_shape
} // namespace nmtools::meta

#endif 