#ifndef NMTOOLS_PLATFORM_CUDA_HPP
#define NMTOOLS_PLATFORM_CUDA_HPP

#define nmtools_func_attribute __host__ __device__

#if defined(__CUDA__) && defined(__CUDA_ARCH__)
// compiling cuda kernel, no stl no malloc available
#define NMTOOLS_DISABLE_STL
#define NMTOOLS_UTL_NO_MALLOC
#define NMTOOLS_DISABLE_DYNAMIC_ARRAY
#define NMTOOLS_DISABLE_VECTOR
// TODO: remove NMTOOLS_META_MAKE_SEQUENCE, check for nmtools_list is defined instead
#define NMTOOLS_META_MAKE_SEQUENCE
#define nmtools_list ::nmtools::utl::static_vector
#define NMTOOLS_OPENCL_KERNEL_MAX_DIM 8
#define NMTOOLS_TESTING_DISABLE_DYNAMIC_ALLOCATION
#elif defined(__CUDA__)
// compiling cuda host, disable stl because causing cudaGetLastError (98): invalid device function (at least on clang-10 cuda)
#define NMTOOLS_DISABLE_STL
#endif

#endif // NMTOOLS_PLATFORM_CUDA_HPP