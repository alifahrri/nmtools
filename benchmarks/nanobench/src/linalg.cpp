// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"

// TODO: rename to nmtools/bench/linalg.hpp or something
#include "linalg.hpp"
// TODO: rename to nmtools/bench/data.hpp or something
#include "data.hpp"

#include "xsimd/xsimd.hpp"

#include <array>
#include <vector>
#include <valarray>
#include <experimental/simd>

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
        auto b = make_bench("linalg::forward_elimination(3x3)");

        {
            using namespace data::array;
            bench::forward_elimination(&b, Md3x3, vd3);
            bench::forward_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::raw;
            bench::forward_elimination(&b, Md3x3, vd3);
            bench::forward_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::vector;
            bench::forward_elimination(&b, Md3x3, vd3);
            bench::forward_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::valarray;
            bench::forward_elimination(&b, Md3x3, vd3);
            bench::forward_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::fixed;
            bench::forward_elimination(&b, Md3x3, vd3);
            bench::forward_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::forward_elimination(&b, Md3x3, vd3);
            bench::forward_elimination(&b, Mf3x3, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::backward_substitution(3x3)");
        {
            using namespace data::array;
            bench::backward_substitution(&b, Md3x3_upper, vd3_upper);
            bench::backward_substitution(&b, Mf3x3_upper, vf3_upper);
        }
        {
            using namespace data::raw;
            bench::backward_substitution(&b, Md3x3_upper, vd3_upper);
            bench::backward_substitution(&b, Mf3x3_upper, vf3_upper);
        }
        {
            using namespace data::vector;
            bench::backward_substitution(&b, Md3x3_upper, vd3_upper);
            bench::backward_substitution(&b, Mf3x3_upper, vf3_upper);
        }
        {
            using namespace data::valarray;
            bench::backward_substitution(&b, Md3x3_upper, vd3_upper);
            bench::backward_substitution(&b, Mf3x3_upper, vf3_upper);
        }
        {
            using namespace data::fixed;
            bench::backward_substitution(&b, Md3x3_upper, vd3_upper);
            bench::backward_substitution(&b, Mf3x3_upper, vf3_upper);
        }
        {
            using namespace data::dynamic;
            bench::backward_substitution(&b, Md3x3_upper, vd3_upper);
            bench::backward_substitution(&b, Mf3x3_upper, vf3_upper);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::naive_gauss_elimination(3x3)");
        {
            using namespace data::array;
            bench::naive_gauss_elimination(&b, Md3x3, vd3);
            bench::naive_gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::raw;
            bench::naive_gauss_elimination(&b, Md3x3, vd3);
            bench::naive_gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::vector;
            bench::naive_gauss_elimination(&b, Md3x3, vd3);
            bench::naive_gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::valarray;
            bench::naive_gauss_elimination(&b, Md3x3, vd3);
            bench::naive_gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::fixed;
            bench::naive_gauss_elimination(&b, Md3x3, vd3);
            bench::naive_gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::naive_gauss_elimination(&b, Md3x3, vd3);
            bench::naive_gauss_elimination(&b, Mf3x3, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::gauss_elimination(2x2)");
        {
            using namespace data::array;
            bench::gauss_elimination(&b, Md2x2, vd2);
            bench::gauss_elimination(&b, Mf2x2, vf2);
        }
        {
            using namespace data::raw;
            bench::gauss_elimination(&b, Md2x2, vd2);
            bench::gauss_elimination(&b, Mf2x2, vf2);
        }
        {
            using namespace data::vector;
            bench::gauss_elimination(&b, Md2x2, vd2);
            bench::gauss_elimination(&b, Mf2x2, vf2);
        }
        {
            using namespace data::valarray;
            bench::gauss_elimination(&b, Md2x2, vd2);
            bench::gauss_elimination(&b, Mf2x2, vf2);
        }
        {
            using namespace data::fixed;
            bench::gauss_elimination(&b, Md2x2, vd2);
            bench::gauss_elimination(&b, Mf2x2, vf2);
        }
        {
            using namespace data::dynamic;
            bench::gauss_elimination(&b, Md2x2, vd2);
            bench::gauss_elimination(&b, Mf2x2, vf2);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::gauss_elimination(3x3)");
        {
            using namespace data::array;
            bench::gauss_elimination(&b, Md3x3, vd3);
            bench::gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::raw;
            bench::gauss_elimination(&b, Md3x3, vd3);
            bench::gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::vector;
            bench::gauss_elimination(&b, Md3x3, vd3);
            bench::gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::valarray;
            bench::gauss_elimination(&b, Md3x3, vd3);
            bench::gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::fixed;
            bench::gauss_elimination(&b, Md3x3, vd3);
            bench::gauss_elimination(&b, Mf3x3, vf3);
        }
        {
            using namespace data::dynamic;
            bench::gauss_elimination(&b, Md3x3, vd3);
            bench::gauss_elimination(&b, Mf3x3, vf3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::tridiagonal_decomposition(4)");
        {
            using namespace data::array;
            bench::tridiagonal_decomposition(&b, vd4_e, vd4_f, vd4_g);
            bench::tridiagonal_decomposition(&b, vf4_e, vf4_f, vf4_g);
        }
        {
            using namespace data::raw;
            bench::tridiagonal_decomposition(&b, vd4_e, vd4_f, vd4_g);
            bench::tridiagonal_decomposition(&b, vf4_e, vf4_f, vf4_g);
        }
        {
            using namespace data::vector;
            bench::tridiagonal_decomposition(&b, vd4_e, vd4_f, vd4_g);
            bench::tridiagonal_decomposition(&b, vf4_e, vf4_f, vf4_g);
        }
        {
            using namespace data::valarray;
            bench::tridiagonal_decomposition(&b, vd4_e, vd4_f, vd4_g);
            bench::tridiagonal_decomposition(&b, vf4_e, vf4_f, vf4_g);
        }
        {
            using namespace data::fixed;
            bench::tridiagonal_decomposition(&b, vd4_e, vd4_f, vd4_g);
            bench::tridiagonal_decomposition(&b, vf4_e, vf4_f, vf4_g);
        }
        {
            using namespace data::dynamic;
            bench::tridiagonal_decomposition(&b, vd4_e, vd4_f, vd4_g);
            bench::tridiagonal_decomposition(&b, vf4_e, vf4_f, vf4_g);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::tridiagonal_elimination(4)");

        {
            using namespace data::array;
            bench::tridiagonal_elimination(&b, vd4_e, vd4_f, vd4_g, vd4_b);
            bench::tridiagonal_elimination(&b, vf4_e, vf4_f, vf4_g, vf4_b);
        }
        {
            using namespace data::raw;
            bench::tridiagonal_elimination(&b, vd4_e, vd4_f, vd4_g, vd4_b);
            bench::tridiagonal_elimination(&b, vf4_e, vf4_f, vf4_g, vf4_b);
        }
        {
            using namespace data::vector;
            bench::tridiagonal_elimination(&b, vd4_e, vd4_f, vd4_g, vd4_b);
            bench::tridiagonal_elimination(&b, vf4_e, vf4_f, vf4_g, vf4_b);
        }
        {
            using namespace data::valarray;
            bench::tridiagonal_elimination(&b, vd4_e, vd4_f, vd4_g, vd4_b);
            bench::tridiagonal_elimination(&b, vf4_e, vf4_f, vf4_g, vf4_b);
        }
        {
            using namespace data::fixed;
            bench::tridiagonal_elimination(&b, vd4_e, vd4_f, vd4_g, vd4_b);
            bench::tridiagonal_elimination(&b, vf4_e, vf4_f, vf4_g, vf4_b);
        }
        {
            using namespace data::dynamic;
            bench::tridiagonal_elimination(&b, vd4_e, vd4_f, vd4_g, vd4_b);
            bench::tridiagonal_elimination(&b, vf4_e, vf4_f, vf4_g, vf4_b);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::lu_decomposition(3x3)");
        {
            using namespace data::array;
            bench::lu_decomposition(&b, Md3x3);
            bench::lu_decomposition(&b, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::lu_decomposition(&b, Md3x3);
            bench::lu_decomposition(&b, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::lu_decomposition(&b, Md3x3);
            bench::lu_decomposition(&b, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::lu_decomposition(&b, Md3x3);
            bench::lu_decomposition(&b, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::lu_decomposition(&b, Md3x3);
            bench::lu_decomposition(&b, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::lu_decomposition(&b, Md3x3);
            bench::lu_decomposition(&b, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::inverse(3x3)");
        {
            using namespace data::array;
            bench::inverse(&b, Md3x3);
            bench::inverse(&b, Mf3x3);
        }
        {
            using namespace data::raw;
            bench::inverse(&b, Md3x3);
            bench::inverse(&b, Mf3x3);
        }
        {
            using namespace data::vector;
            bench::inverse(&b, Md3x3);
            bench::inverse(&b, Mf3x3);
        }
        {
            using namespace data::valarray;
            bench::inverse(&b, Md3x3);
            bench::inverse(&b, Mf3x3);
        }
        {
            using namespace data::fixed;
            bench::inverse(&b, Md3x3);
            bench::inverse(&b, Mf3x3);
        }
        {
            using namespace data::dynamic;
            bench::inverse(&b, Md3x3);
            bench::inverse(&b, Mf3x3);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::inverse(4x4)");
        {
            using namespace data::array;
            bench::inverse(&b, Md4x4_symm);
            bench::inverse(&b, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::inverse(&b, Md4x4_symm);
            bench::inverse(&b, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::inverse(&b, Md4x4_symm);
            bench::inverse(&b, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::inverse(&b, Md4x4_symm);
            bench::inverse(&b, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::inverse(&b, Md4x4_symm);
            bench::inverse(&b, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::inverse(&b, Md4x4_symm);
            bench::inverse(&b, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::inverse(5x5)");
        {
            using namespace data::array;
            bench::inverse(&b, Md5x5_symm);
            bench::inverse(&b, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::inverse(&b, Md5x5_symm);
            bench::inverse(&b, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::inverse(&b, Md5x5_symm);
            bench::inverse(&b, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::inverse(&b, Md5x5_symm);
            bench::inverse(&b, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::inverse(&b, Md5x5_symm);
            bench::inverse(&b, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::inverse(&b, Md5x5_symm);
            bench::inverse(&b, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::cholesky_decomposition(3x3)");
        {
            using namespace data::array;
            bench::cholesky_decomposition(&b, Md3x3_symm);
            bench::cholesky_decomposition(&b, Mf3x3_symm);
        }
        {
            using namespace data::raw;
            bench::cholesky_decomposition(&b, Md3x3_symm);
            bench::cholesky_decomposition(&b, Mf3x3_symm);
        }
        {
            using namespace data::vector;
            bench::cholesky_decomposition(&b, Md3x3_symm);
            bench::cholesky_decomposition(&b, Mf3x3_symm);
        }
        {
            using namespace data::valarray;
            bench::cholesky_decomposition(&b, Md3x3_symm);
            bench::cholesky_decomposition(&b, Mf3x3_symm);
        }
        {
            using namespace data::fixed;
            bench::cholesky_decomposition(&b, Md3x3_symm);
            bench::cholesky_decomposition(&b, Mf3x3_symm);
        }
        {
            using namespace data::dynamic;
            bench::cholesky_decomposition(&b, Md3x3_symm);
            bench::cholesky_decomposition(&b, Mf3x3_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::cholesky_decomposition(4x4)");
        {
            using namespace data::array;
            bench::cholesky_decomposition(&b, Md4x4_symm);
            bench::cholesky_decomposition(&b, Mf4x4_symm);
        }
        {
            using namespace data::raw;
            bench::cholesky_decomposition(&b, Md4x4_symm);
            bench::cholesky_decomposition(&b, Mf4x4_symm);
        }
        {
            using namespace data::vector;
            bench::cholesky_decomposition(&b, Md4x4_symm);
            bench::cholesky_decomposition(&b, Mf4x4_symm);
        }
        {
            using namespace data::valarray;
            bench::cholesky_decomposition(&b, Md4x4_symm);
            bench::cholesky_decomposition(&b, Mf4x4_symm);
        }
        {
            using namespace data::fixed;
            bench::cholesky_decomposition(&b, Md4x4_symm);
            bench::cholesky_decomposition(&b, Mf4x4_symm);
        }
        {
            using namespace data::dynamic;
            bench::cholesky_decomposition(&b, Md4x4_symm);
            bench::cholesky_decomposition(&b, Mf4x4_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }

    {
        auto b = make_bench("linalg::cholesky_decomposition(5x5)");
        {
            using namespace data::array;
            bench::cholesky_decomposition(&b, Md5x5_symm);
            bench::cholesky_decomposition(&b, Mf5x5_symm);
        }
        {
            using namespace data::raw;
            bench::cholesky_decomposition(&b, Md5x5_symm);
            bench::cholesky_decomposition(&b, Mf5x5_symm);
        }
        {
            using namespace data::vector;
            bench::cholesky_decomposition(&b, Md5x5_symm);
            bench::cholesky_decomposition(&b, Mf5x5_symm);
        }
        {
            using namespace data::valarray;
            bench::cholesky_decomposition(&b, Md5x5_symm);
            bench::cholesky_decomposition(&b, Mf5x5_symm);
        }
        {
            using namespace data::fixed;
            bench::cholesky_decomposition(&b, Md5x5_symm);
            bench::cholesky_decomposition(&b, Mf5x5_symm);
        }
        {
            using namespace data::dynamic;
            bench::cholesky_decomposition(&b, Md5x5_symm);
            bench::cholesky_decomposition(&b, Mf5x5_symm);
        }
        gen(ankerl::nanobench::templates::htmlBoxplot(), b);
    }
}