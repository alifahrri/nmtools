#ifndef NMTOOLS_ARRAY_INDEX_PRODUCT_HPP
#define NMTOOLS_ARRAY_INDEX_PRODUCT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/at.hpp"

namespace nmtools::index
{
    struct product_t {};

    // TODO: cleanup index functions
    /**
     * @brief compute product of 1D array
     *
     * Useful to compute number of elements.
     * 
     * @tparam shape_t 
     * @param shape 
     * @return constexpr auto 
     */
    template <typename shape_t>
    constexpr auto product(const shape_t& shape)
    {
        using result_t = resolve_optype_t<product_t, shape_t>;
        auto ret = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_v<result_t>
        ) {
            ret = result_t{1};
            if constexpr (is_fixed_index_array_v<shape_t>) {
                constexpr auto n = len_v<shape_t>;
                template_for<n>([&](auto i){
                    result_t p = ret * at(shape,i);
                    ret = p;
                });
            } else {
                for (nm_size_t i=0; i<(nm_size_t)len(shape); i++) {
                    result_t p = ret * at(shape,i);
                    ret = p;
                }
            }
        }

        return ret;
    } // product
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_PRODUCT_UNSUPPORTED : detail::fail_t {};
    }
    template <typename shape_t>
    struct resolve_optype<
        void, index::product_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>) {
                using type = error::INDEX_PRODUCT_UNSUPPORTED<shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<shape_t>) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto N = index::product(shape);
                return as_value_v<ct<N>>;
            } else if constexpr (is_clipped_index_array_v<shape_t>) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto N = index::product(shape);
                return as_value_v<clipped_size_t<N>>;
            } else {
                using type = conditional_t<
                    is_nullable_index_array_v<shape_t>
                    , null_size_t
                    , get_index_element_type_t<shape_t>
                >;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_PRODUCT_HPP