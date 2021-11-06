#ifndef NMTOOLS_META_TRANSFORM_HPP
#define NMTOOLS_META_TRANSFORM_HPP

#include "nmtools/meta/bits/transform/append_type.hpp"
#include "nmtools/meta/bits/transform/append_value.hpp"
#include "nmtools/meta/bits/transform/at.hpp"
#include "nmtools/meta/bits/transform/bit_reference_to_bool.hpp"
#include "nmtools/meta/bits/transform/concat_type.hpp"
#include "nmtools/meta/bits/transform/get_either.hpp"
#include "nmtools/meta/bits/transform/get_element_type.hpp"
#include "nmtools/meta/bits/transform/get_index_type.hpp"
#include "nmtools/meta/bits/transform/get_maybe_type.hpp"
#include "nmtools/meta/bits/transform/len.hpp"
#include "nmtools/meta/bits/transform/promote_index.hpp"
#include "nmtools/meta/bits/transform/promote_types.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/meta/bits/transform/replace_either.hpp"
#include "nmtools/meta/bits/transform/replace_element_type.hpp"
#include "nmtools/meta/bits/transform/resize_fixed_ndarray.hpp"
#include "nmtools/meta/bits/transform/to_value.hpp"
#include "nmtools/meta/bits/transform/transform_bounded_array.hpp"
#include "nmtools/meta/bits/transform/tuple_to_array.hpp"
#include "nmtools/meta/bits/transform/type_list_at.hpp"

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/traits.hpp"
#include "nmtools/meta/array.hpp"

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>

namespace nmtools::meta
{

    namespace detail
    {
        // TODO: remove metafunctions
        template <typename T, typename U, typename=void>
        struct merge_helper
        {
            using type = std::tuple<T,U>;
        }; // merge_helper

        // TODO: remove metafunctions
        template <template<typename...>typename TT, typename...Ts, template<typename...>typename TU, typename...Us>
        struct merge_helper<TT<Ts...>,TU<Us...>>
        {
            using type = TT<Ts...,Us...>;
        }; // merge_helper

        // TODO: remove metafunctions
        template <template<typename...>typename TT, typename...Ts, typename U>
        struct merge_helper<TT<Ts...>,U>
        {
            using type = TT<Ts...,U>;
        }; // merge_helper

        // TODO: remove metafunctions
        template <typename T, template<typename...>typename TU, typename...Us>
        struct merge_helper<T,TU<Us...>>
        {
            using type = TU<T,Us...>;
        }; // merge_helper

    } // namespace detail

    // TODO: remove metafunctions
    /**
     * @brief merge two type T (possibly tuple) and U (possibly tuple) to single tuple.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T lhs tuple to be merged
     * @tparam U rhs tuple to be merged
     */
    template <typename T, typename U>
    struct merge
    {
        using type = type_t<detail::merge_helper<T,U>>;
    }; // merge

    /**
     * @brief helper alias template to merge two type T (possibly tuple) and U (possibly tuple) to single tuple.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T lhs tuple to be merged
     * @tparam U rhs tuple to be merged
     */
    template <typename T, typename U>
    using merge_t = typename merge<T,U>::type;

