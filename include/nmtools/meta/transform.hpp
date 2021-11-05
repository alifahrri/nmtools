#ifndef NMTOOLS_META_TRANSFORM_HPP
#define NMTOOLS_META_TRANSFORM_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/traits.hpp"
#include "nmtools/meta/array.hpp"
#include "nmtools/meta/arithmetic.hpp"

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>

namespace nmtools::meta
{
    /**
     * @brief transform (bounded) raw array to std::array
     * should have member type `type` with type of std::array
     * if given T is bounded (1D or 2D) raw array, 
     * `type` has type of T otherwise
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct transform_bounded_array 
    {
        using type = T;
    };

    /**
     * @brief helper alias template to transform (bounded) raw array to std::array
     * 
     * @tparam T (bounded) array
     */
    template <typename T>
    using transform_bounded_array_t = typename transform_bounded_array<T>::type;

    /**
     * @brief given T<Origin..>, transform to T<Substitution...>, if failed type is void
     * variadic template parameter Origin... & Substitution... should be type parameter. 
     * For non-type template parameter, only std::array is supported for now
     * 
     * @tparam T class which its template parameter to be replaced
     * @tparam  
     */
    template <typename T, typename...>
    struct replace_template_parameter 
    {
        // TODO: remove metafunctions
        using origin_tparams = void;
        /**
         * @brief define resulting type as void, so that
         * replace_template_parameter_t still well-formed
         * while error handling can be deferred to the caller
         * hence gives much more context
         */
        using type = void;
    };

    // TODO: remove metafunctions
    /**
     * @brief specialization for replace_template_parameter for success case
     * 
     * @tparam T 
     * @tparam Subs 
     * @tparam Origin 
     */
    template <template<typename...> typename T, typename ...Subs, typename ...Origin>
    struct replace_template_parameter<T<Origin...>,Subs...>
    {
        // use lighter type for type-list
        using origin_tparams = std::tuple<Origin...>;
        /**
         * @brief this assumes that the number of given substitute type, sizeof...(Subs),
         * is sufficient to instantiate T<Subs...>. Consider a case where this requirement
         * may not be met, we may need to substitute the missing template parameter from Subs
         * using appropriate type from Origin....
         */
        using type = T<Subs...>;
    };

    // TODO: remove metafunctions
    /**
     * @brief specialization for replace_template_parameter for std::array, 
     * since we can't mix non-type & type as variadic template parameter.
     * The new size of new array should be supplied via std::integral_constant,
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

    /**
     * @brief helper alias template to replace tparam
     * 
     * @tparam T original type
     * @tparam Args template parameter for substitution
     */
    template <typename T, typename...Args>
    using replace_template_parameter_t = typename replace_template_parameter<T,Args...>::type;

    /**
     * @brief Type as value
     * 
     * @tparam T type to wrap
     */
    template <typename T>
    struct as_value
    {
        using type = T;
    };

    /**
     * @brief helper inline variable for as_value
     * 
     * @tparam T type to wrap
     */
    template <typename T>
    constexpr inline auto as_value_v = as_value<T>{};

