#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_EXP2_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_EXP2_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/exp2.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin exp2_spv
#define nmtools_cl_kernel_len exp2_spv_len
#define nmtools_cl_ufunc_name exp2
#define nmtools_cl_ufunc_type exp2_t
#define nmtools_cl_kernel_name(out_type, inp_type) exp2##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(exp2##_##out_type##_##inp_type)
#endif

#include "nmtools/array/eval/opencl/kernels/template_unary_ufunc.hpp"


#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_EXP2_HPP