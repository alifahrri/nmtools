#ifndef NMTOOLS_ARRAY_VIEW_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_FLATTEN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/flatten.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    template <typename array_t, typename=void>
    struct flatten_t
    {
        using value_type      = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type      = resolve_array_type_t<array_t>;
        using src_shape_type  = const decltype(nmtools::shape(meta::declval<array_t>()));
        static constexpr auto fixed_size_vtype = [](){
            constexpr auto fixed_size = meta::fixed_size_v<array_t>;
            // NOTE: for now, ignore if array_t is view
            // TODO: re-enable when all views are cleaned up
            if constexpr (is_view_v<array_t>) {
                return meta::as_value_v<meta::error::FIXED_SIZE_UNSUPPORTED<array_t>>;
            } else if constexpr (meta::is_fail_v<decltype(fixed_size)>) {
                return meta::as_value_v<decltype(fixed_size)>;
            } else {
                return meta::as_value_v<meta::ct<(size_t)fixed_size>>;
            }
        }();
        using fixed_size_type = meta::type_t<decltype(fixed_size_vtype)>;
        using dst_shape_type  = const meta::resolve_optype_t<index::shape_flatten_t,src_shape_type,fixed_size_type>;

        array_type     array;
        dst_shape_type dst_shape;

        constexpr flatten_t(const array_t& array_)
            : array(initialize<array_type>(array_))
            , dst_shape(index::shape_flatten(nmtools::shape(array_),fixed_size_type{}))
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{};
        }

        constexpr auto dim() const noexcept
        {
            // flattened array is strictly 1D
            return 1;
        } // dim

        constexpr auto shape() const noexcept
        {
            return dst_shape;
        } // shape

        template <typename size_type>
        nmtools_index_attribute
        constexpr auto index(size_type i) const
        {
            using index_t = meta::remove_address_space_t<meta::get_index_element_type_t<dst_shape_type>>;
            auto shape_   = detail::shape(array);
            auto indices  = index::compute_indices(static_cast<index_t>(i),shape_);
            return indices;
        } // index
    }; // flatten_t

    /**
     * @brief Specialization of flatten view for num input to follows numpy.
     * needs to support operator() which just return the value, while the default use index().
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct flatten_t<array_t,meta::enable_if_t<meta::is_num_v<array_t>>>
    {
        using value_type      = array_t;
        using const_reference = const value_type&;
        using array_type      = const array_t;
        using src_shape_type  = const decltype(nmtools::shape(meta::declval<array_t>()));
        using fixed_size_type = decltype(meta::fixed_size_v<array_t>);
        using dst_shape_type  = const meta::resolve_optype_t<index::shape_flatten_t,src_shape_type,fixed_size_type>;

        array_type     array;
        dst_shape_type dst_shape;

        constexpr flatten_t(const array_t& array_)
            : array(initialize<array_type>(array_))
            , dst_shape(index::shape_flatten(nmtools::shape(array_),fixed_size_type{}))
        {}

        constexpr auto dim() const noexcept
        {
            // flattened array is strictly 1D
            return 1;
        } // dim

        constexpr auto shape() const noexcept
        {
            return dst_shape;
        } // shape

        template <typename...size_types>
        constexpr auto operator()(size_types...) const noexcept
        {
            // TODO: assert if indices < shape

            return array;
        } // operator()
    }; // flatten_t

    template <typename array_t>
    nmtools_view_attribute
    constexpr auto flatten(const array_t& array)
    {
        // TODO: try to avoid macro branching
        #ifndef __OPENCL_VERSION__
        if constexpr (meta::is_either_v<array_t>) {
            // TODO: support flatten on scalar
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            // deduce return type for each type
            using res_left_t  = decltype(view::flatten(meta::declval<left_t>()));
            using res_right_t = decltype(view::flatten(meta::declval<right_t>()));
            // NOTE: the following meta snippet is the same with eval,
            // TODO: consider to add this metafunction (check if the resulting either is the same)
            constexpr auto vtype = [](){
                if constexpr (meta::is_same_v<res_left_t,res_right_t>) {
                    return meta::as_value_v<res_left_t>;
                } else {
                    using either_t = meta::replace_either_t<array_t,res_left_t,res_right_t>;
                    return meta::as_value_v<either_t>;
                }
            }();
            using return_t = meta::type_t<decltype(vtype)>;
            if (auto l_ptr = nmtools::get_if<left_t>(&array)) {
                return return_t{view::flatten(*l_ptr)};
            } else {
                auto r_ptr = nmtools::get_if<right_t>(&array);
                return return_t{view::flatten(*r_ptr)};
            }
        } else {
            return decorator_t<flatten_t,array_t>{array};
        }
        #else
        #ifdef NMTOOLS_NO_BASE_ACCESS
        using array_type = meta::remove_address_space_t<array_t>;
        using view_type = flatten_t<array_type>;
        using result_type = decorator_t<flatten_t,array_type>;
        return result_type{view_type{array}};
        #else // NMTOOLS_NO_BASE_ACCESS
        return decorator_t<flatten_t,meta::remove_address_space_t<array_t>>{array};
        #endif // NMTOOLS_NO_BASE_ACCESS
        #endif
    } // flatten

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array1d<view::decorator_t<view::flatten_t,array_t>> : meta::true_type {};
} // namespace nmtools::meta

namespace nmtools::meta
{
    template <typename array_t>
    struct is_ndarray< view::decorator_t< view::flatten_t, array_t > >
    {
        static constexpr auto value = is_ndarray_v<array_t> || is_num_v<array_t>;
    }; 
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_FLATTEN_HPP