#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/array/view/ufunc.hpp"
// TODO: maybe do not include all parts of isclose here, refactor to isclose_t maybe
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/to_string/to_string.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for softshrink ufunc
     * 
     * @tparam lambda_t 
     */
    template <typename lambda_t=float>
    struct softshrink
    {
        const lambda_t lambda = 0.5;

        template <typename T>
        constexpr auto operator()(const T& x) const -> T
        {
            if (x > lambda) {
                return x - lambda;
            } else if (x < -lambda) {
                return x + lambda;
            } else {
                return static_cast<T>(0);
            }
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T> args) const noexcept
        {
            return softshrink<T>{nmtools::get<0>(args)};
        }

        template <typename T>
        constexpr auto operator==(const softshrink<T> other) const
        {
            return utils::isclose(lambda,other.lambda);
        }
    }; // softshrink
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename lambda_t>
    struct to_string_t<view::fun::softshrink<lambda_t>,none_t>
    {
        auto operator()(view::fun::softshrink<lambda_t> op) const
        {
            nmtools_string str;

            str += "softshrink{.lambda=";
            str += to_string(op.lambda); 
            str += "}";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename lambda_t=float>
    using softshrink_t = fun::softshrink<lambda_t>;

    /**
     * @brief Create element-wise softshrink ufunc view.
     * 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array     input array
     * @param lambda    lambda value of softshrink formulation
     * @return constexpr auto 
     */
    template <typename array_t, typename lambda_t=float>
    constexpr auto softshrink(const array_t& array, lambda_t lambda=lambda_t{0.5})
    {
        return ufunc(softshrink_t<lambda_t>{{lambda}},array);
    } // softshrink

    template <typename array_t, typename lambda_t=float>
    constexpr auto softshrink(const array_t& array, fun::softshrink<lambda_t> op)
    {
        return ufunc(op,array);
    } // softshrink
    
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_SOFTSHRINK_HPP