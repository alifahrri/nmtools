#include "nmtools/tilekit/tilekit.hpp"
#include "nmtools/tilekit/vector.hpp"
#include "nmtools/tilekit/thread_pool.hpp"
#include "nmtools/nmtools.hpp"

#include <iostream>

namespace nm = nmtools;
namespace tk = nmtools::tilekit;
namespace utils = nmtools::utils;
using mt_vector = tk::thread_pool<tk::vector::context_t>;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

struct add_kernel_t
{
    template <typename tile_shape_t=tuple<nm::ct<2>,nm::ct<4>>, typename context_t, typename out_t, typename a_t, typename b_t>
    auto operator()(context_t ctx, out_t& out, const a_t& a, const b_t& b, const tile_shape_t t_shape=tile_shape_t{})
    {
        auto [t_id] = tk::worker_id(ctx);
        auto [t_size] = tk::worker_size(ctx);

        auto a_shape = shape(a);
        auto offset  = tk::ndoffset(a_shape,t_shape);
        // t_size num workers
        auto n_iter = (offset.size()/t_size);
        for (nm_size_t i=0; i<n_iter; i++) {
            auto tile_offset = offset[(t_id*n_iter)+i];
            auto block_a = tk::load(ctx,a,tile_offset,t_shape);
            auto block_b = tk::load(ctx,b,tile_offset,t_shape);
            auto result  = block_a + block_b;

            tk::store(ctx,out,tile_offset,result);
        }
    }
};
inline auto add_kernel = add_kernel_t{};

int main(int argc, char** argv)
{
    auto gen   = nm::random_engine();
    auto dtype = nm::float32;

    auto M = 1024;
    auto N = 1024;
    auto a_shape = array{M,N};
    auto b_shape = array{M,N};

    auto a = nm::random(a_shape,dtype,gen);
    auto b = nm::random(b_shape,dtype,gen);
    auto c = nm::Array::zeros(array{M,N},dtype);

    auto tile_shape = tuple{2_ct,16_ct};
    auto num_threads = 8;
    auto ctx = mt_vector(num_threads);
    auto worker_size = num_threads;

    for (nm_size_t i=0; i<10'000; i++) {
        ctx.launch(worker_size,add_kernel,c,a,b,tile_shape);
    }

    auto expected = nm::add(a,b);

    auto isclose = utils::isclose(c,expected);

    std::cout << "C shape: "
        << utils::to_string(c.shape())
        << std::endl;
    
    std::cout << "Is close: "
        << std::boolalpha
        << isclose
        << std::endl;
    
    return 0;
}