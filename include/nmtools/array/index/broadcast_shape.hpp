#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/index/max.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/index/where.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of broadcast_shape
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    struct broadcast_shape_t {};

    template <typename ashape_t, typename bshape_t>
    using resolve_broadcast_shape = meta::resolve_optype<void,broadcast_shape_t,meta::remove_cvref_t<ashape_t>,meta::remove_cvref_t<bshape_t>>;

    /**
     * @brief broadcast two array shape together
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t, typename...other_shapes_t>
    constexpr auto broadcast_shape(const ashape_t& ashape, const bshape_t& bshape, const other_shapes_t&...other_shapes)
    {
        using namespace ::nmtools::literals;
        using shape_pack_t = std::tuple<const ashape_t&, const bshape_t&, const other_shapes_t&...>;
        using return_t = meta::apply_reduce_t<resolve_broadcast_shape,shape_pack_t>;

        auto res = return_t{};
        bool success = true;

        auto shapes = shape_pack_t{ashape, bshape, other_shapes...};
        auto dims   = meta::template_map(
            [](auto shape){
                return tuple_size(shape);
            }, shapes
        );

        constexpr auto N = std::tuple_size_v<decltype(shapes)>;
        auto rdim = max(dims);
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(rdim);
        
        // i will start from 0 to rdim (max)
        auto broadcast_shape_impl = [&](auto i){
            // @todo support type list (tuple of int constant)
            // current working index for results
            using idx_t = std::make_signed_t<decltype(rdim-i-1)>;
            idx_t si = rdim - i - 1;

            // current working index for shapes (may be negative, indicating free axis)
            auto shape_indices = meta::template_map([&](auto dim){
                using idx_t = std::make_signed_t<decltype(dim-i-1)>;
                return static_cast<idx_t>(dim-i-1);
            }, dims);

            // check if index is not free (its idx will be >=0)
            // if not free axes is exactly one, we are safe, just take shape at that axis
            // otherwise, axis must all equal, or 1
            auto not_free = meta::template_map(
                // must cast to integer to make sum works properly
                [&](auto i) {
                    return static_cast<size_t>(i >= 0);
                }, shape_indices
            );
            // using sum instead of where to keep compile-time idx
            auto sum_ = sum(not_free);

            // consider the following case
            // shapeA:    (2) idx: (-2,-1, 0)
            // shapeB:  (3,1) idx: (-1, 0, 1)
            // shapeC:(2,3,2) idx: ( 0, 1, 2)
            // result:(2,3,2) idx: ( 0, 1, 2)

            if (sum_==1) {
                // only single non-free axis, can safely assign to ret
                // no need to checking for equal shapes or 1
                meta::template_for<N>([&](auto shape_idx){
                    // shape of shaped_idx-th shapes for current working indices (i)
                    auto shape_index = at(shape_indices, shape_idx);
                    if (shape_index>=0) {
                        auto shape_ = at(shapes, shape_idx);
                        at(res, si) = tuple_at(shape_, shape_index);
                    }
                });
            }
            else {
                // multiple non-free axis detected,
                // must be either same shape or 1

                // TODO: use optional
                auto broadcasted = std::tuple{false,0};
                // unrolled for
                meta::template_for<N>([&](auto shape_idx){
                    auto shape_index = at(shape_indices, shape_idx);
                    if (shape_index>=0 && !at(broadcasted,0_ct)) {
                        // this axis for this shap is not free, broadcasted not set yet set this as initial
                        auto shape_ = at(shapes, shape_idx);
                        // size of this shape for this axis
                        auto size_  = tuple_at(shape_, shape_index);
                        at(broadcasted,1_ct) = size_;
                        at(broadcasted,0_ct) = true;
                    }
                    else if (shape_index>=0 && at(broadcasted,0_ct)) {
                        // this axis for this shap is not free, must be the same as other
                        auto shape_ = at(shapes, shape_idx);
                        // size of this shape for this axis
                        auto size_  = tuple_at(shape_, shape_index);
                        // since current shape exists, make sure to check
                        auto current_size_ = at(broadcasted,1_ct);
                        using common_t = std::common_type_t<decltype(size_),decltype(current_size_)>;
                        // valid if either size_==current_size_ or either size_ or current_size_ is 1
                        if ((size_==current_size_) || (current_size_==1) || (size_==1))
                            at(broadcasted,1_ct) = std::max(static_cast<common_t>(size_),static_cast<common_t>(current_size_));
                        else
                            success = false;
                    }
                }); // template_for
                if (success)
                    at(res,si) = at(broadcasted,1_ct);
            }
        }; // broadcast_shape_impl
        for (int i=0; i<size(res); i++) {
            broadcast_shape_impl(i);
            if (!success)
                break;
        }

        return std::tuple{success, res};
    } // broadcast_shape
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief return resizeable array
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    template <typename ashape_t, typename bshape_t>
    struct resolve_optype <
        void, index::broadcast_shape_t, ashape_t, bshape_t
    >
    {
        template <typename T>
        struct is_resizeable_not_hybrid
            : logical_and<is_resizeable<T>,std::negation<is_hybrid_ndarray<T>>> {};

        using type_list = std::tuple<ashape_t,bshape_t>;
        static constexpr auto selection_kind = [](){
            if constexpr (apply_logical_or_v<is_resizeable_not_hybrid,type_list>)
                return select_resizeable_kind_t {};
            else if constexpr (apply_logical_or_v<is_hybrid_ndarray,type_list>)
                return select_hybrid_kind_t {};
            else return select_fixed_kind_t {};
        }();
        using selection_kind_t = remove_cvref_t<decltype(selection_kind)>;
        // shape type must be integral
        using selection_t = select_array1d_t<
            size_policy_max_t, selection_kind_t, std::is_integral
        >;
        // final type
        using type = resolve_optype_t<
            selection_t, ashape_t, bshape_t
        >;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP