#ifndef NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP
#define NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval/kernel_helper.hpp"
#include "nmtools/exception.hpp"

#include <sycl/sycl.hpp>
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

namespace nmtools::array::sycl
{
    template <typename T>
    using device_mem_ptr = std::shared_ptr<::sycl::buffer<T>>;

    // TODO: check sycl spec for built-in write-only buffer memory
    template <typename T>
    using host_mem_ptr = std::shared_ptr<T>;

    struct context_t
    {
        using queue_t = ::sycl::queue;

        std::shared_ptr<queue_t> queue;

        context_t()
            : queue(std::make_shared<queue_t>())
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
            auto flat_array = view::mutable_flatten(array);
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

                // .accessor() sycl-equivalent to cudaMemcpy + pass to kernel (?)
                auto operands = nmtools_tuple{get_accessor(nmtools::get<Is>(args_pack),cgh,access_mode)...};

                auto kernel_range = ::sycl::range<1>(thread_size);
                cgh.parallel_for(kernel_range,[=](::sycl::id<1> id){
                    auto output = create_mutable_array(&output_accessor[0],&output_shape_accessor[0],output_dim);
                    auto result = functional::apply(f,operands);
                    // TODO: properly get the thread & kernel id and shape
                    auto thread_id  = array::kernel_size<size_t>{id.get(0),0,0};
                    auto block_id   = array::kernel_size<size_t>{0,0,0};
                    auto block_size = array::kernel_size<size_t>{1,1,1};
                    array::assign_result(output,result,thread_id,block_id,block_size);
                });
            });

            this->copy_buffer(output_buffer,output);
        }

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


            using sequence_t = meta::make_index_sequence<meta::len_v<decltype(device_operands)>>;
            this->run_(output,f,device_operands,sequence_t{});
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

#endif // NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP