#ifndef NMTOOLS_ATTRIBUTES_HPP
#define NMTOOLS_ATTRIBUTES_HPP

#if defined(__OPENCL_VERSION__)
#include "nmtools/platform/attributes/opencl.hpp"
#elif defined(__CUDA__)
#include "nmtools/platform/attributes/cuda.hpp"
#endif

#ifndef nmtools_meta_variable_attribute
// do nothing
#define nmtools_meta_variable_attribute
#endif

#ifndef nmtools_func_attribute
#define nmtools_func_attribute
#endif

#endif // NMTOOLS_ATTRIBUTES_HPP