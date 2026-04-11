#ifndef NMTOOLS_CORE_CONTEXT_HPP
#define NMTOOLS_CORE_CONTEXT_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/index/product.hpp"

namespace nmtools
{
    // combine evaluator, context, type resolver, array creation to single "context" object

    template <typename Derived>
    struct base_context_t
    {
        // TODO: implement eval(view), and mutate(buffer) = view;

        static constexpr auto max_static_buffer_bytes = 2 << 20;

        template <typename T, typename shape_t, typename m_size_t=none_t>
        static constexpr auto get_buffer_vtype(as_value<T>, const shape_t&, [[maybe_unused]] const m_size_t = m_size_t{})
        {
            if constexpr (is_constant_index_array_v<shape_t>) {
                constexpr auto size = index::product(shape_t{});
                constexpr auto byte_size = sizeof(T) * size;
                if constexpr (byte_size > max_static_buffer_bytes) {
                    using type = nmtools_list<T>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_array<T,size>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_constant_index_v<m_size_t>) {
                constexpr auto size = m_size_t::value;
                constexpr auto byte_size = sizeof(T) * size;
                if constexpr (byte_size > max_static_buffer_bytes) {
                    using type = nmtools_list<T>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_array<T,size>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_clipped_index_v<m_size_t>) {
                constexpr auto max_size = max_value_v<m_size_t>;
                constexpr auto byte_size = sizeof(T) * max_size;
                if constexpr (byte_size > max_static_buffer_bytes) {
                    using type = nmtools_list<T>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_static_vector<T,max_size>;
                    return as_value_v<type>;
                }
            } else {
                using type = nmtools_list<T>;
                return as_value_v<type>;
            }
            // TODO: handle clipped shape
        }

        template <typename T, typename shape_t, typename size_t=none_t>
        static constexpr auto get_buffer_vtype(dtype_t<T>, const shape_t& shape, const size_t size = size_t{})
        {
            return get_buffer_vtype(as_value_v<T>,shape,size);
        }

        constexpr Derived* self()
        {
            return static_cast<Derived*>(this);
        }

        constexpr const Derived* self() const
        {
            return static_cast<const Derived*>(this);
        }
    };
}

namespace nmtools::meta
{
    template <typename T>
    struct is_context : is_base_of<base_context_t<T>,T> {};

    template <typename T>
    struct is_context<const T> : is_context<T> {};

    template <typename T>
    struct is_context<T&> : is_context<T> {};

    template <typename T>
    constexpr inline auto is_context_v = is_context<T>::value;
}

namespace nmtools
{
    using meta::is_context_v;
}

#endif // NMTOOLS_CORE_CONTEXT_HPP