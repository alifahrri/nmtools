#ifndef NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP
#define NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/evaluator/kernel_helper.hpp"
#include "nmtools/exception.hpp"
#include "nmtools/utility/to_string.hpp"
#include "nmtools/utility/as_static.hpp"
#include "nmtools/utl/vector.hpp"

#include <sycl/sycl.hpp>
#include <iostream>
#include <memory>

namespace nmtools::array
{
    template <typename T, auto...accessor_args_t, typename shape_t, typename dim_t>
    struct device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>
        : base_ndarray_t<device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>>
    {
        using value_type = T;
        using shape_type = shape_t;
        using dim_type   = dim_t;

        using accessor_type = ::sycl::accessor<T,accessor_args_t...>;
        using buffer_type = T*;
        using stride_type = resolve_stride_type_t<shape_type>;
        using offset_type = row_major_offset_t<shape_type,stride_type>;
        using base_type   = base_ndarray_t<device_array>;

        accessor_type accessor_;
        buffer_type data_;
        shape_type shape_;
        dim_type dim_;
        stride_type strides_;
        offset_type offset_;

        device_array(accessor_type accessor_, const shape_t& shape_, dim_t dim_)
            : accessor_(accessor_)
            , data_   (accessor_.get_pointer().get())
            , shape_  (shape_)
            , dim_    (dim_)
            , strides_(base_type::template compute_strides<stride_type>(shape_))
            , offset_ (shape_,strides_)
        {}

        device_array(const device_array& other)
            : device_array(other.accessor_,other.shape_,other.dim_)
        {}
    };

    template <typename T, typename shape_t, typename dim_t>
    struct device_array<::sycl::buffer<T>,shape_t,dim_t>
        : base_ndarray_t<device_array<::sycl::buffer<T>,shape_t,dim_t>>
    {
        using value_type = T;
        using shape_type = shape_t;
        using dim_type   = dim_t;

        using buffer_type = ::sycl::buffer<T>;
        using stride_type = resolve_stride_type_t<shape_type>;
        using offset_type = row_major_offset_t<shape_type,stride_type>;
        using base_type   = base_ndarray_t<device_array>;

        buffer_type data_;
        shape_type shape_;
        dim_type dim_;
        stride_type strides_;
        offset_type offset_;

        device_array(buffer_type data_, const shape_t& shape_, dim_t dim_)
            : data_   (data_)
            , shape_  (shape_)
            , dim_    (dim_)
            , strides_(base_type::template compute_strides<stride_type>(shape_))
            , offset_ (shape_,strides_)
        {}

        device_array(const device_array& other)
            : data_   (other.data_)
            , shape_  (other.shape_)
            , dim_    (other.dim_)
            , strides_(base_type::template compute_strides<stride_type>(shape_))
            , offset_ (shape_,strides_)
        {}

        template <typename...access_args_t>
        auto accessor(::sycl::handler& cgh, access_args_t...access_args)
        {
            auto accessor = ::sycl::accessor(data_, cgh, access_args...);
            using accessor_t = decltype(accessor);
            return device_array<accessor_t,shape_t,dim_t>(accessor,shape_,dim_);
        }
    };

    template <typename data_t, typename shape_t, typename dim_t, auto...accessor_args_t>
    nmtools_func_attribute
    auto create_array(const device_array<::sycl::accessor<data_t,accessor_args_t...>,shape_t,dim_t>& array)
    {
        // assume array.shape is passed by value
        return create_array(array.buffer.get_pointer().get(),array.shape);
    }

    class sycl_exception : public ::nmtools::exception
    {
        public:
        sycl_exception(const std::string& message)
            : ::nmtools::exception(message)
        {}
    };
}

