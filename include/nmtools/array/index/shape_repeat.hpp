#ifndef NMTOOLS_ARRAY_INDEX_SHAPE_REPEAT_HPP
#define NMTOOLS_ARRAY_INDEX_SHAPE_REPEAT_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/sum.hpp"

#include <array>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve repeat return type
     * 
     */
    struct shape_repeat_t {};

    /**
     * @brief 
     * 
     * @tparam shape_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     * @param shape 
     * @param repeats 
     * @param axis 
     * @return constexpr auto 
     */
    template <typename shape_t, typename repeats_t, typename axis_t>
    constexpr auto shape_repeat(const shape_t shape, const repeats_t& repeats, axis_t axis)
    {
        using return_t = meta::resolve_optype_t<shape_repeat_t,shape_t,repeats_t,axis_t>;
        static_assert (!std::is_void_v<return_t>
            , "unsupported shape_repeat, maybe specialization of resolve_optype_t<shape_repeat_t,...> required"
        );
        auto ret = return_t {};

        if constexpr (is_none_v<axis_t>) {
            auto p = product(shape);
            at(ret,0) = p * repeats;
        }
        else {
            auto n = tuple_size(shape);

            if constexpr (meta::is_resizeable_v<return_t>)
                ret.resize(n);
            
            for (size_t i=0; i<n; i++)
                at(ret,i) = tuple_at(shape,i);

            if constexpr (meta::is_array1d_v<repeats_t>) {
                assert ( at(ret,axis) == vector_size(repeats)
                    // , "unsupported shape_repeat"
                    // numpy: ValueError: operands could not be broadcast together with shape
                );
                at(ret,axis) = sum(repeats);
            }
            else
                at(ret,axis) = at(ret,axis) * repeats;
        }

        return ret;
    } // repeat
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type for index::shape_repeat op
     * 
     * @tparam shape_t 
     * @tparam repeats_t 
     * @tparam axis_t 
     */
    template <typename shape_t, typename repeats_t, typename axis_t>
    struct resolve_optype <
        void, index::shape_repeat_t, shape_t, repeats_t, axis_t
    >
    {
        using type = tuple_to_array_t<shape_t>;
    }; // resolve_optype

    /**
     * @brief resolve return type for index::shape_repeat op
     * 
     * @tparam shape_t 
     * @tparam repeats_t 
     */
    template <typename shape_t, typename repeats_t>
    struct resolve_optype <
        void, index::shape_repeat_t, shape_t, repeats_t, none_t
    >
    {
        using type = std::array<size_t,1>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SHAPE_REPEAT_HPP