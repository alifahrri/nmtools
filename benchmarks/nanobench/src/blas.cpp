#define ANKERL_NANOBENCH_IMPLEMENT
/* NOTE: when array implementation available, include first! */
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// TODO: rename to nmtools/bench/blas.hpp or something
#include "blas.hpp"
#include <array>
#include <vector>

namespace nma = nmtools::array;
namespace nmb = nmtools::bench;
using std::array;
using std::vector;

int main()
{
    auto a = array<double,3>{ 1, 2, 3 };
    auto v = vector<double>{ 1, 2, 3 };
    constexpr double r[3] = { 1, 2, 3, };
    auto fv = nma::fixed_vector<double,3>{1, 2, 3};
    auto dv = nma::dynamic_vector<double>{1,2,3};
    auto ma = array<array<double,3>,3> {
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
        array<double,3>{1, 2, 3},
    };
    auto mv = vector<vector<double>> {
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
        vector<double>{1, 2, 3},
    };
    constexpr double mr[3][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    auto fm = nma::fixed_matrix<double,3,3>{
        1, 2, 3,
        1, 2, 3,
        1, 2, 3
    };
    auto dm = nma::dynamic_matrix<double>{
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3}
    };

    auto make_bench = [](std::string title){
        ankerl::nanobench::Bench b;
        b.title(title)
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);
        return b;
    };

    using namespace nmb::nanobench;

    {
        auto b = make_bench("blas::zeros_like(3)");

        zeros_like(&b, a);
        zeros_like(&b, v);
        zeros_like(&b, r);
        zeros_like(&b, fv);
        zeros_like(&b, dv);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::zeros_like(3x3)");

        zeros_like(&b, ma);
        zeros_like(&b, mv);
        zeros_like(&b, mr);
        zeros_like(&b, fm);
        zeros_like(&b, dm);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::clone(3)");
        clone(&b, a);
        clone(&b, v);
        clone(&b, r);
        clone(&b, fv);
        clone(&b, dv);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::clone(3x3)");

        clone(&b, ma);
        clone(&b, mv);
        clone(&b, mr);
        clone(&b, fm);
        clone(&b, dm);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::transpose(3x3)");

        transpose(&b, ma);
        transpose(&b, mv);
        transpose(&b, mr);
        transpose(&b, fm);
        transpose(&b, dm);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::ones_like(3x3)");

        ones_like(&b, ma);
        ones_like(&b, mv);
        ones_like(&b, mr);
        ones_like(&b, fm);
        ones_like(&b, dm);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::vvadd(3x3)");

        vvadd(&b, a, a);
        vvadd(&b, v, v);
        vvadd(&b, r, r);
        vvadd(&b, fv, fv);
        vvadd(&b, dv, dv);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmadd(3x3)");

        mmadd(&b, ma, ma);
        mmadd(&b, mv, mv);
        mmadd(&b, mr, mr);
        mmadd(&b, fm, fm);
        mmadd(&b, dm, dm);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::vsmul(3x3)");

        vsmul(&b, a, 3);
        vsmul(&b, v, 3);
        vsmul(&b, r, 3);
        vsmul(&b, fv, 3);
        vsmul(&b, dv, 3);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::msmul(3x3)");

        msmul(&b, ma, 3);
        msmul(&b, mv, 3);
        msmul(&b, mr, 3);
        msmul(&b, fm, 3);
        msmul(&b, dm, 3);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mvmul(3x3)");

        mvmul(&b, ma, a);
        mvmul(&b, mv, v);
        mvmul(&b, mr, r);
        mvmul(&b, fm, fv);
        mvmul(&b, dm, dv);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmmul(3x3)");

        mmmul(&b, ma, ma);
        mmmul(&b, mv, mv);
        mmmul(&b, mr, mr);
        mmmul(&b, fm, fm);
        mmmul(&b, dm, dm);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::saxpy(3)");

        saxpy(&b, 3, a, a);
        saxpy(&b, 3, v, v);
        saxpy(&b, 3, r, r);
        saxpy(&b, 3, fv, fv);
        saxpy(&b, 3, dv, dv);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::gaxpy(3x3)");

        gaxpy(&b, ma, a, a);
        gaxpy(&b, mv, v, v);
        gaxpy(&b, mr, r, r);
        gaxpy(&b, fm, fv, fv);
        gaxpy(&b, dm, dv, dv);

        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }
}