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

    template <typename D, typename = void>
    struct is_std_array : false_type {};

    template <typename D>
    struct is_std_array<D, enable_if_t<
        std::is_same_v<
            D, std::array<typename D::value_type, std::tuple_size<D>::value>
        > // is_same
    > /* enable_if */ > : true_type {};

    template <typename T>
    inline constexpr bool is_std_array_v = is_std_array<T>::value;

    template <typename D, typename = void>
    struct is_std_vector : false_type {};

    template <typename D>
    struct is_std_vector<D, std::enable_if_t<
        std::is_same_v<
            D, std::vector<typename D::value_type>
        > // is_same
    > /* enable_if */ > : true_type {};

    template <typename D, typename = void>
    struct has_push_back_op : false_type {};

    template <typename D>
    struct has_push_back_op<D, void_t<
            decltype(std::declval<D>().push_back(std::declval<typename D::value_type>()))
    > /* void_t */ > : true_type {};

    template <typename T, typename = void>
    struct is_std_complex : false_type {};

    template <typename T>
    struct is_std_complex<T, enable_if_t<
        std::is_same_v< 
            T, std::complex< typename T::value_type > 
        > // is_same
    > /* enable_if */ > : true_type {};

    template <typename T, typename = void, typename = void, typename = void, typename = void>
    struct is_insertable : false_type {};

    template <typename T, typename U>
    struct is_insertable<T, U, void_t< 
        decltype(declval<T>().insert(declval<T>().begin(),declval<const U&>()))
    >, void, void > : true_type {};

    template <typename T, typename I, typename U>
    struct is_insertable<T, I, U, std::void_t< 
        decltype(declval<T>().insert(declval<I>(),declval<const U&>()))
    >, void > : std::true_type {};

    template <typename T, typename I, typename B, typename E>
    struct is_insertable<T, I, B, E, std::void_t< 
        decltype(declval<T>().insert(declval<I>(),declval<B>(),declval<E>()))
    > > : std::true_type {};

    template <typename T, typename = void>
    struct is_clearable : std::false_type {};

    template <typename T>
    struct is_clearable<T, std::enable_if_t<
        std::is_same_v<
            decltype(declval<T>().clear()),void
        > // is_same
    > /* enable_if */ > : std::false_type {};

    template <typename T, typename = void>
    struct has_ref_square_bracket_operator : std::false_type {};

    template <typename T>
    struct has_ref_square_bracket_operator<T, enable_if_t< 
        !std::is_const<decltype(declval<T>()[size_t{}])>::value &&
        std::is_reference<decltype(declval<T>()[size_t{}])>::value
    > > : std::true_type {};

    /* TODO: remove */
    template <typename T, typename = void>
    struct is_2d_array : false_type {};

    /* TODO: remove */
    template <typename T>
    struct is_2d_array<T, void_t<decltype(declval<T>()[0][0])> 
    > : true_type {};

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
        void_t<decltype(declval<T>()[0][0]), enable_if_t<!is_array3d_v<T>> > 
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
        void_t<decltype(declval<T>()[0]), enable_if_t<!is_array2d_v<T>> >
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

    /* TODO: remove */
    template <typename T, typename U, typename = void>
    struct multiplicative : std::false_type {};

    /* TODO: remove */
    template <typename T, typename U>
    struct multiplicative<T, U, std::void_t<
        decltype(std::declval<T>() * std::declval<U>())
    > > : std::true_type {};

    /* TODO: remove */
    template <typename T, typename U, typename = void>
    struct additive : std::false_type {};

    /* TODO: remove */
    template <typename T, typename U>
    struct additive<T, U, std::void_t<
        decltype(std::declval<T>() + std::declval<U>())
    > > : std::true_type {};

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

    template <typename T, typename = void>
    struct has_transpose_op : std::false_type {};

    template <typename T>
    struct has_transpose_op<T, std::void_t<
        decltype(std::declval<T>().transpose())
    > > : std::true_type {};

    template <typename T, typename = void>
    struct is_transposeable : std::false_type {};

    template <typename T>
    struct is_transposeable<T, std::enable_if_t< 
        std::is_arithmetic_v<T> || has_transpose_op<T>::value 
    > > : std::true_type {};

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

    template <typename T, typename = void>
    struct is_indexable : std::false_type {};
    template <typename T>
    struct is_indexable<T, std::void_t<decltype(std::declval<T>()[size_t{}])> > : std::true_type {};

    template <typename T, typename = void>
    struct is_resizeable : std::false_type {};
    template <typename T>
    struct is_resizeable<T, 
        std::void_t<decltype(std::declval<T>().resize(std::declval<typename T::size_type>()))> >
    : std::true_type {};

    template <typename T>
    static constexpr auto is_resizeable_v = is_resizeable<T>::value;

    template <typename ...T>
    struct all_iterable {
        constexpr static bool value = std::conjunction_v<is_iterable<T>...>;
    };

    template <typename ...T>
    struct all_indexable {
        constexpr static bool value = std::conjunction_v<is_indexable<T>...>;
    };

    template <typename ...T>
    constexpr bool all_iterable_v = all_iterable<T...>::value;

    template <typename ...T>
    constexpr bool all_indexable_v = all_indexable<T...>::value;

    template <typename T>
    using is_std_array_or_vector = std::disjunction<is_std_array<std::decay_t<T>>,is_std_vector<std::decay_t<T>>>;

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
     * @tparam T 
     * @tparam typename=void 
     */
    template <typename T, typename=void>
    struct get_container_value_type { using type = void; };

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

} // namespace nmtools::traits

#endif // NMTOOLS_TRAITS_HPP