    /**
     * @brief helper alias template to get public member type `first` from type T
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using first_t = typename T::first;

    /**
     * @brief helper alias template to get public member type `second` from type T
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using second_t = typename T::second;

    namespace detail
    {
        // TODO: cleanup metafunctions
        template <typename T, auto I, typename=void>
        struct split_at_helper
        {
            using first  = void;
            using second = void;
            using type = T;
        }; // split_at_helper

        // TODO: cleanup metafunctions
        template <template<typename...>typename TT, typename T, typename...Ts>
        struct split_at_helper<TT<T,Ts...>,1>
        {
            using first  = TT<T>;
            using second = TT<Ts...>;
            using type   = std::pair<first,second>;
        }; // split_at_helper

        // TODO: cleanup metafunctions
        template <template<typename...>typename TT, typename T, typename...Ts, auto I>
        struct split_at_helper<TT<T,Ts...>,I,std::enable_if_t<(I>1)>>
        {
            using rest   = split_at_helper<TT<Ts...>,I-1>;
            using first  = merge_t<TT<T>,first_t<rest>>;
            using second = second_t<rest>;
            using type   = std::pair<first,second>;
        }; // split_at_helper
    } // namespace detail

    // TODO: cleanup metafunctions
    /**
     * @brief metafunction to split type list at index I
     *
     * Resulting in member type `first`, `second` and `type`.
     * Where `first` holds the type from 0 until I,
     * `second` hold the type from I until the end,
     * and `type` is `pair<first,second>`.
     * On failed specialization, `first` and `second` are `void`
     * and `type` is equal to T.
     * 
     * @tparam T type to transform
     * @tparam I index for splitting type
     * @tparam typename 
     */
    template <typename T, auto I, typename=void>
    struct split_at
    {
        using split_type = detail::split_at_helper<T,I>;
        using first      = first_t<split_type>;
        using second     = second_t<split_type>;
        using type       = type_t<split_type>;
    }; // split_at

    /**
     * @brief helper alias template for split_at
     * 
     * @tparam T type to transform
     * @tparam I index for splitting type
     */
    template <typename T, auto I>
    using split_at_t = type_t<split_at<T,I>>;


    template <typename T>
    struct pop_first
    {
        // TODO: remove metafunction
        /**
        * @brief pop first type of std::tuple
        * 
        * @tparam First 
        * @tparam Rest 
        * @return constexpr auto 
        */
        template <typename First, typename ...Rest>
        static constexpr auto _pop_first(const std::tuple<First,Rest...>)
        {
            /* NOTE: implemented as function for easy tparam extract */
            return std::tuple<First,std::tuple<Rest...>>{};
        }

        using pair  = decltype(_pop_first(std::declval<T>()));
        /* first type from pair */
        using first = std::tuple_element_t<0,pair>;
        using type  = std::tuple_element_t<1,pair>;
    };

    template <typename T>
    using pop_first_t = typename pop_first<T>::type;

    // TODO: remove metafunctions
    /**
     * @brief pop the last element of typelist (tuple) T.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T tuple to be transformed
     */
    template <typename T>
    struct pop_last
    {
        template <typename...Ts, size_t...Is>
        static constexpr auto _make_tuple(std::tuple<Ts...> t, std::integer_sequence<size_t,Is...>)
        {
            return std::make_tuple(std::get<Is>(t)...);
        }
        
        template <typename...Ts>
        static constexpr auto _pop_last(std::tuple<Ts...>)
        {
            /* NOTE: implemented as function for easy tparam extract */
            constexpr auto N = sizeof...(Ts);
            using indices_t = std::make_index_sequence<N-1>;
            using tuple_t = std::tuple<Ts...>;
            using type = decltype(_make_tuple(std::declval<tuple_t>(),indices_t{}));
            using last_t = std::tuple_element_t<N-1,tuple_t>;
            return std::make_tuple(last_t{},type{});
        } // _pop_last

        using pair  = decltype(_pop_last(std::declval<T>()));
        /* last type from pair */
        using last = std::tuple_element_t<0,pair>;
        using type = std::tuple_element_t<1,pair>;
    }; // pop_last

    /**
     * @brief helper alias template to pop the last element of typelist (tuple) T.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T tuple to be transformed
     */
    template <typename T>
    using pop_last_t = typename pop_last<T>::type;

    /**
     * @brief reverse the element of typelist (tuple) T.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T tuple to be reversed
     */
    template <typename T>
    struct type_reverse
    {
        // TODO: cleanup metafunctions
        template <typename Ts>
        static constexpr auto _reverse_type_list(std::tuple<Ts>)
        {
            return Ts{};
        } // _reverse_type_list

        template <typename...Ts>
        static constexpr auto _reverse_type_list(std::tuple<Ts...>)
        {
            using tuple_t = std::tuple<Ts...>;
            using pop_last_type = pop_last<tuple_t>;
            using last_t = typename pop_last_type::last;
            using type_t = typename pop_last_type::type;
            using rest_t = decltype(_reverse_type_list(std::declval<type_t>()));
            using reversed_t= merge_t<last_t,rest_t>;
            return reversed_t{};
        } // _reverse_type_list

