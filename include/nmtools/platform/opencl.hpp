#ifndef NMTOOLS_PLATFORM_OPENCL_HPP
#define NMTOOLS_PLATFORM_OPENCL_HPP

// compiling opencl kernel
#define NMTOOLS_DISABLE_STL
#define NMTOOLS_UTL_NO_MALLOC
#define NMTOOLS_DISABLE_DYNAMIC_ARRAY
#define NMTOOLS_DISABLE_VECTOR
#define NMTOOLS_META_MAKE_SEQUENCE
#define nmtools_list ::nmtools::utl::static_vector

// use ifndef to make it configurable from outside (e.g. app level)
#ifndef NMTOOLS_KERNEL_MAX_DIM
#define NMTOOLS_KERNEL_MAX_DIM 8
#endif // NMTOOLS_KERNEL_MAX_DIM

#ifndef NMTOOLS_OPENCL_KERNEL_MAX_DIM
#define NMTOOLS_OPENCL_KERNEL_MAX_DIM NMTOOLS_KERNEL_MAX_DIM
#endif // NMTOOLS_OPENCL_KERNEL_MAX_DIM

// TODO: revisit this case
// NOTE: on spirv, we can't have access / cast to base class
#define NMTOOLS_NO_BASE_ACCESS

#define NMTOOLS_HAS_ADDRESS_SPACE

#define nmtools_address_private private
#define nmtools_address_generic generic

#endif // NMTOOLS_PLATFORM_OPENCL_HPP