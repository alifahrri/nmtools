#ifndef NMTOOLS_META_BITS_TRANSFORM_REPLACE_EITHER_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REPLACE_EITHER_HPP

#include "nmtools/meta/common.hpp"
namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct REPLACE_EITHER_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Replace existing Left and Right from given either type
     * with new Left and Right.
     * 
     * @tparam either_t 
     * @tparam Left 
     * @tparam Right 
     * @todo move to transform
     */
    template <typename either_t, typename Left, typename Right>
    struct replace_either
    {
        using type = error::REPLACE_EITHER_UNSUPPORTED<either_t,Left,Right>;
    };

    template <typename either_t, typename Left, typename Right>
    using replace_either_t = typename replace_either<either_t,Left,Right>::type;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_REPLACE_EITHER_HPP