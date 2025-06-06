#ifndef NMTOOLS_ARRAY_UTILITY_SHAPE_HPP
#define NMTOOLS_ARRAY_UTILITY_SHAPE_HPP

#include "nmtools/meta.hpp"

#include "nmtools/utility/at.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::impl::error
{
    template <typename...>
    struct LEN_UNSUPPORTED : meta::detail::fail_t {};

    template <typename...>
    struct SHAPE_UNSUPPORTED : meta::detail::fail_t {};

    template <typename...>
    struct DIM_UNSUPPORTED : meta::detail::fail_t {};
} // namespace nmtools::impl::error

namespace nmtools::impl
{
    template <typename T, typename=void>
    struct len_t
    {
        constexpr auto operator()([[maybe_unused]] const T& a) const noexcept
        {
            [[maybe_unused]] constexpr auto LEN = meta::len_v<T>;
            if constexpr (meta::has_shape_v<T>) {
                auto shape = a.shape();
                return nmtools::at(shape,meta::ct_v<0>);
            } else if constexpr (meta::is_fixed_size_ndarray_v<T>) {
                constexpr auto shape = meta::fixed_ndarray_shape_v<T>;
                return nmtools::at(shape,meta::ct_v<0>);
            } else if constexpr (is_none_v<T>) {
                return 0;
            } else if constexpr (LEN > 0) {
                return LEN;
            } else {
                using type = error::LEN_UNSUPPORTED<T>;
                return type{};
            }
        } // operator()
    }; // len_t

    template <typename T>
    struct len_t<T,meta::enable_if_t<meta::has_address_space_v<T>>>
        : len_t<meta::remove_address_space_t<T>> {};

    template <typename T>
    inline constexpr auto len = len_t<T>{};
} // namespace nmtools::impl

namespace nmtools
{
    template <typename array_t>
    constexpr auto len(const array_t& array)
    {
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type  = meta::get_maybe_type_t<array_t>;
            using result_type = decltype(len(meta::declval<array_type>()));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(array)) {
                return return_type{len(*array)};
            } else {
                return return_type{meta::Nothing};
            }
        } else {
            return impl::len<array_t>(array);
        }
    }
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
            auto res = nmtools_array<T,N>{};
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
            [[maybe_unused]] constexpr auto constrained = [](auto a){
                using type = meta::type_t<meta::remove_cvref_t<decltype(a)>>;
                return meta::is_fixed_size_ndarray_v<type> || meta::has_shape_v<type>
                    || (meta::nested_array_dim_v<type> > 0)
                    || (meta::is_array1d_v<type> && meta::has_size_v<type>)
                    || (meta::is_num_v<type>)
                    || (meta::is_fixed_index_array_v<type>);
            };
            [[maybe_unused]] constexpr auto t_array = meta::as_value_v<array_t>;
            // static_assert (
            //     constrained(t_array) || constrained_either(t_array)
            //     , "unsupported shape; only support fixed-shape array or array has .shape() or scalar type"
            // );

            // prefer .shape() since is is much more explicit
            if constexpr (meta::has_shape_v<T>) {
                return array.shape();
            }
            // for scalar type, simply return None
            else if constexpr (meta::is_num_v<array_t>)
                return None;
            // TODO: remove meta::fixed_ndarray_shape
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
                auto shape_ = nmtools_array<nm_size_t,N>{};
                meta::template_for<N>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    // example for 3dim nested dynamic array
                    // vector<vector<vector<>>>; N==3
                    // i==0:
                    // s: nm_size_t
                    // i==1:
                    // indices = array<nm_size_t,1>{0};
                    // a: vector<vector>>
                    // s: nm_size_t
                    // i==2:
                    // indices = array<nm_size_t,2>{0,0};
                    // s: nm_size_t
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
                return error::SHAPE_UNSUPPORTED<T>{};
            }
        } // operator()
    }; // shape_t

    #if 0
    template <typename T, size_t N>
    struct shape_t<T[N]>
    {
        using array_type = T[N];

        constexpr static auto shape_vtype = [](){
            if constexpr (meta::is_bounded_array_v<T>) {
                using shape_type = typename shape_t<T>::shape_type;
                return meta::as_value_v<meta::append_type_t<shape_type,meta::ct<N>>>;
            } else if constexpr (meta::is_num_v<T>) {
                return meta::as_value_v<nmtools_tuple<meta::ct<N>>>;
            } else {
                return meta::as_value_v<error::SHAPE_UNSUPPORTED<T[N]>>;
            }
        }();
        using shape_type = meta::type_t<decltype(shape_vtype)>;

        constexpr auto operator()(const array_type&) const noexcept
        {
            return shape_type{};
        }
    }; // shape_t
    #endif

    template <typename T>
    struct shape_t<T,meta::enable_if_t<meta::has_address_space_v<T>>>
        : shape_t<meta::remove_address_space_t<T>> {};

    template <typename T>
    inline constexpr auto shape = shape_t<T>{};
} // namespace nmtools::impl

