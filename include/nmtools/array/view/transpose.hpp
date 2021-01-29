#ifndef NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/detail.hpp"
#include "nmtools/array/index.hpp"

#include <cassert>

namespace nmtools::view
{
    using meta::is_array1d_v;
    using meta::is_array2d_v;
    using meta::is_ndarray_v;
    using meta::is_fixed_size_vector_v;
    using meta::is_fixed_size_matrix_v;
    using meta::is_fixed_size_ndarray_v;
    using meta::has_shape_v;
    using meta::has_size_v;
    using meta::has_dim_v;

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

    } // namespace detail
    
    /**
     * @brief Returns a view of the array with axes transposed.
     * 
     * For a 1-D array this has no effect, as a transposed vector is simply the same vector.
     * If axes is given, the indices are permuted by given axis, simply reverese otherwise.
     * Inspired by <a href="https://numpy.org/doc/stable/reference/generated/numpy.ndarray.transpose.html#numpy.ndarray.transpose">numpy</a>.
     * 
     * @tparam array_t array type to be transpose-viewed. only support array1d/array2d for now
     * @tparam axes_t type of axes, deducible via ctad
     * @todo support for compile-time axes (e.g. tuple<integral_constant<...>...>)
     */
    template <typename array_t, typename axes_t=detail::none_t>
    struct transpose_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;
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
            using ::nmtools::detail::make_array;
            using ::nmtools::detail::reverse;
            using ::nmtools::detail::gather;

            auto shape_ = ::nmtools::shape(array);
            if constexpr (std::is_same_v<axes_type,detail::none_t>)
                return reverse(shape_);
            else
                return gather(shape_, axes);
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
            using ::nmtools::detail::reverse;
            using ::nmtools::detail::scatter;

            using common_t = std::common_type_t<size_types...>;

            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for transpose view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            if constexpr (std::is_same_v<axes_type,detail::none_t>)
                indices_ = reverse(indices_);
            else
                indices_ = scatter(indices_, axes);
            return indices_;
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

namespace nmtools
{
    using view::detail::none_t;
    using view::transpose_t;
    using view::decorator_t;
    using std::get;
    using std::make_pair;

    /**
     * @brief specialization of meta::fixed_matrix_size trait for transpose view and the axes_t is none_t.
     * 
     * Only enable when the axes_type is view::detail::none_t and the referenced
     * array is fixed.
     * 
     * @tparam array_t 
     * @todo extend this for compile-time axes
     * @note there is specialization of is_fixed_size_matrix that depends on meta::fixed_matrix_size
     */
    template <typename array_t>
    struct meta::fixed_matrix_size< transpose_t<array_t,none_t>
        , std::enable_if_t< meta::is_fixed_size_matrix_v<meta::remove_cvref_t<array_t>> >
    >
    {
        static inline constexpr auto src_value = meta::fixed_matrix_size_v<meta::remove_cvref_t<array_t>>;
        static inline constexpr auto value = make_pair(get<1>(src_value),get<0>(src_value));
        using value_type = decltype(value); // std::pair
    };

    /**
     * @brief specialization of meta::fixed_matrix_size for transpose view and the axes_t is is integral_constant
     * 
     * @tparam array_t 
     * @tparam indices_t 
     */
    template <typename array_t, typename indices_t>
    struct meta::fixed_matrix_size< transpose_t<array_t, indices_t>
        , std::enable_if_t<
            meta::has_tuple_size_v<indices_t>
            && meta::apply_conjunction_v<meta::is_integral_constant,indices_t>
        >
    >
    {
        static inline constexpr auto src_value = meta::fixed_matrix_size_v<meta::remove_cvref_t<array_t>>;
        static inline constexpr auto value = ::nmtools::detail::gather(src_value,indices_t{});
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    /**
     * @brief specialization of meta::fixed_vector_size strait for transpose view and the axes_t is none_t.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct meta::fixed_vector_size< transpose_t<array_t,none_t>
        , std::enable_if_t< meta::is_fixed_size_vector_v<meta::remove_cvref_t<array_t>> >
    > : meta::fixed_vector_size<meta::remove_cvref_t<array_t>> {};

    /**
     * @brief specialization of meta::fixed_ndarray_shape for transpose view and none axes
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct meta::fixed_ndarray_shape< transpose_t<array_t,none_t>
        , std::enable_if_t< meta::is_fixed_size_ndarray_v<meta::remove_cvref_t<array_t>> >
    >
    {
        static inline constexpr auto src_value = meta::fixed_ndarray_shape_v<meta::remove_cvref_t<array_t>>;
        static inline constexpr auto value = ::nmtools::detail::reverse(src_value);
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    /**
     * @brief specialization of meta::fixed_ndarray_shape for transpose view and integer_constant axes
     * 
     * @tparam array_t 
     * @tparam indices_t 
     */
    template <typename array_t, typename indices_t>
    struct meta::fixed_ndarray_shape< transpose_t<array_t, indices_t>
        , std::enable_if_t<
            meta::has_tuple_size_v<indices_t>
            && meta::apply_conjunction_v<meta::is_integral_constant,indices_t>
        >
    >
    {
        static inline constexpr auto src_value = meta::fixed_ndarray_shape_v<meta::remove_cvref_t<array_t>>;
        static inline constexpr auto value = ::nmtools::detail::gather(src_value,indices_t{});
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    /**
     * @brief specialization of meta::is_ndarray for transpose view and arbitray axes
     *
     * Only enabled when array_t is fixed size, this specialization is necessary since
     * axes_t may holds runtime value hence fixed_ndarray_shape becomes unavailable.
     * 
     * @tparam array_t 
     * @tparam axes_t 
     */
    template <typename array_t, typename axes_t>
    struct meta::is_ndarray< decorator_t<transpose_t,array_t,axes_t> 
        , std::enable_if_t< meta::is_fixed_size_ndarray_v<meta::remove_cvref_t<array_t>> >
    > : std::true_type {};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_TRANSPOSE_HPP