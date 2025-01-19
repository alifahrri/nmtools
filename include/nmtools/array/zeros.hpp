#ifndef NMTOOLS_ARRAY_VIEW_ZEROS_HPP
#define NMTOOLS_ARRAY_VIEW_ZEROS_HPP

#include "nmtools/array/full.hpp"

namespace nmtools::view
{
    /**
     * @brief Creates zeros view with given shape and dtype.
     *
     * All elements of this views has value of 0.
     * 
     * @tparam shape_t 
     * @tparam T 
     * @param shape 
     * @return constexpr auto 
     */
    template <typename shape_t, typename T>
    constexpr auto zeros(const shape_t& shape, dtype_t<T>)
    {
        return view::full(shape,static_cast<T>(0));
    } // zeros
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ZEROS_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ZEROS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ZEROS_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/full.hpp"
#include "nmtools/array/zeros.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct zeros_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::zeros(args...);
            }
        };
    }

    constexpr inline auto zeros = functor_t{nullary_fmap_t<fun::zeros_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ZEROS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ZEROS_HPP
#define NMTOOLS_ARRAY_ARRAY_ZEROS_HPP

#include "nmtools/array/zeros.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate zeros.
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
        typename shape_t, typename T>
    constexpr auto zeros(const shape_t& shape, dtype_t<T> dtype,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::zeros(shape,dtype);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // zeros
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ZEROS_HPP