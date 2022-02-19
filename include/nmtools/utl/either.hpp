#ifndef NMTOOLS_UTL_EITHER_HPP
#define NMTOOLS_UTL_EITHER_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/utility/get_if.hpp"

// poor man's either type

namespace nmtools::utl
{
    /**
     * @brief Poor man's Either type (variant with exactly 2 args).
     * 
     * This structure doesn't aim to be fully STL-compatible,
     * only subset of that is used in nmtools.
     * 
     * @tparam left_t 
     * @tparam right_t 
     */
    template <typename left_t, typename right_t>
    struct either
    {
        enum Tag {LEFT, RIGHT};
    protected:
        // assume default constructible
        union
        {
            left_t  left;
            right_t right;
        };
        Tag tag;
        template <typename,typename>
        friend struct impl::get_if_t;
    public:
        using left_type  = left_t;
        using right_type = right_t;

        static_assert( !meta::is_same_v<left_type,right_type>
            , "left_type and right_type can't be the same"
        );

        // assume left is default constructible,
        // following std variant, default-constructed use first type (left)
        constexpr either() noexcept
            : left{}, tag{LEFT} {}

        constexpr explicit either(const left_t& val) noexcept
            : left(val), tag{LEFT} {}
        constexpr explicit either(const right_t& val) noexcept
            : right(val), tag{RIGHT} {}

        // in-place not supported (yet?)

        constexpr either& operator=(const left_t& val) noexcept
        {
            left = val;
            tag  = LEFT;
            return *this;
        }

        constexpr either& operator=(const right_t& val) noexcept
        {
            right = val;
            tag   = RIGHT;
            return *this;
        }

        constexpr auto index() const noexcept
        {
            if (tag==LEFT) {
                return 0;
            } else /* if (tag==RIGHT) */ {
                return 1;
            }
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            if constexpr (meta::is_same_v<T,left_type>) {
                using type = const left_type*;
                if (tag==LEFT) {
                    return type{&left};
                } else {
                    return type{nullptr};
                }
            } else if constexpr (meta::is_same_v<T,right_type>) {
                using type = const right_type*;
                if (tag==RIGHT) {
                    return type{&right};
                } else {
                    return type{nullptr};
                }
            } else {
                // TODO: error type
            }
        }

        template <typename T>
        constexpr auto* get_if() noexcept
        {
            if constexpr (meta::is_same_v<T,left_type>) {
                using type = left_type*;
                if (tag==LEFT) {
                    return type{&left};
                } else {
                    return type{nullptr};
                }
            } else if constexpr (meta::is_same_v<T,right_type>) {
                using type = right_type*;
                if (tag==RIGHT) {
                    return type{&right};
                } else {
                    return type{nullptr};
                }
            } else {
                // TODO: error type
            }
        }
    };
} // namespace nmtools::utl

#endif // NMTOOLS_UTL_EITHER_HPP