#ifndef NMTOOLS_ARRAY_INDEX_REDUCE_HPP
#define NMTOOLS_ARRAY_INDEX_REDUCE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/index/normalize_axis.hpp"
#include "nmtools/index/where.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    struct reduction_slices_t {};

    template <typename indices_t, typename shape_type, typename axis_type, typename keepdims_type>
    constexpr auto reduction_slices(const indices_t& indices_, const shape_type& src_shape, const axis_type& m_axis, keepdims_type keepdims)
    {
        using result_t = resolve_optype_t<reduction_slices_t,indices_t,shape_type,axis_type,keepdims_type>;

        auto slices = result_t {};

        // assume tuple result means compile time result
        // tuple of constant index array
        // TODO: proper type check or add concept trait

        if constexpr (!is_tuple_v<result_t>) {
            [[maybe_unused]] auto dim = len(src_shape);
            if constexpr (is_resizable_v<result_t>) {
                slices.resize(dim);
            }

            auto src_dim = len(src_shape);
            [[maybe_unused]]
            auto axis = [&](){
                if constexpr (is_none_v<axis_type>) {
                    return m_axis;
                } else {
                    // TODO: propagate error
                    return unwrap(normalize_axis(m_axis,src_dim));
                }
            }();

            // helper lambda to check if axis i is in the specified axis for reduction
            auto in_axis = [&](auto i){
                if constexpr (is_none_v<axis_type>) {
                    return true;
                } else if constexpr (is_index_v<axis_type> && is_pointer_v<axis_type>) {
                    return i==*axis;
                } else if constexpr (is_index_v<axis_type>) {
                    using common_t = promote_index_t<axis_type,decltype(i)>;
                    return (common_t)i==(common_t)axis;
                } else {
                    auto f_predicate = [i](auto axis){
                        using common_t = promote_index_t<decltype(i),decltype(axis)>;
                        return (common_t)i==(common_t)axis;
                    };
                    // axis is index array (reducing on multiple axes),
                    // axis may be pointer, but can't provide convenience function
                    // since may decay bounded array to pointer
                    if constexpr (is_pointer_v<axis_type>) {
                        auto found = index::where(f_predicate, *axis);
                        return static_cast<bool>(len(found));
                    } else {
                        auto found = index::where(f_predicate, axis);
                        return static_cast<bool>(len(found));
                    }
                }
            };

            // use the same type as axis_type for loop index
            constexpr auto idx_vtype = [](){
                if constexpr (is_constant_index_array_v<axis_type>) {
                    // shortcut for now, just use int
                    return as_value_v<int>;
                } else if constexpr (is_index_array_v<axis_type>) {
                    using type = get_element_type_t<axis_type>;
                    return as_value_v<type>;
                } else if constexpr (is_integer_v<axis_type>) {
                    return as_value_v<axis_type>;
                } else {
                    return as_value_v<size_t>;
                }
            }();
            using index_t = get_index_element_type_t<shape_type>;
            using idx_t [[maybe_unused]] = type_t<meta::promote_index<index_t,type_t<decltype(idx_vtype)>>>;

            // indices and the referenced array may have different dim,
            // this variable track index for indices_
            auto ii = idx_t{0};
            constexpr auto DIM = len_v<shape_type>;
            if constexpr (DIM > 0) {
                // here, len(slices) already matched the dimension of source array
                template_for<DIM>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    // take all elements at given axis
                    if (in_axis(i)) {
                        // note that src_shape maybe constant index array
                        at(slices,i) = {
                            static_cast<nm_size_t>(0)
                            , static_cast<nm_size_t>(at(src_shape,ct_v<i>))};
                        // if keepdims is true, also increment indices index
                        if (keepdims)
                            ii++;
                    }
                    // use indices otherwise, just slice with index:index+1
                    else {
                        auto s = at(indices_,ii++);
                        at(slices,i) = {
                            static_cast<nm_size_t>(s)
                            , static_cast<nm_size_t>(s+1)};
                    }
                });
            } else {
                for (size_t i=0; i<dim; i++) {
                    // take all elements at given axis
                    if (in_axis(i)) {
                        // note that src_shape maybe constant index array
                        at(slices,i) = {
                            static_cast<nm_size_t>(0)
                            , static_cast<nm_size_t>(at(src_shape,i))};
                        // if keepdims is true, also increment indices index
                        if (keepdims)
                            ii++;
                    }
                    // use indices otherwise, just slice with index:index+1
                    else {
                        auto s = at(indices_,ii++);
                        at(slices,i) = {
                            static_cast<nm_size_t>(s)
                            , static_cast<nm_size_t>(s+1)};
                    }
                }
            }
        }

        return slices;
    } // reduction_slices
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct REDUCTION_SLICES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename indices_t, typename shape_type, typename axis_type, typename keepdims_type>
    struct resolve_optype<
        void, index::reduction_slices_t, indices_t, shape_type, axis_type, keepdims_type
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t>
                || !is_index_array_v<shape_type>
                || !(is_index_v<axis_type> || is_none_v<axis_type> || is_index_array_v<axis_type>)
                || !is_index_v<keepdims_type>
            ) {
                using type = error::REDUCTION_SLICES_UNSUPPORTED<indices_t,shape_type,axis_type,keepdims_type>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<indices_t>
                && is_constant_index_array_v<shape_type>
                && is_constant_index_v<axis_type>
                && is_constant_index_v<keepdims_type>
            ) {
                constexpr auto indices  = to_value_v<indices_t>;
                constexpr auto shape    = to_value_v<shape_type>;
                constexpr auto axis     = to_value_v<axis_type>;
                constexpr auto keepdims = keepdims_type{};
                constexpr auto result   = index::reduction_slices(indices,shape,axis,keepdims);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    constexpr auto result_i  = at(result,i);
                    constexpr auto v_slice_i = template_reduce<len(result_i)>([&](auto init, auto index){
                        constexpr auto j = decltype(index)::value;
                        constexpr auto index_ij = at(result_i,j);
                        // TODO: handle mixed index array
                        using init_t = type_t<decltype(init)>;
                        using type = append_type_t<init_t,ct<(nm_size_t)index_ij>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<>>);
                    using slice_t = type_t<decltype(v_slice_i)>;
                    using init_t  = type_t<decltype(init)>;
                    using type = append_type_t<init_t,slice_t>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<shape_type>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<shape_type>;
                using slice_type = nmtools_array<nm_size_t,2>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<slice_type,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<slice_type,B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small_vector
                    using type = nmtools_list<slice_type>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // reduction_slices_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REDUCE_HPP