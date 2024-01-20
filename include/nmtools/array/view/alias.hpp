#ifndef NMTOOLS_ARRAY_VIEW_ALIAS_HPP
#define NMTOOLS_ARRAY_VIEW_ALIAS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

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
        using id_type = id_t;

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

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            return pack_indices(indices...);
        } // index
    }; // alias_t

    template <typename T, typename id_t>
    struct alias_t<T*, id_t, meta::enable_if_t<meta::is_num_v<T>>>
    {
        using value_type = T;
        using const_reference = const value_type&;
        using array_type = const T*;
        using id_type = id_t;

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

    template <typename array_t, typename id_t=none_t>
    constexpr auto alias(const array_t& array, id_t id=id_t{})
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        return decorator_t<alias_t,array_t,id_t>{array,id};
    } // alias

    template <typename T, typename id_t=none_t>
    constexpr auto alias(const T* ptr, size_t numel, id_t id=id_t{})
    {
        return decorator_t<alias_t,meta::remove_address_space_t<T*>, id_t>{{ptr,numel,id}};
    }
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename id_t>
    struct is_ndarray< view::decorator_t<view::alias_t, array_t, id_t> >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    // specialization for ptr
    template <typename array_t, typename id_t>
    struct is_ndarray< view::decorator_t<view::alias_t, array_t*, id_t> >
    {
        static constexpr auto value = is_num_v<array_t>;
    };

    template <typename T, typename id_t>
    struct get_element_type<
        view::decorator_t<view::alias_t,T*,id_t>
    >
    {
        using type = meta::remove_address_space_t<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ALIAS_HPP