#ifndef NMTOOLS_ARRAY_INDEX_VSTACK_HPP
#define NMTOOLS_ARRAY_INDEX_VSTACK_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct shape_vstack_t {};

    // return the shape for reshape for vstack
    template <typename src_shape_t>
    constexpr auto shape_vstack(const src_shape_t& src_shape)
    {
        using result_t = meta::resolve_optype_t<shape_vstack_t,src_shape_t>;
        
        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            auto src_dim = len(src_shape);
            if constexpr (meta::is_resizable_v<result_t>) {
                auto dst_dim = (src_dim == 1 ? 2 : src_dim);
                result.resize(dst_dim);
            }
            if (src_dim == 1) {
                at(result,0) = 1;
                at(result,1) = at(src_shape,0);
            } else {
                for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                    at(result,i) = at(src_shape,i);
                }
            }
        }

        return result;
    } // shape_vstack
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_VSTACK_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t>
    struct resolve_optype<void,index::shape_vstack_t,src_shape_t>
    {
        static constexpr auto vtype = [](){
            using index_t [[maybe_unused]] = get_index_element_type_t<src_shape_t>;
            [[maybe_unused]] constexpr auto DIM   = len_v<src_shape_t>;
            [[maybe_unused]] constexpr auto B_DIM = bounded_size_v<src_shape_t>;
            if constexpr (is_constant_index_array_v<src_shape_t>) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto result    = index::shape_vstack(src_shape);
                using nmtools::len, nmtools::at;
                return meta::template_reduce<len(result)>([&](auto init, auto index){
                    using init_type   = type_t<decltype(init)>;
                    using result_type = append_type_t<init_type,ct<at(result,index)>>;
                    return as_value_v<result_type>;
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (DIM > 0) {
                using type = nmtools_array<index_t,((DIM==1) ? 2 : DIM)>;
                return as_value_v<type>;
            } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                using type = nmtools_static_vector<index_t,((B_DIM==1) ? 2 : B_DIM)>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<src_shape_t>) {
                using type = nmtools_list<index_t>;
                return as_value_v<type>;
            } else {
                using type = error::SHAPE_VSTACK_UNSUPPORTED<src_shape_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_VSTACK_HPP

#ifndef NMTOOLS_ARRAY_VIEW_VSTACK_HPP
#define NMTOOLS_ARRAY_VIEW_VSTACK_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/concatenate.hpp"
#include "nmtools/array/reshape.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t>
    constexpr auto vstack(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto aliased = view::aliased(lhs,rhs);
        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);
        auto reshaped_lhs = [&](){
            auto src_shape = shape<true>(a_lhs);
            auto dst_shape = index::shape_vstack(src_shape);
            return view::reshape(a_lhs,dst_shape);
        }();
        auto rehsaped_rhs = [&](){
            auto src_shape = shape<true>(a_rhs);
            auto dst_shape = index::shape_vstack(src_shape);
            return view::reshape(a_rhs,dst_shape);
        }();
        return view::concatenatev2(
            reshaped_lhs
            , rehsaped_rhs
            , meta::ct_v<0>
        );
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_VSTACK_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_VSTACK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_VSTACK_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/vstack.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct vstack_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::vstack(args...);
            }
        };
    }

    constexpr inline auto vstack = functor_t{binary_fmap_t<fun::vstack_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_VSTACK_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_VSTACK_HPP
#define NMTOOLS_ARRAY_ARRAY_VSTACK_HPP

#include "nmtools/array/vstack.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename lhs_array_t, typename rhs_array_t>
    constexpr auto vstack(const lhs_array_t& lhs, const rhs_array_t& rhs,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto result = view::vstack(lhs,rhs);
        return eval(result
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // vstack
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_VSTACK_HPP