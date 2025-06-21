#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_UFUNC_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/evaluator/opencl/context.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"
#include "nmtools/utility/tuple_cat.hpp"

namespace nmtools::opencl
{
    namespace error
    {
        template <typename...>
        struct UNSUPPORTED_KERNEL_TYPES : meta::detail::fail_t {};
    }

    // CRTP base for opencl kernel bridge
    // The derived types must define the get_spirv, kernel_name functions, and optionally get_fn_attributes
    template <typename cl_kernel_t,typename=void>
    struct base_kernel_t;

    template <template<typename...>typename cl_kernel_t, typename func_t, typename lhs_t, typename rhs_t>
    struct base_kernel_t
        < cl_kernel_t<view::decorator_t<view::ufunc_t,func_t,lhs_t,rhs_t>> >
    {
        // TODO: do not static_assert, tell the caller that such combo is unsupported
        // TODO: do not allow view but allow broadcast

        using view_type = view::decorator_t<view::ufunc_t,func_t,lhs_t,rhs_t>;

        using view_t = view_type;
        using derived_t = cl_kernel_t<view_t>;

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

        template <typename out_t, typename...dtypes_t>
        auto kernel_name(meta::as_value<nmtools_tuple<dtypes_t...>>)
        {
            return self()->template kernel_name<dtypes_t...,out_t>();
        }

        template <typename array_t>
        static auto get_data_types(const array_t&) noexcept
        {
            if constexpr (meta::is_tuple_v<array_t>) {
                return meta::template_reduce<meta::len_v<array_t>>([](auto init, auto index){
                    using init_t  = meta::type_t<decltype(init)>;
                    using array_i = meta::at_t<array_t,index>;
                    using data_t  = meta::get_element_type_t<meta::remove_cvref_pointer_t<array_i>>;
                    using result_t = meta::append_type_t<init_t,data_t>;
                    return meta::as_value_v<result_t>;
                }, meta::as_value_v<nmtools_tuple<>>);
            } else if constexpr (meta::is_pointer_v<array_t>) {
                using data_t = meta::get_element_type_t<meta::remove_cvref_pointer_t<array_t>>;
                return meta::as_value_v<nmtools_tuple<data_t>>;
            }
        }

        template <typename output_t>
        auto eval(output_t& output)
        {
            const auto& inp_array = get_array(view);

            using out_t = meta::get_element_type_t<output_t>;

            std::string kernel_name_ = kernel_name<out_t>(get_data_types(inp_array));
            if (!context->has_kernel(kernel_name_)) {
                context->create_kernel(self()->get_spirv(),kernel_name_);
            }
            auto kernel = context->get_kernel(kernel_name_);

            auto fn_attributes = self()->get_fn_attributes();

            context->run(kernel,fn_attributes,output,inp_array);
        }
    }; // base_kernel_t

    // NOTE: can't unify ufunc kernel bridge yet because of LLVM-Spirv Unsupported instruction: freeze, Invalid Record, etc.. errors :|
    // TODO: unify this kernel bridge with binary ufunc specialization above
    #if 1
    // unary ufuncs
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

            auto left_buffer = context->create_buffer(*nmtools::get<0>(view.array));
            auto out_buffer = context->create_buffer<out_t>(nmtools::size(output));

            std::string kernel_name = self()->template kernel_name<inp_t,out_t>();

            if (!context->has_kernel(kernel_name)) {
                context->create_kernel(self()->get_spirv(),kernel_name);
            }

            auto kernel = context->get_kernel(kernel_name);

            auto out_size = nmtools::size(output);
            auto inp_size = nmtools::size(*nmtools::get<0>(view.array));

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(inp_size) / local_size[0])) * local_size[0]};

            auto fn_attributes = self()->get_fn_attributes();
            auto default_args = nmtools_tuple{out_buffer,left_buffer,out_size,inp_size};
            auto args = utility::tuple_cat(default_args,fn_attributes);

            context->set_args(kernel,args);
            context->run(kernel,out_buffer,output,global_size,local_size);
        }
    }; // kernel_t
    #endif
} // namespace nmtools::opencl

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_UFUNC_HPP