#ifndef NMTOOLS_ARRAY_INDEX_REF_HPP
#define NMTOOLS_ARRAY_INDEX_REF_HPP

#include "nmtools/array/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::index
{
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
        constexpr auto at(size_type i) const
        {
            return nmtools::at(array,i);
        }

        template <typename size_type>
        constexpr auto at(size_type i)
        {
            return nmtools::at(array,i);
        }
    }; // ref
} // nmtools::index

namespace nmtools
{
    template <typename array_t>
    constexpr auto len(const index::ref<array_t>& array)
    {
        return array.size();
    }
} // namespace nmtools


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
}

#endif // NMTOOLS_ARRAY_INDEX_REF_HPP