#define ANKERL_NANOBENCH_IMPLEMENT

#include "linalg.hpp"
#include "common.hpp"

#include <array>
#include <vector>

using std::array;
using std::vector;

int main() 
{
    auto Ad3x3 = array<array<double,3>,3>{
        array<double,3>{3.0, -0.1, -0.2},
        array<double,3>{0.1,  7.0, -0.3},
        array<double,3>{0.3, -0.2, 10.0},
    };

    auto Af3x3 = array<array<float,3>,3>{
        array<float,3>{3.0, -0.1, -0.2},
        array<float,3>{0.1,  7.0, -0.3},
        array<float,3>{0.3, -0.2, 10.0},
    };

    auto Vd3x3 = vector<vector<double>>{
        vector<double>{3.0, -0.1, -0.2},
        vector<double>{0.1,  7.0, -0.3},
        vector<double>{0.3, -0.2, 10.0},
    };

    auto Vf3x3 = vector<vector<float>>{
        vector<float>{3.0, -0.1, -0.2},
        vector<float>{0.1,  7.0, -0.3},
        vector<float>{0.3, -0.2, 10.0},
    };

    {
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

    {
        ankerl::nanobench::Bench b;
        b.title("LU Decomposition (3x3)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        lu_decomposition_benchmark(&b, "lu_decomposition_array_double", Ad3x3);
        lu_decomposition_benchmark(&b, "lu_decomposition_array_float", Af3x3);
        lu_decomposition_benchmark(&b, "lu_decomposition_vector_double", Vd3x3);
        lu_decomposition_benchmark(&b, "lu_decomposition_vector_float", Vf3x3);
        gen("lu_decomposition_3x3.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        ankerl::nanobench::Bench b;
        b.title("Matrix Inverse (3x3)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        inverse_benchmark(&b, "inverse_array_double", Ad3x3);
        inverse_benchmark(&b, "inverse_array_float", Af3x3);
        inverse_benchmark(&b, "inverse_vector_double", Vd3x3);
        inverse_benchmark(&b, "inverse_vector_float", Vf3x3);
        gen("inverse_3x3.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }
}