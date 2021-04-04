#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve op type
     * 
     */
    struct broadcast_to_t {};

    /**
     * @brief check if ashape can be broadcasted to bshape
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t>
    constexpr auto broadcast_to(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<broadcast_to_t,ashape_t,bshape_t>;
        using free_axes_t = meta::replace_element_type_t<return_t,bool>;

        auto res = return_t{};

        auto adim = tuple_size(ashape);
        auto bdim = tuple_size(bshape);

        // also track free axes
        auto free_axes = free_axes_t{};
        bool success = bdim >= adim;

        // for broadcast_to, the dimension will follow input shape (bshape)
        // in numpy, the following will raises error
        // np.broadcast_to(np.array([[1],[2],[3]]), (3,))
        // ValueError: input operand has more dimensions than allowed by the axis remapping
        if constexpr (meta::is_resizeable_v<return_t>) {
            res.resize(bdim);
            free_axes.resize(bdim);
        }
        
        auto broadcast_to_impl = [&](auto i){
            using idx_t = std::make_signed_t<decltype(adim-i-1)>;
            idx_t ai = adim - i - 1;
            idx_t bi = bdim - i - 1;
            if (ai<0) {
                at(res,bi) = tuple_at(bshape,bi);
                at(free_axes,bi) = true;
            }
            // unlike broadcast_shape, we dont do this here
            // else if (bi < 0)
            //     at(res,si) = tuple_at(ashape,ai);
            else {
                auto a = tuple_at(ashape,ai);
                auto b = tuple_at(bshape,bi);
                if (a==b) {
                    at(res,bi) = a;
                    at(free_axes,bi) = false;
                }
                else if (a==1) {
                    at(res,bi) = b;
                    at(free_axes,bi) = true;
                }
                else
                    success = false;
            }
        }; // broadcast_to_impl

        for (int i=0; i<size(res); i++) {
            if (!success)
                break;
            broadcast_to_impl(i);
        }

        return std::tuple{success, res, free_axes};
    } // broadcast_to
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type of index::broadcast_to
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    template <typename ashape_t, typename bshape_t>
    struct resolve_optype <
        void, index::broadcast_to_t, ashape_t, bshape_t
    >
    {
        // for broadcast_to, the resulting shape will follow bshape
        using type = tuple_to_array_t<transform_bounded_array_t<bshape_t>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP