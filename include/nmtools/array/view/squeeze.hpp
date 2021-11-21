#ifndef NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP
#define NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/remove_single_dims.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    template <typename array_t>
    struct squeeze_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;

        array_type array;

        constexpr squeeze_t(const array_t& array)
            : array(initialize(array, meta::as_value_v<array_type>)) {}
        
        constexpr auto shape() const noexcept
        {
            auto shape_   = detail::shape(array);
            auto squeezed = index::remove_single_dims(shape_);
            return squeezed;
        } // shape

        constexpr auto dim() const noexcept
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...Is) const
        {
            auto indices = pack_indices(Is...);

            auto squeezed_shape   = shape();
            auto squeezed_strides = index::compute_strides(squeezed_shape);

            auto shape_     = detail::shape(array);
            auto offset     = index::compute_offset(indices,squeezed_strides);
            auto tf_indices = index::compute_indices(offset,shape_);

            return tf_indices;
        } // index
    }; // squeeze_t

    /**
     * @brief remove single dimensional entry from array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto squeeze(const array_t& array)
    {
        return decorator_t<squeeze_t,array_t>{{array}};
    } // squeeze
    /* @} */
} // namespace nmtools::view

namespace nmtools::meta
{
    using view::decorator_t;
    using view::squeeze_t;

    /**
     * @brief Infer squeeze view shape at compile time.
     * 
     * Removes single dimension axis from array shape.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct fixed_ndarray_shape< squeeze_t<array_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<array_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                constexpr auto n_dim  = fixed_ndarray_dim_v<array_t>;
                // remove_single_dims is not constexpr friendly yet
                // use template_reduce for now
                // TODO: make remove_single_dims constexpr friendly
                // return index::remove_single_dims(shape);
                constexpr auto vtype = template_reduce<n_dim>([&](auto init, auto index){
                    // note: we will return value-less type, e.g. tuple<integral_constant<...>>
                    // to make sure reduced value is known at compile-time.
                    constexpr auto idx = decltype(index)::value;
                    constexpr auto dim = at(shape,idx);
                    using init_t = type_t<decltype(init)>;
                    if constexpr (meta::is_void_v<init_t> && (n_dim == 1)) {
                        // for now, return as value-less type for the shape.
                        // note that in numpy, when the shape is 1D and the dim at axis=0 is 1,
                        // np.shape returns empty tuple,
                        // at the moment, empty tuple as shape is not supported yet.
                        // TODO: deduce as scalar or consider to support empty shape.
                        using type = make_tuple_type_t<ct<dim>>;
                        return as_value_v<type>;
                    } else if constexpr (meta::is_void_v<init_t> && (dim > 1)) {
                        // here, we are still initializing,
                        // but the number of dimension should be > 1,
                        // for such case, also filter dimension > 1.
                        using type = make_tuple_type_t<ct<dim>>;
                        return as_value_v<type>;
                    } else if constexpr (dim > 1) {
                        using type = append_type_t<init_t,ct<dim>>;
                        return as_value_v<type>;
                    } else {
                        return init;
                    }
                }, as_value_v<void>);
                using type = type_t<decltype(vtype)>;
                // type should be value-less (at runtime) and default-constructible
                return type{};
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

    template <typename array_t>
    struct is_ndarray< decorator_t<squeeze_t,array_t> >
    {
        static inline constexpr auto value = true;
    }; // is_ndarray
}

#endif // NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP