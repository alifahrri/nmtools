#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_ARCSINH_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_ARCSINH_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/ufuncs/arcsinh.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin arcsinh_spv
#define nmtools_cl_kernel_len arcsinh_spv_len
#define nmtools_cl_ufunc_name arcsinh
#define nmtools_cl_ufunc_type arcsinh_t
#define nmtools_cl_kernel_name(out_type, inp_type) arcsinh##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(arcsinh##_##out_type##_##inp_type)
#endif

#include "nmtools/evaluator/opencl/kernels/template_unary_ufunc.hpp"

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_ARCSINH_HPP