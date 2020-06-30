#define ANKERL_NANOBENCH_IMPLEMENT

#include "spline.hpp"

int main() {
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
}