    /**
     * @brief similar to replace_template_parameter but assuming
     * new parameter are packed in typelist (tuple). default impl
     * has void as resulting type.
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct replace_template_parameter_from_typelist
    {
        /**
         * @brief define resulting type as void, so that
         * replace_template_parameter_t still well-formed
         * while error handling can be deferred to the caller
         * hence gives much more context
         */
        using type = void;
    };

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
         * can be used, e.g. specialization of std::array which unpacks integral_constant<...>
         * to size_t as template parameter.
         * 
         */
        using type = replace_template_parameter_t<T<Origin...>,Subs...>;
    };

    /**
     * @brief helper alias template for replace_template_parameter_from_typelist.
     * 
     * @tparam T class which its template parameter(s) are to be replaced.
     * @tparam TypeList type list, e.g. std::tuple<...>, which holds types for substitution.
     */
    template <typename T, typename TypeList>
    using replace_template_parameter_from_typelist_t = typename replace_template_parameter_from_typelist<T,TypeList>::type;

    /**
     * @brief helper alias template to replace tparam
     * 
     * @tparam T original type
     * @tparam Args template parameter for substitution
     */
    /* TODO: remove */
    template <typename T, typename...Args>
    using replace_tparam_t = typename replace_template_parameter<T,Args...>::type;

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

    /*
    TODO: consider to provide specialization for replace_template_parameter, that accepts
        - T<typename,auto..>, 
        - T<auto,typename...>, etc.
    */

    /**
     * @brief resize fixed array
     * 
     * @tparam T original array
     * @tparam U fixed ndarray type containing new shape
     * @tparam typename 
     */
    template <typename T, typename U, typename=void>
    struct resize_fixed_ndarray
    {
        using type = T;
    }; // resize_fixed_ndarray

    /**
     * @brief helper alias template for resize fixed array
     * 
     * @tparam T original array
     * @tparam U type containing new shape
     */
    template <typename T, typename U>
    using resize_fixed_ndarray_t = type_t<resize_fixed_ndarray<T,U>>;

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

    /**
     * @brief metafunction to get the value/element type of an ndarray
     * 
     * @tparam T type to test
     * @todo consider use expr to deduce type (e.g. expr::atnd)
     */
    template <typename T>
    struct get_ndarray_value_type
    {
        using type = void;
    };

    /**
     * @brief helper alias template for get_ndarray_value_type
     * 
     * @tparam T type to test
     */
    template <typename T>
    using get_ndarray_value_type_t = typename get_ndarray_value_type<T>::type;

    template <typename T, typename=void>
    struct bit_reference_to_bool
    {
        static constexpr auto vtype = [](){
            if constexpr (is_bit_reference_v<T>) {
                return as_value_v<bool>;
            } else {
                return as_value_v<T>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // bit_reference_to_bool

    template <typename T>
    using bit_reference_to_bool_t = type_t<bit_reference_to_bool<T>>;

    namespace error
    {
        struct GET_ELEMENT_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_element_type
    {
        /**
         * @brief helper function to deduce resulting type
         * 
         * @return constexpr auto 
         * @todo consider use expr to deduce type (e.g. expr::atnd)
         */
        static inline constexpr auto vtype = []()
        {
            /**
             * @note since is_array1d_v and is_array2d_v may not be mutually exclusive,
             * it is hard to use std::enable_if / std::void_t to specialize,
             * hence using helper function instead
             * to deduce the resulting element type.
             * 
             * @note using detail::void_to_fail_t since void can't be instantiated, reversed back to void at the caller site.
             */
            if constexpr (std::is_array_v<T>) {
                using type = std::remove_all_extents_t<T>;
                return as_value_v<type>;
            }
            else if constexpr (meta::nested_array_dim_v<T> > 0) {
                using element_t = remove_all_nested_array_dim_t<T>;
                // note that remove_all_nested_array_dim_t using expression to deduce the type
                // causing vector<bool> deduced to std::_Bit_reference instead of bool
                using type = bit_reference_to_bool_t<element_t>;
                return as_value_v<type>;
            }
            // ndarray is more generic
            else if constexpr (meta::is_ndarray_v<T>) {
                using type = get_ndarray_value_type_t<T>;
                return as_value_v<type>;
            }
            else if constexpr (meta::is_integral_constant_v<T>) {
                return as_value_v<typename T::value_type>;
            }
            else if constexpr (meta::has_value_type_v<T>) {
                using type = typename T::value_type;
                if constexpr (std::is_arithmetic_v<type>)
                    return as_value_v<type>;
                else
                    return as_value_v<typename get_element_type<type>::type>;
            }
            else if constexpr (std::is_arithmetic_v<T>)
                return as_value_v<T>;
            else return as_value_v<error::GET_ELEMENT_TYPE_UNSUPPORTED>;
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_element_type

    /**
     * @brief helper alias template for get_element_type
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using get_element_type_t = typename get_element_type<T>::type;

    namespace detail
    {
        /**
         * @brief helper metafunction for replace_element_type
         *
         * return void type if no specialization exists
         * 
         * @tparam T type in which its element type to be replaced
         * @tparam U substitute to element type  of T
         * @tparam typename 
         */
        template <typename T, typename U, typename=void>
        struct replace_element_type_helper
        {
            using type = void;
        };

        // TODO: cleanup metafunctions
        // NOTE: make it easier to recurse
        template <typename T, typename U>
        struct replace_element_type_helper<T,U,std::enable_if_t<std::is_arithmetic_v<U>>>
        {
            static constexpr auto vtype = [](){
                if constexpr (has_value_type_v<T>) {
                    using value_type = typename T::value_type;
                    // TODO: wrap std::is_arithmetic using other metafunctions
                    if constexpr (std::is_arithmetic_v<value_type>)
                        return as_value_v<replace_template_parameter_t<T,U>>;
                    else {
                        using type = type_t<replace_element_type_helper<value_type,U>>;
                        return as_value_v<replace_template_parameter_t<T,type>>;
                    }
                }
                else return as_value_v<void>;
            }();
            using type = type_t<decltype(vtype)>;
        };
    } // namespace detail

    /**
     * @brief given type T, try to replace the element type of T with U.
     *
     * The default implementation if no specialization of type T exists is defined
     * by helper metafunction detail::relace_element_type_helper. This helper can handles
     * nested std::vector and std::array. By deferring implementation to helper class,
     * this metafunction doesn't need to provide specialization hence it will be easier
     * to specialize on custom types.
     * 
     * @tparam T type in which its element type to be replaced
     * @tparam U substitute to element type  of T
     * @tparam typename sfinae point
     * @see detail::replace_element_type_helper
     */
    template <typename T, typename U, typename=void>
    struct replace_element_type
    {
        using type = type_t<detail::replace_element_type_helper<T,U>>;
    }; // replace_element_type

    /**
     * @brief helper alias template for replace element type
     * 
     * @tparam T type in which its element type to be replaced
     * @tparam U substitute to element type  of T
     */
    template <typename T, typename U>
    using replace_element_type_t = typename replace_element_type<T,U>::type;

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

    namespace error
    {
        template <typename...>
        struct TO_VALUE_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Convert constant index to value
     * 
     * If T is tuple, it is expected to transform to array
     * for easy handling as value.
     * 
     * @tparam T 
     */
    template <typename T>
    struct to_value
    {
        static inline constexpr auto value = error::TO_VALUE_UNSUPPORTED<>{};
    }; // to_value

    template <typename T>
    constexpr inline auto to_value_v = to_value<T>::value;

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

    template <typename T, typename=void>
    struct tuple_to_array
    {
        using type = T;
    }; // tuple_to_array

    template <typename T>
    using tuple_to_array_t = type_t<tuple_to_array<T>>;

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

    // TODO(wrap std metafunctions): specialize on std::tuple_size_v instead of as default
    // TODO(wrap stl): do something with std::get
    /**
     * @brief Helper metafunction for convinient tuple-size
     * 
     * @tparam T 
     */
    template <typename T>
    struct len
    {
        static constexpr auto value = [](){
            if constexpr (has_tuple_size_v<T>) {
                return std::tuple_size_v<T>;
            } else if constexpr (is_fixed_size_ndarray_v<T>) {
                // similar to python, when len is used on ndarray
                // return the size of first axis
                constexpr auto shape = fixed_ndarray_shape_v<T>;
                using shape_t = remove_cvref_t<decltype(shape)>;
                if constexpr (has_square_bracket_v<shape_t,size_t>) {
                    return shape[0];
                } else if constexpr (has_bracket_v<shape_t,size_t>) {
                    return shape(0);
                } else if constexpr (has_template_get_v<shape_t>) {
                    using std::get;
                    return get<0>(shape);
                }
            }
            else return 0;
        }();
    };

    template <typename T>
    constexpr inline auto len_v = len<T>::value;

    /**
     * @brief "value-less" type list.
     * 
     * @tparam Ts 
     */
    template <typename...Ts>
    struct type_list {};

    template <size_t I, typename type_list_t, typename=void>
    struct type_list_at
    {
        using type = void;
    }; // type_list_at

    template <size_t I, typename T, typename...Ts>
    struct type_list_at<I,type_list<T,Ts...>>
    {
        static constexpr auto vtype = [](){
            if constexpr (I==0)
                return as_value_v<T>;
            else {
                using new_type_list = type_list<Ts...>;
                using type = type_t<type_list_at<I-1,new_type_list>>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // type_list_at

    template <size_t I, typename T>
    using type_list_at_t = type_t<type_list_at<I,T>>;

    /**
     * @brief Helper metafunction to get type at index I from type list T.
     * 
     * @tparam T type list
     * @tparam I index to get the type
     */
    template <typename T, size_t I>
    struct type_at
    {
        using type = detail::fail_t;
    }; // at

    /**
     * @brief Helper alias template to type_at.
     * 
     * @tparam T type list
     * @tparam I index to get the type
     */
    template <typename T, size_t I>
    using at_t = type_t<type_at<T,I>>;

    /**
     * @brief Append new value to the end of some value type.
     * 
     * @tparam value_type some value type to be appended
     * @tparam new_value  desired new value
     */
    template <typename value_type, auto new_value>
    struct append_value
    {
        using type = void;
    }; // append_value

    template <typename value_type, auto N>
    using append_value_t = type_t<append_value<value_type,N>>;

    namespace error
    {
        struct APPEND_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Append new type to the end of some type list.
     * 
     * @tparam T        some type list to be appended
     * @tparam new_type desired new type
     */
    template <typename T, typename new_type>
    struct append_type
    {
        using type = error::APPEND_TYPE_UNSUPPORTED;
    }; // append_type


    template <typename T, typename new_type>
    using append_type_t = type_t<append_type<T,new_type>>;

    namespace error
    {
        struct CONCAT_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Concatenate two type list to single type list.
     * Given List<Ts...> and List<Us...> return List<Ts...,Us...>;
     * 
     * @tparam T type list
     * @tparam U type list
     */
    template <typename T, typename U>
    struct concat_type
    {
        using type = error::CONCAT_TYPE_UNSUPPORTED;
    }; // concat_type

    /**
     * @brief Helper type alias for concat_type
     * 
     * @tparam T type list
     * @tparam U type list
     */
    template <typename T, typename U>
    using concat_type_t = type_t<concat_type<T,U>>;

    namespace error
    {
        // default type (error-type) for promote_types metafunction
        struct PROMOTE_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief Metafunction to promote / deduce the resulting type from two arrays.
     * 
     * @tparam tag_t can be specialize if desired.
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @tparam typename 
     */
    template <typename tag_t, typename lhs_t, typename rhs_t, typename=void>
    struct promote_types
    {
        using type = error::PROMOTE_TYPE_UNSUPPORTED;
    }; // promote_types

    template <typename tag_t, typename lhs_t, typename rhs_t>
    using promote_types_t = type_t<promote_types<tag_t,lhs_t,rhs_t>>;

    namespace error
    {
        struct PROMOTE_INDEX_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Metafunction to deduce common type for index operation
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename first_t, typename second_t, typename...rest_t>
    struct promote_index
    {
        template <typename left_t, typename right_t>
        static constexpr auto non_constant(as_value<left_t>, as_value<right_t>) {
            if constexpr (!is_constant_index_v<left_t>) {
                return as_value_v<left_t>;
            } else /* if constexpr (!is_constant_index_v<right_t>) */{
                return as_value_v<right_t>;
            }
        }
    
        template <typename T>
        static constexpr auto make_non_constant(as_value<T>) {
            if constexpr (is_constant_index_v<T>) {
                return as_value_v<typename T::value_type>;
            } else {
                return as_value_v<T>;
            }
        }

        template <typename left_t, typename right_t>
        static constexpr auto cast(as_value<left_t>, as_value<right_t>) {
            // TODO: consider to select largest byte
            if constexpr (is_signed_v<left_t>) {
                return as_value_v<left_t>;
            } else /* if (is_signed_v<right_t>) */ {
                return as_value_v<right_t>;
            }
        }

        template <typename lhs_t, typename rhs_t>
        static constexpr auto binary_vtype(as_value<lhs_t>, as_value<rhs_t>) {
            if constexpr (is_constant_index_v<lhs_t> && is_constant_index_v<rhs_t>) {
                using left_t  = typename lhs_t::value_type;
                using right_t = typename rhs_t::value_type;
                return cast(as_value_v<left_t>, as_value_v<right_t>);
            } else if constexpr (is_index_v<lhs_t> && is_index_v<rhs_t>) {
                // simply select signed and non constant if possible
                auto signed_   = cast(make_non_constant(as_value_v<lhs_t>), make_non_constant(as_value_v<rhs_t>));
                auto non_const = make_non_constant(signed_);
                return non_const;
            } else {
                return as_value_v<error::PROMOTE_INDEX_UNSUPPORTED>;
            }
        }

        static constexpr auto vtype = [](){
            using types = type_list<rest_t...>;
            constexpr auto init_ = binary_vtype(as_value_v<remove_cvref_t<first_t>>,as_value_v<remove_cvref_t<second_t>>);
            return template_reduce<sizeof...(rest_t)>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using type_i = remove_cvref_t<at_t<types,i>>;
                return binary_vtype(init,as_value_v<type_i>);
            }, init_);
        }();
        using type = type_t<decltype(vtype)>;
    }; // promote_index

    template <typename lhs_t, typename rhs_t, typename...rest_t>
    using promote_index_t = type_t<promote_index<lhs_t,rhs_t,rest_t...>>;

    namespace error
    {
        // default type (error-type) for get_index_type
        struct GET_INDEX_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename array_t, typename=void>
    struct get_index_type
    {
        using type = error::GET_INDEX_TYPE_UNSUPPORTED;
    }; // get_index_type

    template <typename array_t>
    using get_index_type_t = type_t<get_index_type<array_t>>;

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