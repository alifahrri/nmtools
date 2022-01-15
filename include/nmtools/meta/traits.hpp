#ifndef NMTOOLS_META_TRAITS_HPP
#define NMTOOLS_META_TRAITS_HPP

#include "nmtools/meta/bits/traits/has_at.hpp"
#include "nmtools/meta/bits/traits/has_bracket.hpp"
#include "nmtools/meta/bits/traits/has_dim.hpp"
#include "nmtools/meta/bits/traits/has_shape.hpp"
#include "nmtools/meta/bits/traits/has_size_type.hpp"
#include "nmtools/meta/bits/traits/has_size.hpp"
#include "nmtools/meta/bits/traits/has_square_bracket.hpp"
#include "nmtools/meta/bits/traits/has_template_get.hpp"
#include "nmtools/meta/bits/traits/has_tuple_size.hpp"
#include "nmtools/meta/bits/traits/has_type.hpp"
#include "nmtools/meta/bits/traits/has_value_type.hpp"
#include "nmtools/meta/bits/traits/is_bit_reference.hpp"
#include "nmtools/meta/bits/traits/is_boolean.hpp"
#include "nmtools/meta/bits/traits/is_bounded_array.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/traits/is_constant_index_array.hpp"
#include "nmtools/meta/bits/traits/is_dynamic_index_array.hpp"
#include "nmtools/meta/bits/traits/is_dynamic_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_either.hpp"
#include "nmtools/meta/bits/traits/is_fail.hpp"
#include "nmtools/meta/bits/traits/is_fixed_dim_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_fixed_index_array.hpp"
#include "nmtools/meta/bits/traits/is_fixed_size_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_hybrid_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_hybrid_index_array.hpp"
#include "nmtools/meta/bits/traits/is_index.hpp"
#include "nmtools/meta/bits/traits/is_index_array.hpp"
#include "nmtools/meta/bits/traits/is_integer.hpp"
#include "nmtools/meta/bits/traits/is_integral_constant.hpp"
#include "nmtools/meta/bits/traits/is_maybe.hpp"
#include "nmtools/meta/bits/traits/is_ndarray.hpp"
#include "nmtools/meta/bits/traits/is_nothing.hpp"
#include "nmtools/meta/bits/traits/is_num.hpp"
#include "nmtools/meta/bits/traits/is_pointer.hpp"
#include "nmtools/meta/bits/traits/is_resizeable.hpp"
#include "nmtools/meta/bits/traits/is_signed.hpp"
#include "nmtools/meta/bits/traits/is_specialization.hpp"
#include "nmtools/meta/bits/traits/is_unsigned.hpp"
#include "nmtools/meta/bits/traits/is_tuple.hpp"
#include "nmtools/meta/bits/traits/is_void.hpp"

#include "nmtools/meta/expr.hpp"
#include "nmtools/meta/common.hpp"

namespace nmtools::meta {

    /** @defgroup traits
    * Collections of type traits used accross the library
    * @{ 
    */


    // TODO: cleanup metafunctions
    /**
     * @brief check if F(Args...) is well-formed
     * 
     * @tparam F function
     * @tparam Args arguments
     */
    template <typename F, typename...Args>
    struct is_callable {
    private:
        template <typename FN>
        constexpr static auto test(int) -> decltype(declval<FN>()(declval<Args>()...), bool()) {
            return true;
        }
        template <typename>
        constexpr static auto test(...) -> decltype(bool()) {
            return false;
        }
    public:
        constexpr static bool value = test<F>(int{});
    };

    /**
     * @brief helper variable template for is_callable
     * 
     * @tparam F function
     * @tparam Args arguments
     */
    template <typename F, typename...Args>
    inline constexpr bool is_callable_v = is_callable<F,Args...>::value;

    /** @} */ // end group traits

} // namespace nmtools::meta
#endif // NMTOOLS_META_TRAITS_HPP