#ifndef NMTOOLS_KERNEL_PROD_HPP
#define NMTOOLS_KERNEL_PROD_HPP

#include "nmtools/kernel/ufuncs/reduce.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"

namespace nmtools::kernel
{
    inline auto prod = reduce_t<view::multiply_t<>>{};
}

#endif // NMTOOLS_KERNEL_PROD_HPP
