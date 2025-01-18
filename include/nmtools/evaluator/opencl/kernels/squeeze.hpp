#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_SQUEEZE_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_SQUEEZE_HPP

#include "nmtools/ndarray.hpp"
#include "nmtools/array/view/squeeze.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"
#include "nmtools/array/index/cast.hpp"

#define nmtools_cl_kernel_name(out_type,inp_type) squeeze_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(out_type,inp_type) nm_stringify(squeeze_##out_type##_##inp_type)

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

namespace nm = nmtools;
namespace na = nmtools::array;
namespace view = nmtools::view;
namespace meta = nmtools::meta;
namespace opencl = nmtools::array::opencl;

#define nmtools_cl_kernel(out_type,inp_type) \
kernel void nmtools_cl_kernel_name(out_type,inp_type) \
    ( global out_type* out_ptr \
    , global const inp_type* inp_ptr \
    , global const nm_cl_index_t* out_shape_ptr \
    , global const nm_cl_index_t* inp_shape_ptr \
    , const nm_cl_size_t out_dim \
    , const nm_cl_size_t inp_dim \
    ) \
{ \
    auto input = na::create_array(inp_ptr,inp_shape_ptr,inp_dim); \
    auto output = na::create_mutable_array(out_ptr,out_shape_ptr,out_dim); \
    auto result = view::squeeze(input); \
    opencl::assign_array(output,result); \
}

nmtools_cl_kernel(float,float)
nmtools_cl_kernel(double,double)

#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/evaluator/opencl/context.hpp"
#include <cstring>

extern unsigned char nm_cl_squeeze_spv[];
extern unsigned int nm_cl_squeeze_spv_len;

namespace nmtools::array::opencl
{
    template <typename...args_t>
    struct kernel_t<
        view::decorator_t<view::squeeze_t,args_t...>
    > {
        using view_t = view::decorator_t<view::squeeze_t,args_t...>;

        view_t view;
        std::shared_ptr<context_t> context;

        static auto get_spirv()
        {
            using vector = nmtools_list<unsigned char>;
            auto spirv = vector();
            spirv.resize(nm_cl_squeeze_spv_len);
            memcpy(spirv.data(),nm_cl_squeeze_spv,sizeof(unsigned char)*nm_cl_squeeze_spv_len);
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

            auto out_shape = nmtools::shape(output);
            auto inp_shape = nmtools::shape(inp_array);

            auto out_shape_buffer = context->create_buffer(index::cast<nm_cl_index_t>(out_shape));
            auto inp_shape_buffer = context->create_buffer(index::cast<nm_cl_index_t>(inp_shape));

            auto out_dim = nmtools::len(out_shape);
            auto inp_dim = nmtools::len(inp_shape);

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(out_size) / local_size[0])) * local_size[0]};

            auto default_args = nmtools_tuple{
                out_buffer
                , inp_buffer
                , out_shape_buffer
                , inp_shape_buffer
                , (nm_cl_size_t)out_dim
                , (nm_cl_size_t)inp_dim
            };

            context->set_args(kernel,default_args);
            context->run(kernel,out_buffer,output,global_size,local_size);
        }
    };
}
#endif // NMTOOLS_OPENCL_BUILD_KERNELS

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_SQUEEZE_HPP