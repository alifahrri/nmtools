#ifndef NMTOOLS_ARRAY_INDEX_CONCATENATE_HPP
#define NMTOOLS_ARRAY_INDEX_CONCATENATE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/shape.hpp"

#include <tuple>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type for index::concatenate
     * 
     */
    struct concatenate_t {};

    /**
     * @brief transform indices from concat dst indices to concat src indices
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @param ashape shape of orignal lhs array
     * @param bshape shape of orignal rhs array
     * @param indices indices of dst (concatenated) array
     * @param axis The axis along which the arrays joined. If axis is None, arrays are flattened before use.
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t, typename indices_t, typename axis_t>
    constexpr auto concatenate(const ashape_t& ashape, const bshape_t& bshape, const indices_t& indices, axis_t axis)
    {
        using a_indices_t = meta::resolve_optype_t<concatenate_t,ashape_t,indices_t,axis_t>;
        using b_indices_t = meta::resolve_optype_t<concatenate_t,bshape_t,indices_t,axis_t>;

        auto a_indices = a_indices_t {};
        auto b_indices = b_indices_t {};

        bool aflag = false;
        bool bflag = false;

        auto ad = len(ashape);
        auto bd = len(bshape);

        if constexpr (meta::is_resizeable_v<a_indices_t>)
            a_indices.resize(ad);
        if constexpr (meta::is_resizeable_v<b_indices_t>)
            b_indices.resize(bd);

        // assume len(indices) == len(ashape) == len(bshape)
        // then we can select which indices to be selected from indices[axis]
        // note that ashape should be lhs shape and rhs shape and lhs array corresponds to lower indices,
        // then if indices[axis] < ahape[axis] select a otherwise select b

        if constexpr (is_none_v<axis_t>) {
            auto na = product(ashape);
            auto nb = product(bshape);
            // todo error handling if len(indices) != 1
            auto i = tuple_at(indices,0);
            if (i<na) {
                aflag = true;
                a_indices = compute_indices(i,ashape);
            }
            else if (i<(na+nb)) {
                bflag = true;
                b_indices = compute_indices(i-na,bshape);
            }
            // not valid
        }
        else {
            auto aa = tuple_at(ashape,axis);
            auto ba = tuple_at(bshape,axis);
            auto ia = tuple_at(indices,axis);
            // todo error handling for other axis
            if (ia<aa) {
                aflag = true;
                // select ashape, no need to offset
                for (size_t i=0; i<ad; i++)
                    at(a_indices,i) = tuple_at(indices,i);
            }
            // also take account for offset
            else if (ia<(ba+aa)) {
                bflag = true;
                // select ashape, must apply offset from ashape
                for (size_t i=0; i<bd; i++) {
                    if (i==axis)
                        at(b_indices,i) = tuple_at(indices,i) - aa;
                    else at(b_indices,i) = tuple_at(indices,i);
                }
            }
            // not valid
        }

        return std::tuple{aflag,bflag,a_indices,b_indices};
    } // concatenate
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type for index::concatenate
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam axis_t 
     */
    template <typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::concatenate_t, shape_t, indices_t, axis_t
    >
    {
        template <typename T>
        struct is_resizeable_not_hybrid
            : logical_and<is_resizeable<T>,std::negation<is_hybrid_ndarray<T>>> {};

        using shape_type   = transform_bounded_array_t<tuple_to_array_t<shape_t>>;
        using indices_type = transform_bounded_array_t<tuple_to_array_t<indices_t>>;
        // index for concatenate should follow shape type
        static constexpr auto selection_kind = [](){
            if constexpr (is_resizeable_not_hybrid<shape_type>::value)
                return select_resizeable_kind_t {};
            else if constexpr (is_hybrid_ndarray_v<shape_type>)
                return select_hybrid_kind_t {};
            else return select_fixed_kind_t {};
        }();
        using selection_kind_t = remove_cvref_t<decltype(selection_kind)>;
        // shape type must be integral
        using selection_t = select_array1d_t<
            size_policy_lhs_t, selection_kind_t, std::is_integral
        >;
        // final type
        using type = resolve_optype_t<
            selection_t, shape_type, indices_type
        >;
    }; // struct resolve_optype

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_CONCATENATE_HPP