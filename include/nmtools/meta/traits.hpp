#ifndef NMTOOLS_META_TRAITS_HPP
#define NMTOOLS_META_TRAITS_HPP

#include <type_traits>
/** @todo use __has_include */
#include <array>
#if __has_include(<vector>)
    #include <vector> // @todo remove
    #define NMTOOLS_HAS_VECTOR
#endif
#include <complex> // @todo remove
#include <tuple>
#include <utility>

#include "nmtools/meta/common.hpp"

namespace nmtools::meta {

    /** @defgroup traits
    * Collections of type traits used accross the library
    * @{ 
    */

    using std::false_type;
    using std::true_type;
    using std::declval;
    using std::void_t;
    using std::enable_if_t;

    /**
     * @brief check if T() * U() is valid
     * 
     * @tparam T 
     * @tparam U 
     * @tparam void 
     */
    template <typename T, typename U, typename = void>
    struct is_multiplicative : std::false_type {};

    /**
     * @brief specialization of is_multiplicative
     * 
     * @tparam T lhs
     * @tparam U rhs
     */
    template <typename T, typename U>
    struct is_multiplicative<T, U, std::void_t<
        decltype(std::declval<T>() * std::declval<U>())
    > > : std::true_type {};

    /**
     * @brief helper variable template to check if
     * T and U is multiplicative
     * 
     * @tparam T lhs
     * @tparam U rhs
     */
    template <typename T, typename U>
    inline constexpr bool is_multiplicative_v = is_multiplicative<T,U>::value;

    /**
     * @brief check if T() + U() is valid
     * 
     * @tparam T lhs
     * @tparam U rhs
     * @tparam void 
     */
    template <typename T, typename U, typename = void>
    struct is_additive : std::false_type {};

    /**
     * @brief specialization of is_additive
     * 
     * @tparam T lhs
     * @tparam U rhs
     */
    template <typename T, typename U>
    struct is_additive<T, U, std::void_t<
        decltype(std::declval<T>() + std::declval<U>())
    > > : std::true_type {};

    /**
     * @brief helper variable template to check if
     * T and U is additive
     * 
     * @tparam T lhs
     * @tparam U rhs
     */
    template <typename T, typename U>
    inline constexpr bool is_additive_v = is_additive<T,U>::value;

    /**
     * @brief check if F(Args...) is well-formed
     * 
     * @tparam F function
     * @tparam Args arguments
     */
    template <typename F, typename...Args>
    struct is_callable {
    private:
        template <typename FN>
        constexpr static auto test(int) -> decltype(std::declval<FN>()(std::declval<Args>()...), bool()) {
            return true;
        }
        template <typename>
        constexpr static auto test(...) -> decltype(bool()) {
            return false;
        }
    public:
        constexpr static bool value = test<F>(int{});
    };

    /**
     * @brief helper variable template for is_callable
     * 
     * @tparam F function
     * @tparam Args arguments
     */
    template <typename F, typename...Args>
    inline constexpr bool is_callable_v = is_callable<F,Args...>::value;

    /* TODO : move (?) */
    using std::begin;
    using std::end;

    template <typename T>
    struct is_iterable {
    private:
        template <typename It>
        static constexpr auto test(int)
            -> decltype(begin(std::declval<It>()), end(std::declval<It>()), bool())
        { return true; }
        template <typename It>
        static constexpr auto test(char)
        { return false; }
    public:
        constexpr static bool value = test<T>(int());
    };

    template <typename T>
    inline constexpr bool is_iterable_v = is_iterable<T>::value;

    /**
     * @brief check if type T has member type size_type
     * 
     * @tparam T type to check
     * @tparam void 
     */
    template <typename T, typename = void>
    struct has_size_type : std::false_type {};

    /**
     * @brief specialization when T actually size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_size_type<T,
        std::void_t<typename T::size_type>
    > : std::true_type {};

    /**
     * @brief helper variable template to check if T has size_type
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool has_size_type_v = has_size_type<T>::value;

    /**
     * @brief check if T has member type value_type
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_value_type : std::false_type {};

    /**
     * @brief specialization when T actually has value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_value_type<T, std::void_t<typename T::value_type> > : std::true_type {};

    /**
     * @brief helper variable template to check if T has member type value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_value_type_v = has_value_type<T>::value;

    /**
     * @brief check if type T has member type allocator_type
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_allocator_type : std::false_type {};

    /**
     * @brief specialization when T actually has allocator_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_allocator_type<T,std::void_t<typename T::allocator_type> > : std::true_type {};

    /**
     * @brief helper variable template to chek if T has allocator_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_allocator_type_v = has_allocator_type<T>::value;

    /**
     * @brief helper alias template to enable/add to overload set if T has size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    using enable_if_has_size_type = std::enable_if<has_size_type_v<T>>;

    /**
     * @brief helper alias template to enable/add to overload set if T has size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    using enable_if_has_size_type_t = typename enable_if_has_size_type<T>::type;

    /**
     * @brief helper alias template to disable/remove from overload set if T has size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    using disable_if_has_size_type = std::enable_if<!has_size_type_v<T>>;

    /**
     * @brief helper alias template to disable/remove from overload set if T has size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    using disable_if_has_size_type_t = typename disable_if_has_size_type<T>::type;

    /**
     * @brief check if T is resizeable
     * 
     * @tparam T type to check
     * @tparam void 
     */
    // template <typename T, typename = void>
    // struct is_resizeable : std::false_type {};

    /**
     * @brief specialization of is_resizeable when T is resizeable using size_t
     * 
     * @tparam T type to check
     */
    // template <typename T>
    // struct is_resizeable<T, 
    //     std::void_t<
    //         disable_if_has_size_type_t<T>,
    //         decltype(std::declval<T>().resize(std::declval<size_t>()))
    //     >
    // > : std::true_type {};

    /**
     * @brief specialization of is_resizeable when T is resizeable using T::size_type
     * 
     * @tparam T type to check
     */
    // template <typename T>
    // struct is_resizeable<T, 
    //     std::void_t<
    //         enable_if_has_size_type_t<T>,
    //         decltype(std::declval<T>().resize(std::declval<typename T::size_type>()))
    //     >
    // > : std::true_type {};

    /**
     * @brief helper variable template to check if T is resizeable
     * 
     * @tparam T type to check
     */
    // template <typename T>
    // static constexpr auto is_resizeable_v = is_resizeable<T>::value;

    /**
     * @brief check if T can be resized with 2 arguments, e.g. declval<T>().resize(i,i)
     * 
     * @tparam T type to check
     * @tparam void 
     */
    // template <typename T, typename = void>
    // struct is_resizeable2d : std::false_type {};

    // template <typename T>
    // struct is_resizeable2d<T, 
    //     std::void_t<
    //         disable_if_has_size_type_t<T>,
    //         decltype(declval<T>().resize(declval<size_t>(),declval<size_t>()))
    //     >
    // > : true_type {};

    // template <typename T>
    // struct is_resizeable2d<T, 
    //     std::void_t<
    //         enable_if_has_size_type_t<T>,
    //         decltype(declval<T>().resize(declval<typename T::size_type>(),declval<typename T::size_type>()))
    //     >
    // > : true_type {};

    // template <typename T>
    // static constexpr auto is_resizeable2d_v = is_resizeable2d<T>::value;

    /**
     * @brief check if std::tuple_size<T> is valid for T
     * should be true for std::array, std::tuple, std::pair
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_tuple_size : std::false_type {};

    /**
     * @brief specialization of has_tuple_size when tuple_size<T> is well-formed
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_tuple_size<T, std::void_t<typename std::tuple_size<T>::type>> : std::true_type {};

    /**
     * @brief helper variable template to check if std::tuple_size<T> is valid
     * 
     * @todo test
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_tuple_size_v = has_tuple_size<T>::value;

    /**
     * @brief helper alias template combining remove_cv and remove_reference
     * 
     * @tparam T 
     */
    template <typename T>
    using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

