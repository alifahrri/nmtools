#include "nmtools/optimization.hpp"
#include "nmtools/utility.hpp"
#include <iostream>

namespace nm = nmtools;
namespace optim = nmtools::optimization;

#define DESC(x) std::cout << x << std::endl;
#define EPS 1e-9
#define NEAR(x,y) (std::fabs(x-y) < EPS)

int main()
{
    /* define objective function */
    auto f = [](double x) {
        return x*x;
    };
    /* create logger to observe intermediate value (optional) */
    auto logger = [](std::map<std::string,double> iv){
        for (const auto &[k,v] : iv)
            std::cout << k << ": " << v << std::endl;
    };
    constexpr auto x_l = -2.0;
    constexpr auto x_u = 2.0;
    {
        DESC("compute fibonacci search at compile time");
        constexpr auto x_opt = optim::fibonacci_search<10>(f,x_l,x_u);
        static_assert(NEAR(x_opt,0.0));
        std::cout << "x* : " << x_opt << std::endl;
    }
    {
        DESC("compute fibonacci search at runtime with intermediate value logging");
        auto x_opt = optim::fibonacci_search(f,x_l,x_u,10,&logger);
        std::cout << "x* : " << x_opt << std::endl;
    }
}