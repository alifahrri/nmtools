// TODO: adjust the following params
#if 1
#include "nmtools/array/activations/hardshrink.hpp"

#define nmtools_cl_kernel_bin hardshrink_spv
#define nmtools_cl_kernel_len hardshrink_spv_len
#define nmtools_cl_ufunc_name hardshrink
#define nmtools_cl_ufunc_type hardshrink_t
#define nmtools_cl_kernel_name(out_type, inp_type) hardshrink##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(hardshrink##_##out_type##_##inp_type)
#endif

#include "nmtools/ndarray.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/core/mutable_ref.hpp"

namespace nm = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#ifndef nm_stringify
#define nm_stringify(a) #a
#endif

// check if we are building kernel/device program
#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

#undef nmtools_cl_kernel

// TODO: add additional params/attribute here
#define nmtools_cl_kernel(out_type, inp_type) \
kernel void nmtools_cl_kernel_name(out_type,inp_type)(global out_type* out, global const inp_type* inp, const unsigned long out_size, const unsigned long inp_size, const inp_type lambda) \
{                                                    \
    auto ref     = view::ref(inp,inp_size);          \
    auto mut_ref = view::mutable_ref(out,out_size);  \
    auto fn      = view::nmtools_cl_ufunc_name(ref,lambda); \
    auto i       = get_global_id(0);                 \
    if (i<out_size) {                                \
        nm::at(mut_ref,i) = nm::at(fn,i);            \
    } \
}

nmtools_cl_kernel(float,float)
nmtools_cl_kernel(double,double)

// otherwise, we are building host program
#else

#include "nmtools/evaluator/opencl/ufunc.hpp"
#include <cstring> // memcpy

extern unsigned char nmtools_cl_kernel_bin [];
extern unsigned int nmtools_cl_kernel_len;

namespace nmtools::opencl
{
    // TODO: add variadic template for op args here, if required
    #if 1
    template <typename array_t, typename...op_args_t>
    struct kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type<op_args_t...>,array_t>>
        : base_kernel_t< kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type<op_args_t...>,array_t>> >
    #else
    template <typename array_t>
    struct kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type,array_t>>
        : base_kernel_t< kernel_t<view::decorator_t<view::ufunc_t,view::nmtools_cl_ufunc_type,array_t>> >
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

        template <typename inp_t, typename out_t>
        static auto kernel_name()
        {
            // TODO: handle unsupported types
            if constexpr (meta::is_same_v<out_t,float> && meta::is_same_v<inp_t,float>) {
                return nmtools_cl_kernel_name_str(float,float);
            } else /* if constexpr (meta::is_same_v<out_t,double> && meta::is_same_v<inp_t,double>) */ {
                return nmtools_cl_kernel_name_str(double,double);
            }
        }

        // TODO optional function
        #if 1
        auto get_fn_attributes()
        {
            return nmtools_tuple{this->view.op.lambda};
        }
        #endif
    }; // kernel_t
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS