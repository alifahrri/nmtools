#ifndef NMTOOLS_ARRAY_INDEX_NDENUMERATE_HPP
#define NMTOOLS_ARRAY_INDEX_NDENUMERATE_HPP

#include "nmtools/array/index/ndindex.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::index
{
    /**
     * @brief Makes array_t iterable with single for loop.
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct ndenumerate_t
    {
        using array_type = const array_t&;
        static constexpr auto shape_vtype = [](){
            using shape_type = meta::remove_cvref_t<decltype(nmtools::shape(meta::declval<array_t>()))>;
            if constexpr (meta::is_constant_index_array_v<shape_type>) {
                return meta::as_value_v<decltype(meta::to_value_v<shape_type>)>;
            } else {
                return meta::as_value_v<shape_type>;
            }
        }();
        using shape_type = meta::type_t<decltype(shape_vtype)>;
        // for now assume array_t has default constructor
        using ndindex_type = ndindex_t<shape_type>;
        using element_type = meta::get_element_type_t<array_t>;
        using index_type   = meta::remove_cvref_t<decltype(meta::declval<ndindex_type>()[0])>;

        array_type array;
        shape_type shape;
        ndindex_type ndindex_;

        constexpr ndenumerate_t(array_type array)
            : array(array)
            , shape([&](){
                // TODO: use init_attribute_type
                auto shape_ = ::nmtools::shape(array);
                if constexpr (meta::is_constant_index_array_v<decltype(shape_)>) {
                    return meta::to_value_v<decltype(shape_)>;
                } else {
                    return shape_;
                }
            }())
            , ndindex_(shape)
        {}

        constexpr decltype(auto) size() const noexcept
        {
            return ndindex_.size();
        } // size

        constexpr inline auto operator[](size_t i) const
            -> meta::make_tuple_type_t<index_type,const element_type&>
        {
            auto idx = ndindex_[i];
            const auto& val = apply_at(array,idx);
            return {idx,val};
        } // operator[]

        /**
         * @brief A proxy object to track iteration on on ndenumerate.
         *
         * Allows ndenumerate to be used in range-based for loop.
         * 
         */
        struct ref_t
        {
            const ndenumerate_t& array;
            using size_type = typename ndindex_type::size_type;
            size_type i = 0;

            constexpr decltype(auto) operator*() const { return array[i]; }
            constexpr bool operator==(const ref_t& rhs) const { return i == rhs.i; }
            constexpr bool operator!=(const ref_t& rhs) const { return !operator==(rhs); }
            constexpr auto operator++() { i++; }
        }; 
    }; // ndenumerate_t

    /**
     * @brief Allows ndenumerate to be used with range for.
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto begin(const ndenumerate_t<array_t>& array)
    {
        using ref_t = typename ndenumerate_t<array_t>::ref_t;
        return ref_t{array,0};
    }

    template <typename array_t>
    constexpr auto end(const ndenumerate_t<array_t>& array)
    {
        using ref_t = typename ndenumerate_t<array_t>::ref_t;
        return ref_t{array,array.size()};
    }

    /**
     * @brief Create multidimensional array iterator.
     *
     * Returning indices (or coordinate) and the elements of array.
     * 
     * @tparam array_t 
     * @param array array to be iterated
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto ndenumerate(const array_t& array)
    {
        using type = ndenumerate_t<array_t>;
        return type(array);
    } // ndenumerate
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_NDENUMERATE_HPP