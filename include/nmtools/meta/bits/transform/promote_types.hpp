#ifndef NMTOOLS_META_BITS_TRANSFORM_PROMOTE_TYPES_HPP
#define NMTOOLS_META_BITS_TRANSFORM_PROMOTE_TYPES_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        // default type (error-type) for promote_types metafunction
        struct PROMOTE_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief Metafunction to promote / deduce the resulting type from two arrays.
     * 
     * @tparam tag_t can be specialize if desired.
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @tparam typename 
     */
    template <typename tag_t, typename lhs_t, typename rhs_t, typename=void>
    struct promote_types
    {
        using type = error::PROMOTE_TYPE_UNSUPPORTED;
    }; // promote_types

    template <typename tag_t, typename lhs_t, typename rhs_t>
    using promote_types_t = type_t<promote_types<tag_t,lhs_t,rhs_t>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_PROMOTE_TYPES_HPP