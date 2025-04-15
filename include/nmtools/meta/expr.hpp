#ifndef NMTOOLS_META_EXPR_HPP
#define NMTOOLS_META_EXPR_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/add_reference.hpp"
#include "nmtools/utility/get.hpp"

namespace nmtools::meta
{
    namespace expr
    {
        /**
         * @brief helper alias template to check if given type T has member function `at`
         * taking size_types as parameters.
         * 
         * @tparam T type to check
         * @tparam size_types arguments to `at`
         */
        template <typename T, typename...size_types>
        using atnd = decltype(declval<T>().at(declval<size_types>()...));

        /**
         * @brief helper alias template to check if given type T has operator() overload
         * that takes size_types as arguments.
         * 
         * @tparam T type to check
         * @tparam size_types arguments to `operator()`
         */
        template <typename T, typename...size_types>
        using funcnd = decltype(declval<T>().operator()(declval<size_types>()...));

        template <typename T, typename...arg_types>
        using callable = decltype(declval<T>()(declval<arg_types>()...));

        template <typename T, typename U>
        using equal = decltype(declval<T>()==declval<U>());

        template <typename T>
        using invert = decltype(~declval<T>());

        /**
         * @brief helper alias template to check if given type T has operator [] overload
         * that takes size_types as arguments.
         * 
         * @tparam T type to check
         * @tparam size_types arguments to `operator[]`
         */
        template <typename T, typename...size_types>
        using bracketnd = decltype(declval<T>().operator[](declval<size_types>()...));

        /**
         * @brief helper alias template to check if given type T has member function `resize`
         * taking size_types as parameters.
         * 
         * @tparam T type to check
         * @tparam size_types parameter(s) to `resize`
         */
        template <typename T, typename...size_types>
        using resizend = decltype(declval<T>().resize(declval<size_types>()...));

        /**
         * @brief helper alias template to deduce the return value of member function `size` of type `T`
         * 
         * @tparam T type to check
         */
        template <typename T>
        using size = decltype(declval<T>().size());

        /**
         * @brief helper alias template to deduce the return value of member function `shape` of type `T`
         * 
         * @tparam T type to check
         */
        template <typename T>
        using shape = decltype(declval<T>().shape());

        /**
         * @brief helper alias template to deduce the return value of member function `dim` of type `T`
         * 
         * @tparam T type to check
         */
        template <typename T>
        using dim = decltype(declval<T>().dim());

        // TODO: proper convention on member function vs member variable
        template <typename T>
        using src_size = decltype(declval<T>().src_size);

        // TODO: proper convention on member function vs member variable
        template <typename T>
        using dst_size = decltype(declval<T>().dst_size);

        template <typename T>
        using add_lvalue_reference = decltype(declval<T&>());

        template <typename T>
        using add_rvalue_reference = decltype(declval<T&&>());

        template <typename T, typename...Args>
        using constructor = decltype(T(declval<Args>()...));

        /**
         * @brief helper alias template to deduce the return value from index subscript `[]`.
         *
         * @note not to be confused with bracketnd that deduce from `operator[]` that takes variadic
         * types as arguments.
         * 
         * @tparam T type to check
         * @tparam size_type argument type to index subscript `[]`
         */
        template <typename T, typename size_type>
        using square_bracket = decltype(declval<T>()[declval<size_type>()]);

        template <typename T, typename size_type>
        using reserve = decltype(declval<T>().reserve(declval<size_type>()));

        template <typename T>
        using operands_fn = decltype(declval<T>().operands());

        template <typename T>
        using operands = decltype(declval<T>().operands);

        /**
         * @brief helper alias template to check if T has member type 'type'
         * 
         * @tparam T type to check
         */
        template <typename T>
        using type = typename T::type;

        template <typename T, typename Is, typename=void>
        struct template_get_helper {};

        template <typename T, auto...Is>
        struct template_get_helper<T,index_sequence<Is...>,
            void_t<decltype(get<Is...>(declval<T>()))>>
        {
            using type = decltype(get<Is...>(declval<T>()));
        }; // template_get_helper

        template <typename T, typename Is>
        using template_get = typename template_get_helper<T,Is>::type;
    } // namespace expr

    namespace detail
    {
        /**
         * @brief helper traits to check if given expression
         * (provided as alias template that takes T and tparams...)
         * is well-formed (calling expression<T,tparams...> results in a type).
         * Roughly adapted from https://en.cppreference.com/w/cpp/experimental/is_detected
         * 
         * @tparam always_void provided as specialization point (e.g. using void_t for true case)
         * @tparam expression template template parameter take T and tparams as template arguments
         * @tparam T the type to be checked
         * @tparam tparams optional additional type parameters
         */
        template <typename always_void, template<typename...> typename expression, typename T, typename...tparams>
        struct expression_check : false_type {};

        /**
         * @brief specialization of expression_check traits that check if given expression
         * (provided as alias template that takes T and tparams...)
         * is well-formed (calling expression<T,tparams...> results in a type) for true case.
         * Roughly adapted from https://en.cppreference.com/w/cpp/experimental/is_detected
         * 
         * @tparam expression template template parameter take T and tparams as template arguments
         * @tparam T the type to be checked
         * @tparam tparams optional additional type parameters
         */
        template <template<typename...> typename expression, typename T, typename...tparams>
        struct expression_check<void_t<expression<T,tparams...>>, expression, T, tparams...> : true_type {};
    } // namespace detail

    template <template<typename...> typename expression, typename T, typename...tparams>
    constexpr inline auto expression_check_v = detail::expression_check<void,expression,T,tparams...>::value;
} // namespace nmtools::meta


#endif // NMTOOLS_META_EXPR_HPP