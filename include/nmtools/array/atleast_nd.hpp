#ifndef NMTOOLS_ARRAY_VIEW_ATLEAST_ND_HPP
#define NMTOOLS_ARRAY_VIEW_ATLEAST_ND_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/index/atleast_nd.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/utility/as_static.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/reshape.hpp"

namespace nmtools::view
{
    template <typename array_t, typename nd_t>
    constexpr auto atleast_nd(const array_t& array, nd_t nd)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_atleast_nd(src_shape,nd);
        return view::reshape(array,dst_shape);
    }

    template <typename array_t>
    constexpr auto atleast_1d(const array_t& array)
    {
        return view::atleast_nd(array,meta::ct_v<1>);
    }

    template <typename array_t>
    constexpr auto atleast_2d(const array_t& array)
    {
        return view::atleast_nd(array,meta::ct_v<2>);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ATLEAST_ND_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_ND_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_ND_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/atleast_nd.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct atleast_nd_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::atleast_nd(args...);
            }
        };
    } // namespace fun

    constexpr inline auto atleast_nd = functor_t{unary_fmap_t<fun::atleast_nd_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_ND_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ATLEAST_ND_HPP
#define NMTOOLS_ARRAY_ARRAY_ATLEAST_ND_HPP

#include "nmtools/array/atleast_nd.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute atleast_nd.
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
        typename array_t, typename nd_t>
    constexpr auto atleast_nd(const array_t& array, nd_t nd
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto viewed = view::atleast_nd(array,nd);
        return eval(viewed
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // atleast_nd
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ATLEAST_ND_HPP