#ifndef NMTOOLS_ARRAY_INDEX_NONZERO_HPP
#define NMTOOLS_ARRAY_INDEX_NONZERO_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"

#include <tuple>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type
     * 
     */
    struct nonzero_t {};

    // TODO: remove
    template <typename T, typename=void>
    struct make_resizeable
    {
        static constexpr auto vtype = [](){
            if constexpr (meta::is_fixed_size_ndarray_v<T>) {
                constexpr auto shape = meta::fixed_ndarray_shape_v<T>;
                constexpr auto N = index::product(shape);
                using element_t = meta::get_element_type_t<T>;
                using type = array::hybrid_ndarray<element_t,N,1>;
                return meta::as_value_v<type>;
            } else {
                return meta::as_value_v<T>;
            }
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // make_resizeable

    // TODO: cleanup index functions, handling constant index array
    /**
     * @brief return indices of array a which are nonzero
     * 
     * @tparam array_t 
     * @param a 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto nonzero(const array_t& a)
    {
        using return_t = meta::resolve_optype_t<nonzero_t,array_t>;
        
        auto ret = return_t{};

        ret.resize(len(a));
        
        auto n = size_t{0}; // number of nonzero elements
        auto i = size_t{0};

        auto nonzero_impl = [&](auto idx){
            if (static_cast<bool>(at(a,idx))) {
                at(ret,i) = idx;
                n++; i++;
            }
        }; // nonzero_impl
        
        if constexpr (meta::has_tuple_size_v<array_t>)
            meta::template_for<std::tuple_size_v<array_t>>([&](auto idx){
                nonzero_impl(idx);
            });
        else
            for (size_t idx=0; idx<len(a); idx++)
                nonzero_impl(idx);
        
        ret.resize(n);
        return ret;
    } // nonzero
} // namespace nmtools::index

namespace nmtools::meta
{
    // TODO: cleanup index metafunctions
    /**
     * @brief resolve return type for index::nonzero op
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct resolve_optype<
        void, index::nonzero_t, array_t
    >
    {
        using array_type    = tuple_to_array_t<transform_bounded_array_t<array_t>>;
        using replaced_type = replace_element_type_t<array_type,size_t>;
        using type = type_t<index::make_resizeable<replaced_type>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_NONZERO_HPP