namespace nmtools::meta
{
    template <typename T, auto...accessor_args_t, typename shape_t, typename dim_t>
    struct fixed_dim<
        array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_index_array_v<shape_type>) {
                return len_v<shape_type>;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_dim

    template <typename T, auto...accessor_args_t, typename shape_t, typename dim_t>
    struct fixed_shape<
        array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_shape

    template <typename T, auto...accessor_args_t, typename shape_t, typename dim_t>
    struct fixed_size<
        array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_size_v<buffer_type>) {
                return fixed_size_v<buffer_type>;
            } else if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_size

    template <typename T, auto...accessor_args_t, typename shape_t, typename dim_t>
    struct bounded_dim<
        array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<shape_type>) {
                return bounded_size_v<shape_type>;
            } else if constexpr (is_fixed_size_v<shape_type>) {
                // TODO: consider to add error mapping fn so this else-if/else block not needed
                return fixed_size_v<shape_type>;
            } else {
                return error::BOUNDED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // bounded_dim

    template <typename T, auto...accessor_args_t, typename shape_t, typename dim_t>
    struct bounded_size<
        array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<::sycl::accessor<T,accessor_args_t...>,shape_t,dim_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<buffer_type>) {
                return bounded_size_v<buffer_type>;
            } else if constexpr (is_fixed_size_v<array_type>) {
                return fixed_size_v<array_type>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // bounded_size

    /* sycl::buffer */
    template <typename T, typename shape_t, typename dim_t>
    struct fixed_dim<
        array::device_array<::sycl::buffer<T>,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<::sycl::buffer<T>,shape_t,dim_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_index_array_v<shape_type>) {
                return len_v<shape_type>;
            } else {
                return error::FIXED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_dim

    template <typename T, typename shape_t, typename dim_t>
    struct fixed_shape<
        array::device_array<::sycl::buffer<T>,shape_t,dim_t>
    >
    {
        using array_type = array::device_array<::sycl::buffer<T>,shape_t,dim_t>;
        using shape_type = typename array_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return shape_type {};
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_shape

    template <typename T, typename shape_t, typename dim_t>
    struct fixed_size<
        array::device_array<::sycl::buffer<T>,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<::sycl::buffer<T>,shape_t,dim_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_fixed_size_v<buffer_type>) {
                return fixed_size_v<buffer_type>;
            } else if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // fixed_size

    template <typename T, typename shape_t, typename dim_t>
    struct bounded_dim<
        array::device_array<::sycl::buffer<T>,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<::sycl::buffer<T>,shape_t,dim_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<shape_type>) {
                return bounded_size_v<shape_type>;
            } else if constexpr (is_fixed_size_v<shape_type>) {
                // TODO: consider to add error mapping fn so this else-if/else block not needed
                return fixed_size_v<shape_type>;
            } else {
                return error::BOUNDED_DIM_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // bounded_dim

    template <typename T, typename shape_t, typename dim_t>
    struct bounded_size<
        array::device_array<::sycl::buffer<T>,shape_t,dim_t>
    >
    {
        using array_type  = array::device_array<::sycl::buffer<T>,shape_t,dim_t>;
        using shape_type  = typename array_type::shape_type;
        using buffer_type = typename array_type::buffer_type;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<buffer_type>) {
                return bounded_size_v<buffer_type>;
            } else if constexpr (is_fixed_size_v<array_type>) {
                return fixed_size_v<array_type>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<array_type>{};
            }
        }();
        using value_type = decltype(value);
    }; // bounded_size
}

namespace nmtools::array::sycl
{
    template <typename T>
    using device_mem_ptr = std::shared_ptr<::sycl::buffer<T>>;

    // TODO: check sycl spec for built-in write-only buffer memory
    template <typename T>
    using host_mem_ptr = std::shared_ptr<T>;

    struct context_t
    {
        using queue_t  = ::sycl::queue;
        using device_t = ::sycl::device;

        // TODO: share same queue for same context (?)
        // std::shared_ptr<queue_t> queue;
        nmtools_maybe<device_t> device = meta::Nothing;

        context_t()
        {}

        context_t(device_t device)
            : device(device)
        {}

