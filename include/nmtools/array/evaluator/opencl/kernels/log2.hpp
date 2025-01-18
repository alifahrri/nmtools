#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_LOG2_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_LOG2_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/log2.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin log2_spv
#define nmtools_cl_kernel_len log2_spv_len
#define nmtools_cl_ufunc_name log2
#define nmtools_cl_ufunc_type log2_t
#define nmtools_cl_kernel_name(out_type, inp_type) log2##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(log2##_##out_type##_##inp_type)
#endif

#include "nmtools/array/evaluator/opencl/kernels/template_unary_ufunc.hpp"


#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_LOG2_HPP