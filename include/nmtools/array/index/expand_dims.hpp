#ifndef NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/utility/unwrap.hpp"

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
                if (utils::isequal(at(array,i),value))
                    contain = true;
            });
            return contain;
        }
        else {
            for (size_t i=0; i<len(array); i++)
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
        using result_t = meta::resolve_optype_t<shape_expand_dims_t,shape_t,axes_t>;
        auto new_shape = result_t{};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            auto n_axes = [&](){
                if constexpr (meta::is_index_array_v<axes_t>)
                    return len(axes);
                else return 1ul;
            }();
            auto dim = len(shape);
            [[maybe_unused]] auto n = dim + n_axes;

            // TODO: propagate error
            auto normalized_axes = unwrap(normalize_axis(axes,n));

            // resize output if necessary
            if constexpr (meta::is_resizable_v<result_t>) {
                new_shape.resize(n);
            }
            
            auto idx = nm_size_t{0};
            auto shape_expand_dims_impl = [&](auto i){
                auto in_axis = [&](){
                    if constexpr (meta::is_index_array_v<axes_t>)
                        return contains(normalized_axes,i);
                    else return i == (nm_size_t)normalized_axes;
                }();
                at(new_shape,i) = (in_axis ? 1 : at(shape,idx));
                idx += (!in_axis ? 1 : 0);
            };
            if constexpr (meta::is_tuple_v<result_t>) {
                constexpr auto N = meta::len_v<result_t>;
                meta::template_for<N>(shape_expand_dims_impl);
            } else {
                for (size_t i=0; i<n; i++) {
                    shape_expand_dims_impl(i);
                }
            }
        }

        return new_shape;
    } // shape_expand_dims
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
                if constexpr (
                    is_constant_index_array_v<shape_t>
                    && is_constant_index_v<axes_t>
                ) {
                    constexpr auto shape = to_value_v<shape_t>;
                    constexpr auto axes  = to_value_v<axes_t>;
                    constexpr auto new_shape = index::shape_expand_dims(shape,axes);
                    using nmtools::len, nmtools::at;
                    return template_reduce<len(new_shape)>([&](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = at(new_shape,index);
                        if constexpr (is_constant_index_array_v<shape_t>) {
                            using result_t = append_type_t<init_t,ct<I>>;
                            return as_value_v<result_t>;
                        } else {
                            using result_t = append_type_t<init_t,clipped_size_t<I>>;
                            return as_value_v<result_t>;
                        }
                    }, as_value_v<nmtools_tuple<>>);
                } else if constexpr (is_index_array_v<shape_t> && (is_index_v<axes_t>)) {
                    constexpr auto N = len_v<shape_t>;
                    [[maybe_unused]] constexpr auto B_SIZE = bounded_size_v<shape_t>;
                    using index_t = get_index_element_type_t<shape_t>;
                    if constexpr (N > 0) {
                        using type = nmtools_array<index_t,N+1>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(B_SIZE)>) {
                        using type = nmtools_static_vector<index_t,B_SIZE+1>;
                        return as_value_v<type>;
                    } else {
                        using type = nmtools_list<index_t>;
                        return as_value_v<type>;
                    }
                } else if constexpr (is_index_array_v<shape_t> && is_index_array_v<axes_t>) {
                    constexpr auto N = len_v<shape_t>;
                    constexpr auto M = len_v<axes_t>;
                    [[maybe_unused]] constexpr auto B_N = bounded_size_v<shape_t>;
                    [[maybe_unused]] constexpr auto B_M = bounded_size_v<axes_t>;
                    using index_t = get_index_element_type_t<shape_t>;
                    if constexpr (N > 0 && M > 0) {
                        using type = nmtools_array<index_t,N+M>;
                        return as_value_v<type>;
                    } else if constexpr (N > 0 && !is_fail_v<decltype(B_M)>) {
                        using type = nmtools_static_vector<index_t,N+B_M>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(B_N)> && M > 0) {
                        using type = nmtools_static_vector<index_t,B_N+M>;
                        return as_value_v<type>;
                    } else if constexpr (!is_fail_v<decltype(B_N)> && !is_fail_v<decltype(B_M)>) {
                        using type = nmtools_static_vector<index_t,B_N+B_M>;
                        return as_value_v<type>;
                    } else {
                        using type = nmtools_list<index_t>;
                        return as_value_v<type>;
                    }
                } else {
                    return as_value_v<error::EXPAND_DIMS_UNSUPPORTED<shape_t,axes_t>>;
                }
            }();
            using type = type_t<decltype(vtype)>;
        }; // resolve_optype
    } // namespace meta
}
#endif // NMTOOLS_ARRAY_INDEX_EXPAND_DIMS_HPP