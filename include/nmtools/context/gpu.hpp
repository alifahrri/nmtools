#ifndef NMTOOLS_CONTEXT_GPU_HPP
#define NMTOOLS_CONTEXT_GPU_HPP

#include "nmtools/core/context.hpp"
#include "nmtools/core/transform/linearize.hpp"
#include "nmtools/context/kernel.hpp"

namespace nmtools
{
    template <typename derived_t>
    struct gpu_base_context_t
    {
        constexpr derived_t* self()
        {
            return static_cast<derived_t*>(this);
        }

        constexpr const derived_t* self() const
        {
            return static_cast<const derived_t*>(this);
        }

        template <typename array_t>
        auto create_buffer(const array_t& array)
        {
            static_assert((
                is_ndarray_v<array_t>
                || is_num_v<array_t>
                || is_constant_index_array_v<array_t>
                ) &&
                !is_view_v<array_t>
                , "unsupported array type for create_buffer"
            );
            if constexpr (is_ndarray_v<array_t>) {
                auto data_ptr = nmtools::data(array);
                auto numel    = nmtools::size(array);
                return self()->create_buffer(data_ptr,numel);
            } else if constexpr (is_constant_index_array_v<array_t>) {
                constexpr auto value = to_value_v<array_t>;
                return self()->create_buffer(value);
            } else {
                return self()->create_buffer(&array,1);
            }
        }

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
            }, nmtools_tuple{});

            using sequence_t = meta::make_index_sequence<meta::len_v<decltype(gpu_args_pack)>>;
            self()->run_(output,f,gpu_args_pack,sequence_t{});
            #else
            constexpr auto N = sizeof...(operands_t);
            auto device_operands = meta::template_reduce<N>([&](auto init, auto index){
                const auto& arg_i = nmtools::at(operands,index);
                if constexpr (meta::is_num_v<decltype(arg_i)>) {
                    return utility::tuple_append(init,arg_i);
                } else {
                    auto device_array = self()->create_array(*arg_i);
                    return utility::tuple_append(init,device_array);
                }
            }, nmtools_tuple{});

            // e.g. to convert dynamic allocation to static vector to run on device kernels
            // TODO: rename to "make_bounded" or something
            auto fn = map_to_device(f);
            using sequence_t = meta::make_index_sequence<meta::len_v<decltype(device_operands)>>;
            self()->run_(output,fn,device_operands,sequence_t{});
            #endif
        }

        template <typename view_t>
        constexpr auto eval(none_t, const view_t& view)
        {
            return self()->eval(view);
        }

        static constexpr auto object_enable = false;

        template <typename view_t>
        auto eval(const view_t& view)
        {
            if constexpr (meta::is_either_v<view_t>) {
                using left_t   = meta::get_either_left_t<view_t>;
                using right_t  = meta::get_either_right_t<view_t>;
                // deduce return type for each type
                using rleft_t  = decltype(self()->eval(meta::declval<left_t>()));
                using rright_t = decltype(self()->eval(meta::declval<right_t>()));
                constexpr auto vtype = [](){
                    if constexpr (meta::is_same_v<rleft_t,rright_t>) {
                        return as_value_v<rleft_t>;
                    } else {
                        using either_t = meta::replace_either_t<view_t,rleft_t,rright_t>;
                        return as_value_v<either_t>;
                    }
                }();
                using return_t = meta::type_t<decltype(vtype)>;
                // match either type at runtime
                if (auto view_ptr = nmtools::get_if<left_t>(&view)) {
                    return return_t{self()->eval(*view_ptr)};
                } else /* if (auto view_ptr = get_if<right_t>(&view)) */ {
                    auto view_rptr = nmtools::get_if<right_t>(&view);
                    return return_t{self()->eval(*view_rptr)};
                }
            } else if constexpr (is_maybe_v<view_t> && !object_enable) {
                using view_type   = meta::get_maybe_type_t<view_t>;
                using result_type = decltype(self()->eval(meta::declval<view_type>()));
                static_assert(!is_maybe_v<result_type>);
                using return_type = nmtools_maybe<result_type>;
                return (view
                    ? return_type{self()->eval(*view)}
                    : return_type{meta::Nothing}
                );
            } else {
                auto graph = functional::linearize(functional::get_compute_graph(unwrap(view)));
                auto operands = functional::get_operands(graph);
                auto function = functional::get_function(graph);
                auto functor  = function.functor;

                auto shape = nmtools::shape<true>(unwrap(view));
                auto size  = nmtools::size<true>(unwrap(view));
                using T = get_element_type_t<remove_cvref_t<decltype(unwrap(view))>>;
                auto result = self()->create(dtype_t<T>{},shape,size);
                self()->run(functor,result,operands);

                return result;
            }
        }
    };
}

#endif // NMTOOLS_CONTEXT_GPU_HPP