#ifndef NMTOOLS_ARRAY_VIEW_SLICE_HPP
#define NMTOOLS_ARRAY_VIEW_SLICE_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

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
         * @brief compute offset from slice parameter (start & stop)
         * 
         * @tparam start_t 
         * @tparam stop_t 
         * @tparam T 
         * @param a 
         * @param start 
         * @param stop 
         * @return constexpr auto 
         * @warn the parameter start_t or stop_t is strictly integer or tuple for now, other packed type is not supported yet
         * @todo support other packed type, e.g. array, pair
         */
        template <typename start_t, typename stop_t, typename T>
        constexpr auto offset(const T& a, const start_t& start=start_t{}, const stop_t& stop=stop_t{})
        {
            constexpr auto is_array1d = traits::is_array1d_v<T>;
            constexpr auto is_array2d = traits::is_array2d_v<T>;
            static_assert(
                is_array1d || is_array2d,
                "only support 1D or 2D array for now"
            );
            using traits::remove_cvref_t;
            // note: need to remove_cvref because is_tuple doesnt remove cvref and start_t may be cvref
            constexpr auto start_is_tuple = traits::is_tuple_v<remove_cvref_t<start_t>>;
            constexpr auto stop_is_tuple  = traits::is_tuple_v<remove_cvref_t<stop_t>>;
            static_assert (start_is_tuple == stop_is_tuple,
                "only support same traits for both start_t & stop_t, "
                "either both is tuple-like or not"
            );
            static_assert (
                // not tuple and 1D array, start stop is simply integer
                (!start_is_tuple && is_array1d)
                // tuple and 2d array, start stop is pair of integer
                || (start_is_tuple && is_array2d),
                "for tuple like index, T should be matrix like"
            );

            using ::nmtools::detail::unpack_slice_indices;
            using ::nmtools::matrix_size;

            constexpr auto is_fixed_size = traits::is_fixed_size_matrix_v<T> || traits::is_fixed_size_vector_v<T>;

            // handle fixed size 2D array, start_t and stop_t must be tuple
            if constexpr (start_is_tuple && stop_is_tuple) {
                // @todo check if elements of start & stop is compile-time constant
                // constexpr auto any_start_is_ct = traits::type_list_conjunction_v<start_t,traits::is_integral_constant>;
                // constexpr auto all_start_is_ct = traits::type_list_disjunction_v<start_t,traits::is_integral_constant>;
                // constexpr auto any_stop_is_ct  = traits::type_list_conjunction_v<stop_t,traits::is_integral_constant>;
                // constexpr auto all_stop_is_ct  = traits::type_list_disjunction_v<stop_t,traits::is_integral_constant>;
                /* @todo pack as type */
                return unpack_slice_indices(a,start,stop);
            }
            // handle fixed size 1D array, start_t and stop_t are simply integral constant
            else if constexpr (!start_is_tuple && !stop_is_tuple) {
                // @todo check if elements of start & stop is compile-time constant
                auto [start_, stop_] = unpack_slice_indices(a,start,stop);
                /* @todo pack as type */
                return std::make_tuple(std::make_tuple(start_), std::make_tuple(stop_));
            }
        } // offset
        
        /**
         * @brief add two tuple. https://godbolt.org/z/M4cWx8
         * 
         * @tparam lhs_t types of elements that lhs tuple stores
         * @tparam rhs_t types of elements that rhs tuple stores
         * @tparam Is 
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t, size_t...Is>
        constexpr auto add(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs, std::integer_sequence<size_t,Is...>)
        {
            return std::make_tuple((std::get<Is>(lhs)+std::get<Is>(rhs))...);
        } // add

        /**
         * @brief subtract two tuple
         * 
         * @tparam lhs_t types of elements that lhs tuple stores
         * @tparam rhs_t types of elements that rhs tuple stores
         * @tparam Is 
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t, size_t...Is>
        constexpr auto sub(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs, std::integer_sequence<size_t,Is...>)
        {
            return std::make_tuple((std::get<Is>(lhs)-std::get<Is>(rhs))...);
        } // sub

        /**
         * @brief element-wise gt (greater than) of lhs and rhs
         * 
         * @tparam lhs_t types of elements that lhs tuple stores
         * @tparam rhs_t types of elements that rhs tuple stores
         * @tparam Is 
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t, size_t...Is>
        constexpr auto gt(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs, std::integer_sequence<size_t,Is...>)
        {
            return std::make_tuple((std::get<Is>(lhs)>std::get<Is>(rhs))...);
        } // gt

        /**
         * @brief element-wise lt (lower than) of lhs and rhs
         * 
         * @tparam lhs_t types of elements that lhs tuple stores
         * @tparam rhs_t types of elements that rhs tuple stores
         * @tparam Is 
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t, size_t...Is>
        constexpr auto lt(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs, std::integer_sequence<size_t,Is...>)
        {
            return std::make_tuple((std::get<Is>(lhs)<std::get<Is>(rhs))...);
        } // lt

        /**
         * @brief disjunction of elements of lhs
         * 
         * @tparam lhs_t types of elements that lhs tuple stores
         * @tparam Is 
         * @param lhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, size_t...Is>
        constexpr auto all(const std::tuple<lhs_t...>& lhs, std::integer_sequence<size_t,Is...>)
        {
            return (static_cast<bool>(std::get<Is>(lhs)) && ...) ;
        } // all

        /**
         * @brief add two tuple. https://godbolt.org/z/M4cWx8
         * 
         * @tparam lhs_t the types of elements that lhs tuple stores
         * @tparam rhs_t the types of elements that rhs tuple stores
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t>
        constexpr auto add(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs)
        {
            static_assert (sizeof...(lhs_t)==sizeof...(rhs_t), "mismatched shape");
            using indices_t = std::make_index_sequence<sizeof...(lhs_t)>;
            return add(lhs,rhs,indices_t{});
        } // add

        /**
         * @brief subtract two tuple
         * 
         * @tparam lhs_t the types of elements that lhs tuple stores
         * @tparam rhs_t the types of elements that rhs tuple stores
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t>
        constexpr auto sub(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs)
        {
            static_assert(sizeof...(lhs_t)==sizeof...(rhs_t), "mismatched shape");
            using indices_t = std::make_index_sequence<sizeof...(lhs_t)>;
            return sub(lhs,rhs,indices_t{});
        } // sub

        /**
         * @brief element-wise gt (greater than) of lhs and rhs
         * 
         * @tparam lhs_t the types of elements that lhs tuple stores
         * @tparam rhs_t the types of elements that rhs tuple stores
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t>
        constexpr auto gt(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs)
        {
            static_assert (sizeof...(lhs_t)==sizeof...(rhs_t), "mismatched shape");
            using indices_t = std::make_index_sequence<sizeof...(lhs_t)>;
            return gt(lhs,rhs,indices_t{});
        } // gt

        /**
         * @brief element-wise lt (lower than) of lhs and rhs
         * 
         * @tparam lhs_t the types of elements that lhs tuple stores
         * @tparam rhs_t the types of elements that rhs tuple stores
         * @param lhs 
         * @param rhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t, typename...rhs_t>
        constexpr auto lt(const std::tuple<lhs_t...>& lhs, const std::tuple<rhs_t...>& rhs)
        {
            static_assert (sizeof...(lhs_t)==sizeof...(rhs_t), "mismatched shape");
            using indices_t = std::make_index_sequence<sizeof...(lhs_t)>;
            return lt(lhs,rhs,indices_t{});
        } // lt

        /**
         * @brief disjunction of elements of lhs
         * 
         * @tparam lhs_t the types of elements that lhs tuple stores
         * @param lhs 
         * @return constexpr auto 
         */
        template <typename...lhs_t>
        constexpr auto all(const std::tuple<lhs_t...>& lhs)
        {
            using indices_t = std::make_index_sequence<sizeof...(lhs_t)>;
            return all(lhs,indices_t{});
        } // all

        /**
         * @brief mapping indices from dst (slice view) to src (referenced array)
         * 
         * @tparam start_t tuple or integer
         * @tparam stop_t tuple of integer/end_t or integer/end_t
         * @tparam size_types variadic template of indices
         * @param start offset start indices of slice view
         * @param stop offset stop indices of slice view
         * @param indices desired indices of dst (sliced) view
         * @return constexpr auto 
         */
        template <typename start_t, typename stop_t, typename...size_types>
        constexpr auto slice(const start_t& start, const stop_t& stop, size_types...indices)
        {
            using std::tuple_size_v;

            static_assert (traits::has_tuple_size_v<start_t> && traits::has_tuple_size_v<stop_t>,
                "slice only support both start & stop to be the packed type(s)"
            );
            static_assert (sizeof...(indices)>0 && sizeof...(indices)<3,
                "slice only support indexing up to 2 dimension for now"
            );
            static_assert (sizeof...(indices)==tuple_size_v<start_t>,
                "mismatched shape of start & indices"
            );

            /* pack indices as tuple to make easier when taking the elements */
            auto indices_ = std::make_tuple(indices...);

            /* @todo bounds check at compile-time when possible */

            auto mapped_indices = add(start,indices_);

            return mapped_indices;
        } // slice

        /**
         * @brief helper alias template to deduce offset return type
         * 
         * @tparam array_t 
         * @tparam start_t 
         * @tparam stop_t 
         */
        template <typename array_t, typename start_t, typename stop_t>
        using get_offset_type_t = traits::remove_cvref_t<decltype(offset(std::declval<array_t>(),std::declval<start_t>(),std::declval<stop_t>()))>;
    } // detail

    /**
     * @brief represent sliced constant reference to 1D/2D/ND array.
     * 
     * @tparam Array non-cvref type of array to be referenced, should be deducable via CTAD
     */
    template <typename Array, typename start_t, typename stop_t>
    struct slice_t
    {
        static_assert(
            is_array1d_v<Array> || is_array2d_v<Array>,
            "slice_t only support 1D & 2D array for now"
        );
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<Array>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const Array&;
        using offset_type = detail::get_offset_type_t<array_type,start_t,stop_t>;

        // const reference to actual array type
        array_type array;
        start_t start;
        stop_t stop;
        offset_type offset;

        /**
         * @brief construct slice view
         * 
         */
        constexpr slice_t(array_type array, start_t start, stop_t stop)
            : array(array), start(start), stop(stop)
        {
            offset = detail::offset(array,start,stop);
        } // slice_t

        /**
         * @brief return the shape of dst (sliced) array
         * 
         * @return constexpr auto 
         */
        constexpr auto shape() const noexcept
        {
            const auto& start = std::get<0>(offset);
            const auto& stop  = std::get<1>(offset);
            return detail::sub(stop,start);
        } // shape

        /**
         * @brief index mapping from dst (sliced) indices to src (referenced) indices
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         * @todo provide a way to make assertion optional
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            const auto& start = std::get<0>(offset);
            const auto& stop  = std::get<1>(offset);
            auto mapped_indices = detail::slice(start,stop,indices...);
            assert( detail::all(detail::lt(mapped_indices,stop))
                //, "out of bounds indices"
            );
            return mapped_indices;
        } // index
    }; // slice_t

    /**
     * @brief create slice_t object
     * 
     * @tparam array_t type of array
     * @param array array to be referenced
     * @return constexpr auto 
     * @see nmtools::view::slice_t
     */
    template <typename array_t, typename start_t, typename stop_t>
    constexpr auto slice(const array_t& array, const start_t& start, const stop_t& stop)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        return decorator_t<slice_t,array_t,start_t,stop_t>{slice_t(array, start, stop)};
    } // slice

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specializtion of fixed_vector_size for slice view.
     * 
     * @tparam array_t 
     * @tparam start_t 
     * @tparam stop_t 
     */
    template <typename array_t, typename start_t, typename stop_t>
    struct fixed_vector_size< view::slice_t<array_t,start_t,stop_t>
        , std::enable_if_t<
            // @note use std::conjuction to short circuit
            // since type_list_conjunction requires tparam to have tuple_size
            std::conjunction_v<
                traits::is_fixed_size_vector<traits::remove_cvref_t<array_t>>,
                traits::has_tuple_size<start_t>,
                traits::type_list_conjunction<start_t,traits::is_integral_constant>,
                traits::has_tuple_size<stop_t>,
                traits::type_list_conjunction<stop_t,traits::is_integral_constant>
            >
        >
    > : fixed_vector_size< traits::remove_cvref_t<array_t> > {};

    /**
     * @brief specialization of fixed_matrix_size for slice view.
     * 
     * @tparam array_t 
     * @tparam start_t 
     * @tparam stop_t 
     */
    template <typename array_t, typename start_t, typename stop_t>
    struct fixed_matrix_size< view::slice_t<array_t,start_t,stop_t>
        , std::enable_if_t<
            std::conjunction_v<
                traits::is_fixed_size_matrix<traits::remove_cvref_t<array_t>>,
                traits::has_tuple_size<start_t>,
                traits::type_list_conjunction<start_t,traits::is_integral_constant>,
                traits::has_tuple_size<stop_t>,
                traits::type_list_conjunction<stop_t,traits::is_integral_constant>
            >
        >
    > : fixed_matrix_size< traits::remove_cvref_t<array_t> > {};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_SLICE_HPP