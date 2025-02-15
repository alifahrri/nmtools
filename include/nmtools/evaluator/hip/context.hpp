#ifndef NMTOOLS_ARRAY_EVAL_HIP_CONTEXT_HPP
#define NMTOOLS_ARRAY_EVAL_HIP_CONTEXT_HPP

#include "nmtools/exception.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/evaluator/kernel_helper.hpp"
#include "nmtools/utility/tuple_cat.hpp"

#include <hip/hip_runtime.h>

#include <memory>
#include <iostream>

template <auto out_static_dim=0, typename function_t
    , typename out_t, typename out_shape_t, typename out_dim_t
    , template<typename...>typename tuple
    , typename...operands_t
>
__global__ void nm_hip_run_function(const function_t fun
    , out_t *out, const out_shape_t* out_shape_ptr, const out_dim_t out_dim
    , const tuple<operands_t...> operands
) {
    namespace meta = nmtools::meta;
    namespace na = nmtools::array;
    namespace fn = nmtools::functional;
    auto output = na::create_mutable_array<out_static_dim>(out,out_shape_ptr,out_dim);
    auto result = fn::apply(fun,operands);
    // TODO: properly get the thread & kernel id and shape
    auto thread_id  = na::kernel_size<size_t>{threadIdx.x,0,0};
    auto block_id   = na::kernel_size<size_t>{blockIdx.x,0,0};
    auto block_size = na::kernel_size<size_t>{blockDim.x,1,1};
    na::assign_result(output,result,thread_id,block_id,block_size);
}

namespace nmtools::array
{
    class hip_exception : public ::nmtools::exception
    {
        public:
        hip_exception(hipError_t status, const std::string& message)
            : nmtools::exception(message + " (" + std::to_string(static_cast<int>(status)) + "): " + hipGetErrorString(status))
            , status_(status)
        {}

        inline auto status() const
        {
            return status_;
        }

        protected:
        hipError_t status_;
    };
}

namespace nmtools::array::hip
{
    // TODO: move to nmtools::meta namespace
    namespace helper
    {
        template <typename T>
        struct is_shared_ptr : meta::false_type {};

        template <typename T>
        struct is_shared_ptr<std::shared_ptr<T>> : meta::true_type {};

        template <typename T>
        struct is_shared_ptr<const T> : is_shared_ptr<T> {};

        template <typename T>
        struct is_shared_ptr<T&> : is_shared_ptr<T> {};

        template <typename T>
        constexpr inline auto is_shared_ptr_v = is_shared_ptr<T>::value;
    }

    template <typename T>
    struct buffer_deleter_t
    {
        void operator()(T* ptr) const
        {
            auto status = hipFree(ptr);
            if (status != hipSuccess) {
                throw hip_exception(status, "error when freeing device memory");
            }
        }
    };

    template <typename array_t>
    struct array_deleter_t
    {
        void operator()(array_t* array_ptr) const
        {
            auto status = hipFree(array_ptr->data_);
            if (status != hipSuccess) {
                throw hip_exception(status, "error when freeing device memory");
            }
        }
    };

    template <typename T>
    using device_mem_ptr = std::shared_ptr<T>;

    struct context_t
    {
        // TODO: use hip stream?
        context_t([[maybe_unused]] size_t gpu_id=0) {}

        template <typename T>
        auto create_buffer(const T* data_ptr, size_t n)
        {
            T* device_raw_ptr;
            auto n_bytes = n * sizeof(T);
            auto status = hipMalloc((void**)&device_raw_ptr,n_bytes);
            if (status != hipSuccess) {
                throw hip_exception(status, "error when allocating device memory");
            }
            status = hipMemcpy(device_raw_ptr,data_ptr,n_bytes,hipMemcpyHostToDevice);
            if (status != hipSuccess) {
                throw hip_exception(status, "error when copying memory to device");
            }
            auto device_ptr = device_mem_ptr<T>(device_raw_ptr,buffer_deleter_t<T>());
            return device_ptr;
        }

        template <typename T>
        auto create_buffer(size_t n)
        {
            T* device_raw_ptr;
            auto n_bytes = n * sizeof(T);
            auto status = hipMalloc((void**)&device_raw_ptr,n_bytes);
            if (status != hipSuccess) {
                throw hip_exception(status, "error when allocating device memory");
            }
            auto device_ptr = device_mem_ptr<T>(device_raw_ptr,buffer_deleter_t<T>());
            return device_ptr;
        }

