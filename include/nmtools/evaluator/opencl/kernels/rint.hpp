#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_RINT_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_RINT_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/ufuncs/rint.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin rint_spv
#define nmtools_cl_kernel_len rint_spv_len
#define nmtools_cl_ufunc_name rint
#define nmtools_cl_ufunc_type rint_t
#define nmtools_cl_kernel_name(out_type, inp_type) rint##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(rint##_##out_type##_##inp_type)
#endif

#include "nmtools/evaluator/opencl/kernels/template_unary_ufunc.hpp"


#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_RINT_HPP