#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP

// TODO: remove this file

#include "nmtools/array/atleast_nd.hpp"

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_2D_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/indexing.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/atleast_2d.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct atleast_2d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::atleast_2d(args...);
            }
        };
    }

    constexpr inline auto atleast_2d = functor_t{unary_fmap_t<fun::atleast_2d_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_ARRAY_ATLEAST_2D_HPP

#include "nmtools/array/atleast_2d.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute atleast_2d.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array   Input array
     * @param context Evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto atleast_2d(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto viewed = view::atleast_2d(array);
        return eval(viewed
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // atleast_2d
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ATLEAST_2D_HPP