        template <typename array_t>
        auto create_buffer(const array_t& array)
        {
            static_assert((
                meta::is_ndarray_v<array_t>
                || meta::is_num_v<array_t>
                || meta::is_constant_index_array_v<array_t>
                ) &&
                !meta::is_view_v<array_t>
                , "unsupported array type for create_buffer"
            );
            if constexpr (meta::is_ndarray_v<array_t>) {
                auto data_ptr = nmtools::data(array);
                auto numel    = nmtools::size(array);
                return create_buffer(data_ptr,numel);
            } else if constexpr (meta::is_constant_index_array_v<array_t>) {
                constexpr auto value = meta::to_value_v<array_t>;
                return create_buffer(value);
            } else {
                return create_buffer(&array,1);
            }
        }

        template <typename array_t>
        auto create_array(const array_t& array)
        {
            static_assert(
                meta::is_ndarray_v<array_t>
                && !meta::is_view_v<array_t>
                , "unsupported array type for create_array"
            );
            const auto buffer = nmtools::data(array);
            const auto numel  = nmtools::size(array);
            const auto shape  = nmtools::shape(array);
            const auto dim    = nmtools::dim(array);

            using element_t = meta::get_element_type_t<array_t>;
            using dim_t     = meta::remove_cvref_t<decltype(dim)>;

            element_t* device_raw_ptr;
            {
                auto n_bytes = numel * sizeof(element_t);
                auto status = hipMalloc((void**)&device_raw_ptr,n_bytes);
                if (status != hipSuccess) {
                    throw hip_exception(status, "error when allocating device memory");
                }
                status = hipMemcpy(device_raw_ptr,buffer,n_bytes,hipMemcpyHostToDevice);
                if (status != hipSuccess) {
                    throw hip_exception(status, "error when copying memory to device");
                }
            }

            // TODO: keep src shape traits
            using device_shape_t = nmtools_static_vector<size_t,8>;
            auto device_shape = device_shape_t{};
            device_shape.resize(dim);
            for (size_t i=0; i<dim; i++) {
                at(device_shape,i) = at(shape,i);
            }

            using device_array_t = device_array<element_t,device_shape_t,dim_t>;
            using device_array_ptr = std::shared_ptr<device_array_t>;
            auto array_raw_ptr = new device_array_t{device_raw_ptr,device_shape,dim};

            auto array_ptr = device_array_ptr(array_raw_ptr,array_deleter_t<device_array_t>());
            return array_ptr;
        }

        template <typename attribute_t>
        auto create_attribute(const attribute_t& shape)
        {
            attribute_t* device_raw_ptr;
            auto status = hipMalloc((void**)&device_raw_ptr,sizeof(attribute_t));
            if (status != hipSuccess) {
                throw hip_exception(status, "error when allocating device memory");
            }
            status = hipMemcpy(device_raw_ptr,&shape,sizeof(attribute_t),hipMemcpyHostToDevice);
            if (status != hipSuccess) {
                throw hip_exception(status, "error when copying memory to device");
            }
            auto device_ptr = device_mem_ptr<attribute_t>(device_raw_ptr,buffer_deleter_t<attribute_t>());
            return device_ptr;
        }

        template <typename T, typename array_t>
        auto copy_buffer(device_mem_ptr<T> mem_obj, array_t& array)
        {
            using element_t = meta::get_element_type_t<array_t>;
            static_assert( meta::is_same_v<T,element_t>, "element type does not match" );

            auto byte_size = nmtools::size(array) * sizeof(element_t);
            T* out_ptr     = nmtools::data(array);

            T* mem_obj_raw = mem_obj.get();
            auto status = hipMemcpy(out_ptr,mem_obj_raw,byte_size,hipMemcpyDeviceToHost);
            if (status != hipSuccess) {
                throw hip_exception(status, "error when copying memory to host");
            }
        }

        template <typename arg_t>
        static auto get_(arg_t arg)
        {
            if constexpr (helper::is_shared_ptr_v<arg_t>) {
                return arg.get();
            } else {
                return arg;
            }
        }

        template <typename data_t, typename shape_t, typename dim_t>
        static auto get_(std::shared_ptr<device_array<data_t,shape_t,dim_t>> arg)
        {
            return *arg.get();
        }

