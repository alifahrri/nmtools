#ifndef NMTOOLS_ARRAY_INDEX_REPEAT_HPP
#define NMTOOLS_ARRAY_INDEX_REPEAT_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/index/cumsum.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/sum.hpp"

#include "nmtools/assert.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve repeat return type
     * 
     */
    struct shape_repeat_t {};

    /**
     * @brief Compute the shape of a repeat view.
     * 
     * If axis is none, the shape is reduced to 1D, with size: numel * repeats.
     * Otherwise, the dimension is remains the same.
     * 
     * @tparam shape_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param shape shape of src array
     * @param repeats number of repetitions of each elements
     * @param axis 
     * @return constexpr auto 
     */
    template <typename shape_t, typename repeats_t, typename axis_t>
    constexpr auto shape_repeat(const shape_t& shape, const repeats_t& repeats, [[maybe_unused]] axis_t axis)
    {
        using return_t = meta::resolve_optype_t<shape_repeat_t,shape_t,repeats_t,axis_t>;
        static_assert (meta::is_index_array_v<return_t>
            , "unsupported shape_repeat, maybe specialization of resolve_optype_t<shape_repeat_t,...> required"
        );
        auto ret = return_t {};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            // when axis is None, repeat the flattened array
            // so the resulting shape is 1-dimensional
            if constexpr (is_none_v<axis_t>) {
                auto p = product(shape);
                at(ret,0) = p * repeats;
            }
            else {
                auto n = len(shape);

                if constexpr (meta::is_resizeable_v<return_t>)
                    ret.resize(n);
                
                // TODO: do not use tuple_at
                for (size_t i=0; i<n; i++)
                    at(ret,i) = tuple_at(shape,i);

                if constexpr (meta::is_index_array_v<repeats_t>) {
                    auto r_a = at(ret,axis);
                    auto n   = len(repeats);
                    using common_t = meta::promote_index_t<decltype(r_a),decltype(n)>;
                    // TODO: support optional
                    nmtools_assert ( (common_t)r_a == (common_t)n
                        , "unsupported shape_repeat"
                        // numpy: ValueError: operands could not be broadcast together with shape
                    );
                    // when axis is specified and repeats is index array,
                    // the number of element at the specified axis is simply the sum of the repeats
                    // for example:
                    // >>> x = np.array([[1,2],[3,4]])
                    // >>> np.repeat(x, [1, 2], axis=0)
                    // array([[1, 2],
                    //        [3, 4],
                    //        [3, 4]])
                    // at axis 0, first element x(axis,0) is not repeated (repeats(0)=1)
                    // while the second element x(axis,1) is repeated once (repeats(1)=2)
                    at(ret,axis) = sum(repeats);
                }
                else
                    at(ret,axis) = at(ret,axis) * repeats;
            }
        }

        return ret;
    } // repeat
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_REPEAT_UNSUPPORTED : detail::fail_t {};
    }
    /**
     * @brief resolve return type for index::shape_repeat op
     * 
     * @tparam shape_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     */
    template <typename shape_t, typename repeats_t, typename axis_t>
    struct resolve_optype <
        void, index::shape_repeat_t, shape_t, repeats_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_constant_index_array_v<shape_t>
                && (is_constant_index_v<repeats_t> || is_constant_index_array_v<repeats_t>)
                && (is_none_v<axis_t> || is_constant_index_v<axis_t>)
            ) {
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto repeats = to_value_v<repeats_t>;
                constexpr auto axis    = to_value_v<axis_t>;
                constexpr auto result  = index::shape_repeat(shape,repeats,axis);
                return template_reduce<nmtools::len(result)-1>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using result_t  = append_type_t<init_type,ct<nmtools::at(result,index+1)>>;
                    return as_value_v<result_t>;
                }, as_value_v<nmtools_tuple<ct<nmtools::at(result,0)>>>);
            } else if constexpr (is_none_v<axis_t>) {
                using type = make_array_type_t<size_t,1>;
                return as_value_v<type>;
            } else if constexpr (
                is_index_array_v<shape_t>
                && (is_index_v<repeats_t> || is_index_array_v<repeats_t>)
                && (is_none_v<axis_t> || is_index_v<axis_t>)
            ) {
                using type = tuple_to_array_t<transform_bounded_array_t<shape_t>>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_REPEAT_UNSUPPORTED<shape_t,repeats_t,axis_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of repeat op
     * 
     */
    struct repeat_t {};

    /**
     * @brief Transform indices from repeated view (dst) to indices for origin shape (src).
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param shape original shape
     * @param indices indices from repeat view
     * @param repeats number of repetitions
     * @param axis the axis along which to repeat values
     * @return constexpr auto 
     */
    template <typename shape_t, typename indices_t, typename repeats_t, typename axis_t>
    constexpr auto repeat(const shape_t& shape, const indices_t& indices, const repeats_t& repeats, [[maybe_unused]] axis_t axis)
    {
        using return_t = meta::resolve_optype_t<repeat_t,shape_t,indices_t,repeats_t,axis_t>;
        static_assert (meta::is_index_array_v<return_t>
            , "unsupported index::repeat, could not deduce return type" );
        auto ret = return_t {};

        // following numpy, when axis is None, repeat the flattened array
        // and indices must be integral type or array with size exactly 1
        if constexpr (is_none_v<axis_t>) {
            auto i = [&](){
                if constexpr (meta::is_integral_v<indices_t>)
                    return indices / repeats;
                else {
                    static_assert (meta::len_v<indices_t> == 1
                        , "unsupported index::repeat, expect array with size of 1 when axis is None"
                    );
                    return at<0>(indices) / repeats;
                }
            }();
            ret = compute_indices(i,shape);
        }
        else {
            auto n = len(indices);
            if constexpr (meta::is_resizeable_v<return_t>)
                ret.resize(n);
            for (size_t i=0; i<n; i++) {
                using common_t = meta::promote_index_t<size_t,axis_t>;
                auto idx = at(indices,i);
                if constexpr (meta::is_integral_v<repeats_t>) {
                    at(ret,i) = (static_cast<common_t>(i)==static_cast<common_t>(axis) ? idx / repeats : idx);
                } else {
                    auto csum = cumsum(repeats);
                    if (static_cast<common_t>(i)==static_cast<common_t>(axis)) {
                        // note: len(repeats) == shape[axis]
                        // simply find arg of repeats such that idx >= accumulate(repeats)[args]
                        auto f = [&](auto a){
                            using common_t = meta::promote_index_t<decltype(idx),decltype(a)>;
                            return (common_t)idx<(common_t)a;
                        };
                        auto arg = where(f, csum);
                        at(ret,i) = at(arg,0); // take first
                    }
                    else at(ret,i) = idx;
                }
            } // for
        }

        return ret;
    } // repeat
} // namespace nmtools::index

namespace nmtools::meta
{
    // TODO: cleanup index metafunctions: add error type
    /**
     * @brief resolve return type for repeat op that transform indices from view (dst) to src
     * follow shape_t
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam repeats_t 
     */
    template <typename shape_t, typename indices_t, typename repeats_t, typename axis_t>
    struct resolve_optype<
        void, index::repeat_t, shape_t, indices_t, repeats_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            using type = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
            // make sure type is index array
            if constexpr (!is_index_array_v<type>) {
                // assume the index type is size_t
                using result_t = replace_element_type_t<type,size_t>;
                return as_value_v<result_t>;
            }
            else return as_value_v<type>;
        }();
        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REPEAT_HPP