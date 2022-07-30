#ifndef NMTOOLS_META_STL_TRANSFORM_HPP
#define NMTOOLS_META_STL_TRANSFORM_HPP

#include "nmtools/meta/transform.hpp"

#include <optional>
#include <tuple>
#include <array>
#include <utility>
#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <variant>
#include <vector>

namespace nmtools::meta
{

    template <auto I>
    struct to_value<std::integral_constant<decltype(I),I>>
    {
        static inline constexpr auto value = I;
    }; // to_value

    // some edge case: array of constant, simply transform to value
    // such array exist maybe because element type deduction is imperfect
    // or couldnt handle such case
    template <auto I, size_t N>
    struct to_value<std::array<std::integral_constant<decltype(I),I>,N>>
    {
        static inline constexpr auto value = [](){
            using type = std::array<decltype(I),N>;
            auto value = type{};
            for (size_t i=0; i<N; i++) {
                value[i] = I;
            }
            return value;
        }();
    }; // to_value

    template <typename left_t, typename right_t>
    struct get_either_left<std::variant<left_t,right_t>>
    {
        using type = left_t;
    };

    template <typename left_t, typename right_t>
    struct get_either_right<std::variant<left_t,right_t>>
    {
        using type = right_t;
    };

    template <typename left_t, typename right_t>
    struct get_either_left<const std::variant<left_t,right_t>>
    {
        using type = left_t;
    };

    template <typename left_t, typename right_t>
    struct get_either_right<const std::variant<left_t,right_t>>
    {
        using type = right_t;
    };

    template <typename...Ts, size_t I>
    struct type_at<std::tuple<Ts...>,I>
    {
        using tuple_t = std::tuple<Ts...>;
        using type = std::tuple_element_t<I,tuple_t>;
    }; // type_at


    /**
     * @brief specialization of resize_fixed_vector for std::array type
     * 
     * @tparam T value_type of std::array, automatically deduced
     * @tparam N size of std::array, automatically deduced
     * @tparam new_size new desired size
     */
    template <typename T, auto N, auto new_size>
    struct resize_fixed_vector<std::array<T,N>,new_size>
    {
        using type = std::array<T,new_size>;
    };

    /**
     * @brief specialization of resize_fixed_vector for raw array type,
     * resulting type is std::array instead of raw array.
     * 
     * @tparam T element type of raw array, automatically deduced
     * @tparam N size of raw array, automatically deduced
     * @tparam new_size new desired size
     */
    template <typename T, auto N, auto new_size>
    struct resize_fixed_vector<T[N],new_size>
    {
        using type = std::array<T,new_size>;
    };

    // TODO: remove
    #if 0
    template <typename...Ts>
    struct tuple_to_array<std::tuple<Ts...>>
    {
        using common_t = std::common_type_t<Ts...>;
        using type = std::array<common_t,sizeof...(Ts)>;
    }; // tuple_to_array
    #endif

    template <typename first, typename second>
    struct tuple_to_array<std::pair<first,second>>
    {
        using common_t = std::common_type_t<first,second>;
        using type = std::array<common_t,2>;
    }; // tuple_to_array

    template <typename...Ts, typename new_type>
    struct append_type<std::tuple<Ts...>,new_type>
    {
        using type = std::tuple<Ts...,new_type>;
    }; // append_type

    template <typename...Ts, typename...Us>
    struct concat_type< std::tuple<Ts...>, std::tuple<Us...> >
    {
        using type = std::tuple<Ts...,Us...>;
    }; // concat_type

    template <typename left_t, typename right_t, typename Left, typename Right>
    struct replace_either<std::variant<left_t,right_t>,Left,Right>
    {
        using type = std::variant<Left,Right>;
    };

#if 0
    // TODO: remove, add more generic specialization with sfinae on is_tuple
    template <typename...Ts>
    struct get_common_type<std::tuple<Ts...>>
    {
        // we do not want this because it trigger compile error when failing
        // using type = std::common_type_t<Ts...>;

