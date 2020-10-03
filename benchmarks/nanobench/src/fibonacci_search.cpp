#include "fibonacci_search.hpp"

int main() {
    ankerl::nanobench::Bench b;
    b.title("Fibonacci Search")
        .warmup(100)
        .epochs(1000)
        .relative(true);
    b.performanceCounters(true);

    fibonacci_search_benchmark<double>(&b, "fibonacci_search_double");
    fibonacci_search_benchmark<float>(&b, "fibonacci_search_float");
}