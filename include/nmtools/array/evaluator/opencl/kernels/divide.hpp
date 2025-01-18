#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_DIVIDE_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_DIVIDE_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/divide.hpp"

#if 1
#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str
#endif

#define NMTOOLS_UFUNC_OP_HAS_ARGS 0

#define nmtools_cl_ufunc_type divide_t
#define nmtools_cl_ufunc_name divide
#define nmtools_cl_kernel_bin nm_cl_divide_spv
#define nmtools_cl_kernel_len nm_cl_divide_spv_len
#define nmtools_cl_kernel_name(out_type, left_type, right_type) nm_cl_divide##_##out_type##_##left_type##_##right_type
#define nmtools_cl_kernel_name_str(out_type, left_type, right_type) nm_stringify(nm_cl_divide##_##out_type##_##left_type##_##right_type)
#endif

#include "nmtools/array/evaluator/opencl/kernels/template_binary_ufunc.hpp"

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_DIVIDE_HPP