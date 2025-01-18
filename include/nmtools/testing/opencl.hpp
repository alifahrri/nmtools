#ifndef NMTOOLS_TESTING_OPENCL_HPP
#define NMTOOLS_TESTING_OPENCL_HPP

#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/opencl/context.hpp"
#include "nmtools/index/cast.hpp"

#include <cstring>
#include <unordered_map>

#ifndef nm_cl_index_t
using nmtools::int32_t;
#define nm_cl_index_t int32_t
#endif

namespace opencl = nmtools::array::opencl;

namespace nmtools::testing
{
    struct OpenCLTester
    {
        std::string kernel_name = {};

        // arity -> kernel_name
        using arity_kernel_t = std::unordered_map<size_t,std::string>;
        arity_kernel_t arity_overload_kernel;

        nmtools_list<unsigned char> spv_kernel = {};

        static auto pack_spirv(unsigned char* spv_kernel_ptr, unsigned int spv_kernel_len)
        {
            using vector = nmtools_list<unsigned char>;
            auto spirv = vector();
            spirv.resize(spv_kernel_len);
            memcpy(spirv.data(),spv_kernel_ptr,sizeof(unsigned char)*spv_kernel_len);
            return spirv;
        }

        OpenCLTester(const std::string& kernel_name, unsigned char* spv_kernel_ptr, unsigned int spv_kernel_len)
            : kernel_name(kernel_name)
            , spv_kernel(pack_spirv(spv_kernel_ptr, spv_kernel_len))
        {}

        OpenCLTester(const arity_kernel_t& arity_kernels, unsigned char* spv_kernel_ptr, unsigned int spv_kernel_len)
            : arity_overload_kernel(arity_kernels)
            , spv_kernel(pack_spirv(spv_kernel_ptr, spv_kernel_len))
        {}

        template <typename expect_t, typename...args_t>
        auto test(opencl::context_ptr_t context, const expect_t& expect, const args_t&...args)
        {
            using out_t = meta::get_element_or_common_type_t<expect_t>;
            auto out_size = [&](){
                if constexpr (meta::is_num_v<expect_t>) {
                    return 1;
                } else {
                    return nmtools::size(expect);
                }
            }();
            auto out_buffer = context->create_buffer<out_t>(out_size);

            const auto& kernel_name_ = arity_overload_kernel.size() ?
                  arity_overload_kernel.at(sizeof...(args))
                : kernel_name
            ;

            if (!context->has_kernel(kernel_name_)) {
                context->create_kernel(spv_kernel,kernel_name_);
            }

            auto kernel = context->get_kernel(kernel_name_);

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(out_size) / local_size[0])) * local_size[0]};

            using output_t = meta::transform_bounded_array_t<expect_t>;
            auto output = output_t{};
            if constexpr (meta::is_resizable_v<output_t>) {
                output.resize(out_size);
            }

            auto args_pack = nmtools_tuple<const args_t&...>{args...};
            auto [args_cl_buffers,args_cl_sizes] = meta::template_reduce<sizeof...(args)>([&](auto& init, auto index){
                const auto& arg = nmtools::at(args_pack,index);
                const auto [cl_buffers,cl_sizes] = init;
                if constexpr (meta::is_num_v<decltype(arg)>) {
                    auto cl_buffers_ = utility::tuple_append(cl_buffers,arg);
                    return nmtools_tuple{cl_buffers_,cl_sizes};
                } else {
                    auto buffer = context->create_buffer(arg);
                    auto size   = (nm_cl_index_t)nmtools::size(arg);
                    auto cl_buffers_ = utility::tuple_append(cl_buffers,buffer);
                    auto cl_sizes_   = utility::tuple_append(cl_sizes,size);
                    return nmtools_tuple{cl_buffers_,cl_sizes_};
                }
            }, nmtools_tuple{nmtools_tuple<>{},nmtools_tuple<>{}});

            auto cl_buffers = utility::tuple_cat(nmtools_tuple{out_buffer},args_cl_buffers);
            auto cl_sizes = utility::tuple_cat(nmtools_tuple{(nm_cl_index_t)out_size},args_cl_sizes);
            auto cl_args = utility::tuple_cat(cl_buffers,cl_sizes);

            context->set_args(kernel,cl_args);
            context->run(kernel,out_buffer,output,global_size,local_size);

            NMTOOLS_ASSERT_EQUAL(nmtools::shape(output),nmtools::shape(expect));
            NMTOOLS_ASSERT_EQUAL(output,expect);
        }
    };
}
#endif // NMTOOLS_TESTING_OPENCL_HPP