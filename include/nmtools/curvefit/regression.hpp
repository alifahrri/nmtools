#ifndef NMTOOLS_CURVEFIT_REGRESSION_HPP
#define NMTOOLS_CURVEFIT_REGRESSION_HPP

#include "nmtools/blas.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/utility/tag.hpp"
#include "nmtools/linalg/elimination.hpp"

#include <tuple>
#include <type_traits>

namespace nmtools::curvefit
{
    /* reduce verbosity at function body */
    using std::size;
    using std::tuple;
    using std::is_base_of;
    using std::is_base_of_v;
    using tag::is_assert_v;
    using tag::size_assert_t;
    using tag::is_tag_enabled_v;
    using meta::type_in_tuple;

    namespace regression_tag
    {
        /**
         * @brief default tag for linear_regression, return coefficients
         * 
         */
        struct regression_t {};

        /**
         * @brief tag for linear_regression to return function instead of coefficients
         * 
         */
        struct fn_regression_t : regression_t {};

        /**
         * @brief helper variable template to check if T is a valid tag for linear_regression
         * 
         * @tparam T 
         */
        template <typename T>
        inline constexpr bool is_regression_tag_v = is_base_of_v<regression_t,T>;

        /**
         * @brief specialization of helper variable template is_regression_tag_v 
         * when tuple is supplied as template parameters
         * 
         * @tparam Args 
         */
        template <typename ...Args>
        inline constexpr bool is_regression_tag_v<tuple<Args...>> = type_in_tuple<is_base_of>(regression_t{},tuple<Args...>{});
    } // namespace regression_tag

    namespace rtag = regression_tag;

    /**
     * @brief construct callable for linear function: f(x) = a0 + a1*x
     * 
     * @param a0 
     * @param a1 
     * @return constexpr auto callable f
     */
    constexpr auto make_linear_regression_fn(const auto a0, const auto a1)
    {
        auto f = [=](auto x){
            return a0 + a1 * x;
        };
        return f;
    }

    /**
     * @brief Fit a straight line to the x and y values
     * 
     * @tparam tag_t=size_assert_t 
     * @tparam X vector-like
     * @tparam Y vector-like
     * @param x independent variable
     * @param y dependent variable
     * @return constexpr auto 
     * - [a0,a1], where f(x) = a0 + a1*x; default
     * - f, where f is callable, e.g. f(x); if fn_regression_t in tag_t
     * @cite chapra2014numerical_linear_regression
     */
    template <typename tag_t=size_assert_t, typename X, typename Y>
    constexpr auto linear_regression(const X& x, const Y& y)
    {
        using meta::get_container_value_type_t;
        using traits::remove_cvref_t;
        using traits::is_array1d_v;
        using std::common_type_t;

        static_assert(
            is_array1d_v<X> && is_array1d_v<Y>,
            "only support 1D array for X and Y for linear_regression"
        );

        /* TODO: only allow tag_t to be regression tag or assert tag only!!! */
        constexpr auto is_assert_tag = is_assert_v<tag_t>;
        constexpr auto is_regression_tag = rtag::is_regression_tag_v<tag_t>;

        /* check if assertion tag and return tag is enabled */
        constexpr bool assert_enabled = is_tag_enabled_v<size_assert_t,tag_t>;
        constexpr bool return_fn = is_tag_enabled_v<rtag::fn_regression_t,tag_t>;

        auto nx = size(x);
        auto ny = size(y);

        /* check if we should perform size asserttion */
        if constexpr (assert_enabled)
            assert(nx == ny);

        /* deduce value type */
        using x_t = remove_cvref_t<get_container_value_type_t<X>>;
        using y_t = remove_cvref_t<get_container_value_type_t<Y>>;
        using value_t = common_type_t<x_t,y_t>;

        /* init value for summation */
        auto sum_x = static_cast<value_t>(0);
        auto sum_y = static_cast<value_t>(0);
        auto sumxy = static_cast<value_t>(0);
        auto sumx2 = static_cast<value_t>(0);

        /* compute sums */
        for (int i=0; i<nx; i++) {
            sum_x += x[i];
            sum_y += y[i];
            sumxy += x[i]*y[i];
            sumx2 += x[i]*x[i];
        }

        using n_t = meta::get_value_type_or_same_t<value_t>;
        auto n = static_cast<n_t>(nx);

        /* compute mean */
        auto xm = sum_x / n;
        auto ym = sum_y / n;

        /* compute coefficients */
        auto a1 = (n*sumxy - sum_x*sum_y) / (n*sumx2 - sum_x*sum_x);
        auto a0 = ym - a1*xm;

        /* TODO: also compute estimation of errors */

        /* return callable lambda or tuple of coefficients */
        if constexpr (return_fn)
            return make_linear_regression_fn(a0, a1);
        else
            return std::make_tuple(a0,a1);
    }

