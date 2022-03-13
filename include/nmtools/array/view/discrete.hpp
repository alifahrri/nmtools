#ifndef NMTOOLS_ARRAY_VIEW_DISCRETE_HPP
#define NMTOOLS_ARRAY_VIEW_DISCRETE_HPP

#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::view
{
    template <typename T, typename=void>
    struct is_discrete_view : meta::false_type {};

    template <typename T>
    static inline constexpr bool is_discrete_view_v = is_discrete_view<T>::value;

    /**
     * @brief A discrete view, a view that can't be composed at element-level.
     * 
     * @tparam view_t 
     * @tparam Ts 
     */
    template <template<typename...>typename view_t, typename...Ts>
    struct discrete_t : view_t<Ts...>
    {
        using view_type  = view_t<Ts...>;
        // force view_t to define array_type
        using array_type = typename view_type::array_type;

        // TODO: only enable if view_type has valid shape
        // TODO: check if view_type has shape member variable
        // Then look for member function
        constexpr auto shape() const noexcept
        {
            return view_type::dst_shape;
        } // shape

        // TODO: only enable if view_type has valid shape/dim
        // TODO: check if view_type has dim member variable
        // Then look for shape member variable to compute dim,
        // otherwise look for member function
        constexpr auto dim() const noexcept
        {
            return len(view_type::dst_shape);
        } // dim

        template <typename array_t>
        constexpr operator array_t () const // TODO: set noexcept specifier
        {
            constexpr auto array_vtype = [](){
                if constexpr (meta::is_maybe_v<array_t>) {
                    using type = meta::get_maybe_type_t<array_t>;
                    return meta::as_value_v<type>;
                } else {
                    using type = array_t;
                    return meta::as_value_v<type>;
                }
            }();
            using ndarray_t = meta::type_t<decltype(array_vtype)>;
            // TODO: make sure array_t is not view
            static_assert( meta::is_ndarray_v<ndarray_t> && !is_discrete_view_v<ndarray_t>
                , "cant cast discrete view, desired type is not ndarray"
            );

            auto output = ndarray_t {};
            // assume view_type has eval and return status
            auto status = view_type::eval(output);

            if constexpr (meta::is_maybe_v<array_t>) {
                if (status) {
                    return array_t{output};
                } else {
                    return array_t{}; // Nothing
                }
            } else {
                // TODO: check if 
                nmtools_cassert( status, "failed to eval the view" );
                return output;
            }
        } // operator array_t ()
    }; // discrete_t

    template <template<typename...> typename view_t, typename...Ts>
    struct is_discrete_view<discrete_t<view_t,Ts...>> : meta::true_type {};
} // namespace nmtools::view

namespace nmtools::meta
{
    template <template<typename...>typename view_t, typename...Ts>
    struct get_element_type<
        view::discrete_t< view_t, Ts... >
    >
    {
        static constexpr auto vtype = [](){
            using view_type = view::discrete_t< view_t, Ts... >;
            using type = get_element_type_t<remove_cvref_pointer_t<typename view_type::array_type>>;
            return as_value_v<type>;
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_element_type

    // TODO: implement is_ndarray
    // TODO: decide how discrete_t interact with other view
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_DISCRETE_HPP