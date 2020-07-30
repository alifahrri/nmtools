#define ANKERL_NANOBENCH_IMPLEMENT

#include "curvefit.hpp"

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

int main() {
    {
        ankerl::nanobench::Bench b;
        b.title("Linear Regression (8)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        auto axd = array<double,8>{1,2,3,4,5,6,7,8};
        auto ayd = array<double,8>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        auto vxd = vector<double>{1,2,3,4,5,6,7,8};
        auto vyd = vector<double>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        double rxd[8] = {1,2,3,4,5,6,7,6.3};
        double ryd[8] = {0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        auto axf = array<float,8>{1,2,3,4,5,6,7,8};
        auto ayf = array<float,8>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        auto vxf = vector<float>{1,2,3,4,5,6,7,8};
        auto vyf = vector<float>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        float rxf[8] = {1,2,3,4,5,6,7,8};
        float ryf[8] = {0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        auto vaxd = valarray<double>{1,2,3,4,5,6,7,8};
        auto vayd = valarray<double>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        auto vaxf = valarray<float>{1,2,3,4,5,6,7,8};
        auto vayf = valarray<float>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};

        /* simd types */
        auto axd_simd = array<native_simd<double>,8>{1,2,3,4,5,6,7,8};
        auto ayd_simd = array<native_simd<double>,8>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        auto vxd_simd = vector<native_simd<double>>{1,2,3,4,5,6,7,8};
        auto vyd_simd = vector<native_simd<double>>{0.5,2.5,2.0,4.0,3.5,6.0,5.5,6.3};
        auto axf_simd = array<native_simd<float>,8>{1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f};
        auto ayf_simd = array<native_simd<float>,8>{0.5f,2.5f,2.0f,4.0f,3.5f,6.0f,5.5f,6.3f};
        auto vxf_simd = vector<native_simd<float>>{1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f};
        auto vyf_simd = vector<native_simd<float>>{0.5f,2.5f,2.0f,4.0f,3.5f,6.0f,5.5f,6.3f};

        linear_regression_benchmark(&b, "linear_regression_array_double",    axd,   ayd);
        linear_regression_benchmark(&b, "linear_regression_array_float",     axf,   ayf);
        linear_regression_benchmark(&b, "linear_regression_vector_double",   vxd,   vyd);
        linear_regression_benchmark(&b, "linear_regression_vector_float",    vxf,   vyf);
        linear_regression_benchmark(&b, "linear_regression_raw_double",      rxd,   ryd);
        linear_regression_benchmark(&b, "linear_regression_raw_float",       rxf,   ryf);
        linear_regression_benchmark(&b, "linear_regression_valarray_double", vaxd, vayd);
        linear_regression_benchmark(&b, "linear_regression_valarray_float",  vaxf, vayf);
        linear_regression_benchmark(&b, "linear_regression_array_double_simd",    axd_simd,   ayd_simd);
        linear_regression_benchmark(&b, "linear_regression_array_float_simd",     axf_simd,   ayf_simd);
        linear_regression_benchmark(&b, "linear_regression_vector_double_simd",   vxd_simd,   vyd_simd);
        linear_regression_benchmark(&b, "linear_regression_vector_float_simd",    vxf_simd,   vyf_simd);
    }

    {
        ankerl::nanobench::Bench b;
        b.title("Linear Regression (16)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        auto axd = array<double,16>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        auto ayd = array<double,16>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50.,51.};
        auto vxd = vector<double>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        auto vyd = vector<double>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        double rxd[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        double ryd[16] = {10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        auto axf = array<float,16>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        auto ayf = array<float,16>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        auto vxf = vector<float>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        auto vyf = vector<float>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        float rxf[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        float ryf[16] = {10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        auto vaxd = valarray<double>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        auto vayd = valarray<double>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        auto vaxf = valarray<float>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        auto vayf = valarray<float>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};

        /* simd types */
        auto axd_simd = array<native_simd<double>,16>{1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.};
        auto ayd_simd = array<native_simd<double>,16>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        auto vxd_simd = vector<native_simd<double>>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        auto vyd_simd = vector<native_simd<double>>{10.,16.3,23.,27.5,31.,35.6,39.,41.5,42.9,45.,46.,45.5,46.,49.,50,51.};
        auto axf_simd = array<native_simd<float>,16>{1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f,10.f,11.f,12.f,13.f,14.f,15.f,16.f};
        auto ayf_simd = array<native_simd<float>,16>{10.f,16.3f,23.f,27.5f,31.f,35.6f,39.f,41.5f,42.9f,45.f,46.f,45.5f,46.f,49.f,50.f,51.f};
        auto vxf_simd = vector<native_simd<float>>{1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f,10.f,11.f,12.f,13.f,14.f,15.f,16.f};
        auto vyf_simd = vector<native_simd<float>>{10.f,16.3f,23.f,27.5f,31.f,35.6f,39.f,41.5f,42.9f,45.f,46.f,45.5f,46.f,49.f,50.f,51.f};

        linear_regression_benchmark(&b, "linear_regression_array_double",    axd,   ayd);
        linear_regression_benchmark(&b, "linear_regression_array_float",     axf,   ayf);
        linear_regression_benchmark(&b, "linear_regression_vector_double",   vxd,   vyd);
        linear_regression_benchmark(&b, "linear_regression_vector_float",    vxf,   vyf);
        linear_regression_benchmark(&b, "linear_regression_raw_double",      rxd,   ryd);
        linear_regression_benchmark(&b, "linear_regression_raw_float",       rxf,   ryf);
        linear_regression_benchmark(&b, "linear_regression_valarray_double", vaxd, vayd);
        linear_regression_benchmark(&b, "linear_regression_valarray_float",  vaxf, vayf);
        linear_regression_benchmark(&b, "linear_regression_array_double_simd",    axd_simd,   ayd_simd);
        linear_regression_benchmark(&b, "linear_regression_array_float_simd",     axf_simd,   ayf_simd);
        linear_regression_benchmark(&b, "linear_regression_vector_double_simd",   vxd_simd,   vyd_simd);
        linear_regression_benchmark(&b, "linear_regression_vector_float_simd",    vxf_simd,   vyf_simd);
    }

    {
        /* array double */
        auto aad = array<double,6>{ 0.,  2., 2.5, 1., 4.,  7. };
        auto abd = array<double,6>{ 0.,  1.,  2., 3., 6.,  2. };
        auto ayd = array<double,6>{ 5., 10.,  9., 0., 3., 27. };
        /* array float */
        auto aaf = array<float,6>{ 0.,  2., 2.5, 1., 4.,  7. };
        auto abf = array<float,6>{ 0.,  1.,  2., 3., 6.,  2. };
        auto ayf = array<float,6>{ 5., 10.,  9., 0., 3., 27. };
        /* vector double */
        auto vad = vector<double>{ 0.,  2., 2.5, 1., 4.,  7. };
        auto vbd = vector<double>{ 0.,  1.,  2., 3., 6.,  2. };
        auto vyd = vector<double>{ 5., 10.,  9., 0., 3., 27. };
        /* vector float */
        auto vaf = vector<float>{ 0.,  2., 2.5, 1., 4.,  7. };
        auto vbf = vector<float>{ 0.,  1.,  2., 3., 6.,  2. };
        auto vyf = vector<float>{ 5., 10.,  9., 0., 3., 27. };
        /* raw double */
        double rad[6] = { 0.,  2., 2.5, 1., 4.,  7. };
        double rbd[6] = { 0.,  1.,  2., 3., 6.,  2. };
        double ryd[6] = { 5., 10.,  9., 0., 3., 27. };
        /* raw float */
        float raf[6] = { 0.,  2., 2.5, 1., 4.,  7. };
        float rbf[6] = { 0.,  1.,  2., 3., 6.,  2. };
        float ryf[6] = { 5., 10.,  9., 0., 3., 27. };
        /* stdx simd double */
        auto aad_simd = array<native_simd<double>,6>{ 0.,  2., 2.5, 1., 4.,  7. };
        auto abd_simd = array<native_simd<double>,6>{ 0.,  1.,  2., 3., 6.,  2. };
        auto ayd_simd = array<native_simd<double>,6>{ 5., 10.,  9., 0., 3., 27. };
        /* stdx simd float */
        auto aaf_simd = array<native_simd<float>,6>{ 0.f,  2.f, 2.5f, 1.f, 4.f,  7.f };
        auto abf_simd = array<native_simd<float>,6>{ 0.f,  1.f,  2.f, 3.f, 6.f,  2.f };
        auto ayf_simd = array<native_simd<float>,6>{ 5.f, 10.f,  9.f, 0.f, 3.f, 27.f };

        ankerl::nanobench::Bench b;
        b.title("General Linear Least-Square Regression (f(x1,x2),6)")
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);

        least_square_regression_benchmark(&b, "least_square_regression_array_double", ayd, aad, abd);
        least_square_regression_benchmark(&b, "least_square_regression_array_float",  ayf, aaf, abf);

        /* TODO: make these types supported! */
        // least_square_regression_benchmark(&b, "least_square_regression_array_double_simd", ayd_simd, aad_simd, abd_simd);
        // least_square_regression_benchmark(&b, "least_square_regression_array_float_simd",  ayf_simd, aaf_simd, abf_simd);
        // least_square_regression_benchmark(&b, "least_square_regression_vector_double", vyd, vad, vbd);
        // least_square_regression_benchmark(&b, "least_square_regression_vector_float",  vyf, vaf, vbf);
        // least_square_regression_benchmark(&b, "least_square_regression_raw_double", ryd, rad, rbd);
        // least_square_regression_benchmark(&b, "least_square_regression_raw_float",  ryf, raf, rbf);
    }
    {
        /* array double */
        auto axd = array<double,4>{3.0, 4.5, 7.0, 9.0};
        auto ayd = array<double,4>{2.5, 1.0, 2.5, 0.5};
        /* array float */
        auto axf = array<float,4>{3.0, 4.5, 7.0, 9.0};
        auto ayf = array<float,4>{2.5, 1.0, 2.5, 0.5};
        /* vector double */
        auto vxd = vector<double>{3.0, 4.5, 7.0, 9.0};
        auto vyd = vector<double>{2.5, 1.0, 2.5, 0.5};
        /* vector float */
        auto vxf = vector<float>{3.0, 4.5, 7.0, 9.0};
        auto vyf = vector<float>{2.5, 1.0, 2.5, 0.5};
        /* vector double */
        auto vaxd = valarray<double>{3.0, 4.5, 7.0, 9.0};
        auto vayd = valarray<double>{2.5, 1.0, 2.5, 0.5};
        /* vector float */
        auto vaxf = valarray<float>{3.0, 4.5, 7.0, 9.0};
        auto vayf = valarray<float>{2.5, 1.0, 2.5, 0.5};
        /* raw double */
        double rxd[4] = {3.0, 4.5, 7.0, 9.0};
        double ryd[4] = {2.5, 1.0, 2.5, 0.5};
        /* raw float */
        float rxf[4] = {3.0, 4.5, 7.0, 9.0};
        float ryf[4] = {2.5, 1.0, 2.5, 0.5};
        /* array simd double */
        auto axd_simd = array<native_simd<double>,4>{3.0, 4.5, 7.0, 9.0};
        auto ayd_simd = array<native_simd<double>,4>{2.5, 1.0, 2.5, 0.5};
        /* array simd float */
        auto axf_simd = array<native_simd<float>,4>{3.0f, 4.5f, 7.0f, 9.0f};
        auto ayf_simd = array<native_simd<float>,4>{2.5f, 1.0f, 2.5f, 0.5f};

        {
            ankerl::nanobench::Bench b;
            b.title("Cubic Spline Construct (4 intv)")
                .warmup(100)
                .epochs(1000)
                .relative(true);
            b.performanceCounters(true);

            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_array_double", axd, ayd);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_array_float",  axf, ayf);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_array_double_simd", axd_simd, ayd_simd);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_array_float_simd",  axf_simd, ayf_simd);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_vector_double", vxd, vyd);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_vector_float",  vxf, vyf);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_valarray_double", vaxd, vayd);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_valarray_float",  vaxf, vayf);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_raw_double", rxd, ryd);
            cubic_spline_construct_benchmark(&b, "cubic_spline_construct_raw_float",  rxf, ryf);
        }

        {
            auto afd = cvt::cubic_spline(axd, ayd);
            auto aff = cvt::cubic_spline(axf, ayf);
            auto vfd = cvt::cubic_spline(vxd, vyd);
            auto vff = cvt::cubic_spline(vxf, vyf);
            auto vafd = cvt::cubic_spline(vaxd, vayd);
            auto vaff = cvt::cubic_spline(vaxf, vayf);
            auto rfd = cvt::cubic_spline(rxd, ryd);
            auto rff = cvt::cubic_spline(rxf, ryf);
            auto afd_simd = cvt::cubic_spline(axd_simd, ayd_simd);
            auto aff_simd = cvt::cubic_spline(axf_simd, ayf_simd);

            ankerl::nanobench::Bench b;
            b.title("Cubic Spline Eval (4 intv)")
                .warmup(100)
                .epochs(1000)
                .relative(true);
            b.performanceCounters(true);

            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_array_double", afd, axd[1]);
            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_array_float",  aff, axf[1]);
            /* cannot convert operator to 'bool' */
            /* TODO: make this supported */
            // cubic_spline_eval_benchmark(&b, "cubic_spline_eval_array_double", afd_simd, axd_simd[1]);
            // cubic_spline_eval_benchmark(&b, "cubic_spline_eval_array_float",  aff_simd, axf_simd[1]);
            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_vector_double", vfd, vxd[1]);
            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_vector_float",  vff, vxf[1]);
            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_valarray_double", vafd, vaxd[1]);
            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_valarray_float",  vaff, vaxf[1]);
            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_raw_double", rfd, rxd[1]);
            cubic_spline_eval_benchmark(&b, "cubic_spline_eval_raw_float",  rff, rxf[1]);
        }
    }
}