    /**
     * @brief construct callable for linear function f(x1,...,xn) = a0 + a1*x1 + ... + an*xn
     * 
     * @tparam A vector-like
     * @param a linear function coefficients
     * @return constexpr auto 
     */
    template <typename A>
    constexpr auto make_linear_least_square_fn(const A& a)
    {
        using linalg::detail::make_array;
        static_assert(traits::is_array1d_v<A>);
        auto f = [=](auto...xs) {
            /* the size of vector a is known at compile time,
                dispatch compile-time version that will assert 
                number of parameter with tnumber of coefficients 
            */
            if constexpr (traits::has_tuple_size_v<A>) {
                using std::tuple_size_v;
                constexpr auto na = tuple_size_v<A>;
                static_assert(sizeof...(xs) == na-1);
                auto y = a[0];
                auto x = make_array(xs...);
                for (int i=1; i<na; i++)
                    y += a[i]*x[i-1];
                return y;
            }
            /* dispatch runtime version that will assert
                number of param with number of coeff at runtime
            */
            else {
                auto na = size(a);
                assert (sizeof...(xs)==na-1);
                auto y = a[0];
                auto x = make_array(xs...);
                for (int i=1; i<na; i++)
                    y += a[i]*x[i-1];
                return y;
            }            
        };
        return f;
    }
    /**
     * @brief generic linear least-square regression
     * note that unlike `linear_regression`, this function
     * takes first argument as dependent variable,
     * followed by independent variables.
     * 
     * @tparam tag_t=rtag::regression_t optional tag,
     * @tparam Y vector-like
     * @tparam X vector-like
     * @tparam Vector vector-like
     * @param y calculated values of dependent variables
     * @param x calculated values of independent variables
     * @param xs (optional) calculated values of independent variables
     * @return constexpr auto
     * - if tag_t==rtag::fn_regression_t, will return callable function
     * - regression coefficients otherwise
     * @cite chapra2014numerical_general_least_square 
     */
    template <typename tag_t=rtag::regression_t, typename Y, typename X, typename ...Vector>
    constexpr auto least_square_regression(const Y& y, const X& x, const Vector& ...xs)
    {
        using namespace linalg;
        using traits::is_array1d_v;
        using linalg::detail::make_array;
        
        static_assert(
            is_array1d_v<X> && is_array1d_v<Y>
            /* TODO: check Vector is array1d */
        );

        auto ones = ones_like(x);
        /* TODO: do not make array if any of vector is dynamic, provide runtime version!!! */
        auto ZT = make_array(ones, x, xs...);
        auto Z = transpose(ZT); // transpose can't mix nested dynamic-fixed container
        auto ZTZ = mmmul(ZT,Z);
        auto ZTy = mvmul(ZT,y);
        auto a = gauss_elimination(ZTZ,ZTy);

        /* TODO: also compute estimation of errors, (use matrix inverse instead of elimination) */

        /* TODO: check if tag_t is valid tag! */
        /* check if we should return function instead of coefficients */
        constexpr bool return_fn = is_tag_enabled_v<rtag::fn_regression_t,tag_t>;
        if constexpr (return_fn)
            return make_linear_least_square_fn(a);
        else
            return a;
    }
}

#endif // NMTOOLS_CURVEFIT_REGRESSION_HPP