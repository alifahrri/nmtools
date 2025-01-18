#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_WHERE_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_WHERE_HPP

#include "nmtools/ndarray.hpp"
#include "nmtools/array/view/where.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"
#include "nmtools/array/index/cast.hpp"

#define nmtools_cl_kernel_name(out_type,cond_type,x_type,y_type) where_##out_type##_##cond_type##_##x_type##_##y_type
#define nmtools_cl_kernel_name_str(out_type,cond_type,x_type,y_type) nm_stringify(where_##out_type##_##cond_type##_##x_type##_##y_type)

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

namespace nm = nmtools;
namespace na = nmtools::array;
namespace view = nmtools::view;
namespace meta = nmtools::meta;
namespace opencl = nmtools::array::opencl;

#define nmtools_cl_kernel(out_type,cond_type,x_type,y_type) \
kernel void nmtools_cl_kernel_name(out_type,cond_type,x_type,y_type) \
    ( global out_type* out_ptr \
    , global const cond_type* cond_ptr \
    , global const x_type* x_ptr \
    , global const y_type* y_ptr \
    , global const nm_cl_index_t* out_shape_ptr \
    , global const nm_cl_index_t* cond_shape_ptr \
    , global const nm_cl_index_t* x_shape_ptr \
    , global const nm_cl_index_t* y_shape_ptr \
    , const nm_cl_size_t out_dim \
    , const nm_cl_size_t cond_dim \
    , const nm_cl_size_t x_dim \
    , const nm_cl_size_t y_dim \
    ) \
{ \
    auto cond = na::create_array(cond_ptr,cond_shape_ptr,cond_dim); \
    auto x = na::create_array(x_ptr,x_shape_ptr,x_dim); \
    auto y = na::create_array(y_ptr,y_shape_ptr,y_dim); \
    auto output = na::create_mutable_array(out_ptr,out_shape_ptr,out_dim); \
    auto result = view::where(cond,x,y); \
    opencl::assign_array(output,result); \
}

nmtools_cl_kernel(float,int,float,float)
nmtools_cl_kernel(double,int,double,double)

#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/evaluator/opencl/context.hpp"
#include <cstring>

extern unsigned char nm_cl_where_spv[];
extern unsigned int nm_cl_where_spv_len;

namespace nmtools::array::opencl
{
    template <typename...args_t>
    struct kernel_t<
        view::decorator_t<view::where_t,args_t...>
    > {
        using view_t = view::decorator_t<view::where_t,args_t...>;

        view_t view;
        std::shared_ptr<context_t> context;

        static auto get_spirv()
        {
            using vector = nmtools_list<unsigned char>;
            auto spirv = vector();
            spirv.resize(nm_cl_where_spv_len);
            memcpy(spirv.data(),nm_cl_where_spv,sizeof(unsigned char)*nm_cl_where_spv_len);
            return spirv;
        }

        template <typename cond_t, typename x_t, typename y_t, typename out_t=cond_t>
        static auto kernel_name()
        {
            if constexpr (
                meta::is_same_v<cond_t,int>
                && meta::is_same_v<x_t,float>
                && meta::is_same_v<y_t,float>
                && meta::is_same_v<out_t,float>
            ) {
                return nmtools_cl_kernel_name_str(float,int,float,float);
            } else if constexpr (
                meta::is_same_v<cond_t,int>
                && meta::is_same_v<x_t,double>
                && meta::is_same_v<y_t,double>
                && meta::is_same_v<out_t,double>
            ) {
                return nmtools_cl_kernel_name_str(double,int,double,double);
            }
        }

        template <typename output_t>
        auto eval(output_t& output)
        {
            using out_t = meta::get_element_type_t<output_t>;

            const auto& operands = get_array(view);
            const auto& cond_array = *nmtools::get<0>(operands);
            const auto& x_array = *nmtools::get<1>(operands);
            const auto& y_array = *nmtools::get<2>(operands);

            using cond_t = meta::get_element_type_t<meta::remove_cvref_pointer_t<decltype(cond_array)>>;
            using x_t = meta::get_element_type_t<meta::remove_cvref_pointer_t<decltype(x_array)>>;
            using y_t = meta::get_element_type_t<meta::remove_cvref_pointer_t<decltype(y_array)>>;

            auto cond_buffer = context->create_buffer(cond_array);
            auto x_buffer = context->create_buffer(x_array);
            auto y_buffer = context->create_buffer(y_array);
            auto out_buffer = context->create_buffer<out_t>(nmtools::size(output));

            auto kernel_name = this->kernel_name<cond_t,x_t,y_t,out_t>();

            if (!context->has_kernel(kernel_name)) {
                context->create_kernel(get_spirv(),kernel_name);
            }

            auto kernel = context->get_kernel(kernel_name);

            auto out_size = nmtools::size(output);
            [[maybe_unused]] auto inp_size = nmtools::size(cond_array);

            auto out_shape  = nmtools::shape(output);
            auto cond_shape = nmtools::shape(cond_array);
            auto x_shape    = nmtools::shape(x_array);
            auto y_shape    = nmtools::shape(y_array);

            auto out_shape_buffer = context->create_buffer(index::cast<nm_cl_index_t>(out_shape));
            auto cond_shape_buffer = context->create_buffer(index::cast<nm_cl_index_t>(cond_shape));
            auto x_shape_buffer = context->create_buffer(index::cast<nm_cl_index_t>(x_shape));
            auto y_shape_buffer = context->create_buffer(index::cast<nm_cl_index_t>(y_shape));

            auto out_dim = nmtools::len(out_shape);
            auto cond_dim = nmtools::len(cond_shape);
            auto x_dim = nmtools::len(x_shape);
            auto y_dim = nmtools::len(y_shape);

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(out_size) / local_size[0])) * local_size[0]};

            auto default_args = nmtools_tuple{
                out_buffer
                , cond_buffer
                , x_buffer
                , y_buffer
                , out_shape_buffer
                , cond_shape_buffer
                , x_shape_buffer
                , y_shape_buffer
                , (nm_cl_size_t)out_dim
                , (nm_cl_size_t)cond_dim
                , (nm_cl_size_t)x_dim
                , (nm_cl_size_t)y_dim
            };

            context->set_args(kernel,default_args);
            context->run(kernel,out_buffer,output,global_size,local_size);
        }
    };
}
#endif // NMTOOLS_OPENCL_BUILD_KERNELS

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_KERNELS_WHERE_HPP