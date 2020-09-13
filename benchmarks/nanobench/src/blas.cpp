#define ANKERL_NANOBENCH_IMPLEMENT
// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// TODO: rename to nmtools/bench/blas.hpp or something
#include "blas.hpp"
// TODO: rename to nmtools/bench/data.hpp or something
#include "data.hpp"

#include <array>
#include <vector>

namespace nma = nmtools::array;
namespace nmb = nmtools::bench;
using std::array;
using std::vector;

int main()
{
    auto make_bench = [](std::string title){
        ankerl::nanobench::Bench b;
        b.title(title)
            .warmup(100)
            .epochs(1000)
            .relative(true);
        b.performanceCounters(true);
        return b;
    };

    namespace bench = nmtools::bench::nanobench;
    namespace data = nmtools::bench::data;

    {
        auto b = make_bench("blas::zeros_like(3)");
        {
            using namespace data::array;
            bench::zeros_like(&b,vd3);
            bench::zeros_like(&b,vf3);
        }
        {
            using namespace data::raw;
            bench::zeros_like(&b,vd3);
            bench::zeros_like(&b,vf3);
        }
        {
            using namespace data::vector;
            bench::zeros_like(&b,vd3);
            bench::zeros_like(&b,vf3);
        }
        {
            using namespace data::valarray;
            bench::zeros_like(&b,vd3);
            bench::zeros_like(&b,vf3);
        }
        {
            using namespace data::fixed;
            bench::zeros_like(&b,vd3);
            bench::zeros_like(&b,vf3);
        }
        {
            using namespace data::dynamic;
            bench::zeros_like(&b,vd3);
            bench::zeros_like(&b,vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::zeros_like(4)");
        {
            using namespace data::array;
            bench::zeros_like(&b,vd4_e);
            bench::zeros_like(&b,vf4_e);
        }
        {
            using namespace data::raw;
            bench::zeros_like(&b,vd4_e);
            bench::zeros_like(&b,vf4_e);
        }
        {
            using namespace data::vector;
            bench::zeros_like(&b,vd4_e);
            bench::zeros_like(&b,vf4_e);
        }
        {
            using namespace data::valarray;
            bench::zeros_like(&b,vd4_e);
            bench::zeros_like(&b,vf4_e);
        }
        {
            using namespace data::fixed;
            bench::zeros_like(&b,vd4_e);
            bench::zeros_like(&b,vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::zeros_like(&b,vd4_e);
            bench::zeros_like(&b,vf4_e);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::zeros_like(3x3)");
        {
            using namespace data::array;
            bench::zeros_like(&b, Md3x3);
            bench::zeros_like(&b, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::zeros_like(&b, Md3x3);
            bench::zeros_like(&b, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::zeros_like(&b, Md3x3);
            bench::zeros_like(&b, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::zeros_like(&b, Md3x3);
            bench::zeros_like(&b, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::zeros_like(&b, Md3x3);
            bench::zeros_like(&b, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::zeros_like(&b, Md3x3);
            bench::zeros_like(&b, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::zeros_like(4x4)");
        {
            using namespace data::array;
            bench::zeros_like(&b, Md4x4_symm);
            bench::zeros_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::zeros_like(&b, Md4x4_symm);
            bench::zeros_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::zeros_like(&b, Md4x4_symm);
            bench::zeros_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::zeros_like(&b, Md4x4_symm);
            bench::zeros_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::zeros_like(&b, Md4x4_symm);
            bench::zeros_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::zeros_like(&b, Md4x4_symm);
            bench::zeros_like(&b, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::zeros_like(5x5)");
        {
            using namespace data::array;
            bench::zeros_like(&b, Md5x5_symm);
            bench::zeros_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::zeros_like(&b, Md5x5_symm);
            bench::zeros_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::zeros_like(&b, Md5x5_symm);
            bench::zeros_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::zeros_like(&b, Md5x5_symm);
            bench::zeros_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::zeros_like(&b, Md5x5_symm);
            bench::zeros_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::zeros_like(&b, Md5x5_symm);
            bench::zeros_like(&b, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::clone(3)");
        {
            using namespace data::array;
            bench::clone(&b, vd3);
            bench::clone(&b, vf3);
        }
        {
            using namespace data::raw;
            bench::clone(&b, vd3);
            bench::clone(&b, vf3);
        }
        {
            using namespace data::vector;
            bench::clone(&b, vd3);
            bench::clone(&b, vf3);
        }
        {
            using namespace data::valarray;
            bench::clone(&b, vd3);
            bench::clone(&b, vf3);
        }
        {
            using namespace data::fixed;
            bench::clone(&b, vd3);
            bench::clone(&b, vf3);
        }
        {
            using namespace data::dynamic;
            bench::clone(&b, vd3);
            bench::clone(&b, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::clone(4)");
        {
            using namespace data::array;
            bench::clone(&b, vd4_e);
            bench::clone(&b, vf4_e);
        }
        {
            using namespace data::raw;
            bench::clone(&b, vd4_e);
            bench::clone(&b, vf4_e);
        }
        {
            using namespace data::vector;
            bench::clone(&b, vd4_e);
            bench::clone(&b, vf4_e);
        }
        {
            using namespace data::valarray;
            bench::clone(&b, vd4_e);
            bench::clone(&b, vf4_e);
        }
        {
            using namespace data::fixed;
            bench::clone(&b, vd4_e);
            bench::clone(&b, vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::clone(&b, vd4_e);
            bench::clone(&b, vf4_e);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::clone(3x3)");
        {
            using namespace data::array;
            bench::clone(&b, Md3x3);
            bench::clone(&b, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::clone(&b, Md3x3);
            bench::clone(&b, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::clone(&b, Md3x3);
            bench::clone(&b, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::clone(&b, Md3x3);
            bench::clone(&b, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::clone(&b, Md3x3);
            bench::clone(&b, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::clone(&b, Md3x3);
            bench::clone(&b, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::clone(4x4)");
        {
            using namespace data::array;
            bench::clone(&b, Md4x4_symm);
            bench::clone(&b, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::clone(&b, Md4x4_symm);
            bench::clone(&b, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::clone(&b, Md4x4_symm);
            bench::clone(&b, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::clone(&b, Md4x4_symm);
            bench::clone(&b, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::clone(&b, Md4x4_symm);
            bench::clone(&b, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::clone(&b, Md4x4_symm);
            bench::clone(&b, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::clone(5x5)");
        {
            using namespace data::array;
            bench::clone(&b, Md5x5_symm);
            bench::clone(&b, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::clone(&b, Md5x5_symm);
            bench::clone(&b, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::clone(&b, Md5x5_symm);
            bench::clone(&b, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::clone(&b, Md5x5_symm);
            bench::clone(&b, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::clone(&b, Md5x5_symm);
            bench::clone(&b, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::clone(&b, Md5x5_symm);
            bench::clone(&b, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::transpose(3x3)");
        {
            using namespace data::array;
            bench::transpose(&b, Md3x3);
            bench::transpose(&b, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::transpose(&b, Md3x3);
            bench::transpose(&b, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::transpose(&b, Md3x3);
            bench::transpose(&b, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::transpose(&b, Md3x3);
            bench::transpose(&b, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::transpose(&b, Md3x3);
            bench::transpose(&b, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::transpose(&b, Md3x3);
            bench::transpose(&b, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::transpose(4x4)");
        {
            using namespace data::array;
            bench::transpose(&b, Md4x4_symm);
            bench::transpose(&b, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::transpose(&b, Md4x4_symm);
            bench::transpose(&b, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::transpose(&b, Md4x4_symm);
            bench::transpose(&b, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::transpose(&b, Md4x4_symm);
            bench::transpose(&b, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::transpose(&b, Md4x4_symm);
            bench::transpose(&b, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::transpose(&b, Md4x4_symm);
            bench::transpose(&b, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::transpose(5x5)");
        {
            using namespace data::array;
            bench::transpose(&b, Md5x5_symm);
            bench::transpose(&b, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::transpose(&b, Md5x5_symm);
            bench::transpose(&b, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::transpose(&b, Md5x5_symm);
            bench::transpose(&b, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::transpose(&b, Md5x5_symm);
            bench::transpose(&b, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::transpose(&b, Md5x5_symm);
            bench::transpose(&b, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::transpose(&b, Md5x5_symm);
            bench::transpose(&b, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::ones_like(3x3)");
        {
            using namespace data::array;
            bench::ones_like(&b, Md3x3);
            bench::ones_like(&b, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::ones_like(&b, Md3x3);
            bench::ones_like(&b, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::ones_like(&b, Md3x3);
            bench::ones_like(&b, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::ones_like(&b, Md3x3);
            bench::ones_like(&b, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::ones_like(&b, Md3x3);
            bench::ones_like(&b, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::ones_like(&b, Md3x3);
            bench::ones_like(&b, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::ones_like(4x4)");
        {
            using namespace data::array;
            bench::ones_like(&b, Md4x4_symm);
            bench::ones_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::ones_like(&b, Md4x4_symm);
            bench::ones_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::ones_like(&b, Md4x4_symm);
            bench::ones_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::ones_like(&b, Md4x4_symm);
            bench::ones_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::ones_like(&b, Md4x4_symm);
            bench::ones_like(&b, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::ones_like(&b, Md4x4_symm);
            bench::ones_like(&b, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::ones_like(5x5)");
        {
            using namespace data::array;
            bench::ones_like(&b, Md5x5_symm);
            bench::ones_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::ones_like(&b, Md5x5_symm);
            bench::ones_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::ones_like(&b, Md5x5_symm);
            bench::ones_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::ones_like(&b, Md5x5_symm);
            bench::ones_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::ones_like(&b, Md5x5_symm);
            bench::ones_like(&b, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::ones_like(&b, Md5x5_symm);
            bench::ones_like(&b, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::vvadd(3x3,3x3)");
        {
            using namespace data::array;
            bench::vvadd(&b, vd3, vd3);
            bench::vvadd(&b, vf3, vf3);
        }
        {
            using namespace data::raw;
            bench::vvadd(&b, vd3, vd3);
            bench::vvadd(&b, vf3, vf3);
        }
        {
            using namespace data::vector;
            bench::vvadd(&b, vd3, vd3);
            bench::vvadd(&b, vf3, vf3);
        }
        {
            using namespace data::valarray;
            bench::vvadd(&b, vd3, vd3);
            bench::vvadd(&b, vf3, vf3);
        }
        {
            using namespace data::fixed;
            bench::vvadd(&b, vd3, vd3);
            bench::vvadd(&b, vf3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::vvadd(&b, vd3, vd3);
            bench::vvadd(&b, vf3, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::vvadd(4x4,4x4)");
        {
            using namespace data::array;
            bench::vvadd(&b, vd4_e, vd4_e);
            bench::vvadd(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::raw;
            bench::vvadd(&b, vd4_e, vd4_e);
            bench::vvadd(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::vector;
            bench::vvadd(&b, vd4_e, vd4_e);
            bench::vvadd(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::valarray;
            bench::vvadd(&b, vd4_e, vd4_e);
            bench::vvadd(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::fixed;
            bench::vvadd(&b, vd4_e, vd4_e);
            bench::vvadd(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::vvadd(&b, vd4_e, vd4_e);
            bench::vvadd(&b, vf4_e, vf4_e);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmadd(3x3,3x3)");
        {
            using namespace data::array;
            bench::mmadd(&b, Md3x3, Md3x3);
            bench::mmadd(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::mmadd(&b, Md3x3, Md3x3);
            bench::mmadd(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::mmadd(&b, Md3x3, Md3x3);
            bench::mmadd(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::mmadd(&b, Md3x3, Md3x3);
            bench::mmadd(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::mmadd(&b, Md3x3, Md3x3);
            bench::mmadd(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::mmadd(&b, Md3x3, Md3x3);
            bench::mmadd(&b, Mf3x3, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmadd(4x4,4x4)");
        {
            using namespace data::array;
            bench::mmadd(&b, Md4x4_symm, Md4x4_symm);
            bench::mmadd(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::mmadd(&b, Md4x4_symm, Md4x4_symm);
            bench::mmadd(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::mmadd(&b, Md4x4_symm, Md4x4_symm);
            bench::mmadd(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::mmadd(&b, Md4x4_symm, Md4x4_symm);
            bench::mmadd(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::mmadd(&b, Md4x4_symm, Md4x4_symm);
            bench::mmadd(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::mmadd(&b, Md4x4_symm, Md4x4_symm);
            bench::mmadd(&b, Mf4x4_symm, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmadd(5x5,5x5)");
        {
            using namespace data::array;
            bench::mmadd(&b, Md5x5_symm, Md5x5_symm);
            bench::mmadd(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::mmadd(&b, Md5x5_symm, Md5x5_symm);
            bench::mmadd(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::mmadd(&b, Md5x5_symm, Md5x5_symm);
            bench::mmadd(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::mmadd(&b, Md5x5_symm, Md5x5_symm);
            bench::mmadd(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::mmadd(&b, Md5x5_symm, Md5x5_symm);
            bench::mmadd(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::mmadd(&b, Md5x5_symm, Md5x5_symm);
            bench::mmadd(&b, Mf5x5_symm, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::vsmul(3x3)");
        {
            using namespace data::array;
            bench::vsmul(&b, vd3, 3.);
            bench::vsmul(&b, vf3, 3.f);
        }
        {
            using namespace data::raw;
            bench::vsmul(&b, vd3, 3.);
            bench::vsmul(&b, vf3, 3.f);
        }
        {
            using namespace data::vector;
            bench::vsmul(&b, vd3, 3.);
            bench::vsmul(&b, vf3, 3.f);
        }
        {
            using namespace data::valarray;
            bench::vsmul(&b, vd3, 3.);
            bench::vsmul(&b, vf3, 3.f);
        }
        {
            using namespace data::fixed;
            bench::vsmul(&b, vd3, 3.);
            bench::vsmul(&b, vf3, 3.f);
        }
        {
            using namespace data::dynamic;
            bench::vsmul(&b, vd3, 3.);
            bench::vsmul(&b, vf3, 3.f);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::vsmul(4x4)");
        {
            using namespace data::array;
            bench::vsmul(&b, vd4_e, 3.);
            bench::vsmul(&b, vf4_e, 3.f);
        }
        {
            using namespace data::raw;
            bench::vsmul(&b, vd4_e, 3.);
            bench::vsmul(&b, vf4_e, 3.f);
        }
        {
            using namespace data::vector;
            bench::vsmul(&b, vd4_e, 3.);
            bench::vsmul(&b, vf4_e, 3.f);
        }
        {
            using namespace data::valarray;
            bench::vsmul(&b, vd4_e, 3.);
            bench::vsmul(&b, vf4_e, 3.f);
        }
        {
            using namespace data::fixed;
            bench::vsmul(&b, vd4_e, 3.);
            bench::vsmul(&b, vf4_e, 3.f);
        }
        {
            using namespace data::dynamic;
            bench::vsmul(&b, vd4_e, 3.);
            bench::vsmul(&b, vf4_e, 3.f);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::msmul(3x3)");
        {
            using namespace data::array;
            bench::msmul(&b, Md3x3, 3.);
            bench::msmul(&b, Mf3x3, 3.f);
        }
        {
            using namespace data::raw;
            bench::msmul(&b, Md3x3, 3.);
            bench::msmul(&b, Mf3x3, 3.f);
        }
        {
            using namespace data::vector;
            bench::msmul(&b, Md3x3, 3.);
            bench::msmul(&b, Mf3x3, 3.f);
        }
        {
            using namespace data::valarray;
            bench::msmul(&b, Md3x3, 3.);
            bench::msmul(&b, Mf3x3, 3.f);
        }
        {
            using namespace data::fixed;
            bench::msmul(&b, Md3x3, 3.);
            bench::msmul(&b, Mf3x3, 3.f);
        }
        {
            using namespace data::dynamic;
            bench::msmul(&b, Md3x3, 3.);
            bench::msmul(&b, Mf3x3, 3.f);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::msmul(4x4)");
        {
            using namespace data::array;
            bench::msmul(&b, Md4x4_symm, 3.);
            bench::msmul(&b, Mf4x4_symm, 3.f);
        }
        {
            using namespace data::raw;
            bench::msmul(&b, Md4x4_symm, 3.);
            bench::msmul(&b, Mf4x4_symm, 3.f);
        }
        {
            using namespace data::vector;
            bench::msmul(&b, Md4x4_symm, 3.);
            bench::msmul(&b, Mf4x4_symm, 3.f);
        }
        {
            using namespace data::valarray;
            bench::msmul(&b, Md4x4_symm, 3.);
            bench::msmul(&b, Mf4x4_symm, 3.f);
        }
        {
            using namespace data::fixed;
            bench::msmul(&b, Md4x4_symm, 3.);
            bench::msmul(&b, Mf4x4_symm, 3.f);
        }
        {
            using namespace data::dynamic;
            bench::msmul(&b, Md4x4_symm, 3.);
            bench::msmul(&b, Mf4x4_symm, 3.f);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::msmul(5x5)");
        {
            using namespace data::array;
            bench::msmul(&b, Md5x5_symm, 3.);
            bench::msmul(&b, Mf5x5_symm, 3.f);
        }
        {
            using namespace data::raw;
            bench::msmul(&b, Md5x5_symm, 3.);
            bench::msmul(&b, Mf5x5_symm, 3.f);
        }
        {
            using namespace data::vector;
            bench::msmul(&b, Md5x5_symm, 3.);
            bench::msmul(&b, Mf5x5_symm, 3.f);
        }
        {
            using namespace data::valarray;
            bench::msmul(&b, Md5x5_symm, 3.);
            bench::msmul(&b, Mf5x5_symm, 3.f);
        }
        {
            using namespace data::fixed;
            bench::msmul(&b, Md5x5_symm, 3.);
            bench::msmul(&b, Mf5x5_symm, 3.f);
        }
        {
            using namespace data::dynamic;
            bench::msmul(&b, Md5x5_symm, 3.);
            bench::msmul(&b, Mf5x5_symm, 3.f);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mvmul(3x3,3)");
        {
            using namespace data::array;
            bench::mvmul(&b, Md3x3, vd3);
            bench::mvmul(&b, Mf3x3, vf3);
        }
        {
            using namespace data::raw;
            bench::mvmul(&b, Md3x3, vd3);
            bench::mvmul(&b, Mf3x3, vf3);
        }
        {
            using namespace data::vector;
            bench::mvmul(&b, Md3x3, vd3);
            bench::mvmul(&b, Mf3x3, vf3);
        }
        {
            using namespace data::valarray;
            bench::mvmul(&b, Md3x3, vd3);
            bench::mvmul(&b, Mf3x3, vf3);
        }
        {
            using namespace data::fixed;
            bench::mvmul(&b, Md3x3, vd3);
            bench::mvmul(&b, Mf3x3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::mvmul(&b, Md3x3, vd3);
            bench::mvmul(&b, Mf3x3, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mvmul(4x4,4)");
        {
            using namespace data::array;
            bench::mvmul(&b, Md4x4_symm, vd4_e);
            bench::mvmul(&b, Mf4x4_symm, vf4_e);
        }
        {
            using namespace data::raw;
            bench::mvmul(&b, Md4x4_symm, vd4_e);
            bench::mvmul(&b, Mf4x4_symm, vf4_e);
        }
        {
            using namespace data::vector;
            bench::mvmul(&b, Md4x4_symm, vd4_e);
            bench::mvmul(&b, Mf4x4_symm, vf4_e);
        }
        {
            using namespace data::valarray;
            bench::mvmul(&b, Md4x4_symm, vd4_e);
            bench::mvmul(&b, Mf4x4_symm, vf4_e);
        }
        {
            using namespace data::fixed;
            bench::mvmul(&b, Md4x4_symm, vd4_e);
            bench::mvmul(&b, Mf4x4_symm, vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::mvmul(&b, Md4x4_symm, vd4_e);
            bench::mvmul(&b, Mf4x4_symm, vf4_e);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmmul(3x3,3x3)");
        {
            using namespace data::array;
            bench::mmmul(&b, Md3x3, Md3x3);
            bench::mmmul(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::mmmul(&b, Md3x3, Md3x3);
            bench::mmmul(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::mmmul(&b, Md3x3, Md3x3);
            bench::mmmul(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::mmmul(&b, Md3x3, Md3x3);
            bench::mmmul(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::mmmul(&b, Md3x3, Md3x3);
            bench::mmmul(&b, Mf3x3, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::mmmul(&b, Md3x3, Md3x3);
            bench::mmmul(&b, Mf3x3, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmmul(4x4,4x4)");
        {
            using namespace data::array;
            bench::mmmul(&b, Md4x4_symm, Md4x4_symm);
            bench::mmmul(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::mmmul(&b, Md4x4_symm, Md4x4_symm);
            bench::mmmul(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::mmmul(&b, Md4x4_symm, Md4x4_symm);
            bench::mmmul(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::mmmul(&b, Md4x4_symm, Md4x4_symm);
            bench::mmmul(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::mmmul(&b, Md4x4_symm, Md4x4_symm);
            bench::mmmul(&b, Mf4x4_symm, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::mmmul(&b, Md4x4_symm, Md4x4_symm);
            bench::mmmul(&b, Mf4x4_symm, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::mmmul(5x5,5x5)");
        {
            using namespace data::array;
            bench::mmmul(&b, Md5x5_symm, Md5x5_symm);
            bench::mmmul(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::mmmul(&b, Md5x5_symm, Md5x5_symm);
            bench::mmmul(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::mmmul(&b, Md5x5_symm, Md5x5_symm);
            bench::mmmul(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::mmmul(&b, Md5x5_symm, Md5x5_symm);
            bench::mmmul(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::mmmul(&b, Md5x5_symm, Md5x5_symm);
            bench::mmmul(&b, Mf5x5_symm, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::mmmul(&b, Md5x5_symm, Md5x5_symm);
            bench::mmmul(&b, Mf5x5_symm, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::dot(3,3)");
        {
            using namespace data::array;
            bench::dot(&b, vd3, vd3);
            bench::dot(&b, vf3, vf3);
        }
        {
            using namespace data::raw;
            bench::dot(&b, vd3, vd3);
            bench::dot(&b, vf3, vf3);
        }
        {
            using namespace data::vector;
            bench::dot(&b, vd3, vd3);
            bench::dot(&b, vf3, vf3);
        }
        {
            using namespace data::valarray;
            bench::dot(&b, vd3, vd3);
            bench::dot(&b, vf3, vf3);
        }
        {
            using namespace data::fixed;
            bench::dot(&b, vd3, vd3);
            bench::dot(&b, vf3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::dot(&b, vd3, vd3);
            bench::dot(&b, vf3, vf3);
        }
    }

    {
        auto b = make_bench("blas::dot(4,4)");
        {
            using namespace data::array;
            bench::dot(&b, vd4_e, vd4_e);
            bench::dot(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::raw;
            bench::dot(&b, vd4_e, vd4_e);
            bench::dot(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::vector;
            bench::dot(&b, vd4_e, vd4_e);
            bench::dot(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::valarray;
            bench::dot(&b, vd4_e, vd4_e);
            bench::dot(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::fixed;
            bench::dot(&b, vd4_e, vd4_e);
            bench::dot(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::dot(&b, vd4_e, vd4_e);
            bench::dot(&b, vf4_e, vf4_e);
        }
    }

    {
        auto b = make_bench("blas::outer(3,3)");
        {
            using namespace data::array;
            bench::outer(&b, vd3, vd3);
            bench::outer(&b, vf3, vf3);
        }
        {
            using namespace data::raw;
            bench::outer(&b, vd3, vd3);
            bench::outer(&b, vf3, vf3);
        }
        {
            using namespace data::vector;
            bench::outer(&b, vd3, vd3);
            bench::outer(&b, vf3, vf3);
        }
        {
            using namespace data::valarray;
            bench::outer(&b, vd3, vd3);
            bench::outer(&b, vf3, vf3);
        }
        {
            using namespace data::fixed;
            bench::outer(&b, vd3, vd3);
            bench::outer(&b, vf3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::outer(&b, vd3, vd3);
            bench::outer(&b, vf3, vf3);
        }
    }

    {
        auto b = make_bench("blas::outer(4,4)");
        {
            using namespace data::array;
            bench::outer(&b, vd4_e, vd4_e);
            bench::outer(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::raw;
            bench::outer(&b, vd4_e, vd4_e);
            bench::outer(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::vector;
            bench::outer(&b, vd4_e, vd4_e);
            bench::outer(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::valarray;
            bench::outer(&b, vd4_e, vd4_e);
            bench::outer(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::fixed;
            bench::outer(&b, vd4_e, vd4_e);
            bench::outer(&b, vf4_e, vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::outer(&b, vd4_e, vd4_e);
            bench::outer(&b, vf4_e, vf4_e);
        }
    }

    {
        auto b = make_bench("blas::saxpy(3,3)");
        {
            using namespace data::array;
            bench::saxpy(&b, 3., vd3, vd3);
            bench::saxpy(&b, 3.f, vf3, vf3);
        }
        {
            using namespace data::raw;
            bench::saxpy(&b, 3., vd3, vd3);
            bench::saxpy(&b, 3.f, vf3, vf3);
        }
        {
            using namespace data::vector;
            bench::saxpy(&b, 3., vd3, vd3);
            bench::saxpy(&b, 3.f, vf3, vf3);
        }
        {
            using namespace data::valarray;
            bench::saxpy(&b, 3., vd3, vd3);
            bench::saxpy(&b, 3.f, vf3, vf3);
        }
        {
            using namespace data::fixed;
            bench::saxpy(&b, 3., vd3, vd3);
            bench::saxpy(&b, 3.f, vf3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::saxpy(&b, 3., vd3, vd3);
            bench::saxpy(&b, 3.f, vf3, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::saxpy(4,4)");
        {
            using namespace data::array;
            bench::saxpy(&b, 3.,  vd4_e, vd4_e);
            bench::saxpy(&b, 3.f, vf4_e, vf4_e);
        }
        {
            using namespace data::raw;
            bench::saxpy(&b, 3.,  vd4_e, vd4_e);
            bench::saxpy(&b, 3.f, vf4_e, vf4_e);
        }
        {
            using namespace data::vector;
            bench::saxpy(&b, 3.,  vd4_e, vd4_e);
            bench::saxpy(&b, 3.f, vf4_e, vf4_e);
        }
        {
            using namespace data::valarray;
            bench::saxpy(&b, 3.,  vd4_e, vd4_e);
            bench::saxpy(&b, 3.f, vf4_e, vf4_e);
        }
        {
            using namespace data::fixed;
            bench::saxpy(&b, 3.,  vd4_e, vd4_e);
            bench::saxpy(&b, 3.f, vf4_e, vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::saxpy(&b, 3.,  vd4_e, vd4_e);
            bench::saxpy(&b, 3.f, vf4_e, vf4_e);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::gaxpy(3x3,3,3)");
        {
            using namespace data::array;
            bench::gaxpy(&b, Md3x3, vd3, vd3);
            bench::gaxpy(&b, Mf3x3, vf3, vf3);
        }
        {
            using namespace data::raw;
            bench::gaxpy(&b, Md3x3, vd3, vd3);
            bench::gaxpy(&b, Mf3x3, vf3, vf3);
        }
        {
            using namespace data::vector;
            bench::gaxpy(&b, Md3x3, vd3, vd3);
            bench::gaxpy(&b, Mf3x3, vf3, vf3);
        }
        {
            using namespace data::valarray;
            bench::gaxpy(&b, Md3x3, vd3, vd3);
            bench::gaxpy(&b, Mf3x3, vf3, vf3);
        }
        {
            using namespace data::fixed;
            bench::gaxpy(&b, Md3x3, vd3, vd3);
            bench::gaxpy(&b, Mf3x3, vf3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::gaxpy(&b, Md3x3, vd3, vd3);
            bench::gaxpy(&b, Mf3x3, vf3, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("blas::gaxpy(4x4,4,4)");
        {
            using namespace data::array;
            bench::gaxpy(&b, Md4x4_symm, vd4_e, vd4_e);
            bench::gaxpy(&b, Mf4x4_symm, vf4_e, vf4_e);
        }
        {
            using namespace data::raw;
            bench::gaxpy(&b, Md4x4_symm, vd4_e, vd4_e);
            bench::gaxpy(&b, Mf4x4_symm, vf4_e, vf4_e);
        }
        {
            using namespace data::vector;
            bench::gaxpy(&b, Md4x4_symm, vd4_e, vd4_e);
            bench::gaxpy(&b, Mf4x4_symm, vf4_e, vf4_e);
        }
        {
            using namespace data::valarray;
            bench::gaxpy(&b, Md4x4_symm, vd4_e, vd4_e);
            bench::gaxpy(&b, Mf4x4_symm, vf4_e, vf4_e);
        }
        {
            using namespace data::fixed;
            bench::gaxpy(&b, Md4x4_symm, vd4_e, vd4_e);
            bench::gaxpy(&b, Mf4x4_symm, vf4_e, vf4_e);
        }
        {
            using namespace data::dynamic;
            bench::gaxpy(&b, Md4x4_symm, vd4_e, vd4_e);
            bench::gaxpy(&b, Mf4x4_symm, vf4_e, vf4_e);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }
}