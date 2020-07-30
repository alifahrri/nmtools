#ifndef NMTOOLS_META_HPP
#define NMTOOLS_META_HPP

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>
#include "nmtools/traits.hpp"

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
     * @tparam T 
     * @tparam  
     */
    template <typename T, typename...>
    struct replace_template_parameter 
    {
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
     * @brief helper alias template to replace tparam
     * 
     * @tparam T original type
     * @tparam Args template parameter for substitution
     */
    template <typename T, typename...Args>
    using replace_tparam_t = typename replace_template_parameter<T,Args...>::type;

    /*
    TODO: consider to provide specialization for replace_template_parameter, that accepts
        - T<typename,auto..>, 
        - T<auto,typename...>, etc.
    */

    /**
     * @brief metafunction to select resizeable matrix type
     * 
     * @tparam A 
     * @tparam B 
     * @tparam typename=void 
     */
    template <typename A, typename B, typename=void>
    struct select_resizeable_mat {};

    /**
     * @brief specialization of select_resizeable_mat when both A & B is resizeable
     * will have member type `type` that is resizeable
     * 
     * @tparam A 
     * @tparam B 
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
     */
    template <typename A, typename B>
    using select_resizeable_mat_t = typename select_resizeable_mat<A,B>::type;

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

} // namespace nmtools::meta

#endif // NMTOOLS_META_HPP