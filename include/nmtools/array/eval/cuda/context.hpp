#ifndef NMTOOLS_ARRAY_EVAL_CUDA_CONTEXT_HPP
#define NMTOOLS_ARRAY_EVAL_CUDA_CONTEXT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/eval/cuda/kernel_helper.hpp"
#include "nmtools/utility/tuple_cat.hpp"
#include <stdexcept>
#include <memory>

template <auto out_static_dim=0, typename function_t
    , typename out_t, typename out_shape_t, typename out_dim_t
    , typename...args_t
>
__global__ void nm_cuda_run_function(const function_t fun
    , out_t *out, const out_shape_t* out_shape_ptr, const out_dim_t out_dim
    , const args_t...args
) {
    namespace cuda = nmtools::array::cuda;
    auto output = cuda::create_mutable_array<out_static_dim>(out,out_shape_ptr,out_dim);

    auto args_pack = nmtools_tuple<const args_t...>(args...);
    auto result = nmtools::meta::template_reduce<sizeof...(args_t) / 3>([&](auto init, auto index){
        using init_t = decltype(init);
        constexpr auto ptr_idx = (size_t)index * 3;
        constexpr auto shp_idx = ptr_idx + 1;
        constexpr auto dim_idx = ptr_idx + 2;
        // TODO: support constant shape, clipped shape, fixed dim, fixed size, bounded dim, size etc...
        auto array = cuda::create_array(
              nmtools::get<ptr_idx>(args_pack)
            , nmtools::get<shp_idx>(args_pack)
            , nmtools::get<dim_idx>(args_pack)
        );
        if constexpr (nmtools::is_none_v<init_t>) {
            return fun (array);
        } else {
            return init (array);
        }
    }, nmtools::None);
    static_assert( nmtools::meta::is_ndarray_v<decltype(result)> );
    cuda::assign_array(output,result);
}

namespace nmtools::array::cuda
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

    class cuda_exception : public std::runtime_error
    {
        public:
        cuda_exception(cudaError status, const std::string& message)
            : std::runtime_error(message + " (" + std::to_string(static_cast<int>(status)) + "): " + cudaGetErrorString(status))
            , status_(status)
        {}

        inline auto status() const
        {
            return status_;
        }

        protected:
        cudaError status_;
    };

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
            static_assert( (meta::is_ndarray_v<array_t> || meta::is_num_v<array_t> || meta::is_constant_index_array_v<array_t>) && !meta::is_view_v<array_t>, "unsupported array type for create_buffer" );
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
        auto get_(arg_t arg)
        {
            if constexpr (helper::is_shared_ptr_v<arg_t>) {
                return arg.get();
            } else {
                return arg;
            }
        }

        template <typename output_array_t, typename function_t, typename...args_t, auto...Is, template<auto...>typename sequence>
        auto run_(output_array_t& output, const function_t& f, nmtools_tuple<args_t...> args_pack, sequence<Is...>)
        {
            using out_element_t = meta::get_element_type_t<output_array_t>;

            auto out_size  = nmtools::size(output);
            auto out_shape = nmtools::shape(output);
            auto out_dim   = nmtools::len(out_shape);

            auto output_buffer = this->create_buffer<out_element_t>(out_size);
            auto gpu_out_shape = this->create_buffer(out_shape);

            auto warp_size   = 32;
            auto thread_size = size_t(std::ceil(float(out_size) / warp_size)) * warp_size;

            nm_cuda_run_function<<<thread_size,warp_size>>>(f
                ,output_buffer.get(),gpu_out_shape.get(),out_dim
                ,get_(nmtools::get<Is>(args_pack))...
            );

            auto status = cudaDeviceSynchronize();
            if (status != cudaSuccess) {
                throw cuda::cuda_exception(status, "cudaDeviceSynchronize");
            }

            status = cudaGetLastError();
            if (status != cudaSuccess) {
                throw cuda::cuda_exception(status, "cudaGetLastError");
            }

            this->copy_buffer(output_buffer,output);
        }

        template <typename function_t, typename output_array_t, typename arg0_t, typename...args_t>
        auto run(const function_t& f, output_array_t& output, const arg0_t& arg0, const args_t&...args)
            // -> meta::enable_if_t<(sizeof...(args_t) > 2)>
        {
            auto args_pack = [&](){
                if constexpr (meta::is_tuple_v<arg0_t>) {
                    return arg0;
                } else {
                    return nmtools_tuple<const arg0_t&, const args_t&...>{arg0, args...};
                }
            }();
            constexpr auto N = meta::len_v<decltype(args_pack)>;
            auto gpu_args_pack = meta::template_reduce<N>([&](auto init, auto index){
                const auto& arg_i = *nmtools::get<index>(args_pack);

                auto arg_shape = nmtools::shape(arg_i);
                auto arg_dim   = nmtools::len(arg_shape);

                auto gpu_buffer = this->create_buffer(arg_i);
                // TODO: allow constant/clipped index shape
                auto gpu_shape  = this->create_buffer(arg_shape);
                return utility::tuple_cat(init,nmtools_tuple{gpu_buffer,gpu_shape,arg_dim});
            }, nmtools_tuple<>{});

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