#ifndef NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/detail.hpp"
#include "nmtools/array/index.hpp"

#include <cassert>

namespace nmtools::view
{
    using traits::is_array1d_v;
    using traits::is_array2d_v;
    using traits::is_ndarray_v;
    using traits::is_fixed_size_vector_v;
    using traits::is_fixed_size_matrix_v;
    using traits::is_fixed_ndarray_v;
    using traits::has_shape_v;
    using traits::has_size_v;
    using traits::has_dim_v;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    namespace detail {

        /**
         * @brief specific tag to indicate that transpose does not have given axes
         * 
         */
        struct none_t {};

        /**
         * @brief reverse array
         * 
         * @tparam indices_t array of same type
         * @tparam Is index sequence
         * @param indices 
         * @return constexpr auto 
         */
        template <typename indices_t, size_t...Is>
        constexpr auto reverse(const indices_t& indices, std::index_sequence<Is...>)
        {
            // assuming same shape
            return indices_t{std::get<Is>(indices)...};
        } // reverse

        /**
         * @brief entrypoint for reversing array
         * 
         * @tparam indices_t array of same type
         * @param indices 
         * @return constexpr auto 
         */
        template <typename indices_t>
        constexpr auto reverse(const indices_t& indices)
        {
            static_assert (traits::has_tuple_size_v<indices_t>,
                "reverse indices only support type with tuple_size for now"
            );
            constexpr auto N = std::tuple_size_v<indices_t>;
            using reverse_t = meta::make_reversed_index_sequence<N>;
            return reverse(indices, reverse_t{});
        } // reverse

        template <typename F, size_t...Is>
        constexpr auto template_for(F&& f, std::index_sequence<Is...>)
        {
            (f(std::integral_constant<size_t,Is>{}),...);
        } // template_for

        template <size_t N, typename F>
        constexpr auto template_for(F&& f)
        {
            using index_t = std::make_index_sequence<N>;
            template_for(f,index_t{});
        } // template_for

    } // namespace detail
    
    /**
     * @brief Returns a view of the array with axes transposed.
     * 
     * For a 1-D array this has no effect, as a transposed vector is simply the same vector.
     * If axes is given, the indices are permuted by given axis, simply reverese otherwise.
     * Inspired by <a href="https://numpy.org/doc/stable/reference/generated/numpy.ndarray.transpose.html#numpy.ndarray.transpose">numpy</a>.
     * 
     * @tparam Array array type to be transpose-viewed. only support array1d/array2d for now
     * @tparam axes_t type of axes, deducible via ctad
     * @todo support for compile-time axes (e.g. tuple<integral_constant<...>...>)
     */
    template <typename Array, typename axes_t=detail::none_t>
    struct transpose_t
    {
        static_assert (
            is_array1d_v<Array> || is_array2d_v<Array>,
            "transpose_t only support 2D or 1D array for now"
        );

        using value_type = meta::get_element_type_t<Array>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const Array&;
        using axes_type = axes_t;

        array_type array;
        axes_type axes;

        constexpr transpose_t(array_type array, axes_type axes=axes_t{})
            : array(array), axes(axes) {}
        
        /**
         * @brief return the shape of dst (sliced) array
         * 
         * @return constexpr auto 
         */
        constexpr decltype(auto) shape() const noexcept
        {
            using std::size;
            using ::nmtools::detail::make_array;
            using array_t = traits::remove_cvref_t<array_type>;

            // 2D array
            if constexpr (is_array2d_v<array_t>) {
                // get the shape of referenced array
                // note that the type may be tuple/pair that doesnt have at
                // convert to array for such condition
                auto shape_ = [&](){
                    auto shape_ = detail::shape(array);
                    using shape_t = traits::remove_cvref_t<decltype(shape_)>;
                    // convert to std::array to make at available
                    if constexpr (traits::has_tuple_size_v<shape_t>)
                        return make_array<std::array>(shape_);
                    else return shape_;
                }();
                using shape_t = decltype(shape_);

                auto new_shape = shape_t{};
                // when axes is not given, simply reverse
                if constexpr (std::is_same_v<axes_type,detail::none_t>) {
                    auto n = size(shape_);
                    for (size_t i=0; i<n; i++)
                        new_shape.at(i) = shape_.at(n-1-i);
                }
                // when axes_type is tuple size() is unavailable, use template_for to extract
                else if constexpr (traits::has_tuple_size_v<axes_type>) {
                    constexpr auto N = std::tuple_size_v<axes_type>;
                    detail::template_for<N>([&](auto index_constant){
                        // extract compile-time index
                        using index_constant_t = decltype(index_constant);
                        constexpr auto src_I = index_constant_t::value;
                        // here axes is packed-type (tuple, pair,)
                        // since we use template_for, index is available at compile-time
                        auto dst_I = std::get<src_I>(axes);
                        // @note that the value of axes has not been validated to be [0,N] yet
                        new_shape.at(src_I) = shape_.at(dst_I);
                    });
                }
                // otherwise select by axis and size() is available for axis_type
                else {
                    for (size_t i=0; i<size(axes); i++)
                        new_shape.at(i) = shape_.at(axes.at(i));
                }
                // done
                return new_shape;
            } // 2D array
            // 1D array
            else if constexpr (is_array1d_v<array_t>)
                return detail::shape(array); // 1D array has no effect for transpose
        } // shape
        