    using std::tuple;

    /**
     * @brief check if given type is tuple
     */
    template <typename>
    struct is_tuple : false_type {};
    template <typename ...Args>
    struct is_tuple<tuple<Args...>> : true_type {};

    /**
     * @brief helper variable template to check if given type is tuple
     * 
     * @tparam Args automatically deduced
     * @example 
     *  static_assert(is_tuple_v<std::tuple<int,double>> == true);
     *  static_assert(is_tuple_v<double> == false);
     */
    template <typename ...Args>
    inline constexpr bool is_tuple_v = is_tuple<Args...>::value;

    /**
     * @brief check if T is bounded array
     * 
     * @tparam T 
     */
    template<typename T>
    struct is_bounded_array: std::false_type {};
    
    template<typename T, std::size_t N>
    struct is_bounded_array<T[N]> : std::true_type {};

    /**
     * @brief helper variable template to check if T is bounded array
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

    template <template<typename...> typename T, typename...>
    struct is_template_instantiable : std::false_type {};
    
    template <template<typename...> typename T, typename U, typename ...Args>
    struct is_template_instantiable<T,T<U,Args...>> : std::true_type {};

    /**
     * @brief check if type T has operator at with size_type as single argument.
     * 
     * @tparam T type to check.
     * @tparam size_type argument type.
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_at : false_type {};

    /**
     * @brief specialization of has_at for true case.
     * Enabled if T has operator at with size_type as single argument,
     * e.g. declval<T>().at(i), with i of size_type, is well-formed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    struct has_at<T,size_type,
        void_t<decltype(declval<T>().at(declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_at
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_at_v = has_at<T,size_type>::value;

    /**
     * @brief check if type T has operator at with size_type as single argument.
     * 
     * @tparam T type to check.
     * @tparam size_type argument type.
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_at2d : false_type {};

    /**
     * @brief specialization of has_at for true case.
     * Enabled if T has operator at with size_type as single argument,
     * e.g. declval<T>().at(i,i), with i of size_type, is well-formed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    struct has_at2d<T,size_type,
        void_t<decltype(declval<T>().at(declval<size_type>(),declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_at2d
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_at2d_v = has_at2d<T,size_type>::value;

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
        using square_bracket = decltype(std::declval<T>()[std::declval<size_type>()]);

        /**
         * @brief helper alias template to check if T has member type 'type'
         * 
         * @tparam T type to check
         */
        template <typename T>
        using type = typename T::type;

        template <typename T, typename Is, typename=void>
        struct template_get_helper {};

        using std::get;

        template <typename T, auto...Is>
        struct template_get_helper<T,std::index_sequence<Is...>,
            std::void_t<decltype(get<Is...>(std::declval<T>()))>>
        {
            using type = decltype(get<Is...>(std::declval<T>()));
        }; // template_get_helper

