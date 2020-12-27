#ifndef NMTOOLS_ARRAY_DETAIL_HPP
#define NMTOOLS_ARRAY_DETAIL_HPP

#include <type_traits>
#include <cstddef> // size_t
#include <utility> // integer_sequence
#include <array>
#include <tuple>

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"

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
        // @note meta::remove_cvref_t is required to properly check the traits!
        if constexpr (meta::has_tuple_size_v<meta::remove_cvref_t<T>>) {
            using indices_t = std::make_index_sequence<std::tuple_size_v<meta::remove_cvref_t<T>>>;
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

    /**
     * @brief create tuple from array
     * 
     * @tparam array_t array type, `std::get<Is>(array)` must be well-formed
     * @tparam Is index sequence
     * @param array array to be converted
     * @return constexpr decltype(auto) 
     */
    template <typename array_t, size_t...Is>
    constexpr decltype(auto) as_tuple(array_t&& array, std::index_sequence<Is...>)
    {
        return std::tuple{std::get<Is>(std::forward<array_t>(array))...};
    } // as_tuple

    /**
     * @brief create tuple from array
     * 
     * @tparam array_t tempate template parameter for corresponding array
     * @tparam T value type of the array
     * @tparam N size of the array
     * @param array array to be converted
     * @return constexpr auto 
     */
    template <template <typename,size_t> typename array_t, typename T, size_t N>
    constexpr auto as_tuple(array_t<T,N>&& array)
    {
        using indices_t = std::make_index_sequence<N>;
        return as_tuple(std::forward<array_t<T,N>>(array), indices_t{});
    } // as_tuple
    
    /** @} */ // end group array
} // namespace nmtools::detail

namespace nmtools::array::detail
{

