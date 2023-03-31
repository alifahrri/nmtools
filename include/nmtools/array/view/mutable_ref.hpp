#ifndef NMTOOLS_ARRAY_VIEW_MUTABLE_REF_HPP
#define NMTOOLS_ARRAY_VIEW_MUTABLE_REF_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/ref.hpp"

namespace nmtools::view
{
    using meta::is_array1d_v;
    using meta::is_ndarray_v;
    using meta::is_fixed_size_ndarray_v;
    using meta::has_shape_v;
    using meta::has_size_v;
    using meta::has_dim_v;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    /**
     * @brief represent mutable reference to 1D/2D/ND array.
     * Inspired from <a href="https://llvm.org/doxygen/classllvm_1_1MutableArrayRef.html">llvm ArrayRef</a>
     * and <a href="https://github.com/tcbrindle/NanoRange/blob/master/include/nanorange/views/ref.hpp">nanorange view ref</a>
     * but specialized for 1D/2D/ND fixed/resizable array with random access and numpy-like
     * array shape information (dim(), shape())
     * 
     * @tparam Array_t non-cvref type of array to be referenced, should be deducable via CTAD
     */
    template <typename Array_t, typename=void>
    struct mutable_ref_t
    {
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<Array_t>;
        using const_reference = const value_type&;

        // array type as required by decorator
        using array_type = Array_t&;

        // const reference to actual array type
        array_type array;

        /**
         * @brief construct ref view
         * 
         */
        constexpr mutable_ref_t(array_type array) : array(array) {}

        /**
         * @brief identity mapping of indices
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices)
        {
            return detail::identity(indices...);
        } // index

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            return detail::identity(indices...);
        } // index
    }; // mutable_ref_t

    template <typename T>
    struct mutable_ref_t<T*, meta::enable_if_t<meta::is_num_v<meta::remove_address_space_t<T>>>>
    {
        using value_type = T;
        using const_reference = const value_type&;
        using array_type = T*;

        array_type array;
        size_t numel;

        constexpr mutable_ref_t(T* ptr, size_t numel)
            : array(ptr)
            , numel(numel)
        {}

        constexpr auto dim() const
        {
            return meta::ct_v<1>;
        }

        constexpr auto shape() const
        {
            #if 0
            // broken on c++ for opencl 😭
            // error: field may not be qualified with an address space
            return nmtools_array{numel};
            #else
            return nmtools_array<size_t,1>{numel};
            #endif
        }

        template <typename...size_types>
        constexpr auto& operator()(const size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            return array[at(indices_,meta::ct_v<0>)];
        }

        template <typename...size_types>
        constexpr auto& operator()(const size_types...indices)
        {
            auto indices_ = pack_indices(indices...);
            return array[at(indices_,meta::ct_v<0>)];
        }
    };

    /**
     * @brief create mutable_ref_t object
     * 
     * @tparam array_t type of array
     * @param array array to be referenced
     * @return constexpr auto 
     * @see nmtools::view::mutable_ref_t
     */
    template <typename array_t>
    constexpr auto mutable_ref(array_t& array)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        return decorator_t<mutable_ref_t,array_t>{array};
    } // mutable_ref

    template <typename T>
    constexpr auto mutable_ref(T* ptr, size_t numel)
    {
        return decorator_t<mutable_ref_t,T*>{{ptr,numel}};
    }

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specialization of meta::fixed_ndarray_shape cvfor mutable_ref view.
     * 
     * @tparam array_t referenced array type
     */
    template <typename array_t>
    struct meta::fixed_ndarray_shape< view::mutable_ref_t<array_t>
        , meta::enable_if_t< meta::is_fixed_size_ndarray_v< meta::remove_cvref_t<array_t> > >
    > : meta::fixed_ndarray_shape< meta::remove_cvref_t<array_t> > {};
} // namespace nmtools

namespace nmtools::meta
{
    template <typename array_t>
    struct is_ndarray< view::decorator_t<view::mutable_ref_t,array_t> >
    {
        static constexpr auto value = is_ndarray_v<remove_cvref_t<array_t>>;
    };

    template <typename T>
    struct get_element_type<
        view::decorator_t<view::mutable_ref_t,T*>
    >
    {
        using type = meta::remove_address_space_t<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_MUTABLE_REF_HPP