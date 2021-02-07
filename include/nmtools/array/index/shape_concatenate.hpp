#ifndef NMTOOLS_ARRAY_INDEX_SHAPE_CONCATENATE_HPP
#define NMTOOLS_ARRAY_INDEX_SHAPE_CONCATENATE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/shape.hpp"

#include <tuple>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of index::shape_concatenate
     * 
     */
    struct shape_concatenate_t {};

    /**
     * @brief compute the resulting shape of concatenate op
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @tparam axis_t 
     * @param ashape lhs array
     * @param bshape rhs array
     * @param axis The axis along which the arrays will be joined. If axis is None, arrays are flattened before use.
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t, typename axis_t>
    constexpr auto shape_concatenate(const ashape_t& ashape, const bshape_t& bshape, axis_t axis)
    {
        using return_t = meta::resolve_optype_t<shape_concatenate_t,ashape_t,bshape_t,axis_t>;

        auto ret = return_t {};
        bool suc = true;

        auto ad = len(ashape);
        auto bd = len(bshape);

        if constexpr (meta::is_resizeable_v<return_t>)
            ret.resize(ad); // ad must be == bd

        if constexpr (is_none_v<axis_t>)
        {
            auto na = product(ashape);
            auto nb = product(bshape);
            at(ret,0) = na + nb;
        }
        else if (ad==bd) {
            // todo: maybe convert ashape & bshape to array first to simplify expression
            for (size_t i=0; i<ad; i++) {
                auto ai = tuple_at(ashape,i);
                auto bi = tuple_at(bshape,i);
                if (i==axis)
                    at(ret,i) = ai + bi;
                // concat must have same shape except at axis idx
                else if (ai==bi)
                    at(ret,i) = ai;
                else {
                    suc = false;
                    break;
                }
            }
        }
        else suc = false;
        
        return std::tuple{suc,ret};
    } // shape_concatenate
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type for index::shape_concatenate op
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @tparam axis_t 
     */
    template <typename ashape_t, typename bshape_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_concatenate_t, ashape_t, bshape_t, axis_t
    >
    {
        // @todo enforce same dim

        template <typename T>
        struct is_resizeable_not_hybrid
            : logical_and<is_resizeable<T>,std::negation<is_hybrid_ndarray<T>>> {};

        using type_list = std::tuple<ashape_t,bshape_t>;
        static constexpr auto selection_kind = [](){
            // either ashape or bshape is pure resizeable, prefer pure resizeable
            if constexpr (apply_logical_or_v<is_resizeable_not_hybrid,type_list>)
                return select_resizeable_kind_t {};
            // either ashape or bshape is hybrid, but bot is not pure resizeable, prefer hybrid
            else if constexpr (apply_logical_or_v<is_hybrid_ndarray,type_list>)
                return select_hybrid_kind_t {};
            // both is fixed ndarray
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

    template <typename ashape_t, typename bshape_t>
    struct resolve_optype <
        void, index::shape_concatenate_t, ashape_t, bshape_t, none_t
    >
    {
        // todo make is_index_array trait
        template <typename T>
        using is_tuple = is_specialization<T,std::tuple>;
        template <typename T>
        using is_ndarray_or_tuple = compose_logical_or<T,is_ndarray,is_tuple>;

        using type = std::conditional_t<
            is_ndarray_or_tuple<ashape_t>::value
            && is_ndarray_or_tuple<bshape_t>::value,
            std::array<size_t,1>, void
        >;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SHAPE_CONCATENATE_HPP