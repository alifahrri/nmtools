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
    struct shape_expand_dims_t {};

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
    constexpr auto shape_expand_dims([[maybe_unused]] const shape_t& shape, [[maybe_unused]] const axes_t& axes)
    {
        using return_t = meta::resolve_optype_t<shape_expand_dims_t,shape_t,axes_t>;
        auto newshape = return_t{};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            auto n_axes = [&](){
                if constexpr (meta::is_index_array_v<axes_t>)
                    return len(axes);
                else return 1ul;
            }();
            auto dim = len(shape);
            auto n = dim+n_axes;

            // resize output if necessary
            if constexpr (meta::is_resizeable_v<return_t>)
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
        }

        return newshape;
    } // shape_expand_dims

    // TODO: remove
    template <typename shape_t, typename axes_t>
    constexpr auto expand_dims([[maybe_unused]] const shape_t& shape, [[maybe_unused]] const axes_t& axes)
    {
        return shape_expand_dims(shape,axes);
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
            void, index::shape_expand_dims_t, shape_t, axes_t
        >
        {
            static constexpr auto vtype = [](){
                // TODO: use more generic fixed_shape, fixed_size, fixed_dim
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
                    return as_value_v<nmtools_array<get_index_element_type_t<shape_t>,newdim>>;
                } else if constexpr ((is_hybrid_index_array_v<shape_t> || is_fixed_index_array_v<shape_t>) && (is_index_v<axes_t> || is_fixed_index_array_v<axes_t> || is_hybrid_index_array_v<axes_t>)) {
                    constexpr auto n_max_axes = [](){
                        constexpr auto N = len_v<axes_t>;
                        using len_type [[maybe_unused]] = decltype(N);
                        [[maybe_unused]] constexpr auto bounded_size = bounded_size_v<axes_t>;
                        if constexpr (is_index_v<axes_t>) {
                            return 1;
                        } else if constexpr (!is_fail_v<len_type>) {
                            // NOTE: zero len is invalid
                            if constexpr (N > 0) {
                                return N;
                            } else {
                                return bounded_size;
                            }
                        } else /* if constexpr (is_bounded_size_v<axes_t>) */ {
                            return bounded_size;
                        }
                    }();
                    constexpr auto shape_dim = [](){
                        constexpr auto N = len_v<shape_t>;
                        [[maybe_unused]] constexpr auto bounded_size = bounded_size_v<shape_t>;
                        if constexpr (!is_fail_v<decltype(N)>) {
                            if constexpr (N > 0) {
                                return N;
                            } else {
                                return bounded_size;
                            }
                        } else {
                            return bounded_size;
                        }
                    }();
                    constexpr auto max_dim = shape_dim + n_max_axes;
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
        }; // resolve_optype
    } // namespace meta
}
#endif // NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP