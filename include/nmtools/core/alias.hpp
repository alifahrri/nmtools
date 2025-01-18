#ifndef NMTOOLS_ARRAY_VIEW_ALIAS_HPP
#define NMTOOLS_ARRAY_VIEW_ALIAS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/array/index/max.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/core/decorator.hpp"

namespace nmtools::view
{
    template <typename array_t, typename id_t=none_t, typename=void>
    struct alias_t
    {
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;

        // TODO: assert id is constant index (or none)
        using id_type = id_t;

        static constexpr auto operands_ids = nmtools_tuple{id_type{}};

        // const reference to actual array type
        array_type array;
        id_type id;

        /**
         * @brief construct alias view
         * 
         */
        constexpr alias_t(const array_t& array, id_t id)
            : array(initialize<array_type>(array))
            , id(id)
        {}

        constexpr auto attribute() const noexcept
        {
            return nmtools_tuple{id};
        }

        constexpr auto shape() const
        {
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<array_type>>) {
                return nmtools::shape<true>(*array);
            } else {
                return nmtools::shape<true>(array);
            }
        }

        constexpr auto dim() const
        {
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<array_type>>) {
                return nmtools::dim<true>(*array);
            } else {
                return nmtools::dim<true>(array);
            }
        }

        constexpr auto size() const
        {
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<array_type>>) {
                return nmtools::size<true>(*array);
            } else {
                return nmtools::size<true>(array);
            }
        }

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        } // operands

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            return pack_indices(indices...);
        } // index
    }; // alias_t

    template <typename array_t, typename id_t>
    struct alias_t<array_t,id_t,meta::enable_if_t<meta::is_num_v<array_t>>>
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = resolve_array_type_t<array_t>;
        using id_type = id_t;

        static constexpr auto operands_ids = nmtools_tuple{id_type{}};

        array_type array;
        id_type id;

        constexpr alias_t(const array_t& array, id_t id)
            : array(array)
            , id(id)
        {}

        constexpr operator value_type() const
        {
            return array;
        }

        constexpr auto attribute() const noexcept
        {
            return nmtools_tuple{id};
        }

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        } // operands
    }; // alias

    template <typename T, typename id_t>
    struct alias_t<T*, id_t, meta::enable_if_t<meta::is_num_v<T>>>
    {
        using value_type = T;
        using const_reference = const value_type&;
        using array_type = const T*;
        using id_type = id_t;

        static constexpr auto operands_ids = nmtools_tuple{id_type{}};

        array_type array;
        size_t numel;
        id_type id;

        constexpr alias_t(const T* ptr, size_t numel, id_type id)
            : array(ptr)
            , numel(numel)
            , id(id)
        {}

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{id};
        }

        constexpr auto dim() const
        {
            return meta::ct_v<1>;
        }

        constexpr auto shape() const
        {
            #if 0
            // broken on c++ for opencl 😭
            // error: field may not be qualified with an address space
            return nmtools_array{numel};
            #else
            return nmtools_array<size_t,1>{numel};
            #endif
        }

        template <typename...size_types>
        constexpr auto operator()(const size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            return array[at(indices_,meta::ct_v<0>)];
        }
    };

    // TODO: drop none default, make id mandatory
    template <typename array_t, typename id_t=none_t>
    constexpr auto alias(const array_t& array, id_t id=id_t{})
    {
        // TODO: handle either type
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type  = meta::get_maybe_type_t<array_t>;
            using result_type = decltype(alias(meta::declval<array_type>(),id));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>,result_type,nmtools_maybe<result_type>>;
            return (static_cast<bool>(array)
                ? return_type{alias(*array,id)}
                : return_type{meta::Nothing}
            );
        } else if constexpr (meta::is_same_view_v<alias_t,array_t> && !is_none_v<id_t>) {
            // Quick-hack: aliasing an alias will rename
            const auto& m_array = array.array;
            if constexpr (meta::is_pointer_v<meta::remove_cvref_t<decltype(m_array)>>) {
                return alias(*array.array,id);
            } else {
                return alias(array.array,id);
            }
        } else if constexpr (meta::is_view_v<array_t>) {
            // view is already aliased
            static_assert( array_t::id_type::value == id_t::value );
            return array;
        } else {
            return decorator_t<alias_t,array_t,id_t>{{array,id}};
        }
    } // alias

    template <typename...arrays_t>
    constexpr auto aliased(const arrays_t&...arrays)
    {
        auto array_pack = pack_operands(arrays...);
        auto f = [](const auto& array_pack){
            constexpr auto N = sizeof...(arrays);
            constexpr auto initial_ids = meta::template_reduce<N>([&](auto init, auto index){
                using array_type = decltype(unwrap(at(array_pack,index)));
                constexpr auto id = get_id_v<meta::remove_cvref_pointer_t<array_type>>;
                return utility::tuple_append(init,meta::ct_v<(nm_index_t)id>);
            },nmtools_tuple{});
            constexpr auto max_id    = index::max(meta::to_value_v<decltype(initial_ids)>);
            constexpr auto offset_id = max_id + 1; // if max_id: -1, then offset 0
            constexpr auto final_ids = meta::template_reduce<N>([&](auto init, auto index){
                constexpr auto id = at(initial_ids,index);
                constexpr auto final_id = ((id < 0) ? (offset_id + index) : id);
                return utility::tuple_append(init,meta::ct_v<final_id>);
            },nmtools_tuple{});
            auto aliased = meta::template_reduce<N>([&](auto init, auto index){
                const auto& array = at(array_pack,index);
                if constexpr (meta::is_pointer_v<meta::remove_cvref_pointer_t<decltype(array)>>) {
                    return append_operands(init,alias(*array,at(final_ids,index)));
                } else {
                    return append_operands(init,alias(array,at(final_ids,index)));
                }
            },nmtools_tuple{});
            if constexpr (N == 1) {
                return nmtools::get<0>(aliased);
            } else {
                return aliased;
            }
        };
        if constexpr (meta::is_maybe_v<decltype(array_pack)>) {
            using result_t = decltype(f(unwrap(array_pack)));
            using return_t = nmtools_maybe<result_t>;
            return (array_pack
                ? return_t{f(unwrap(array_pack))}
                : return_t{meta::Nothing}
            );
        } else {
            return f(array_pack);
        }
    } // aliased

    template <typename T, typename id_t=none_t>
    constexpr auto alias(const T* ptr, size_t numel, id_t id=id_t{})
    {
        return decorator_t<alias_t,meta::remove_address_space_t<T*>, id_t>{{ptr,numel,id}};
    }
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename...args_t>
    struct is_ndarray< view::decorator_t<view::alias_t, array_t, args_t...> >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    template <typename array_t, typename...args_t>
    struct is_num< view::decorator_t<view::alias_t, array_t, args_t...> >
    {
        static constexpr auto value = is_num_v<array_t>;
    };

    // specialization for ptr
    template <typename array_t, typename...args_t>
    struct is_ndarray< view::decorator_t<view::alias_t, array_t*, args_t...> >
    {
        static constexpr auto value = is_num_v<array_t>;
    };

    template <typename array_t, typename...args_t>
    struct get_element_type<
        view::decorator_t<view::alias_t, array_t, args_t...>
    >
    {
        using type = get_element_type_t<array_t>;
    };

    template <typename T, typename...args_t>
    struct get_element_type<
        view::decorator_t<view::alias_t,T*,args_t...>
    >
    {
        using type = meta::remove_address_space_t<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ALIAS_HPP