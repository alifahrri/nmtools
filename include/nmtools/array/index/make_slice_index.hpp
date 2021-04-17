#ifndef NMTOOLS_ARRAY_INDEX_MAKE_SLICE_INDEX_HPP
#define NMTOOLS_ARRAY_INDEX_MAKE_SLICE_INDEX_HPP

#include "nmtools/array/detail.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools::index
{
    using std::size;
    using std::get;
    using std::common_type_t;
    using meta::remove_cvref_t;

    /**
     * @brief special tag to represent end index, used for slicing.
     * 
     * @see nmtools::slice
     */
    struct end_t {};

    /**
     * @brief helper function to create compile-time slice index
     * 
     * @tparam i non-type template parameter representing slicing index
     * @return constexpr auto meta::index_constant
     * @see nmtools::slice
     * @see nmtools::meta::index_constant
     */
    template <auto i>
    constexpr auto make_slice_index()
    {
        return meta::index_constant<i>{};
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice index
     * 
     * @tparam i template parameter representing slicing index
     * @return constexpr auto meta::index_constant
     * @see nmtools::slice
     * @see nmtools::meta::index_constant
     * @todo constraint to nmtools::end_t only
     */
    template <typename i>
    constexpr auto make_slice_index()
    {
        return i{};
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices,
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a value
     * @tparam j index of 2nd axis, expects a value
     * @return constexpr auto tuple of meta::index_constant
     * @see nmtools::meta::index_constant
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <auto i, auto j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(meta::index_constant<i>{},meta::index_constant<j>{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a type, e.g. nmtools::end_t
     * @tparam j index of 2nd axis, expects a type, e.g. nmtools::end_t
     * @return constexpr auto tuple of meta::index_constant
     * @see nmtools::end_t
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <typename i, typename j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(i{},j{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a value
     * @tparam j index of 2nd axis, expects a type, e.g. nmtools::end_t
     * @return constexpr auto tuple of meta::index_constant and given type
     * @see nmtools::end_t
     * @see nmtools::meta::index_constant
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <auto i, typename j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(meta::index_constant<i>{},j{});
    } // make_slice_index

    /**
     * @brief helper function to create compile-time slice indices
     * effectively maps compile-time value to type.
     * 
     * @tparam i index of 1st axis, expects a type, e.g. nmtools::end_t
     * @tparam j index of 2nd axis, expects a value
     * @return constexpr auto tuple of given type and meta::index_constant
     * @see nmtools::end_t
     * @see nmtools::meta::index_constant
     * @note that this is workaround for c++17 since class NTTP is not supported until c++20
     */
    template <typename i, auto j>
    constexpr auto make_slice_index()
    {
        return std::make_tuple(i{},meta::index_constant<j>{});
    } // make_slice_index
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_MAKE_SLICE_INDEX_HPP