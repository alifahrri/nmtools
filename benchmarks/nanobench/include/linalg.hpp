#ifndef LINALG_HPP
#define LINALG_HPP

#include "nanobench/nanobench.h"
#include "nmtools/linalg.hpp"
#include <array>

namespace nmt = nmtools;
namespace nla = nmt::linalg;
using std::array;

template <typename T>
void gauss_elimination_benchmark(ankerl::nanobench::Bench *bench, char const *name) 
{
    /** TODO: benchmark other container **/
    auto A = array<array<T,3>,3>{
        array<T,3>{3.0, -0.1, -0.2},
        array<T,3>{0.1,  7.0, -0.3},
        array<T,3>{0.3, -0.2, 10.0},
    };
    auto b = array<T,3>{7.85, -19.3, 71.4};
    bench->run(name, [&](){
        auto x = nla::gauss_elimination(A,b);
    });
}

#endif