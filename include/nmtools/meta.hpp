#ifndef NMTOOLS_META_HPP
#define NMTOOLS_META_HPP

#include "nmtools/traits.hpp"
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
        using enable_if_tuple_t = std::enable_if_t<traits::is_tuple_v<T>,R>;

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
    template <typename T>
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
        using type = std::array<T,N>;
    };

    /**
     * @brief overloaded version of transform_bounded_array for T[N][M]
     * 
     * @tparam T element type
     * @tparam N number of first indices
     * @tparam M number of last indices
     */
    template <typename T, std::size_t N, std::size_t M>
    struct transform_bounded_array<T[N][M]>
    {
        using type = std::array<std::array<T,M>,N>;
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
    struct get_value_type_or_same<T,std::enable_if_t<traits::has_value_type_v<T>>>
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
        std::enable_if_t<traits::is_resizeable_v<A> && traits::is_resizeable_v<B> >
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
        std::enable_if_t<traits::is_resizeable_v<A> && !traits::is_resizeable_v<B> >
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
        std::enable_if_t<traits::is_resizeable_v<B> && !traits::is_resizeable_v<A> >
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

    template <typename A, typename B, typename=void>
    struct select_resizeable_matrix {};

    template <typename A, typename B>
    struct select_resizeable_matrix<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array2d */
            traits::is_array2d_v<A> && traits::is_array2d_v<B> &&
            traits::is_resizeable_v<A> && traits::is_resizeable_v<B>
        >
    >{
        /* when both A and B is resizeable, select A */
        using type = A;
    };

    template <typename A, typename B>
    struct select_resizeable_matrix<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array2d */
            traits::is_array2d_v<A> && traits::is_array2d_v<B> &&
            !traits::is_resizeable_v<A> && traits::is_resizeable_v<B>
        >
    >{
        using type = B;
    };

    template <typename A, typename B>
    struct select_resizeable_matrix<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array2d */
            traits::is_array2d_v<A> && traits::is_array2d_v<B> &&
            traits::is_resizeable_v<A> && !traits::is_resizeable_v<B>
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
            traits::is_array1d_v<A> && traits::is_array1d_v<B> &&
            traits::is_resizeable_v<A> && traits::is_resizeable_v<B>
        >
    >{
        /* when both A and B is resizeable, select A */
        using type = A;
    };

    template <typename A, typename B>
    struct select_resizeable_vector<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array1d */
            traits::is_array1d_v<A> && traits::is_array1d_v<B> &&
            !traits::is_resizeable_v<A> && traits::is_resizeable_v<B>
        >
    >{
        using type = B;
    };

    template <typename A, typename B>
    struct select_resizeable_vector<A,B,
        std::enable_if_t<
            /* BOTH A and B should be array1d */
            traits::is_array1d_v<A> && traits::is_array1d_v<B> &&
            traits::is_resizeable_v<A> && !traits::is_resizeable_v<B>
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
    using enable_if_resizeable_t = std::enable_if_t<traits::is_resizeable_v<T>>;

    /**
     * @brief helper alias template to add specialization
     * (which check if T has tuple size) to overload set
     * 
     * @tparam T type to check
     */
    template <typename T>
    using enable_if_fixed_t = std::enable_if_t<traits::has_tuple_size_v<T>>;

    /**
     * @brief helper alias template to remove specialization
     * (which check if T is resizeable) from overload set
     * 
     * @tparam T type to check
     */
    template <typename T>
    using disable_if_resizeable_t = std::enable_if_t<!traits::is_resizeable_v<T>>;

    /**
     * @brief helper alias template to remove specialization
     * (which check if T has tuple size) from overload set
     * 
     * @tparam T type to check
     */
    template <typename T>
    using disable_if_fixed_t = std::enable_if_t<!traits::has_tuple_size_v<T>>;

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
        using type = C;
    };

    /**
     * @brief specialization of select_resizeable when A is resizeable and B is not
     * 
     * @tparam A 
     * @tparam B 
     * @tparam C 
     */
    template <typename A, typename B, typename C>
    struct select_resizeable<A,B,C,
        std::void_t<enable_if_resizeable_t<A>,disable_if_resizeable_t<B>>
    >
    {
        using type = A;
    };

    /**
     * @brief specialization of select resizeable when B is resizeable and A is not
     * 
     * @tparam A 
     * @tparam B 
     * @tparam C 
     */
    template <typename A, typename B, typename C>
    struct select_resizeable<A,B,C,
        std::void_t<enable_if_resizeable_t<B>,disable_if_resizeable_t<A>>
    >
    {
        using type = B;
    };

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
        using type = C;
    };

    template <typename A, typename B, typename C>
    struct select_fixed<A,B,C,
        std::void_t<enable_if_fixed_t<A>,disable_if_fixed_t<B>>
    >
    {
        using type = A;
    };

    template <typename A, typename B, typename C>
    struct select_fixed<A,B,C,
        std::void_t<enable_if_fixed_t<B>,disable_if_fixed_t<A>>
    >
    {
        using type = B;
    };

    template <typename A, typename B, typename C>
    using select_fixed_t = typename select_fixed<A,B,C>::type;

    /**
     * @brief get the velue type of container T via decltype, has void member type if failed
     * - using type = decltype(std::declval<T>()[0]); 
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_container_value_type { using type = void; };

    /**
     * @brief get the velue type of container T via decltype, has void member type if failed
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct get_container_value_type<T,std::void_t<decltype(std::declval<T>()[0])>> 
    { 
        /* TODO: consider to use nmtools::at from nmtools/array/utility.hpp for generic case */
        /* TODO: use std::remove_cvref_t when possible */
        using type = traits::remove_cvref_t<decltype(std::declval<T>()[0])>;
    };

    /**
     * @brief get the velue type of container T via decltype, has void member type if failed
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct get_container_value_type<T,std::void_t<decltype(std::declval<T>()(0))>>
    { 
        /* TODO: consider to use nmtools::at from nmtools/array/utility.hpp for generic case */
        /* TODO: use std::remove_cvref_t when possible */
        using type = traits::remove_cvref_t<decltype(std::declval<T>()(0))>;
    };

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
    using enable_if_has_value_type = std::enable_if<traits::has_value_type_v<T>>;

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
    using disable_if_nested_array2d = std::enable_if<!traits::is_nested_array2d_v<T>>;

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
        using type = traits::remove_cvref_t<decltype(std::declval<T>()[0][0])>;
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
         */
        static inline constexpr auto __get_type()
        {
            /**
             * @note since is_array1d_v and is_array2d_v may not be mutually exclusive,
             * it is hard to use std::enable_if / std::void_t to specialize,
             * hence using helper function instead
             * to deduce the resulting element type.
             * 
             * @todo make this fn consteval
             */
            if constexpr (traits::is_array2d_v<T>)
                return get_matrix_value_type_t<T>{};
            else if constexpr (traits::is_array1d_v<T>)
                return get_vector_value_type_t<T>{};
            else if constexpr (std::is_arithmetic_v<T>)
                return T{};
            else return;
        }
        using type = decltype(__get_type());
    };

    /**
     * @brief 
     * 
     * @tparam T 
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
        using value_t   = traits::remove_cvref_t<typename T::value_type>;
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
        using col_t = traits::remove_cvref_t<typename row_t::value_type>;
        using element_t = traits::remove_cvref_t<typename col_t::value_type>;
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
        using col_t = traits::remove_cvref_t<V2>;
        using col_tparam = extract_template_parameters_t<col_t>;
        using col_value_type = traits::remove_cvref_t<typename pop_first<col_tparam>::first>;

        using row_t = traits::remove_cvref_t<V1>;
        using row_tparam = extract_template_parameters_t<row_t>;
        using row_value_type = traits::remove_cvref_t<typename pop_first<row_tparam>::first>;

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
    struct get_column_type<T,std::enable_if_t<traits::is_nested_array2d_v<T> && traits::has_value_type_v<T>>>
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
        using value_t = traits::remove_cvref_t<T>;
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
    struct get_row_type<T,std::enable_if_t<traits::is_nested_array2d_v<T> && traits::has_value_type_v<T> && traits::is_dynamic_size_matrix_v<T>>>
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

    /** @} */ // end group meta
} // namespace nmtools::meta

#endif // NMTOOLS_META_HPP