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
    namespace detail {

        template <typename T, typename R=void>
        using enable_if_tuple_t = std::enable_if_t<meta::is_tuple_v<T>,R>;

        /**
         * @brief find type T in tuple Tuple, return tuple element index
         * https://devblogs.microsoft.com/oldnewthing/20200629-00/?p=103910#comment-136848
         * 
         * @tparam index current search index
         * @tparam TypeCompare=std::is_same type comparator 
         *      TypeCompare<T,tuple_element_t<index,Tuple>>::value should be valid
         * @tparam T type to find
         * @tparam Tuple tuple to be searched
         * @return constexpr int matched index if success, tuple size else
         * @todo make this consteval in c++20
         */
        template <size_t index, template<typename,typename> typename TypeCompare=std::is_same, typename T, typename Tuple>
        constexpr int tuple_element_index(T=T{}, Tuple=Tuple{})
        {
            /* reached max tuple element, means failed to find matched type */
            if constexpr (index == std::tuple_size_v<Tuple>)
                return index;
            /* if we find matched T, return index, else increment index and retry */
            else 
                return TypeCompare<T,std::tuple_element_t<index, Tuple>>::value ?
                    index : tuple_element_index<index+1,TypeCompare>(T{},Tuple{});
        }

        /**
         * @brief overloaded version of tuple_element_index 
         * where arguments only supported via template parameters
         * and differs in template parameters order
         * to supports non-literal type
         * 
         * @tparam index 
         * @tparam T 
         * @tparam Tuple 
         * @tparam TypeCompare=std::is_same 
         * @return constexpr int 
         */
        template <size_t index, typename T, typename Tuple, template<typename,typename> typename TypeCompare=std::is_same>
        constexpr int tuple_element_index()
        {
            /* reached max tuple element, means failed to find matched type */
            if constexpr (index == std::tuple_size_v<Tuple>)
                return index;
            /* if we find matched T, return index, else increment index and retry */
            else 
                return TypeCompare<T,std::tuple_element_t<index, Tuple>>::value ?
                    index : tuple_element_index<index+1,T,Tuple,TypeCompare>();
        }
    } // namespace detail

    /** @defgroup meta
    * Collections of metafunctions used accross the library
    * @{
    */

    /**
     * @brief find type T in tuple Tuple, return tuple element index
     * https://devblogs.microsoft.com/oldnewthing/20200629-00/?p=103910#comment-136848
     * @tparam TypeCompare=std::is_same type comparator
     *      TypeCompare<T,tuple_element_t<index,Tuple>>::value should be valid
     * @tparam T type to find
     * @tparam Tuple tupe to be searched
     * @return constexpr int matched index if success, tuple size else
     * @todo make this consteval in c++20
     */
    template <template<typename,typename> typename TypeCompare=std::is_same, typename T, typename Tuple>
    constexpr int tuple_element_index(T=T{}, Tuple=Tuple{}) {
        /* start search from 0 */
        return detail::tuple_element_index<0,TypeCompare>(T{},Tuple{});
    }

    /**
     * @brief overloaded version of tuple_element_index,
     * differs in template parameter order and only supports
     * passing parameter type via template parameter
     * to supports non-literal type
     * 
     * @tparam T 
     * @tparam Tuple 
     * @tparam TypeCompare=std::is_same type comparator
     *      TypeCompare<T,tuple_element_t<index,Tuple>>::value should be valid
     * @return constexpr int 
     * @todo make this consteval in c++20
     */
    template <typename T, typename Tuple, template<typename,typename> typename TypeCompare=std::is_same>
    constexpr int tuple_element_index() {
        /* start search from 0 */
        return detail::tuple_element_index<0,T,Tuple,TypeCompare>();
    }

    /**
     * @brief check if type T is found in tuple Tuple
     * 
     * @tparam TypeCompare=std::is_same 
     * @tparam T type to find
     * @tparam Tuple tuple to be searched
     * @return true type T is in tuple Tuple
     * @return false type T is not in tuple Tuple
     * @todo make this consteval in c++20
     */
    template <template<typename,typename> typename TypeCompare=std::is_same, typename T, typename Tuple>
    constexpr auto type_in_tuple(T=T{}, Tuple=Tuple{}) -> detail::enable_if_tuple_t<Tuple,bool>
    {
        return tuple_element_index<TypeCompare>(T{},Tuple{}) < std::tuple_size_v<Tuple>;
    }

    /**
     * @brief overloaded version of type_in_tuple,
     * differs in template parameter order and only supports
     * passing parameter type via template parameter 
     * to supports non-literal type
     * 
     * @tparam T 
     * @tparam Tuple 
     * @tparam TypeCompare=std::is_same 
     * @return true 
     * @return false
     * @todo make this consteval in c++20 
     */
    template <typename T, typename Tuple, template<typename,typename> typename TypeCompare=std::is_same>
    constexpr auto type_in_tuple() -> detail::enable_if_tuple_t<Tuple,bool>
    {
        return tuple_element_index<T,Tuple,TypeCompare>() < std::tuple_size_v<Tuple>;
    }

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
     * @brief overloaded version of transform_bounded_array for T[N]
     * 
     * @tparam T element type
     * @tparam N number of elements
     */
    template <typename T, std::size_t N>
    struct transform_bounded_array<T[N]>
    {
        using value_type = typename transform_bounded_array<remove_cvref_t<T>>::type;
        using type = std::array<remove_cvref_t<value_type>,N>;
    };

    /**
     * @brief helper alias template to transform (bounded) raw array to std::array
     * 
     * @tparam T (bounded) array
     */
    template <typename T>
    using transform_bounded_array_t = typename transform_bounded_array<T>::type;

    /**
     * @brief get T::value_type as member type or type == T
     * 
     * @tparam T type to transform
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_value_type_or_same
    {
        using type = T;
    };

    /**
     * @brief specialization when T actually has value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct get_value_type_or_same<T,std::enable_if_t<meta::has_value_type_v<T>>>
    {
        using type = typename T::value_type;
    };

    /**
     * @brief helper alias template to transform get T::value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    using get_value_type_or_same_t = typename get_value_type_or_same<T>::type;

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
        using origin_tparams = void;
        /**
         * @brief define resulting type as void, so that
         * replace_template_parameter_t still well-formed
         * while error handling can be deferred to the caller
         * hence gives much more context
         */
        using type = void;
    };

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
        template <typename T, typename U, typename=void>
        struct merge_helper
        {
            using type = std::tuple<T,U>;
        }; // merge_helper

        template <template<typename...>typename TT, typename...Ts, template<typename...>typename TU, typename...Us>
        struct merge_helper<TT<Ts...>,TU<Us...>>
        {
            using type = TT<Ts...,Us...>;
        }; // merge_helper

        template <template<typename...>typename TT, typename...Ts, typename U>
        struct merge_helper<TT<Ts...>,U>
        {
            using type = TT<Ts...,U>;
        }; // merge_helper

        template <typename T, template<typename...>typename TU, typename...Us>
        struct merge_helper<T,TU<Us...>>
        {
            using type = TU<T,Us...>;
        }; // merge_helper

    } // namespace detail

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
        template <typename T, auto I, typename=void>
        struct split_at_helper
        {
            using first  = void;
            using second = void;
            using type = T;
        }; // split_at_helper

        template <template<typename...>typename TT, typename T, typename...Ts>
        struct split_at_helper<TT<T,Ts...>,1>
        {
            using first  = TT<T>;
            using second = TT<Ts...>;
            using type   = std::pair<first,second>;
        }; // split_at_helper

        template <template<typename...>typename TT, typename T, typename...Ts, auto I>
        struct split_at_helper<TT<T,Ts...>,I,std::enable_if_t<(I>1)>>
        {
            using rest   = split_at_helper<TT<Ts...>,I-1>;
            using first  = merge_t<TT<T>,first_t<rest>>;
            using second = second_t<rest>;
            using type   = std::pair<first,second>;
        }; // split_at_helper
    } // namespace detail

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

    namespace detail
    {
        template <typename T, typename U, auto I, typename=void>
        struct replace_at_helper
        {
            using type = void;
        }; // replace_at_helper

        template <template<typename...>typename TT, typename T, typename U, typename...Ts>
        struct replace_at_helper<TT<T,Ts...>,U,0>
        {
            using type = TT<U,Ts...>;
        }; // replace_at_helper

        template <template<typename...>typename TT, typename U, typename...Ts, auto I>
        struct replace_at_helper<TT<Ts...>,U,I>
        {
            using type_list  = TT<Ts...>;
            // split at can results on same type
            using split_type = split_at<type_list,I>;

            // @note cant work since need to 
            // check for first and second type to be not void

            // using first    = first_t<split_type>;
            // using second   = second_t<split_type>;
            // using replaced = type_t<replace_at_helper<second,U,0>>;
            // using type     = merge_t<first,replaced>;

            template <typename split_type>
            static constexpr auto get_type()
            {
                // first and second can be void
                using first    = first_t<split_type>;
                using second   = second_t<split_type>;
                // assuming replaced type is default constructible
                if constexpr (!std::is_void_v<first>) {
                    using replaced = type_t<replace_at_helper<second,U,0>>;
                    using type = merge_t<first,replaced>;
                    return type{};
                }
                else {
                    using replaced = replace_at_helper<type_t<split_type>,U,0>;
                    return type_t<replaced>{};
                }
            } // get_type
            using type = decltype(get_type<split_type>());
        }; // replace_at_helper
    } // namespace detail

    /**
     * @brief metafunction to replace the type of type-list T at index I with U.
     *
     * On failed specialization (default case) member type `type` is defined as `void`,
     * otherwise it hold the replaced type-list.
     * 
     * @tparam T type-list to replace
     * @tparam U replacement type
     * @tparam I replacement index
     * @tparam typename 
     */
    template <typename T, typename U, auto I, typename=void>
    struct replace_at
    {
        using type = typename detail::replace_at_helper<T,U,I>::type;
    }; // replace_at

    /**
     * @brief helper alias template for replace_at
     * 
     * @tparam T type-list to replace
     * @tparam U replacement type
     * @tparam I replacement index
     */
    template <typename T, typename U, auto I>
    using replace_at_t = typename replace_at<T,U,I>::type;

    /*
    TODO: consider to provide specialization for replace_template_parameter, that accepts
        - T<typename,auto..>, 
        - T<auto,typename...>, etc.
    */

    /**
     * @brief metafunction to resize fixed vector.
     * 
     * @tparam T fixed vector type to be resized.
     * @tparam N new size.
     */
    template <typename T, auto N, typename=void>
    struct resize_fixed_vector
    {
        /* pack new size as type instead of non-type template param */
        using new_size = std::integral_constant<size_t,N>;
        using type = replace_template_parameter_t<T,new_size>;
    };

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

    /**
     * @brief helper alias template to resize metafunction to resize fixed vector.
     * 
     * @tparam T fixed vector type to be resized.
     * @tparam N new size.
     */
    template <typename T, auto N>
    using resize_fixed_vector_t = typename resize_fixed_vector<T,N>::type;

    /**
     * @brief given fixed matrix T, return new type of fixed matrix with Rows and Cols.
     * Default implementation define type as void.
     * 
     * @tparam T 
     * @tparam Rows 
     * @tparam Cols 
     */
    template <typename T, auto Rows, auto Cols>
    struct resize_fixed_matrix
    {
        using type = void;
    };

    /**
     * @brief specialization of metafunction resize_fixed_matrix for nested std::array
     * 
     * @tparam T value type
     * @tparam M number of row of origin type
     * @tparam N number of column of origin type
     * @tparam Rows new desired row size
     * @tparam Cols new desired column size
     */
    template <typename T, auto M, auto N, auto Rows, auto Cols>
    struct resize_fixed_matrix<std::array<std::array<T,N>,M>,Rows,Cols>
    {
        using type = std::array<std::array<T,Cols>,Rows>;
    };

    /**
     * @brief specialization of metafunction resize_fixed_matrix for nested raw array
     * 
     * @tparam T value type
     * @tparam M number of row of origin type
     * @tparam N number of column of origin type
     * @tparam Rows new desired row size
     * @tparam Cols new desired column size
     */
    template <typename T, auto M, auto N, auto Rows, auto Cols>
    struct resize_fixed_matrix<T[M][N],Rows,Cols>
    {
        using type = std::array<std::array<T,Cols>,Rows>;
    };

    /**
     * @brief helper alias template to get the resulting type of metafunction resize_fixed_matrix
     * 
     * @tparam T origin type
     * @tparam Rows new desired row size
     * @tparam Cols new desired column size
     * @see nmtools::meta::resize_fixed_matrix
     */
    template <typename T, auto Rows, auto Cols>
    using resize_fixed_matrix_t = typename resize_fixed_matrix<T,Rows,Cols>::type;

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

    /**
     * @brief metafunction to extract template paramters.
     * Given type T, return its template parameters as tuple,
     * e.g. given T<Params...>, return std::tuple<Params...>{}.
     * 
     * @tparam T type which its template parameters are to be extracted
     * @tparam Params template parameters of T, automatically deduced.
     * @return constexpr auto tuple of template parameters of T.
     */
    template <template<typename...> typename T, typename...Params>
    constexpr auto extract_template_parameters(const T<Params...>)
    {
        /* TODO: use consteval instead */
        /* template parameter packs must be the last template parameter,
            can't have typename=void at the end, deduce using function instead */
        /* assuming each type from Rest... can be instantiated this way */
        return std::tuple<Params...>{};
    }

    /**
     * @brief specialization of extract_template_parameters
     * for std::array since it accepts template parameters that is not a type
     * (size_t N as its element size), N will be packed as integral_constant
     * so that its value can be treated as type.
     * 
     * @tparam T value_type of std::array, automatically deduced.
     * @tparam N element size of std::array, automatically deduced.
     * @return constexpr auto tuple<T,integral_constant<size_t,N>>;
     */
    template <typename T, size_t N>
    constexpr auto extract_template_parameters(const std::array<T,N>)
    {
        return std::tuple<T,std::integral_constant<size_t,N>>{};
    }

    /**
     * @brief helper alias template for extract_template_parameters.
     * 
     * @tparam T type which its template parameters are to be extracted.
     */
    template <typename T>
    using extract_template_parameters_t = decltype(extract_template_parameters(std::declval<T>()));

    template <typename T>
    struct pop_first
    {
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
     * @brief add U to typelist (tuple) T.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T tuple to be added with U
     * @tparam U type to be added to T
     */
    template <typename T, typename U>
    struct type_push_back
    {
        template <typename...Ts>
        static constexpr auto _type_push_back(std::tuple<Ts...>)
        {
            using type = std::tuple<Ts...,U>;
            return type{};
        }

        using type = decltype(_type_push_back(std::declval<T>()));
    }; // push

    /**
     * @brief helper alias template to add U to typelist (tuple) T.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T tuple to be added with U
     * @tparam U type to be added to T
     */
    template <typename T, typename U>
    using type_push_back_t = typename type_push_back<T,U>::type;

    /**
     * @brief reverse the element of typelist (tuple) T.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T tuple to be reversed
     */
    template <typename T>
    struct type_reverse
    {
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
     * @brief metafunction to select resizeable matrix type
     * 
     * @tparam A 
     * @tparam B 
     * @tparam typename=void 
     * @TODO: rename this to select_resizeable_container to avoid confusion
     */
    template <typename A, typename B, typename=void>
    struct select_resizeable_mat {};

    /**
     * @brief specialization of select_resizeable_mat when both A & B is resizeable
     * will have member type `type` that is resizeable
     * 
     * @tparam A 
     * @tparam B 
     * @TODO: rename this to select_resizeable_container to avoid confusion
     */
    template <typename A, typename B>
    struct select_resizeable_mat<A,B,
        std::enable_if_t<meta::is_resizeable_v<A> && meta::is_resizeable_v<B> >
    >
    {
        using type = A;
    };

    /**
     * @brief specialization of select_resizeable_mat when A is resizeable and B is not
     * will have member type `type` that is resizeable
     * 
     * @tparam A 
     * @tparam B 
     * @TODO: rename this to select_resizeable_container to avoid confusion
     */
    template <typename A, typename B>
    struct select_resizeable_mat<A,B,
        std::enable_if_t<meta::is_resizeable_v<A> && !meta::is_resizeable_v<B> >
    >
    {
        using type = A;
    };

    /**
     * @brief specialization of select_resizeable_mat when B is resizeable and A is not
     * will have member type `type` that is resizeable
     * 
     * @tparam A 
     * @tparam B 
     * @TODO: rename this to select_resizeable_container to avoid confusion
     */
    template <typename A, typename B>
    struct select_resizeable_mat<A,B,
        std::enable_if_t<meta::is_resizeable_v<B> && !meta::is_resizeable_v<A> >
    >
    {
        using type = B;
    };

    /**
     * @brief helper alias template to select resizeable mat
     * 
     * @tparam A 
     * @tparam B 
     * @TODO: rename this to select_resizeable_container to avoid confusion
     */
    template <typename A, typename B>
    using select_resizeable_mat_t = typename select_resizeable_mat<A,B>::type;

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

    template <typename A, typename B, typename=void>
    struct select_resizeable_matrix {};

    template <typename A, typename B>
    struct select_resizeable_matrix<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array2d */
            meta::is_array2d_v<A> && meta::is_array2d_v<B> &&
            meta::is_resizeable_v<A> && meta::is_resizeable_v<B>
        >
    >{
        /* when both A and B is resizeable, select A */
        using type = A;
    };

    template <typename A, typename B>
    struct select_resizeable_matrix<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array2d */
            meta::is_array2d_v<A> && meta::is_array2d_v<B> &&
            !meta::is_resizeable_v<A> && meta::is_resizeable_v<B>
        >
    >{
        using type = B;
    };

    template <typename A, typename B>
    struct select_resizeable_matrix<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array2d */
            meta::is_array2d_v<A> && meta::is_array2d_v<B> &&
            meta::is_resizeable_v<A> && !meta::is_resizeable_v<B>
        >
    >{
        using type = A;
    };

    template <typename A, typename B>
    using select_resizeable_matrix_t = typename select_resizeable_matrix<A,B>::type;

    /* select resizeable vector */

    template <typename A, typename B, typename=void>
    struct select_resizeable_vector {};

    template <typename A, typename B>
    struct select_resizeable_vector<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array1d */
            meta::is_array1d_v<A> && meta::is_array1d_v<B> &&
            meta::is_resizeable_v<A> && meta::is_resizeable_v<B>
        >
    >{
        /* when both A and B is resizeable, select A */
        using type = A;
    };

    template <typename A, typename B>
    struct select_resizeable_vector<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array1d */
            meta::is_array1d_v<A> && meta::is_array1d_v<B> &&
            !meta::is_resizeable_v<A> && meta::is_resizeable_v<B>
        >
    >{
        using type = B;
    };

    template <typename A, typename B>
    struct select_resizeable_vector<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array1d */
            meta::is_array1d_v<A> && meta::is_array1d_v<B> &&
            meta::is_resizeable_v<A> && !meta::is_resizeable_v<B>
        >
    >{
        using type = A;
    };

    template <typename A, typename B>
    using select_resizeable_vector_t = typename select_resizeable_vector<A,B>::type;
    
    /**
     * @brief helper alias template to add specialization 
     * (which check if T is rezieable) to overload set
     * 
     * @tparam T type to check
     */
    template <typename T>
    using enable_if_resizeable_t = std::enable_if_t<meta::is_resizeable_v<T>>;

    /**
     * @brief helper alias template to add specialization
     * (which check if T has tuple size) to overload set
     * 
     * @tparam T type to check
     */
    template <typename T>
    using enable_if_fixed_t = std::enable_if_t<meta::has_tuple_size_v<T>>;

    /**
     * @brief helper alias template to remove specialization
     * (which check if T is resizeable) from overload set
     * 
     * @tparam T type to check
     */
    template <typename T>
    using disable_if_resizeable_t = std::enable_if_t<!meta::is_resizeable_v<T>>;

    /**
     * @brief helper alias template to remove specialization
     * (which check if T has tuple size) from overload set
     * 
     * @tparam T type to check
     */
    template <typename T>
    using disable_if_fixed_t = std::enable_if_t<!meta::has_tuple_size_v<T>>;

    /**
     * @brief given type A, B, C, select A (has type = A) 
     * if A is resizeable (satisfy is_resizeable_v) and B is not resizeable;
     * select B if B is resizeable and A is not, select C 
     * 
     * @tparam A type to check
     * @tparam B type to check
     * @tparam C default type when specialization fails
     * @tparam typename=void 
     */
    template <typename A, typename B, typename C, typename=void>
    struct select_resizeable
    {
        /**
         * @brief default implementation to select resizeable.
         *
         * Implemented as static member function instead of clunky sfinae.
         * Assuming the type(s) has default initializaton.
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (meta::is_resizeable_v<A> && !meta::is_resizeable_v<B>)
                return A{};
            else if constexpr (!meta::is_resizeable_v<A> && meta::is_resizeable_v<B>)
                return B{};
            else if constexpr (meta::is_resizeable_v<A> && meta::is_resizeable_v<B>)
                return A{};
            else return C{};
        } // _get()

        using type = decltype(_get());
    }; // select_resizeable

    /**
     * @brief helper alias template for select_resizeable
     * 
     * @tparam A type to check
     * @tparam B type to check
     * @tparam C default type
     */
    template <typename A, typename B, typename C>
    using select_resizeable_t = typename select_resizeable<A,B,C>::type;


    template <typename A, typename B, typename C, typename=void>
    struct select_fixed
    {
        /**
         * @brief default implementation to select fixed.
         *
         * Implemented as static member function instead of clunky sfinae.
         * Assuming the type(s) has default initializaton.
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (!meta::is_resizeable_v<A> && meta::is_resizeable_v<B>)
                return A{};
            else if constexpr (meta::is_resizeable_v<A> && !meta::is_resizeable_v<B>)
                return B{};
            else if constexpr (!meta::is_resizeable_v<A> && !meta::is_resizeable_v<B>)
                return A{};
            else return C{};
        }
        using type = decltype(_get());
    }; // select_fixed

    template <typename A, typename B, typename C>
    using select_fixed_t = typename select_fixed<A,B,C>::type;

    /**
     * @brief get the velue type of container
     * 
     * @tparam T type to check
     * @tparam typename=void sfinae point
     */
    template <typename T, typename=void>
    struct get_container_value_type
    {
        /**
         * @brief helper function declaration to get the return type of U(i).
         *
         * This function is not intended to be called, only to deduce type
         * without requiring U to be initialized.
         * 
         * @tparam U 
         * @tparam size_type 
         * @return decltype(std::declval<U>().operator()(std::declval<size_type>())) 
         */
        template <typename U, typename size_type>
        static constexpr auto _func()
            -> decltype(std::declval<U>().operator()(std::declval<size_type>()));
        /**
         * @brief helper function declaration to get the return type of U[i].
         * 
         * @tparam U 
         * @tparam size_type 
         * @return decltype(std::declval<U>().operator[](std::declval<size_type>())) 
         */
        template <typename U, typename size_type>
        static constexpr auto _bracket()
            -> decltype(std::declval<U>().operator[](std::declval<size_type>()));
        /**
         * @brief helper function declaration to get the return type of U(i).
         * 
         * @tparam U 
         * @tparam size_type 
         * @return decltype(std::declval<U>().at(std::declval<size_type>())) 
         */
        template <typename U, typename size_type>
        static constexpr auto _at()
            -> decltype(std::declval<U>().at(std::declval<size_type>()));
        /**
         * @brief default implementation to get container value_type.
         *
         * Implemented as static member function instead of clunky sfinae.
         * Assuming the element type(s) has default initializaton.
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (meta::has_value_type_v<T>) {
                using type = typename T::value_type;
                return meta::remove_cvref_t<type>{};
            }
            else if constexpr (std::is_array_v<T>) {
                using type = std::remove_all_extents_t<T>;
                return meta::remove_cvref_t<type>{};
            }
            else if constexpr (meta::has_funcnd_v<T,size_t>) {
                using type = decltype(_func<T,size_t>());
                return meta::remove_cvref_t<type>{};
            }
            else if constexpr (meta::has_bracketnd_v<T,size_t>) {
                using type = decltype(_bracket<T,size_t>());
                return meta::remove_cvref_t<type>{};
            }
            else if constexpr (meta::has_atnd_v<T,size_t>) {
                using type = decltype(_at<T,size_t>());
                return meta::remove_cvref_t<type>{};
            }
            else return detail::fail_t{};
        } // _get()
        using type = meta::remove_cvref_t<detail::fail_to_void_t<decltype(_get())>>;
    }; // get_container_value_type

    /**
     * @brief helper alias template to get the value type of container T
     * 
     * @tparam T 
     */
    template <typename T>
    using get_container_value_type_t = typename get_container_value_type<T>::type;

    /**
     * @brief specialization of enable_if, to improve readibility,
     * for cases where T::value_type is well-formed.
     * used by get_matrix_value_type
     * 
     * @tparam T type to test
     */
    template <typename T>
    using enable_if_has_value_type = std::enable_if<meta::has_value_type_v<T>>;

    /**
     * @brief helper alias template for enable_if_has_value_type.
     * 
     * @tparam T type to test
     */
    template <typename T>
    using enable_if_has_value_type_t = typename enable_if_has_value_type<T>::type;

    /**
     * @brief specialization of enable_if to disable nested 2d array specialization.
     * used by get_matrix_value_type.
     * 
     * @tparam T type to test
     */
    template <typename T>
    using disable_if_nested_array2d = std::enable_if<!meta::is_nested_array2d_v<T>>;

    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T>
    using disable_if_nested_array2d_t = typename disable_if_nested_array2d<T>::type;

    /**
     * @brief metafunction to get matrix element type, has public
     * member type `type` (T::value_type or deduced from experession)
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_matrix_value_type
    {
        /* TODO: consider to set value_type to void 
            to allow easier to set error message with context */
        /* assuming nested vector */
        /* TODO: consider to use nmtools::at from nmtools/array/utility.hpp for generic case */
        /* TODO: use std::remove_cvref_t when possible */
        using type = meta::remove_cvref_t<decltype(std::declval<T>()[0][0])>;
    };

    /**
     * @brief specialization of metafunction get_matrix_value_type
     * when T actually has public member type value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct get_matrix_value_type<T,
        /* has value type but not nested array (which also has value_type) */
        std::void_t<enable_if_has_value_type_t<T>,disable_if_nested_array2d_t<T>>
    >
    {
        using type = typename T::value_type;
    };
    
    /**
     * @brief helper alias template for metafunction get_matrix_value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    using get_matrix_value_type_t = typename get_matrix_value_type<T>::type;

    /**
     * @brief alias for get_container_value_type
     * 
     * @tparam T type to test
     */
    template <typename T>
    struct get_vector_value_type : get_container_value_type<T> {};

    /**
     * @brief helper alias template for get_vector_value_type
     * 
     * @tparam T type to test
     */
    template <typename T>
    using get_vector_value_type_t = typename get_vector_value_type<T>::type;

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
        using type = T;
    }; // bit_reference_to_bool

    template <typename T>
    struct bit_reference_to_bool<T,std::enable_if_t<is_bit_reference_v<T>>>
    {
        using type = bool;
    }; // bit_reference_to_bool

    template <typename T>
    using bit_reference_to_bool_t = type_t<bit_reference_to_bool<T>>;

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
        static inline constexpr auto _get()
        {
            /**
             * @note since is_array1d_v and is_array2d_v may not be mutually exclusive,
             * it is hard to use std::enable_if / std::void_t to specialize,
             * hence using helper function instead
             * to deduce the resulting element type.
             * 
             * @todo make this fn consteval
             * @note using detail::void_to_fail_t since void can't be instantiated, reversed back to void at the caller site.
             */
            if constexpr (std::is_array_v<T>) {
                using type = std::remove_all_extents_t<T>;
                return detail::void_to_fail_t<type>{};
            }
            else if constexpr (meta::nested_array_dim_v<T> > 0) {
                using element_t = remove_all_nested_array_dim_t<T>;
                // note that remove_all_nested_array_dim_t using expression to deduce the type
                // causing vector<bool> deduced to std::_Bit_reference instead of bool
                using type = bit_reference_to_bool_t<element_t>;
                return detail::void_to_fail_t<type>{};
            }
            else if constexpr (meta::is_array2d_v<T>) {
                using type = get_matrix_value_type_t<T>;
                return detail::void_to_fail_t<type>{};
            }
            else if constexpr (meta::is_array1d_v<T>) {
                using type = get_vector_value_type_t<T>;
                return detail::void_to_fail_t<type>{};
            }
            // ndarray is more generic
            else if constexpr (meta::is_ndarray_v<T>) {
                using type = get_ndarray_value_type_t<T>;
                return detail::void_to_fail_t<type>{};
            }
            else if constexpr (meta::is_integral_constant_v<T>)
                return typename T::value_type{};
            else if constexpr (meta::has_value_type_v<T>) {
                using type = typename T::value_type;
                if constexpr (std::is_arithmetic_v<type>)
                    return type{};
                else
                    return typename get_element_type<type>::type{};
            }
            else if constexpr (std::is_arithmetic_v<T>)
                return T{};
            else return detail::fail_t{};
        }
        using type = detail::fail_to_void_t<decltype(_get())>;
    }; // get_element_type

    /**
     * @brief helper alias template for get_element_type
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using get_element_type_t = typename get_element_type<T>::type;

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

    namespace detail
    {
        /**
         * @brief helper metafunction for replace_element_type
         *
         * return void type if no specialization exists
         * 
         * @tparam T type in which its element type to be replaced
         * @tparam U substitute to elemen type  of T
         * @tparam typename 
         */
        template <typename T, typename U, typename=void>
        struct replace_element_type_helper
        {
            using type = void;
        };

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
     * this metafunction doesnt need to provide specialization hence it will be easier
     * to specialize on custom types.
     * 
     * @tparam T type in which its element type to be replaced
     * @tparam U substitute to elemen type  of T
     * @tparam typename sfinae point
     * @see detail::replace_element_type_helper
     */
    template <typename T, typename U, typename=void>
    struct replace_element_type
    {
        using type = type_t<detail::replace_element_type_helper<T,U>>;
    }; // replace_element_type

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

    /**
     * @brief helper alias template for replace element type
     * 
     * @tparam T type in which its element type to be replaced
     * @tparam U substitute to elemen type  of T
     */
    template <typename T, typename U>
    using replace_element_type_t = typename replace_element_type<T,U>::type;

    /**
     * @brief metafunction to make vector with new size N from original type T
     * default implementation will try to replace template parameter of T with new size,
     * may be specialized with custom type implementation.
     * 
     * @tparam T original fixed-size vector with fixed compile time size
     * @tparam N new desired size
     * @tparam typename=void 
     */
    template <typename T, size_t N, typename=void>
    struct make_zeros_vector
    {
        using value_t   = meta::remove_cvref_t<typename T::value_type>;
        using new_size  = std::integral_constant<size_t,N>;
        using new_array = replace_template_parameter<T,value_t,new_size>;

        /* final type */
        using type = typename new_array::type;
    };

    /**
     * @brief helper alias template to make vector with new size N from original type T
     * 
     * @tparam T original fixed-size vector with fixed compile time size
     * @tparam N new desired size
     */
    template <typename T, size_t N>
    using make_zeros_vector_t = typename make_zeros_vector<T,N>::type;

    /**
     * @brief metafunction to make zeros matrix with new Rows and Cols
     * default implementation assumes nested array-like
     * and will try to replace its template parameters with new size.
     * 
     * @tparam T original fixed-size matrix with fixed compile-time size
     * @tparam Rows new desired rows
     * @tparam Cols new desired cols
     * @tparam typename=void 
     */
    template <typename T, size_t Rows, size_t Cols, typename=void>
    struct make_zeros_matrix
    {
        /* NOTE: assuming nested array */
        using row_t = T;
        using col_t = meta::remove_cvref_t<typename row_t::value_type>;
        using element_t = meta::remove_cvref_t<typename col_t::value_type>;
        using new_col_size = std::integral_constant<size_t,Cols>;
        using new_row_size = std::integral_constant<size_t,Rows>;
        using new_col_t = replace_template_parameter<col_t,element_t,new_col_size>;
        using new_row_t = replace_template_parameter<row_t,typename new_col_t::type,new_row_size>;

        /* final type, implicitly assumed that it has constructor that fills it elements with zero */
        using type = typename new_row_t::type;

        /* TODO: consider to provide operator() that actually return zeros matrix */
    };

    /**
     * @brief helper alias template for make_zeros_matrix.
     * 
     * @tparam T original fixed-size matrix with fixed compile-time size
     * @tparam Rows new desired rows
     * @tparam Cols new desired cols
     */
    template <typename T, size_t Rows, size_t Cols>
    using make_zeros_matrix_t = typename make_zeros_matrix<T,Rows,Cols>::type;
    
    /**
     * @brief make matrix type for outer product operations.
     * 
     * @tparam V1 lhs vector type
     * @tparam V2 rhs vector type
     * @tparam typename=void 
     */
    template <typename V1, typename V2, typename=void>
    struct make_outer_matrix
    {
        using type = detail::fail_t;
    }; // make_outer_matrix

    /**
     * @brief specialization of make_outer_matrix for std::array.
     * 
     * @tparam row_t lhs vector value_type
     * @tparam col_t lhs vector value_type
     * @tparam M 
     * @tparam N 
     */
    template <typename row_t, typename col_t, size_t M, size_t N>
    struct make_outer_matrix<std::array<row_t,M>,std::array<col_t,N>>
    {
        using common_t = std::common_type_t<row_t,col_t>;
        using type = std::array<std::array<common_t,N>,M>;
    };

    /**
     * @brief helper alias template for make_outer_matrix.
     * example: https://godbolt.org/z/zMMosG
     * 
     * @tparam V1 lhs vector type
     * @tparam V2 rhs vector type
     */
    template <typename V1, typename V2>
    using make_outer_matrix_t = typename make_outer_matrix<V1,V2>::type;

    /**
     * @brief metafunction to deduce type of column operation for matrix.
     * 
     * @tparam T matrix type
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_column_type
    {
        using type = void;
    };

    /**
     * @brief specialization of metafunction get_column_type when T
     * satifies is_nested_array2d and has_value_type traits.
     * 
     * @tparam T matrix type
     */
    template <typename T>
    struct get_column_type<T,std::enable_if_t<meta::is_nested_array2d_v<T> && meta::has_value_type_v<T>>>
    {
        using type = typename T::value_type;
    };

    /**
     * @brief specialization of metafunction get_column_type when T is raw 2d array.
     * 
     * @tparam T element type of raw array, automatically deduced
     * @tparam M size of first axis (rows) of raw array, automatically deduced
     * @tparam N size of second axis (cols) of raw array, automatically deduced
     */
    template <typename T, size_t M, size_t N>
    struct get_column_type<T[M][N],void>
    {
        using value_t = meta::remove_cvref_t<T>;
        using type    = std::array<value_t,N>;
    };

    /**
     * @brief helper alias template for metafunction get_column_type
     * to deduce the type of column operation.
     * 
     * @tparam T type to check
     */
    template <typename T>
    using get_column_type_t = typename get_column_type<T>::type;

    /**
     * @brief 
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_row_type
    {
        using type = void;
    };

    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T>
    struct get_row_type<T,std::enable_if_t<meta::is_nested_array2d_v<T> && meta::has_value_type_v<T> && meta::is_dynamic_size_matrix_v<T>>>
    {
        using col_type = typename T::value_type;
        using value_type = typename col_type::value_type;
        using type = replace_template_parameter_t<T,value_type>;
    };

    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T, size_t M, size_t N>
    struct get_row_type<std::array<std::array<T,N>,M>>
    {
        using type = std::array<T,M>;
    };

    template <typename T, size_t M, size_t N>
    struct get_row_type<T[M][N]>
    {
        using type = std::array<T,M>;
    };

    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T>
    using get_row_type_t = typename get_row_type<T>::type;

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
     * @brief make nested array given template-template parameter, element type and shape.
     *
     * https://godbolt.org/z/Pdha6T
     * 
     * @tparam array_t template-template parameter in which nested array is to be constructed from, (e.g. std::array)
     * @tparam T desired element type of nested array
     * @tparam I size of first axis
     * @tparam Ns size(s) of the rest axes
     */
    template <template<typename,size_t> typename array_t, typename T, size_t I, size_t...Ns>
    struct make_nested_fixed_array
    {
        static constexpr auto _make_nested_type()
        {
            if constexpr (sizeof...(Ns)==0)
                return array_t<T,I>{};
            else {
                using type = typename make_nested_fixed_array<array_t,T,Ns...>::type;
                return array_t<type,I>{};
            }
        } // _make_nested_type()

        using type = decltype(_make_nested_type());
    };

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

    /**
     * @brief helper alias template to get the type of nested raw array.
     * 
     * @tparam T desired element type
     * @tparam N size of the first axis
     * @tparam Ns size(s) of the rest axes
     */
    template <typename T, size_t N, size_t...Ns>
    using make_nested_raw_array_t = typename make_nested_raw_array<T,N,Ns...>::type;

    /**
     * @brief helper alias template to make nested array given template-template parameter, element type and shape
     * 
     * @tparam array_t template-template parameter in which nested array is to be constructed from, (e.g. std::array)
     * @tparam T desired element type of nested array
     * @tparam I size of first axis
     * @tparam Ns size(s) of the rest axes
     */
    template <template<typename,size_t> typename array_t, typename T, size_t I, size_t...Ns>
    using make_nested_fixed_array_t = typename make_nested_fixed_array<array_t,T,I,Ns...>::type;

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

    /**
     * @brief helper function declaration to get the type of nested array.
     * 
     * @tparam T desired element type
     * @tparam N size of first axis
     * @tparam Ns size of the rest of axes
     * @return make_nested_raw_array_t<T,N,Ns...> 
     */
    template <typename T, size_t N, size_t...Ns>
    constexpr auto make_nested_array()
        -> make_nested_raw_array_t<T,N,Ns...>;

    /**
     * @brief helper function declaration to get the type of nested array.
     *
     * Note that since class template parameter can't be overloaded (https://godbolt.org/z/vrsKn5), we need helper function
     * to properly calls correct class template given its template parameter, either it is template or type tparams.
     * <a href="https://godbolt.org/z/qsno5Y">Examples</a>.:
     * @code{.cpp}
     * // same name make_nested_array can handle both template and type template-parameter
     * static_assert( std::is_same_v<decltype(make_nested_array<std::array,double,1,2>()),std::array<std::array<double,2>,1>> );
     * static_assert( std::is_same_v<decltype(make_nested_array<std::vector,double,2>()),std::vector<std::vector<double>>> );
     * @endcode
     * 
     * @tparam array_t 
     * @tparam T 
     * @tparam I 
     * @tparam Ns 
     * @return make_nested_fixed_array_t<array_t,T,I,Ns...> 
     */
    template <template<typename,size_t> typename array_t, typename T, size_t I, size_t...Ns>
    constexpr auto make_nested_array()
        -> make_nested_fixed_array_t<array_t,T,I,Ns...>;

    /**
     * @brief overloaded version of make_nested_array
     * 
     * @tparam array_t 
     * @tparam T 
     * @tparam N 
     * @return make_nested_dynamic_array_t<array_t,T,N,Args...> 
     */
    template <template<typename...> typename array_t, typename T, size_t N>
    constexpr auto make_nested_array()
        -> make_nested_dynamic_array_t<array_t,T,N>;

    namespace detail
    {
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

        template <template<typename...>typename TT, template<typename...>typename type_list, typename...Ts>
        struct apply_helper<TT,type_list<Ts...>>
        {
            #pragma clang diagnostic push
            #pragma clang diagnostic ignored "-Wunused-value"
            static constexpr auto _get()
            {
                using meta_fn_type = TT<Ts...>;
                if constexpr (meta::has_type_v<meta_fn_type>)
                    // assumning type from meta_fn_type is default constructible
                    return typename meta_fn_type::type{};
                else detail::fail_t{};
            } // _get()

            // @note this wont work
            // using type = std::conditional_t<
            //     meta::has_type_v<meta_fn_type>,
            //     typename meta_fn_type::type, void
            // >;

            // clang complain about return from _get() unused while gcc doesnt
            // an it is SHOULD BE UNUSED
            using type = detail::fail_to_void_t<decltype(_get())>;
            #pragma clang diagnostic pop
        }; // apply_helper
    } // namespace detail

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

    namespace detail
    {
        template <typename T, typename U, typename=void>
        struct gather_helper
        {
            using type = void;
        }; // gather_helper

        using std::tuple_element_t;
        using std::integer_sequence;

        template <template<typename...>typename TT, typename T, typename...Ts, typename int_t, auto I, auto...Is>
        struct gather_helper<TT<T,Ts...>,integer_sequence<int_t,I,Is...>
            , std::enable_if_t<(sizeof...(Ts)>0)&&(sizeof...(Is)>0)>
        >
        {
            // ret[i] = vec[idx[i]]
            using type_list = TT<T,Ts...>;
            using type_i = tuple_element_t<I,type_list>;
            using rest_t = type_t<gather_helper<TT<T,Ts...>,integer_sequence<int_t,Is...>>>;
            using type   = merge_t<TT<type_i>,rest_t>;
        }; // gather_helper

        template <template<typename...>typename TT, typename T, typename...Ts, typename int_t, auto I>
        struct gather_helper<TT<T,Ts...>,integer_sequence<int_t,I>>
        {
            using type_list = TT<T,Ts...>;
            using type_i = tuple_element_t<I,type_list>;
            using type = TT<type_i>;
        }; // gather_helper

        template <typename T, typename U, typename=void>
        struct scatter_helper
        {
            using type = void;
        }; // scatter_helper

        template <template<typename...>typename TT, typename T, typename T1, typename...Ts, typename int_t, auto I, auto I1, auto...Is>
        struct scatter_helper<TT<T,T1,Ts...>,integer_sequence<int_t,I,I1,Is...>
            , std::enable_if_t<(sizeof...(Ts)>0)&&(sizeof...(Is)>0)>
        >
        {
            // ret[indices[i]] = type_list[i]
            // indices[i] = I;

            // example:
            // type_list = <int,size_t,double>;
            // indices = <2,1,0>
            // i = 0; (Ts=1 - Is=1)
            // type_list[i] = int
            // rest_t = scatter(<int,size_t,double>,<1,0>)
            // i = 1; (Ts=1 - Is=0)
            // rest_t = <double,size_t,double>
            // type = replace(<double,size_t,double>,int,2)
            // type = <double,size_t,int>

            static constexpr auto i = sizeof...(Ts) - sizeof...(Is);
            using type_list   = TT<T,T1,Ts...>;
            using type_list_i = tuple_element_t<i,type_list>;
            
            using rest_indices = integer_sequence<int_t,I1,Is...>;
            using rest_t = type_t<scatter_helper<type_list,rest_indices>>;

            using type = replace_at_t<rest_t,type_list_i,I>;
        }; // scatter_helper

        template <template<typename...>typename TT, typename T, typename T1, typename...Ts, typename int_t, auto I0, auto I1>
        struct scatter_helper<TT<T,T1,Ts...>,integer_sequence<int_t,I0,I1>
            // , std::enable_if_t<(sizeof...(Ts)>0)>
        >
        {
            // ret[indices[i]] = type_list[i]
            static constexpr auto i = sizeof...(Ts);
            using type_list = TT<T,T1,Ts...>;
            using type_0 = tuple_element_t<i,type_list>;
            using type_1 = tuple_element_t<i+1,type_list>;
            using type = replace_at_t<
                replace_at_t<type_list,type_1,I1>,
                type_0, I0
            >;
        }; // scatter_helper

        // template <template<typename...>typename TT, typename T, typename T1, typename int_t, auto I0, auto I1>
        // struct scatter_helper<TT<T,T1>,integer_sequence<int_t,I0,I1>>
        // {
        //     // ret[indices[i]] = type_list[i]
        //     using type_list = TT<T,T1>;
        //     using type_0 = tuple_element_t<I0,type_list>;
        //     using type_1 = tuple_element_t<I1,type_list>;
        //     using type = TT<type_0,type_1>;
        // }; // scatter_helper
    } // namespace detail

    /**
     * @brief metafunction to perform gather op `ret[i] = vec[idx[i]]` on type-list
     * 
     * @tparam T type-list
     * @tparam U integer_sequence represents the gather indices
     */
    template <typename T, typename U>
    struct gather
    {
        using type = type_t<detail::gather_helper<T,U>>;
    }; // gather

    /**
     * @brief helper alias template for gather
     * 
     * @tparam T type-list
     * @tparam U integer_sequence represents the gather indices
     */
    template <typename T, typename U>
    using gather_t = type_t<gather<T,U>>;

    /**
     * @brief metafunction to perform scatter op `ret[idx[i]] = vec[i]` on type-list
     * 
     * @tparam T type-list
     * @tparam U integer_sequence respresenting scatter indices
     */
    template <typename T, typename U>
    struct scatter
    {
        using type = type_t<detail::scatter_helper<T,U>>;
    }; // scatter

    /**
     * @brief helper alias template for scatter
     * 
     * @tparam T type-list
     * @tparam U integer_sequence respresenting scatter indices
     */
    template <typename T, typename U>
    using scatter_t = type_t<scatter<T,U>>;

    namespace detail
    {
        template <template<typename,typename...> typename Op, typename T, typename=void>
        struct apply_reduce_helper
        {
            using type = void;
        }; // apply_reduce_helper

        template <template<typename,typename...> typename Op, template<typename...>typename TT, typename T, typename U, typename V, typename...Ts>
        struct apply_reduce_helper<Op,TT<T,U,V,Ts...>>
        {
            using tmp_type = type_t<Op<T,U>>;
            using type = type_t<apply_reduce_helper<Op,TT<tmp_type,V,Ts...>>>;
        }; //  apply_reduce_helper

        template <template<typename,typename...> typename Op, template<typename...>typename TT, typename T, typename U>
        struct apply_reduce_helper<Op,TT<T,U>>
        {
            using type = type_t<Op<T,U>>;
        }; // apply_reduce_helper
    }  // namespace detail

    template <template<typename,typename...>typename Op, typename T, typename=void>
    struct apply_reduce
    {
        using type = type_t<detail::apply_reduce_helper<Op,T>>;
    }; // reduce

    template <template<typename,typename...>typename Op, typename T>
    using apply_reduce_t = type_t<apply_reduce<Op,T>>;

    template <typename T>
    using apply_prod = apply_reduce<mul,T>;

    template <typename T>
    using apply_prod_t = type_t<apply_prod<T>>;

    template <typename T>
    using apply_sum = apply_reduce<add,T>;

    template <typename T>
    using apply_sum_t = type_t<apply_sum<T>>;

    namespace detail
    {
        template <template<typename,typename...> typename Op, typename T, typename=void>
        struct apply_accumulate_helper
        {
            using type = void;
        }; // apply_accumulate_helper

        template <template<typename,typename...> typename Op, template<typename...>typename TT, typename T>
        struct apply_accumulate_helper<Op,TT<T>>
        {
            using type = TT<T>;
        }; // apply_accumulate_helper

        template <template<typename,typename...> typename Op, template<typename...>typename TT, typename T, typename U>
        struct apply_accumulate_helper<Op,TT<T,U>>
        {
            using type_list    = TT<T,U>;
            using reduced_type = apply_reduce_t<Op,type_list>;
            using type = TT<T,reduced_type>;
        }; // apply_accumulate_helper

        // @note this specialization behaves differently on clang & gcc (8.3)
        // example case:
        // using arg_t = std::tuple<meta::ct<1>,meta::ct<3>,meta::ct<7>>;
        // using result_t = meta::apply_accumulate_t<meta::add,arg_t>;
        // using expected_t = std::tuple<meta::ct<1>,meta::ct<4>,meta::ct<11>>;
        // clang correctly produce expected type, while gcc results void for second type of expected type
        // must be something to do when recursively call the metafunction, 
        // somehow gcc cant find specialization for struct apply_accumulate_helper<Op,TT<T,U>>
        template <template<typename,typename...> typename Op, template<typename...>typename TT, typename T, typename U, typename...Ts>
        struct apply_accumulate_helper<Op,TT<T,U,Ts...>,std::enable_if_t<(sizeof...(Ts)>0)>>
        {
            static constexpr auto numel = 2 + sizeof...(Ts);
            using type_list  = TT<T,U,Ts...>;
            using split_type = split_at<type_list,numel-1>;
            using first_type = first_t<split_type>;

            using fst = type_t<apply_accumulate_helper<Op,first_type>>;
            using snd = apply_reduce_t<Op,type_list>;

            using type = merge_t<fst,snd>;
        }; // apply_accumulate_helper
    } // namespace detail

    template <template<typename,typename...> typename Op, typename T>
    struct apply_accumulate
    {
        using type = type_t<detail::apply_accumulate_helper<Op,T>>;
    }; // apply_accumulate

    template <template<typename,typename...> typename Op, typename T>
    using apply_accumulate_t = type_t<apply_accumulate<Op,T>>;

    template <typename T>
    using apply_cumprod = apply_accumulate<mul,T>;

    template <typename T>
    using apply_cumprod_t = type_t<apply_cumprod<T>>;

    /**
     * @brief helper alias template to construct (tuple of) integral_constant
     * 
     * @tparam I first constant
     * @tparam Is optional constant
     */
    template <auto I, auto...Is>
    using constant_t = std::conditional_t<
        (sizeof...(Is) > 0),
        std::tuple<
            std::integral_constant<decltype(I),I>,
            std::integral_constant<decltype(Is),Is>...
        >,
        std::integral_constant<decltype(I),I>
    >;

    /**
     * @brief helper alias template for constant_t
     * 
     * @tparam I first constant
     * @tparam Is optional constant
     */
    template <auto I, auto...Is>
    using ct = constant_t<I,Is...>;

    /**
     * @brief helper alias template to construct integer_sequence
     * 
     * @tparam I 
     * @tparam Is 
     */
    template <auto I, auto...Is>
    using sequence_t = std::integer_sequence<decltype(I),I,Is...>;

    /**
     * @brief convert compile time type constant to value.
     *
     * Default behaviour results in meta::detail::fail_t{}
     * unless specialization for type T provided
     * 
     * @tparam T type to convert
     * @tparam typename sfinae point
     */
    template <typename T, typename=void>
    struct constant_to_value
    {
        static constexpr auto value = detail::fail_t{};
    }; // constant_to_value

    template <typename T>
    constexpr inline auto constant_to_value_v = constant_to_value<T>::value;

    /**
     * @brief specialization of integral_constant for constant_to_value
     * 
     * @tparam T 
     * @tparam I 
     */
    template <typename T, auto I>
    struct constant_to_value<std::integral_constant<T,I>>
    {
        static constexpr auto value = I;
    }; // constant_to_value

    /**
     * @brief specialization of tuple of integral_constant for constant_to_value
     * 
     * @tparam I 
     * @tparam Is 
     */
    template <auto I, auto...Is>
    struct constant_to_value<
        std::tuple<
            std::integral_constant<decltype(I),I>,
            std::integral_constant<decltype(Is),Is>...
        >
    >
    {
        static constexpr auto value = std::tuple{I,Is...};
    }; // constant_to_value

    // some edge case for single element array with compile-time value
    // such array exist maybe because element type deduction is imperfect
    // or couldnt handle such case
    template <auto I, size_t N>
    struct constant_to_value< std::array<std::integral_constant<decltype(I),I>,N> >
    {
        static constexpr auto value = [](){
            using return_t = std::array<decltype(I),N>;
            auto res = return_t{};
            for (size_t i=0; i<N; i++)
                res[i] = I;
            return res;
        }();
    }; // constant_to_value

    /**
     * @brief metafunction to transform (tuple of) integral constant to integer sequence
     * 
     * @tparam T type to transform
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct constant_to_sequence
    {
        static constexpr auto value = detail::fail_t{};
        using type = void;
    }; // constant_to_sequence

    template <typename T, auto I>
    struct constant_to_sequence<std::integral_constant<T,I>>
    {
        static constexpr auto value = I;
        using type = sequence_t<I>;
    }; // constant_to_sequence

    template <auto I, auto...Is>
    struct constant_to_sequence<
        std::tuple<
            std::integral_constant<decltype(I),I>,
            std::integral_constant<decltype(Is),Is>...
        >
    >
    {
        static constexpr auto value = std::tuple{I,Is...};
        using type = sequence_t<I,Is...>;
    }; // constant_to_sequence

    /**
     * @brief helper alias template for constant_to_sequence
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using constant_to_sequence_t = type_t<constant_to_sequence<T>>;

    /**
     * @brief metafunction to transform integer sequence to (tuple of) integeral constant
     * 
     * @tparam T type to transform
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct sequence_to_constant
    {
        static constexpr auto value = detail::fail_t{};
        using type = void;
    }; // sequence_to_constant

    template <typename T, auto I, auto...Is>
    struct sequence_to_constant<std::integer_sequence<T,I,Is...>>
    {
        static constexpr auto value = std::tuple{I,Is...};
        using type = constant_t<I,Is...>;
    }; // sequence_to_constant

    /**
     * @brief helper alias template for sequence_to_constant
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using sequence_to_constant_t = type_t<sequence_to_constant<T>>;

    namespace detail
    {
        template <template<typename>typename Predicate, typename T, typename=void>
        struct filter_helper
        {
            using type = void;
        }; // filter_helper

        template <template<typename>typename Predicate, template<typename...>typename TT, typename T>
        struct filter_helper<Predicate,TT<T>>
        {
            using type = std::conditional_t<
                Predicate<T>::value, TT<T>, TT<>
            >;
        }; // filter_helper

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

    template <template<typename>typename Predicate, typename T, typename=void>
    struct filter
    {
        using type = type_t<detail::filter_helper<Predicate,T>>;
    }; // filter

    template <template<typename>typename Predicate, typename T>    
    using filter_t = type_t<filter<Predicate,T>>;

    template <typename array_t>
    struct get_element_or_common_type
    {
        using element_t = get_element_type_t<array_t>;
        using common_t  = apply_t<std::common_type,array_t>;
        using type      = std::conditional_t<
            std::is_void_v<element_t>, common_t, element_t
        >;
    }; // get_element_or_common_type

    template <typename array_t>
    using get_element_or_common_type_t = type_t<get_element_or_common_type<array_t>>;

    namespace detail
    {
        template <typename T, typename U, auto I, typename=void>
        struct insert_type
        {
            using type = void;
        }; // insert_type

        // @note clang & gcc disagree on this, see compiler notes
        // template <typename...Ts, typename U, auto I>
        // struct insert_type<std::tuple<Ts...>,U,I,std::enable_if_t<(I>=0 && I<=sizeof...(Ts))>>
        // {
        //     using tuple_t = std::tuple<Ts...>;
        //     using split_type = split_at<tuple_t,I>;
        //     using fst = first_t<split_type>;
        //     using snd = second_t<split_type>;
        //     using type = merge_t<merge_t<fst,U>,snd>;
        // }; // insert_type
        // template <typename...Ts, typename U>
        // struct insert_type<std::tuple<Ts...>,U,0>
        // {
        //     using type = std::tuple<U,Ts...>;
        // }; // insert_type

        template <typename...Ts, typename U, auto I>
        struct insert_type<std::tuple<Ts...>,U,I,std::enable_if_t<(I>0 && I<=sizeof...(Ts))>>
        {
            using tuple_t    = std::tuple<Ts...>;
            using split_type = split_at<tuple_t,I>;
            using fst  = first_t<split_type>;
            using snd  = second_t<split_type>;
            using type = merge_t<merge_t<fst,U>,snd>;
        }; // insert_type

        template <typename...Ts, typename U>
        struct insert_type<std::tuple<Ts...>,U,0>
        {
            using type = std::tuple<U,Ts...>;
        }; // insert_type
    } // namespace detail

    template <typename T, typename U, auto I, typename=void>
    struct insert_type
    {
        using type = type_t<detail::insert_type<T,U,I>>;
    }; // insert_type

    template <typename T, typename U, auto I>
    using insert_type_t = type_t<insert_type<T,U,I>>;

    /**
     * @brief tag to tell array kind preference
     * 
     */
    struct select_resizeable_kind_t {};
    /**
     * @brief tag to tell array kind preference
     * 
     */
    struct select_fixed_kind_t {};
    /**
     * @brief tag to tell array kind preference
     * 
     */
    struct select_hybrid_kind_t {};

    struct size_policy_add_t
    {
        template <typename T, typename U>
        static constexpr auto get(T t, U u)
        {
            return t + u;
        } // get
    }; // size_policy_add_t
    struct size_policy_min_t
    {
        template <typename T, typename U>
        static constexpr auto get(T t, U u)
        {
            return t < u ? t : u;
        } // get
    }; // size_policy_min_t
    struct size_policy_max_t
    {
        template <typename T, typename U>
        static constexpr auto get(T t, U u)
        {
            return t > u ? t : u;
        } // get
    }; // size_policy_max_t
    struct size_policy_lhs_t
    {
        template <typename T, typename U>
        static constexpr auto get(T t, U u)
        {
            return t;
        } // get
    }; // size_policy_lhs_t
    struct size_policy_rhs_t
    {
        template <typename T, typename U>
        static constexpr auto get(T t, U u)
        {
            return u;
        } // get
    }; // size_policy_rhs_t

    template <typename T, typename U>
    struct element_type_policy_common
    {
        using type = std::common_type_t<T,U>;
    }; // element_type_policy_common

    template <typename T, typename U>
    struct element_type_policy_lhs
    {
        using type = T;
    }; // element_type_policy_lhs

    template <typename T, typename U>
    struct element_type_policy_rhs
    {
        using type = U;
    }; // element_type_policy_rhs

    template <typename T, typename=void>
    struct tuple_to_array
    {
        using type = T;
    }; // tuple_to_array

    template <typename...Ts>
    struct tuple_to_array<std::tuple<Ts...>>
    {
        using common_t = std::common_type_t<Ts...>;
        using type = std::array<common_t,sizeof...(Ts)>;
    }; // tuple_to_array

    template <typename first, typename second>
    struct tuple_to_array<std::pair<first,second>>
    {
        using common_t = std::common_type_t<first,second>;
        using type = std::array<common_t,2>;
    }; // tuple_to_array

    template <typename T>
    using tuple_to_array_t = type_t<tuple_to_array<T>>;

    // TODO: remove
    template <typename size_policy_t, typename selection_kind_t=void,
        template<typename> typename element_predicate_t=std::is_arithmetic,
        template<typename,typename> typename element_type_policy_t=element_type_policy_common>
    struct select_array1d_t {};

    // TODO: remove
    template <typename lhs_t, typename rhs_t,
        typename size_policy_t, typename selection_kind_t,
        template<typename> typename element_predicate_t,
        template<typename,typename> typename element_type_policy_t>
    struct resolve_optype<
        std::enable_if_t<
               is_resizeable_v<lhs_t> && !is_hybrid_ndarray_v<lhs_t>
            && is_resizeable_v<rhs_t> && !is_hybrid_ndarray_v<rhs_t>
            && element_predicate_t<get_element_or_common_type_t<lhs_t>>::value
            && element_predicate_t<get_element_or_common_type_t<rhs_t>>::value
            && is_array1d_v<lhs_t> && is_array1d_v<rhs_t>
        >,
        select_array1d_t<size_policy_t,selection_kind_t,element_predicate_t,element_type_policy_t>, lhs_t, rhs_t
    >
    {
        using lhs_value_t = get_element_type_t<lhs_t>;
        using rhs_value_t = get_element_type_t<rhs_t>;
        using value_t = type_t<element_type_policy_t<lhs_value_t,rhs_value_t>>;
        using type    = replace_element_type_t<lhs_t,value_t>;
    }; // resolve_optype expand_dims_t

    // TODO: remove
    template <typename lhs_t, typename rhs_t,
        typename size_policy_t, typename selection_kind_t,
        template<typename> typename element_predicate_t,
        template<typename,typename> typename element_type_policy_t>
    struct resolve_optype<
        std::enable_if_t<
               is_resizeable_v<lhs_t> && !is_hybrid_ndarray_v<lhs_t>
            && (is_hybrid_ndarray_v<rhs_t> || has_tuple_size_v<rhs_t>)
            && element_predicate_t<get_element_or_common_type_t<lhs_t>>::value
            && element_predicate_t<get_element_or_common_type_t<rhs_t>>::value
        >,
        select_array1d_t<size_policy_t,selection_kind_t,element_predicate_t,element_type_policy_t>, lhs_t, rhs_t
    >
    {
        using lhs_value_t = get_element_or_common_type_t<lhs_t>;
        using rhs_value_t = get_element_or_common_type_t<rhs_t>;
        using value_t = type_t<element_type_policy_t<lhs_value_t,rhs_value_t>>;

        using rhs_type = tuple_to_array_t<rhs_t>;
        using a_t = std::conditional_t<
            std::is_same_v<selection_kind_t,select_resizeable_kind_t>,
            lhs_t, void
        >;
        using b_t = std::conditional_t<
            is_hybrid_ndarray_v<rhs_type> && std::is_void_v<a_t>
            && std::is_same_v<selection_kind_t,select_hybrid_kind_t>,
            rhs_type, a_t
        >;
        using c_t = std::conditional_t<
            has_tuple_size_v<rhs_type> && std::is_void_v<b_t>
            && std::is_same_v<selection_kind_t,select_fixed_kind_t>,
            rhs_type, b_t
        >;
        using type = replace_element_type_t<c_t,value_t>;
    }; // resolve_optype expand_dims_t

    // TODO: remove
    template <typename lhs_t, typename rhs_t,
        typename size_policy_t, typename selection_kind_t,
        template<typename> typename element_predicate_t,
        template<typename,typename> typename element_type_policy_t>
    struct resolve_optype<
        std::enable_if_t<
               !is_resizeable_v<lhs_t> && has_tuple_size_v<lhs_t>
            && !is_resizeable_v<rhs_t> && has_tuple_size_v<rhs_t>
            && element_predicate_t<get_element_or_common_type_t<lhs_t>>::value
            && element_predicate_t<get_element_or_common_type_t<rhs_t>>::value
        >,
        select_array1d_t<size_policy_t,selection_kind_t,element_predicate_t,element_type_policy_t>, lhs_t, rhs_t
    >
    {
        static constexpr auto M = std::tuple_size_v<lhs_t>;
        static constexpr auto N = std::tuple_size_v<rhs_t>;
        static constexpr auto n = size_policy_t::get(M,N);
        using lhs_value_t = get_element_or_common_type_t<lhs_t>;
        using rhs_value_t = get_element_or_common_type_t<rhs_t>;
        using value_t = type_t<element_type_policy_t<lhs_value_t,rhs_value_t>>;
        using type    = std::array<value_t,n>;
    }; // resolve_optype expand_dims_t

    // TODO: remove
    template <typename lhs_t, typename rhs_t,
        typename size_policy_t, typename selection_kind_t,
        template<typename> typename element_predicate_t,
        template<typename,typename> typename element_type_policy_t>
    struct resolve_optype<
        std::enable_if_t<
               !is_resizeable_v<lhs_t> && has_tuple_size_v<lhs_t>
            && (is_resizeable_v<rhs_t> || is_hybrid_ndarray_v<rhs_t>)
            && element_predicate_t<get_element_or_common_type_t<lhs_t>>::value
            && element_predicate_t<get_element_or_common_type_t<rhs_t>>::value
            && is_array1d_v<rhs_t>
        >,
        select_array1d_t<size_policy_t,selection_kind_t,element_predicate_t,element_type_policy_t>, lhs_t, rhs_t
    >
    {
        using lhs_value_t = get_element_or_common_type_t<lhs_t>;
        using rhs_value_t = get_element_or_common_type_t<rhs_t>;
        using common_t    = type_t<element_type_policy_t<lhs_value_t,rhs_value_t>>;

        static constexpr auto M = std::tuple_size_v<lhs_t>;
        static constexpr auto N = [](){
            if constexpr (has_tuple_size_v<rhs_t>)
                return std::tuple_size_v<rhs_t>;
            else if constexpr (is_hybrid_ndarray_v<rhs_t>)
                return hybrid_ndarray_max_size_v<rhs_t>;
            else return 0;
        }();
        static constexpr auto n = size_policy_t::get(M,N);

        using a_t = std::conditional_t<
            std::is_same_v<selection_kind_t,select_fixed_kind_t>,
            resize_fixed_vector_t<tuple_to_array_t<lhs_t>,n>, void
        >;
        using b_t = std::conditional_t<
            is_resizeable_v<rhs_t> && !is_hybrid_ndarray_v<rhs_t> && std::is_void_v<a_t> &&
            std::is_same_v<selection_kind_t,select_resizeable_kind_t>,
            rhs_t, a_t
        >;
        using c_t = std::conditional_t<
            is_hybrid_ndarray_v<rhs_t> && std::is_void_v<b_t> &&
            std::is_same_v<selection_kind_t,select_hybrid_kind_t>,
            resize_hybrid_ndarray_max_size_t<rhs_t, n>, b_t
        >;
        // final type
        using type = replace_element_type_t<c_t,common_t>;
    }; // resolve_optype expand_dims_t

    // TODO: remove
    template <typename lhs_t, typename rhs_t,
        typename size_policy_t, typename selection_kind_t,
        template<typename> typename element_predicate_t,
        template<typename,typename> typename element_type_policy_t>
    struct resolve_optype<
        std::enable_if_t<
               is_resizeable_v<lhs_t> && is_hybrid_ndarray_v<lhs_t>
            && is_resizeable_v<rhs_t> && is_hybrid_ndarray_v<rhs_t>
            && element_predicate_t<get_element_or_common_type_t<lhs_t>>::value
            && element_predicate_t<get_element_or_common_type_t<rhs_t>>::value
            && is_array1d_v<lhs_t> && is_array1d_v<rhs_t>
        >,
        select_array1d_t<size_policy_t,selection_kind_t,element_predicate_t,element_type_policy_t>, lhs_t, rhs_t
    >
    {
        static constexpr auto M = hybrid_ndarray_max_size_v<lhs_t>;
        static constexpr auto N = hybrid_ndarray_max_size_v<rhs_t>;
        static constexpr auto n = size_policy_t::get(M,N);
        using lhs_value_t = get_element_type_t<lhs_t>;
        using rhs_value_t = get_element_type_t<rhs_t>;
        using common_t = type_t<element_type_policy_t<lhs_value_t,rhs_value_t>>;
        using array_t  = replace_element_type_t<lhs_t,common_t>;
        using type     = resize_hybrid_ndarray_max_size_t<array_t,n>;
    }; // resolve_optype expand_dims_t

    // TODO: remove
    template <typename lhs_t, typename rhs_t,
        typename size_policy_t, typename selection_kind_t,
        template<typename> typename element_predicate_t,
        template<typename,typename> typename element_type_policy_t>
    struct resolve_optype<
        std::enable_if_t<
               is_resizeable_v<lhs_t> && is_hybrid_ndarray_v<lhs_t>
            && (
                   (is_resizeable_v<rhs_t> && !is_hybrid_ndarray_v<rhs_t>)
                || (!is_resizeable_v<rhs_t> && has_tuple_size_v<rhs_t>)
               )
            && element_predicate_t<get_element_or_common_type_t<lhs_t>>::value
            && element_predicate_t<get_element_or_common_type_t<rhs_t>>::value
            && is_array1d_v<lhs_t> // && is_array1d_v<rhs_t>
        >,
        select_array1d_t<size_policy_t,selection_kind_t,element_predicate_t,element_type_policy_t>, lhs_t, rhs_t
    >
    {
        static constexpr auto M = hybrid_ndarray_max_size_v<lhs_t>;
        static constexpr auto N = [](){
            if constexpr (has_tuple_size_v<rhs_t>)
                return std::tuple_size_v<rhs_t>;
            else return 0;
        }();
        static constexpr auto n = size_policy_t::get(M,N);
        using lhs_value_t = get_element_type_t<lhs_t>;
        using rhs_value_t = get_element_or_common_type_t<rhs_t>;
        using common_t = type_t<element_type_policy_t<lhs_value_t,rhs_value_t>>;

        using a_t = std::conditional_t<
            std::is_same_v<selection_kind_t,select_hybrid_kind_t>,
            resize_hybrid_ndarray_max_size_t<lhs_t,n>, void
        >;
        using b_t = std::conditional_t<
            std::is_same_v<selection_kind_t,select_resizeable_kind_t>
            && is_resizeable_v<rhs_t> && std::is_void_v<a_t>,
            rhs_t, a_t
        >;
        using c_t = std::conditional_t<
            std::is_same_v<selection_kind_t,select_fixed_kind_t>
            && has_tuple_size_v<rhs_t> && std::is_void_v<b_t>,
            resize_fixed_vector_t<rhs_t,n>, b_t
        >;
        // final type
        using type = replace_element_type_t<c_t,common_t>;
    }; // resolve_optype expand_dims_t

    template <typename T, size_t N>
    struct resize_fixed_index_array : resize_fixed_vector<T,N> {};

    template <typename T, size_t N>
    using resize_fixed_index_array_t = type_t<resize_fixed_index_array<T,N>>;

    /**
     * @brief Helper metafunction for convinient tuple-size
     * 
     * @tparam T 
     */
    template <typename T>
    struct len
    {
        static constexpr auto value = [](){
            if constexpr (has_tuple_size_v<T>)
                return std::tuple_size_v<T>;
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

    template <typename...Ts, size_t I>
    struct type_at<std::tuple<Ts...>,I>
    {
        using tuple_t = std::tuple<Ts...>;
        using type = std::tuple_element_t<I,tuple_t>;
    }; // type_at

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

    /**
     * @brief Append new type to the end of some type list.
     * 
     * @tparam T        some type list to be appended
     * @tparam new_type desired new type
     */
    template <typename T, typename new_type>
    struct append_type
    {
        using type = void;
    }; // append_type


    template <typename T, typename new_type>
    using append_type_t = type_t<append_type<T,new_type>>;

    template <typename...Ts, typename new_type>
    struct append_type<std::tuple<Ts...>,new_type>
    {
        using type = std::tuple<Ts...,new_type>;
    }; // append_type

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
            constexpr auto DIM = fixed_ndarray_dim_v<U>;
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

    template <typename T, typename U, size_t N>
    struct resize_fixed_ndarray<T[N],U,
        std::enable_if_t<is_fixed_size_ndarray_v<U>>
    >
    {
        using shape_t = std::tuple<std::integral_constant<size_t,N>>;
        using default_ndarray_t = type_t<make_fixed_ndarray<T,shape_t>>;
        using type = resize_fixed_ndarray_t<default_ndarray_t,U>;
    }; // resize_fixed_ndarray

    /** @} */ // end group meta
} // namespace nmtools::meta

#endif // NMTOOLS_META_TRANSFORM_HPP