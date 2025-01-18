#ifndef NMTOOLS_ARRAY_VIEW_ONES_HPP
#define NMTOOLS_ARRAY_VIEW_ONES_HPP

#include "nmtools/array/full.hpp"

namespace nmtools::view
{
    /**
     * @brief Creates a ones view with given shape and dtype.
     * 
     * All elements in the view has value of 1.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto ones(const shape_t& shape, dtype_t<T>)
    {
        return view::full(shape,static_cast<T>(1));
    } // ones
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ONES_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/full.hpp"
#include "nmtools/array/ones.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct ones_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::ones(args...);
            }
        };
    }

    constexpr inline auto ones = functor_t{nullary_fmap_t<fun::ones_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ONES_HPP
#define NMTOOLS_ARRAY_ARRAY_ONES_HPP

#include "nmtools/array/ones.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute ones.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam shape_t 
     * @tparam T 
     * @param shape   Desired shape
     * @param dtype   Desired data type
     * @param context Evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename shape_t, typename T=float>
    constexpr auto ones(const shape_t& shape, dtype_t<T> dtype=float32,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::ones(shape,dtype);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // ones
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ONES_HPP