#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_UFUNC_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/eval/opencl/context.hpp"
#include "nmtools/array/view/ufunc/ufunc.hpp"
#include "nmtools/utility/tuple_cat.hpp"

namespace nmtools::array::opencl
{
    template <typename cl_kernel_t>
    struct base_kernel_t;

    template <template<typename...>typename cl_kernel_t,typename array_t, typename func_t>
    struct base_kernel_t
        < cl_kernel_t<view::decorator_t<view::ufunc_t,func_t,array_t>> >
    {
        // TODO: do not static_assert, tell the caller that such combo is unsupported
        static_assert( meta::is_ndarray_v<array_t> && !meta::is_view_v<array_t> );

        using view_t = view::decorator_t<view::ufunc_t,func_t,array_t>;
        using derived_t = cl_kernel_t<view::decorator_t<view::ufunc_t,func_t,array_t>>;

        view_t view;
        std::shared_ptr<context_t> context;

        derived_t* self()
        {
            return static_cast<derived_t*>(this);
        }

        const derived_t* self() const
        {
            return static_cast<const derived_t*>(this);
        }

        auto get_fn_attributes()
        {
            return nmtools_tuple{};
        }

        template <typename output_t>
        auto eval(output_t& output)
        {
            using out_t = meta::get_element_type_t<output_t>;
            using inp_t = meta::get_element_type_t<view_t>;

            auto inp_buffer = context->create_buffer(*nmtools::get<0>(view.operands));
            auto out_buffer = context->create_buffer<out_t>(nmtools::size(output));

            std::string kernel_name = self()->template kernel_name<inp_t,out_t>();

            if (!context->has_kernel(kernel_name)) {
                context->create_kernel(self()->get_spirv(),kernel_name);
            }

            auto kernel = context->get_kernel(kernel_name);

            auto out_size = nmtools::size(output);
            auto inp_size = nmtools::size(*nmtools::get<0>(view.operands));

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(inp_size) / local_size[0])) * local_size[0]};

            auto fn_attributes = self()->get_fn_attributes();
            auto default_args = nmtools_tuple{out_buffer,inp_buffer,out_size,inp_size};
            auto args = utility::tuple_cat(default_args,fn_attributes);

            context->set_args(kernel,args);
            context->run(kernel,out_buffer,output,global_size,local_size);
        }
    }; // kernel_t
} // namespace nmtools::array::opencl

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_UFUNC_HPP