#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_LOG10_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_LOG10_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/log10.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin log10_spv
#define nmtools_cl_kernel_len log10_spv_len
#define nmtools_cl_ufunc_name log10
#define nmtools_cl_ufunc_type log10_t
#define nmtools_cl_kernel_name(out_type, inp_type) log10##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(log10##_##out_type##_##inp_type)
#endif

#include "nmtools/array/eval/opencl/kernels/template_unary_ufunc.hpp"


#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_LOG10_HPP