        using type = decltype(_reverse_type_list(std::declval<T>()));
    };

    template <typename T>
    struct type_reverse<std::tuple<T>>
    {
        using type = std::tuple<T>;
    }; // type_reverse

    /**
     * @brief helper alias template to reverse the element of typelist (tuple) T.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T tuple to be reversed
     */
    template <typename T>
    using type_reverse_t = typename type_reverse<T>::type;

    /**
     * @brief create reversed integer sequence.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T an integer type to use for the elements of the sequence
     * @tparam N number of integer to be created
     */
    template <typename T, auto N>
    struct reversed_integer_sequence
    {
        template <typename U> struct sequence_to_tuple {};
        template <auto...Is>
        struct sequence_to_tuple<std::integer_sequence<T,Is...>>
        {
            using type = std::tuple<std::integral_constant<T,Is>...>;
        }; // sequence_to_tuple

        template <typename U> struct tuple_to_sequence {};
        template <typename...Ts>
        struct tuple_to_sequence<std::tuple<Ts...>>
        {
            using type = std::integer_sequence<T,static_cast<T>(Ts::value)...>;
        }; // tuple_to_sequence

        using sequence_type = std::make_integer_sequence<T,N>;
        using sequence_tuple_type = typename sequence_to_tuple<sequence_type>::type;
        using reversed_tuple_type = type_reverse_t<sequence_tuple_type>;
        using type = typename tuple_to_sequence<reversed_tuple_type>::type;
    }; // reversed_integer_sequence

    /**
     * @brief helper alias template to create reversed integer sequence.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T an integer type to use for the elements of the sequence
     * @tparam N number of integer to be created
     */
    template <typename T, T N>
    using make_reversed_integer_sequence = typename reversed_integer_sequence<T,N>::type;

    /**
     * @brief helper alias template to create reversed index sequence.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam N number of index to be created
     */
    template <size_t N>
    using make_reversed_index_sequence = make_reversed_integer_sequence<size_t,N>;

    /**
     * @brief metafunction to resolve specific op return type.
     *
     * Default implementation has `type` member type aliasing `void`,
     * may be used at caller site to check and provide context.
     * 
     * @tparam always_void 
     * @tparam op_t operator tag
     * @tparam tparams 
     */
    template <typename always_void, typename op_t, typename...tparams>
    struct resolve_optype
    {
        using type = void;
    }; // resolve_optype

    /**
     * @brief helper alias template to get the resulting type of metafunction
     * resolve_optype.
     * 
     * @tparam op_t operator tag
     * @tparam tparams 
     */
    template <typename op_t, typename...tparams>
    using resolve_optype_t = typename resolve_optype<void,op_t,tparams...>::type;


    // TODO: cleanup metafunctions
    /**
     * @brief make nested raw array from element type T, first axis size N, and the rest of axis size Ns...
     *
     * For example make_nested_raw_array<double,3,4,5> is creating double[3][4][5].
     * 
     * @tparam T desired element type
     * @tparam N size of the first axis
     * @tparam Ns size(s) of the rest axes
     */
    template <typename T, size_t N, size_t...Ns>
    struct make_nested_raw_array
    {
        template <typename T_, size_t N_, size_t...Ns_>
        struct _make_type
        {
            using nested_type = typename _make_type<T_,Ns_...>::type;
            using type = nested_type[N_];
        }; // _make_type
        template <typename T_, size_t N_>
        struct _make_type<T_,N_>
        {
            using type = T_[N_];
        }; // _make_type

        using type = typename _make_type<T,N,Ns...>::type;
    }; // make_nested_raw_array

