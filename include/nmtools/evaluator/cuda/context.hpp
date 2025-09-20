#ifndef NMTOOLS_ARRAY_EVAL_CUDA_CONTEXT_HPP
#define NMTOOLS_ARRAY_EVAL_CUDA_CONTEXT_HPP

#include "nmtools/exception.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/evaluator/kernel_helper.hpp"
#include "nmtools/utility/tuple_cat.hpp"
#include "nmtools/core/functor.hpp"
#include <memory>

template <auto out_static_dim=0, typename function_t
    , typename out_t, typename out_shape_t, typename out_dim_t
    , template<typename...>typename tuple
    , typename...operands_t
>
__global__ void nm_cuda_run_function(const function_t fun
    , out_t *out, const out_shape_t* out_shape_ptr, const out_dim_t out_dim
    , const tuple<operands_t...> operands
) {
    namespace meta = nmtools::meta;
    namespace na = nmtools;
    namespace fn = nmtools::functional;
    auto output = na::create_mutable_array<out_static_dim>(out,out_shape_ptr,out_dim);
    auto result = fn::apply(fun,operands);
    // TODO: properly get the thread & kernel id and shape
    auto thread_id  = na::kernel_size<size_t>{threadIdx.x,0,0};
    auto block_id   = na::kernel_size<size_t>{blockIdx.x,0,0};
    auto block_size = na::kernel_size<size_t>{blockDim.x,1,1};
    na::assign_result(output,result,thread_id,block_id,block_size);
}

namespace nmtools
{
    class cuda_exception : public ::nmtools::exception
    {
        public:
        cuda_exception(cudaError status, const std::string& message)
            : nmtools::exception(message + " (" + std::to_string(static_cast<int>(status)) + "): " + cudaGetErrorString(status))
            , status_(status)
        {}

        inline auto status() const
        {
            return status_;
        }

        protected:
        cudaError status_;
    };
}

namespace nmtools::cuda
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
            auto status = cudaFree(ptr);
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when freeing device memory");
            }
        }
    };

    template <typename array_t>
    struct array_deleter_t
    {
        void operator()(array_t* array_ptr) const
        {
            auto status = cudaFree(array_ptr->data_);
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when freeing device memory");
            }
        }
    };

    template <typename T>
    using device_mem_ptr = std::shared_ptr<T>;

    struct context_t
    {
        // TODO: use cuda stream?
        context_t([[maybe_unused]] size_t gpu_id=0) {}

        template <typename T>
        auto create_buffer(const T* data_ptr, size_t n)
        {
            T* device_raw_ptr;
            auto n_bytes = n * sizeof(T);
            auto status = cudaMalloc((void**)&device_raw_ptr,n_bytes);
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when allocating device memory");
            }
            status = cudaMemcpy(device_raw_ptr,data_ptr,n_bytes,cudaMemcpyHostToDevice);
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when copying memory to device");
            }
            auto device_ptr = device_mem_ptr<T>(device_raw_ptr,buffer_deleter_t<T>());
            return device_ptr;
        }

        template <typename T>
        auto create_buffer(size_t n)
        {
            T* device_raw_ptr;
            auto n_bytes = n * sizeof(T);
            auto status = cudaMalloc((void**)&device_raw_ptr,n_bytes);
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when allocating device memory");
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
                auto status = cudaMalloc((void**)&device_raw_ptr,n_bytes);
                if (status != cudaSuccess) {
                    throw cuda_exception(status, "error when allocating device memory");
                }
                status = cudaMemcpy(device_raw_ptr,buffer,n_bytes,cudaMemcpyHostToDevice);
                if (status != cudaSuccess) {
                    throw cuda_exception(status, "error when copying memory to device");
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
            auto status = cudaMalloc((void**)&device_raw_ptr,sizeof(attribute_t));
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when allocating device memory");
            }
            status = cudaMemcpy(device_raw_ptr,&shape,sizeof(attribute_t),cudaMemcpyHostToDevice);
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when copying memory to device");
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
            auto status = cudaMemcpy(out_ptr,mem_obj_raw,byte_size,cudaMemcpyDeviceToHost);
            if (status != cudaSuccess) {
                throw cuda_exception(status, "error when copying memory to host");
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

            nm_cuda_run_function<<<thread_size,warp_size>>>(f
                ,output_buffer.get(),gpu_out_shape.get(),out_dim
                ,utl::tuple{get_(nmtools::get<Is>(args_pack))...}
            );

            auto status = cudaDeviceSynchronize();
            if (status != cudaSuccess) {
                throw cuda_exception(status, "cudaDeviceSynchronize");
            }

            status = cudaGetLastError();
            if (status != cudaSuccess) {
                throw cuda_exception(status, "cudaGetLastError");
            }

            this->copy_buffer(output_buffer,output);
        }

        template <typename function_t, typename output_array_t, typename arg0_t, typename...args_t>
        auto run(const function_t& f, output_array_t& output, const arg0_t& arg0, const args_t&...args)
        {
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
            }, nmtools_tuple{});

            using sequence_t = meta::make_index_sequence<meta::len_v<decltype(gpu_args_pack)>>;
            this->run_(output,f,gpu_args_pack,sequence_t{});
        }
    };

    inline auto default_context()
    {
        static std::shared_ptr<context_t> default_context;
        if (!default_context) {
            default_context = std::make_shared<context_t>();
        }
        return default_context;
    }
}

#endif // NMTOOLS_ARRAY_EVAL_CUDA_CONTEXT_HPP