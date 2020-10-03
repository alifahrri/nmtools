#include "ode.hpp"

int main() {
    ankerl::nanobench::Bench b;
    b.title("Ordinary Differential Equations")
        .warmup(100)
        .epochs(1000)
        .relative(true);
    b.performanceCounters(true);

    ode_benchmark<double>(&b, "ode_rk4_double");
    ode_benchmark<float>(&b, "ode_rk4_float");
}