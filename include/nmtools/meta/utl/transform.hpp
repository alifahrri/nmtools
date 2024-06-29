#ifndef NMTOOLS_META_UTL_TRANSFORM_HPP
#define NMTOOLS_META_UTL_TRANSFORM_HPP

#include "nmtools/meta/transform.hpp"
#include "nmtools/utl.hpp"
#include "nmtools/meta/utl/array.hpp"

#include "nmtools/utility/get.hpp"

namespace nmtools::meta
{
    template <typename T>
    struct get_maybe_type<utl::maybe<T>>
    {
        using type = T;
    };

    template <typename T, size_t N, size_t M>
    struct resize_fixed_vector<utl::array<T,N>,M>
    {
        using type = utl::array<T,M>;
    };

    template <typename T, size_t N, auto M>
    struct resize_size<utl::array<T,N>,M>
    {
        using type = utl::array<T,(size_t)M>;
    };

    template <typename T, size_t N, typename U>
    struct resize_fixed_ndarray<utl::array<T,N>,U>
    {
        using array_type = utl::array<T,N>;
        using element_type = get_element_type_t<array_type>;

        static constexpr auto vtype = [](){
            // TODO: remove is_fixed_size_ndarray_v
            if constexpr (is_fixed_shape_v<U> || is_fixed_size_ndarray_v<U>) {
                constexpr auto shape = [](){
                    constexpr auto shape = fixed_shape_v<U>;
                    if constexpr (is_fail_v<decltype(shape)>) {
                        return fixed_ndarray_shape_v<U>;
                    } else {
                        return shape;
                    }
                }();
                constexpr auto dim = len_v<decltype(shape)>;
                auto initial = as_value_v<utl::array<element_type,nmtools::get<dim-1>(shape)>>;
                return template_reduce<dim-1>([&](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    constexpr auto s = nmtools::get<dim-i-2>(shape);
                    using init_t = type_t<decltype(init)>;
                    return as_value_v<utl::array<init_t,s>>;
                }, initial);
            } else {
                return as_value_v<error::RESIZE_FIXED_NDARRAY_UNSUPPORTED<array_type,U>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    // TODO: remove this specialization
    template <typename...Ts, typename new_type>
    struct append_type<utl::tuple<Ts...>,new_type>
    {
        using type = utl::tuple<Ts...,new_type>;
    };

    // TODO: remove this specialization
    template <typename...Ts, typename new_type>
    struct append_type<utl::tuplev2<Ts...>,new_type>
    {
        using type = utl::tuplev2<Ts...,new_type>;
    };

    // TODO: remove
    template <typename...Ts>
    struct tuple_to_array<utl::tuple<Ts...>>
    {
        using common_t = typename common_type<Ts...>::type;
        static constexpr auto value_vtype = [](){
            if constexpr (is_integral_constant_v<common_t>) {
                return as_value_v<typename common_t::value_type>;
            } else {
                return as_value_v<common_t>;
            }
        }();
        using value_type = remove_cvref_t<type_t<decltype(value_vtype)>>;
        // TODO: check if common_type fail, only return array if common_type is valid
        using type = utl::array<value_type,sizeof...(Ts)>;
    };

    // TODO: consider to remove, abstract away the either impl. and using is_either to decide
    template <typename left_t, typename right_t, typename Left, typename Right>
    struct replace_either<utl::either<left_t,right_t>,Left,Right>
    {
        using type = utl::either<Left,Right>;
    };

    // TODO: remove
    #if 0
    template <typename...Ts>
    struct to_value<utl::tuple<Ts...>
        , enable_if_t<(is_constant_index_v<Ts> && ...)>
    >
    {
        using tuple_type = utl::tuple<Ts...>;
        using error_type = error::TO_VALUE_UNSUPPORTED<tuple_type>;
        static constexpr auto value = [](){
            constexpr auto N = sizeof...(Ts);
            return meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using init_t = remove_cvref_t<decltype(init)>;
                using type_i = remove_cvref_t<typename std::tuple_element<i,tuple_type>::type>;
                if constexpr (is_constant_index_v<type_i>) {
                    if constexpr (i==0) {
                        // starting point, create the array
                        using element_t = typename type_i::value_type;
                        using array_type = utl::array<element_t,1>;
                        auto array = array_type{};
                        array[i] = type_i::value;
                        return array;
                    } else if constexpr (is_same_v<init_t,error_type>) {
                        return error_type{};
                    } else /* if constexpr (is_index_array_v<init_t>) */ {
                        using value_type = typename type_i::value_type;
                        using element_t  = promote_index_t<value_type,get_element_type_t<init_t>>;
                        using array_type = utl::array<element_t,i+1>;
                        auto array = array_type{};
                        for (size_t j=0; j<i; j++) {
                            array[j] = init[j];
                        }
                        array[i] = type_i::value;
                        return array;
                    }
                } else {
                    return error_type{};
                }
            }, error_type{});
        }();
    };
    #endif

    template <typename left_t, typename right_t>
    struct get_either_left<utl::either<left_t,right_t>>
    {
        using type = left_t;
    };

    template <typename left_t, typename right_t>
    struct get_either_right<utl::either<left_t,right_t>>
    {
        using type = right_t;
    };

    // TODO: remove this specialization
    template <typename...Ts, size_t I>
    struct type_at<utl::tuple<Ts...>,I>
    {
        using tuple_t = utl::tuple<Ts...>;
        using type = utl::tuple_element_t<I,tuple_t>;
    };

    // TODO: remove this specialization
    template <typename...Ts, size_t I>
    struct type_at<utl::tuplev2<Ts...>,I>
    {
        using tuple_t = utl::tuplev2<Ts...>;
        using type = utl::tuple_element_t<I,tuple_t>;
    };

    template <typename T, size_t N, typename U>
    struct replace_element_type<utl::array<T,N>,U>
    {
        // NOTE: this array maybe nested array
        // so must resize back to the original shape
        using array_type = utl::array<T,N>;
        static constexpr auto vtype = [](){
            using array_t = utl::array<U,N>;
            using replaced_t = resize_fixed_ndarray_t<array_t,array_type>;
            return as_value_v<replaced_t>;
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename T, template<typename>typename Allocator, typename U>
    struct replace_value_type<utl::vector<T,Allocator<T>>,U>
    {
        using type = utl::vector<U,Allocator<U>>;
    };

    template <typename T, size_t N, typename U>
    struct replace_value_type<utl::array<T,N>,U>
    {
        using type = utl::array<U,N>;
    };

    template <typename T, size_t N, typename U>
    struct replace_value_type<utl::static_vector<T,N>,U>
    {
        using type = utl::static_vector<U,N>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_META_UTL_TRANSFORM_HPP