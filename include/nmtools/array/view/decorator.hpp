#ifndef NMTOOLS_ARRAY_VIEW_DECORATOR_HPP
#define NMTOOLS_ARRAY_VIEW_DECORATOR_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/apply_at.hpp"

#include <cassert>

namespace nmtools::view
{
    using meta::is_fixed_size_ndarray_v;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    /**
     * @brief provide generic common implementation for view objects. 
     * 
     * @note implemented as decorator/mixin instead of 'interface'
     * @tparam view_t template template parameter
     * @tparam Ts arbitrary number of tparams for view_t
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct decorator_t : view_t<Ts...>
    {
        using view_type = view_t<Ts...>;
        // @note possibly const
        using array_type = typename view_type::array_type;

        /**
         * @todo
         *  - static assert if view_type array exists
         *  - has index member function that transform indices
         */

        /**
         * @brief return the dimensionality of the referred array
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const noexcept
        {
            // @note `this` must be constexpr when constexpr return value is desired
            if constexpr (meta::has_dim_v<meta::remove_cvref_t<view_type>>)
                return view_type::dim();
            // @note may be recursive
            else
                return ::nmtools::dim(view_type::array);
        } // dim()

        /**
         * @brief return the shape of this array
         * 
         * @return constexpr auto 
         * @see nmtools::vector_size
         * @see nmtools::matrix_size
         * @see nmtools::shape
         */
        constexpr decltype(auto) shape() const noexcept
        {
            using array_t = meta::remove_cvref_t<array_type>;
            if constexpr (meta::has_shape_v<meta::remove_cvref_t<view_type>>)
                return view_type::shape();
            else return ::nmtools::shape(view_type::array);
        } // shape