        template <typename output_array_t, typename function_t, typename...args_t, auto...Is, template<auto...>typename sequence>
        auto run_(output_array_t& output, const function_t& f, nmtools_tuple<args_t...> args_pack, sequence<Is...>)
        {
            using out_element_t = meta::get_element_type_t<output_array_t>;

            auto out_size  = nmtools::size(output);
            if (out_size <= 0) {
                throw exception("invalid output size! expect > 0, got " + std::to_string(out_size));
            }
            // TODO: pass actual type (constant / clipped shape) as is to device
            auto out_shape = nmtools::shape<false,/*disable_clipped_index*/true>(output);
            auto out_dim   = nmtools::len(out_shape);

            auto output_buffer = this->create_buffer<out_element_t>(out_size);
            auto gpu_out_shape = this->create_buffer(out_shape);

            auto warp_size   = 32;
            auto thread_size = size_t(std::ceil(float(out_size) / warp_size)) * warp_size;

            nm_hip_run_function<<<thread_size,warp_size>>>(f
                ,output_buffer.get(),gpu_out_shape.get(),out_dim
                ,utl::tuple{get_(nmtools::get<Is>(args_pack))...}
            );

            auto status = hipDeviceSynchronize();
            if (status != hipSuccess) {
                throw hip_exception(status, "hipDeviceSynchronize");
            }

            status = hipGetLastError();
            if (status != hipSuccess) {
                throw hip_exception(status, "hipGetLastError");
            }

            this->copy_buffer(output_buffer,output);
        }

        template <typename F, typename operands_t, typename attributes_t>
        auto map_to_device(const functional::functor_t<F,operands_t,attributes_t>& f)
        {
            static_assert( meta::len_v<operands_t> == 0 );
            if constexpr (meta::is_same_v<attributes_t,meta::empty_attributes_t>) {
                return f;
            } else {
                constexpr auto N = meta::len_v<attributes_t>;
                auto attributes  = meta::template_reduce<N>([&](auto init, auto I){
                    auto attribute = array::as_static(at(f.attributes,I));
                    return utility::tuple_append(init,attribute);
                }, nmtools_tuple{});
                return functional::functor_t<F,operands_t,decltype(attributes)>{
                    {f.fmap, f.operands, attributes}
                };
            }
        } // map_to_device

        template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
        auto map_to_device(const functional::functor_composition_t<tuple<functors_t...>,operands_t>& f)
        {
            static_assert( meta::len_v<operands_t> == 0 );
            auto functors = meta::template_reduce<sizeof...(functors_t)>([&](auto init, auto I){
                auto functor = map_to_device(at(f.functors,I));
                return utility::tuple_append(init,functor);
            }, nmtools_tuple{});
            return functional::functor_composition_t<decltype(functors)>{functors};
        } // map_to_device

        template <typename function_t, typename output_array_t, template<typename...>typename tuple, typename...operands_t>
        auto run(const function_t& f, output_array_t& output, const tuple<operands_t...>& operands)
        {
            #if 0
            auto args_pack = [&](){
                if constexpr (meta::is_tuple_v<arg0_t>) {
                    static_assert( sizeof...(args_t) == 0, "nmtools error" );
                    return static_cast<const arg0_t&>(arg0);
                } else {
                    return nmtools_tuple<const arg0_t&, const args_t&...>{arg0, args...};
                }
            }();
            constexpr auto N = meta::len_v<decltype(args_pack)>;
            auto gpu_args_pack = meta::template_reduce<N>([&](auto init, auto index){
                const auto& arg_i = nmtools::get<index>(args_pack);
                if constexpr (meta::is_num_v<decltype(arg_i)>) {
                    return utility::tuple_append(init,arg_i);
                } else {
                    auto device_array = create_array(*arg_i);
                    return utility::tuple_append(init,device_array);
                }
            }, nmtools_tuple<>{});

            using sequence_t = meta::make_index_sequence<meta::len_v<decltype(gpu_args_pack)>>;
            this->run_(output,f,gpu_args_pack,sequence_t{});
            #else
            constexpr auto N = sizeof...(operands_t);
            auto device_operands = meta::template_reduce<N>([&](auto init, auto index){
                const auto& arg_i = nmtools::at(operands,index);
                if constexpr (meta::is_num_v<decltype(arg_i)>) {
                    return utility::tuple_append(init,arg_i);
                } else {
                    auto device_array = create_array(*arg_i);
                    return utility::tuple_append(init,device_array);
                }
            }, nmtools_tuple<>{});

            // e.g. to convert dynamic allocation to static vector to run on device kernels
            auto fn = map_to_device(f);
            using sequence_t = meta::make_index_sequence<meta::len_v<decltype(device_operands)>>;
            this->run_(output,fn,device_operands,sequence_t{});
            #endif
        }