namespace nmtools
{

    template <template<typename...>typename tuple, typename...clipped_t>
    auto clipped_index_array_to_array(const tuple<clipped_t...>& clipped_indices)
    {
        constexpr auto N = sizeof...(clipped_t);
        using index_t = meta::get_index_element_type_t<tuple<clipped_t...>>;
        auto array = nmtools_array<index_t,N>{};
        meta::template_for<N>([&](auto index){
            at(array,index) = at(clipped_indices,index);
        });
        return array;
    }

    /**
     * @brief return the shape of an array
     *
     * This function should work for fixed-size ndarray, fixed-dim ndarray, array1d, or array that has .shape().
     * 
     * @tparam array_t array type
     * @param array
     * @return constexpr auto 
     */
    template <bool prefer_constant_index=false, bool disable_clipped_index=false, typename array_t>
    constexpr auto shape(const array_t& array)
    {
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type = meta::get_maybe_type_t<array_t>;
            using result_type = decltype(shape<prefer_constant_index>(meta::declval<array_type>()));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(array)) {
                return return_type{shape<prefer_constant_index>(*array)};
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using left_shape_t  = decltype(shape(meta::declval<left_t>()));
            using right_shape_t = decltype(shape(meta::declval<right_t>()));
            constexpr auto shape_vtype = [](){
                // in c++ stl, while variant can hold the same type more than once,
                // it is rather cumbersome so just skip variant if left and right
                // result the same type (for example: reduction on dynamic ndarray)
                if constexpr (meta::is_same_v<left_shape_t,right_shape_t>) {
                    using shape_t = left_shape_t;
                    return meta::as_value_v<shape_t>;
                } else {
                    using shape_t = meta::replace_either_t<array_t,left_shape_t,right_shape_t>;
                    return meta::as_value_v<shape_t>;
                }
            }();
            using shape_t = meta::type_t<decltype(shape_vtype)>;
            if (auto lptr = nmtools::get_if<left_t>(&array)) {
                return shape_t{shape(*lptr)};
            } else /* if (auto ptr = nmtools::get_if<right_t>(&array)) */ {
                auto rptr = nmtools::get_if<right_t>(&array);
                return shape_t{shape(*rptr)};
            }
        } else if constexpr (prefer_constant_index) {
            using meta::ct_v;
            constexpr auto fixed_shape = meta::fixed_shape_v<array_t>;
            if constexpr (!meta::is_fail_v<decltype(fixed_shape)>) {
                return meta::template_reduce<len(fixed_shape)-1>([&](auto init, auto index){
                    using init_type = decltype(init);
                    using type = meta::append_type_t<init_type,meta::ct<(nm_size_t)at(fixed_shape,ct_v<index+1>)>>;
                    return type{};
                }, nmtools_tuple<meta::ct<static_cast<nm_size_t>(at(fixed_shape,ct_v<0>))>>{});
            } else {
                return impl::shape<array_t>(array);
            }
        } else if constexpr (disable_clipped_index) {
            auto m_shape = shape<false,false>(array);
            if constexpr (meta::is_clipped_index_array_v<decltype(m_shape)>) {
                return clipped_index_array_to_array(m_shape);
            } else {
                return m_shape;
            }
        } else {
            return impl::shape<array_t>(array);
        }
    } // shape
}

namespace nmtools::impl
{
    template <typename array_t,typename=void>
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

