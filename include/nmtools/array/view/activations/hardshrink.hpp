#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP

#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/core/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for hardshrink ufunc.
     * 
     * @tparam lambda_t 
     */
    template <typename lambda_t=float>
    struct hardshrink
    {
        const lambda_t lambda = 0.5;

        template <typename T>
        constexpr auto operator()(const T& t) const -> T
        {
            auto x = t;
            if ((x >= -lambda) && (x <= lambda)) {
                x = 0;
            }
            return x;
        } // operator()

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& t) const noexcept
        {
            return hardshrink<T>{nmtools::get<0>(t)};
        }

        template <typename T>
        constexpr auto operator==(const hardshrink<T> other) const
        {
            return utils::isclose(lambda,other.lambda);
        }
    }; // hardshrink
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename lambda_t
        , auto...fmt_args
    >
    struct to_string_t<view::fun::hardshrink<lambda_t>
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::hardshrink<lambda_t> op) const
        {
            nmtools_string str;

            str += "hardshrink";
            str += "{";
            str += ".lambda=";
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
    using hardshrink_t = fun::hardshrink<lambda_t>;

    /**
     * @brief Creates element-wise hardshrink ufunc view.
     * 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array 
     * @param lambda 
     * @return constexpr auto 
     */
    template <typename array_t, typename lambda_t=float>
    constexpr auto hardshrink(const array_t& array, lambda_t lambda=lambda_t{0.5})
    {
        return ufunc(hardshrink_t<lambda_t>{{lambda}},array);
    } // hardshrink

    template <typename array_t, typename lambda_t=float>
    constexpr auto hardshrink(const array_t& array, fun::hardshrink<lambda_t> op)
    {
        return ufunc(op,array);
    } // hardshrink
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATION_HARDSHRINK_HPP