        template <typename view_t>
        auto eval(const view_t& view)
        {
            auto graph = functional::linearize(functional::get_compute_graph(unwrap(view)));
            auto operands = functional::get_operands(graph);
            auto function = functional::get_function(graph);
            auto functor  = function.functor;

            using result_t = meta::resolve_optype_t<eval_result_t<>,view_t,none_t>;
            auto result    = result_t{};

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(unwrap(shape(view)));
            }
            this->run(functor,result,operands);

            return result;
        }
    };
    
    #ifndef NMTOOLS_HIP_LOG_DEFAULT
    #define NMTOOLS_HIP_LOG_DEFAULT 1
    #endif // NMTOOLS_HIP_LOG_DEFAULT

    inline auto default_context()
    {
        static std::shared_ptr<context_t> default_context;
        if (!default_context) {
            default_context = std::make_shared<context_t>();
            auto enable_log = NMTOOLS_HIP_LOG_DEFAULT;
            if (auto env_log = std::getenv("NMTOOLS_HIP_LOG"))  {
                enable_log = std::stoi(env_log);
            }
            if (enable_log) {
                int driver_version = 0;
                int runtime_version = 0;
                int device_count = 0;
                hipError_t status{};
                status = hipDriverGetVersion(&driver_version);
                if (status != hipSuccess) {
                    throw hip_exception(status, "hipDriverGetVersion");
                }
                // TODO: better logging utilities
                std::cout << "\033[1;33m[nmtools hip]\033[0m driver version: " << driver_version << "\n";
                status = hipRuntimeGetVersion(&runtime_version);
                if (status != hipSuccess) {
                    throw hip_exception(status, "hipRuntimeGetVersion");
                }
                // TODO: better logging utilities
                std::cout << "\033[1;33m[nmtools hip]\033[0m runtime version: " << runtime_version << "\n";
                status = hipGetDeviceCount(&device_count);
                if (status != hipSuccess) {
                    throw hip_exception(status, "hipGetDeviceCount");
                }
                // TODO: better logging utilities
                std::cout << "\033[1;33m[nmtools hip]\033[0m number of hip devices: " << device_count << "\n";
                for (nm_size_t i=0; i<(nm_size_t)device_count; i++) {
                    hipDevice_t device;
                    status = hipDeviceGet(&device,i);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGet");
                    }
                    int major;
                    int minor;
                    status = hipDeviceComputeCapability(&major, &minor, device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceComputeCapability");
                    }
                    std::cout << "- compute capability: " \
                        << "major: " << major << " " \
                        << "minor: " << minor << std::endl;
                    constexpr auto max_len = 32;
                    char device_name[max_len];
                    status = hipDeviceGetName(device_name,max_len,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetName");
                    }
                    std::cout << "- device name: " << device_name << std::endl;
                    size_t bytes;
                    status = hipDeviceTotalMem(&bytes,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceTotalMem");
                    }
                    std::cout << "- total mem (bytes): " << bytes << std::endl;
                    int ecc_enabled;
                    status = hipDeviceGetAttribute(&ecc_enabled,hipDeviceAttributeEccEnabled,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeEccEnabled)");
                    }
                    std::cout << "- ecc enabled: " << ecc_enabled << std::endl;
                    int async_engine_count;
                    status = hipDeviceGetAttribute(&async_engine_count,hipDeviceAttributeAsyncEngineCount,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeAsyncEngineCount)");
                    }
                    std::cout << "- async engine count: " << async_engine_count << std::endl;
                    int can_map_to_host_mem;
                    status = hipDeviceGetAttribute(&can_map_to_host_mem,hipDeviceAttributeCanMapHostMemory,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeCanMapHostMemory)");
                    }
                    std::cout << "- can map to host memory: " << can_map_to_host_mem << std::endl;
                    int can_use_host_pointer_for_registered_mem;
                    status = hipDeviceGetAttribute(&can_use_host_pointer_for_registered_mem,hipDeviceAttributeCanUseHostPointerForRegisteredMem,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeCanUseHostPointerForRegisteredMem)");
                    }
                    std::cout << "- can use host pointer for registered memory: " << can_map_to_host_mem << std::endl;
                    int clock_rate_khz;
                    status = hipDeviceGetAttribute(&clock_rate_khz,hipDeviceAttributeClockRate,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeClockRate)");
                    }
                    std::cout << "- maximum clock (kHz): " << clock_rate_khz << std::endl;
                    int compute_mode;
                    status = hipDeviceGetAttribute(&compute_mode,hipDeviceAttributeComputeMode,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeComputeMode)");
                    }
                    std::cout << "- compute mode: " << compute_mode << std::endl;
                    int compute_preemption;
                    status = hipDeviceGetAttribute(&compute_preemption,hipDeviceAttributeComputePreemptionSupported,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeComputePreemptionSupported)");
                    }
                    std::cout << "- compute preemption supported: " << compute_preemption << std::endl;
                    int concurrent_kernels;
                    status = hipDeviceGetAttribute(&concurrent_kernels,hipDeviceAttributeConcurrentKernels,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeConcurrentKernels)");
                    }
                    std::cout << "- concurrent kernel execution supported: " << concurrent_kernels << std::endl;
                    int concurrent_managed_access;
                    status = hipDeviceGetAttribute(&concurrent_managed_access,hipDeviceAttributeConcurrentManagedAccess,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeConcurrentManagedAccess)");
                    }
                    std::cout << "- coherent access managed memory concurrently with cpu: " << concurrent_managed_access << std::endl;
                    int cooperative_launch;
                    status = hipDeviceGetAttribute(&cooperative_launch,hipDeviceAttributeCooperativeLaunch,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeCooperativeLaunch)");
                    }
                    std::cout << "- cooperative launch supported: " << cooperative_launch << std::endl;
                    int cooperative_device_launch;
                    status = hipDeviceGetAttribute(&cooperative_device_launch,hipDeviceAttributeCooperativeMultiDeviceLaunch,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeCooperativeMultiDeviceLaunch)");
                    }
                    std::cout << "- cooperative device launch supported: " << cooperative_device_launch << std::endl;
                    int global_l1_cache_support;
                    status = hipDeviceGetAttribute(&global_l1_cache_support,hipDeviceAttributeGlobalL1CacheSupported,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeGlobalL1CacheSupported)");
                    }
                    std::cout << "- caching globals in L1 supported: " << global_l1_cache_support << std::endl;
                    int host_native_atomic;
                    status = hipDeviceGetAttribute(&host_native_atomic,hipDeviceAttributeHostNativeAtomicSupported,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeHostNativeAtomicSupported)");
                    }
                    std::cout << "- host device operation is native atomic: " << host_native_atomic << std::endl;
                    int is_igpu;
                    status = hipDeviceGetAttribute(&is_igpu,hipDeviceAttributeIntegrated,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeIntegrated)");
                    }
                    std::cout << "- is integrated GPU: " << is_igpu << std::endl;
                    int is_multi_gpu_board;
                    status = hipDeviceGetAttribute(&is_multi_gpu_board,hipDeviceAttributeIsMultiGpuBoard,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeIsMultiGpuBoard)");
                    }
                    std::cout << "- is multi GPUs: " << is_multi_gpu_board << std::endl;
                    int kernel_timeout_limit;
                    status = hipDeviceGetAttribute(&kernel_timeout_limit,hipDeviceAttributeKernelExecTimeout,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeKernelExecTimeout)");
                    }
                    std::cout << "- kernel execution timeout limit: " << kernel_timeout_limit << std::endl;
                    int l2_cache_size_bytes;
                    status = hipDeviceGetAttribute(&l2_cache_size_bytes,hipDeviceAttributeL2CacheSize,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeL2CacheSize)");
                    }
                    std::cout << "- L2 cache size (bytes): " << l2_cache_size_bytes << std::endl;
                    int local_l1_cache_support;
                    status = hipDeviceGetAttribute(&local_l1_cache_support,hipDeviceAttributeLocalL1CacheSupported,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeLocalL1CacheSupported)");
                    }
                    std::cout << "- caching locals in L1 supported: " << local_l1_cache_support << std::endl;
                    int managed_memory_support;
                    status = hipDeviceGetAttribute(&managed_memory_support,hipDeviceAttributeManagedMemory,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeManagedMemory)");
                    }
                    std::cout << "- supports allocating managed memory: " << managed_memory_support << std::endl;
                    int max_block_size;
                    status = hipDeviceGetAttribute(&max_block_size,hipDeviceAttributeMaxBlocksPerMultiProcessor,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxBlocksPerMultiProcessor)");
                    }
                    std::cout << "- maximum block size per multiprocessors: " << max_block_size << std::endl;
                    int max_block_dim_x;
                    status = hipDeviceGetAttribute(&max_block_dim_x,hipDeviceAttributeMaxBlockDimX,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxBlockDimX)");
                    }
                    std::cout << "- maximum block size in width (x): " << max_block_dim_x << std::endl;
                    int max_block_dim_y;
                    status = hipDeviceGetAttribute(&max_block_dim_y,hipDeviceAttributeMaxBlockDimY,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxBlockDimY)");
                    }
                    std::cout << "- maximum block size in height (y): " << max_block_dim_y << std::endl;
                    int max_block_dim_z;
                    status = hipDeviceGetAttribute(&max_block_dim_z,hipDeviceAttributeMaxBlockDimZ,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxBlockDimZ)");
                    }
                    std::cout << "- maximum block size in depth (z): " << max_block_dim_z << std::endl;
                    int max_grid_size_x;
                    status = hipDeviceGetAttribute(&max_grid_size_x,hipDeviceAttributeMaxGridDimX,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxGridDimX)");
                    }
                    std::cout << "- maximum grid size in width (x): " << max_grid_size_x << std::endl;
                    int max_grid_size_y;
                    status = hipDeviceGetAttribute(&max_grid_size_y,hipDeviceAttributeMaxGridDimY,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxGridDimY)");
                    }
                    std::cout << "- maximum grid size in height (y): " << max_grid_size_y << std::endl;
                    int max_grid_size_z;
                    status = hipDeviceGetAttribute(&max_grid_size_z,hipDeviceAttributeMaxGridDimZ,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxGridDimZ)");
                    }
                    std::cout << "- maximum grid size in depth (z): " << max_grid_size_z << std::endl;
                    #if 0
                    // crashed (at least on 780M)
                    int max_threads_dim;
                    status = hipDeviceGetAttribute(&max_threads_dim,hipDeviceAttributeMaxThreadsDim,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxThreadsDim)");
                    }
                    std::cout << "- maximum dimensionn of a block: " << max_threads_dim << std::endl;
                    #endif
                    int max_threads_per_block;
                    status = hipDeviceGetAttribute(&max_threads_per_block,hipDeviceAttributeMaxThreadsPerBlock,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxThreadsPerBlock)");
                    }
                    std::cout << "- maximum threads per block: " << max_threads_per_block << std::endl;
                    int max_threads_per_multiprocessor;
                    status = hipDeviceGetAttribute(&max_threads_per_multiprocessor,hipDeviceAttributeMaxThreadsPerMultiProcessor,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxThreadsPerMultiProcessor)");
                    }
                    std::cout << "- maximum threads per multiprocessor: " << max_threads_per_multiprocessor << std::endl;
                    int memory_bus_width;
                    status = hipDeviceGetAttribute(&memory_bus_width,hipDeviceAttributeMemoryBusWidth,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMaxThreadsPerMultiProcessor)");
                    }
                    std::cout << "- global memory bus width (bits): " << memory_bus_width << std::endl;
                    int max_memory_clock_khz;
                    status = hipDeviceGetAttribute(&max_memory_clock_khz,hipDeviceAttributeMemoryClockRate,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMemoryClockRate)");
                    }
                    std::cout << "- maximum memory clock frequency (kHz): " << max_memory_clock_khz << std::endl;
                    int multiprocessor_count;
                    status = hipDeviceGetAttribute(&multiprocessor_count,hipDeviceAttributeMultiprocessorCount,device);
                    if (status != hipSuccess) {
                        throw hip_exception(status, "hipDeviceGetAttribute(hipDeviceAttributeMultiprocessorCount)");
                    }
                    std::cout << "- multiprocessor count: " << multiprocessor_count << std::endl;
                }
            }
        }
        return default_context;
    }
}

#endif // NMTOOLS_ARRAY_EVAL_HIP_CONTEXT_HPP