        template <typename T>
        auto create_buffer(const T* data_ptr, size_t n)
        {
            using buffer_t = ::sycl::buffer<T>;
            auto buffer_ptr = std::make_shared<buffer_t>(data_ptr,n);
            return buffer_ptr;
        }

        template <typename array_t>
        auto create_buffer(const array_t& array)
        {
            // TODO: pass constant index as constant index
            static_assert( (meta::is_ndarray_v<array_t>
                || meta::is_num_v<array_t>
                || meta::is_constant_index_array_v<array_t>
            ));
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
                ((meta::is_ndarray_v<meta::remove_pointer_t<array_t>> && meta::is_pointer_v<array_t>)
                    || meta::is_num_v<array_t> || meta::is_ndarray_v<array_t>)
                    && !meta::is_view_v<meta::remove_pointer_t<array_t>>
                , "unsupported array type for create_array"
            );
            if constexpr (meta::is_num_v<array_t>) {
                return array;
            } else if constexpr (meta::is_pointer_v<array_t>) {
                return create_array(*array);
            } else {
                const auto buffer = nmtools::data(array);
                const auto numel  = nmtools::size(array);
                const auto shape  = nmtools::shape(array);
                const auto dim    = nmtools::dim(array);

                using element_t = meta::get_element_type_t<array_t>;
                using dim_t     = meta::remove_cvref_t<decltype(dim)>;

                // TODO: keep src shape traits
                using device_shape_t = nmtools_static_vector<size_t,8>;
                auto device_shape = device_shape_t{};
                device_shape.resize(dim);
                for (size_t i=0; i<dim; i++) {
                    at(device_shape,i) = at(shape,i);
                }

                using buffer_t = ::sycl::buffer<element_t>;
                auto sycl_buffer = buffer_t(buffer,(size_t)numel);

                using device_array_t = device_array<buffer_t,device_shape_t,dim_t>;
                using device_array_ptr = std::shared_ptr<device_array_t>;

                auto array_raw_ptr = new device_array_t{sycl_buffer,device_shape,dim};
                auto array_ptr = device_array_ptr(array_raw_ptr);
                return array_ptr;
            }
        }

        template <typename T>
        auto create_buffer(size_t n)
        {
            using buffer_t = ::sycl::buffer<T>;
            auto buffer_ptr = std::make_shared<buffer_t>(n);
            return buffer_ptr;
        }

        template <typename T, typename array_t>
        auto copy_buffer(device_mem_ptr<T> mem_obj, array_t& array)
        {
            auto host_accessor = ::sycl::host_accessor(*mem_obj);
            auto flat_array    = unwrap(view::mutable_flatten(array));
            auto size = nmtools::size(flat_array);
            auto accessor_size = host_accessor.size();
            if (size != accessor_size) {
                throw sycl_exception(std::string("unexpected size mismatch output: ") + std::to_string(size) + "; accessor: " + std::to_string(accessor_size));
            }
            // TODO: memcpy?
            for (size_t i=0; i<size; i++) {
                at(flat_array,i) = host_accessor[i];
            }
        }

        template <typename operand_t, typename...accessor_args_t>
        static auto get_accessor(operand_t operand, [[maybe_unused]] accessor_args_t&&...args)
        {
            if constexpr (meta::is_num_v<operand_t>) {
                return operand;
            } else {
                return operand->accessor(nmtools::forward<accessor_args_t>(args)...);
            }
        }

