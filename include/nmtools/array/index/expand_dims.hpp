#ifndef NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"

// TODO: move to shape.hpp
#ifdef NMTOOLS_ENABLE_BOOST
#include "nmtools/array/impl/boost.hpp"
#endif

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct expand_dims_t {};

    // TODO: remove
    template <typename array_t, typename value_t>
    constexpr auto contains(const array_t& array, const value_t& value)
    {
        if constexpr (meta::is_fixed_index_array_v<array_t>) {
            bool contain = false;
            meta::template_for<meta::len_v<array_t>>([&](auto i){
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
        // TODO: maybe remove
        template <typename newshape_t, typename shape_t, typename axes_t>
        constexpr auto expand_dims(newshape_t& newshape, const shape_t shape, const axes_t& axes)
        {
            auto n_axes = [&](){
                if constexpr (meta::is_index_array_v<axes_t>)
                    return len(axes);
                else return 1ul;
            }();
            auto dim = len(shape);
            auto n = dim+n_axes;

            // resize output if necessary
            if constexpr (meta::is_resizeable_v<newshape_t>)
                newshape.resize(n);
            
            auto idx = size_t{0};
            for (size_t i=0; i<n; i++) {
                auto in_axis = [&](){
                    if constexpr (meta::is_index_array_v<axes_t>)
                        return contains(axes,i);
                    else return i == (size_t)axes;
                }();
                at(newshape,i) = (in_axis ? 1 : tuple_at(shape,idx));
                idx += (!in_axis ? 1 : 0);
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
    constexpr auto expand_dims([[maybe_unused]] const shape_t shape, [[maybe_unused]] const axes_t& axes)
    {
        using return_t = meta::resolve_optype_t<expand_dims_t,shape_t,axes_t>;
        auto newshape = return_t{};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            impl::expand_dims(newshape, shape, axes);
        }

        return newshape;
    } // expand_dims
} // namespace nmtools::index

namespace nmtools
{
    namespace meta
    {

        namespace error
        {
            template <typename...>
            struct EXPAND_DIMS_UNSUPPORTED : detail::fail_t {};
        } // namespace error
        
        template <typename shape_t, typename axes_t>
        struct resolve_optype<
            void, index::expand_dims_t, shape_t, axes_t
        >
        {
            static constexpr auto vtype = [](){
                if constexpr (is_constant_index_array_v<shape_t> && (is_constant_index_v<axes_t> || is_constant_index_array_v<axes_t>)) {
                    constexpr auto shape = to_value_v<shape_t>;
                    constexpr auto axes  = to_value_v<axes_t>;
                    constexpr auto newshape = index::expand_dims(shape,axes);
                    return template_reduce<nmtools::len(newshape)-1>([&](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = decltype(index)::value + 1;
                        using result_t = append_type_t<init_t,ct<nmtools::at(newshape,I)>>;
                        return as_value_v<result_t>;
                    }, as_value_v<nmtools_tuple<ct<nmtools::at(newshape,0)>>>);
                } else if constexpr (is_fixed_index_array_v<shape_t> && (is_index_v<axes_t> || is_fixed_index_array_v<axes_t>)) {
                    constexpr auto n_axes = [](){
                        if constexpr (is_index_v<axes_t>) {
                            return 1;
                        } else {
                            return len_v<axes_t>;
                        }
                    }();
                    constexpr auto newdim = len_v<shape_t> + n_axes;
                    // TODO: try to resize instead of create new type
                    return as_value_v<nmtools_array<get_element_or_common_type_t<shape_t>,newdim>>;
                } else if constexpr ((is_hybrid_index_array_v<shape_t> || is_fixed_index_array_v<shape_t>) && (is_index_v<axes_t> || is_fixed_index_array_v<axes_t> || is_hybrid_index_array_v<axes_t>)) {
                    constexpr auto n_max_axes = [](){
                        if constexpr (is_index_v<axes_t>) {
                            return 1;
                        } else if constexpr (is_fixed_index_array_v<axes_t>) {
                            return len_v<axes_t>;
                        } else /* if constexpr (is_bounded_size_v<axes_t>) */ {
                            return bounded_size_v<axes_t>;
                        }
                    }();
                    constexpr auto max_dim = bounded_size_v<shape_t> + n_max_axes;
                    using index_t = get_element_or_common_type_t<shape_t>;
                    // TODO: try to resize instead of create new type
                    return as_value_v<nmtools_hybrid_ndarray<index_t,max_dim,1>>;
                } else if constexpr (is_index_array_v<shape_t> && is_index_v<axes_t>) {
                    return as_value_v<shape_t>;
                } else if constexpr ((is_fixed_index_array_v<shape_t> || is_hybrid_index_array_v<shape_t>) && is_index_array_v<axes_t>) {
                    using index_t = get_element_or_common_type_t<shape_t>;
                    return as_value_v<replace_element_type_t<axes_t,index_t>>;
                } else if constexpr (is_index_array_v<shape_t> && is_index_array_v<axes_t>) {
                    return as_value_v<shape_t>;
                } else {
                    return as_value_v<error::EXPAND_DIMS_UNSUPPORTED<shape_t,axes_t>>;
                }
            }();
            using type = type_t<decltype(vtype)>;

            // TODO: remove
            #if 0
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
                else if constexpr (is_hybrid_index_array_v<shape_t> && is_index_v<axes_t>) {
                    constexpr auto max_shape = hybrid_index_array_max_size_v<shape_t>;
                    using type = resize_hybrid_index_array_max_size_t<shape_t,max_shape+1>;
                    return as_value<type>{};
                }
                else if constexpr (is_fixed_index_array_v<shape_t> && is_index_v<axes_t>) {
                    constexpr auto n_shape = fixed_index_array_size_v<shape_t>;
                    using type = resize_fixed_index_array_t<
                        tuple_to_array_t<
                            transform_bounded_array_t<shape_t>>
                        , n_shape+1
                    >;
                    return as_value<type>{};
                }
                else return as_value<void>{};
            }();

            using type = tuple_to_array_t<
                transform_bounded_array_t<
                    type_t<remove_cvref_t<decltype(vtype)>>>
            >;
            #endif
        }; // resolve_optype
    } // namespace meta
}
#endif // NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP