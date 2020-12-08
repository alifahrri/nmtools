#ifndef NMTOOLS_META_TRANSFORM_HPP
#define NMTOOLS_META_TRANSFORM_HPP

#include "nmtools/meta/detail.hpp"
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
     * @brief merge two type T (possibly tuple) and U (possibly tuple) to single tuple.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T lhs tuple to be merged
     * @tparam U rhs tuple to be merged
     */
    template <typename T, typename U>
    struct type_merge
    {
        template <typename...Ts, typename...Us>
        static constexpr auto _type_merge(std::tuple<Ts...>, std::tuple<Us...>)
        {
            using type_t = std::tuple<Ts...,Us...>;
            return type_t{};
        } // _type_merge

        template <typename Ts, typename...Us>
        static constexpr auto _type_merge(Ts, std::tuple<Us...>)
        {
            using type_t = std::tuple<Ts,Us...>;
            return type_t{};
        } // _type_merge

        template <typename...Ts, typename Us>
        static constexpr auto _type_merge(std::tuple<Ts...>, Us)
        {
            using type_t = std::tuple<Ts...,Us>;
            return type_t{};
        } // _type_merge

        template <typename Ts, typename Us>
        static constexpr auto _type_merge(Ts, Us)
        {
            using type_t = std::tuple<Ts,Us>;
            return type_t{};
        } // _type_merge

        using type = decltype(_type_merge(std::declval<T>(),std::declval<U>()));
    }; // type_merge

    /**
     * @brief helper alias template to merge two type T (possibly tuple) and U (possibly tuple) to single tuple.
     * <a href="https://godbolt.org/z/MEEjsE">godbolt demo</a>.
     * 
     * @tparam T lhs tuple to be merged
     * @tparam U rhs tuple to be merged
     */
    template <typename T, typename U>
    using type_merge_t = typename type_merge<T,U>::type;

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
            using reversed_t= type_merge_t<last_t,rest_t>;
            return reversed_t{};
        } // _reverse_type_list

        using type = decltype(_reverse_type_list(std::declval<T>()));
    };

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
        template <auto...Is>
        static constexpr auto _sequence_to_tuple(std::integer_sequence<T,Is...>)
        {
            using tuple_type = std::tuple<std::integral_constant<T,Is>...>;
            return tuple_type{};
        } // _sequence_to_tuple

        template <typename...Ts>
        static constexpr auto _tuple_to_sequence(std::tuple<Ts...>)
        {
            using sequence_type = std::integer_sequence<T,static_cast<T>(Ts::value)...>;
            return sequence_type{};
        } // _tuple_to_sequence

        using sequence_type = std::make_integer_sequence<T,N>;
        using sequence_tuple_type = decltype(_sequence_to_tuple(std::declval<sequence_type>()));
        using reversed_tuple_type = type_reverse_t<sequence_tuple_type>;
        using type = decltype(_tuple_to_sequence(std::declval<reversed_tuple_type>()));
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
                using type = remove_all_nested_array_dim_t<T>;
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
     * @brief helper alias tempate for get_element_type
     * 
     * @tparam T type to transform
     */
    template <typename T>
    using get_element_type_t = typename get_element_type<T>::type;

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
        /* TODO: assert if V1 and v2 is vector-like */
        
        /* default implementation will try to replace value_type (and value_type only) of V1 with V2 */
        using col_t = meta::remove_cvref_t<V2>;
        using col_tparam = extract_template_parameters_t<col_t>;
        using col_value_type = meta::remove_cvref_t<typename pop_first<col_tparam>::first>;

        using row_t = meta::remove_cvref_t<V1>;
        using row_tparam = extract_template_parameters_t<row_t>;
        using row_value_type = meta::remove_cvref_t<typename pop_first<row_tparam>::first>;

        /* TODO: tell matrix_t to use common_t! */
        using common_t = std::common_type_t<col_value_type,row_value_type>;
        using matrix_t = replace_template_parameter_from_typelist_t<V1,std::tuple<col_t>>;

        using type = matrix_t;
    };

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

    /** @} */ // end group meta
} // namespace nmtools::meta

#endif // NMTOOLS_META_TRANSFORM_HPP