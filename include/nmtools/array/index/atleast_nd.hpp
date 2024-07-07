#ifndef NMTOOLS_ARRAY_INDEX_ATLEAST_ND_HPP
#define NMTOOLS_ARRAY_INDEX_ATLEAST_ND_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray.hpp"

// TODO: move to shape.hpp
#ifdef NMTOOLS_ENABLE_BOOST
#include "nmtools/array/impl/boost.hpp"
#endif

namespace nmtools::index
{
    struct shape_atleast_nd_t {};

    template <typename shape_t, typename nd_t>
    constexpr auto shape_atleast_nd(const shape_t& shape, [[maybe_unused]] nd_t nd)
    {
        using result_t [[maybe_unused]] = meta::resolve_optype_t<shape_atleast_nd_t,shape_t,nd_t>;

        if constexpr (meta::is_maybe_v<shape_t>) {
            using shape_type = meta::get_maybe_type_t<shape_t>;
            using result_t   = meta::resolve_optype_t<shape_atleast_nd_t,shape_type,nd_t>;
            using return_t   = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (static_cast<bool>(shape)
                ? return_t{shape_atleast_nd(*shape,nd)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_constant_index_array_v<result_t>) {
            return result_t {};
        } else {
            auto result = result_t {};

            [[maybe_unused]]
            constexpr auto N = meta::len_v<shape_t>;

            auto dim = len(shape);
            auto max_dim = [&](){
                if constexpr ((N>0) && meta::is_constant_index_v<nd_t>) {
                    constexpr auto nd = nd_t{};
                    constexpr auto max_dim = ((nm_size_t)N > (nm_size_t)nd ? N : nd);
                    return meta::ct_v<max_dim>;
                } else {
                    return ((nm_size_t)dim > (nm_size_t)nd ? dim : nd);
                }
            }();
            auto diff = [&](){
                if constexpr ((N>0) && meta::is_constant_index_v<decltype(max_dim)>) {
                    constexpr auto diff = max_dim - N;
                    return meta::ct_v<diff>;
                } else {
                    return max_dim - dim;
                }
            }();
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(max_dim);
            }

            // assume diff is constant index
            constexpr auto DIFF = meta::to_value_v<decltype(diff)>;

            if constexpr (meta::is_tuple_v<result_t> && !meta::is_fail_v<decltype(DIFF)>) {
                meta::template_for<(size_t)DIFF>([&](auto i){
                    at(result,i) = 1;
                });
            } else {
                // fill ones for "extra" dim
                for (nm_index_t i=0; i<(nm_index_t)diff; i++) {
                    at(result,i) = 1;
                }
            }

            // fill the rest with src shape
            if constexpr (meta::is_tuple_v<shape_t> && !meta::is_fail_v<decltype(DIFF)>) {
                meta::template_for<N>([&](auto i){
                    constexpr auto I = meta::ct_v<i+diff>;
                    at(result,I) = at(shape,i);
                });
            } else {
                for (nm_index_t i=0; i<(nm_index_t)dim; i++) {
                    at(result,i+diff) = at(shape,i);
                }
            }

            return result;
        }
    } // shape_atleast_nd
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_ATLEAST_ND_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename shape_t, typename nd_t>
    struct resolve_optype<
        void, index::shape_atleast_nd_t, shape_t, nd_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<shape_t> && is_constant_index_v<nd_t>) {
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto result = index::shape_atleast_nd(shape,nd_t{});
                constexpr auto dim = nmtools::len(result);
                using init_type = nmtools_tuple<ct<nmtools::at(result,0)>>;
                return template_reduce<dim-1>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<nmtools::at(result,index+1)>>;
                    return as_value_v<type>;
                }, as_value_v<init_type>);
            } else if constexpr (is_clipped_index_array_v<shape_t> && is_constant_index_v<nd_t>) {
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto result = index::shape_atleast_nd(shape,nd_t{});
                using nmtools::at, nmtools::len;
                return template_reduce<(len(result)-1)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,clipped_size_t<at(result,index+1)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<clipped_size_t<at(result,0)>>>);
            } else if constexpr (is_fixed_index_array_v<shape_t> && is_constant_index_v<nd_t>) {
                constexpr auto nd  = nd_t::value;
                constexpr auto dim = len_v<shape_t>;
                using index_t = get_element_or_common_type_t<shape_t>;
                // TODO: use resize instead
                return as_value_v<nmtools_array<index_t,(dim > nd ? dim : nd)>>;
            } else if constexpr (is_hybrid_index_array_v<shape_t> && is_constant_index_v<nd_t> ) {
                constexpr auto nd = nd_t::value;
                constexpr auto max_dim = bounded_size_v<shape_t>;
                using index_t = get_element_or_common_type_t<shape_t>;
                // TODO: use resize instead
                return as_value_v<array::static_vector<index_t,(max_dim > nd ? max_dim : nd)>>;
            } else if constexpr (is_index_array_v<shape_t>) {
                using index_t = get_element_or_common_type_t<shape_t>;
                // TODO: support small_vector/small_buffer
                return as_value_v<nmtools_list<index_t>>;
            } else if constexpr (is_none_v<shape_t> && is_constant_index_v<nd_t>) {
                return template_reduce<nd_t::value-1>([](auto init, [[maybe_unused]] auto index){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<1ul>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<ct<1ul>>>);
            } else if constexpr (is_none_v<shape_t> && is_index_v<nd_t>) {
                // TODO; consider to use index_type
                return as_value_v<nmtools_list<size_t>>;
            } else {
                return as_value_v<error::SHAPE_ATLEAST_ND_UNSUPPORTED<shape_t,nd_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_ATLEAST_ND_HPP