        template <typename T, typename Is>
        using template_get = typename template_get_helper<T,Is>::type;
    } // namespace expr

    template <typename T, auto...Is>
    struct has_template_get : detail::expression_check<void,expr::template_get,T,std::index_sequence<Is...>> {};

    template <typename T, auto...Is>
    inline constexpr bool has_template_get_v = has_template_get<T,Is...>::value;

    /**
     * @brief check if type T has member type 'type'
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_type : detail::expression_check<void,expr::type,T> {};

    /**
     * @brief helper variable template to check if type T has member type 'type'
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_type_v = has_type<T>::value;

    /**
     * @brief check if type T can be indexed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type to indexing subscript
     * @tparam typename customizaiton point
     * @see expr::square_bracket
     */
    template <typename T, typename size_type, typename=void>
    struct has_square_bracket
    {
        /**
         * @brief check using expression checker
         * 
         * @return constexpr auto 
         */
        static constexpr auto _check()
        {
            using expression = detail::expression_check<void,expr::square_bracket,T,size_type>;
            if constexpr (expression::value)
                return true;
            else return false;
        } // _check()
        static constexpr auto value = _check();
    }; // has_square_bracket

    /**
     * @brief helper variable template for has_square_bracket
     * 
     * @tparam T type to check
     * @tparam size_type argument type to indexing subscript
     */
    template <typename T, typename size_type>
    inline constexpr bool has_square_bracket_v = has_square_bracket<T,size_type>::value;

    /**
     * @brief trait to check if given type T is resizeable with size_types as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `resize`
     */
    template <typename T, typename...size_types>
    struct is_resizeable_nd : detail::expression_check<void,expr::resizend,T,size_types...>{};

    /**
     * @brief helper variable template to check if given type T is resizeable with size_types as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `resize`
     */
    template <typename T, typename...size_types>
    inline constexpr bool is_resizeable_nd_v = is_resizeable_nd<T,size_types...>::value;

    /**
     * @brief check if given type T is resizeable (1D).
     *
     * Default implementation will check if T has size_type,
     * then calls is_resizeable_nd with size_type as arguments,
     * otherwise assume size_type is size_t then call is_resizeable_nd.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_resizeable
    {
        /**
         * @brief default implementation for actual checking,
         * implemented as static member function to avoid clunky sfinae
         * and allows to easily specialize specific type.
         * 
         * @return constexpr auto 
         */
        static constexpr auto _check()
        {
            if constexpr (has_size_type_v<T>) {
                using size_type = typename T::size_type;
                return is_resizeable_nd_v<T,size_type>;
            }
            else {
                using size_type = size_t;
                return is_resizeable_nd_v<T,size_type>;
            }
        } // _check()

        static constexpr inline bool value = _check();
    }; // is_resizeable

    /**
     * @brief helper variable template to check if type T is resizeable
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_resizeable_v = is_resizeable<T>::value;

    /**
     * @brief check if given type T is resizeable (2D).
     *
     * Default implementation will check if T has size_type,
     * then calls is_resizeable_nd with size_type as arguments,
     * otherwise assume size_type is size_t then call is_resizeable_nd.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_resizeable2d
    {
        /**
         * @brief default implementation for actual checking,
         * implemented as static member function to avoid clunky sfinae
         * and allows to easily specialize specific type.
         * 
         * @return constexpr auto 
         */
        static constexpr auto _check()
        {
            if constexpr (has_size_type_v<T>) {
                using size_type = typename T::size_type;
                return is_resizeable_nd_v<T,size_type,size_type>;
            }
            else {
                using size_type = size_t;
                return is_resizeable_nd_v<T,size_type,size_type>;
            }
        } // _check()

        static constexpr inline bool value = _check();
    };

    /**
     * @brief helper variable template to check if type T is resizeable
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_resizeable2d_v = is_resizeable2d<T>::value;

    /**
     * @brief check if T has member function `at` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `at`
     * @see nmtools::meta::expr::has_atnd
     * @see nmtools::meta::detail::expression_check
     */
    template <typename T, typename...size_types>
    struct has_atnd : detail::expression_check<void,expr::atnd,T,size_types...> {};

    /**
     * @brief helper variable template to check if T has member function `at` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `at`
     * @see nmtools::meta::has_atnd
     */
    template <typename T, typename...size_types>
    inline constexpr bool has_atnd_v = has_atnd<T,size_types...>::value;

    /**
     * @brief check if type `T` has `operator()` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator()`
     */
    template <typename T, typename...size_types>
    struct has_funcnd : detail::expression_check<void,expr::funcnd,T,size_types...> {};

    /**
     * @brief helper variable template to check if type `T` has `operator()` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator()`
     */
    template <typename T, typename...size_types>
    inline constexpr bool has_funcnd_v = has_funcnd<T,size_types...>::value;

    /**
     * @brief check if T has bracket operator (()) with size_type as argument
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_bracket : has_funcnd<T,size_type> {};

    /**
     * @brief helper variable template for has_bracket.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_bracket_v = has_bracket<T,size_type>::value;

    /**
     * @brief check if type `T` has `operator[]` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator[]`
     */
    template <typename T, typename...size_types>
    struct has_bracketnd : detail::expression_check<void,expr::bracketnd,T,size_types...> {};

    /**
     * @brief helper variable template to check if type `T` has `operator[]` that takes `size_types...` as arguments.
     * 
     * @tparam T type to check
     * @tparam size_types arguments to `operator[]`
     */
    template <typename T, typename...size_types>
    inline constexpr bool has_bracketnd_v = has_bracketnd<T,size_types...>::value;

    /**
     * @brief check if type `T` has member function `size`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_size : detail::expression_check<void,expr::size,T> {};

    /**
     * @brief helper variable template to check if type `T` has member function `size`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    inline constexpr bool has_size_v = has_size<T>::value;

    /**
     * @brief check if type `T` has member function `shape`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_shape : detail::expression_check<void,expr::shape,T> {};

    /**
     * @brief helper variable template to check if type `T` has member function `shape`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    inline constexpr bool has_shape_v = has_shape<T>::value;

    /**
     * @brief check if type `T` has member function `dim`.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_dim : detail::expression_check<void,expr::dim,T> {};

    /**
     * @brief helper variable template to check if type `T` has member function `dim`.
     * 
     * @tparam T type to check 
     */
    template <typename T>
    inline constexpr bool has_dim_v = has_dim<T>::value;

    /**
     * @brief check if T has square bracket operator ([]) with size_type as arguments.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_square_bracket2d : false_type {};

    /**
     * @brief specialization of has_square_bracket2d for true case.
     * Enabled if T has square bracket operator with size_type as argument,
     * e.g. declval<T>()[i,i], with i of type size_type, is well-formed.
     * 
     * @tparam T 
     * @tparam size_type 
     */
    template <typename T, typename size_type>
    struct has_square_bracket2d<T,size_type,
        /* note: use .operator[](i,i) so that 
            it doesn't implicitly call [] with comma operator .operator[](operator,(i,i))*/
        void_t<decltype(declval<T>().operator[](declval<size_type>(),declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_square_bracket2d
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_square_bracket2d_v = has_square_bracket2d<T,size_type>::value;

    /**
     * @brief check if T has bracket operator (()) with size_type as argument
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_bracket2d : false_type {};

    /**
     * @brief specialization of has_bracket2d for true case.
     * Enabled if T has bracket operator with size_type as argument,
     * e.g. declval<T>()(i,i), with i of type size_type, is well-formed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    struct has_bracket2d<T,size_type,
        void_t<decltype(declval<T>()(declval<size_type>(),declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_bracket2d.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_bracket2d_v = has_bracket2d<T,size_type>::value;

    /**
     * @brief check if T is nested 2d array,
     * default is false unless specialization is provided.
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct is_nested_array2d : false_type {};

    /**
     * @brief specialization of is_nested_array2d when
     * expression T{}[0][0] is well-formed;
     * 
     * @tparam T type to check.
     */
    template <typename T>
    struct is_nested_array2d<T,
        void_t<decltype(std::declval<T>()[0][0])>
    > : true_type {};

    /**
     * @brief helper variable template to check if T is_nested_array2d.
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_nested_array2d_v = is_nested_array2d<T>::value;

    /**
     * @brief check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_integral_constant : false_type {};

    /**
     * @brief check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T, auto N>
    struct is_integral_constant<std::integral_constant<T,N>> : true_type {};

    /**
     * @brief helper inline variable to check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_integral_constant_v = is_integral_constant<T>::value;

    namespace detail {
        template <template <typename> typename trait, typename type_list, typename=void>
        struct apply_disjunction_helper
        {
            static constexpr auto value = fail_t{};
        }; // apply_disjunction_helper

        template <template <typename> typename trait, typename T, typename...Ts>
        struct apply_disjunction_helper<trait,std::tuple<T,Ts...>,std::enable_if_t<(sizeof...(Ts)==0)>>
        {
            static constexpr auto value = trait<T>::value;
        }; // apply_disjunction_helper

        template <template <typename> typename trait, typename T, typename U>
        struct apply_disjunction_helper<trait,std::pair<T,U>>
        {
            static constexpr auto value = trait<T>::value || trait<U>::value;
        }; // apply_disjunction_helper

        template <template <typename> typename trait, typename T, typename...Ts>
        struct apply_disjunction_helper<trait,std::tuple<T,Ts...>,std::enable_if_t<(sizeof...(Ts)>0)>>
        {
            static constexpr auto value = trait<T>::value || apply_disjunction_helper<trait,std::tuple<Ts...>>::value;
        }; // apply_disjunction_helper

        template <template <typename> typename trait, typename type_list, typename=void>
        struct apply_conjunction_helper
        {
            static constexpr auto value = fail_t{};
        }; // apply_conjunction_helper

        template <template <typename> typename trait, typename T, typename...Ts>
        struct apply_conjunction_helper<trait,std::tuple<T,Ts...>,std::enable_if_t<(sizeof...(Ts)==0)>>
        {
            static constexpr auto value = trait<T>::value;
        }; // apply_conjunction_helper

        template <template <typename> typename trait, typename T, typename U>
        struct apply_conjunction_helper<trait,std::pair<T,U>,void>
        {
            static constexpr auto value = trait<T>::value && trait<U>::value;
        }; // apply_conjunction_helper

        template <template <typename> typename trait, typename T, typename...Ts>
        struct apply_conjunction_helper<trait,std::tuple<T,Ts...>,std::enable_if_t<(sizeof...(Ts)>0)>>
        {
            static constexpr auto value = trait<T>::value && apply_conjunction_helper<trait,std::tuple<Ts...>>::value;
        }; // apply_conjunction_helper
    } // namespace detail

    /**
     * @brief check if any type in type_list satisfy trait
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    struct apply_disjunction
    {
        static inline constexpr auto impl_value = detail::apply_disjunction_helper<trait,type_list>::value;
        using value_type = decltype(impl_value);
        // make false on fail (value_type==fail_t)
        static inline constexpr auto value = detail::fail_to_false(impl_value);
    }; // apply_disjunction

    /**
     * @brief helper variable template to check if all type in type_list satisfy trait
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    static constexpr auto apply_disjunction_v = apply_disjunction<trait,type_list>::value;

    /**
     * @brief check if all type in type_list satisfy trait
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    struct apply_conjunction
    {
        static inline constexpr auto impl_value = detail::apply_conjunction_helper<trait,type_list>::value;
        using value_type = decltype(impl_value);
        // make false on fail (value_type==fail_t)
        static inline constexpr auto value = detail::fail_to_false(impl_value);
    }; // apply_conjunction

    /**
     * @brief helper variable template to check if any type in type_list satisfy trait
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    static constexpr auto apply_conjunction_v = apply_conjunction<trait,type_list>::value;

    /**
     * @brief alias for appply_disjunction
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    struct apply_logical_or : apply_disjunction<trait, type_list> {};

    /**
     * @brief alias for apply_conjunction
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    struct apply_logical_and : apply_conjunction<trait, type_list> {};

    /**
     * @brief helper variable template for apply_logical_or
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    static inline constexpr auto apply_logical_or_v = apply_logical_or<trait,type_list>::value;

    /**
     * @brief helper variable template for apply_logical_and
     * 
     * @tparam type_list type list to be checked
     * @tparam trait template template parameter corresponding to trait to be satisfied
     */
    template <template <typename> typename trait, typename type_list>
    static inline constexpr auto apply_logical_and_v = apply_logical_and<trait,type_list>::value;

    /**
     * @brief alias for std::conjuction
     * 
     * @tparam Ts types that has value static constexpr member variable
     */
    template <typename...Ts>
    struct logical_and : std::conjunction<Ts...> {};

    template <typename...Ts>
    static constexpr inline auto logical_and_v = logical_and<Ts...>::value;

    /**
     * @brief alias for std::disjunction
     * 
     * @tparam Ts types that has value static constexpr member variable
     */
    template <typename...Ts>
    struct logical_or : std::disjunction<Ts...> {};

    template <typename...Ts>
    static constexpr inline auto logical_or_v = logical_or<Ts...>::value;

    /**
     * @brief alias for std::negation
     * 
     * @tparam Ts types that has value static constexpr member variable
     */
    template <typename T>
    struct logical_not : std::negation<T> {};

    template <typename T>
    static constexpr inline auto logical_not_v = logical_not<T>::value;

    namespace detail
    {
        template <typename always_void, template<typename...>typename predicate, typename T, template<typename> typename trait, template<typename> typename...traits>
        struct compose_trait_helper
        {
            static constexpr auto value = predicate<trait<T>,traits<T>...>::value;
        };
    } // namespace detail

    /**
     * @brief given type T and variadic traits, perform logical_and on trait<T> for each trait in traits
     * 
     * @tparam T type to check
     * @tparam traits template template parameter resulting static constexpr member variable value
     */
    template <typename T, template<typename> typename...traits>
    struct compose_logical_and
    {
        static constexpr auto value = detail::compose_trait_helper<void,logical_and,T,traits...>::value;
    }; // compose_logical_and

    /**
     * @brief given type T and variadic traits, perform logical_or on trait<T> for each trait in traits
     * 
     * @tparam T type to check
     * @tparam traits template template parameter resulting static constexpr member variable value
     */
    template <typename T, template<typename> typename...traits>
    struct compose_logical_or
    {
        static constexpr auto value = detail::compose_trait_helper<void,logical_or,T,traits...>::value;
    }; // compose_logical_or

    /**
     * @brief alias variable template for compose_logical_and
     * 
     * @tparam T type to check
     * @tparam traits template template parameter resulting static constexpr member variable value
     */
    template <typename T, template<typename> typename...traits>
    static inline constexpr auto compose_logical_and_v = compose_logical_and<T,traits...>::value;

    /**
     * @brief alias variable template for compose_logical_or
     * 
     * @tparam T type to check
     * @tparam traits template template parameter resulting static constexpr member variable value
     */
    template <typename T, template<typename> typename...traits>
    static inline constexpr auto compose_logical_or_v = compose_logical_or<T,traits...>::value;

    /**
     * @brief check if given type T is specialization of template-template param primary_template
     * 
     * @tparam T type to check
     * @tparam primary_template primary template
     */
    template <typename T, template <typename...> typename primary_template>
    struct is_specialization : std::false_type {};

    template <template <typename...> typename primary_template, typename... Args>
    struct is_specialization<primary_template<Args...>, primary_template> : std::true_type {};

    /**
     * @brief helper alias template for is_specialization
     * 
     * @tparam T type to check
     * @tparam primary_template primary template 
     */
    template <typename T, template <typename...> typename primary_template>
    inline constexpr auto is_specialization_v = is_specialization<T,primary_template>::value;

    /**
     * @brief check if type T is std::_Bit_reference
     * 
     * This trait is added since std::vector<bool> access return std::_Bit_reference
     * and specializing is_integral is undefined behaviour
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T>
    struct is_bit_reference : std::false_type {};

    template <typename T>
    inline constexpr auto is_bit_reference_v = is_bit_reference<T>::value;

#if defined(NMTOOLS_HAS_VECTOR)
    template <>
    struct is_bit_reference<std::_Bit_reference> : std::true_type {};
#endif

    /**
     * @brief check if type T is boolean
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_boolean : std::false_type {};

    template <typename T>
    inline constexpr auto is_boolean_v = is_boolean<T>::value;

    /**
     * @brief specialization of is_boolean for actual boolean type
     * 
     * @tparam  
     */
    template <>
    struct is_boolean<bool> : std::true_type {};

    /** @} */ // end group traits

} // namespace nmtools::meta
#endif // NMTOOLS_META_TRAITS_HPP