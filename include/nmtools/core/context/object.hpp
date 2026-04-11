#ifndef NMTOOLS_CORE_CONTEXT_OBJECT_HPP
#define NMTOOLS_CORE_CONTEXT_OBJECT_HPP

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
    template <auto broadcast_enable=true, template <typename...>typename layout_t=row_major_offset_t>
    struct object_context_t : base_context_t<object_context_t<broadcast_enable,layout_t>>
    {
        // NOTE: actually unused
        // TODO: remove resolver when evalv2 is finalized
        using resolver_type = object_eval_resolver_t<>;

        using base_type = base_context_t<object_context_t<broadcast_enable,layout_t>>;

        constexpr auto col_major() const noexcept
        {
            return object_context_t<broadcast_enable,column_major_offset_t>{};
        }

        constexpr auto row_major() const noexcept
        {
            return object_context_t<broadcast_enable,row_major_offset_t>{};
        }

        constexpr auto enable_broadcast() const noexcept
        {
            return object_context_t<true,layout_t>{};
        }

        constexpr auto disable_broadcast() const noexcept
        {
            return object_context_t<false,layout_t>{};
        }

        template <auto new_broadcast>
        constexpr auto broadcast(ct<new_broadcast>) const noexcept
        {
            return object_context_t<new_broadcast,layout_t>{};
        }

        template <typename buffer_t, typename shape_t>
        constexpr auto create(as_value<buffer_t>, as_value<shape_t>) const noexcept
        {
            using result_t = object_t<buffer_t,shape_t,resolve_stride_type_t,layout_t,resolver_type,object_context_t,broadcast_enable>;

            auto result = result_t {};
            return result;
        }

        template <typename buffer_t, typename shape_t>
        constexpr auto create(as_value<buffer_t>, const shape_t& shape) const
        {
            using result_t = object_t<buffer_t,shape_t,resolve_stride_type_t,layout_t,resolver_type,object_context_t,broadcast_enable>;

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
            // in object context we want to unwrap to return object
            using element_t = get_element_type_t<view_t>;
            auto output = create(dtype_t<element_t>{},shape<true>(unwrap(view)),size<true>(unwrap(view)));
            this->eval(output,unwrap(view));
            return output;
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
            // in object context we want to unwrap to return object
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

            auto n = inp_index.size();
            for (size_t i=0; i<n; i++) {
                // while the shape is the same,
                // the underlying type of indexing may be not
                auto inp_idx = inp_index[i];
                auto out_idx = out_index[i];
                apply_at(output,out_idx) = apply_at(unwrap(view),inp_idx);
            }
        }

        template <typename view_t>
        constexpr auto eval(const view_t& view) const
        {
            // in object context we want to unwrap to return object
            auto shape = nmtools::shape(unwrap(view));
            using T = get_element_type_t<view_t>;

            auto result = create(dtype_t<T>{},shape);
            eval(result,unwrap(view));

            return result;
        }
    };

    constexpr inline auto Object = object_context_t<>{};
}

#endif // NMTOOLS_CORE_CONTEXT_OBJECT_HPP