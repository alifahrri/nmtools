#ifndef NMTOOLS_ARRAY_INDEX_REF_HPP
#define NMTOOLS_ARRAY_INDEX_REF_HPP

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
    // TODO: unify with pointer version below
    // simple wrapper that is aware to raw array
    template <typename array_t>
    struct ref
    {
        const array_t& array;
        
        constexpr ref(const array_t& array)
            : array(array) {}
        
        constexpr auto size() const
        {
            return len(array);
        }

        template <typename size_type>
        constexpr auto operator[](size_type i) const
        {
            return nmtools::at(array,i);
        }
    }; // ref

    template <typename array_t, typename size_type=size_t>
    struct ref_ptr
    {
        const array_t* array;
        const size_type size_;

        static_assert( meta::is_index_v<size_type>);
        
        constexpr ref_ptr(const array_t* array, size_type size_)
            : array(array)
            , size_(size_)
        {}
        
        constexpr auto size() const
        {
            return size_;
        }

        template <typename index_t>
        constexpr auto operator[](index_t i) const
        {
            return array[i];
        }
    }; // ref_ptr
} // nmtools::index

namespace nmtools
{
    // TODO: remove
    template <typename array_t>
    constexpr auto len(const index::ref<array_t>& array)
    {
        return array.size();
    } // len

    // TODO: remove
    template <typename array_t, typename index_t>
    constexpr auto at(const index::ref<array_t>& array, index_t i)
    {
        return at(array.array,i);
    } // len
} // namespace nmtools

namespace nmtools::impl
{
    template <typename array_t>
    struct len_t<index::ref<array_t>>
    {
        using array = const index::ref<array_t>&;
        using type  = decltype(meta::declval<array>().size());
        constexpr auto operator()(array a) const
        {
            return a.size();
        } // operator()
    };

    template <typename array_t, typename size_type>
    struct len_t<index::ref_ptr<array_t,size_type>>
    {
        using array = const index::ref_ptr<array_t,size_type>&;
        using type  = decltype(meta::declval<array>().size());
        constexpr auto operator()(array a) const
        {
            return a.size();
        } // operator()
    };
}


namespace nmtools::meta
{
    template <typename array_t>
    struct hybrid_index_array_max_size<
        index::ref<array_t>
    > : hybrid_index_array_max_size<array_t>
    {};

    template <typename array_t>
    struct fixed_index_array_size<
        index::ref<array_t>
    > : fixed_index_array_size<array_t>
    {};

    template <typename array_t>
    struct is_fixed_index_array<
        index::ref<array_t>
    > : is_fixed_index_array<array_t>
    {};

    template <typename array_t>
    struct is_hybrid_index_array<
        index::ref<array_t>
    > : is_hybrid_index_array<array_t>
    {};

    template <typename array_t>
    struct is_constant_index_array<
        index::ref<array_t>
    > : is_constant_index_array<array_t>
    {};

    template <typename array_t>
    struct is_dynamic_index_array<
        index::ref<array_t>
    > : is_dynamic_index_array<array_t>
    {};
    

    template <typename array_t, typename size_type>
    struct hybrid_index_array_max_size<
        index::ref_ptr<array_t,size_type>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_index_v<array_t> && is_clipped_integer_v<size_type>) {
                return size_type::Max;
            } else {
                // TODO: use specicif error type
                return detail::fail_t{};
            }
        }();
    };

    template <typename array_t, typename size_type>
    struct fixed_index_array_size<
        index::ref_ptr<array_t,size_type>
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_constant_index_v<size_type>) {
                return size_type::value;
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<index::ref_ptr<array_t,size_type>>{};
            }
        }();
    };

    template <typename array_t, typename size_type>
    struct is_fixed_index_array<
        index::ref_ptr<array_t,size_type>
    >
    {
        static constexpr auto value = is_index_v<array_t> && is_constant_index_v<size_type>;
    };

    template <typename array_t, typename size_type>
    struct is_hybrid_index_array<
        index::ref_ptr<array_t,size_type>
    >
    {
        static constexpr auto value = is_index_v<array_t> && is_clipped_integer_v<size_type>;
    };

    template <typename array_t, typename size_type>
    struct is_constant_index_array<
        index::ref_ptr<array_t,size_type>
    > : false_type {};

    template <typename array_t, typename size_type>
    struct is_dynamic_index_array<
        index::ref_ptr<array_t,size_type>
    >
    {
        static constexpr auto value = is_index_v<array_t> && !is_constant_index_v<size_type> && !is_clipped_integer_v<size_type> && is_index_v<size_type>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_REF_HPP