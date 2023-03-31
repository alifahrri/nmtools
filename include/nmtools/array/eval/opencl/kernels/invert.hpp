#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_INVERT_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_INVERT_HPP

// TODO: adjust the following params
#if 1
#include "nmtools/array/view/ufuncs/invert.hpp"

#if 1
#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str
#endif

#define nmtools_cl_kernel_bin invert_spv
#define nmtools_cl_kernel_len invert_spv_len
#define nmtools_cl_ufunc_name invert
#define nmtools_cl_ufunc_type invert_t
#define nmtools_cl_kernel_name(out_type, inp_type) invert##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(invert##_##out_type##_##inp_type)
#endif

#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/view/mutable_ref.hpp"

namespace nm = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#ifndef nm_stringify
#define nm_stringify(a) #a
#endif

// check if we are building kernel/device program
#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

// TODO: add additional params/attribute here
#define nmtools_cl_kernel(out_type, inp_type) \
kernel void nmtools_cl_kernel_name(out_type,inp_type)(global out_type* out, global const inp_type* inp, const unsigned long out_size, const unsigned long inp_size) \
{                                                    \
    auto ref     = view::ref(inp,inp_size);          \
    auto mut_ref = view::mutable_ref(out,out_size);  \
    auto fn      = view::nmtools_cl_ufunc_name(ref); \
    auto i       = get_global_id(0);                 \
    if (i<out_size) {                                \
        nm::at(mut_ref,i) = nm::at(fn,i);            \
    } \
}

using nm::uint8_t, nm::uint16_t, nm::uint32_t, nm::uint64_t;

nmtools_cl_kernel(char,char)
nmtools_cl_kernel(short,short)
nmtools_cl_kernel(int,int)
nmtools_cl_kernel(long,long)
nmtools_cl_kernel(uint8_t,uint8_t)
nmtools_cl_kernel(uint16_t,uint16_t)
nmtools_cl_kernel(uint32_t,uint32_t)
nmtools_cl_kernel(uint64_t,uint64_t)

// otherwise, we are building host program
#else

#include "nmtools/array/eval/opencl/ufunc.hpp"
#include <cstring> // memcpy

extern unsigned char nmtools_cl_kernel_bin [];
extern unsigned int nmtools_cl_kernel_len;

namespace nmtools::array::opencl
{
    // TODO: add variadic template for op args here, if required
    #if 0
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
            if constexpr (meta::is_same_v<out_t,int> && meta::is_same_v<inp_t,int>) {
                return nmtools_cl_kernel_name_str(int,int);
            } else if constexpr (meta::is_same_v<out_t,long> && meta::is_same_v<inp_t,long>) {
                return nmtools_cl_kernel_name_str(long,long);
            } else if constexpr (meta::is_same_v<out_t,char> && meta::is_same_v<inp_t,char>) {
                return nmtools_cl_kernel_name_str(char,char);
            } else if constexpr (meta::is_same_v<out_t,short> && meta::is_same_v<inp_t,short>) {
                return nmtools_cl_kernel_name_str(short,short);
            } else if constexpr (meta::is_same_v<out_t,uint8_t> && meta::is_same_v<inp_t,uint8_t>) {
                return nmtools_cl_kernel_name_str(uint8_t,uint8_t);
            } else if constexpr (meta::is_same_v<out_t,uint16_t> && meta::is_same_v<inp_t,uint16_t>) {
                return nmtools_cl_kernel_name_str(uint16_t,uint16_t);
            } else if constexpr (meta::is_same_v<out_t,uint32_t> && meta::is_same_v<inp_t,uint32_t>) {
                return nmtools_cl_kernel_name_str(uint32_t,uint32_t);
            } else if constexpr (meta::is_same_v<out_t,uint64_t> && meta::is_same_v<inp_t,uint64_t>) {
                return nmtools_cl_kernel_name_str(uint64_t,uint64_t);
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


#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_INVERT_HPP