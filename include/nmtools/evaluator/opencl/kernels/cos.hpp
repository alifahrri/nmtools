#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_COS_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_COS_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/cos.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin cos_spv
#define nmtools_cl_kernel_len cos_spv_len
#define nmtools_cl_ufunc_name cos
#define nmtools_cl_ufunc_type cos_t
#define nmtools_cl_kernel_name(out_type, inp_type) cos##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(cos##_##out_type##_##inp_type)
#endif

#include "nmtools/evaluator/opencl/kernels/template_unary_ufunc.hpp"

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_COS_HPP