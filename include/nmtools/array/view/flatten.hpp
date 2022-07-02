#ifndef NMTOOLS_ARRAY_VIEW_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_FLATTEN_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"

// TODO: remove
#include "nmtools/array/meta.hpp"

namespace nmtools::index
{
    using namespace literals;

    // TODO: consider to move somewhere else
    template <typename array_t>
    constexpr auto shape_flatten(const array_t& array)
    {
        // TODO: return fixed index whenever possible
        // TODO: use make_unsigned_t instead of size_t
        if constexpr (meta::is_num_v<array_t>) {
            return nmtools_tuple{1_ct};
        } else {
            auto shape_ = view::detail::shape(array);
            auto N = index::product(shape_);
            // flattened array is strictly 1D
            if constexpr (meta::is_constant_index_v<decltype(N)>) {
                return nmtools_tuple{N};
            } else {
                return nmtools_array{N};
            }
        }
    } // shape_flatten
} // namespace nmtools::index

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
        using dst_shape_type  = decltype(index::shape_flatten(meta::declval<array_t>()));

        array_type     array;
        dst_shape_type dst_shape;

        constexpr flatten_t(const array_t& array)
            : array(initialize<array_type>(array))
            , dst_shape(index::shape_flatten(array))
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

        template <typename size_type>
        constexpr auto index(size_type i) const
        {
            using ::nmtools::index::compute_indices;
            constexpr auto index_vtype = [](){
                using index_t = meta::get_index_type_t<array_t>;
                if constexpr (meta::is_constant_index_v<index_t>) {
                    return meta::as_value_v<typename index_t::value_type>;
                } else {
                    return meta::as_value_v<index_t>;
                }
            }();
            using index_t = meta::type_t<decltype(index_vtype)>;
            auto shape_   = detail::shape(array);
            auto indices  = compute_indices(static_cast<index_t>(i),shape_);
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
        using dst_shape_type  = const decltype(index::shape_flatten(meta::declval<array_type>()));

        array_type     array;
        dst_shape_type dst_shape;

        constexpr flatten_t(const array_t& array)
            : array(initialize<array_type>(array))
            , dst_shape(index::shape_flatten(array))
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
    constexpr auto flatten(const array_t& array)
    {
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

namespace nmtools
{
    // TODO: remove
    // TODO: update this, to check for fixed dst_shape member type
    /**
     * @brief Infer the shape of flatten view at compile time.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct meta::fixed_ndarray_shape< view::flatten_t<array_t> >
    {
        static constexpr auto value = [](){
            if constexpr (meta::is_num_v<array_t>) {
                return nmtools_array{(size_t)1};
            } else if constexpr (meta::is_fixed_size_ndarray_v<array_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto N     = index::product(shape);
                return nmtools_array{(size_t)N};
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    // TODO: remove
    #if 0
    /**
     * @brief Infer the dimension of flatten view at compile-time.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct meta::fixed_dim < view::decorator_t<view::flatten_t, array_t> >
    {
        static constexpr auto value = 1ul;
        using value_type = size_t;
    }; // fixed_dim
    #endif
} // nmtools

namespace nmtools::meta
{
    template <typename array_t>
    struct fixed_shape<
        view::decorator_t< view::flatten_t, array_t >
    >
    {
        static constexpr auto value = [](){
            // flatten view is strictly 1D, only need the size to decide the resulting shape
            constexpr auto fixed_size = fixed_size_v<array_t>;
            if constexpr (is_index_v<decltype(fixed_size)>) {
                return nmtools_array{fixed_size};
            } else {
                return fixed_size;
            }
        }();
    }; // fixed_shape

    template <typename array_t>
    struct is_ndarray< view::decorator_t< view::flatten_t, array_t > >
    {
        static constexpr auto value = is_ndarray_v<array_t> || is_num_v<array_t>;
    }; 
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_FLATTEN_HPP