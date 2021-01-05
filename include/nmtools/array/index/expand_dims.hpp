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
            for (size_t i=0; i<size(newshape); i++) {
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
        /**
         * @brief expand_dims for resizeable shape and axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                is_resizeable_v<shape_t>
                && is_resizeable_v<axes_t>
                && !is_hybrid_vector_v<shape_t>
                && !is_hybrid_vector_v<axes_t>
                && std::is_integral_v<get_element_type_t<shape_t>>
                && std::is_integral_v<get_element_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            using shape_value_t = get_element_type_t<shape_t>;
            using axes_value_t  = get_element_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using type = replace_element_type_t<shape_t,value_t>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for resizeable shape and fixed axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                is_resizeable_v<shape_t>
                && !is_hybrid_vector_v<shape_t>
                && !is_resizeable_v<axes_t>
                && has_tuple_size_v<axes_t>
                && std::is_integral_v<get_element_type_t<shape_t>>
                && std::is_integral_v<get_element_or_common_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            using shape_value_t = get_element_type_t<shape_t>;
            using axes_value_t  = get_element_or_common_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using type = replace_element_type_t<shape_t,value_t>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for resizeable shape and hybrid axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                is_resizeable_v<shape_t>
                && !is_hybrid_vector_v<shape_t>
                && is_resizeable_v<axes_t>
                && is_hybrid_vector_v<axes_t>
                && std::is_integral_v<get_element_type_t<shape_t>>
                && std::is_integral_v<get_element_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            using shape_value_t = get_element_type_t<shape_t>;
            using axes_value_t  = get_element_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using type = replace_element_type_t<shape_t,value_t>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for fixed shape and axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                !is_resizeable_v<shape_t>
                && !is_resizeable_v<axes_t>
                && has_tuple_size_v<shape_t>
                && has_tuple_size_v<axes_t>
                && std::is_integral_v<get_element_or_common_type_t<shape_t>>
                && std::is_integral_v<get_element_or_common_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            static constexpr auto M = std::tuple_size_v<shape_t>;
            static constexpr auto N = std::tuple_size_v<axes_t>;
            using shape_value_t = get_element_or_common_type_t<shape_t>;
            using axes_value_t  = get_element_or_common_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using type    = std::array<value_t,M+N>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for fixed shape and resizeable axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                !is_resizeable_v<shape_t>
                && has_tuple_size_v<shape_t>
                && is_resizeable_v<axes_t>
                && !is_hybrid_vector_v<axes_t>
                && std::is_integral_v<get_element_or_common_type_t<shape_t>>
                && std::is_integral_v<get_element_or_common_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            using shape_value_t = get_element_or_common_type_t<shape_t>;
            using axes_value_t  = get_element_or_common_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using type    = replace_element_type_t<axes_t,value_t>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for fixed shape and hybrid axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                !is_resizeable_v<shape_t>
                && has_tuple_size_v<shape_t>
                && !is_hybrid_vector_v<shape_t>
                && is_resizeable_v<axes_t>
                && is_hybrid_vector_v<axes_t>
                && std::is_integral_v<get_element_or_common_type_t<shape_t>>
                && std::is_integral_v<get_element_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            static constexpr auto N = hybrid_vector_maximum_size_v<axes_t>;
            static constexpr auto M = std::tuple_size_v<shape_t>;
            using shape_value_t = get_element_or_common_type_t<shape_t>;
            using axes_value_t  = get_element_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using newshape_t = replace_element_type_t<axes_t,value_t>;
            using type = replace_hybrid_vector_maximum_size_t<newshape_t,M+N>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for hybrid shape and axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                is_resizeable_v<shape_t>
                && is_hybrid_vector_v<shape_t>
                && is_resizeable_v<axes_t>
                && is_hybrid_vector_v<axes_t>
                && std::is_integral_v<get_element_type_t<shape_t>>
                && std::is_integral_v<get_element_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            static constexpr auto M = hybrid_vector_maximum_size_v<shape_t>;
            static constexpr auto N = hybrid_vector_maximum_size_v<axes_t>;
            using shape_value_t = get_element_type_t<shape_t>;
            using axes_value_t  = get_element_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using newshape_t = replace_element_type_t<shape_t,value_t>;
            using type = replace_hybrid_vector_maximum_size_t<newshape_t,M+N>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for hybrid shape and fixed axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                is_resizeable_v<shape_t>
                && is_hybrid_vector_v<shape_t>
                && !is_resizeable_v<axes_t>
                && has_tuple_size_v<axes_t>
                && std::is_integral_v<get_element_type_t<shape_t>>
                && std::is_integral_v<get_element_or_common_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            static constexpr auto M = hybrid_vector_maximum_size_v<shape_t>;
            static constexpr auto N = std::tuple_size_v<axes_t>;
            using shape_value_t = get_element_type_t<shape_t>;
            using axes_value_t  = get_element_or_common_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using newshape_t = replace_element_type_t<shape_t,value_t>;
            using type = replace_hybrid_vector_maximum_size_t<newshape_t,M+N>;
        }; // resolve_optype expand_dims_t

        /**
         * @brief expand_dims for hybrid shape and resizeable axes
         * 
         * @tparam shape_t 
         * @tparam axes_t 
         */
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            std::enable_if_t<
                is_resizeable_v<shape_t>
                && is_hybrid_vector_v<shape_t>
                && is_resizeable_v<axes_t>
                && !is_hybrid_vector_v<axes_t>
                && std::is_integral_v<get_element_type_t<shape_t>>
                && std::is_integral_v<get_element_or_common_type_t<axes_t>>
            >,
            index::expand_dims_t, shape_t, axes_t
        >
        {
            static constexpr auto M = hybrid_vector_maximum_size_v<shape_t>;
            using shape_value_t = get_element_type_t<shape_t>;
            using axes_value_t  = get_element_type_t<axes_t>;
            using value_t = std::common_type_t<shape_value_t,axes_value_t>;
            using type = replace_element_type_t<axes_t,value_t>;
        }; // resolve_optype expand_dims_t
    } // namespace meta
}
#endif // NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP