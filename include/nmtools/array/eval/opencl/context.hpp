#ifndef NMTOOLS_ARRAY_EVAL_OPENCL_CONTEXT_HPP
#define NMTOOLS_ARRAY_EVAL_OPENCL_CONTEXT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/data.hpp"

#include <CL/cl.h>
// for CL_PLATFORM_ICD_SUFFIX_KHR
#include <CL/cl_ext.h>

#include <memory>
#include <mutex>
#include <unordered_map>
#include <shared_mutex>
#include <iostream>

namespace nmtools::array::opencl
{
    struct buffer_deleter_t
    {
        void operator()(cl_mem* ptr) const
        {
            [[maybe_unused]] cl_int ret = clReleaseMemObject(*ptr);
            delete ptr;
        }
    };

    struct kernel_deleter_t
    {
        void operator()(cl_kernel* ptr) const
        {
            [[maybe_unused]] cl_int ret = clReleaseKernel(*ptr);
            delete ptr;
        }
    };

    struct program_deleter_t
    {
        void operator()(cl_program* ptr) const
        {
            [[maybe_unused]] cl_int ret = clReleaseProgram(*ptr);
            delete ptr;
        }
    };

    template <typename T, typename key_t=std::string>
    struct registry_t
    {
        public:
        auto add(const std::string& key, T t)
        {
            std::unique_lock lock{mutex};
            if (!registry.count(key)) {
                registry[key] = t;
            }
        }
        auto at(const std::string& key)
        {
            std::shared_lock lock{mutex};
            return registry.at(key);
        }
        bool has(const std::string& key)
        {
            std::shared_lock lock{mutex};
            return registry.count(key);
        }
        registry_t() {}
        protected:
        std::shared_mutex mutex;
        std::unordered_map<key_t,T> registry;
    };

    #define CL_ERROR_MESSAGE_RETURN_STR(status) \
    case status: \
        return #status;