    /**
     * @brief metafunction to make nested dynamic array.
     * 
     * Create nested array type to N number of depth.
     * 
     * @tparam array_t template-template parameters that takes types. (e.g. array_t<typename...>)
     * @tparam T element type of desired nested dynamic array
     * @tparam N desired number of depth
     * @tparam Args additional template parameter to each array_t instantiation. e.g. array_t<T,Args...>
     */
    template <template<typename...> typename array_t, typename T, size_t N>
    struct make_nested_dynamic_array
    {
        // @note apparently it is required to make array_t to takes arbitrary nr of params
        static constexpr auto _make_nested_type()
        {
            if constexpr (N==1)
                return array_t<T>{};
            else {
                using type = typename make_nested_dynamic_array<array_t,T,N-1>::type;
                return array_t<type>{};
            }
        } // _make_nested_type()

        using type = decltype(_make_nested_type());
    };

    // TODO: remove metafunctions
    /**
     * @brief helper alias template to get the type of nested raw array.
     * 
     * @tparam T desired element type
     * @tparam N size of the first axis
     * @tparam Ns size(s) of the rest axes
     */
    template <typename T, size_t N, size_t...Ns>
    using make_nested_raw_array_t = typename make_nested_raw_array<T,N,Ns...>::type;

    // TODO: remove metafunctions
    /**
     * @brief helper alias template to make nested dynamic array.
     * 
     * Create nested array type to N number of depth.
     * 
     * @tparam array_t template-template parameters that takes types. (e.g. array_t<typename...>)
     * @tparam T element type of desired nested dynamic array
     * @tparam N desired number of depth
     */
    template <template<typename...> typename array_t, typename T, size_t N>
    using make_nested_dynamic_array_t = typename make_nested_dynamic_array<array_t,T,N>::type;

    namespace detail
    {
        // TODO: remove metafunctions
        /**
         * @brief helper metafunction for meta::apply
         * 
         * @tparam TT template template parameter
         * @tparam T type list
         */
        template <template<typename...>typename TT, typename T>
        struct apply_helper
        {
            using type = void;
        }; // apply_helper

        // TODO: remove metafunctions
        template <template<typename...>typename TT, template<typename...>typename type_list, typename...Ts>
        struct apply_helper<TT,type_list<Ts...>>
        {
            static constexpr auto vtype = []()
            {
                using meta_fn_type = TT<Ts...>;
                if constexpr (meta::has_type_v<meta_fn_type>)
                    // assuming type from meta_fn_type is default constructible
                    return typename meta_fn_type::type{};
                else return detail::fail_t{};
            }();
            using type = meta::remove_cvref_t<detail::fail_to_void_t<decltype(vtype)>>;
        }; // apply_helper
    } // namespace detail

    // TODO: remove metafunctions
    /**
     * @brief apply template template parameter T on type list T
     * 
     * @tparam TT template template parameter
     * @tparam T type list
     */
    template <template<typename...>typename TT, typename T>
    struct apply
    {
        // @note use helper metafunction so specialization is not necessary
        using type = typename detail::apply_helper<TT,T>::type;
    }; // apply_traits_helper

    /**
     * @brief helper alias template for apply
     * 
     * @tparam TT template template parameter
     * @tparam T type list
     */
    template <template<typename...>typename TT, typename T>
    using apply_t = typename apply<TT,T>::type;

    /**
     * @brief Reserved metafunction to create a compile-time constant
     * 
     * @tparam I 
     * @tparam Is 
     */
    template <auto I, auto...Is>
    struct make_ct;

    // TODO: remove metafunctions
    /**
     * @brief helper alias template to construct integer_sequence
     * 
     * @tparam I 
     * @tparam Is 
     */
    template <auto I, auto...Is>
    using sequence_t = std::integer_sequence<decltype(I),I,Is...>;

    namespace detail
    {
        // TODO: remove metafunctions
        template <template<typename>typename Predicate, typename T, typename=void>
        struct filter_helper
        {
            using type = void;
        }; // filter_helper

        // TODO: remove metafunctions
        template <template<typename>typename Predicate, template<typename...>typename TT, typename T>
        struct filter_helper<Predicate,TT<T>>
        {
            using type = std::conditional_t<
                Predicate<T>::value, TT<T>, TT<>
            >;
        }; // filter_helper

