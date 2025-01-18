// TODO: adjust the following params
#if 0
#include "nmtools/array/view/ufuncs/add.hpp"

#if 0
#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str
#endif

#define nmtools_cl_kernel_bin add_spv
#define nmtools_cl_kernel_len add_spv_len
#define nmtools_cl_ufunc_name add
#define nmtools_cl_ufunc_type add_t
#define nmtools_cl_kernel_name(out_type, left_type, right_type) add##_##out_type##_##left_type##right_type
#define nmtools_cl_kernel_name_str(out_type, left_type, right_type) nm_stringify(add##_##out_type##_##left_type##right_type)
#endif

#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/evaluator/kernel_helper.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

#ifndef nm_stringify
#define nm_stringify(a) #a
#endif

// check if we are building kernel/device program
#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

namespace nm = nmtools;
namespace na = nmtools::array;
namespace view = nmtools::view;
namespace meta = nmtools::meta;
namespace opencl = nmtools::array::opencl;
namespace detail = nmtools::view::detail;

// TODO: add additional params/attribute here
#define nmtools_cl_kernel(out_type, left_type, right_type) \
kernel void nmtools_cl_kernel_name(out_type,left_type,right_type) \
    ( global out_type* out_ptr                   \
    , global const left_type* left_ptr           \
    , global const right_type* right_ptr         \
    , global const unsigned int* out_shape_ptr   \
    , global const unsigned int* left_shape_ptr  \
    , global const unsigned int* right_shape_ptr \
    , const unsigned int out_dim                \
    , const unsigned int left_dim               \
    , const unsigned int right_dim)             \
{ \
    auto left   = na::create_array(left_ptr,left_shape_ptr,left_dim);       \
    auto right  = na::create_array(right_ptr,right_shape_ptr,right_dim);    \
    auto output = na::create_mutable_array(out_ptr,out_shape_ptr,out_dim);  \
    auto result = view::nmtools_cl_ufunc_name(left,right);                  \
    opencl::assign_array(output,result);                                    \
}

nmtools_cl_kernel(float,float,float)
nmtools_cl_kernel(double,double,double)

// otherwise, we are building host program
#else

#include "nmtools/evaluator/opencl/ufunc.hpp"
#include <cstring> // memcpy

extern unsigned char nmtools_cl_kernel_bin [];
extern unsigned int nmtools_cl_kernel_len;

namespace nmtools::array::opencl
{
    #ifndef NMTOOLS_UFUNC_OP_HAS_ARGS
    #define NMTOOLS_UFUNC_OP_HAS_ARGS 1
    #endif

    // TODO: add variadic template for op args here, if required
    #if NMTOOLS_UFUNC_OP_HAS_ARGS
    template <typename...arrays_t, typename...op_args_t>
    struct kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type<op_args_t...>,arrays_t...>>
        : base_kernel_t< kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type<op_args_t...>,arrays_t...>> >
    #else
    template <typename...arrays_t>
    struct kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type,arrays_t...>>
        : base_kernel_t< kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type,arrays_t...>> >
    #endif
    {
        static auto get_spirv()
        {
            using vector = nmtools_list<unsigned char>;
            auto spirv = vector();
            spirv.resize(nmtools_cl_kernel_len);
            memcpy(spirv.data(),nmtools_cl_kernel_bin,sizeof(unsigned char) * nmtools_cl_kernel_len);
            return spirv;
        }

        template <typename left_t, typename right_t, typename out_t>
        static auto kernel_name()
        {
            // note that macro can't nicely interacts with type system, so manually unroll type checks
            if constexpr (meta::is_same_v<out_t,float> && meta::is_same_v<left_t,float> && meta::is_same_v<right_t,float>) {
                return nmtools_cl_kernel_name_str(float,float,float);
            } else if constexpr (meta::is_same_v<out_t,double> && meta::is_same_v<left_t,double> && meta::is_same_v<right_t,double>) {
                return nmtools_cl_kernel_name_str(double,double,double);
            } else {
                return error::UNSUPPORTED_KERNEL_TYPES<left_t,right_t,out_t>{};
            }
        }

        // TODO optional function
        #if 0
        auto get_fn_attributes()
        {
            return nmtools_tuple{};
        }
        #endif
    }; // kernel_t
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str