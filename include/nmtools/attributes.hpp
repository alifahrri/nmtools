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

// defaults:

#ifndef nmtools_func_attribute
#define nmtools_func_attribute
#endif

#ifndef nmtools_inline
#define nmtools_inline
#endif

#ifndef nmtools_index_inline
#define nmtools_index_inline
#endif

#ifndef nmtools_index_attribute
#define nmtools_index_attribute
#endif

#ifndef nmtools_view_attribute
#define nmtools_view_attribute
#endif

#endif // NMTOOLS_ATTRIBUTES_HPP