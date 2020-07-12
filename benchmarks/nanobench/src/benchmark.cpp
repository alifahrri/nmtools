#define ANKERL_NANOBENCH_IMPLEMENT

#include "fibonacci_search.hpp"
#include "ode.hpp"
#include "spline.hpp"
#include "common.hpp"

int main()
{
    {
        ankerl::nanobench::Bench b;
        b.title("Fibonacci Search")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        fibonacci_search_benchmark<double>(&b, "fibonacci_search_double");
        fibonacci_search_benchmark<float>(&b, "fibonacci_search_float");
        gen("fibonacci_search.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }
    {
        ankerl::nanobench::Bench b;
        b.title("Ordinary Differential Equations")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        ode_benchmark<double>(&b, "ode_rk4_double");
        ode_benchmark<float>(&b, "ode_rk4_float");
        gen("ode.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }
    {
        ankerl::nanobench::Bench b;
        b.title("Cubic Spline")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        spline_benchmark<std::vector<double>>(&b, "cubic_spline_vector_double");
        spline_benchmark<std::vector<float>>(&b, "cubic_spline_vector_float");
        spline_benchmark<std::array<double,9>>(&b, "cubic_spline_array_double");
        spline_benchmark<std::array<float,9>>(&b, "cubic_spline_array_float");
        gen("cubic_spline.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }
}