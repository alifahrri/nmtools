#ifndef NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"

#include <array>
#include <tuple>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct expand_dims_t {};

    template <typename array_t, typename value_t>
    constexpr auto contains(const array_t& array, const value_t& value)
    {
        if constexpr (meta::has_tuple_size_v<array_t>) {
            bool contain = false;
            meta::template_for<std::tuple_size_v<array_t>>([&](auto i){
                if (utils::isequal(tuple_at(array,i),value))
                    contain = true;
            });
            return contain;
        }
        else {
            for (size_t i=0; i<tuple_size(array); i++)
                if (utils::isequal(at(array,i),value))
                    return true;
            return false;   
        }
    } // contains

    namespace impl
    {
        template <typename newshape_t, typename shape_t, typename axes_t>
        constexpr auto expand_dims(newshape_t& newshape, const shape_t shape, axes_t axes)
        {
            auto n_axes = tuple_size(axes);
            auto dim = tuple_size(shape);

            // resize output if necessary
            if constexpr (meta::is_resizeable_v<newshape_t>)
                newshape.resize(dim+n_axes);
            
            auto idx = size_t{0};
            auto n = len(newshape);
            for (size_t i=0; i<n; i++) {
                // fill ones
                if (contains(axes,i))
                    at(newshape,i) = 1;
                // fill empty with shape
                else {
                    at(newshape,i) = tuple_at(shape,idx);
                    idx++;
                }
            }
        } // expand_dims
    } // namespace impl

    /**
     * @brief extend the shape with value 1 for each given axis
     * 
     * @tparam shape_t 
     * @tparam axes_t 
     * @param shape 
     * @param axes 
     * @return constexpr auto 
     */
    template <typename shape_t, typename axes_t>
    constexpr auto expand_dims(const shape_t shape, axes_t axes)
    {
        using return_t = meta::resolve_optype_t<expand_dims_t,shape_t,axes_t>;
        auto newshape = return_t{};

        impl::expand_dims(newshape, shape, axes);
        
        return newshape;
    } // expand_dims
} // namespace nmtools::index

namespace nmtools
{
    namespace meta
    {
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            void, index::expand_dims_t, shape_t, axes_t
        >
        {
            // deduce the type of expand_dim ops prefer dynamic index array when possible,
            // otherwise select hybrid index, choose fixed index only if both are fixed 
            static constexpr auto vtype = [](){
                if constexpr (is_dynamic_index_array_v<shape_t>)
                    return as_value<shape_t>{};
                else if constexpr (is_dynamic_index_array_v<axes_t>)
                    return as_value<axes_t>{};
                else if constexpr (is_hybrid_index_array_v<shape_t> && is_hybrid_index_array_v<axes_t>) {
                    constexpr auto max_shape = hybrid_index_array_max_size_v<shape_t>;
                    constexpr auto max_axes  = hybrid_index_array_max_size_v<axes_t>;
                    using type = resize_hybrid_index_array_max_size_t<shape_t,max_shape+max_axes>;
                    return as_value<type>{};
                }
                else if constexpr (is_hybrid_index_array_v<shape_t> && is_fixed_index_array_v<axes_t>) {
                    constexpr auto max_shape = hybrid_index_array_max_size_v<shape_t>;
                    constexpr auto n_axes    = fixed_index_array_size_v<axes_t>;
                    using type = resize_hybrid_index_array_max_size_t<shape_t,max_shape+n_axes>;
                    return as_value<type>{};
                }
                else if constexpr (is_fixed_index_array_v<shape_t> && is_hybrid_index_array_v<axes_t>) {
                    constexpr auto n_shape  = fixed_index_array_size_v<shape_t>;
                    constexpr auto max_axes = hybrid_index_array_max_size_v<axes_t>;
                    using type = resize_hybrid_index_array_max_size_t<axes_t,n_shape+max_axes>;
                    return as_value<type>{};
                }
                else if constexpr (is_fixed_index_array_v<shape_t> && is_fixed_index_array_v<axes_t>) {
                    constexpr auto n_shape = fixed_index_array_size_v<shape_t>;
                    constexpr auto n_axes  = fixed_index_array_size_v<axes_t>;
                    using type = resize_fixed_index_array_t<
                        tuple_to_array_t<
                            transform_bounded_array_t<shape_t>>
                        , n_shape+n_axes
                    >;
                    return as_value<type>{};
                }
                else return as_value<void>{};
            }();

            using type = tuple_to_array_t<
                transform_bounded_array_t<
                    type_t<remove_cvref_t<decltype(vtype)>>>
            >;
        }; // resolve_optype
    } // namespace meta
}
#endif // NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP