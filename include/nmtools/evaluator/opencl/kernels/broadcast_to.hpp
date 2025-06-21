#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_BROADCAST_TO_HPP

#include "nmtools/ndarray.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/core/mutable_ref.hpp"
#include "nmtools/evaluator/kernel_helper.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

#ifndef nm_stringify
#define nm_stringify(a) #a
#endif

#define nmtools_cl_kernel_name(out_type, inp_type) broadcast_to##_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type, inp_type) nm_stringify(broadcast_to##_##out_type##_##inp_type)

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nmtools::view;
namespace meta = nmtools::meta;
namespace opencl = nmtools::opencl;
namespace detail = nmtools::view::detail;

#define nmtools_cl_kernel(out_type,inp_type) \
kernel void nmtools_cl_kernel_name(out_type,inp_type) \
    ( global out_type* out_ptr                  \
    , global const inp_type* inp_ptr            \
    , global const unsigned int* out_shape_ptr  \
    , global const unsigned int* inp_shape_ptr  \
    , global const unsigned int* dst_shape_ptr  \
    , const unsigned int out_dim                \
    , const unsigned int inp_dim                \
    , const unsigned int dst_size)              \
{ \
    auto dst_shape   = na::create_vector</*DIM*/1>(dst_shape_ptr,dst_size);               \
    auto input       = na::create_array(inp_ptr,inp_shape_ptr,inp_dim);         \
    auto output      = na::create_mutable_array(out_ptr,out_shape_ptr,out_dim); \
    auto broadcasted = view::broadcast_to(input,dst_shape);                     \
    opencl::assign_array(output,broadcasted);                                   \
}

nmtools_cl_kernel(float,float)
nmtools_cl_kernel(double,double)

#else

#include "nmtools/evaluator/opencl/context.hpp"
#include <cstring> // memcpy

extern unsigned char nm_cl_broadcast_to_spv [];
extern unsigned int nm_cl_broadcast_to_spv_len;

namespace nmtools::opencl
{
    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct kernel_t<view::decorator_t<view::broadcast_to_t,array_t,shape_t,origin_axes_t,bsize_t>>
    {
        using view_t = view::decorator_t<view::broadcast_to_t,array_t,shape_t,origin_axes_t,bsize_t>;

        view_t view;
        std::shared_ptr<context_t> context;

        static auto get_spirv()
        {
            using vector = nmtools_list<unsigned char>;
            auto spirv   = vector();
            spirv.resize(nm_cl_broadcast_to_spv_len);
            memcpy(spirv.data(),nm_cl_broadcast_to_spv,sizeof(unsigned char) * nm_cl_broadcast_to_spv_len);
            return spirv;
        }

        template <typename inp_t, typename out_t=inp_t>
        static auto kernel_name()
        {
            if constexpr (meta::is_same_v<inp_t,float> && meta::is_same_v<out_t,float>) {
                return nmtools_cl_kernel_name_str(float,float);
            } else if constexpr (meta::is_same_v<inp_t,double> && meta::is_same_v<out_t,double>) {
                return nmtools_cl_kernel_name_str(double,double);
            }
        }

        template <typename output_t>
        auto eval(output_t& output)
        {
            using out_t = meta::get_element_type_t<output_t>;

            const auto& inp_array = *get_array(view);
            using inp_t = meta::get_element_type_t<meta::remove_cvref_pointer_t<decltype(inp_array)>>;

            auto inp_buffer = context->create_buffer(inp_array);
            auto out_buffer = context->create_buffer<out_t>(nmtools::size(output));

            auto kernel_name = this->kernel_name<inp_t,out_t>();

            if (!context->has_kernel(kernel_name)) {
                context->create_kernel(get_spirv(),kernel_name);
            }

            auto kernel = context->get_kernel(kernel_name);

            auto out_size = nmtools::size(output);
            [[maybe_unused]] auto inp_size = nmtools::size(inp_array);
            [[maybe_unused]] auto dst_size = nmtools::size(view);

            auto out_shape = nmtools::shape(output);
            auto inp_shape = nmtools::shape(inp_array);

            auto out_shape_buffer = context->create_buffer(out_shape);
            auto inp_shape_buffer = context->create_buffer(inp_shape);
            auto dst_shape_buffer = context->create_buffer(view.shape_);

            uint32_t out_dim = nmtools::len(out_shape);
            uint32_t inp_dim = nmtools::len(inp_shape);

            uint32_t dst_shape_size = nmtools::len(view.shape_);

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(out_size) / local_size[0])) * local_size[0]};

            auto default_args = nmtools_tuple{out_buffer,inp_buffer,out_shape_buffer,inp_shape_buffer,dst_shape_buffer,out_dim,inp_dim,dst_shape_size};

            context->set_args(kernel,default_args);
            context->run(kernel,out_buffer,output,global_size,local_size);
        }
    };
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS

#undef nmtools_cl_kernel_bin
#undef nmtools_cl_kernel_len
#undef nmtools_cl_ufunc_name
#undef nmtools_cl_ufunc_type
#undef nmtools_cl_kernel_name
#undef nmtools_cl_kernel_name_str

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_BROADCAST_TO_HPP