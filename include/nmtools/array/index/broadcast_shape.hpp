#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_SHAPE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"

#include <algorithm> // max

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of broadcast_shape
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    struct broadcast_shape_t {};

    /**
     * @brief broadcast two array shape together
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t>
    constexpr auto broadcast_shape(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<broadcast_shape_t,ashape_t,bshape_t>;

        auto res = return_t{};
        bool success = true;

        auto m = tuple_size(ashape);
        auto n = tuple_size(bshape);
        auto s = std::max(m,n);

        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(s);
        
        auto broadcast_shape_impl = [&](auto i){
            // @todo support type list (tuple of int constant)
            using idx_t = std::make_signed_t<decltype(m-i-1)>;
            idx_t ai = m - i - 1;
            idx_t bi = n - i - 1;
            idx_t si = s - i - 1;
            if (ai < 0)
                at(res,si) = tuple_at(bshape,bi);
            else if (bi < 0)
                at(res,si) = tuple_at(ashape,ai);
            else {
                auto a = tuple_at(ashape,ai);
                auto b = tuple_at(bshape,bi);
                if ((a==b) || (b==1))
                    at(res,si) = a;
                else if (a==1)
                    at(res,si) = b;
                else
                    success = false;
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