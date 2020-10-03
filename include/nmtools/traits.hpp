#ifndef NMTOOLS_TRAITS_HPP
#define NMTOOLS_TRAITS_HPP

#include <type_traits>
/** @todo use __has_include */
#include <array>
#include <vector>
#include <complex>

namespace nmtools::traits {

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
     * @brief check if T t{} are:
     * - t[0][0][0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename = void>
    struct is_array3d : false_type {};

    template <typename T>
    struct is_array3d<T, 
        void_t<decltype(declval<T>()[0][0][0])>
    > : true_type {};

    template <typename T>
    inline constexpr bool is_array3d_v = is_array3d<T>::value;

    /**
     * @brief check if T t{} are:
     * - t[0][0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename = void>
    struct is_array2d : false_type {};

    template <typename T>
    struct is_array2d<T, 
        void_t<decltype(declval<T>()[0][0])> 
    > : true_type {};

    template <typename T>
    inline constexpr bool is_array2d_v = is_array2d<T>::value;

    /**
     * @brief check if T t{} are:
     * - t[0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename = void>
    struct is_array1d : false_type {};

    template <typename T>
    struct is_array1d<T, 
        void_t<decltype(declval<T>()[0])>
    > : true_type {};

    /**
     * @brief helper variable template to check if T is 1d array-like
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_array1d_v = is_array1d<T>::value;

    /**
     * @brief check if T is vector-like, (in math terms, not container terms)
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_vector_like : is_array1d<T> {};

    template <typename T>
    inline constexpr bool is_vector_like_v = is_vector_like<T>::value;

    /**
     * @brief check if T is matrix-like
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_matrix_like : is_array2d<T> {};

    template <typename T>
    inline constexpr bool is_matrix_like_v = is_matrix_like<T>::value;

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
    template <typename T, typename = void>
    struct is_resizeable : std::false_type {};

    /**
     * @brief specialization of is_resizeable when T is resizeable using size_t
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_resizeable<T, 
        std::void_t<
            disable_if_has_size_type_t<T>,
            decltype(std::declval<T>().resize(std::declval<size_t>()))
        >
    > : std::true_type {};

    /**
     * @brief specialization of is_resizeable when T is resizeable using T::size_type
     * 
     * @tparam T type to check
     */
    template <typename T>
    struct is_resizeable<T, 
        std::void_t<
            enable_if_has_size_type_t<T>,
            decltype(std::declval<T>().resize(std::declval<typename T::size_type>()))
        >
    > : std::true_type {};

    /**
     * @brief helper variable template to check if T is resizeable
     * 
     * @tparam T type to check
     */
    template <typename T>
    static constexpr auto is_resizeable_v = is_resizeable<T>::value;

    /**
     * @brief check if T can be resized with 2 arguments, e.g. declval<T>().resize(i,i)
     * 
     * @tparam T type to check
     * @tparam void 
     */
    template <typename T, typename = void>
    struct is_resizeable2d : std::false_type {};

    template <typename T>
    struct is_resizeable2d<T, 
        std::void_t<
            disable_if_has_size_type_t<T>,
            decltype(declval<T>().resize(declval<size_t>(),declval<size_t>()))
        >
    > : true_type {};

    template <typename T>
    struct is_resizeable2d<T, 
        std::void_t<
            enable_if_has_size_type_t<T>,
            decltype(declval<T>().resize(declval<typename T::size_type>(),declval<typename T::size_type>()))
        >
    > : true_type {};

    template <typename T>
    static constexpr auto is_resizeable2d_v = is_resizeable2d<T>::value;

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
     * @brief check if T has square bracket operator ([]) with size_type as arguments.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_square_bracket : false_type {};

    /**
     * @brief specialization of has_square_bracket for true case.
     * Enabled if T has square bracket operator with size_type as argument,
     * e.g. declval<T>()[i], with i of type size_type, is well-formed.
     * 
     * @tparam T 
     * @tparam size_type 
     */
    template <typename T, typename size_type>
    struct has_square_bracket<T,size_type,
        void_t<decltype(declval<T>()[declval<size_type>()])>
    > : true_type {};

    /**
     * @brief helper variable template for has_square_bracket
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_square_bracket_v = has_square_bracket<T,size_type>::value;

    /**
     * @brief check if T has bracket operator (()) with size_type as argument
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     * @tparam typename=void 
     */
    template <typename T, typename size_type, typename=void>
    struct has_bracket : false_type {};

    /**
     * @brief specialization of has_bracket for true case.
     * Enabled if T has bracket operator with size_type as argument,
     * e.g. declval<T>()(i), with i of type size_type, is well-formed.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    struct has_bracket<T,size_type,
        void_t<decltype(declval<T>()(declval<size_type>()))>
    > : true_type {};

    /**
     * @brief helper variable template for has_bracket.
     * 
     * @tparam T type to check
     * @tparam size_type argument type
     */
    template <typename T, typename size_type>
    inline constexpr bool has_bracket_v = has_bracket<T,size_type>::value;

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
     * @brief traits to check if type T is fixed-size matrix
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct is_fixed_size_matrix : std::false_type {};

    /**
     * @brief helper variable template for is_fixed_size_matrix
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_fixed_size_matrix_v = is_fixed_size_matrix<T>::value;

    /**
     * @brief trait to check if type T is fixed-size vector (as in math vector, not container ones).
     * 
     * @tparam T type to check
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct is_fixed_size_vector : false_type {};

    /**
     * @brief specializaton fo is_fixed_size_vector for raw array type.
     * 
     * @tparam T element type of raw array, automatically deduced
     * @tparam N size of raw array, automatically deduced
     */
    template <typename T, size_t N>
    struct is_fixed_size_vector<T[N]> : true_type {};

    /**
     * @brief helper variable template for is_fixed_size_vector.
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_fixed_size_vector_v = is_fixed_size_vector<T>::value;

    template <typename T>
    struct is_dynamic_size_matrix : std::negation<is_fixed_size_matrix<T>> {};

    template <typename T>
    inline constexpr bool is_dynamic_size_matrix_v = is_dynamic_size_matrix<T>::value;

    template <typename T>
    struct is_dynamic_size_vector : std::negation<is_fixed_size_vector<T>> {};

    template <typename T>
    inline constexpr bool is_dynamic_size_vector_v = is_dynamic_size_vector<T>::value;
    
    /** @} */ // end group traits

} // namespace nmtools::traits
#endif // NMTOOLS_TRAITS_HPP