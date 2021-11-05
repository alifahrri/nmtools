#ifndef NMTOOLS_META_TRAITS_HPP
#define NMTOOLS_META_TRAITS_HPP

#include <type_traits>
/** @todo use __has_include */
#include <array>
#if __has_include(<vector>)
    #include <vector> // @todo remove
    #define NMTOOLS_HAS_VECTOR 1
#else
    #define NMTOOLS_HAS_VECTOR 0
#endif
#include <complex> // @todo remove
#include <tuple>
#include <utility>
#include <variant>
#include <optional>

#include "nmtools/meta/common.hpp"

namespace nmtools::meta {

    /** @defgroup traits
    * Collections of type traits used accross the library
    * @{ 
    */

    using std::declval;
    using std::void_t;

    // TODO: cleanup metafunctions
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

    // TODO: remove metafunctions
    /* TODO : move (?) */
    using std::begin;
    using std::end;

    // TODO: remove metafunctions
    /**
     * @brief check if type T has member type size_type
     * 
     * @tparam T type to check
     * @tparam void 
     */
    template <typename T, typename = void>
    struct has_size_type : false_type {};

    /**
     * @brief specialization when T actually size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_size_type<T,
        std::void_t<typename T::size_type>
    > : true_type {};

    // TODO: remove metafunctions
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
    struct has_value_type : false_type {};

    // TODO: cleanup metafunctions
    /**
     * @brief specialization when T actually has value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_value_type<T, std::void_t<typename T::value_type> > : true_type {};

    /**
     * @brief helper variable template to check if T has member type value_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_value_type_v = has_value_type<T>::value;

    template <typename T>
    struct is_void : false_type {};

    template <>
    struct is_void<void> : true_type {};

    template <typename T>
    constexpr inline auto is_void_v  = is_void<T>::value;

    /**
     * @brief check if std::tuple_size<T> is valid for T
     * should be true for std::array, std::tuple, std::pair
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_tuple_size : false_type {};

    // TODO: remove metafunctions
    /**
     * @brief specialization of has_tuple_size when tuple_size<T> is well-formed
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct has_tuple_size<T, std::void_t<typename std::tuple_size<T>::type>> : true_type {};

    /**
     * @brief helper variable template to check if std::tuple_size<T> is valid
     * 
     * @todo test
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool has_tuple_size_v = has_tuple_size<T>::value;

    // TODO cleanup metafunctions
    /**
     * @brief helper alias template combining remove_cv and remove_reference
     * 
     * @tparam T 
     */
    template <typename T>
    using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

    // TODO: remove
    using std::tuple;

    /**
     * @brief check if given type is tuple kind.
     *
     * Note that this is not necessarily std::tuple,
     * this is intended to be more like tuple in concept.
     * The choice of the name, tuple, is from haskell Tuple.
     */
    template <typename>
    struct is_tuple : false_type {};

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
    struct is_bounded_array: false_type {};
    
    template<typename T, std::size_t N>
    struct is_bounded_array<T[N]> : true_type {};

    /**
     * @brief helper variable template to check if T is bounded array
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

    /**
     * @brief check if type T has operator at with size_type as single argument.
     * 
     * @tparam T type to check.
     * @tparam size_type argument type.
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_at : false_type {};

    // TODO: cleanup metafunctions
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

        // TODO: remove
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
     * @tparam typename customization point
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
        static constexpr auto value = [](){
            using expression = detail::expression_check<void,expr::square_bracket,T,size_type>;
            if constexpr (expression::value)
                return true;
            else return false;
        }();
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

    // TODO: cleanup metafunctions
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

    // TODO: cleanup metafunctions
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
     * @brief check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_integral_constant : false_type {};

    template <typename T>
    struct is_integral_constant<const T> : is_integral_constant<T> {};

    template <typename T>
    struct is_integral_constant<const T&> : is_integral_constant<T> {}; 

    /**
     * @brief helper inline variable to check if given type T is std::integral_constant
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_integral_constant_v = is_integral_constant<T>::value;

    /**
     * @brief check if given type T is specialization of template-template param primary_template
     * 
     * @tparam T type to check
     * @tparam primary_template primary template
     */
    template <typename T, template <typename...> typename primary_template>
    struct is_specialization : false_type {};

    template <template <typename...> typename primary_template, typename... Args>
    struct is_specialization<primary_template<Args...>, primary_template> : true_type {};

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
    struct is_bit_reference : false_type {};

    template <typename T>
    inline constexpr auto is_bit_reference_v = is_bit_reference<T>::value;