        static constexpr auto vtype = [](){
            using type = std::common_type<Ts...>;
            if constexpr (has_type_v<type>) {
                return as_value_v<type_t<type>>;
            } else {
                return as_value_v<error::GET_COMMON_TYPE_UNSUPPORTED<std::tuple<Ts...>>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
#endif

    template <typename T, typename Allocator>
    struct get_value_type<std::vector<T,Allocator>>
    {
        using type = T;
    };

    template <typename T, template<typename...>typename Allocator, typename value_type>
    struct replace_value_type<std::vector<T,Allocator<T>>,value_type>
    {
        using type = std::vector<value_type,Allocator<value_type>>;
    };

    template <typename T, size_t N, typename value_type>
    struct replace_value_type<std::array<T,N>,value_type>
    {
        using type = std::array<value_type,N>;
    };

    // TODO: remove metafunctions
    /**
     * @brief specialization for replace_template_parameter for std array, 
     * since we can't mix non-type & type as variadic template parameter.
     * The new size of new array should be supplied via std integral_constant,
     * since we expects type here.
     * 
     * @tparam value_t origin value_type
     * @tparam N origin size
     * @tparam subs_value_t value_type for substitution
     * @tparam subs_N substitution size
     */
    template <typename value_t, auto N, typename subs_value_t, auto subs_N, typename size_type>
    struct replace_template_parameter<std::array<value_t,N>,subs_value_t,std::integral_constant<size_type,subs_N>>
    {
        using origin_tparams = std::tuple<value_t>;
        using type = std::array<subs_value_t,subs_N>;
    };

    // TODO: remove metafunctions
    /**
     * @brief replace_template_parameter of class T with parameter(s) packed as tuple.
     *
     * @example 
     * @tparam T template template parameter, deduced automatically
     * @tparam Origin template parameter(s) of T, deduced automatically
     * @tparam Subs substitute for Origin, deduced automatically
     */
    template <template <typename...> typename T, typename...Origin, typename...Subs>
    struct replace_template_parameter_from_typelist<T<Origin...>,std::tuple<Subs...>>
    {
        /**
         * @brief call replace_template_parameter here so that any existing specialization
         * can be used, e.g. specialization of std array which unpacks integral_constant<...>
         * to size_t as template parameter.
         * 
         */
        using type = replace_template_parameter_t<T<Origin...>,Subs...>;
    };
} // namespace nmtools::meta

#include "nmtools/meta/stl/traits.hpp"

namespace nmtools::meta
{
    // the following code breaks gcc: "internal compiler error: in finish_member_declaration, at cp/semantics.c:3237"
    // (even in newest version: 11.2), works fine on clang, check the else block for workaround
    // https://github.com/alifahrri/nmtools/runs/3708887742?check_suite_focus=true
    // https://github.com/alifahrri/nmtools/pull/156/checks?check_run_id=3708887743
    // https://github.com/alifahrri/nmtools/pull/156/checks?check_run_id=3711520594
    #if 0
        /**
     * @brief Specialization fo to_value for std types (tuple of int constant)
     * 
     * @tparam Is 
     */
    template <auto...Is>
    struct to_value<
        std::tuple<std::integral_constant<decltype(Is),Is>...>
    >
    {
        using tuple_type = std::tuple<std::integral_constant<decltype(Is),Is>...>;
        using value_type = std::common_type_t<decltype(Is)...>;
        // The following line breaks gcc (even in newest version: 11.2)
        static inline constexpr auto value = std::array<value_type,sizeof...(Is)>{static_cast<value_type>(Is)...};

        // trying to find workaround but didn't work
        // static constexpr auto value = [](){
        //     using type = std::array<value_type,sizeof...(Is)>;
        //     auto dst = type{};
        //     meta::template_for<sizeof...(Is)>([&](auto index){
        //         constexpr auto i = decltype(index)::value;
        //         constexpr auto v = std::tuple_element_t<i,tuple_type>::value;
        //         dst[i] = v;
        //     });
        //     return dst;
        // }();
    }; // to_value

    #else
    template <typename...Ts>
    struct to_value<
        std::tuple<Ts...>
    >
    {
        using tuple_type = std::tuple<Ts...>;
        using error_type = error::TO_VALUE_UNSUPPORTED<std::tuple<Ts...>>;
        static constexpr auto value = [](){
            constexpr auto N = sizeof...(Ts);
            // the following alias decl. can't compile on clang 10 & gcc 9.3
            // gcc error: pack expansion argument for non-pack parameter
            // clang error: pack expansion used as argument for non-pack parameter of alias template
            // seems like related:
            // - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59498
            // - https://stackoverflow.com/questions/57080425/clang-fails-to-expand-parameter-pack-in-stdfunction-instantiation
            // using element_t  = promote_index_t<Ts...>;

            /* trying to work-around but cannot make this work, both on gcc (9.3) and clang (10), */
            // using element_t = typename promote_index<Ts...>::type;
            // static_assert( is_index_v<element_t>, "nmtools internal error" );
            // using array_type = std::array<element_t,N>;
            return meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using init_t = remove_cvref_t<decltype(init)>;
                using type_i = remove_cvref_t<std::tuple_element_t<i,tuple_type>>;
                if constexpr (is_constant_index_v<type_i>) {
                    if constexpr (i==0) {
                        // starting point, create the array
                        using element_t = typename type_i::value_type;
                        using array_type = std::array<element_t,1>;
                        auto array = array_type{};
                        array[i] = type_i::value;
                        return array;
                    } else if constexpr (std::is_same_v<init_t,error_type>) {
                        return error_type{};
                    } else /* if constexpr (is_index_array_v<init_t>) */ {
                        using value_type = typename type_i::value_type;
                        using element_t  = promote_index_t<value_type,get_element_type_t<init_t>>;
                        using array_type = std::array<element_t,i+1>;
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
    }; // to_value
    #endif

    /**
     * @brief Specialization of resize_fixed_ndarray for std::array.
     * 
     * @tparam T 
     * @tparam U 
     * @tparam N 
     * @todo move to separate file, e.g. meta/stl/transform.hpp
     */
    template <typename T, typename U, size_t N>
    struct resize_fixed_ndarray<std::array<T,N>,U,
        std::enable_if_t<is_fixed_size_ndarray_v<U>>
    >
    {
        template <typename array_t, typename new_t>
        struct replace_value_type
        {
            using type = void;
        };

        template <typename value_t, size_t M, typename new_t>
        struct replace_value_type<std::array<value_t,M>,new_t>
        {
            static constexpr auto vtype = [](){
                if constexpr (is_num_v<value_t>) {
                    using type = std::array<new_t,M>;
                    return as_value_v<type>;
                } else {
                    using inner_t = type_t<replace_value_type<value_t,new_t>>;
                    using type = std::array<inner_t,M>;
                    return as_value_v<type>;
                }
            }();
            using type = type_t<decltype(vtype)>;
        };
        
        static constexpr auto vtype = [](){
            constexpr auto shape = fixed_ndarray_shape_v<U>;
            constexpr auto DIM   = fixed_ndarray_dim_v<U>;
            using element_t = get_element_type_t<std::array<T,N>>;
            return template_reduce<DIM>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using init_t = type_t<remove_cvref_t<decltype(init)>>;
                constexpr auto size = std::get<i>(shape);
                if constexpr (i==0) {
                    using type = std::array<element_t,size>;
                    return as_value_v<type>;
                } else {
                    using array_t = init_t;
                    using inner_t = std::array<element_t,size>;
                    using type = type_t<replace_value_type<array_t,inner_t>>;
                    return as_value_v<type>;
                }
            }, /*init=*/as_value_v<void>);
        }();
        using type = type_t<decltype(vtype)>;
    }; // resize_fixed_ndarray

    /**
     * @brief Replace element type of std::array
     * 
     * @tparam T src element type, maybe nested array
     * @tparam N 
     * @tparam U dst element type
     */
    template <typename T, size_t N, typename U>
    struct replace_element_type<std::array<T,N>,U,std::enable_if_t<std::is_arithmetic_v<U>>>
    {
        static constexpr auto vtype = [](){
            if constexpr (std::is_arithmetic_v<T>) {
                using type = std::array<U,N>;
                return as_value_v<type>;
            }
            else {
                using element_t = type_t<replace_element_type<T,U>>;
                using type = std::array<element_t,N>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // replace_element_type
}

#endif // NMTOOLS_META_STL_TRANSFORM_HPP