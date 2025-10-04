#ifndef NMTOOLS_TESTS_KERNELS_COPY_HPP
#define NMTOOLS_TESTS_KERNELS_COPY_HPP

#include "nmtools/nmtools.hpp"
#include "nmtools/tilekit/tilekit.hpp"

namespace nm = nmtools;
namespace tk = nmtools::tilekit;
namespace view = nmtools::view;

using nmtools_tuple;
using nmtools_array;
using namespace nmtools::literals;

using nmtools::at, nmtools::shape;

template <typename context_t, typename out_t, typename array_t>
auto copy_kernel(context_t&& context, out_t& out, const array_t& array)
{
    auto t_shape    = tuple{4_ct};
    auto [blk_dim0] = t_shape;
    auto [inp_dim0] = shape(array);

    auto n_iter = inp_dim0 / blk_dim0;
    for (nm_size_t i=0; i<n_iter; i++) {
        auto offset = tuple{i};
        auto block  = tk::load(context,array,offset,t_shape);

        tk::store(context,out,offset,block);
    }
}

#endif // NMTOOLS_TESTS_KERNELS_COPY_HPP