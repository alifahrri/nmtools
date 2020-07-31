#ifndef NMTOOLS_TRAITS_HPP
#define NMTOOLS_TRAITS_HPP

#include <type_traits>
#include <array>
#include <vector>
#include <complex>

namespace nmtools::traits {

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
     * - t[0][0][0] is invalid
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
     * - t[0][0] is invalid
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

    template <typename T, typename U>
    struct is_multiplicative<T, U, std::void_t<
        decltype(std::declval<T>() * std::declval<U>())
    > > : std::true_type {};

    /**
     * @brief helper variable template to check if
     * T and U is multiplicative
     * 
     * @tparam T 
     * @tparam U 
     */
    template <typename T, typename U>
    inline constexpr bool is_multiplicative_v = is_multiplicative<T,U>::value;

    /**
     * @brief check if T() + U() is valid
     * 
     * @tparam T 
     * @tparam U 
     * @tparam void 
     */
    template <typename T, typename U, typename = void>
    struct is_additive : std::false_type {};

    template <typename T, typename U>
    struct is_additive<T, U, std::void_t<
        decltype(std::declval<T>() + std::declval<U>())
    > > : std::true_type {};

    template <typename T, typename U>
    inline constexpr bool is_additive_v = is_additive<T,U>::value;

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

    template <typename T>
    using enable_if_has_size_type = std::enable_if<has_size_type_v<T>>;

    template <typename T>
    using enable_if_has_size_type_t = typename enable_if_has_size_type<T>::type;

    template <typename T>
    using disable_if_has_size_type = std::enable_if<!has_size_type_v<T>>;

    template <typename T>
    using disable_if_has_size_type_t = typename disable_if_has_size_type<T>::type;

    template <typename T, typename = void>
    struct is_resizeable : std::false_type {};

    template <typename T>
    struct is_resizeable<T, 
        std::void_t<
            disable_if_has_size_type_t<T>,
            decltype(std::declval<T>().resize(std::declval<size_t>()))
        >
    > : std::true_type {};

    template <typename T>
    struct is_resizeable<T, 
        std::void_t<
            enable_if_has_size_type_t<T>,
            decltype(std::declval<T>().resize(std::declval<typename T::size_type>()))
        >
    > : std::true_type {};

    template <typename T>
    static constexpr auto is_resizeable_v = is_resizeable<T>::value;

    /**
     * @brief check if std::tuple_size<T> is valid for T
     * should be true for std::array, std::tuple, std::pair
     * 
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct has_tuple_size : std::false_type {};

    template <typename T>
    struct has_tuple_size<T, std::void_t<typename std::tuple_size<T>::type>> : std::true_type {};

    /**
     * @brief helper variable template to check if std::tuple_size<T> is valid
     * 
     * @todo test
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool has_tuple_size_v = has_tuple_size<T>::value;

    /**
     * @brief get the velue type of container T via decltype, has void member type if failed
     * - using type = decltype(std::declval<T>()[0]); 
     * 
     * @tparam T type to check
     * @tparam typename=void 
     * @todo move to meta
     */
    template <typename T, typename=void>
    struct get_container_value_type { using type = void; };

    /**
     * @brief get the velue type of container T via decltype, has void member type if failed
     * 
     * @tparam T type to check
     * @todo move to meta
     */
    template <typename T>
    struct get_container_value_type<T,std::void_t<decltype(std::declval<T>()[0])>> 
    { 
        using type = decltype(std::declval<T>()[0]);
    };

    /**
     * @brief helper alias template to get the value type of container T
     * 
     * @tparam T 
     */
    template <typename T>
    using get_container_value_type_t = typename get_container_value_type<T>::type;

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

} // namespace nmtools::traits

#endif // NMTOOLS_TRAITS_HPP