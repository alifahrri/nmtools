#ifndef NMTOOLS_EULER_HPP
#define NMTOOLS_EULER_HPP

#include <type_traits>
#include <map>
namespace nmtools::ode {
    namespace detail {
        template <typename DF, typename Scalar>
        constexpr auto euler(DF &df, Scalar &x, Scalar &y, Scalar h) {
            auto dydx = df(x,y);
            auto ynew = y + dydx*h;
            return ynew;
        }
        template <typename DF, typename Scalar>
        constexpr auto midpoint(DF &df, Scalar &x, Scalar &y, Scalar h) {
            auto dydx = df(x,y);
            auto ym = y + dydx*(h/2);
            auto dymdx = df(x+h/2,ym);
            auto ynew = y + dymdx*h;
            return ynew;
        }
        template <typename DF, typename Scalar>
        constexpr auto heun(DF &df, Scalar &x, Scalar &y, Scalar h) {
            auto dy1dx = df(x,y);
            auto ye = y + dy1dx*h;
            auto dy2dx = df(x+h,ye);
            auto slope = (dy1dx + dy2dx) / 2;
            auto ynew = y + slope*h;
            return ynew;
        }
        template <typename DF, typename Scalar, typename Integrator, typename Logger=std::nullptr_t>
        constexpr auto common_driver(DF &df, Scalar yi, Scalar xi, Scalar xf, Scalar dx, const Integrator &integrator, Logger *logger=Logger{}) {
            auto y = yi;
            auto x = xi;
            auto &h = dx;
            const auto &xend = xf;
            size_t i=0;
            do {
                if (xend - x < h) {
                    h = xend - x;
                }
                if constexpr (!std::is_same_v<Logger,std::nullptr_t>) {
                    static_assert(std::is_pointer_v<decltype(logger)>);
                    using arg_t = std::map<std::string,Scalar>;
                    /* TODO: check if callable */
                    (*logger)(arg_t{{"i",i},{"x",x},{"y",y},{"h",h}});
                }
                auto ynew = integrator(df,x,y,h);
                x = x + h;
                y = ynew;
            } while (x < xend);
            return y;
        }
    } // namespace detail

    /**
     * @brief evaluate ODE initial value problem using Euler's method
     * 
     * @tparam DF differential equation, with signature DF(ScalarX,ScalarY)
     * @tparam ScalarY real number for y
     * @tparam ScalarX real number for x
     * @tparam Logger=std::nullptr_t 
     * @param df callable differential equation
     * \f[
     *      \frac{dy}{dx} = f(x,y)
     * \f]
     * @param yi initital dependent variable
     * @param xi initital independent variable
     * @param xf final independent variable
     * @param dx independent variable step
     * @param logger optional intermediate value logger
     * no runtime cost (logging block won't be compiled) if left unspecified
     * @return constexpr auto 
     * @cite chapra2014numerical_ode_euler
     */
    template <typename DF, typename ScalarY, typename ScalarX, typename Logger=std::nullptr_t>
    constexpr auto euler(DF &df, ScalarY yi, ScalarX xi, ScalarX xf, ScalarX dx, Logger *logger=Logger{}) {
        constexpr auto integrator = [](DF &df, auto&& x, auto&& y, auto&& h){
            return detail::euler(df,x,y,h);
        };
        return detail::common_driver(df,yi,xi,xf,dx,integrator);
    }

    /**
     * @brief evaluate ODE initial value problem using 
     * modified Euler's (a.k.a the midpoint a.k.a improved polygon) method
     * 
     * @tparam DF differential equation, with signature DF(ScalarX,ScalarY)
     * @tparam ScalarY real number for y
     * @tparam ScalarX real number for x
     * @tparam Logger=std::nullptr_t 
     * @param df callable differential equation
     * \f[
     *      \frac{dy}{dx} = f(x,y)
     * \f]
     * @param yi initital dependent variable
     * @param xi initital independent variable
     * @param xf final independent variable
     * @param dx independent variable step
     * @param logger optional intermediate value logger
     * no runtime cost (logging block won't be compiled) if left unspecified
     * @return constexpr auto 
     * @cite chapra2014numerical_ode_midpoint
     */
    template <typename DF, typename ScalarY, typename ScalarX, typename Logger=std::nullptr_t>
    constexpr auto midpoint(DF &df, ScalarY yi, ScalarX xi, ScalarX xf, ScalarX dx, Logger *logger=Logger{}) {
        constexpr auto integrator = [](DF &df, auto&& x, auto &&y, auto&& h){
            return detail::midpoint(df,x,y,h);
        };
        return detail::common_driver(df,yi,xi,xf,dx,integrator);
    }
    /**
     * @brief evaluate ODE initial value problem using Heun's method
     * 
     * @tparam DF differential equation, with signature DF(ScalarX,ScalarY)
     * @tparam ScalarY real number for y
     * @tparam ScalarX real number for x
     * @tparam Logger=std::nullptr_t 
     * @param df callable differential equation
     * \f[
     *      \frac{dy}{dx} = f(x,y)
     * \f]
     * @param yi initital dependent variable
     * @param xi initital independent variable
     * @param xf final independent variable
     * @param dx independent variable step
     * @param logger optional intermediate value logger
     * no runtime cost (logging block won't be compiled) if left unspecified
     * @return constexpr auto 
     * @cite chapra2014numerical_ode_heun
     */
    template <typename DF, typename ScalarY, typename ScalarX, typename Logger=std::nullptr_t>
    constexpr auto heun(DF &df, ScalarY yi, ScalarX xi, ScalarX xf, ScalarX dx, Logger *logger=Logger{}) {
        constexpr auto integrator = [](DF &df, auto&& x, auto&& y, auto&& h){
            return detail::heun(df,x,y,h);
        };
        return detail::common_driver(df,yi,xi,xf,dx,integrator);
    }
} // namespace nmtools::ode

#endif