        template <typename output_array_t, typename function_t, typename...args_t, auto...Is, template<auto...>typename sequence>
        auto run_(output_array_t& output, const function_t& f, nmtools_tuple<args_t...> args_pack, sequence<Is...>)
        {
            auto queue = std::shared_ptr<queue_t>();
            if (!device) {
                queue = std::make_shared<queue_t>();
            } else {
                queue = std::make_shared<queue_t>(*device);
            }
            using element_t = meta::get_element_type_t<output_array_t>;
            auto numel = nmtools::size(output);
            // TODO: pass actual type (constant / clipped shape) as is to device
            auto output_shape = nmtools::shape<false,/*disable_clipped_index*/true>(output);
            auto output_dim   = nmtools::dim(output);

            auto output_buffer = this->create_buffer<element_t>(numel);
            auto shape_buffer  = this->create_buffer(output_shape);

            auto warp_size   = 32;
            auto thread_size = size_t(std::ceil(float(numel) / warp_size)) * warp_size;

            queue->submit([&](::sycl::handler& cgh){
                // create accessor
                // NOTE: can be unused when sizeof...(args_t) == 0
                [[maybe_unused]] auto access_mode = ::sycl::read_only;

                auto output_accessor = ::sycl::accessor(*output_buffer, cgh, ::sycl::write_only);
                auto output_shape_accessor = ::sycl::accessor(*shape_buffer, cgh, ::sycl::read_only);

                [[maybe_unused]]
                constexpr auto N = sizeof...(args_t);

                // get_accessor / .accessor() sycl-equivalent to cudaMemcpy + pass to kernel (?)
                auto operands = nmtools_tuple{get_accessor(nmtools::get<Is>(args_pack),cgh,access_mode)...};

                auto kernel_range = ::sycl::nd_range<1>(thread_size, warp_size);

                // TODO: fix wrong result on cuda, but correct on openmp:
                // seems like the work item is clipped to 32(?) on cuda, the rest of work item is not executed
                #if 0
                std::cout << "- numel: " << numel << "\n";
                std::cout << "- warp_size: " << warp_size << "\n";
                std::cout << "- thread_size: " << thread_size << "\n";
                std::cout << "- kernel_range: " << kernel_range << "\n";

                ::sycl::stream out(1024, 256, cgh);
                out << ::sycl::endl;
                #endif

                // TODO: change to nd_item with 3 dim to properly use thread & block structure like cuda
                cgh.parallel_for(kernel_range,[=](::sycl::nd_item<1> item){
                    auto output = create_mutable_array(&output_accessor[0],&output_shape_accessor[0],output_dim);
                    auto result = functional::apply(f,operands);
                    // TODO: properly get the thread & kernel id and shape
                    auto thread_id  = array::kernel_size<size_t>{item.get_global_id(),0,0};
                    auto block_id   = array::kernel_size<size_t>{0,0,0};
                    auto block_size = array::kernel_size<size_t>{1,1,1};

                    #if 0
                    auto idx = compute_offset(thread_id,block_id,block_size);
                    out << item.get_global_id()
                        << "->"
                        << idx
                        << ";"
                        << ::sycl::flush
                    ;
                    #endif

                    array::assign_result(output,result,thread_id,block_id,block_size);
                });
            });

            // TODO: support async
            queue->wait_and_throw();
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
                    return utility::tuple_append(init,array::as_static(at(f.attributes,I)));
                }, nmtools_tuple{});
                return functional::functor_t<F,operands_t,decltype(attributes)>{{
                    f.fmap, f.operands, attributes
                }};
            }
        } // map_to_device

        template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
        auto map_to_device(const functional::functor_composition_t<tuple<functors_t...>,operands_t>& f)
        {
            static_assert( meta::len_v<operands_t> == 0 );
            auto functors = meta::template_reduce<sizeof...(functors_t)>([&](auto init, auto I){
                return utility::tuple_append(init,map_to_device(at(f.functors,I)));
            }, nmtools_tuple{});
            return functional::functor_composition_t<decltype(functors)>{functors};
        } // map_to_device

        template <typename function_t, typename output_array_t, template<typename...>typename tuple, typename...operands_t>
        auto run(const function_t& f, output_array_t& output, const tuple<operands_t...>& operands)
        {
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

            result.resize(unwrap(shape(view)));
            this->run(functor,result,operands);

            return result;
        }
    };
} // namespace nmtools::array::sycl

