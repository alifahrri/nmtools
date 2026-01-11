#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/vector.hpp"
#include "nmtools/nmtools.hpp"

#include <iostream>

namespace nm = nmtools;
namespace tk = nmtools::tilekit;
namespace utils = nmtools::utils;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

template <typename context_t, typename out_t, typename a_t, typename b_t>
auto vector_add(context_t& ctx, out_t& out, const a_t& a, const b_t& b)
{
    auto t_shape  = tuple{4_ct};
    auto [dim0]   = t_shape;
    auto a_shape  = shape(a);
    auto [a_dim0] = a_shape;
    auto n_iter   = a_dim0 / dim0;

    for (nm_size_t i=0; i<n_iter; i++) {
        auto offset  = tuple{i};
        auto block_a = tk::load(ctx,a,offset,t_shape);
        auto block_b = tk::load(ctx,b,offset,t_shape);
        auto result  = block_a + block_b;

        tk::store(ctx,out,offset,result);
    }
}

int main(int argc, char** argv)
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    constexpr auto DIM = 128;
    auto a_shape = array{DIM};
    auto b_shape = array{DIM};
    auto c_shape = array{DIM};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nmtools_array<float,DIM>{};
    auto ctx = tk::vector::Context;

    for (nm_size_t i=0; i<1'000'000; i++) {
        vector_add(ctx,c,a,b);
    }

    auto expected = nm::add(a,b);

    auto isclose = utils::isclose(c,expected);

    std::cout << "C shape: "
        << utils::to_string(c_shape)
        << std::endl;

    std::cout << "C: "
        << std::endl
        << utils::to_string(c)
        << std::endl;
    
    std::cout << "Is close: "
        << std::boolalpha
        << isclose
        << std::endl;
    
    return 0;
}