#ifndef NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP
#define NMTOOLS_ARRAY_EVAL_SYCL_CONTEXT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval/kernel_helper.hpp"
#include "nmtools/exception.hpp"

#include <sycl/sycl.hpp>
#include <memory>

namespace nmtools::array::sycl
{
    template <typename T>
    using device_mem_ptr = std::shared_ptr<::sycl::buffer<T>>;

    // TODO: check sycl spec for built-in write-only buffer memory
    template <typename T>
    using host_mem_ptr = std::shared_ptr<T>;

    class sycl_exception : public exception
    {
        public:
        sycl_exception(const std::string& message)
            : exception(message)
        {}
    };

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
            for (size_t i=0; i<size; i++) {
                at(flat_array,i) = host_accessor[i];
            }
        }

        template <typename function_t, typename output_array_t, typename arg0_t, typename...args_t>
        auto run(const function_t& f, output_array_t& output, const arg0_t& arg0, const args_t&...args)
        {
            auto args_pack = [&](){
                if constexpr (meta::is_tuple_v<arg0_t>) {
                    static_assert( sizeof...(args_t) == 0 );
                    return static_cast<const arg0_t&>(arg0);
                } else {
                    return nmtools_tuple<const arg0_t&, const args_t&...>{arg0,args...};
                }
            }();
            constexpr auto N = meta::len_v<decltype(args_pack)>;
            auto device_args_pack = meta::template_reduce<N>([&](auto init, auto index){
                const auto& arg_i = *nmtools::get<index>(args_pack);
                // TODO: pass actual type (constant / clipped shape) as is to device
                auto arg_shape = nmtools::shape<false,/*disable_clipped_index*/true>(arg_i);
                auto arg_dim   = nmtools::len(arg_shape);

                auto device_buffer = this->create_buffer(arg_i);
                // TODO: allow constant/clipped index shape
                auto device_shape = this->create_buffer(arg_shape);
                auto buffer_shape_pack = utility::tuple_cat(nmtools::get<0>(init),nmtools_tuple{device_buffer,device_shape});
                auto args_dim_pack = utility::tuple_append(nmtools::get<1>(init),arg_dim);
                return nmtools_tuple{buffer_shape_pack,args_dim_pack};
            }, nmtools_tuple<nmtools_tuple<>,nmtools_tuple<>>{});

            using element_t = meta::get_element_type_t<output_array_t>;
            auto numel = nmtools::size(output);
            // TODO: pass actual type (constant / clipped shape) as is to device
            auto output_shape = nmtools::shape<false,/*disable_clipped_index*/true>(output);
            auto output_dim   = nmtools::dim(output);

            auto output_buffer = this->create_buffer<element_t>(numel);
            auto shape_buffer  = this->create_buffer(output_shape);

            queue->submit([&](::sycl::handler& cgh){
                // create accessor
                auto& buffer_shape_pack = nmtools::get<0>(device_args_pack);
                auto& dim_pack = nmtools::get<1>(device_args_pack);
                constexpr auto N = meta::len_v<decltype(buffer_shape_pack)>;
                auto accessor_pack = meta::template_reduce<N>([&](auto init, auto index){
                    constexpr auto buffer_idx = size_t(index);
                    auto buffer_ptr = nmtools::get<buffer_idx>(buffer_shape_pack);
                    auto accessor = ::sycl::accessor(*buffer_ptr, cgh, ::sycl::read_only);
                    return utility::tuple_append(init,accessor);
                }, nmtools_tuple<>{});

                auto warp_size   = 32;
                auto thread_size = size_t(std::ceil(float(numel) / warp_size)) * warp_size;

                auto output_accessor = ::sycl::accessor(*output_buffer, cgh, ::sycl::write_only);
                auto output_shape_accessor = ::sycl::accessor(*shape_buffer, cgh, ::sycl::read_only);

                cgh.parallel_for(::sycl::range<1>(thread_size),[=](::sycl::id<1> id){
                    auto output = create_mutable_array(&output_accessor[0],&output_shape_accessor[0],output_dim);
                    auto result = [&](){
                        if constexpr (N == 0) {
                            return f();
                        } else {
                            return meta::template_reduce<N/2>([&](auto init, auto index){
                                constexpr auto ptr_idx = (size_t)index * 2;
                                constexpr auto shp_idx = ptr_idx + 1;
                                constexpr auto dim_idx = (size_t)index / 2;
                                auto array = create_array(
                                    nmtools::get<ptr_idx>(accessor_pack).get_pointer().get()
                                    , nmtools::get<shp_idx>(accessor_pack).get_pointer().get()
                                    , nmtools::get<dim_idx>(dim_pack)
                                );
                                return init (array);
                            },f);
                        }
                    }();
                    auto assign_array = [&](auto& output, const auto& array){
                        auto size = numel;
                        auto idx = id.get(0);
                        if (idx < size) {
                            auto flat_lhs = view::mutable_flatten(output);
                            auto flat_rhs = view::flatten(array);
                            const auto rhs = flat_rhs(idx);
                            auto& lhs = flat_lhs(idx);
                            lhs = rhs;
                        }
                    };
                    using result_t = decltype(result);
                    if constexpr (meta::is_maybe_v<result_t>) {
                        static_assert( meta::is_ndarray_v<meta::get_maybe_type_t<result_t>> );
                        assign_array(output,*result);
                    } else {
                        static_assert( meta::is_ndarray_v<result_t> );
                        assign_array(output,result);
                    }
                });

                this->copy_buffer(output_buffer,output);
            });
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