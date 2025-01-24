#ifndef NMTOOLS_ARRAY_INDEX_FREE_AXES_HPP
#define NMTOOLS_ARRAY_INDEX_FREE_AXES_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/stl.hpp"

namespace nmtools::index
{
    struct free_axes_t {};

    // TODO: cleanup index functions
    /**
     * @brief given ashape determine which axes' are free with respect to bshape.
     *
     * ashape should be output from shape broadcasting while bshape is the original
     * shape of interest.
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t>
    constexpr auto free_axes(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<free_axes_t,ashape_t,bshape_t>;

        if constexpr (meta::is_maybe_v<ashape_t>) {
            if (static_cast<bool>(ashape)) {
                auto result = free_axes(*ashape,bshape);
                if constexpr (meta::is_maybe_v<decltype(result)>) {
                    return (result
                        ? return_t{*result}
                        : return_t{meta::Nothing}
                    );
                } else {
                    return return_t{result};
                }
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<bshape_t>) {
            if (static_cast<bool>(bshape)) {
                auto result = free_axes(ashape,*bshape);
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_constant_index_array_v<return_t>) {
            auto result = return_t{};
            return result;
        } else {
            auto res = return_t{};

            auto m = len(ashape);
            auto n = len(bshape);
            auto s = m;

            if constexpr (meta::is_resizable_v<return_t>)
                res.resize(s);
            
            auto free_axes_impl = [&](auto i){
                // @todo support type list (tuple of int constant)
                using idx_t = meta::make_signed_t<decltype(m-i-1)>;
                idx_t bi = n - i - 1;
                idx_t si = s - i - 1;
                auto free = (bi < 0);
                if (!free)
                    free = at(bshape,bi) == 1;
                at(res,si) = free;
            }; // free_axes_impl

            // choose to use int since may be treated as signed
            for (int i=0; i<(int)len(res); i++)
                free_axes_impl(i);

            return res;
        }
    } // free_axes
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct FREE_AXES_UNSUPPORTED : detail::fail_t {};
    }

    template <typename ashape_t, typename bshape_t>
    struct resolve_optype<
        void, index::free_axes_t, ashape_t, bshape_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_maybe_v<ashape_t>) {
                using ashape_type = get_maybe_type_t<ashape_t>;
                using result_type = resolve_optype_t<index::free_axes_t,ashape_type,bshape_t>;
                if constexpr (is_maybe_v<result_type>) {
                    using type = result_type;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_maybe<result_type>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_maybe_v<bshape_t>) {
                using bshape_type = get_maybe_type_t<bshape_t>;
                using result_type = resolve_optype_t<index::free_axes_t,ashape_t,bshape_type>;
                using type = nmtools_maybe<result_type>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<ashape_t>
                && is_constant_index_array_v<bshape_t>
            ) {
                constexpr auto ashape = to_value_v<ashape_t>;
                constexpr auto bshape = to_value_v<bshape_t>;
                constexpr auto result = index::free_axes(ashape,bshape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto r_i = at(result,index);
                    using result_t = append_type_t<type_t<decltype(init)>,ct<r_i>>;
                    return as_value_v<result_t>;
                },as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_index_array_v<ashape_t> && is_index_array_v<bshape_t>) {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<ashape_t>;
                constexpr auto DIM   = len_v<ashape_t>;
                using element_t = nm_bool_t;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<element_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<element_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::FREE_AXES_UNSUPPORTED<ashape_t,bshape_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_FREE_AXES_HPP