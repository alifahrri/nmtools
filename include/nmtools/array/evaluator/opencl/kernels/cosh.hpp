#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_COSH_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_COSH_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/cosh.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin cosh_spv
#define nmtools_cl_kernel_len cosh_spv_len
#define nmtools_cl_ufunc_name cosh
#define nmtools_cl_ufunc_type cosh_t
#define nmtools_cl_kernel_name(out_type, inp_type) cosh##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(cosh##_##out_type##_##inp_type)
#endif

#include "nmtools/array/evaluator/opencl/kernels/template_unary_ufunc.hpp"

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_COSH_HPP