        /**
         * @brief transpose index mapping
         * 
         * @tparam size_types variadic template parameter for indices
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            using ::nmtools::detail::make_array;
            auto indices_ = make_array<std::array>(indices...);
            // dispatch 2D array transpose
            // @note that since array1d and array2d may not be mutually exclusive, check for array2d first!
            if constexpr (is_array2d_v<Array>) {
                using std::size;
                auto mapped_indices = indices_;
                // when axes is not given, simply reverse
                if constexpr (std::is_same_v<axes_t,detail::none_t>)
                    return detail::reverse(indices_);
                // for fixed size axes, checking can be done at compile-time
                else if constexpr (traits::has_tuple_size_v<axes_type>) {
                    constexpr auto N = std::tuple_size_v<axes_type>;
                    static_assert (N==sizeof...(size_types),
                        "mismatched dimension between axes and indices"
                    );
                    detail::template_for<N>([&](auto index_constant){
                        using index_constant_t = decltype(index_constant);
                        constexpr auto src_I = index_constant_t::value;
                        auto dst_I = std::get<src_I>(axes);
                        // @note that the value of axes has not been validated to be [0,N] yet
                        std::get<src_I>(mapped_indices) = indices_.at(dst_I);
                    });
                }
                // otherwise check and map at runtime
                else {
                    assert (size(axes)==size(indices_)
                        // , "mismatched dimension between axes and indices"
                    );
                    for (size_t i=0; i<size(axes); i++)
                        mapped_indices.at(i) = indices_.at(axes.at(i));
                }
                return mapped_indices;
            } // 2D array
            // for 1D array, this has no effect
            else if constexpr (is_array1d_v<Array>) {
                static_assert (indices_.size()==1,
                    "mismatched indices size with array dim"
                );
                return indices_;
            } // 1D array
        } // index
    }; // transpose_t

    /**
     * @brief make transpose view
     * 
     * @tparam array_t 
     * @tparam axes_t 
     * @param array 
     * @param axes 
     * @return constexpr auto 
     */
    template <typename array_t, typename axes_t=detail::none_t>
    constexpr auto transpose(const array_t& array, axes_t axes=axes_t{})
    {
        return decorator_t<transpose_t,array_t,axes_t>{{array,axes}};
    } // transpose

    /** @} */ // end group view

} // namespace nmtools::view

namespace nmtools::traits
{
    /**
     * @brief specialization of is_fixed_size_vector trait for transpose view
     * 
     * @tparam array_t 
     * @tparam axes_t 
     */
    template <typename array_t, typename axes_t>
    struct is_fixed_size_vector<view::decorator_t<view::transpose_t,array_t,axes_t>>
    {
        static constexpr auto _check()
        {
            using view_t = view::transpose_t<array_t,axes_t>;
            if constexpr (std::is_same_v<axes_t,view::detail::none_t>)
                return is_fixed_size_vector_v<array_t>;
            else return false;
        }
        static inline constexpr bool value = _check();
    };

    /**
     * @brief specialization of is_fixed_size_matrix trait for transpose view
     * 
     * @tparam array_t 
     * @tparam axes_t 
     */
    template <typename array_t, typename axes_t>
    struct is_fixed_size_matrix<view::decorator_t<view::transpose_t,array_t,axes_t>>
    {
        static constexpr auto _check()
        {
            using view_t = view::transpose_t<array_t,axes_t>;
            if constexpr (std::is_same_v<axes_t,view::detail::none_t>)
                return is_fixed_size_matrix_v<array_t>;
            else return false;
        }
        static inline constexpr bool value = _check();
    };
} // namespace nmtools::traits

namespace nmtools
{
    using view::detail::none_t;
    using view::transpose_t;
    using view::decorator_t;
    using std::get;
    using std::make_pair;

    /**
     * @brief specialization of fixed_matrix_size trait for transpose view.
     * Only enable when the axes_type is view::detail::none_t and the referenced
     * array is fixed.
     * 
     * @tparam array_t 
     * @todo extend this for compile-time axes
     */
    template <typename array_t>
    struct fixed_matrix_size<
        decorator_t<transpose_t,array_t,none_t>,
        std::enable_if_t<
            traits::is_fixed_size_matrix_v<decorator_t<transpose_t,array_t,none_t>
    >>>
    {
        static inline constexpr auto src_value = fixed_matrix_size_v<array_t>;
        static inline constexpr auto value = make_pair(get<0>(src_value),get<1>(src_value));
        using value_type = decltype(value); // std::pair
    };
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP