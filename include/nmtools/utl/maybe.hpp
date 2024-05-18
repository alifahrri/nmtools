#ifndef NMTOOLS_UTL_MAYBE_HPP
#define NMTOOLS_UTL_MAYBE_HPP

#include "nmtools/utl/either.hpp"
#include "nmtools/meta/bits/traits/is_trivially_destructible.hpp"
#include "nmtools/meta/bits/traits/is_trivially_constructible.hpp"
#include "nmtools/meta/bits/traits/is_copy_constructible.hpp"
#include "nmtools/meta/bits/traits/is_copy_assignable.hpp"

namespace nmtools::utl
{
    struct nothing_t {};

    inline constexpr auto nothing = nothing_t {};

    
    /**
     * @brief Poor man's optional (Maybe type).
     * 
     * This structure doesn't aim to be fully STL-compatible,
     * only subset of that is used in nmtools.
     * 
     * @tparam T 
     */
    template <typename T, typename=void>
    struct maybe : either<T,nothing_t>
    {
    public:
        using base = either<T,nothing_t>;
        using value_type = T;
        using pointer    = T*;
        using reference  = T&;
        using const_pointer   = const T*;
        using const_reference = const T&;

        constexpr maybe() : base(nothing) {}

        constexpr maybe(nothing_t) : base(nothing) {}

        // assume copy-constructible
        constexpr maybe(const T& t) : base(t) {}

        constexpr maybe(const maybe& other) : base(other) {}

        constexpr bool has_value() const noexcept
        {
            return this->tag == base::LEFT;
        }

        template <typename U>
        /*constexpr*/ maybe& operator=(const U& val)
        {
            // NOTE: using current approach (using either which use union), assignment cant be constexpr
            // since union can't be changed for constexpr call.
            // other approach for example using placement-new doesn't interact well with constexpr
            // 
            base::operator=(val);
            return *this;
        }

        /*constexpr*/ maybe& operator=(const maybe& other)
        {
            if (other.has_value()) {
                this->left = other.left;
                this->tag  = base::LEFT;
            } else {
                this->right = other.right;
                this->tag  = base::RIGHT;
            }
            return *this;
        }

        constexpr explicit operator bool() const noexcept
        {
            return has_value();
        }

        constexpr const_reference value() const noexcept
        {
            return this->left;
        }

        constexpr reference value() noexcept
        {
            return this->left;
        }

        constexpr const_reference operator*() const noexcept
        {
            return value();
        }

        constexpr reference operator*() noexcept
        {
            return value();
        }
    };

    template <typename T>
    struct maybe<T,meta::enable_if_t<
        (!meta::is_trivially_destructible_v<T>
            || !meta::is_trivially_constructible_v<T>)
        >>
    : either<T,nothing_t>
    {
    public:
        using base = either<T,nothing_t>;
        using value_type = T;
        using pointer    = T*;
        using reference  = T&;
        using const_pointer   = const T*;
        using const_reference = const T&;

        constexpr maybe() : base(nothing) {}

        constexpr maybe(nothing_t) : base(nothing) {}

        constexpr maybe(const T& t) : base(t) {}

        constexpr maybe(const maybe& other)
            : base(nothing)
        {
            if (other.has_value()) {
                this->tag = base::LEFT;
                new(&this->left) T(other.left);
                #if 0
                if constexpr (meta::is_copy_assignable_v<T>) {
                    this->left = other.left;
                } else {
                    new(&this->left) T(other.left);
                }
                #endif
            } else {
                this->tag = base::RIGHT;
                this->right = nothing;
            }
        }

        constexpr bool has_value() const noexcept
        {
            return this->tag == base::LEFT;
        }

        template <typename U>
        /*constexpr*/ maybe& operator=(const U& val)
        {
            // NOTE: using current approach (using either which use union), assignment cant be constexpr
            // since union can't be changed for constexpr call.
            // other approach for example using placement-new doesn't interact well with constexpr
            // 
            base::operator=(val);
            return *this;
        }

        /*constexpr*/ maybe& operator=(const maybe& other)
        {
            if (other.has_value()) {
                if constexpr (meta::is_copy_assignable_v<T>) {
                    this->left = other.left;
                } else {
                    new(&this->left) T(other.left);
                }
                this->tag  = base::LEFT;
            } else {
                this->right = other.right;
                this->tag  = base::RIGHT;
            }
            return *this;
        }

        constexpr explicit operator bool() const noexcept
        {
            return has_value();
        }

        constexpr const_reference value() const noexcept
        {
            return this->left;
        }

        constexpr reference value() noexcept
        {
            return this->left;
        }

        constexpr const_reference operator*() const noexcept
        {
            return value();
        }

        constexpr reference operator*() noexcept
        {
            return value();
        }
    };

} // namespace nmtools::utl

#endif // NMTOOLS_UTL_MAYBE_HPP