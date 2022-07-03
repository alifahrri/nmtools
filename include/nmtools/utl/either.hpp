#ifndef NMTOOLS_UTL_EITHER_HPP
#define NMTOOLS_UTL_EITHER_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_trivially_destructible.hpp"
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
    template <typename Derived>
    struct base_either
    {
    public:

        // in-place not supported (yet?)

        Derived& self()
        {
            return static_cast<Derived&>(*this);
        }

        const Derived& self() const
        {
            return static_cast<const Derived&>(*this);
        }

        template <typename T>
        constexpr Derived& operator=(const T& val) noexcept
        {
            using left_type  = typename Derived::left_type;
            using right_type = typename Derived::right_type;
            static_assert( meta::is_same_v<T,left_type> || meta::is_same_v<T,right_type>
                , "unsupported type for either assignment"
            );
            if constexpr (meta::is_same_v<T,left_type>) {
                self().left = val;
                self().tag  = Derived::LEFT;
                return self();
            } else {
                self().right = val;
                self().tag  = Derived::RIGHT;
                return self();
            }
        }

        constexpr auto index() const noexcept
        {
            if (self().tag==Derived::LEFT) {
                return 0;
            } else /* if (tag==RIGHT) */ {
                return 1;
            }
        }

        template <typename T>
        constexpr auto* get_if() const noexcept
        {
            using left_type  = typename Derived::left_type;
            using right_type = typename Derived::right_type;
            if constexpr (meta::is_same_v<T,left_type>) {
                using type = const left_type*;
                if (self().tag==Derived::LEFT) {
                    return type{&self().left};
                } else {
                    return type{nullptr};
                }
            } else if constexpr (meta::is_same_v<T,right_type>) {
                using type = const right_type*;
                if (self().tag==Derived::RIGHT) {
                    return type{&self().right};
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
            using left_type  = typename Derived::left_type;
            using right_type = typename Derived::right_type;
            if constexpr (meta::is_same_v<T,left_type>) {
                using type = left_type*;
                if (self().tag==Derived::LEFT) {
                    return type{&self().left};
                } else {
                    return type{nullptr};
                }
            } else if constexpr (meta::is_same_v<T,right_type>) {
                using type = right_type*;
                if (self().tag==Derived::RIGHT) {
                    return type{&self().right};
                } else {
                    return type{nullptr};
                }
            } else {
                // TODO: error type
            }
        }
    }; // either

    template <typename left_t, typename right_t, typename=void>
    struct either : base_either<either<left_t,right_t>>
    {
    protected:
        using base = base_either<either>;
        enum Tag {LEFT, RIGHT};
        // assume default constructible
        union
        {
            left_t  left;
            right_t right;
        };
        Tag tag;
        template <typename,typename>
        friend struct impl::get_if_t;
        friend base;
    public:
        using left_type  = left_t;
        using right_type = right_t;

        static_assert( !meta::is_same_v<left_type,right_type>
            , "left_type and right_type can't be the same"
        );

        constexpr either() noexcept
            : left{}, tag{LEFT} {}

        constexpr explicit either(const left_t& val) noexcept
            : left(val), tag{LEFT} {}
        constexpr explicit either(const right_t& val) noexcept
            : right(val), tag{RIGHT} {}

        ~either() = default;

        template <typename U>
        constexpr either& operator=(const U& val) noexcept
        {
            base::operator=(val);
            return *this;
        }
    };

    #if 1
    template <typename left_t, typename right_t>
    struct either<left_t,right_t,
        meta::enable_if_t<!meta::is_trivially_destructible_v<left_t> || !meta::is_trivially_destructible_v<right_t>>
    > : base_either<either<left_t,right_t>>
    {
    protected:
        using base = base_either<either>;
        enum Tag {LEFT, RIGHT};
        // assume default constructible
        union
        {
            left_t  left;
            right_t right;
        };
        Tag tag;
        template <typename,typename>
        friend struct impl::get_if_t;
        friend base;
    public:

        constexpr either() noexcept
            : left{}, tag{LEFT} {}

        constexpr explicit either(const left_t& val) noexcept
            : left(val), tag{LEFT} {}
        constexpr explicit either(const right_t& val) noexcept
            : right(val), tag{RIGHT} {}

        ~either()
        {
            if (tag == LEFT) {
                left.~left_t();
            } else {
                right.~right_t();
            }
        }

        template <typename U>
        constexpr either& operator=(const U& val) noexcept
        {
            base::operator=(val);
            return *this;
        }
    }; // either
    #endif
} // namespace nmtools::utl

#endif // NMTOOLS_UTL_EITHER_HPP