#define PRINT_SYCL_PLATFORM_PROPERTY(platform, prop) \
    std::cout << "- " << #prop << ": " \
        << nmtools::utils::to_string(platform.get_info<::sycl::info::platform::prop>()) << std::endl;
    
#define PRINT_SYCL_DEVICE_PROPERTY(selected_device, prop) \
std::cout << "- " << #prop << ": " \
    << nmtools::utils::to_string(selected_device.get_info<::sycl::info::device::prop>()) << std::endl;

namespace nmtools::utils::impl
{
    template <>
    struct to_string_t<
        ::sycl::info::device_type, none_t
    > {
        using device_type = ::sycl::info::device_type;
        auto operator()(device_type prop) const noexcept
        {
            nmtools_string str;
            switch (prop) {
                case device_type::cpu:
                    str = "CPU"; break;
                case device_type::gpu:
                    str = "GPU"; break;
                case device_type::accelerator:
                    str = "Accelerator"; break;
                case device_type::custom:
                    str = "Custom"; break;
                case device_type::automatic:
                    str = "Automatic"; break;
                case device_type::host:
                    str = "Host"; break;
                case device_type::all:
                    str = "All"; break;
                default:
                    str = "UNKNOWN";
            }
            return str;
        }
    }; // device_type

    template <>
    struct to_string_t<
        ::sycl::info::local_mem_type, none_t
    > {
        using local_mem_type = ::sycl::info::local_mem_type;
        auto operator()(local_mem_type prop) const noexcept
        {
            nmtools_string str;
            switch (prop) {
                case local_mem_type::none:
                    str = "None"; break;
                case local_mem_type::local:
                    str = "Local"; break;
                case local_mem_type::global:
                    str = "Global"; break;
                default:
                    str = "UNKNOWN";
            }
            return str;
        }
    }; // local_mem_type

    template <>
    struct to_string_t<
        ::sycl::info::global_mem_cache_type, none_t
    > {
        using global_mem_cache_type = ::sycl::info::global_mem_cache_type;
        auto operator()(global_mem_cache_type prop) const noexcept
        {
            nmtools_string str;
            switch (prop) {
                case global_mem_cache_type::none:
                    str = "None"; break;
                case global_mem_cache_type::read_only:
                    str = "Read-Only"; break;
                case global_mem_cache_type::read_write:
                    str = "Read-Write"; break;
                default:
                    str = "UNKNOWN";
            }
            return str;
        }
    }; // global_mem_cache_type

    template <>
    struct to_string_t<
        ::sycl::info::fp_config, none_t
    > {
        using fp_config = ::sycl::info::fp_config;
        auto operator()(fp_config prop) const noexcept
        {
            nmtools_string str;
            switch (prop) {
                case fp_config::denorm:
                    str = "Denorm"; break;
                case fp_config::inf_nan:
                    str = "Inf-Nan"; break;
                case fp_config::round_to_nearest:
                    str = "Round-to-Nearest"; break;
                case fp_config::round_to_zero:
                    str = "Round-to-Zero"; break;
                case fp_config::round_to_inf:
                    str = "Round-to-Inf"; break;
                case fp_config::fma:
                    str = "FMA"; break;
                case fp_config::correctly_rounded_divide_sqrt:
                    str = "Correctly-Rounded-Divide-Sqrt"; break;
                case fp_config::soft_float:
                    str = "Soft-Float"; break;
                default:
                    str = "UNKNOWN";
            }
            return str;
        }
    }; // fp_config

    template <>
    struct to_string_t<
        ::sycl::info::execution_capability, none_t
    > {
        using execution_capability = ::sycl::info::execution_capability;
        auto operator()(execution_capability prop) const noexcept
        {
            nmtools_string str;
            switch (prop) {
                case execution_capability::exec_kernel:
                    str = "Exec-Kernel"; break;
                case execution_capability::exec_native_kernel:
                    str = "Exec-Native-Kernel"; break;
                default:
                    str = "UNKNOWN";
            }
            return str;
        }
    }; // execution_capability

