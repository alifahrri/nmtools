#include "nmtools/curvefit.hpp"
#include <iostream>
#include <fstream>

namespace nmt = nmtools;
namespace cvt = nmt::curvefit;

#define DESC(x) std::cout << x << std::endl;

auto print_matrix = [](auto M){
    for (const auto m : M) {
        if constexpr (std::is_arithmetic_v<decltype(m)>)
            std::cout << m << "\t";
        else {
            for (const auto a : m)
                std::cout << a << "\t";
        }
        std::cout << std::endl;
    }
};

int main()
{
    DESC("\n# linear regression")
    {
        auto axd = std::array<double,7>{1,2,3,4,5,6,7};
        auto ayd = std::array<double,7>{0.5,2.5,2.0,4.0,3.5,6.0,5.5};

        DESC("## compute coefficients")
        {
            auto [a0, a1] = cvt::linear_regression(axd, ayd);
            std::cout << "f(x) = " << a0 << " + " << a1 << "x" << std::endl;
        }
        DESC("## directly return callable function")
        {
            using tag = cvt::rtag::fn_regression_t;
            auto f = cvt::linear_regression<tag>(axd,ayd);
            DESC("here, we have callable function f:");
            std::cout << "where std::is_invocable_v<decltype(f),double>: "
                << std::boolalpha
                << std::is_invocable_v<decltype(f),double> << std::endl;
            std::cout << "f(0) = " << f(0) << "; f(1) = " << f(1) << std::endl;
            
        }
    }
    DESC("\n# general linear least-square regression")
    {
        auto x1 = std::array<double,6>{ 0., 2., 2.5, 1., 4., 7. };
        auto x2 = std::array<double,6>{ 0., 1., 2.,  3., 6., 2. };
        auto y  = std::array<double,6>{ 5, 10, 9, 0, 3, 27 };
        DESC("## compute coefficients, for f(x1,x2) = a0 + a1*x1 + a2*x2")
        {
            auto [a0, a1, a2] = cvt::least_square_regression(y, x1, x2);
            std::cout << "f(x1,x2) = " << a0 << " + " << a1 << "x1 + " << a2 << "x2" << std::endl;
        }
        DESC("## directly return callable function")
        {
            using tag = cvt::rtag::fn_regression_t;
            auto f = cvt::least_square_regression<tag>(y,x1,x2);
            DESC("here, we have callable function f:");
            std::cout << "where std::is_invocable_v<decltype(f),double,double>: "
                << std::boolalpha
                << std::is_invocable_v<decltype(f),double,double> << std::endl;
            std::cout << "f(0,0) = " << f(0,0) << "; " 
                << "f(1,0) = " << f(1,0) <<"; " 
                << "f(0,1) = " << f(0,1) << std::endl;
        }
    }
    DESC("\n# cubic spline")
    {
        {
            using std::array;

            auto x = array<double,4>{3.0, 4.5, 7.0, 9.0};
            auto y = array<double,4>{2.5, 1.0, 2.5, 0.5};

            auto fn = cvt::cubic_spline(x,y);
            for (const auto t : x) {
                auto [fx, in_range] = fn(t);
                std::cout << "f(" << t << "): " << fx << std::endl;
            }
            auto t = 5.0;
            auto [fx, in_range] = fn(t);
            std::cout << "f(" << t << "): " << fx << std::endl;

            /* write to csv */
            {
                std::ofstream file;
                file.open("cubic_spline.csv");
                file << "cubic spline" << std::endl;
                auto dt = x[3] - x[0];
                for (int i=0; i<1000; i++) {
                    auto t = x[0] + double(i) / 1000 * dt;
                    auto [fx, in_range] = fn(t);
                    file << t << ", " << fx << std::endl;
                }
                file.close();
            }
        }
    }
}