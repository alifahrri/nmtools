#define ANKERL_NANOBENCH_IMPLEMENT

#include "linalg.hpp"
#include "common.hpp"

#include "xsimd/xsimd.hpp"

#include <array>
#include <vector>
#include <valarray>
#include <experimental/simd>

using std::array;
using std::vector;
using std::valarray;
using std::experimental::native_simd;

namespace xs = xsimd;

namespace xsimd {
    template <typename T, size_t s>
    constexpr auto size(const xsimd::batch<T,s>& batch)
    {
        return s;
    }
}

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

    auto Ad3x3_val = valarray<valarray<double>>{
        valarray<double>{3.0, -0.1, -0.2},
        valarray<double>{0.1,  7.0, -0.3},
        valarray<double>{0.3, -0.2, 10.0},
    };

    auto Af3x3_val = valarray<valarray<float>>{
        valarray<float>{3.0, -0.1, -0.2},
        valarray<float>{0.1,  7.0, -0.3},
        valarray<float>{0.3, -0.2, 10.0},
    };

    auto Ad3x3_simd = array<array<native_simd<double>,3>,3>{
        array<native_simd<double>,3>{3.0, -0.1, -0.2},
        array<native_simd<double>,3>{0.1,  7.0, -0.3},
        array<native_simd<double>,3>{0.3, -0.2, 10.0},
    };

    auto Af3x3_simd = array<array<native_simd<float>,3>,3>{
        array<native_simd<float>,3>{3.0f, -0.1f, -0.2f},
        array<native_simd<float>,3>{0.1f,  7.0f, -0.3f},
        array<native_simd<float>,3>{0.3f, -0.2f, 10.0f},
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
        // lu_decomposition_benchmark(&b, "lu_decomposition_array_double_simd", Ad3x3_simd);
        // lu_decomposition_benchmark(&b, "lu_decomposition_array_float_simd", Af3x3_simd);
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
        // inverse_benchmark(&b, "inverse_array_double_simd", Ad3x3_simd);
        // inverse_benchmark(&b, "inverse_array_float_simd", Af3x3_simd);
        inverse_benchmark(&b, "inverse_vector_double", Vd3x3);
        inverse_benchmark(&b, "inverse_vector_float", Vf3x3);
        gen("inverse_3x3.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto Ad3x3 = array<array<double,3>,3>{
            array<double,3>{ 6,  15,  55},
            array<double,3>{15,  55, 225},
            array<double,3>{55, 225, 979},
        };

        auto Af3x3 = array<array<float,3>,3>{
            array<float,3>{ 6,  15,  55},
            array<float,3>{15,  55, 225},
            array<float,3>{55, 225, 979},
        };

        auto Ad3x3_simd = array<array<native_simd<double>,3>,3>{
            array<native_simd<double>,3>{ 6,  15,  55},
            array<native_simd<double>,3>{15,  55, 225},
            array<native_simd<double>,3>{55, 225, 979},
        };

        auto Af3x3_simd = array<array<native_simd<float>,3>,3>{
            array<native_simd<float>,3>{ 6,  15,  55},
            array<native_simd<float>,3>{15,  55, 225},
            array<native_simd<float>,3>{55, 225, 979},
        };

        auto Vd3x3 = vector<vector<double>>{
            vector<double>{ 6,  15,  55},
            vector<double>{15,  55, 225},
            vector<double>{55, 225, 979},
        };

        auto Vf3x3 = vector<vector<float>>{
            vector<float>{ 6,  15,  55},
            vector<float>{15,  55, 225},
            vector<float>{55, 225, 979},
        };

        double Rd3x3[3][3] = {
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        };

        float Rf3x3[3][3] = {
            { 6,  15,  55},
            {15,  55, 225},
            {55, 225, 979},
        };

        ankerl::nanobench::Bench b;
        b.title("Cholesky Decomposition (3x3)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_double", Ad3x3);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_float", Af3x3);
        // cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_double_simd", Ad3x3_simd);
        // cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_float_simd", Af3x3_simd);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_valarray_double", Ad3x3_val);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_valarray_float", Af3x3_val);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_vector_double", Vd3x3);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_vector_float", Vf3x3);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_raw_double", Rd3x3);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_raw_float", Rf3x3);
        gen("cholesky_decomposition_3x3.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto Ad4x4 = std::array<std::array<double,4>,4>{
            std::array<double,4>{ 1,  4,  9, 16},
            std::array<double,4>{ 4,  9, 16, 25},
            std::array<double,4>{ 9, 16, 25, 36},
            std::array<double,4>{16, 25, 36, 49},
        };
        auto Af4x4 = std::array<std::array<float,4>,4>{
            std::array<float,4>{ 1,  4,  9, 16},
            std::array<float,4>{ 4,  9, 16, 25},
            std::array<float,4>{ 9, 16, 25, 36},
            std::array<float,4>{16, 25, 36, 49},
        };
        auto Ad4x4_simd = std::array<std::array<native_simd<double>,4>,4>{
            std::array<native_simd<double>,4>{ 1,  4,  9, 16},
            std::array<native_simd<double>,4>{ 4,  9, 16, 25},
            std::array<native_simd<double>,4>{ 9, 16, 25, 36},
            std::array<native_simd<double>,4>{16, 25, 36, 49},
        };
        auto Af4x4_simd = std::array<std::array<native_simd<float>,4>,4>{
            std::array<native_simd<float>,4>{ 1,  4,  9, 16},
            std::array<native_simd<float>,4>{ 4,  9, 16, 25},
            std::array<native_simd<float>,4>{ 9, 16, 25, 36},
            std::array<native_simd<float>,4>{16, 25, 36, 49},
        };
        double Rd4x4[4][4] = {
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        };
        float Rf4x4[4][4] = {
            { 1,  4,  9, 16},
            { 4,  9, 16, 25},
            { 9, 16, 25, 36},
            {16, 25, 36, 49},
        };
        auto Vf4x4 = std::vector<std::vector<float>>{
            std::vector<float>{ 1,  4,  9, 16},
            std::vector<float>{ 4,  9, 16, 25},
            std::vector<float>{ 9, 16, 25, 36},
            std::vector<float>{16, 25, 36, 49},
        };
        auto Vd4x4 = std::vector<std::vector<double>>{
            std::vector<double>{ 1,  4,  9, 16},
            std::vector<double>{ 4,  9, 16, 25},
            std::vector<double>{ 9, 16, 25, 36},
            std::vector<double>{16, 25, 36, 49},
        };

        using xbatchd4 = xs::batch<double,4>;
        using xbatchf4 = xs::batch<float,4>;

        auto Ad4x4_xsimd = array<xbatchd4,4>{
            xbatchd4( 1,  4,  9, 16),
            xbatchd4( 4,  9, 16, 25),
            xbatchd4( 9, 16, 25, 36),
            xbatchd4(16, 25, 36, 49),
        };

        auto Af4x4_xsimd = array<xbatchf4,4>{
            xbatchf4( 1,  4,  9, 16),
            xbatchf4( 4,  9, 16, 25),
            xbatchf4( 9, 16, 25, 36),
            xbatchf4(16, 25, 36, 49),
        };

        ankerl::nanobench::Bench b;
        b.title("Cholesky Decomposition (4x4)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_double", Ad4x4);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_float", Af4x4);
        // cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_double_simd", Ad4x4_simd);
        // cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_float_simd", Af4x4_simd);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_double_xsimd", Ad4x4_xsimd);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_float_xsimd", Af4x4_xsimd);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_vector_double", Vd4x4);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_vector_float", Vf4x4);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_raw_double", Rd4x4);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_raw_float", Rf4x4);

        gen("cholesky_decomposition_4x4.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto Ad5x5 = std::array<std::array<double,5>,5>{
            std::array<double,5>{ 1,  4,  9, 16, 25},
            std::array<double,5>{ 4,  9, 16, 25, 36},
            std::array<double,5>{ 9, 16, 25, 36, 49},
            std::array<double,5>{16, 25, 36, 49, 64},
            std::array<double,5>{25, 36, 49, 64, 81},
        };
        auto Af5x5 = std::array<std::array<float,5>,5>{
            std::array<float,5>{ 1,  4,  9, 16, 25},
            std::array<float,5>{ 4,  9, 16, 25, 36},
            std::array<float,5>{ 9, 16, 25, 36, 49},
            std::array<float,5>{16, 25, 36, 49, 64},
            std::array<float,5>{25, 36, 49, 64, 81},
        };
        auto Vd5x5 = std::vector<std::vector<double>>{
            std::vector<double>{ 1,  4,  9, 16, 25},
            std::vector<double>{ 4,  9, 16, 25, 36},
            std::vector<double>{ 9, 16, 25, 36, 49},
            std::vector<double>{16, 25, 36, 49, 64},
            std::vector<double>{25, 36, 49, 64, 81},
        };
        auto Vf5x5 = std::vector<std::vector<float>>{
            std::vector<float>{ 1,  4,  9, 16, 25},
            std::vector<float>{ 4,  9, 16, 25, 36},
            std::vector<float>{ 9, 16, 25, 36, 49},
            std::vector<float>{16, 25, 36, 49, 64},
            std::vector<float>{25, 36, 49, 64, 81},
        };
        auto Ad5x5_simd = std::array<std::array<native_simd<double>,5>,5>{
            std::array<native_simd<double>,5>{ 1,  4,  9, 16, 25},
            std::array<native_simd<double>,5>{ 4,  9, 16, 25, 36},
            std::array<native_simd<double>,5>{ 9, 16, 25, 36, 49},
            std::array<native_simd<double>,5>{16, 25, 36, 49, 64},
            std::array<native_simd<double>,5>{25, 36, 49, 64, 81},
        };
        auto Af5x5_simd = std::array<std::array<native_simd<float>,5>,5>{
            std::array<native_simd<float>,5>{ 1,  4,  9, 16, 25},
            std::array<native_simd<float>,5>{ 4,  9, 16, 25, 36},
            std::array<native_simd<float>,5>{ 9, 16, 25, 36, 49},
            std::array<native_simd<float>,5>{16, 25, 36, 49, 64},
            std::array<native_simd<float>,5>{25, 36, 49, 64, 81},
        };
        double Rd5x5[5][5] = {
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        };
        float Rf5x5[5][5] = {
            { 1,  4,  9, 16, 25},
            { 4,  9, 16, 25, 36},
            { 9, 16, 25, 36, 49},
            {16, 25, 36, 49, 64},
            {25, 36, 49, 64, 81},
        };
        ankerl::nanobench::Bench b;
        b.title("Cholesky Decomposition (5x5)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_double", Ad5x5);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_float", Af5x5);
        // cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_double_simd", Ad5x5_simd);
        // cholesky_decomposition_benchmark(&b, "cholesky_decomposition_array_float_simd", Af5x5_simd);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_vector_double", Vd5x5);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_vector_float", Vf5x5);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_raw_double", Rd5x5);
        cholesky_decomposition_benchmark(&b, "cholesky_decomposition_raw_float", Rf5x5);

        gen("cholesky_decomposition_5x5.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        /* basic type */
        auto ae_d4 = std::array<double,4>{0, -1, -1, -1};
        auto af_d4 = std::array<double,4>{2.04, 2.04, 2.04, 2.04};
        auto ag_d4 = std::array<double,4>{-1, -1, -1, 0};
        auto ab_d4 = std::array<double,4>{40.8, 0.8, 0.8, 200.8};

        auto ve_d4 = std::vector<double>{0, -1, -1, -1};
        auto vf_d4 = std::vector<double>{2.04, 2.04, 2.04, 2.04};
        auto vg_d4 = std::vector<double>{-1, -1, -1, 0};
        auto vb_d4 = std::vector<double>{40.8, 0.8, 0.8, 200.8};

        auto ae_f4 = std::array<float,4>{0, -1, -1, -1};
        auto af_f4 = std::array<float,4>{2.04, 2.04, 2.04, 2.04};
        auto ag_f4 = std::array<float,4>{-1, -1, -1, 0};
        auto ab_f4 = std::array<float,4>{40.8, 0.8, 0.8, 200.8};

        auto ve_f4 = std::vector<float>{0, -1, -1, -1};
        auto vf_f4 = std::vector<float>{2.04, 2.04, 2.04, 2.04};
        auto vg_f4 = std::vector<float>{-1, -1, -1, 0};
        auto vb_f4 = std::vector<float>{40.8, 0.8, 0.8, 200.8};

        double re_d4[4] = {0, -1, -1, -1};
        double rf_d4[4] = {2.04, 2.04, 2.04, 2.04};
        double rg_d4[4] = {-1, -1, -1, 0};
        double rb_d4[4] = {40.8, 0.8, 0.8, 200.8};

        float re_f4[4] = {0, -1, -1, -1};
        float rf_f4[4] = {2.04, 2.04, 2.04, 2.04};
        float rg_f4[4] = {-1, -1, -1, 0};
        float rb_f4[4] = {40.8, 0.8, 0.8, 200.8};

        /* simd type */
        auto ae_d4_simd = std::array<native_simd<double>,4>{0, -1, -1, -1};
        auto af_d4_simd = std::array<native_simd<double>,4>{2.04, 2.04, 2.04, 2.04};
        auto ag_d4_simd = std::array<native_simd<double>,4>{-1, -1, -1, 0};
        auto ab_d4_simd = std::array<native_simd<double>,4>{40.8, 0.8, 0.8, 200.8};

        auto ae_d4_xsimd = xs::batch<double,4>{0, -1, -1, -1};
        auto af_d4_xsimd = xs::batch<double,4>{2.04, 2.04, 2.04, 2.04};
        auto ag_d4_xsimd = xs::batch<double,4>{-1, -1, -1, 0};
        auto ab_d4_xsimd = xs::batch<double,4>{40.8, 0.8, 0.8, 200.8};

        auto ae_f4_simd = std::array<native_simd<float>,4>{0.f, -1.f, -1.f, -1.f};
        auto af_f4_simd = std::array<native_simd<float>,4>{2.04f, 2.04f, 2.04f, 2.04f};
        auto ag_f4_simd = std::array<native_simd<float>,4>{-1.f, -1.f, -1.f, 0.f};
        auto ab_f4_simd = std::array<native_simd<float>,4>{40.8f, 0.8f, 0.8f, 200.8f};

        auto ae_f4_xsimd = xs::batch<float,4>(0.f, -1.f, -1.f, -1.f);
        auto af_f4_xsimd = xs::batch<float,4>(2.04f, 2.04f, 2.04f, 2.04f);
        auto ag_f4_xsimd = xs::batch<float,4>(-1.f, -1.f, -1.f, 0.f);
        auto ab_f4_xsimd = xs::batch<float,4>(40.8f, 0.8f, 0.8f, 200.8f);

        ankerl::nanobench::Bench b;
        b.title("Tridiagonal Elimination (4x4)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        tridiagonal_elimination_benchmark(&b, "tridiagonal_array_double", ae_d4, af_d4, ag_d4, ab_d4);
        tridiagonal_elimination_benchmark(&b, "tridiagonal_array_double", ae_f4, af_f4, ag_f4, ab_f4);
        // tridiagonal_elimination_benchmark(&b, "tridiagonal_array_double_simd", ae_d4_simd, af_d4_simd, ag_d4_simd, ab_d4_simd);
        // tridiagonal_elimination_benchmark(&b, "tridiagonal_array_double_simd", ae_f4_simd, af_f4_simd, ag_f4_simd, ab_f4_simd);
        tridiagonal_elimination_benchmark(&b, "tridiagonal_array_double_xsimd", ae_d4_xsimd, af_d4_xsimd, ag_d4_xsimd, ab_d4_xsimd);
        tridiagonal_elimination_benchmark(&b, "tridiagonal_array_double_xsimd", ae_f4_xsimd, af_f4_xsimd, ag_f4_xsimd, ab_f4_xsimd);
        tridiagonal_elimination_benchmark(&b, "tridiagonal_vector_double", ve_d4, vf_d4, vg_d4, vb_d4);
        tridiagonal_elimination_benchmark(&b, "tridiagonal_vector_double", ve_f4, vf_f4, vg_f4, vb_f4);
        tridiagonal_elimination_benchmark(&b, "tridiagonal_raw_double", re_d4, rf_d4, rg_d4, rb_d4);
        tridiagonal_elimination_benchmark(&b, "tridiagonal_raw_double", re_f4, rf_f4, rg_f4, rb_f4);

        gen("tridiagonal_elimination_4x4.html", ankerl::nanobench::templates::htmlBoxplot(), b);
    }
}