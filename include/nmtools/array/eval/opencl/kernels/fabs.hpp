#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_FABS_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_FABS_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/fabs.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin fabs_spv
#define nmtools_cl_kernel_len fabs_spv_len
#define nmtools_cl_ufunc_name fabs
#define nmtools_cl_ufunc_type fabs_t
#define nmtools_cl_kernel_name(out_type, inp_type) fabs##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(fabs##_##out_type##_##inp_type)
#endif

#include "nmtools/array/eval/opencl/kernels/template_unary_ufunc.hpp"


#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_FABS_HPP