    /**
     * @brief compute product of 1D array
     *
     * Useful to compute number of elements.
     * 
     * @tparam array_t 
     * @param vec 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto product(const array_t& vec)
    {
        using element_t = meta::get_element_type_t<array_t>;
        using common_t  = std::conditional_t<
            std::is_void_v<element_t>,
            meta::apply_t<std::common_type,array_t>,
            element_t
        >;
        // handle type vector
        if constexpr (meta::apply_logical_and_v<array_t,meta::is_integral_constant>) {
            constexpr auto vec_ = meta::constant_to_value<array_t>::value;
            constexpr auto ret  = product(vec_);
            // @todo convert back to type
            return ret;
        }
        else {
            auto ret = common_t{1};
            if constexpr (meta::has_tuple_size_v<array_t>) {
                constexpr auto n = std::tuple_size_v<array_t>;
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    ret *= std::get<i>(vec);
                });
                return ret;
            }
            else
                for (size_t i=0; i<vec.size(); i++)
                    ret *= vec.at(i);
            return ret;
        }
    } // product

    /**
     * @brief compute stride for ndarray offset
     * 
     * @param shape container of shape, should have value_type member type
     * @param k k-th stride to compute
     * @return constexpr auto
     */
    template <typename array_t, typename size_type>
    constexpr auto stride(const array_t& shape, size_type k)
    {
        if constexpr (meta::is_specialization_v<array_t,std::tuple> || meta::is_specialization_v<array_t,std::pair>)
        {
            using value_type = meta::apply_t<std::common_type,array_t>;
            static_assert( meta::is_integral_constant_v<size_type>
                , "unsupported size_type for stride. for tuple type, k must be integral constant"
            );
            constexpr auto n = std::tuple_size_v<array_t>;
            auto p = value_type{1};
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                if constexpr (i>=k+1)
                    p *= std::get<i>(shape);
            });
            return p;
        }
        else
        {
            using value_type = typename std::decay_t<decltype(shape)>::value_type;
            auto p = value_type{1};
            for (auto j=k+1; j<shape.size(); j++)
                p *= shape[j];
            return p;
        }
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
    template <typename array_t>
    constexpr auto compute_strides(const array_t& shape)
    {
        // handle if all elements in array_t is integral_constant
        // return type can not have same type as shape, assignment is not available
        // convert to value and then compute
        if constexpr (meta::apply_logical_and_v<array_t,meta::is_integral_constant>)
        {
            constexpr auto shape_   = meta::constant_to_value<array_t>::value;
            constexpr auto strides_ = compute_strides(shape_);
            // @todo value_to_constant
            return strides_;
        }
        // otherwise value of array_t is only known at runtime
        // return type can have same type as shape, assignment is ok
        else
        {
            auto strides_ = shape;
            if constexpr (meta::is_specialization_v<array_t,std::tuple> || meta::is_specialization_v<array_t,std::pair>)
            {
                constexpr auto n = std::tuple_size_v<array_t>;
                meta::template_for<n>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    auto k = std::integral_constant<size_t,i>{};
                    std::get<i>(strides_) = stride(shape, k);
                });
            }
            else
                for (size_t i=0; i<strides_.size(); i++)
                    strides_[i] = stride(shape, i);
            return strides_;
        }       
    } // strides

    /**
     * @brief access tuple with runtime value
     *
     * Also works with std::array or std::vector.
     * 
     * @tparam vector_t 
     * @tparam idx_t 
     * @param vec 
     * @param idx 
     * @return constexpr auto 
     */
    template <typename vector_t, typename idx_t>
    constexpr auto tuple_at(const vector_t& vec, idx_t idx)
    {
        // std::array type has value_type
        using element_t = meta::get_element_type_t<vector_t>;
        using common_t  = std::conditional_t<
            std::is_void_v<element_t>,
            meta::apply_t<std::common_type,vector_t>,
            element_t
        >;
        static_assert( std::is_arithmetic_v<common_t>
            , "unsupported tuple_at"
        );
        auto value = common_t{};

        if constexpr (meta::has_at_v<vector_t,idx_t>)
            value = at(vec,idx);
        // @note to check to N since n may be > i
        // @note integral constant is cast-able to its value_type (int,size_t,...)
        else
            meta::template_for<std::tuple_size_v<vector_t>>([&](auto j){
                if (idx==j) value = static_cast<common_t>(at(vec,j));
            });
        return value;
    } // tuple_at

    template <typename vector_t>
    constexpr auto size(const vector_t& vec)
    {
        if constexpr (meta::has_tuple_size_v<vector_t>)
            return std::tuple_size_v<vector_t>;
        else return vec.size();
    } // size

    /**
     * @brief compute offset from given indices and computed strides
     * 
     * Indices to offset (flat index).
     * 
     * @param indices container of indices
     * @param strides container of strides
     * @return constexpr auto 
     */
    template <typename indices_t, typename strides_t>
    constexpr auto compute_offset(const indices_t& indices, const strides_t& strides)
    {
        constexpr auto indices_is_fixed = meta::has_tuple_size_v<indices_t> || meta::has_tuple_size_v<indices_t>;
        constexpr auto strides_is_fixed = meta::has_tuple_size_v<strides_t> || meta::has_tuple_size_v<strides_t>;
        size_t offset = 0;
        auto m = detail::size(indices);
        auto n = detail::size(strides);
        // @todo static_assert whenever possible
        assert (m==n
            // , "unsupported compute_offset, mismatched shape for indices and strides"
        );
        if constexpr (indices_is_fixed || strides_is_fixed)
        {
            constexpr auto n = [&](){
                if constexpr (indices_is_fixed)
                    return std::tuple_size_v<meta::remove_cvref_t<decltype(indices)>>;
                else return std::tuple_size_v<meta::remove_cvref_t<decltype(strides)>>;
            }();
            meta::template_for<n>([&](auto index){
                offset += tuple_at(strides,index) * tuple_at(indices,index);
            });
        }
        else
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
    template <typename offset_t, typename shape_t, typename strides_t>
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape, const strides_t& strides)
    {
        constexpr auto shape_is_tuple_or_pair = meta::is_specialization_v<shape_t,std::tuple> || meta::is_specialization_v<shape_t,std::pair>;
        constexpr auto strides_is_tuple_or_pair = meta::is_specialization_v<strides_t,std::tuple> || meta::is_specialization_v<strides_t,std::pair>;
        auto indices = shape;
        if constexpr (shape_is_tuple_or_pair && strides_is_tuple_or_pair)
        {
            constexpr auto n = std::tuple_size_v<shape_t>;
            constexpr auto m = std::tuple_size_v<strides_t>;
            static_assert (m==n
                , "unsupported compute_indices, mismatched shape for shape and strides"
            );
            meta::template_for<n>([&](auto index){
                constexpr auto i = decltype(index)::value;
                std::get<i>(indices) = (offset / std::get<i>(strides)) % std::get<i>(shape);
            });
        }
        else
            for (size_t i=0; i<shape.size(); i++)
                indices[i] = (offset / strides[i]) % shape[i];
        return indices;
    } // compute indices

    /**
     * @brief inverse operation of compute_offset
     * 
     * Offset (flat index) to indices.
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename offset_t, typename shape_t>
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape)
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