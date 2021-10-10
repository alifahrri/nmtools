#ifndef NMTOOLS_ARRAY_INDEX_FREE_AXES_HPP
#define NMTOOLS_ARRAY_INDEX_FREE_AXES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::index
{
    // TODO: cleanup index functions
    /**
     * @brief given ashape determine which axes' are free with respect to bshape.
     *
     * ashape should be output from shape broadcasting while bshape is the original
     * shape of interest.
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t>
    constexpr auto free_axes(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::replace_element_type_t<ashape_t,bool>;
        auto res = return_t{};

        auto m = len(ashape);
        auto n = len(bshape);
        auto s = m;

        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(s);
        
        auto free_axes_impl = [&](auto i){
            // @todo support type list (tuple of int constant)
            using idx_t = std::make_signed_t<decltype(m-i-1)>;
            idx_t bi = n - i - 1;
            idx_t si = s - i - 1;
            auto free = (bi < 0);
            if (!free)
                free = at(bshape,bi) == 1;
            at(res,si) = free;
        }; // free_axes_impl

        // choose to use int since may be treated as signed
        for (int i=0; i<(int)len(res); i++)
            free_axes_impl(i);

        return res;
    } // free_axes
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_FREE_AXES_HPP