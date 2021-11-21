#ifndef NMTOOLS_ARRAY_UTILITY_SHAPE_HPP
#define NMTOOLS_ARRAY_UTILITY_SHAPE_HPP

#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::impl::error
{
    template <typename...>
    struct LEN_UNSUPPORTED : meta::detail::fail_t {};

    template <typename...>
    struct SHAPE_UNSUPPORTED : meta::detail::fail_t {};

    template <typename...>
    struct DIM_UNSUPPORTED : meta::detail::fail_t {};

    template <typename...>
    struct GET_IF_UNSUPPORTED : meta::detail::fail_t {};
} // namespace nmtools::impl::error

namespace nmtools::impl
{
    template <typename T, typename=void>
    struct len_t
    {
        constexpr auto operator()([[maybe_unused]] const T& a) const noexcept
        {
            if constexpr (meta::is_fixed_size_ndarray_v<T>) {
                constexpr auto shape = meta::fixed_ndarray_shape_v<T>;
                return nmtools::at(shape,meta::ct_v<0>);
            } else if constexpr (is_none_v<T>) {
                return 0;
            } else if constexpr (meta::has_shape_v<T>) {
                auto shape = a.shape();
                return nmtools::at(shape,meta::ct_v<0>);
            } else {
                using type = error::LEN_UNSUPPORTED<T>;
                return type{};
            }
        } // operator()
    }; // len_t

    template <typename T>
    inline constexpr auto len = len_t<T>{};
} // namespace nmtools::impl

namespace nmtools
{
    template <typename array_t>
    constexpr auto len(const array_t& array)
    {
        return impl::len<array_t>(array);
    }

    template <typename T, size_t N>
    constexpr auto len(const T(&)[N])
    {
        return N;
    } // len
} // namespace nmtools

namespace nmtools::impl
{
    namespace detail
    {
        // TODO: remove
        /**
         * @brief repeat t N times as array
         * 
         * @tparam N desired number for t to be repeated
         * @tparam T 
         * @param t value to be repeated
         * @return constexpr auto 
         */
        template <size_t N, typename T>
        constexpr auto repeat(const T& t)
        {
            auto res = meta::make_array_type_t<T,N>{};
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                get<i>(res) = t;
            });
            return res;
        } // repeat

    } // namespace detail

    template <typename T, typename=void>
    struct shape_t
    {
        using array_t = T;
        constexpr auto operator()(const T& array) const noexcept
        {
            // allow scalar and ndarray
            constexpr auto constrained = [](auto a){
                using type = meta::type_t<meta::remove_cvref_t<decltype(a)>>;
                return meta::is_fixed_size_ndarray_v<type> || meta::has_shape_v<type>
                    || (meta::nested_array_dim_v<type> > 0)
                    || (meta::is_array1d_v<type> && meta::has_size_v<type>)
                    || (meta::is_num_v<type>)
                    || (meta::is_fixed_index_array_v<type>);
            };
            constexpr auto t_array = meta::as_value_v<array_t>;
            // static_assert (
            //     constrained(t_array) || constrained_either(t_array)
            //     , "unsupported shape; only support fixed-shape array or array has .shape() or scalar type"
            // );
            if constexpr (!constrained(t_array)) {
                return error::SHAPE_UNSUPPORTED<T>{};
            }
            // for scalar type, simply return None
            else if constexpr (meta::is_num_v<array_t>)
                return None;
            // check for fixed-shape array, should capture all kind of fixed-size array
            else if constexpr (meta::is_fixed_size_ndarray_v<array_t>) {
                // @todo whenever the shape is constant return it as compile-time constant
                // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
                return meta::fixed_ndarray_shape_v<array_t>;
            }
            else if constexpr (meta::is_fixed_index_array_v<array_t>)
                return meta::fixed_index_array_size_v<array_t>;
            // TODO: remove support for nested dynamic vector
            // check for dynamic-shape array but fixed-dimension array
            else if constexpr (meta::nested_array_dim_v<array_t> > 0) {
                constexpr auto N = meta::nested_array_dim_v<array_t>;
                auto shape_ = meta::make_array_type_t<size_t,N>{};
                meta::template_for<N>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    // example for 3dim nested dynamic array
                    // vector<vector<vector<>>>; N==3
                    // i==0:
                    // s: size_t
                    // i==1:
                    // indices = array<size_t,1>{0};
                    // a: vector<vector>>
                    // s: size_t
                    // i==2:
                    // indices = array<size_t,2>{0,0};
                    // s: size_t
                    if constexpr (i==0) {
                        auto s = nmtools::len(array);
                        nmtools::get<i>(shape_) = s;
                    }
                    else {
                        auto indices = detail::repeat<i>(0ul);
                        auto a = apply_at(array, indices);
                        // assuming nested array has size(a), which it should
                        auto s = nmtools::len(a);
                        nmtools::get<i>(shape_) = s;
                    }
                });
                return shape_;
            }
            else {
                return array.shape();
            }
        } // operator()
    }; // shape_t

    template <typename T>
    inline constexpr auto shape = shape_t<T>{};
} // namespace nmtools::impl

