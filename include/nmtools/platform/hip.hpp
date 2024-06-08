#ifndef NMTOOLS_PLATFORM_HIP_HPP
#define NMTOOLS_PLATFORM_HIP_HPP

#define nmtools_func_attribute __host__ __device__

#if defined(__HIP__) && defined(__HIP_ARCH__)
// compiling hip kernel, no stl no malloc available
#define NMTOOLS_DISABLE_STL
#define NMTOOLS_UTL_NO_MALLOC
#define NMTOOLS_DISABLE_DYNAMIC_ARRAY
#define NMTOOLS_DISABLE_VECTOR
// TODO: remove NMTOOLS_META_MAKE_SEQUENCE, check for nmtools_list is defined instead
#define NMTOOLS_META_MAKE_SEQUENCE
#define nmtools_list ::nmtools::utl::static_vector
#define NMTOOLS_OPENCL_KERNEL_MAX_DIM 8
#define NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
#elif defined(__HIP__)
// follow cuda
#define NMTOOLS_DISABLE_STL
#endif

#endif // NMTOOLS_PLATFORM_HIP_HPP