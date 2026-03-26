#ifndef NMTOOLS_META_BITS_TRANSFORM_RESIZE_FIXED_VECTOR_HPP
#define NMTOOLS_META_BITS_TRANSFORM_RESIZE_FIXED_VECTOR_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_void.hpp"
#include "nmtools/meta/bits/transform/replace_element_type.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct RESIZE_FIXED_VECTOR_UNSUPPORTED : detail::fail_t {};
    }

    template <typename T, auto N, typename=void>
    struct resize_fixed_vector
    {
        // TODO: use error type
        /* pack new size as type instead of non-type template param */
        using new_size = integral_constant<size_t,N>;
        static constexpr auto vtype = [](){
            using type = replace_template_parameter_t<T,new_size>;
            if constexpr (is_void_v<type>) {
                return as_value_v<error::RESIZE_FIXED_VECTOR_UNSUPPORTED<T,as_type<N>>>;
            } else {
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    /**
     * @brief helper alias template to resize metafunction to resize fixed vector.
     * 
     * @tparam T fixed vector type to be resized.
     * @tparam N new size.
     */
    template <typename T, auto N>
    using resize_fixed_vector_t = typename resize_fixed_vector<T,N>::type;

    template <typename T, size_t N>
    struct resize_fixed_index_array : resize_fixed_vector<T,N> {};

    template <typename T, size_t N>
    using resize_fixed_index_array_t = type_t<resize_fixed_index_array<T,N>>;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_RESIZE_FIXED_VECTOR_HPP