namespace nmtools::impl
{
    template <typename T, typename=void>
    struct get_if_t
    {
        template <typename U>
        constexpr auto operator()(const T*) const noexcept
        {
            return error::GET_IF_UNSUPPORTED<T>{};
        }
    }; // get_if_t

    template <typename T>
    constexpr inline auto get_if = get_if_t<T>{};
} // namespace nmtools::impl

namespace nmtools
{

    /**
     * @brief Helper function to return the value of Either object.
     * 
     * @tparam T 
     * @param t 
     * @return constexpr auto 
     */
    template <typename U, typename T>
    constexpr auto get_if(const T* t)
    {
        constexpr auto get_if = impl::get_if<T>;
        return get_if.template operator()<U>(t);
    } // get_if

    /**
     * @brief return the shape of an array
     *
     * This function should work for fixed-size ndarray, fixed-dim ndarray, array1d, or array that has .shape().
     * 
     * @tparam array_t array type
     * @param array
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto shape(const array_t& array)
    {
        // TODO: handle maybe type
        if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using left_shape_t  = decltype(shape(meta::declval<left_t>()));
            using right_shape_t = decltype(shape(meta::declval<right_t>()));
            using shape_t = meta::replace_either_t<array_t,left_shape_t,right_shape_t>;
            if (auto lptr = nmtools::get_if<left_t>(&array)) {
                return shape_t{shape(*lptr)};
            } else /* if (auto ptr = nmtools::get_if<right_t>(&array)) */ {
                auto rptr = nmtools::get_if<right_t>(&array);
                return shape_t{shape(*rptr)};
            }
        } else {
            return impl::shape<array_t>(array);
        }
    } // shape
}

namespace nmtools::impl
{
    template <typename array_t>
    struct dim_t
    {
        constexpr auto operator()([[maybe_unused]] const array_t& array) const noexcept
        {
            // prefer for explicit call to dim() first
            if constexpr (meta::has_dim_v<array_t>)
                return array.dim();
            else if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
                // @todo whenever the dim is constant return it as compile-time constant
                // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
                // return meta::index_constant<meta::fixed_ndarray_dim_v<array_t>>{};
                return meta::fixed_dim_v<array_t>;
            }
            else {
                auto shape = nmtools::shape(array);
                return nmtools::len(shape);
            }
        }
    }; // dim_t

    template <typename array_t>
    inline constexpr auto dim = dim_t<array_t>{};
} // namespace nmtools::impl

namespace nmtools
{
    /** @addtogroup utility
    * @ingroup array
    * Collections of utility functions for array-like objects
    * @{
    */

    /**
     * @brief return the number of dimension of an array
     *
     * This fn should work with an array that is fixed-dim or the array has .dim().
     * 
     * @tparam array_t array type
     * @param array 
     * @return constexpr auto 
     * @see meta::fixed_dim_v
     */
    template <typename array_t>
    constexpr auto dim(const array_t& array)
    {
        return impl::dim<array_t>(array);
    } // dim

    /** @} */ // end group utility
} // namespace nmtools

namespace nmtools::meta
{
    /**
     * @brief Return the index type of an array.
     * 
     * By default, deduce using expression: shape(array).
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct get_index_type<array_t, enable_if_t<is_ndarray_v<array_t>>>
    {
        using type = get_element_or_common_type_t<decltype(nmtools::shape(meta::declval<array_t>()))>;
    }; // get_index_type
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_UTILITY_SHAPE_HPP

#include "nmtools/array/impl/stl.hpp"