    inline auto error_message(cl_int status) -> std::string
    {
        switch (status) {
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_VALUE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_OUT_OF_HOST_MEMORY);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_PLATFORM);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_DEVICE_TYPE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_DEVICE_NOT_FOUND);
            CL_ERROR_MESSAGE_RETURN_STR(CL_OUT_OF_RESOURCES);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_PROPERTY);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_DEVICE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_DEVICE_NOT_AVAILABLE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_CONTEXT);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_QUEUE_PROPERTIES);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_BUFFER_SIZE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_HOST_PTR);
            CL_ERROR_MESSAGE_RETURN_STR(CL_MEM_OBJECT_ALLOCATION_FAILURE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_COMMAND_QUEUE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_MEM_OBJECT);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_EVENT_WAIT_LIST);
            CL_ERROR_MESSAGE_RETURN_STR(CL_MISALIGNED_SUB_BUFFER_OFFSET);
            CL_ERROR_MESSAGE_RETURN_STR(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_OPERATION);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_PROGRAM);
            CL_ERROR_MESSAGE_RETURN_STR(CL_BUILD_PROGRAM_FAILURE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_BINARY);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_BUILD_OPTIONS);
            CL_ERROR_MESSAGE_RETURN_STR(CL_COMPILER_NOT_AVAILABLE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_SPEC_ID);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_PROGRAM_EXECUTABLE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_KERNEL_NAME);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_KERNEL_DEFINITION);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_KERNEL);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_KERNEL_ARGS);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_WORK_DIMENSION);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_GLOBAL_WORK_SIZE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_GLOBAL_OFFSET);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_WORK_GROUP_SIZE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_WORK_ITEM_SIZE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_IMAGE_SIZE);
            CL_ERROR_MESSAGE_RETURN_STR(CL_IMAGE_FORMAT_NOT_SUPPORTED);
            CL_ERROR_MESSAGE_RETURN_STR(CL_INVALID_EVENT);
            default:
                return "UNKNOWN_ERROR (" + std::to_string(status) + ")";
        }
    }
    #undef CL_ERROR_MESSAGE_RETURN_STR

    class cl_exception : public std::runtime_error
    {
        cl_int status_;
        public:
        cl_exception(cl_int status, const std::string& message)
            : std::runtime_error(message)
            , status_(status)
        {}

        inline auto status() const
        {
            return status_;
        }
    };

    #ifndef nmtools_cl_check_error
    #define nmtools_cl_check_error(status, function) \
    if (status != CL_SUCCESS) { \
        throw cl_exception(status, "Got error: " + error_message(status) + " when " + function); \
    }
    #endif // nmtools_cl_check_error

    struct platform_info_t
    {
        std::string profile;
        std::string version;
        std::string name;
        std::string vendor;
        std::string extensions;
        std::string icd_suffix;
    };

    inline auto get_platform_infos()
    {
        auto platform_ids  = std::vector<cl_platform_id>();
        cl_int ret;
        cl_uint ret_num_platforms;
        ret = clGetPlatformIDs(0, NULL, &ret_num_platforms);
        nmtools_cl_check_error( ret, "getting the number of platform ids (clGetPlatformIDs)" );
        platform_ids.resize(ret_num_platforms);

        ret = clGetPlatformIDs(ret_num_platforms, platform_ids.data(), &ret_num_platforms);
        nmtools_cl_check_error( ret, "reading platform ids (clGetPlatformIDs)" );

        // cl_platform_id platform_id = platform_ids.at(platform_idx);

        auto platform_infos = std::vector<platform_info_t>();
        // fill-in platform info
        for (const auto& platform_id : platform_ids)
        {
            platform_infos.push_back({});
            auto& platform_info = platform_infos.back();
            size_t param_value_size_ret;

            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_PROFILE, 0, NULL, &param_value_size_ret);
            nmtools_cl_check_error( ret, "getting the size of platform profile (clGetPlatformInfo)" );
            auto& profile = platform_info.profile;
            profile.resize(param_value_size_ret);
            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_PROFILE, param_value_size_ret, profile.data(), &param_value_size_ret);
            nmtools_cl_check_error( ret, "reading platform profile (clGetPlatformInfo)" );

            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION, 0, NULL, &param_value_size_ret);
            nmtools_cl_check_error( ret, "getting the size of platform version (clGetPlatformInfo)" );
            auto& version = platform_info.version;
            version.resize(param_value_size_ret);
            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION, param_value_size_ret, version.data(), &param_value_size_ret);
            nmtools_cl_check_error( ret, "reading platform version (clGetPlatformInfo)" );

            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 0, NULL, &param_value_size_ret);
            nmtools_cl_check_error( ret, "getting the size of platform name (clGetPlatformInfo)" );
            auto& name = platform_info.name;
            name.resize(param_value_size_ret);
            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, param_value_size_ret, name.data(), &param_value_size_ret);
            nmtools_cl_check_error( ret, "reading platform version (clGetPlatformInfo)" );

            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_VENDOR, 0, NULL, &param_value_size_ret);
            nmtools_cl_check_error( ret, "getting the size of platform name (clGetPlatformInfo)" );
            auto& vendor = platform_info.vendor;
            vendor.resize(param_value_size_ret);
            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_VENDOR, param_value_size_ret, vendor.data(), &param_value_size_ret);
            nmtools_cl_check_error( ret, "reading platform vendor (clGetPlatformInfo)" );

            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_EXTENSIONS, 0, NULL, &param_value_size_ret);
            nmtools_cl_check_error( ret, "getting the size of platform extensions (clGetPlatformInfo)" );
            auto& extensions = platform_info.extensions;
            extensions.resize(param_value_size_ret);
            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_EXTENSIONS, param_value_size_ret, extensions.data(), &param_value_size_ret);
            nmtools_cl_check_error( ret, "reading platform vendor (clGetPlatformInfo)" );

            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_ICD_SUFFIX_KHR, 0, NULL, &param_value_size_ret);
            nmtools_cl_check_error( ret, "getting the size of platform extensions (clGetPlatformInfo)" );
            auto& icd_suffix = platform_info.icd_suffix;
            icd_suffix.resize(param_value_size_ret);
            ret = clGetPlatformInfo(platform_id, CL_PLATFORM_ICD_SUFFIX_KHR, param_value_size_ret, icd_suffix.data(), &param_value_size_ret);
            nmtools_cl_check_error( ret, "reading platform vendor (clGetPlatformInfo)" );
        }

        return platform_infos;
    }

    using cl_mem_ptr_t = std::shared_ptr<cl_mem>;

    struct context_t
    {
        struct kernel_info_t
        {
            nmtools_array<size_t,3> global_work_size;
            nmtools_array<size_t,3> compile_work_group_size;
            size_t work_group_size;
            size_t local_mem_size;
            size_t preferred_work_group_size_multiple;
            size_t private_mem_size;
        };
        struct kernel_t
        {
            std::shared_ptr<cl_kernel> kernel_;
            std::shared_ptr<kernel_info_t> kernel_info_;
        };
        using kernel_registry  = registry_t<kernel_t>;
        using program_registry = registry_t<std::shared_ptr<cl_program>>;

        kernel_registry kernel_registry_;
        program_registry program_registry_;

        cl_device_id device_id;
        cl_platform_id platform_id;
        cl_context context;
        cl_command_queue command_queue;

        context_t(size_t platform_idx=0)
        {
            // Get platform and device information
            device_id = NULL;
            cl_uint ret_num_devices, ret_num_platforms;

            // TODO: handle case: platform_idx >= max_platform / ret_num_platform
            constexpr auto max_platforms = 3;
            auto platform_ids  = std::vector<cl_platform_id>();
            cl_int ret;
            ret = clGetPlatformIDs(max_platforms, NULL, &ret_num_platforms);
            nmtools_cl_check_error( ret, "getting the number of platform ids (clGetPlatformIDs)" );
            platform_ids.resize(ret_num_platforms);

            ret = clGetPlatformIDs(max_platforms, platform_ids.data(), &ret_num_platforms);
            nmtools_cl_check_error( ret, "reading platform ids (clGetPlatformIDs)" );
            cl_platform_id platform_id = platform_ids.at(platform_idx);

            ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
            nmtools_cl_check_error( ret, "reading device ids (clGetDeviceIDs)" );
            context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
            nmtools_cl_check_error( ret, "creating context (clCreateContext)" );
            command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
            nmtools_cl_check_error( ret, "creating command queue (clCreateCommandQueue)" );
        }

        template <typename T>
        auto create_buffer(const T* data_ptr, size_t n)
        {
            cl_int ret;
            auto mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(T), NULL, &ret);
            nmtools_cl_check_error( ret, "creating buffer (clCreateBuffer)" );
            ret = clEnqueueWriteBuffer(command_queue, mem_obj, CL_TRUE, 0, n * sizeof(int), data_ptr, 0, NULL, NULL);
            nmtools_cl_check_error( ret, "enqueueing write buffer (clEnqueueWriteBuffer)" );
            auto shared_mem_obj = cl_mem_ptr_t(new cl_mem(mem_obj), buffer_deleter_t());
            return shared_mem_obj;
        }

        template <typename T>
        auto create_buffer(size_t n)
        {
            cl_int ret;
            auto mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(T), NULL, &ret);
            nmtools_cl_check_error( ret, "creating buffer (clCreateBuffer)" );
            auto shared_mem_obj = cl_mem_ptr_t(new cl_mem(mem_obj), buffer_deleter_t());
            return shared_mem_obj;
        }

        template <typename array_t>
        auto create_buffer(const array_t& array)
            -> meta::enable_if_t<(meta::is_ndarray_v<array_t> || meta::is_num_v<array_t>) && !meta::is_view_v<array_t>, cl_mem_ptr_t>
        {
            if constexpr (meta::is_ndarray_v<array_t>) {
                return create_buffer(nmtools::data(array),nmtools::size(array));
            } else {
                return create_buffer(&array,1);
            }
        }

        template <typename array_t>
        auto copy_buffer(cl_mem_ptr_t mem_obj, array_t& array)
            -> meta::enable_if_t<(meta::is_num_v<array_t> || meta::is_ndarray_v<array_t>) && !meta::is_view_v<array_t>, bool>
        {
            using element_t = meta::get_element_type_t<array_t>;

            auto byte_size = [&](){
                if constexpr (meta::is_ndarray_v<array_t>) {
                    return nmtools::size(array) * sizeof(element_t);
                } else {
                    return sizeof(element_t);
                }
            }();
            auto out_ptr = [&](){
                if constexpr (meta::is_ndarray_v<array_t>) {
                    return nmtools::data(array);
                } else {
                    return &array;
                }
            }();

            auto ret = clEnqueueReadBuffer(command_queue, *mem_obj, CL_TRUE, 0, byte_size, out_ptr, 0, NULL, NULL);
            return ret;
        }

        inline auto create_kernel(const std::vector<unsigned char>& spirv, const std::string& kernel_name)
        {
            cl_int ret;
            auto program = clCreateProgramWithIL(context,spirv.data(),spirv.size(),&ret);
            nmtools_cl_check_error( ret, "creating program with IL (clCreateProgramWithIL)" );
            ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);
            if (ret != CL_SUCCESS) {
                auto build_log = std::string();
                auto build_log_ret_size = 0ul;
                cl_int m_ret;
                m_ret = clGetProgramBuildInfo(program,device_id,CL_PROGRAM_BUILD_LOG,0,NULL,&build_log_ret_size);
                nmtools_cl_check_error( m_ret, "trying to get build log from build failure (" + error_message(ret) + ") (clGetProgramBuildInfo)" );
                build_log.resize(build_log_ret_size);
                m_ret = clGetProgramBuildInfo(program,device_id,CL_PROGRAM_BUILD_LOG,build_log_ret_size,(void*)build_log.data(),NULL);
                nmtools_cl_check_error( m_ret, "trying to get build log from build failure (" + error_message(ret) + ") (clGetProgramBuildInfo)" );
                auto message = "building program (clBuildProgram); build log (" + std::to_string(build_log_ret_size) + "): " + build_log;
                nmtools_cl_check_error( ret, message );
            }
            auto kernel = clCreateKernel(program,kernel_name.c_str(),&ret);
            nmtools_cl_check_error( ret, "creating kernel (clCreateKernel)" );
            auto shared_program = std::shared_ptr<cl_program>(new cl_program(program),program_deleter_t());
            auto shared_kernel  = std::shared_ptr<cl_kernel>(new cl_kernel(kernel),kernel_deleter_t());
            auto kernel_info    = std::make_shared<kernel_info_t>();
            // TODO: make this optional?
            // get kernel info
            {
                // ret = clGetKernelWorkGroupInfo(kernel,device_id,CL_KERNEL_GLOBAL_WORK_SIZE,sizeof(size_t)*3,kernel_info->global_work_size.data(),NULL);
                // nmtools_cl_check_error( ret, "querying kernel info: CL_KERNEL_GLOBAL_WORK_SIZE (clGetKernelWorkGroupInfo)" );
                // ret = clGetKernelWorkGroupInfo(kernel,device_id,CL_KERNEL_COMPILE_WORK_GROUP_SIZE,sizeof(size_t),kernel_info->compile_work_group_size.data(),NULL);
                // nmtools_cl_check_error( ret, "querying kernel info: CL_KERNEL_COMPILE_WORK_GROUP_SIZE (clGetKernelWorkGroupInfo)" );

                ret = clGetKernelWorkGroupInfo(kernel,device_id,CL_KERNEL_WORK_GROUP_SIZE,sizeof(size_t),&kernel_info->work_group_size,NULL);
                nmtools_cl_check_error( ret, "querying kernel info: CL_KERNEL_WORK_GROUP_SIZE (clGetKernelWorkGroupInfo)" );
                ret = clGetKernelWorkGroupInfo(kernel,device_id,CL_KERNEL_LOCAL_MEM_SIZE,sizeof(size_t),&kernel_info->local_mem_size,NULL);
                nmtools_cl_check_error( ret, "querying kernel info: CL_KERNEL_LOCAL_MEM_SIZE (clGetKernelWorkGroupInfo)" );
                ret = clGetKernelWorkGroupInfo(kernel,device_id,CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,sizeof(size_t),&kernel_info->preferred_work_group_size_multiple,NULL);
                nmtools_cl_check_error( ret, "querying kernel info: CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE (clGetKernelWorkGroupInfo)" );
                ret = clGetKernelWorkGroupInfo(kernel,device_id,CL_KERNEL_PRIVATE_MEM_SIZE,sizeof(size_t),&kernel_info->private_mem_size,NULL);
                nmtools_cl_check_error( ret, "querying kernel info: CL_KERNEL_PRIVATE_MEM_SIZE (clGetKernelWorkGroupInfo)" );
            }
            program_registry_.add(kernel_name,shared_program);
            kernel_registry_.add(kernel_name,{shared_kernel,kernel_info});
            return shared_kernel;
        }

        template <typename global_size_t, typename local_size_t>
        auto enqueue_kernel(std::shared_ptr<cl_kernel> kernel, const global_size_t& global_size, const local_size_t& local_size)
        {
            static_assert( meta::is_index_array_v<global_size_t> && meta::is_index_array_v<local_size_t> );
            cl_int ret;
            auto work_dim = len(global_size);
            auto global_work_size = nmtools::data(global_size);
            auto local_work_size  = nmtools::data(local_size);
            ret = clEnqueueNDRangeKernel(command_queue, *kernel, work_dim, NULL, global_work_size, local_work_size, 0, NULL, NULL);
            return ret;
        }

        template <typename...args_t>
        auto set_args(std::shared_ptr<cl_kernel> kernel, nmtools_tuple<args_t...> args_pack)
        {
            meta::template_for<sizeof...(args_t)>([&](auto index){
                constexpr auto I = size_t(index);
                auto arg_i = nmtools::get<I>(args_pack);
                using arg_t = meta::remove_cvref_t<decltype(arg_i)>;
                if constexpr (meta::is_same_v<arg_t,cl_mem_ptr_t>) {
                    auto ret = clSetKernelArg(*kernel,I,sizeof(cl_mem),arg_i.get());
                    auto message = std::string("setting kernel arg #") + std::to_string(I);
                    nmtools_cl_check_error( ret, message );
                } else {
                    auto ret = clSetKernelArg(*kernel,I,sizeof(arg_t),&arg_i);
                    auto message = std::string("setting kernel arg #") + std::to_string(I);
                    nmtools_cl_check_error( ret, message );
                }
            });
        }

        template <typename...args_t>
        auto set_args(kernel_t kernel, nmtools_tuple<args_t...> args_pack)
        {
            this->set_args(kernel.kernel_,args_pack);
        }

        template <typename array_t, typename global_size_t, typename local_size_t>
        auto run(std::shared_ptr<cl_kernel> kernel, cl_mem_ptr_t out_buffer, array_t& output, const global_size_t& global_size, const local_size_t& local_size)
        {
            cl_int ret;
            ret = enqueue_kernel(kernel,global_size,local_size);
            nmtools_cl_check_error( ret, "enqueueing kernel" );

            ret = copy_buffer(out_buffer,output);
            nmtools_cl_check_error( ret, "copying buffer" );
        }

        template <typename output_array_t, typename fn_attributes_t, typename arg0_t, typename...args_t>
        auto run(kernel_t kernel, const fn_attributes_t& fn_attributes, output_array_t& output, const arg0_t& arg0, const args_t&...args)
        {
            auto args_pack = [&](){
                if constexpr (meta::is_tuple_v<arg0_t>) {
                    static_assert( sizeof...(args_t) == 0, "nmtools error" );
                    return static_cast<const arg0_t&>(arg0);
                } else {
                    return nmtools_tuple<const arg0_t&, const args_t&...>{arg0, args...};
                }
            }();

            using kernel_size_t = uint32_t;
            
            using out_t = meta::get_element_type_t<output_array_t>;

            auto out_buffer       = this->create_buffer<out_t>(nmtools::size(output));
            auto out_shape_buffer = this->create_buffer(nmtools::shape(output));

            auto out_dim  = nmtools::dim(output);
            auto out_size = nmtools::size(output);

            constexpr auto N = meta::len_v<decltype(args_pack)>;
            auto dev_args_pack = meta::template_reduce<N>([&](auto init, auto index){
                auto buffer_pack = nmtools::get<0>(init);
                auto shape_pack  = nmtools::get<1>(init);
                auto dim_pack    = nmtools::get<2>(init);

                const auto& arg_i = *nmtools::get<index>(args_pack);

                auto arg_shape = nmtools::shape(arg_i);
                auto arg_dim   = nmtools::len(arg_shape);

                auto dev_buffer = this->create_buffer(arg_i);
                auto dev_shape  = this->create_buffer(arg_shape);

                auto ret_buffer_pack = utility::tuple_append(buffer_pack,dev_buffer);
                auto ret_shape_pack  = utility::tuple_append(shape_pack,dev_shape);
                auto ret_dim_pack    = utility::tuple_append(dim_pack,(kernel_size_t)arg_dim);

                return nmtools_tuple{ret_buffer_pack,ret_shape_pack,ret_dim_pack};
            }, nmtools_tuple{nmtools_tuple{out_buffer},nmtools_tuple{out_shape_buffer},nmtools_tuple{(kernel_size_t)out_dim}});

            auto kernel_info = kernel.kernel_info_;
            auto local_size  = nmtools_array{kernel_info->preferred_work_group_size_multiple};
            auto global_size = nmtools_array{size_t(std::ceil(float(out_size) / local_size[0])) * local_size[0]};

            auto buffer_pack = nmtools::get<0>(dev_args_pack);
            auto shape_pack  = nmtools::get<1>(dev_args_pack);
            auto dim_pack    = nmtools::get<2>(dev_args_pack);
            auto cl_args_pack = utility::tuple_cat(utility::tuple_cat(buffer_pack,utility::tuple_cat(shape_pack,dim_pack)),fn_attributes);
            this->set_args(kernel,cl_args_pack);
            this->run(kernel,out_buffer,output,global_size,local_size);
        }

        template <typename array_t, typename out_buffer_t, typename global_size_t, typename local_size_t>
        auto run(kernel_t kernel, out_buffer_t out_buffer, array_t& output, const global_size_t& global_size, const local_size_t& local_size)
        {
            this->run(kernel.kernel_,out_buffer,output,global_size,local_size);
        }

        inline auto has_kernel(const std::string& kernel_name)
        {
            return kernel_registry_.has(kernel_name);   
        }

        inline auto get_kernel(const std::string& kernel_name)
        {
            return kernel_registry_.at(kernel_name);
        }

        ~context_t()
        {
            [[maybe_unused]] cl_int ret;
            ret = clFlush(command_queue);
            ret = clFinish(command_queue);
            ret = clReleaseCommandQueue(command_queue);
            ret = clReleaseContext(context);
        }
    };

    using context_ptr_t = std::shared_ptr<context_t>;

    inline auto default_context()
    {
        static context_ptr_t default_context;
        if (!default_context) {
            auto platform_idx = 0ul;
            if (auto env_idx = std::getenv("NMTOOLS_OPENCL_DEFAULT_PLATFORM_IDX")) {
                platform_idx = std::stoi(env_idx);
            }
            if (auto env_debug = std::getenv("NMTOOLS_OPENCL_DEBUG")) {
                auto enable_debug = true;
                try {
                    enable_debug = std::stoi(env_debug);
                } catch (std::invalid_argument&) {}
                if (enable_debug) {
                    auto platform_infos = get_platform_infos();
                    std::cout << "[nmtools opencl] Number of OpenCL platforms: " << platform_infos.size() << "\n";
                    for (size_t i=0; i<platform_infos.size(); i++) {
                        const auto& platform_info = platform_infos.at(i);
                        std::cout << "[nmtools opencl] platform id: "   << i << "\n";
                        std::cout << "[nmtools opencl] name:\t"         << platform_info.name << "\n";
                        std::cout << "[nmtools opencl] icd_suffix:\t"   << platform_info.icd_suffix << "\n";
                        std::cout << "[nmtools opencl] profile:\t"      << platform_info.profile << "\n";
                        std::cout << "[nmtools opencl] version:\t"      << platform_info.version << "\n";
                        std::cout << "[nmtools opencl] vendor:\t"       << platform_info.vendor << "\n";
                        std::cout << "[nmtools opencl] extensions:\t"   << platform_info.extensions << "\n";
                    }
                    std::cout << "[nmtools opencl] default context using platform #" << platform_idx << "\n";
                }
            }
            default_context = std::make_shared<context_t>(platform_idx);
        }
        return default_context;
    }

    template <typename view_t>
    struct kernel_t;
} // namespace nmtools::array::opencl

#endif // NMTOOLS_ARRAY_EVAL_OPENCL_CONTEXT_HPP