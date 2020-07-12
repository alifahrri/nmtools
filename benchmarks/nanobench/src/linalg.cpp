#define ANKERL_NANOBENCH_IMPLEMENT

#include "linalg.hpp"
#include "common.hpp"

int main() {
    ankerl::nanobench::Bench b;
    b.title("Gauss Elimination")
        .warmup(100)
        .epochs(1000)
        .relative(true);
    b.performanceCounters(true);

    gauss_elimination_benchmark<double>(&b, "gauss_elimination_double");
    gauss_elimination_benchmark<float>(&b, "gauss_elimination_float");
    gen("gauss_elimination.html", ankerl::nanobench::templates::htmlBoxplot(), b);
}