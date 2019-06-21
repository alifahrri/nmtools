#ifndef EULER_HPP
#define EULER_HPP

namespace numeric {
    namespace ode {
        namespace detail {
            template <typename DF, typename Scalar>
            void euler(DF &df, Scalar &x, Scalar &y, Scalar h, Scalar &ynew) {
                auto dydx = df(x,y);
                ynew = y + dydx*h;
                x = x + h;
            }
            template <typename DF, typename Scalar>
            void midpoint(DF &df, Scalar &x, Scalar &y, Scalar h, Scalar &ynew) {
                auto dydx = df(x,y);
                auto ym = y + dydx*(h/2);
                auto dymdx = df(x+h/2,ym);
                ynew = y + dymdx*h;
                x = x + h;
            }
        } // namespace detail

        template <typename DF, typename Scalar>
        void euler(DF &df, Scalar yi, Scalar xi, Scalar xf, Scalar dx, Scalar &y) {
            y = yi;
            auto x = xi;
            auto &h = dx;
            const auto &xend = xf;
            do {
                if (xend - x < h) {
                    h = xend - x;
                }
                typename std::decay<decltype(y)>::type ynew;
                detail::euler(df,x,y,h,ynew);
                y = ynew;
            } while (x < xend);
        }
        template <typename DF, typename Scalar>
        void midpoint(DF &df, Scalar yi, Scalar xi, Scalar xf, Scalar dx, Scalar &y) {
            y = yi;
            auto x = xi;
            auto &h = dx;
            const auto &xend = xf;
            do {
                if (xend - x < h) {
                    h = xend - x;
                }
                typename std::decay<decltype(y)>::type ynew;
                detail::midpoint(df,x,y,h,ynew);
                y = ynew;
            } while (x < xend);
        }
    } // namespace ode
} // namespace numeric

#endif