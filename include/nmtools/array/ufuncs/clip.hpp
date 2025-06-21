#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_CLIP_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_CLIP_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/array/ufuncs/less.hpp"
#include "nmtools/array/ufuncs/greater.hpp"
#include "nmtools/array/where.hpp"

namespace nmtools::view
{
    struct clip_t
    {
        template <typename T, typename min_t, typename max_t>
        constexpr auto operator()(const T& t, const min_t& min, const max_t& max) const
        {
            auto r = t < min ? min : t;
                 r = r > max ? max : r;
            return r;
        } // operator()
    }; // clip_t

    template <typename array_t, typename amin_t, typename amax_t>
    constexpr auto clip(const array_t& array, const amin_t& amin, const amax_t& amax)
    {
        auto lt  = view::less(array,amin);
        auto wlt = view::where(lt,amin,array);
        auto gt  = view::greater(wlt,amax);
        auto wgt = view::where(gt,amax,wlt);
        return wgt;
    } // clip
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_CLIP_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/clip.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct clip_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::clip(args...);
            }
        };
    }

    constexpr inline auto clip = functor_t{ternary_fmap_t<fun::clip_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CLIP_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CLIP_HPP
#define NMTOOLS_ARRAY_ARRAY_CLIP_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/clip.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate clip
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam amin_t 
     * @tparam amax_t 
     * @param a array to be clipped
     * @param amin 
     * @param amax 
     * @param context execution context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename amin_t, typename amax_t>
    constexpr auto clip(const array_t& a, const amin_t& amin, const amax_t& amax,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) 
    {
        auto clipped = view::clip(a,amin,amax);
        return eval(clipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // clip
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_CLIP_HPP