        // TODO: remove metafunctions
        template <template<typename>typename Predicate, template<typename...>typename TT, typename T, typename U, typename...Ts>
        struct filter_helper<Predicate,TT<T,U,Ts...>>
        {
            using fst  = TT<T>;
            using snd  = TT<U,Ts...>;
            using type = merge_t<
                type_t<filter_helper<Predicate,fst>>,
                type_t<filter_helper<Predicate,snd>>
            >;
        }; // filter_helper
    } // namespace detail

    // TODO: remove metafunctions
    template <template<typename>typename Predicate, typename T, typename=void>
    struct filter
    {
        using type = type_t<detail::filter_helper<Predicate,T>>;
    }; // filter

    // TODO: remove metafunctions
    template <template<typename>typename Predicate, typename T>    
    using filter_t = type_t<filter<Predicate,T>>;

    template <typename array_t>
    struct get_element_or_common_type
    {
        static constexpr auto vtype = [](){
            using element_t = get_element_type_t<array_t>;
            if constexpr (std::is_void_v<element_t> || is_fail_v<element_t>) {
                using common_t = apply_t<std::common_type,array_t>;
                return as_value_v<common_t>;
            } else /* if constexpr (is_num_v<element_t>) */ {
                return as_value_v<element_t>;
            }
        }();
        using type = type_t<decltype(vtype)>;
        using element_t = get_element_type_t<array_t>;
        using common_t  = apply_t<std::common_type,array_t>;
    }; // get_element_or_common_type

    template <typename array_t>
    using get_element_or_common_type_t = type_t<get_element_or_common_type<array_t>>;

    /**
     * @brief metafunction to resize fixed vector.
     * 
     * @tparam T fixed vector type to be resized.
     * @tparam N new size.
     */
    template <typename T, auto N, typename=void>
    struct resize_fixed_vector
    {
        // TODO: use error type
        /* pack new size as type instead of non-type template param */
        using new_size = std::integral_constant<size_t,N>;
        using type = replace_template_parameter_t<T,new_size>;
    };

    /**
     * @brief helper alias template to resize metafunction to resize fixed vector.
     * 
     * @tparam T fixed vector type to be resized.
     * @tparam N new size.
     */
    template <typename T, auto N>
    using resize_fixed_vector_t = typename resize_fixed_vector<T,N>::type;

    template <typename T, size_t N>
    struct resize_fixed_index_array : resize_fixed_vector<T,N> {};

    template <typename T, size_t N>
    using resize_fixed_index_array_t = type_t<resize_fixed_index_array<T,N>>;

    /**
     * @brief Alias to std::remove_pointer_t.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    using remove_pointer_t = std::remove_pointer_t<array_t>;

    /**
     * @brief Remove const-ness, reference, and pointer from a type.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    using remove_cvref_pointer_t = remove_cvref_t<remove_pointer_t<array_t>>;

    /**
     * @brief Reserved metafunction to make type T unsigned
     * 
     * @tparam T 
     * @note implementation should use macro NMTOOLS_META_MAKE_UNSIGNED
     */
    template <typename T>
    struct make_unsigned;

    /**
     * @brief Reserved metafunction to make type T signed
     * 
     * @tparam T 
     * @note implementation should use macro NMTOOLS_META_MAKE_SIGNED
     */
    template <typename T>
    struct make_signed;

    /**
     * @brief Reserved metafunction to create a tuple type
     * 
     * @tparam Ts 
     * @note implementation should use macro NMTOOLS_META_MAKE_TUPLE
     */
    template <typename...Ts>
    struct make_tuple;

    /**
     * @brief Reserved metafunction to create maybe type
     * 
     * @tparam T 
     * @note implementation should use macro NMTOOLS_META_MAKE_MAYBE_TYPE
     */
    template <typename T, typename=void>
    struct make_maybe_type;

    /**
     * @brief Reserved metafunction to create an array type
     * 
     * @tparam T element type
     * @tparam N desired length
     * @tparam typename 
     * @note implementation should use macro NMTOOLS_META_MAKE_ARRAY_TYPE
     */
    template <typename T, size_t N, typename=void>
    struct make_array_type;

    /** @} */ // end group meta
} // namespace nmtools::meta

#endif // NMTOOLS_META_TRANSFORM_HPP