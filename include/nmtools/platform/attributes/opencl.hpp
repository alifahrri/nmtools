#ifndef NMTOOLS_PLATFORM_ATTRIBUTES_OPENCL_HPP
#define NMTOOLS_PLATFORM_ATTRIBUTES_OPENCL_HPP

// to avoid c++4opencl error: program scope variable must reside in global or constant address space
#define nmtools_meta_variable_attribute constant

// on kernel force inline for index
#ifdef __OPENCL_VERSION__
#define nmtools_inline __attribute__((always_inline))
#else
#define nmtools_inline
#endif
#define nmtools_index_inline nmtools_inline
#define nmtools_index_attribute nmtools_index_inline
// to avoid invalid cast triggered by view when building c++ for opencl kernel
#define nmtools_view_attribute nmtools_inline

#endif // NMTOOLS_PLATFORM_ATTRIBUTES_OPENCL_HPP