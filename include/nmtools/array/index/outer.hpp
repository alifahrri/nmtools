#ifndef NMTOOLS_ARRAY_INDEX_OUTER_HPP
#define NMTOOLS_ARRAY_INDEX_OUTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/index/product.hpp"

namespace nmtools::index
{
    struct shape_outer_t {};

    template <typename ashape_t, typename bshape_t>
    constexpr auto shape_outer(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<shape_outer_t,ashape_t,bshape_t>;
        auto res = return_t {};

        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            auto adim = len(ashape);
            auto bdim = len(bshape);
            if constexpr (meta::is_resizeable_v<return_t>) {
                auto dim  = adim + bdim;
                res.resize(dim);
            }
            
            for (size_t i=0; i<adim; i++)
                at(res,i) = at(ashape,i);
            for (size_t i=0; i<bdim; i++)
                at(res,i+adim) = at(bshape,i);
        }
        
        return res;
    } // shape_outer

    struct size_outer_t {};

    template <typename dst_shape_t, typename a_size_t, typename b_size_t>
    constexpr auto size_outer(const dst_shape_t&, const a_size_t& a_size, const b_size_t& b_size)
    {
        using result_t = meta::resolve_optype_t<size_outer_t,dst_shape_t,a_size_t,b_size_t>;
        auto res = result_t {};

        if constexpr (!meta::is_constant_index_v<result_t>) {
            res = static_cast<result_t>(a_size) * static_cast<result_t>(b_size);
        }

        return res;
    } // size_outer

    template <typename indices_t, typename ashape_t, typename bshape_t>
    constexpr auto outer(const indices_t& indices, const ashape_t& ashape, const bshape_t& bshape)
    {
        using aidx_t = meta::tuple_to_array_t<meta::transform_bounded_array_t<ashape_t>>;
        using bidx_t = meta::tuple_to_array_t<meta::transform_bounded_array_t<bshape_t>>;
        auto aidx = aidx_t {};
        auto bidx = bidx_t {};

        auto adim = len(ashape);
        auto bdim = len(bshape);

        if constexpr (meta::is_resizeable_v<ashape_t>)
            aidx.resize(adim);
        if constexpr (meta::is_resizeable_v<bshape_t>)
            bidx.resize(bdim);
        
        for (size_t i=0; i<adim; i++)
            at(aidx,i) = at(indices,i);
        for (size_t i=0; i<bdim; i++)
            at(bidx,i) = at(indices,i+adim);
        
        using return_t = meta::make_tuple_type_t<aidx_t,bidx_t>;
        return return_t{aidx,bidx};
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_OUTER_UNSUPPORTED : detail::fail_t {};
    }

    template <typename ashape_t, typename bshape_t>
    struct resolve_optype<
        void, index::shape_outer_t, ashape_t, bshape_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                constexpr auto result = index::shape_outer(to_value_v<ashape_t>,to_value_v<bshape_t>);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)-1>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    return as_value_v<append_type_t<init_type,ct<at(result,index+1)>>>;
                }, as_value_v<nmtools_tuple<ct<at(result,0)>>>);
            } else if constexpr (
                is_index_array_v<ashape_t>
                && is_index_array_v<bshape_t>
            ) {
                constexpr auto len_a = len_v<ashape_t>;
                constexpr auto len_b = len_v<bshape_t>;
                [[maybe_unused]] constexpr auto b_dim_a = bounded_size_v<ashape_t>;
                [[maybe_unused]] constexpr auto b_dim_b = bounded_size_v<bshape_t>;
                if constexpr ((len_a > 0) && (len_b > 0)) {
                    constexpr auto new_dim = len_a + len_b;
                    using type = nmtools_array<size_t,new_dim>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_dim_a)> && !is_fail_v<decltype(b_dim_b)>) {
                    constexpr auto new_dim = b_dim_a + b_dim_b;
                    using type = array::static_vector<size_t,new_dim>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<size_t>;
                    return as_value_v<type>;
                }
            } else {
                return as_value<error::SHAPE_OUTER_UNSUPPORTED<ashape_t,bshape_t>>{};
            }
        }();

        using type = type_t<meta::remove_cvref_t<decltype(vtype)>>;
    }; // shape_outer_t

    namespace error
    {
        template <typename...>
        struct SIZE_OUTER_UNSUPPORTED : detail::fail_t {};
    }

    template <typename dst_shape_t, typename a_size_t, typename b_size_t>
    struct resolve_optype<
        void, index::size_outer_t, dst_shape_t, a_size_t, b_size_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<dst_shape_t>) {
                constexpr auto size = index::product(to_value_v<dst_shape_t>);
                using type = ct<size>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<a_size_t>
                && is_constant_index_v<b_size_t>
            ) {
                constexpr auto size = to_value_v<a_size_t> * to_value_v<b_size_t>;
                using type = ct<size>;
                return as_value_v<type>;
            } else if constexpr (
                is_index_v<a_size_t>
                && is_index_v<b_size_t>
            ) {
                using type = size_t;
                return as_value_v<type>;
            } else {
                using type = error::SIZE_OUTER_UNSUPPORTED<dst_shape_t,a_size_t,b_size_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // size_outer_t
}

#endif // NMTOOLS_ARRAY_INDEX_OUTER_HPP