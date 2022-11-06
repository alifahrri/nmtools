#ifndef NMTOOLS_ARRAY_INDEX_COMPRESS_HPP
#define NMTOOLS_ARRAY_INDEX_COMPRESS_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/index/count.hpp"

namespace nmtools::index
{
    struct shape_compress_t {};

    struct compress_t {};

    template <typename condition_t, typename shape_t, typename axis_t>
    constexpr auto shape_compress(const condition_t& condition, const shape_t& shape, [[maybe_unused]] const axis_t axis)
    {
        using return_t = meta::resolve_optype_t<shape_compress_t,condition_t,shape_t,axis_t>;

        auto res = return_t{};

        // the dimension of the result should be:
        // - at maximum, the length of condition
        // - at a given axis, the size at that axis is the number of nonzero elements of condition
        // example from numpy:
        // ```
        // >>> a = np.array([[1, 2], [3, 4], [5, 6]])
        // >>> np.compress([0, 1], a, axis=0)
        // array([[3, 4]])
        // >>> np.compress([0, 1], a, axis=0).shape
        // (1, 2)
        // >>> np.compress([0], a, axis=0)
        // array([], shape=(0, 2), dtype=int64)
        // ```
        // note that when the value of condition is zero, shape=(0,2)
        // another example:
        // ```
        // >>> np.compress([False, True], a, axis=1)
        // array([[2],
        //     [4],
        //     [6]])
        // >>> np.compress([False, True], a, axis=1).shape
        // (3, 1)
        // ```

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            auto c_dim = len(nonzero(condition));
            if constexpr (is_none_v<axis_t>)
                at(res,0) = c_dim;
            else {
                // array dim
                [[maybe_unused]] auto dim = len(shape);
                if constexpr (meta::is_resizable_v<return_t>)
                    res.resize(dim);

                auto shape_compress_impl = [&](auto i){
                    using a_t = meta::get_element_or_common_type_t<axis_t>;
                    using idx_t = meta::promote_index_t<decltype(i),a_t>;
                    at(res,i) = ((idx_t)i == (idx_t)axis) ? c_dim : at(shape,i);
                };

                if constexpr (meta::is_fixed_index_array_v<shape_t>) {
                    constexpr auto N = meta::len_v<shape_t>;
                    meta::template_for<N>(shape_compress_impl);
                }
                else {
                    for (size_t i=0; i<dim; i++)
                        shape_compress_impl(i);
                }
            }
        }

        return res;
    } // shape_compress

    template <typename indices_t, typename condition_t, typename shape_t, typename axis_t>
    constexpr auto compress(const indices_t& indices, const condition_t& condition, const shape_t& shape, axis_t axis)
    {
        using return_t = meta::resolve_optype_t<compress_t,indices_t,condition_t,shape_t,axis_t>;
        static_assert (!meta::is_void_v<return_t>
            , "unsupported index::compress, couldn't deduce return type");

        auto res = return_t{};

        if constexpr (meta::is_resizable_v<return_t>) {
            // array dim
            auto dim = len(shape);
            res.resize(dim);
        }

        // maps dst indices (compress) to src indices (following shape)
        // given condition and axis
        // let:
        // ```
        // indices = [2,0]
        // condition = [1,0,1,0,1]
        // shape, axis = [5,2], 0
        // ```
        // the resulting indices should be `[4,0]`
        // this can be calculated as follows
        // - at axis=0, dst indices=2
        // - we know that nonzero_condition = [1,1,1] with nonzero_condition_index = [0,2,4]
        // - create a mapping indices[axis] -> nonzero_condition_index, (2->4)
        // ```
        // # here, x is indices[axis]
        // f = lambda x: nonzero_condition_index[x]
        // ```
        // for flat indices (axis is None)
        // ```
        // indices = [0]
        // condition = [0,1]
        // shape, axis = [3,2], 0
        // ```
        // the resulting indices should be `[0,1]`
        // 

        // TODO: provide overload for computed idx_nonzero
        // compute indices of condition which has true/nonzero value
        auto fun_nonzero = [](auto i){
            return static_cast<bool>(i);
        };
        auto idx_nonzero = where(fun_nonzero, condition);

        // i should start form 0 to len(shape)
        [[maybe_unused]] auto compress_impl = [&](auto i){
            auto dst_i = at(indices, i);
            using common_t = meta::promote_index_t<axis_t,decltype(i)>;
            at(res, i) = ((common_t)i == (common_t)axis) ? at(idx_nonzero,dst_i) : dst_i;
        };

        if constexpr (is_none_v<axis_t>) {
            // handle flat indices
            // TODO: provide overload that already compute strides
            auto strides = compute_strides(shape);
            auto index   = at(indices,0);
            auto offset  = at(idx_nonzero,index);
            impl::compute_indices(res, offset, shape, strides);
        }
        else {
            // assume len(indices) == len(shape) == len(res)
            if constexpr (meta::is_fixed_index_array_v<indices_t>) {
                constexpr auto N = meta::len_v<indices_t>;
                meta::template_for<N>(compress_impl);
            }
            else {
                auto n = len(indices);
                for (size_t i=0; i<n; i++)
                    compress_impl(i);
            }
        }

        return res;
    } // compress
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_COMPRESS_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Infer the type of shape_compress index function
     * 
     * @tparam condition_t 
     * @tparam shape_t 
     * @tparam axis_t 
     */
    template <typename condition_t, typename shape_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_compress_t, condition_t, shape_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_constant_index_array_v<condition_t>
                && is_constant_index_array_v<shape_t>
                && (is_constant_index_v<axis_t> || is_none_v<axis_t>)
            ) {
                constexpr auto condition = to_value_v<condition_t>;
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto axis   = to_value_v<axis_t>;
                constexpr auto result = index::shape_compress(condition,shape,axis);
                using index_t = get_index_element_type_t<decltype(result)>;
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)-1>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,ct<(index_t)at(result,index+1)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<ct<(index_t)at(result,0)>>>);
            } else if constexpr (
                is_constant_index_array_v<condition_t>
            ) {
                using condition_type = decltype(to_value_v<condition_t>);
                using type = resolve_optype_t<index::shape_compress_t,condition_type,shape_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<shape_t>
            ) {
                using shape_type = decltype(to_value_v<shape_t>);
                using type = resolve_optype_t<index::shape_compress_t,condition_t,shape_type,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_index_array_v<condition_t>
                && is_index_array_v<shape_t>
                && is_none_v<axis_t>
            ) {
                using index_t = get_index_element_type_t<shape_t>;
                using type = nmtools_array<index_t,1>;
                return as_value_v<type>;
            } else if constexpr (
                is_index_array_v<condition_t>
                && is_index_array_v<shape_t>
                && is_index_v<axis_t>
            ) {
                // compress doesn't reduce dimension, so simply return the same as shape_t
                using type = transform_bounded_array_t<shape_t>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_COMPRESS_UNSUPPORTED<condition_t,shape_t,axis_t>;
                return as_value_v<type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // shape_compress_t

    // TODO: cleanup index metafunctions
    template <typename indices_t, typename condition_t, typename shape_t, typename axis_t>
    struct resolve_optype<
        void, index::compress_t, indices_t, condition_t, shape_t, axis_t
    >
    {
        // just follow the type original array shape type
        // this should also be the case for None axis
        using type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
    }; // compress_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPRESS_HPP