    template <>
    struct to_string_t<
        ::sycl::info::partition_property, none_t
    > {
        using partition_property = ::sycl::info::partition_property;
        auto operator()(partition_property prop) const noexcept
        {
            nmtools_string str;
            switch (prop) {
                case partition_property::no_partition:
                    str = "No-Partition"; break;
                case partition_property::partition_equally:
                    str = "Partition-Equally"; break;
                case partition_property::partition_by_counts:
                    str = "Partition-by-Counts"; break;
                case partition_property::partition_by_affinity_domain:
                    str = "Partition-by-Affinity-Domain"; break;
                default:
                    str = "UNKNOWN";
            }
            return str;
        }
    }; // partition_property

    template <>
    struct to_string_t<
        ::sycl::info::partition_affinity_domain, none_t
    > {
        using partition_affinity_domain = ::sycl::info::partition_affinity_domain;
        auto operator()(partition_affinity_domain prop) const noexcept
        {
            nmtools_string str;
            switch (prop) {
                case partition_affinity_domain::not_applicable:
                    str = "Not-Applicable"; break;
                case partition_affinity_domain::numa:
                    str = "NUMA"; break;
                case partition_affinity_domain::L4_cache:
                    str = "L4 Cache"; break;
                case partition_affinity_domain::L3_cache:
                    str = "L3 Cache"; break;
                case partition_affinity_domain::L2_cache:
                    str = "L2 Cache"; break;
                case partition_affinity_domain::L1_cache:
                    str = "L1 Cache"; break;
                case partition_affinity_domain::next_partitionable:
                    str = "Next-Partitionable"; break;
                default:
                    str = "UNKNOWN";
            }
            return str;
        }
    }; // partition_affinity_domain

    template <>
    struct to_string_t<
        ::sycl::id<3>, none_t
    > {
        auto operator()(const ::sycl::id<3>& idx) const noexcept
        {
            nmtools_string str;
            str += to_string(idx[0]); str += " ";
            str += to_string(idx[1]); str += " ";
            str += to_string(idx[2]);

            return str;
        }
    };

    template <auto N>
    struct to_string_t<
        ::sycl::range<N>, none_t
    >
    {
        auto operator()(const ::sycl::range<N>& range) const noexcept
        {
            nmtools_string str;
            for (size_t i=0; i<N; i++) {
                str += to_string(range[i]);
                if (i<(N-1)) {
                    str += ", ";
                }
            }
            return str;
        }
    };

    template <auto N>
    struct to_string_t<
        ::sycl::nd_range<N>, none_t
    >
    {
        auto operator()(const ::sycl::nd_range<N>& range) const noexcept
        {
            nmtools_string str;
            str += "global:";
            str += to_string(range.get_global_range());
            str += ",";
            str += to_string(range.get_local_range());
            str += ",";
            str += to_string(range.get_group_range());
            
            return str;
        }
    };

    template <typename T>
    struct to_string_t<
        std::vector<T>, none_t, meta::enable_if_t<!meta::is_num_v<T>>
    > {
        auto operator()(const std::vector<T>& props) const noexcept
        {
            nmtools_string str;
            for (size_t i=0; i<props.size(); i++) {
                str += to_string(props[i]);
                if (i<(props.size()-1)) {
                    str += ", ";
                }
            }
            return str;
        }
    };

    template <>
    struct to_string_t<
        std::string, none_t
    > {
        auto operator()(const std::string& string) const noexcept
        {
            nmtools_string str = string;
            return str;
        }
    };
}

