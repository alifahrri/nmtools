#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_RESIZE_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_RESIZE_HPP

#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/view/pooling.hpp"
#include "nmtools/array/evaluator/opencl/kernel_helper.hpp"
#include "nmtools/array/index/cast.hpp"

#define nmtools_cl_kernel_name(reducer,out_type,inp_type) reducer##_pool2d_##out_type##_##inp_type
#define nmtools_cl_kernel_name_str(reducer,out_type,inp_type) nm_stringify(reducer##_pool2d_##out_type##_##inp_type)

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

namespace nm = nmtools;
namespace na = nmtools::array;
namespace view = nmtools::view;
namespace meta = nmtools::meta;
namespace opencl = nmtools::array::opencl;

#define nmtools_cl_kernel(reducer,out_type,inp_type) \
kernel void nmtools_cl_kernel_name(reducer,out_type,inp_type) \
    ( global out_type* out_ptr \
    , global const inp_type* inp_ptr \
    , global const nm_cl_index_t* out_shape_ptr \
    , global const nm_cl_index_t* inp_shape_ptr \
    , global const nm_cl_index_t* kernel_size_ptr \
    , global const nm_cl_index_t* stride_ptr \
    , const nm_cl_size_t out_dim \
    , const nm_cl_size_t inp_dim \
    , const nm_cl_size_t kernel_size_len \
    , const nm_cl_size_t stride_len \
    , const nm_cl_index_t ceil_mode \
    ) \
{ \
    auto kernel_size = na::create_vector(kernel_size_ptr,kernel_size_len); \
    auto stride      = na::create_vector(stride_ptr,stride_len); \
    auto input       = na::create_array(inp_ptr,inp_shape_ptr,inp_dim); \
    auto output      = na::create_mutable_array(out_ptr,out_shape_ptr,out_dim); \
    auto result      = view::reducer##_pool2d(input,kernel_size,stride,ceil_mode); \
    opencl::assign_array(output,result); \
}

nmtools_cl_kernel(max,float,float)
nmtools_cl_kernel(max,double,double)

// TODO: support avg pooling
// nmtools_cl_kernel(avg,float,float)
// nmtools_cl_kernel(avg,double,double)

#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/array/evaluator/opencl/context.hpp"
#include <cstring> // memcpy

extern unsigned char nm_cl_pooling_spv[];
extern unsigned int nm_cl_pooling_spv_len;

namespace nmtools::array::opencl
{
    template <typename...args_t>
    struct kernel_t<
        view::decorator_t<view::pool2d_t,args_t...>
    > {
        using view_t = view::decorator_t<view::pool2d_t,args_t...>;

        view_t view;
        std::shared_ptr<context_t> context;

        static auto get_spirv()
        {
            using vector = nmtools_list<unsigned char>;
            auto spirv = vector();
            spirv.resize(nm_cl_pooling_spv_len);
            memcpy(spirv.data(),nm_cl_pooling_spv,sizeof(unsigned char)*nm_cl_pooling_spv_len);
            return spirv;
        }

        template <typename inp_t, typename out_t=inp_t>
        static auto kernel_name()
        {
            using reducer_type = typename view_t::reducer_type;
            if constexpr (meta::is_same_v<inp_t,float> && meta::is_same_v<out_t,float> && meta::is_same_v<reducer_type,view::max_reducer_t>) {
                return nmtools_cl_kernel_name_str(max,float,float);
            } else if constexpr (meta::is_same_v<inp_t,float> && meta::is_same_v<out_t,float> && meta::is_same_v<reducer_type,view::avg_reducer_t>) {
                return nmtools_cl_kernel_name_str(avg,float,float);
            } else if constexpr (meta::is_same_v<inp_t,double> && meta::is_same_v<out_t,double> && meta::is_same_v<reducer_type,view::max_reducer_t>) {
                return nmtools_cl_kernel_name_str(max,double,double);
            } else if constexpr (meta::is_same_v<inp_t,double> && meta::is_same_v<out_t,double> && meta::is_same_v<reducer_type,view::avg_reducer_t>) {
                return nmtools_cl_kernel_name_str(avg,double,double);
            }
        }

        template <typename output_t>
        auto eval(output_t& output)
        {
            using out_t = meta::get_element_type_t<output_t>;

            const auto& inp_array = *get_array(view);

            using inp_t = meta::get_element_type_t<decltype(inp_array)>;

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

            auto kernel_size_buffer = context->create_buffer(index::cast<nm_index_t>(view.kernel_size));
            auto stride_buffer = context->create_buffer(index::cast<nm_index_t>(view.stride));

            auto kernel_size_len = nmtools::len(view.kernel_size);
            auto stride_len = nmtools::len(view.stride);
            auto ceil_mode = view.ceil_mode;

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(out_size) / local_size[0])) * local_size[0]};

            auto default_args = nmtools_tuple{
                out_buffer
                , inp_buffer
                , out_shape_buffer
                , inp_shape_buffer
                , kernel_size_buffer
                , stride_buffer
                , (nm_cl_size_t)out_dim
                , (nm_cl_size_t)inp_dim
                , (nm_cl_size_t)kernel_size_len
                , (nm_cl_size_t)stride_len
                , (nm_cl_index_t)ceil_mode
            };

            context->set_args(kernel,default_args);
            context->run(kernel,out_buffer,output,global_size,local_size);
        }
    };
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_RESIZE_HPP