        /**
         * @brief immutable element acces to the referenced array
         * 
         * @tparam size_types size type(s) to array
         * @param indices 
         * @return constexpr auto
         * @todo make error handling configurable, e.g. throw/assert/optional
         * @note for fixed size, it is necessary to pass Array{} (value initialization) to dim since `this` may not be constant exprression
         * @see https://en.cppreference.com/w/cpp/language/value_initialization
         * @see nmtools::at
         */
        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices) const
        {
            // @note either using auto& or decltype(auto) for return type
            // since at(...) return auto&

            using common_t = std::common_type_t<size_types...>;
            using meta::has_funcnd_v;
            if constexpr (has_funcnd_v<view_type,size_types...>)
                return view_type::operator()(indices...);
            else {
                auto transformed_indices = view_type::index(indices...);

                using array_t = meta::remove_cvref_t<array_type>;
                constexpr auto n = sizeof...(size_types);
                // only perform assert if integral type is passed
                // otherwise assume indices is packed and pass to apply_at
                // to allow access from packed indices
                if constexpr (std::is_integral_v<common_t>)
                    // @todo static_assert whenever possible
                    assert (dim()==n); // tmp assertion

                // @note needs to initialize array_t since view_type::array may not be constant expression
                // @note flatten_t dim invocation differs from other view types @todo fix
                // if constexpr (meta::is_fixed_size_ndarray_v<array_t>)
                //     static_assert (detail::dim(array_t{})==n);
                // else
                //     assert (dim()==n);

                // call at to referred object, not to this
                return apply_at(view_type::array, transformed_indices);
            }
        } // operator()

        /**
         * @brief mutable element acces to the referenced array
         * 
         * @tparam size_types size type(s) to array
         * @param indices 
         * @return constexpr auto
         * @todo make error handling configurable, e.g. throw/assert/optional
         * @note for fixed size, it is necessary to pass Array{} (value initialization) to dim since `this` may not be constant exprression
         * @see https://en.cppreference.com/w/cpp/language/value_initialization
         * @see nmtools::at
         */
        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices)
        {
            // @note either using auto& or decltype(auto) for return type
            // since at(...) return auto&

            using common_t = std::common_type_t<size_types...>;
            using meta::has_funcnd_v;
            if constexpr (has_funcnd_v<view_type,size_types...>)
                return view_type::operator()(indices...);
            else {
                auto transformed_indices = view_type::index(indices...);

                using array_t = meta::remove_cvref_t<array_type>;
                constexpr auto n = sizeof...(size_types);
                // only perform assert if integral type is passed
                // otherwise assume indices is packed and pass to apply_at
                // to allow access from packed indices
                if constexpr (std::is_integral_v<common_t>)
                    // @todo static_assert whenever possible
                    assert (dim()==n); // tmp assertion

                // @note needs to initialize array_t since view_type::array may not be constant expression
                // @note flatten_t dim invocation differs from other view types @todo fix
                // if constexpr (meta::is_fixed_size_ndarray_v<array_t>)
                //     static_assert (detail::dim(array_t{})==n);
                // else
                //     assert (dim()==n);

                // call at to referred object, not to this
                return apply_at(view_type::array, transformed_indices);
            }
        } // operator()

    }; // decorator_t

    /**
     * @brief make view given parameters arrays
     * 
     * @tparam view_t template template parameter
     * @tparam Ts tparams for view_t, should be deducible from template argument deduction
     * @param arrays array to be viewed
     * @return constexpr auto 
     */
    template <template<typename...> typename view_t, typename...Ts>
    constexpr auto make_view(Ts&&...arrays)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        // @note requires nested brace so that view_t that takes
        // multiple value at instantiation can be instantiated
        return decorator_t<view_t,Ts...>{{arrays...}};
    } // make_view

    /**
     * @brief helper trait to check if type T is view
     * 
     * @tparam T type to check
     * @tparam typename sfinae/customization point
     */
    template <typename T, typename=void>
    struct is_view : std::false_type {};

    /**
     * @brief true case for helper trait to check if type T is view
     * 
     * @tparam view_t template template param corresponding to actual view
     * @tparam Ts template parameters to actual view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_view<decorator_t<view_t,Ts...>> : std::true_type {};

    /**
     * @brief helper variable template to check if type T is view
     * 
     * @tparam T type to check
     */
    template <typename T>
    static inline constexpr bool is_view_v = is_view<T>::value;

    /**
     * @brief get array_type
     * 
     * @tparam T type to transform
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct get_array_type
    {
        using type = void;
    }; // get_array_type

    /**
     * @brief specialization of get_array_type for view_type
     * 
     * @tparam view_t 
     * @tparam Ts 
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_array_type<decorator_t<view_t,Ts...>>
    {
        using view_type = decorator_t<view_t,Ts...>;
        using type = typename view_type::array_type;
    }; // get_array_type

    /**
     * @brief helper alias template for get_array_type
     * 
     * @tparam T type to transform
     * @see get_array_type
     */
    template <typename T>
    using get_array_type_t = typename get_array_type<T>::type;

    /**
     * @brief get array_type of possibly nested view
     *
     * For non view type, default implementations define `type` as `void`.
     * The caller site may check if the returned type is void to perform
     * specific handling/assert.
     * 
     * @tparam T type to transform
     * @tparam typename customization point, e.g. using enable_if_t or void_t
     */
    template <typename T, typename=void>
    struct get_underlying_array_type
    {
        using type = void;
    }; // get_underlying_array_type

    /**
     * @brief specialization of get_underlying_array_type for view type.
     * 
     * @tparam view_t 
     * @tparam Ts 
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_underlying_array_type<decorator_t<view_t,Ts...>>
    {
        using view_type = decorator_t<view_t,Ts...>;
        using array_type = get_array_type_t<view_type>;
        // need to remove cvref from array_type since is_view doesnt aware of it
        using type = std::conditional_t<is_view_v<meta::remove_cvref_t<array_type>>,
            typename get_underlying_array_type<meta::remove_cvref_t<array_type>>::type, array_type>;
    }; // get_underlying_array_type

    /**
     * @brief helper alias template for get_underlying_array_type
     * 
     * @tparam T type to transform
     * @see get_underlying_array_type
     */
    template <typename T>
    using get_underlying_array_type_t = typename get_underlying_array_type<T>::type;

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief sfinae-enabled matrix_size specialization for view type
     * 
     * @tparam view_t underlying view class template
     * @tparam Ts arguments to view_t
     * @param t 
     * @return std::enable_if_t<meta::is_array2d_v<view::decorator_t<view_t,Ts...>>,std::pair<size_t,size_t>> 
     */
    template <template<typename...> typename view_t, typename...Ts>
    constexpr auto matrix_size(const view::decorator_t<view_t,Ts...>& t)
        -> std::enable_if_t<meta::is_array2d_v<view::decorator_t<view_t,Ts...>>,std::pair<size_t,size_t>>
    {
        auto [rows, cols] = t.shape();
        return {rows,cols};
    } // matrix_size

    /**
     * @brief sfinae-enable specializatoin for vector_size
     * 
     * @tparam T view type
     * @param t viewed vector
     * @return std::enable_if_t<view::is_view_v<T> && meta::is_array1d_v<T>, size_t> 
     * @note vector_size has sfinae overload that enabled for is_fixed_size_vector
     */
    template <typename T>
    constexpr auto vector_size(const T& t)
        -> std::enable_if_t<view::is_view_v<T> && meta::is_array1d_v<T> && !meta::is_fixed_size_vector_v<T>, size_t>
    {
        auto [n] = t.shape();
        return n;
    } // vector_size
} // namespace nmtools

