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

namespace nm = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#ifndef nm_stringify
#define nm_stringify(a) #a
#endif

// check if we are building kernel/device program
#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

// TODO: add additional params/attribute here
#define nmtools_cl_kernel(out_type, left_type, right_type) \
kernel void nmtools_cl_kernel_name(out_type,left_type,right_type)(global out_type* out, global const left_type* left, global const right_type* right, const unsigned long out_size, const unsigned long left_size, const unsigned long right_size) \
{                                                      \
    auto left_ref  = view::ref(left,left_size);        \
    auto right_ref = view::ref(right,right_size);      \
    auto mut_out   = view::mutable_ref(out,out_size);  \
    /* auto fn        = view::nmtools_cl_ufunc_name(left_ref,right_ref); */ \
    /* auto flat_out  = view::mutable_flatten(mut_out); */ \
    /* auto flat_inp  = view::flatten(fn); */ \
    const auto b_shape = nmtools_array<size_t,1>{out_size}; \
    const auto b_left = view::broadcast_to(left_ref,b_shape); \
    /* const auto broadcasted = view::broadcast_arrays(left_ref,right_ref); */ \
    /* const auto& b_left  = nm::get<0>(broadcasted); */ \
    /* const auto& b_right = nm::get<1>(broadcasted); */ \
    /* const auto i = get_global_id(0); */                 \
    if (true) {                                  \
        /* flat_out(i) = flat_inp(i); */ \
        /* nm::at(mut_out,i) = nm::at(left_ref,i) + nm::at(right_ref,i); */ \
        /* nm::at(mut_out,i) = nm::at(b_left,i) + nm::at(b_right,i); */ \
        /* auto dst_shape = nm::shape(fn); */ \
        /* auto src_shape = nm::shape(left_ref); */ \
        /* auto indices = nmtools_array<size_t,1>{i}; */ \
        /* auto origin_axes = b_left.origin_axes; */ \
        /* auto origin_strides = nmtools_array<size_t,1>{1}; */ \
        /* auto offset = i; */ \
        /* auto offset = nm::at(origin_strides,0) * nm::at(indices,0); */ \
        /* auto offset = nm::index::compute_offset(indices,origin_strides); */ \
        /* auto tf_indices = nm::index::compute_indices(offset,src_shape); */ \
        /* auto tf_indices = nmtools_array<size_t,1>{i}; */ \
        /* auto tf_indices = nm::index::broadcast_to_(src_shape,indices,origin_strides); */ \
        /* auto tf_indices = nm::index::broadcast_to(indices,src_shape,dst_shape,origin_axes); */ \
        /* auto offset = nm::index::compute_offset(indices,nmtools_array<size_t,1>{1}); */ \
        /* auto offset = i; */ \
        /* auto tf_indices = nm::index::compute_indices(offset,src_shape,nmtools_array<size_t,1>{1}); */ \
        /* auto tf_indices = nmtools_array<size_t,1>{}; */ \
        /* auto strides = nmtools_array<size_t,1>{1}; */ \
        /* for (size_t i=0; i<nm::len(tf_indices); i++) */ \
        /*     nm::at(tf_indices,i) = (offset / nm::at(strides,i)) % nm::at(src_shape,i); */ \
        /*     nm::at(tf_indices,i) = offset; */ \
        /* nm::apply_at(mut_out,tf_indices) = nm::apply_at(b_left,tf_indices); */ \
        /* nm::at(mut_out,tf_indices[0]) = nm::at(b_left,tf_indices[0]); */ \
        /* ERRROR: nm::at(mut_out,offset) = nm::at(b_left,offset); */ \
        /* nm::apply_at(mut_out,tf_indices) = nm::apply_at(left_ref,tf_indices) + nm::apply_at(right_ref,tf_indices); */ \
    } \
}

nmtools_cl_kernel(float,float,float)
// nmtools_cl_kernel(double,double,double)

// otherwise, we are building host program
#else

#include "nmtools/array/eval/opencl/ufunc.hpp"
#include <cstring> // memcpy

extern unsigned char nmtools_cl_kernel_bin [];
extern unsigned int nmtools_cl_kernel_len;

namespace nmtools::array::opencl
{
    // TODO: add variadic template for op args here, if required
    #if 1
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
            // TODO: handle unsupported types
            if constexpr (meta::is_same_v<out_t,float> && meta::is_same_v<left_t,float> && meta::is_same_v<right_t,float>) {
                return nmtools_cl_kernel_name_str(float,float,float);
            } else if constexpr (meta::is_same_v<out_t,double> && meta::is_same_v<left_t,double> && meta::is_same_v<right_t,double>) {
                return nmtools_cl_kernel_name_str(double,double,double);
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