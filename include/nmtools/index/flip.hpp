#ifndef NMTOOLS_ARRAY_INDEX_FLIP_HPP
#define NMTOOLS_ARRAY_INDEX_FLIP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/index/count.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility.hpp"

namespace nmtools::index
{
    struct flip_slices_t {};

    template <typename dim_t, typename axes_t>
    constexpr auto flip_slices(const dim_t& dim, const axes_t& axes)
    {
        // TODO: support constant index array
        using result_t = meta::resolve_optype_t<flip_slices_t,dim_t,axes_t>;

        auto result = result_t {};

        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(dim);
        }

        for (size_t i=0; i<(size_t)dim; i++) {
            if constexpr (meta::is_index_array_v<axes_t>) {
                auto in_axis = static_cast<bool>(
                    index::count([&](const auto ii){
                        using common_t = meta::promote_index_t<decltype(ii),size_t>;
                        return (common_t)ii == (common_t)i;
                    }, axes)
                );
                nmtools::get<2>(at(result,i)) = in_axis ? -1 : 1;
            } else if constexpr (meta::is_index_v<axes_t>) {
                nmtools::get<2>(at(result,i)) = ((size_t)axes == i) ? -1 : 1;
            } else if constexpr (is_none_v<axes_t>) {
                nmtools::get<2>(at(result,i)) = -1;
            }
        }

        return result;
    } // get_flip_slices
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FLIP_SLICES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename dim_t, typename axes_t>
    struct resolve_optype<
        void, index::flip_slices_t, dim_t, axes_t
    >
    {
        static constexpr auto vtype = [](){
            using slice_t [[maybe_unused]] = nmtools_tuple<none_t,none_t,int>;
            if constexpr (
                !is_index_v<dim_t>
                || !(is_index_array_v<axes_t> || is_index_v<axes_t> || is_none_v<axes_t>)
            ) {
                using type = error::FLIP_SLICES_UNSUPPORTED<dim_t,axes_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<dim_t>
            ) {
                using type = nmtools_array<slice_t,dim_t::value>;
                return as_value_v<type>;
            } else if constexpr (
                is_clipped_integer_v<dim_t>
            ) {
                using type = nmtools_static_vector<slice_t,dim_t::max_value>;
                return as_value_v<type>;
            } else {
                // TODO: use small_vector
                using type = nmtools_list<slice_t>;
                return as_value_v<type>; 
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_FLIP_HPP