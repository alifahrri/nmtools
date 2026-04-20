#ifndef NMTOOLS_ARRAY_INDEX_CAST_HPP
#define NMTOOLS_ARRAY_INDEX_CAST_HPP

#include "nmtools/meta.hpp"
#include "nmtools/stl.hpp"

namespace nmtools::index
{
    struct cast_t {};

    template <typename dst_type_t, typename array_t>
    constexpr auto cast(const array_t& array, dtype_t<dst_type_t> = dtype_t<dst_type_t>{})
    {
        using result_t = resolve_optype_t<cast_t,dst_type_t,array_t>;

        auto result = result_t {};

        [[maybe_unused]] auto dim = len(array);
        if constexpr (is_resizable_v<result_t>) {
            result.resize(dim);
        }

        constexpr auto N = len_v<array_t>;

        if constexpr (is_num_v<result_t>) {
            result = array;
        } else if constexpr (!is_fail_v<decltype(N)>) {
            template_for<N>([&](auto i){
                at(result,i) = at(array,i);
            });
        } else {
            for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                at(result,i) = at(array,i);
            }
        }

        return result;
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_CAST_UNSUPPORTED : detail::fail_t {};
    }

    template <typename dst_type_t, typename array_t>
    struct resolve_optype<
        void, index::cast_t, dst_type_t, array_t
    >
    {
        static constexpr auto vtype = [](){
            constexpr auto N = len_v<array_t>;
            [[maybe_unused]]
            constexpr auto B_SIZE = bounded_size_v<array_t>;
            // TODO: try to resize instead, to keep the class/struct of original array
            // TODO: keep compile-time index array
            if constexpr (N > 0) {
                using type = nmtools_array<dst_type_t,N>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_SIZE)>) {
                using type = nmtools_static_vector<dst_type_t,B_SIZE>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<array_t>) {
                // TODO: add nmtools_small_vector instead
                using type = nmtools_list<dst_type_t>;
                return as_value_v<type>;
            } else if constexpr (is_num_v<array_t>) {
                using type = dst_type_t;
                return as_value_v<type>;
            } else {
                using type = error::INDEX_CAST_UNSUPPORTED<dst_type_t,array_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_CAST_HPP