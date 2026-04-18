#ifndef NMTOOLS_CONTEXT_DEFAULT_HPP
#define NMTOOLS_CONTEXT_DEFAULT_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/index/ndindex.hpp"
#include "nmtools/ndarray/array.hpp"
#include "nmtools/core/context.hpp"

namespace nmtools
{
    template <auto broadcast_enable
        , auto object_enable
        , auto unroll_enable
        , template <typename...>typename layout_t>
    struct default_context_t
        : base_context_t<default_context_t<broadcast_enable,object_enable,unroll_enable,layout_t>>
    {
        // if broadcast is disabled, then object must be enabled
        static_assert(
            (!broadcast_enable ? object_enable : true)
        );

        static constexpr auto broadcasting = broadcast_enable;

        using base_type = base_context_t<default_context_t<broadcast_enable,object_enable,unroll_enable,layout_t>>;

        constexpr auto col_major() const noexcept
        {
            return default_context_t<broadcast_enable,object_enable,unroll_enable,column_major_offset_t>{};
        }

        constexpr auto row_major() const noexcept
        {
            return default_context_t<broadcast_enable,object_enable,unroll_enable,row_major_offset_t>{};
        }

        constexpr auto enable_broadcast() const noexcept
        {
            return default_context_t<true,object_enable,unroll_enable,layout_t>{};
        }

        constexpr auto disable_broadcast() const noexcept
        {
            return default_context_t<false,object_enable,unroll_enable,layout_t>{};
        }

        template <typename new_broadcast_t=true_type>
        constexpr auto broadcast(new_broadcast_t=new_broadcast_t{}) const noexcept
        {
            constexpr auto new_broadcast = new_broadcast_t::value;
            return default_context_t<new_broadcast,object_enable,unroll_enable,layout_t>{};
        }

        template <typename new_object_t=true_type>
        constexpr auto object(new_object_t=new_object_t{}) const noexcept
        {
            constexpr auto new_object = new_object_t::value;
            return default_context_t<broadcast_enable,new_object,unroll_enable,layout_t>{};
        }

        template <typename buffer_t, typename shape_t>
        constexpr auto create(as_value<buffer_t>, as_value<shape_t>) const noexcept
        {
            static_assert( is_constant_index_array_v<shape_t> || !unroll_enable );

            using result_t = conditional_t<object_enable
                , object_t<buffer_t,shape_t,resolve_stride_type_t,layout_t,default_context_t,broadcast_enable>
                , ndarray_t<buffer_t,shape_t,resolve_stride_type_t,layout_t>
            >;

            auto result = result_t {};
            return result;
        }

        template <typename buffer_t, typename shape_t>
        constexpr auto create(as_value<buffer_t>, const shape_t& shape) const
        {
            static_assert( is_constant_index_array_v<shape_t> || !unroll_enable );

            using result_t = conditional_t<object_enable
                , object_t<buffer_t,shape_t,resolve_stride_type_t,layout_t,default_context_t,broadcast_enable>
                , ndarray_t<buffer_t,shape_t,resolve_stride_type_t,layout_t>
            >;

            auto result = result_t {};
            if constexpr (!is_constant_index_array_v<shape_t>) {
                result.resize(shape);
            }
            return result;
        }

        template <typename T, typename shape_t, typename m_size_t=none_t>
        constexpr auto create(dtype_t<T> dtype
            , const shape_t& shape
            , [[maybe_unused]] const m_size_t size=m_size_t{}) const
        {
            if constexpr (is_none_v<shape_t>) {
                return T{0};
            } else {
                auto buffer_vtype = base_type::get_buffer_vtype(dtype,shape,size);
                return create(buffer_vtype, shape);
            }
        }

        template <typename T, typename shape_t>
        constexpr auto full(const shape_t& shape, T t) const
        {
            auto buffer_vtype = base_type::get_buffer_vtype(as_value_v<T>, shape);
            auto result = create(buffer_vtype,shape);
            for (nm_size_t i=0; i<result.size(); i++) {
                result.data_[i] = t;
            }
            return result;
        }

        template <typename shape_t, typename T=float>
        constexpr auto zeros(const shape_t& shape, dtype_t<T> = dtype_t<T>{}) const
        {
            return full(shape, static_cast<T>(0));
        }

        template <typename shape_t, typename T=float>
        constexpr auto ones(const shape_t& shape, dtype_t<T> = dtype_t<T>{}) const
        {
            return full(shape, static_cast<T>(1));
        }

        template <typename view_t>
        constexpr auto eval(none_t, const view_t& view) const
        {
            return this->eval(view);
        }

        template <typename output_t, typename view_t>
        constexpr auto eval(output_t& output, const view_t& view) const
            -> enable_if_t<is_num_v<output_t> && is_num_v<view_t>>
        {
            output = static_cast<output_t>(view);
        }

        template <typename output_t, typename view_t>
        constexpr auto eval(output_t& output, const view_t& view) const
            -> enable_if_t<!is_none_v<output_t> && !is_num_v<output_t>>
        {
            auto out_shape = shape(output);
            auto inp_shape = shape(unwrap(view));
            auto is_equal  = utils::isequal(out_shape,inp_shape);
            if (!is_equal) {
                nmtools_assert( is_equal
                    , "mismatched shape for eval"
                );
            }

            auto out_index = index::ndindex(out_shape);
            auto inp_index = index::ndindex(inp_shape);

            if constexpr (!unroll_enable) {
                auto n = inp_index.size();
                for (size_t i=0; i<n; i++) {
                    // while the shape is the same,
                    // the underlying type of indexing may be not
                    auto inp_idx = inp_index[i];
                    auto out_idx = out_index[i];
                    apply_at(output,out_idx) = apply_at(unwrap(view),inp_idx);
                }
            } else {
                constexpr auto OUT_SIZE = len_v<decltype(out_index)>;
                constexpr auto INP_SIZE = len_v<decltype(inp_index)>;
                static_assert( (OUT_SIZE > 0) && (INP_SIZE > 0) );

                const auto out_stride = index::compute_strides(out_shape);
                // const auto inp_stride = index::compute_strides(inp_shape);
                template_for<OUT_SIZE>([&](auto i){
                    auto inp_idx = inp_index[i];
                    auto out_idx = out_index[i];
                    // auto flat_inp_idx = index::compute_offset(inp_idx,inp_stride);
                    auto flat_out_idx = index::compute_offset(out_idx,out_stride);
                    output.data()[flat_out_idx] = apply_at(view,inp_idx);
                });
            }
        }

        template <typename view_t>
        constexpr auto eval(const view_t& view) const
        {
            if constexpr (meta::is_either_v<view_t>) {
                using left_t   = meta::get_either_left_t<view_t>;
                using right_t  = meta::get_either_right_t<view_t>;
                // deduce return type for each type
                using rleft_t  = decltype(this->eval(meta::declval<left_t>()));
                using rright_t = decltype(this->eval(meta::declval<right_t>()));
                constexpr auto vtype = [](){
                    if constexpr (meta::is_same_v<rleft_t,rright_t>) {
                        return meta::as_value_v<rleft_t>;
                    } else {
                        using either_t = meta::replace_either_t<view_t,rleft_t,rright_t>;
                        return meta::as_value_v<either_t>;
                    }
                }();
                using return_t = meta::type_t<decltype(vtype)>;
                // match either type at runtime
                if (auto view_ptr = nmtools::get_if<left_t>(&view)) {
                    return return_t{this->eval(*view_ptr)};
                } else /* if (auto view_ptr = get_if<right_t>(&view)) */ {
                    auto view_rptr = nmtools::get_if<right_t>(&view);
                    return return_t{this->eval(*view_rptr)};
                }
            } else if constexpr (meta::is_maybe_v<view_t> && !object_enable) {
                using view_type   = meta::get_maybe_type_t<view_t>;
                using result_type = decltype(this->eval(meta::declval<view_type>()));
                static_assert(!meta::is_maybe_v<result_type>);
                using return_type = nmtools_maybe<result_type>;
                return (view
                    ? return_type{this->eval(*view)}
                    : return_type{meta::Nothing}
                );
            } else {
                auto shape = nmtools::shape<true>(unwrap(view));
                auto size  = nmtools::size<true>(unwrap(view));
                using T = get_element_type_t<remove_cvref_t<decltype(unwrap(view))>>;
                using element_t = conditional_t<is_same_v<T,bool>,nm_bool_t,T>;

                auto result = create(dtype_t<element_t>{},shape,size);
                eval(result,unwrap(view));

                return result;
            }
        }
    };

    template <auto broadcast_enable=true
        , auto unroll_enable=false
        , template <typename...>typename layout_t=row_major_offset_t>
    using object_context_t = default_context_t<broadcast_enable,true,unroll_enable,layout_t>;

    template <auto broadcast_enable=true
        , auto object_enable=false
        , template <typename...>typename layout_t=row_major_offset_t>
    using unroll_context_t = default_context_t<broadcast_enable,object_enable,true,layout_t>;

    constexpr inline auto Object  = object_context_t<>{};
    constexpr inline auto Unroll  = unroll_context_t<>{};
    constexpr inline auto Default = default_context_t<>{};
}

#endif // NMTOOLS_CONTEXT_DEFAULT_HPP