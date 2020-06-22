#include <gtest/gtest.h>
#include <cmath>
#include "nmtools/optimization.hpp"

namespace opt = nmtools::optimization;

TEST(optimization, gold_section_maximum)
{
    auto f = [](double x){
        return 2*sin(x)-(std::pow(x,2)/10);
    };
    double xl{0}, xu{4}, xopt;
    double es{1e-6}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::gold_section(f,xl,xu,xopt,imax,iter,es,ea,fxopt);
    /* see chapra numerical method */
    double x_true{1.4276}, fx_true{1.7757};
    EXPECT_NEAR(xopt,x_true,1e-4);
    EXPECT_NEAR(fxopt,fx_true,1e-4);
}

TEST(optimization, gold_section_generic_max)
{
    auto f = [](double x){
        return 2*sin(x)-(std::pow(x,2)/10);
    };
    double xl{0}, xu{4}, xopt;
    double es{1e-6}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::detail::gold_section(f,xl,xu,xopt,imax,iter,es,ea,fxopt);
    /* see chapra numerical method */
    double x_true{1.4276}, fx_true{1.7757};
    EXPECT_NEAR(xopt,x_true,1e-4);
    EXPECT_NEAR(fxopt,fx_true,1e-4);
}

TEST(optimization, parabolic_interpolation_max_0)
{
    auto f = [](double x){
        return 2*sin(x)-(std::pow(x,2)/10);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{0}, x1{1}, x2{4}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::greater<double>{},&logger);
    /* see chapra numerical method */
    double x_true{1.4276}, fx_true{1.7757};
    EXPECT_NEAR(xopt,x_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, parabolic_interpolation_max_1)
{
    auto f = [](double x){
        return sin(x);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{0}, x1{1}, x2{2}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::greater<double>{},&logger);
    double x_true{M_PI_2}, fx_true{1.};
    EXPECT_NEAR(xopt,x_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, parabolic_interpolation_max_2)
{
    auto f = [](double x){
        return cos(x);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{0}, x1{1}, x2{2}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::greater<double>{},&logger);
    double x_true{0.}, fx_true{1.};
    EXPECT_NEAR(xopt,x_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, parabolic_interpolation_min_1)
{
    auto f = [](double x){
        return cos(x);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(x2,f2) " << "(" << map["x2"] << "," << map["f2"] << "); ";
        ss << "(x3,f3) " << "(" << map["x3"] << "," << map["f3"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    double x0{4}, x1{0}, x2{-2}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::parabolic_interpolation(f,x0,x1,x2,xopt,imax,iter,es,ea,fxopt,std::less<double>{},&logger);
    double x_true{M_PI}, fx_true{-1.};
    EXPECT_NEAR(f(xopt),fx_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, newton_max_0)
{
    auto f = [](double x){
        return 2*sin(x)-(std::pow(x,2)/10.);
    };
    auto df = [](double x){
        return 2*cos(x)-(x/5.);
    };
    auto ddf = [](double x){
        return -2*sin(x)-(1./5.);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(df,ddf) " << "(" << map["df"] << "," << map["ddf"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    auto op = std::greater<double>{};
    double x0{2.5}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::newton(f,df,ddf,x0,xopt,imax,iter,es,ea,fxopt,op,&logger);
    /* see chapra numerical method */
    double x_true{1.4276}, fx_true{1.7757};
    EXPECT_NEAR(xopt,x_true,1e-4) << ss.str();
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

/* todo : resolve minimization*/
TEST(optimization, newton_min_0)
{
    auto f = [](double x){
        return sin(x);
    };
    auto df = [](double x){
        return cos(x);
    };
    auto ddf = [](double x){
        return -sin(x);
    };
    std::stringstream ss;
    auto logger = [&](std::map<std::string,double> map) {
        ss << "LOG : " << map["iter"] << "\n";
        ss << "(x0,f0) " << "(" << map["x0"] << "," << map["f0"] << "); ";
        ss << "(x1,f1) " << "(" << map["x1"] << "," << map["f1"] << "); ";
        ss << "(df,ddf) " << "(" << map["df"] << "," << map["ddf"] << "); ";
        ss << "(xo,fx) " << "(" << map["xopt"] << "," << map["fx"] << "); ";
        ss << "ea : " << "(" << map["ea"] << ")";
        ss << std::endl;
    };
    auto op = std::less<double>{};
    double x0{2.5/2*M_PI}, xopt;
    double es{1e-4}, ea, fxopt;
    size_t imax{1000}, iter;
    opt::newton(f,df,ddf,x0,xopt,imax,iter,es,ea,fxopt,op,&logger);
    double x_true{-1.}, fx_true{-1.};
    EXPECT_NEAR(fxopt,fx_true,1e-4) << ss.str();
}

TEST(optimization, backtracking_line_search) 
{
    namespace nm = nmtools;
    auto f = [](double x) {
        return x*x;
    };
    auto alpha_init{1.0};
    auto xi{1.0};
    auto d{-2.};
    auto tau{0.5};
    auto alpha = nm::optimization::backtracking_line_search(f,xi,d,alpha_init,tau);
    EXPECT_NEAR(alpha,0.5,1e-6);
}

TEST(optimization, backtracking_armijo_line_search) 
{
    namespace nm = nmtools;
    auto f = [](double x) {
        return x*x;
    };
    auto df = [](double x) {
        return 2*x;
    };
    auto alpha_init{1.0};
    auto beta{1.0};
    auto xi{1.0};
    auto d{-2.};
    auto tau{0.5};
    auto alpha = nm::optimization::backtracking_armijo_line_search(f,df,xi,d,alpha_init,beta,tau);
    EXPECT_NEAR(alpha,0.0,1e-6);
}

#define EPS 1e-9
#define NEAR(x,y) (std::fabs(x-y) < EPS)

TEST(optimization, fibonacci_search)
{
    namespace nm = nmtools;
    constexpr auto x_l = -1.0;
    constexpr auto x_u = 1.0;
    {
        auto f = [](double x) {
            return x*x;
        };
        auto x_opt = nm::optimization::fibonacci_search<10>(f,x_l,x_u);
        EXPECT_NEAR(x_opt,0.0,1e-6) << x_opt;
        {
            std::stringstream ss;
            auto logger = [&ss](std::map<std::string,double> iv){
                for (const auto &[k,v] : iv)
                    ss << k << ": " << v << std::endl;
            };
            {
                auto x_opt = nm::optimization::fibonacci_search(f,x_l,x_u,10,&logger);
                EXPECT_NEAR(x_opt,0.0,1e-6) << ss.str();
            }
            {
                auto x_opt = nm::optimization::fibonacci_search<10>(f,x_l,x_u,&logger);
                EXPECT_NEAR(x_opt,0.0,1e-6) << ss.str();
            }
        }
        {
            constexpr auto x_opt = nm::optimization::fibonacci_search<10>(f,x_l,x_u);
            static_assert(NEAR(x_opt,0.0));
        }
    }
    {
        auto f = [](double x) {
            return 3. - x*x;
        };
        auto x_opt = nm::optimization::fibonacci_search<10>(f,x_l,x_u);
        EXPECT_NEAR(x_opt,1.0,1e-6) << x_opt;
        {
            constexpr auto x_opt = nm::optimization::fibonacci_search<10>(f,x_l,x_u);
            static_assert(NEAR(x_opt,1.0));
        }
    }
}

/*
TEST(optimization, gold_section_minimum)
{

}
*/