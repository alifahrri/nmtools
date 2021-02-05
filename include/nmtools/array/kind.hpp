#ifndef NMTOOLS_ARRAY_KIND_HPP
#define NMTOOLS_ARRAY_KIND_HPP

namespace nmtools::array::kind
{
    /**
     * @brief helper tag for easy dispatch
     * 
     */
    struct fixed_t {};
    struct hybrid_t {};
    struct dynamic_t {};

    /**
     * @brief helper inline variable for each tag
     * 
     */
    inline constexpr auto fixed   = fixed_t {};
    inline constexpr auto hybrid  = hybrid_t {};
    inline constexpr auto dynamic = dynamic_t {};
} // namespace nmtools::array::kind

#endif // NMTOOLS_ARRAY_KIND_HPP