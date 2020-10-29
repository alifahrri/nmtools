#ifndef NMTOOLS_ARRAY_DETAIL_HPP
#define NMTOOLS_ARRAY_DETAIL_HPP

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

#include "nmtools/traits.hpp"

namespace nmtools::detail
{
    /**
     * @addtogroup array
     * @{
     */

    /**
     * @brief given array-like a, make array of type array_t,
     * where the element is initialized using elements of array-like a
     * at indices I... with offset, e.g. {a[I+offset]...}.
     * 
     * @tparam array_t desired array_t, asuming aggregate initialization is well-formed
     * @tparam T array-like
     * @tparam I integer sequence to take elements of a
     * @param a array to initialize the resulting array
     * @param offset index offset
     * @return constexpr auto 
     * @see nmtools::row
     * @see nmtools::array::detail::make_array_ref
     */
    template <typename array_t, typename T, size_t ...I>
    constexpr auto make_array(const T &a, std::integer_sequence<size_t, I...>, size_t offset=0)
    {
        return array_t{a[I+offset]...};
    } // make_array

    /**
     * @brief create array from packed type T.
     * <a href="https://godbolt.org/z/v39Goh">godbolt demo</a>.
     * 
     * @tparam array_t desired array template-template param
     * @tparam T 
     * @tparam I 
     * @param a 
     * @return constexpr auto 
     * @note underscore prefix added to avoid ambiguous calls with make_array
     * @todo remove prefix
     */
    template <template <typename,size_t> typename array_t, typename T, size_t ...I>
    constexpr auto _make_array(const T &a, std::integer_sequence<size_t, I...>)
    {
        using common_t = std::common_type_t<decltype(std::get<I>(a))...>;
        return array_t{static_cast<common_t>(std::get<I>(a))...};
    } // make_array

    /**
     * @brief create array from single type or packed type T.
     * 
     * @tparam array_t desired array template-template param
     * @tparam T either simply type or pakced type like tuple/pair.
     * @param t 
     * @return constexpr auto 
     */
    template <template <typename,size_t> typename array_t, typename T>
    constexpr auto make_array(T&& t)
    {
        // @note traits::remove_cvref_t is required to properly check the traits!
        if constexpr (traits::has_tuple_size_v<traits::remove_cvref_t<T>>) {
            using indices_t = std::make_index_sequence<std::tuple_size_v<traits::remove_cvref_t<T>>>;
            return _make_array<array_t>(std::forward<T>(t), indices_t{});
        }
        else {
            return array_t{std::forward<T>(t)};
        }
    } // make_array

    /**
     * @brief create array.
     * 
     * @tparam array_t desired array template-template param
     * @tparam T first type
     * @tparam U second type
     * @tparam Ts rest of the type(s)
     * @param t 
     * @param u 
     * @param ts 
     * @return constexpr auto 
     */
    template <template <typename,size_t> typename array_t, typename T, typename U, typename...Ts>
    constexpr auto make_array(T&& t, U&& u, Ts&&...ts)
    {
        using common_type = std::common_type_t<T,U,Ts...>;
        return array_t{
            static_cast<common_type>(std::forward<T>(t)),
            static_cast<common_type>(std::forward<U>(u)),
            static_cast<common_type>(std::forward<Ts>(ts))...
        };
    } // make_array
    
    /** @} */ // end group array
} // namespace nmtools::detail

namespace nmtools::array::detail
{
    /**
     * @brief compute stride for ndarray offset
     * 
     * @param shape container of shape, should have value_type member type
     * @param k k-th stride to compute
     * @return constexpr auto
     */
    constexpr auto stride(const auto& shape, auto k)
    {
        using value_type = typename std::decay_t<decltype(shape)>::value_type;
        auto p = value_type{1};
        for (auto j=k+1; j<shape.size(); j++)
            p *= shape[j];
        return p;
    } // stride

    /**
     * @brief compute stride for ndarray offset.
     *
     * This follows numpy's row-major
     * <a href="https://numpy.org/doc/stable/reference/arrays.ndarray.html#internal-memory-layout-of-an-ndarray">stride computation</a>.
     * 
     * @param shape container of shape, should have value_type member type
     * @return constexpr auto
     */
    constexpr auto compute_strides(const auto& shape)
    {
        auto strides_ = shape;
        for (size_t i=0; i<strides_.size(); i++)
            strides_[i] = stride(shape, i);
        return strides_;
    } // strides

    /**
     * @brief compute offset from given indices and computed strides
     * 
     * @param indices container of indices
     * @param strides container of strides
     * @return constexpr auto 
     */
    constexpr auto compute_offset(const auto& indices, const auto& strides)
    {
        size_t offset = 0;
        for (size_t i=0; i<strides.size(); i++)
            offset += strides[i]*indices[i];
        return offset;
    } // compute_offset

    /**
     * @brief inverse operation of compute_offset
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @param strides computed strides, should be computed from shape
     * @return constexpr auto 
     */
    constexpr auto compute_indices(const auto& offset, const auto& shape, const auto& strides)
    {
        auto indices = shape;
        for (size_t i=0; i<shape.size(); i++)
            indices[i] = (offset / strides[i]) % shape[i];
        return indices;
    } // compute indices

    /**
     * @brief inverse operation of compute_offset
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @return constexpr auto 
     */
    constexpr auto compute_indices(const auto& offset, const auto& shape)
    {
        auto strides = compute_strides(shape);
        return compute_indices(offset, shape, strides);
    } // compute_indices

    using ::nmtools::detail::make_array;

    /**
     * @brief helper alias template to make array of reference
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    using array_ref = std::array<std::reference_wrapper<T>,N>;

    /**
     * @brief helper alias template for make_array_ref
     * 
     * @tparam N 
     */
    template <size_t N>
    using size_constant = std::integral_constant<size_t,N>;

    /**
     * @brief create array of reference from a.
     * With new_size starting from offset.
     * 
     * @tparam T value_type of a
     * @tparam N size of a
     * @tparam new_size new size of returning array ref
     * @param a array to take reference of
     * @param offset starting index, e.g. a[I+offset]...
     * @return auto array of reference
     */
    template <typename T, size_t N, size_t new_size>
    constexpr auto make_array_ref(std::array<T,N> &a, size_constant<new_size>, size_t offset=0)
    {
        using array_t = array_ref<T,N>;
        return make_array<array_t>(a, std::make_index_sequence<new_size>{}, offset);
    }

    /**
     * @brief create array of reference from a.
     * With new_size starting from offset.
     * 
     * @tparam T value_type of a
     * @tparam N size of a
     * @tparam new_size new size of returning array ref
     * @param a array to take reference of
     * @param offset starting index, e.g. a[I+offset]...
     * @return auto array of reference
     */
    template <typename T, size_t N, size_t new_size>
    constexpr auto make_array_ref(const std::array<T,N> &a, size_constant<new_size>, size_t offset=0)
    {
        using array_t = array_ref<const T,N>;
        return make_array(a, std::make_index_sequence<new_size>{}, offset);
    }
}

#endif // NMTOOLS_ARRAY_DETAIL_HPP