    /**
     * @brief check if type T is boolean
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_boolean : false_type {};

    template <typename T>
    inline constexpr auto is_boolean_v = is_boolean<T>::value;

    /**
     * @brief specialization of is_boolean for actual boolean type
     * 
     * @tparam  
     */
    template <>
    struct is_boolean<bool> : true_type {};

    /**
     * @brief Check if type T is compile-time index.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_constant_index : is_integral_constant<T> {}; 

    template <typename T>
    inline constexpr auto is_constant_index_v = is_constant_index<T>::value;

    /**
     * @brief Check if type T is num type.
     * 
     * Note that specializing std::is_arithmetic is undefined behaviour.
     * This traits exists to avoid UB while specializing similar concept is allowed.
     * THis is useful to allow reduce view that reduce the elements to single num.
     * The name "num" is inspired from haskell's `Num`.
     *
     * @tparam T type tot check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_num : std::is_arithmetic<T> {};

    template <typename T>
    constexpr inline auto is_num_v = is_num<T>::value;

    /**
     * @brief Check if type T is integer type.
     * 
     * Note that specializing std::is_integral is undefined behaviour.
     * This traits exists to avoid UB while specializing similar concept is allowed.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_integer : false_type {};

    template <typename T>
    constexpr inline auto is_integer_v = is_integer<T>::value;

    template <typename T, typename=void>
    struct is_integral : is_integer<T> {};

    template <typename T>
    constexpr inline auto is_integral_v = is_integral<T>::value;

#define NMTOOLS_IS_INTEGER_TRAIT(type) \
    template <> \
    struct is_integer<type> : true_type {};

    NMTOOLS_IS_INTEGER_TRAIT(short int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned short int)

    NMTOOLS_IS_INTEGER_TRAIT(int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned int)

    NMTOOLS_IS_INTEGER_TRAIT(long int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned long int)

    NMTOOLS_IS_INTEGER_TRAIT(long long int)
    NMTOOLS_IS_INTEGER_TRAIT(unsigned long long int)

#undef NMTOOLS_IS_INTEGER_TRAIT

    /**
     * @brief Check if type `T` is an index
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_index
    {
        static constexpr auto value = [](){
            return is_constant_index_v<T> || is_integer_v<T>;
        }();
    };

    template <typename T>
    inline constexpr auto is_index_v = is_index<T>::value;

    template <typename T>
    struct is_signed : false_type {};

// TODO: do not use true_type / false_type, define value instead
#define NMTOOLS_META_REGISTER_IS_SIGNED(type, signed) \
    template <> \
    struct is_signed<type> : std::signed##_type {}; \

    NMTOOLS_META_REGISTER_IS_SIGNED(int32_t,true);
    NMTOOLS_META_REGISTER_IS_SIGNED(int64_t,true);
    NMTOOLS_META_REGISTER_IS_SIGNED(int16_t,true);
    NMTOOLS_META_REGISTER_IS_SIGNED(int8_t, true);

    NMTOOLS_META_REGISTER_IS_SIGNED(uint32_t,false);
    NMTOOLS_META_REGISTER_IS_SIGNED(uint64_t,false);
    NMTOOLS_META_REGISTER_IS_SIGNED(uint16_t,false);
    NMTOOLS_META_REGISTER_IS_SIGNED(uint8_t, false);

#undef NMTOOLS_META_REGISTER_IS_SIGNED

    template <typename T>
    inline constexpr auto is_signed_v = is_signed<T>::value;

    template <typename T>
    struct is_unsigned
    {
        static constexpr auto value = !is_signed_v<T>;
    }; // is_unsigned

    template <typename T>
    inline constexpr auto is_unsigned_v = is_unsigned<T>::value;

    // TODO: remove
    /**
     * @brief 
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_index<T, enable_if_t<
        std::is_integral_v<T> ||
        meta::is_integral_constant_v<T>
    > > : true_type {};

    // TODO: do not directly use detail::fail_t,
    // define specific error type instead
    /**
     * @brief Return the length of fixed index array.
     *
     * By default, return fail_t type.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct fixed_index_array_size
    {
        static constexpr auto value = detail::fail_t{};
    };

    template <typename T, size_t N>
    struct fixed_index_array_size<T[N],enable_if_t<is_index_v<T>>>
    {
        static constexpr auto value = N;
    };

    template <typename T>
    static constexpr auto fixed_index_array_size_v = fixed_index_array_size<T>::value;

    /**
     * @brief Check if type T is fixed index array.
     * 
     * A fixed index array represent fixed-dim index/shape.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_fixed_index_array : false_type {};

    template <typename T>
    inline constexpr auto is_fixed_index_array_v = is_fixed_index_array<T>::value;

    template <typename T, size_t N>
    struct is_fixed_index_array<T[N],enable_if_t<is_index_v<T>>> : true_type {};

    /**
     * @brief Check if type T is hybrid_index_array.
     *
     * Has max size but resizeable.
     * Note that the max size represents maximum "dimension" of the array
     * instead of maximum "element" of the array.
     * Currently querying maximum "element" of an hybrid array
     * from the index/shape array is not supported.
     * 
     * @tparam T type to check
     */
    template <typename T, typename=void>
    struct is_hybrid_index_array : false_type {};

