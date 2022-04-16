#ifndef NMTOOLS_ARRAY_FUNCTIONAL_COMPRESS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_COMPRESS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/compress.hpp"

namespace nmtools::functional
{
    struct compress_fmap_t
    {
        static constexpr auto arity = 1;

        template <
            template<typename...>typename attr_tuple, typename condition_t, typename axis_t,
            template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(const attr_tuple<condition_t,axis_t>& attributes, const operand_tuple<array_t>& operands) const
        {
            const auto& [condition, axis] = attributes;
            if constexpr (meta::is_pointer_v<array_t>) {
                return view::compress(condition,*nmtools::get<0>(operands),axis);
            } else {
                return view::compress(condition,nmtools::get<0>(operands),axis);
            }
        } // operator()
    }; // compress_fmap_t

    constexpr inline auto compress = functor_t(compress_fmap_t{});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_COMPRESS_HPP