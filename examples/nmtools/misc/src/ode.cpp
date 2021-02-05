#include "nmtools/ode.hpp"
#include <iostream>

#define DESC(x) std::cout << x << std::endl;

namespace nmt = nmtools;
namespace ode = nmtools::ode;

int main()
{
    /* define differential equation */
    constexpr auto dy = [](double x, double y) {
        return -2*std::pow(x,3) + 12*std::pow(x,2) - 20*x + 8.5;
    };
    /* initial state and step */
    constexpr double h{0.125};
    constexpr double xi{0.0}, xf{0.5}, yi{1.0};
    constexpr double zero{5e-5};

    DESC("compute ode at runtime using Runge-Kutta method")
    {
        /* create intermediate-value logger */
        auto logging = [](auto mapping){
            std::cout << "iteration: " << mapping["i"] << std::endl;
            for (const auto &[k,v] : mapping)
                if (k!=std::string("i")) // skip printing iteration idx
                    std::cout << k << ": " << v << "\t";
            std::cout << std::endl;
        };
        auto yn = ode::rk4(dy,xi,xf,yi,h,&logging);
        std::cout << yn << std::endl;
    }

    DESC("compute ode at compile-time using Runge-Kutta method")
    {
        constexpr auto yn = ode::rk4(dy,xi,xf,yi,h);
        static_assert(nmt::near(yn,3.21875,zero));
        std::cout << yn << std::endl;
    }
}