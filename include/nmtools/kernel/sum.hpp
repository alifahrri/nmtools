#ifndef NMTOOLS_KERNEL_SUM_HPP
#define NMTOOLS_KERNEL_SUM_HPP

#include "nmtools/kernel/ufuncs/reduce.hpp"
#include "nmtools/array/ufuncs/add.hpp"

namespace nmtools::kernel
{
    inline auto sum = reduce_t<view::add_t<>>{};
}

#endif // NMTOOLS_KERNEL_SUM_HPP