namespace nmtools::meta
{
    // make is_view available from namespace meta
    using view::is_view;
    using view::is_view_v;

    // make get_array_type available from namespace meta
    using view::get_array_type;
    using view::get_array_type_t;

    // make get_underlying_array_type available from namespace meta
    using view::get_underlying_array_type;
    using view::get_underlying_array_type_t;

    /**
     * @brief specialization of is_array1d for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @note for specific view that may requires to specialize this, it is possible to do so by specialize "view_t" for the desired view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_array1d<view::decorator_t<view_t,Ts...>,void>
        : is_array1d<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of is_array2d for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @note for specific view that may requires to specialize this, it is possible to do so by specialize "view_t" for the desired view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_array2d<view::decorator_t<view_t,Ts...>>
        : is_array2d<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of is_array3d for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @note for specific view that may requires to specialize this, it is possible to do so by specialize "view_t" for the desired view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_array3d<view::decorator_t<view_t,Ts...>>
        : is_array3d<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
} // namespace nmtools::meta

namespace nmtools
{

    template <template<typename...> typename view_t, typename...Ts>
    struct meta::fixed_ndarray_shape<view::decorator_t<view_t,Ts...>>
    {
        /**
         * @brief helper function to deduce the value of the matrix
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (meta::is_fixed_size_ndarray_v<view_t<Ts...>>)
                return meta::fixed_ndarray_shape_v<view_t<Ts...>>;
            else return detail::fail_t{};
        } // _get()
    
        static inline constexpr auto value = _get();
        // @note that remove_cvref_t here is necessary since decltype(value) may be const
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // meta::fixed_ndarray_shape

    /**
     * @brief specialization of meta::fixed_matrix_size for view type (view::decorator_t<...>).
     * 
     * Metafunction to get the size of matrix at compile-time. This specialization also
     * serves as entry point for checking the underlying view type (view_t<Ts...>) if that
     * underlying view is_fixed_size_matrix then calls meta::fixed_matrix_size_v for that underlying view,
     * otherwise this should fail. Note that meta::is_fixed_size_matrix has specialization
     * for type(s) that its specialization of meta::fixed_matrix_size has value, value_type, and the value_type
     * is not void.
     * 
     * @tparam view_t template-template parameter corresponding to the underlying view type
     * @tparam Ts template parameters to underlying type
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct meta::fixed_matrix_size<view::decorator_t<view_t,Ts...>>
    {
        /**
         * @brief helper function to deduce the value of the matrix
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (meta::is_fixed_size_matrix_v<view_t<Ts...>>)
                return meta::fixed_matrix_size_v<view_t<Ts...>>;
            else return detail::fail_t{};
        } // _get()
    
        static inline constexpr auto value = _get();
        // @note that remove_cvref_t here is necessary since decltype(value) may be const
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // meta::fixed_matrix_size

    template <template<typename...> typename view_t, typename...Ts>
    struct meta::fixed_vector_size<view::decorator_t<view_t,Ts...>>
    {
        /**
         * @brief helper function to deduce the value of the matrix
         * 
         * @return constexpr auto 
         */
        static constexpr auto _get()
        {
            if constexpr (meta::is_fixed_size_vector_v<view_t<Ts...>>)
                return meta::fixed_vector_size_v<view_t<Ts...>>;
            else return detail::fail_t{};
        } // _get()

        static inline constexpr auto value = _get();
        // @note that remove_cvref_t here is necessary since decltype(value) may be const
        using value_type = detail::fail_to_void_t<meta::remove_cvref_t<decltype(value)>>;
    }; // meta::fixed_vector_size
} // namespace nmtools

namespace nmtools::meta
{
    /**
     * @brief specializtion of metafunction get_vector_value_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @todo remove
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_vector_value_type<view::decorator_t<view_t,Ts...>>
        : get_vector_value_type<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of metafunction get_matrix_value_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @todo remove
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_matrix_value_type<view::decorator_t<view_t,Ts...>>
        : get_matrix_value_type<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};

    /**
     * @brief specialization of metafunction get_ndarray_value_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     * @todo remove
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_ndarray_value_type<view::decorator_t<view_t,Ts...>>
        : get_ndarray_value_type<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of metafunction get_element_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_element_type<view::decorator_t<view_t,Ts...>>
        : get_element_type<meta::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_DECORATOR_HPP