#ifndef NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP

#include "nmtools/index/argsort.hpp"
#include "nmtools/index/normalize_axis.hpp"
#include "nmtools/index/moveaxis.hpp"
#include "nmtools/array/transpose.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view::detail
{
    using nmtools::index::moveaxis_to_transpose;
}

namespace nmtools::view
{
    /**
     * @brief Move axes of an array to a new postions.
     * 
     * Under the hood, this creates transpose view.
     * 
     * @tparam array_t 
     * @tparam source_t 
     * @tparam destination_t 
     * @param array         input array
     * @param source        original postions of axes to be moved
     * @param destination   desired position for each original axes
     * @return constexpr auto 
     */
    template <typename array_t, typename source_t, typename destination_t>
    constexpr auto moveaxis(const array_t& array, const source_t& source, const destination_t& destination)
    {
        auto shape_ = shape<true>(array);
        auto order  = index::moveaxis_to_transpose(shape_,source,destination);
        return view::transpose(array,order);
    } // moveaxis
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_MOVEAXIS_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/moveaxis.hpp"

namespace nmtools::functional
{
    constexpr inline auto moveaxis_fun = [](const auto&...args){
        return view::moveaxis(args...);
    };

    constexpr inline auto moveaxis = functor_t{unary_fmap_t<decltype(moveaxis_fun)>{{moveaxis_fun}}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_ARRAY_MOVEAXIS_HPP

#include "nmtools/array/moveaxis.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly move axis of an array to another position
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam source_t 
     * @tparam destination_t 
     * @param array         input array
     * @param source        original position of axes to be moved
     * @param destination   desired position for each axes
     * @param context       evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename source_t, typename destination_t>
    constexpr auto moveaxis(const array_t& array, const source_t& source, const destination_t& destination,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::moveaxis(array,source,destination);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // moveaxis
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_MOVEAXIS_HPP