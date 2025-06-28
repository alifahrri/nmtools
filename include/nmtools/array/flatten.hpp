#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/core/flatten.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct flatten_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::flatten(args...);
            }
        };
    }

    constexpr inline auto flatten = functor_t{unary_fmap_t<fun::flatten_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FLATTEN_HPP
#define NMTOOLS_ARRAY_ARRAY_FLATTEN_HPP

#include "nmtools/core/flatten.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate flatten.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     array to be flattened
     * @param context   evalutation context
     * @param output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto flatten(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto flattened = view::flatten(array);
        return eval(flattened
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // flatten
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_FLATTEN_HPP