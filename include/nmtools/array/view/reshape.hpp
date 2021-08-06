#ifndef NMTOOLS_ARRAY_VIEW_RESHAPE_HPP
#define NMTOOLS_ARRAY_VIEW_RESHAPE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/flatten.hpp"

#include "nmtools/array/detail.hpp"
#include "nmtools/array/index.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    /**
     * @brief reshape view type
     * 
     * @tparam array_t type of array to be reshaped
     * @tparam shape_t type of new shape
     */
    template <typename array_t, typename shape_t>
    struct reshape_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;
        using shape_type = shape_t;
        
        array_type array;
        shape_type new_shape;

        /**
         * @brief construct reshape view
         * 
         */
        constexpr reshape_t(array_type array, shape_type shape)
            : array(array), new_shape(shape) {}
        
        /**
         * @brief simply return size of new_shape
         * 
         * @return constexpr auto 
         */
        constexpr auto dim() const noexcept
        {
            auto n = [&](){
                if constexpr (meta::has_tuple_size_v<shape_type>)
                    return std::tuple_size_v<shape_type>;
                else return new_shape.size();
            }();
            return n;
        } // dim
        
        /**
         * @brief simply return new_shape
         * 
         * @return constexpr decltype(auto) 
         */
        constexpr decltype(auto) shape() const noexcept
        {
            // TODO: support negative shape dimension
            return new_shape;
        } // shape

        /**
         * @brief index transformer for reshape view
         * 
         * @tparam size_types
         * @param indices variadic of integral type or single packed indices
         * @return constexpr auto transformed indices, mapped to original array shape
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            using ::nmtools::array::detail::compute_strides;
            using ::nmtools::array::detail::compute_indices;
            using ::nmtools::array::detail::compute_offset;
            using ::nmtools::detail::make_array;
            using ::nmtools::shape;
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
            auto shape_  = shape(array);
            auto strides = compute_strides(new_shape);
            auto offset  = compute_offset(indices_,strides);
            auto tf_idx  = compute_indices(offset,shape_);
            return tf_idx;
        } // index
    }; // reshape_t

    /**
     * @brief return reshape view
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array array to be reshaped
     * @param new_shape 
     * @return constexpr auto reshape view
     */
    template <typename array_t, typename shape_t>
    constexpr auto reshape(const array_t& array, shape_t new_shape)
    {
        using ::nmtools::array::detail::product;
        auto shape = ::nmtools::shape(array);
        auto numel = product(shape);
        // TODO: better error handling
        assert( numel == product(new_shape)
            // , "unsupported reshape, mismatched number of elements"
        );
        return decorator_t<reshape_t,array_t,shape_t>{{array,new_shape}};
    } // reshape

    /** @} */ // end group view

} // namespace nmtools::view

namespace nmtools
{
    // TODO: remove
    /**
     * @brief specialization of fixed_vector_size for reshape view
     * 
     * @tparam array_t referenced array of reshape view
     * @tparam shape_t type of new shape of reshape view
     */
    template <typename array_t, typename shape_t>
    struct meta::fixed_vector_size< view::reshape_t<array_t, shape_t>
        , std::enable_if_t< meta::is_fixed_size_vector_v<
            meta::remove_cvref_t<typename view::reshape_t<array_t,shape_t>::array_type>
        >
    >>
    {
        static constexpr auto get()
        {
            if constexpr (meta::apply_conjunction_v<meta::is_integral_constant,shape_t>)
            {
                constexpr auto N = std::tuple_size_v<shape_t>;
                if constexpr (N > 1)
                    return detail::fail_t{};
                else std::tuple_element_t<0,shape_t>::value;
            }
            else return detail::fail_t{};
        } // get()

        static inline constexpr auto value = get();
        using value_type = decltype(value);
    }; // fixed_vector_size

    // TODO: remove
    /**
     * @brief specialization fo is_array1d for reshape view
     *
     * Note that this specialization bypass the specialization from decorator_t
     * by being more specific on view_t (reshape_t in this case)
     * 
     * @tparam array_t referenced array of reshape view
     * @tparam shape_t type of new shape of reshape view
     */
    template <typename array_t, typename shape_t>
    struct meta::is_array1d< view::decorator_t<view::reshape_t, array_t, shape_t>, void >
    {
        static constexpr auto get()
        {
            using view_type  = view::decorator_t<view::reshape_t, array_t, shape_t>;
            using array_type = typename view_type::array_type;
            if constexpr (meta::has_tuple_size_v<shape_t>)
                return std::tuple_size_v<shape_t> == 1;
            else return false;
        } // get()

        static inline constexpr auto value = get();
        using value_type = decltype(value);
    }; // is_array_1d

    // TODO: remove
    /**
     * @brief specialization fo is_array2d for reshape view
     *
     * Note that this specialization bypass the specialization from decorator_t
     * by being more specific on view_t (reshape_t in this case)
     * 
     * @tparam array_t referenced array of reshape view
     * @tparam shape_t type of new shape of reshape view
     */
    template <typename array_t, typename shape_t>
    struct meta::is_array2d< view::decorator_t<view::reshape_t, array_t, shape_t> >
    {
        static constexpr auto get()
        {
            using view_type  = view::decorator_t<view::reshape_t, array_t, shape_t>;
            using array_type = typename view_type::array_type;
            if constexpr (meta::has_tuple_size_v<shape_t>)
                return std::tuple_size_v<shape_t> == 2;
            else return false;
        } // get()

        static inline constexpr auto value = get();
        using value_type = decltype(value);
    }; // is_array_2d

    /**
     * @brief specialization fo is_ndarray for reshape view
     *
     * Note that this specialization bypass the specialization from decorator_t
     * by being more specific on view_t (reshape_t in this case)
     * 
     * @tparam array_t referenced array of reshape view
     * @tparam shape_t type of new shape of reshape view
     */
    template <typename array_t, typename shape_t>
    struct meta::is_ndarray< view::decorator_t<view::reshape_t, array_t, shape_t> >
    {
        static constexpr auto get()
        {
            using view_type  = view::decorator_t<view::reshape_t, array_t, shape_t>;
            using array_type = typename view_type::array_type;
            if constexpr (meta::is_array2d_v<view_type>)
                return true;
            else if constexpr (meta::is_array1d_v<view_type>)
                return true;
            else return meta::is_ndarray_v<meta::remove_cvref_t<array_type>>;
        } // get()

        static inline constexpr auto value = get();
        using value_type = decltype(value);
    }; // is_ndarray

    /**
     * @brief specialization of meta::fixed_ndarray_shape for reshape view
     *
     * Enabled for fixed size ndarray.
     * Results in fail_t when shape_t is not integral_constant.
     * 
     * @tparam array_t 
     * @tparam shape_t 
     */
    template <typename array_t, typename shape_t>
    struct meta::fixed_ndarray_shape<
        view::reshape_t< array_t, shape_t>
    >
    {
        static constexpr auto value = []()
        {
            // for now, simply return the new shape
            // when both src shape and dst shape is known at compile time.
            // it should be possible to allow array with runtime shape
            // to be reshaped with fixed shape.
            if constexpr (is_fixed_size_ndarray_v<array_t> && (is_constant_index_v<shape_t> || is_constant_index_array_v<shape_t>)) {
                return shape_t{};
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_RESHAPE_HPP