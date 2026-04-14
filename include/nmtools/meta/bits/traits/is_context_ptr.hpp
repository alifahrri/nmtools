#ifndef NMTOOLS_META_BITS_TRAITS_IS_CONTEXT_PTR_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_CONTEXT_PTR_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_pointer.hpp"
#include "nmtools/meta/bits/traits/is_shared_ptr.hpp"
#include "nmtools/meta/bits/traits/is_context.hpp"

namespace nmtools::meta
{
    template<typename T>
    struct is_context_ptr
    {
        static constexpr auto value = [](){
            if constexpr (is_pointer_v<T> || is_shared_ptr_v<T>) {
                return is_context_v<decltype(*meta::declval<T>())>;
            } else {
                return false;
            }
        }();
    }; // is_context_ptr

    template <typename T>
    struct is_context_ptr<const T> : is_context_ptr<T> {};

    template <typename T>
    struct is_context_ptr<T&> : is_context_ptr<T> {};

    template <typename T>
    constexpr inline auto is_context_ptr_v = is_context_ptr<T>::value;
}

namespace nmtools
{
    using meta::is_context_ptr_v;
}

#endif // NMTOOLS_META_BITS_TRAITS_IS_CONTEXT_PTR_HPP