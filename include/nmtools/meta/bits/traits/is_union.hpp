#ifndef NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP

namespace nmtools::meta
{
    // is_union requires compiler-specific intrinsic :|
    // reserved metafunctions
    template <typename>
    struct is_union;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_UNION_HPP