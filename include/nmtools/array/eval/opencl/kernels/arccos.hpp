#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_ARCCOS_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_ARCCOS_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/arccos.hpp"

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#define nmtools_cl_kernel_bin arccos_spv
#define nmtools_cl_kernel_len arccos_spv_len
#define nmtools_cl_ufunc_name arccos
#define nmtools_cl_ufunc_type arccos_t
#define nmtools_cl_kernel_name(out_type, inp_type) arccos##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(arccos##_##out_type##_##inp_type)
#endif

#include "nmtools/array/eval/opencl/kernels/template_unary_ufunc.hpp"

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_ARCCOS_HPP