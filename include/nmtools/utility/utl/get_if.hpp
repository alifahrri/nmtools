#ifndef NMTOOLS_UTILITY_UTL_GET_IF_HPP
#define NMTOOLS_UTILITY_UTL_GET_IF_HPP

#include "nmtools/utility/get_if.hpp"

#include "nmtools/utl/either.hpp"

namespace nmtools::impl
{
    template <typename left_t, typename right_t>
    struct get_if_t<utl::either<left_t,right_t>>
    {
        using either_t = utl::either<left_t,right_t>;

        template <typename T>
        constexpr auto* operator()(const either_t* either) const noexcept
        {
            // return (*either).template get_if<U>();

            using Tag = typename either_t::Tag;
            if constexpr (meta::is_same_v<T,left_t>) {
                using type = const left_t*;
                if (either->tag==Tag::LEFT) {
                    return type{&(either->left)};
                } else {
                    return type{nullptr};
                }
            } else if constexpr (meta::is_same_v<T,right_t>) {
                using type = const right_t*;
                if (either->tag==Tag::RIGHT) {
                    return type{&(either->right)};
                } else {
                    return type{nullptr};
                }
            } else {
                // TODO: error type
            }
        }
    };
} // namespace nmtools::impl


#endif // NMTOOLS_UTILITY_UTL_GET_IF_HPP