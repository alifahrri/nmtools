#ifndef NMTOOLS_ARRAY_DETAIL_HPP
#define NMTOOLS_ARRAY_DETAIL_HPP

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>

namespace nmtools::detail
{
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
}

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