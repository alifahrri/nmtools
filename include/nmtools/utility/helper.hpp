#ifndef NMTOOLS_UTILITY_HELPER_HPP
#define NMTOOLS_UTILITY_HELPER_HPP

#include <type_traits>
#include <cassert>
#include <iterator>
#include <cmath>
#include <tuple>
#include <array>
#include "nmtools/traits.hpp"

namespace nmtools::helper {

    using std::size;

    /**
     * @brief helper function for compile-time conditional logging
     * 
     * @tparam Logger 
     * @param logger logger pointer to callable
     * @param mapping arguments mapping, to be logged
     * @return auto 
     */
    template <typename Logger>
    auto log(Logger logger, auto mapping) {
        /* only compile if logger is not nullptr_t */
        if constexpr (!std::is_null_pointer_v<Logger>) {
            static_assert(
                std::is_pointer_v<Logger>, 
                "expects logger to be pointer"
            );
            (*logger)(mapping);
        }
    }

    /**
     * @brief check if M is close with N given tolerance
     * 
     * @param M matrix-like or vector-like
     * @param N matrix-like or vector-like
     * @param eps tolerance
     * @return constexpr auto 
     */
    constexpr auto isclose(auto M, auto N, double eps=1e-6)
    {
        auto nm = size(M);
        auto nn = size(N);
        assert(nm==nn);
        for (size_t i=0; i<nm; i++) {
            auto m = M[i];
            auto n = N[i];
            if constexpr (std::is_arithmetic_v<decltype(m)>) {
                if (fabs(m-n) > eps)
                    return false;
            } else {
                auto nmm = size(m);
                auto nnn = size(n);
                assert (nmm=nnn);
                for (size_t j=0; j<nmm; j++) {
                    auto mm = m[j];
                    auto nn = n[j];
                    if (fabs(mm-nn) > eps)
                        return false;
                }
            }
        }
        return true;
    }

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
} // namespace nmtools::helper

#endif // NMTOOLS_UTILITY_HELPER_HPP