    template <typename T>
    inline constexpr auto is_hybrid_index_array_v = is_hybrid_index_array<T>::value;

    /**
     * @brief Check if type T is constant index array.
     * 
     * A constant index array represent index/shape at compile-time.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_constant_index_array : false_type {};

    template <typename T>
    inline constexpr auto is_constant_index_array_v = is_constant_index_array<T>::value;

    /**
     * @brief Check if type T is dynamic index array.
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_dynamic_index_array : false_type {};

    template <typename T>
    inline constexpr auto is_dynamic_index_array_v = is_dynamic_index_array<T>::value;

    /**
     * @brief Check if type `T` is index array
     * 
     * @tparam T type to check
     */
    template <typename T, typename=void>
    struct is_index_array
    {
        static constexpr auto value = [](){
            return is_fixed_index_array_v<T>
                || is_dynamic_index_array_v<T>
                || is_constant_index_array_v<T>
                || is_hybrid_index_array_v<T>;
        }();
    };

    template <typename T>
    constexpr inline auto is_index_array_v = is_index_array<T>::value;

    /**
     * @brief Check if type T is either type (variant with exactly 2 type).
     * 
     * The name is from haskell's Either type with Left and Right.
     *
     * @tparam T type to check
     * @tparam typename sfinae point
     */
    template <typename T, typename=void>
    struct is_either : false_type{};

    template <typename T>
    constexpr inline auto is_either_v = is_either<T>::value;

    /**
     * @brief Check if type T is optional type.
     *
     * The name is from haskell's Maybe type.
     * 
     * @tparam T type to check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct is_maybe : false_type {};

    template <typename T>
    constexpr inline auto is_maybe_v = is_maybe<T>::value;

    /**
     * @brief Check if type T is Nothing type (std::nullopt,..)
     * 
     * The name Nothing is from haskell maybe type
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_nothing : false_type {};

    template <typename T>
    constexpr inline auto is_nothing_v = is_nothing<T>::value;

    namespace error
    {
        struct GET_EITHER_LEFT_UNSUPPORTED : detail::fail_t {};
        struct GET_EITHER_RIGHT_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Get the Left type of Either
     * 
     * @tparam T 
     * @todo move to transform
     */
    template <typename T>
    struct get_either_left
    {
        using type = error::GET_EITHER_LEFT_UNSUPPORTED;
    };

    /**
     * @brief Get the Right type of Either
     * 
     * @tparam T 
     * @todo move to transform
     */
    template <typename T>
    struct get_either_right
    {
        using type = error::GET_EITHER_RIGHT_UNSUPPORTED;
    };

    template <typename T>
    using get_either_left_t = typename get_either_left<T>::type;

    template <typename T>
    using get_either_right_t = typename get_either_right<T>::type;

    /**
     * @brief Get the value type of maybe type
     * 
     * @tparam T type to check 
     * @tparam typename 
     * @todo move to transform
     */
    template <typename T, typename=void>
    struct get_maybe_type
    {
        using type = void;
    };

    template <typename T>
    using get_maybe_type_t = typename get_maybe_type<T>::type;

    /**
     * @brief Replace existing Left and Right from given either type
     * with new Left and Right.
     * 
     * @tparam either_t 
     * @tparam Left 
     * @tparam Right 
     * @todo move to transform
     */
    template <typename either_t, typename Left, typename Right>
    struct replace_either
    {
        using type = either_t;
    };

    template <typename either_t, typename Left, typename Right>
    using replace_either_t = typename replace_either<either_t,Left,Right>::type;

    /**
     * @brief Check if type T is fail type.
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_fail : std::is_base_of<detail::fail_t,T> {};

    template <typename T>
    constexpr inline auto is_fail_v = is_fail<T>::value;

    /** @} */ // end group traits

} // namespace nmtools::meta
#endif // NMTOOLS_META_TRAITS_HPP