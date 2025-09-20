#ifndef NMTOOLS_META_UTL_ARRAY_HPP
#define NMTOOLS_META_UTL_ARRAY_HPP

#include "nmtools/meta/array.hpp"

#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"
#include "nmtools/meta/bits/traits/is_slice_index.hpp"

#include "nmtools/utl.hpp"

namespace nmtools::meta
{
    template <typename T, size_t N>
    struct len<utl::array<T,N>>
    {
        static constexpr auto value = N;
    };

    // TODO: remove this specialization
    template <typename...Args>
    struct len<utl::tuple<Args...>>
    {
        static constexpr auto value = sizeof...(Args);
    };

    template <typename T, size_t Capacity>
    struct max_len<utl::static_vector<T,Capacity>>
    {
        static constexpr auto value = Capacity;
    };

    template <typename T, size_t N>
    struct fixed_shape<utl::array<T,N>>
    {
        static constexpr auto value = [](){
            if constexpr (is_num_v<T>) {
                return utl::array<size_t,1>{N};
            } else if constexpr (is_fixed_size_ndarray_v<T>) {
                auto shape = fixed_ndarray_shape_v<T>;
                using shape_t = decltype(shape);
                constexpr auto M = len_v<shape_t>;
                using res_t = utl::array<size_t,M+1>;
                auto res = res_t{};
                res[0] = N;
                for (size_t i=0; i<M; i++) {
                    res[i+1] = shape[i];
                }
                return res;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<utl::array<T,N>>{};
            }
        }();
        using value_type = decltype(value);
    };

    template <typename T, size_t N>
    struct fixed_ndarray_shape<utl::array<T,N>> : fixed_shape<utl::array<T,N>> {};

    template <typename T, size_t N>
    struct fixed_index_array_size<utl::array<T,N>,enable_if_t<is_index_v<T>>>
    {
        static constexpr auto value = N;
    };

    template <typename...Ts>
    struct fixed_index_array_size<utl::tuple<Ts...>,enable_if_t<(is_index_v<Ts> && ...)>>
    {
        static constexpr auto value = sizeof...(Ts);
    };

    template <typename T, typename Allocator>
    struct fixed_dim<utl::vector<T,Allocator>>
    {
        static constexpr auto value = [](){
            if constexpr (is_num_v<T> || is_slice_index_v<T>) {
                return 1;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<utl::vector<T,Allocator>>{};
            }
        }();
    };

    template <typename T, size_t Capacity>
    struct fixed_dim<
        utl::static_vector<T,Capacity>
    >
    {
        // TODO: no need to check for num or slice index
        static constexpr auto value = [](){
            if constexpr (is_num_v<T> || is_slice_index_v<T>) {
                return 1;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<utl::static_vector<T,Capacity>>{};
            }
        }();
    };

    template <typename T, size_t Capacity>
    struct bounded_size<
        utl::static_vector<T,Capacity>
    >
    {
        static constexpr auto value = Capacity;
    };

    // TODO: remove this specialization
    template <typename...Ts>
    struct fixed_shape<utl::tuple<Ts...>>
    {
        static constexpr auto value = [](){
            if constexpr ((is_constant_index_v<Ts> && ...)) {
                return nmtools_array{sizeof...(Ts)};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<utl::tuple<Ts...>>{};
            }
        }();
    };
} // namespace nmtools::meta

#endif // NMTOOLS_META_UTL_ARRAY_HPP