    template <typename T>
    struct dim_t<T,meta::enable_if_t<meta::has_address_space_v<T>>>
        : dim_t<meta::remove_address_space_t<T>> {};

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
    template <bool prefer_constant_index=false, typename array_t>
    constexpr auto dim([[maybe_unused]] const array_t& array)
    {
        // TODO: handle maybe & either type
        if constexpr (prefer_constant_index) {
            constexpr auto fixed_dim = meta::fixed_dim_v<array_t>;
            if constexpr (!meta::is_fail_v<decltype(fixed_dim)>) {
                return meta::ct_v<(nm_size_t)fixed_dim>;
            } else {
                return impl::dim<array_t>(array);
            }
        } else {
            return impl::dim<array_t>(array);
        }
    } // dim

    /** @} */ // end group utility
} // namespace nmtools

namespace nmtools::impl
{
    template <typename array_t,typename=void>
    struct numel_t
    {
        constexpr auto operator()([[maybe_unused]] const array_t& array) const noexcept
        {
            // prefer for explicit call to dim() first
            if constexpr (meta::has_size_v<array_t>) {
                return array.size();
            } else if constexpr (meta::is_fixed_size_v<array_t>) {
                return meta::fixed_size_v<array_t>;
            } else {
                auto shape = nmtools::shape(array);
                if constexpr (is_none_v<decltype(shape)>) {
                    return nm_size_t{1};
                } else {
                    auto product = nm_size_t{1};
                    for (nm_size_t i=0; i<(nm_size_t)nmtools::len(shape); i++) {
                        product *= nmtools::at(shape,i);
                    }
                    return product;
                }
            }
        }
    };

    template <typename T>
    struct numel_t<T,meta::enable_if_t<meta::has_address_space_v<T>>>
        : numel_t<meta::remove_address_space_t<T>> {};

    template <typename array_t>
    inline constexpr auto size = numel_t<array_t>{};
} // namespace nmtools::impl

namespace nmtools
{
    /**
     * @brief Compute the number of elements of an array
     * 
     * @tparam prefer_constant_index 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <bool prefer_constant_index=false, typename array_t>
    constexpr auto size([[maybe_unused]] const array_t& array)
    {
        // TODO: handle either type
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type = meta::get_maybe_type_t<array_t>;
            using result_type = decltype(size<prefer_constant_index>(meta::declval<array_type>()));
            using return_type = nmtools_maybe<result_type>;
            if (static_cast<bool>(array)) {
                return return_type{size<prefer_constant_index>(*array)};
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (prefer_constant_index) {
            constexpr auto fixed_size = meta::fixed_size_v<array_t>;
            [[maybe_unused]]
            constexpr auto bounded_size = meta::bounded_size_v<array_t>;
            [[maybe_unused]]
            constexpr auto c_shape = meta::to_value_v<decltype(shape(array))>;
            if constexpr (!meta::is_fail_v<decltype(fixed_size)>) {
                using type = meta::ct<(nm_size_t)fixed_size>;
                return type{};
            } else if constexpr (!meta::is_fail_v<decltype(bounded_size)>) {
                using type = clipped_size_t<(nm_size_t)bounded_size>;
                return type{static_cast<nm_size_t>(nmtools::size(array))};
            } else if constexpr (!meta::is_fail_v<decltype(c_shape)> && !is_none_v<decltype(c_shape)>) {
                constexpr auto c_sum = [&](){
                    nm_size_t c_sum = 1;
                    for (nm_size_t i=0; i<(nm_size_t)len(c_shape); i++) {
                        c_sum *= at(c_shape,i);
                    }
                    return c_sum;
                }();
                using type = clipped_size_t<nm_size_t(c_sum)>;
                return type{nmtools::size(array)};
            } else if constexpr (meta::is_num_v<array_t>) {
                return meta::ct_v<1ul>;
            } else {
                return impl::size<array_t>(array);
            }
        } else {
            return impl::size<array_t>(array);
        }
    } // size
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

// try to automatically detect platform, which may disable STL
#include "nmtools/platform.hpp"

#ifndef NMTOOLS_DISABLE_STL
#include "nmtools/utility/impl/stl.hpp"
#endif

// NOTE: currently breaks ref view (maybe circular dependency)
// #ifdef NMTOOLS_ENABLE_BOOST
// #include "nmtools/utility/impl/boost.hpp"
// #endif

// UTL should be available on any platform
#include "nmtools/utility/impl/utl.hpp"

#endif // NMTOOLS_ARRAY_UTILITY_SHAPE_HPP