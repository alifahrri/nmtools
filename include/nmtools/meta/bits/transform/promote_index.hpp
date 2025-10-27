#ifndef NMTOOLS_META_BITS_TRANSFORM_PROMOTE_INDEX_HPP
#define NMTOOLS_META_BITS_TRANSFORM_PROMOTE_INDEX_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/loop.hpp"
#include "nmtools/meta/bits/traits/is_clipped_integer.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/traits/is_signed.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"
#include "nmtools/meta/bits/traits/is_nullable_index.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/meta/bits/transform/at.hpp"
#include "nmtools/meta/bits/transform/type_list_at.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct PROMOTE_INDEX_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Metafunction to deduce common type for index operation
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename first_t, typename...rest_t>
    struct promote_index
    {
        template <typename left_t, typename right_t>
        static constexpr auto non_constant(as_value<left_t>, as_value<right_t>) {
            if constexpr (!is_constant_index_v<left_t>) {
                return as_value_v<left_t>;
            } else /* if constexpr (!is_constant_index_v<right_t>) */{
                return as_value_v<right_t>;
            }
        }
    
        template <typename T>
        static constexpr auto make_non_constant(as_value<T>) {
            if constexpr (is_constant_index_v<T> || is_clipped_integer_v<T> || is_nullable_index_v<T>) {
                return as_value_v<typename T::value_type>;
            } else {
                return as_value_v<T>;
            }
        }

        template <typename left_t, typename right_t>
        static constexpr auto cast(as_value<left_t>, as_value<right_t>) {
            // TODO: consider to select largest byte
            if constexpr (is_signed_v<left_t>) {
                return as_value_v<left_t>;
            } else /* if (is_signed_v<right_t>) */ {
                return as_value_v<right_t>;
            }
        }

        template <typename lhs_t, typename rhs_t>
        static constexpr auto binary_vtype(as_value<lhs_t>, as_value<rhs_t>) {
            if constexpr (is_constant_index_v<lhs_t> && is_constant_index_v<rhs_t>) {
                using left_t  = typename lhs_t::value_type;
                using right_t = typename rhs_t::value_type;
                return cast(as_value_v<left_t>, as_value_v<right_t>);
            } else if constexpr (is_index_v<lhs_t> && is_index_v<rhs_t>) {
                // simply select signed and non constant if possible
                auto signed_   = cast(make_non_constant(as_value_v<lhs_t>), make_non_constant(as_value_v<rhs_t>));
                auto non_const = make_non_constant(signed_);
                return non_const;
            } else {
                return as_value_v<error::PROMOTE_INDEX_UNSUPPORTED<lhs_t,rhs_t>>;
            }
        }

        static constexpr auto vtype = [](){
            using types = type_list<rest_t...>;
            constexpr auto init_ = as_value_v<remove_cvref_t<first_t>>;
            return template_reduce<sizeof...(rest_t)>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using type_i = remove_cvref_t<at_t<types,i>>;
                return binary_vtype(init,as_value_v<type_i>);
            }, init_);
        }();
        using type = type_t<decltype(vtype)>;
    }; // promote_index

    template <typename...rest_t>
    using promote_index_t = type_t<promote_index<rest_t...>>;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_PROMOTE_INDEX_HPP