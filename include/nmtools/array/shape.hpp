#ifndef NMTOOLS_ARRAY_UTILITY_SHAPE_HPP
#define NMTOOLS_ARRAY_UTILITY_SHAPE_HPP

#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/constants.hpp"

/* TODO: should we include array and std::array specialization here? */
#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools
{
    /** @addtogroup utility
    * @ingroup array
    * Collections of utility functions for array-like objects
    * @{
    */

    using std::get;

    namespace detail
    {
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
            auto res = std::array<T,N>{};
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                std::get<i>(res) = t;
            });
            return res;
        } // repeat

    } // namespace detail

    template <typename array_t>
    constexpr auto len(const array_t& array);

    template <typename T>
    constexpr auto len(const std::vector<T>& array)
    {
        return array.size();
    } // len

    template <typename T, size_t N>
    constexpr auto len(const std::array<T,N>&)
    {
        return N;
    } // len

    template <typename T, size_t N>
    constexpr auto len(const T(&)[N])
    {
        return N;
    } // len

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
        // allow scalar and ndarray
        constexpr auto constrained = [](auto a){
            using type = meta::type_t<meta::remove_cvref_t<decltype(a)>>;
            return meta::is_fixed_size_ndarray_v<type> || meta::has_shape_v<type>
                || (meta::nested_array_dim_v<type> > 0)
                || (meta::is_array1d_v<type> && meta::has_size_v<type>)
                || (meta::is_num_v<type>)
                || (meta::is_fixed_index_array_v<type>);
        };
        // for either type, both Left and Right must satisfy constraint (scalar or ndarray)
        constexpr auto constrained_either = [constrained](auto a){
            using type = meta::type_t<meta::remove_cvref_t<decltype(a)>>;
            [[maybe_unused]] auto lhs = meta::as_value_v<meta::get_either_left_t<type>>;
            [[maybe_unused]] auto rhs = meta::as_value_v<meta::get_either_right_t<type>>;
            if constexpr (meta::is_either_v<type>)
                return constrained(lhs) && constrained(rhs);
            else return false;
        };
        constexpr auto t_array = meta::as_value<array_t>{};
        static_assert (
            constrained(t_array) || constrained_either(t_array)
            , "unsupported shape; only support fixed-shape array or array has .shape() or scalar type"
        );
        if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using left_shape_t  = decltype(shape(std::declval<left_t>()));
            using right_shape_t = decltype(shape(std::declval<right_t>()));
            using shape_t = meta::replace_either_t<array_t,left_shape_t,right_shape_t>;
            if (auto lptr = std::get_if<left_t>(&array)) {
                return shape_t{shape(*lptr)};
            } else /* if (auto ptr = std::get_if<right_t>(&array)) */ {
                auto rptr = std::get_if<right_t>(&array);
                return shape_t{shape(*rptr)};
            }
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
        // check for dynamic-shape array but fixed-dimension array
        else if constexpr (meta::nested_array_dim_v<array_t> > 0) {
            constexpr auto N = meta::nested_array_dim_v<array_t>;
            // TODO: do not directly use std::array, create and wrap via meta::make_array_t<size_t,N>
            auto shape_ = std::array<size_t,N>{};
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
                    auto s = len(array);
                    std::get<i>(shape_) = s;
                }
                else {
                    auto indices = detail::repeat<i>(0ul);
                    auto a = apply_at(array, indices);
                    // assuming nested array has size(a), which it should
                    auto s = len(a);
                    std::get<i>(shape_) = s;
                }
            });
            return shape_;
        }
        else if constexpr (meta::is_array1d_v<array_t> && meta::has_size_v<array_t>) {
            // TODO (wrap std metafunctions): wrap as meta::make_tuple
            return std::tuple{vector_size(array)};
        }
        else {
            return array.shape();
        }
    } // shape

    /**
     * @brief Get the length of array.
     *
     * Mimics python's len.
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto len(const array_t& array)
    {
        const auto shape_ = shape(array);
        // TODO (wrap std metafunctions): wrap as meta::integral_constant
        return at(shape_, std::integral_constant<size_t,0>{});
    } // len

    // TODO (wrap std metafunctions): wrap as meta::make_tuple_type_t
    template <typename...size_types>
    constexpr auto len(const std::tuple<size_types...>&)
    {
        return sizeof...(size_types);
    } // len

    template <>
    constexpr auto len<none_t>(const none_t&)
    {
        return 0;
    } // len

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
        // prefer for explicit call to dim() first
        if constexpr (meta::has_dim_v<array_t>)
            return array.dim();
        else if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
            // @todo whenever the dim is constant return it as compile-time constant
            // @note not possible at this point, need to refactor indices & strides computation to support compile-time constant
            // return meta::index_constant<meta::fixed_ndarray_dim_v<array_t>>{};
            return meta::fixed_dim_v<array_t>;
        }
        else return len(shape(array));
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
    struct get_index_type<array_t, std::enable_if_t<is_ndarray_v<array_t>>>
    {
        // TODO (wrap std metafunctions): wrap as meta::enable_if_t
        using type = get_element_or_common_type_t<decltype(nmtools::shape(std::declval<array_t>()))>;
    }; // get_index_type
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_UTILITY_SHAPE_HPP