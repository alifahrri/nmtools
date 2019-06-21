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
            template <typename DF, typename Scalar>
            void heun(DF &df, Scalar &x, Scalar &y, Scalar h, Scalar &ynew) {
                auto dy1dx = df(x,y);
                auto ye = y + dy1dx*h;
                auto dy2dx = df(x+h,ye);
                auto slope = (dy1dx + dy2dx) / 2;
                ynew = y + slope*h;
                x = x + h;
            }
            template <typename DF, typename Scalar, typename Integrator>
            void common_driver(DF &df, Scalar yi, Scalar xi, Scalar xf, Scalar dx, Scalar &y, const Integrator &integrator) {
                y = yi;
                auto x = xi;
                auto &h = dx;
                const auto &xend = xf;
                do {
                    if (xend - x < h) {
                        h = xend - x;
                    }
                    typename std::decay<decltype(y)>::type ynew;
                    integrator(df,x,y,h,ynew);
                    y = ynew;
                } while (x < xend);
            }
        } // namespace detail

        template <typename DF, typename Scalar>
        void euler(DF &df, Scalar yi, Scalar xi, Scalar xf, Scalar dx, Scalar &y) {
            detail::common_driver(df,yi,xi,xf,dx,y,[](DF &df, Scalar &x, Scalar &y, Scalar h, Scalar &ynew){
                detail::euler(df,x,y,h,ynew);
            });
        }
        template <typename DF, typename Scalar>
        void midpoint(DF &df, Scalar yi, Scalar xi, Scalar xf, Scalar dx, Scalar &y) {
            detail::common_driver(df,yi,xi,xf,dx,y,[](DF &df, Scalar &x, Scalar &y, Scalar h, Scalar &ynew){
                detail::midpoint(df,x,y,h,ynew);
            });
        }
        template <typename DF, typename Scalar>
        void heun(DF &df, Scalar yi, Scalar xi, Scalar xf, Scalar dx, Scalar &y) {
            detail::common_driver(df,yi,xi,xf,dx,y,[](DF &df, Scalar &x, Scalar &y, Scalar h, Scalar &ynew){
                detail::heun(df,x,y,h,ynew);
            });
        }
    } // namespace ode
} // namespace numeric

#endif