namespace nmtools::array::sycl
{
    inline auto default_context()
    {
        static std::shared_ptr<context_t> default_context;
        if (!default_context) {
            auto sycl_devices = ::sycl::device::get_devices();
            auto platform_idx = 0ul;
            auto platform_name = std::string();
            if (auto env_idx = std::getenv("NMTOOLS_SYCL_DEFAULT_PLATFORM_IDX")) {
                platform_idx = std::stoi(env_idx);
            }
            if (auto env_name = std::getenv("NMTOOLS_SYCL_DEFAULT_PLATFORM")) {
                platform_name = env_name;
                std::transform(platform_name.begin(), platform_name.end(), platform_name.begin(), 
                   [](unsigned char c){ return std::tolower(c); }
                );
            }
            // TODO: better logging utilities
            std::cout << "\033[1;33m[nmtools sycl]\033[0m number of sycl devices: " << sycl_devices.size() << "\n";
            for (auto i=0ul; i<sycl_devices.size(); i++) {
                auto device = sycl_devices.at(i);
                auto platform = device.get_platform();

                std::cout << "\033[1;33m[nmtools sycl]\033[0m platform #" << i << ":\n";
                PRINT_SYCL_PLATFORM_PROPERTY(platform, name);
                PRINT_SYCL_PLATFORM_PROPERTY(platform, vendor);
                PRINT_SYCL_PLATFORM_PROPERTY(platform, version);
                PRINT_SYCL_PLATFORM_PROPERTY(platform, profile);
                PRINT_SYCL_PLATFORM_PROPERTY(platform, extensions);

                auto name = platform.get_info<::sycl::info::platform::name>();
                std::transform(name.begin(), name.end(), name.begin(), 
                   [](unsigned char c){ return std::tolower(c); }
                );
                if (name == platform_name) {
                    platform_idx = i;
                }
            }
            auto selected_device = sycl_devices.at(platform_idx);
            std::cout << "\033[1;33m[nmtools sycl]\033[0m default context using platform #" << platform_idx << "\n";
            // TODO: log level
            {
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, name);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, vendor);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, driver_version);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, profile);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, version);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, opencl_c_version);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, extensions);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, device_type);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, vendor_id);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_compute_units);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_work_item_dimensions);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_work_item_sizes<1>);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_work_item_sizes<2>);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_work_item_sizes<3>);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_work_group_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_vector_width_char);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_vector_width_short);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_vector_width_int);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_vector_width_long);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_vector_width_float);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_vector_width_double);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_vector_width_half);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, native_vector_width_char);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, native_vector_width_short);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, native_vector_width_int);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, native_vector_width_long);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, native_vector_width_float);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, native_vector_width_double);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, native_vector_width_half);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_clock_frequency);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, address_bits);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_mem_alloc_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image_support);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_read_image_args);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_write_image_args);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image2d_max_height);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image2d_max_width);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image3d_max_height);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image3d_max_width);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image3d_max_depth);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image_max_buffer_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, image_max_array_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_samplers);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_parameter_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, mem_base_addr_align);
                
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, half_fp_config);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, single_fp_config);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, double_fp_config);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, global_mem_cache_type);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, global_mem_cache_line_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, global_mem_cache_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, global_mem_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_constant_buffer_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, max_constant_args);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, local_mem_type);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, local_mem_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, error_correction_support);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, host_unified_memory);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, profiling_timer_resolution);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, is_endian_little);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, is_available);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, is_compiler_available);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, is_linker_available);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, execution_capabilities);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, queue_profiling);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, built_in_kernels);
                
                
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, printf_buffer_size);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, preferred_interop_user_sync);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, partition_max_sub_devices);
                
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, partition_properties);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, partition_affinity_domains);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, partition_type_property);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, partition_type_affinity_domain);
                PRINT_SYCL_DEVICE_PROPERTY(selected_device, reference_count);
            }
            default_context = std::make_shared<context_t>(selected_device);
        }
        return default_context;
    }
}

#undef PRINT_SYCL_PLATFORM_PROPERTY
#undef PRINT_SYCL_DEVICE_PROPERTY

#endif // NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP