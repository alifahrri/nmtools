#ifndef NMTOOLS_ARRAY_VIEW_TENSORDOT_HPP
#define NMTOOLS_ARRAY_VIEW_TENSORDOT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/index/range.hpp"
#include "nmtools/index/normalize_axis.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/index/contains.hpp"

namespace nmtools::index
{
    struct tensordot_lhs_transpose_t {};

    template <typename lhs_dim_t, typename axes_t>
    constexpr auto tensordot_lhs_transpose([[maybe_unused]] lhs_dim_t lhs_dim, [[maybe_unused]] const axes_t& axes)
    {
        using result_t = meta::resolve_optype_t<tensordot_lhs_transpose_t,lhs_dim_t,axes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(lhs_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)lhs_dim; i++) {
                at(result,i) = i;
            }

            if constexpr (!meta::is_index_v<axes_t>) {
                // TODO: propagate error
                auto m_axes = unwrap(normalize_axis(axes,lhs_dim));
                nm_index_t index = 0;
                for (nm_size_t i=0; i<(nm_size_t)lhs_dim; i++) {
                    if (contains(m_axes,i)) {
                        continue;
                    }
                    at(result,index++) = i;
                }
                for (nm_size_t i=0; i<(nm_size_t)len(m_axes); i++) {
                    at(result,index++) = at(m_axes,i);
                }
            }
        }

        return result;
    } // tensordot_lhs_transpose

    struct tensordot_rhs_transpose_t {};

    template <typename rhs_dim_t, typename axes_t>
    constexpr auto tensordot_rhs_transpose([[maybe_unused]] rhs_dim_t rhs_dim, [[maybe_unused]] const axes_t& axes)
    {
        using result_t = meta::resolve_optype_t<tensordot_rhs_transpose_t,rhs_dim_t,axes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(rhs_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)rhs_dim; i++) {
                at(result,i) = i;
            }

            nm_size_t index = 0;

            const auto m_axes = [&](){
                if constexpr (meta::is_index_v<axes_t>) {
                    return range(meta::ct_v<0>,axes);
                } else {
                    // TODO: propagate error
                    return unwrap(normalize_axis(axes,rhs_dim));
                }
            }();

            for (nm_size_t i=0; i<(nm_size_t)rhs_dim; i++) {
                if (contains(m_axes,i)) {
                    continue;
                }
                at(result,index) = i;
                index++;
            }

            for (nm_size_t i=0; i<(nm_size_t)len(m_axes); i++) {
                at(result,index) = at(m_axes,i);
                index++;
            }
        }

        return result;
    } // tensordot_rhs_transpose

    struct tensordot_lhs_reshape_t {};

    template <typename lhs_shape_t, typename rhs_shape_t, typename lhs_axes_t>
    constexpr auto tensordot_lhs_reshape([[maybe_unused]] const lhs_shape_t& lhs_shape
        , [[maybe_unused]] const rhs_shape_t& rhs_shape
        , [[maybe_unused]] const lhs_axes_t& lhs_axes
    ) {
        using result_t = meta::resolve_optype_t<tensordot_lhs_reshape_t,lhs_shape_t,rhs_shape_t,lhs_axes_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto lhs_dim = len(lhs_shape);
            auto rhs_dim = len(rhs_shape);
            auto sum_dim = [&](){
                if constexpr (meta::is_index_v<lhs_axes_t>) {
                    return lhs_axes;
                } else {
                    return len(lhs_axes);
                }
            }();
            auto dst_dim = lhs_dim + rhs_dim - sum_dim;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                at(result,i) = 1;
            }

            auto non_contracted = lhs_dim - sum_dim;
            for (nm_size_t i=0; i<(non_contracted); i++) {
                at(result,i) = at(lhs_shape,i);
            }
            for (nm_size_t i=0; i<(sum_dim); i++) {
                nm_index_t index = -(i+1);
                at(result,index) = at(lhs_shape,index);
            }
        }

        return result;
    } // tensordot_lhs_reshape
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TENSORDOT_LHS_TRANSPOSE_UNSUPPORTED : detail::fail_t {};
        
        template <typename...>
        struct TENSORDOT_RHS_TRANSPOSE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct TENSORDOT_LHS_RESHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename lhs_dim_t, typename axes_t>
    struct resolve_optype<
        void, index::tensordot_lhs_transpose_t, lhs_dim_t, axes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<lhs_dim_t>
                || !(is_index_array_v<axes_t> || is_index_v<axes_t>)
            ) {
                using type = error::TENSORDOT_LHS_TRANSPOSE_UNSUPPORTED<lhs_dim_t,axes_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<lhs_dim_t>
                && (is_constant_index_array_v<axes_t> || is_constant_index_v<axes_t>)
            ) {
                constexpr auto lhs_dim    = to_value_v<lhs_dim_t>;
                constexpr auto lhs_dim_cl = clipped_size_t<lhs_dim>(lhs_dim);
                constexpr auto axes = [&](){
                    if constexpr (is_constant_index_v<axes_t>) {
                        constexpr auto axes = to_value_v<axes_t>;
                        constexpr auto axes_cl = clipped_size_t<(nm_size_t)axes>(axes);   
                        return axes_cl;
                    } else {
                        return to_value_v<axes_t>;
                    }
                }();
                constexpr auto result = index::tensordot_lhs_transpose(lhs_dim_cl,axes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                if constexpr (is_constant_index_v<lhs_dim_t>) {
                    constexpr auto DIM = lhs_dim_t::value;
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (is_clipped_index_v<lhs_dim_t>) {
                    constexpr auto MAX_DIM = max_value_v<lhs_dim_t>;
                    using type = nmtools_static_vector<nm_size_t,MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: small vector optimization
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::tensordot_lhs_transpose_t

    template <typename rhs_dim_t, typename axes_t>
    struct resolve_optype<
        void, index::tensordot_rhs_transpose_t, rhs_dim_t, axes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<rhs_dim_t>
                || !(is_index_v<axes_t> || is_index_array_v<axes_t>)
            ) {
                using type = error::TENSORDOT_RHS_TRANSPOSE_UNSUPPORTED<rhs_dim_t,axes_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<rhs_dim_t>
                && (is_constant_index_array_v<axes_t> || is_constant_index_v<axes_t>)
            ) {
                constexpr auto rhs_dim    = to_value_v<rhs_dim_t>;
                constexpr auto rhs_dim_cl = clipped_size_t<rhs_dim>(rhs_dim);
                constexpr auto axes = [&](){
                    if constexpr (is_constant_index_v<axes_t>) {
                        constexpr auto axes = to_value_v<axes_t>;
                        constexpr auto axes_cl = clipped_size_t<(nm_size_t)axes>(axes);   
                        return axes_cl;
                    } else {
                        return to_value_v<axes_t>;
                    }
                }();
                constexpr auto result = index::tensordot_rhs_transpose(rhs_dim_cl,axes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                if constexpr (is_constant_index_v<rhs_dim_t>) {
                    constexpr auto DIM = rhs_dim_t::value;
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (is_clipped_index_v<rhs_dim_t>) {
                    constexpr auto MAX_DIM = max_value_v<rhs_dim_t>;
                    using type = nmtools_static_vector<nm_size_t,MAX_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: small vector optimization
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename lhs_shape_t, typename rhs_shape_t, typename lhs_axes_t>
    struct resolve_optype<
        void, index::tensordot_lhs_reshape_t, lhs_shape_t, rhs_shape_t, lhs_axes_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_shape_t>
                || !is_index_array_v<rhs_shape_t>
                || !(is_index_array_v<lhs_axes_t> || is_index_v<lhs_axes_t>)
            ) {
                using type = error::TENSORDOT_LHS_RESHAPE_UNSUPPORTED<lhs_shape_t,rhs_shape_t,lhs_axes_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<lhs_shape_t>
                && is_constant_index_array_v<lhs_shape_t>
                && (is_constant_index_array_v<lhs_axes_t> || is_constant_index_v<lhs_axes_t>)
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto lhs_axes  = to_value_v<lhs_axes_t>;
                constexpr auto result = index::tensordot_lhs_reshape(lhs_shape,rhs_shape,lhs_axes);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto LHS_DIM = len_v<lhs_shape_t>;
                constexpr auto RHS_DIM = len_v<rhs_shape_t>;

                [[maybe_unused]] constexpr auto LHS_B_DIM = bounded_size_v<lhs_shape_t>;
                [[maybe_unused]] constexpr auto RHS_B_DIM = bounded_size_v<rhs_shape_t>;

                [[maybe_unused]] constexpr auto AXIS_DIM = len_v<lhs_axes_t>;

                if constexpr ((LHS_DIM > 0) && (RHS_DIM > 0)
                    && (is_constant_index_v<lhs_axes_t> || (AXIS_DIM > 0))
                ) {
                    constexpr auto SUM_DIM = [&](){
                        if constexpr (AXIS_DIM > 0) {
                            return AXIS_DIM;
                        } else {
                            return lhs_axes_t::value;
                        }
                    }();
                    constexpr auto DST_DIM = LHS_DIM + RHS_DIM - SUM_DIM;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)>
                    && !is_fail_v<decltype(RHS_B_DIM)>
                ) {
                    // lhs_axes used as subtractor, contribute inversely to max dim
                    constexpr auto DST_B_DIM = LHS_B_DIM + RHS_B_DIM - 1;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // nmtools::meta

/*******************************************************************************/

#include "nmtools/core/decorator.hpp"
#include "nmtools/core/alias.hpp"
#include "nmtools/array/transpose.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename axes_t=meta::ct<2>>
    constexpr auto tensordot(const lhs_t& lhs, const rhs_t& rhs, const axes_t& axes=axes_t{})
    {
        auto lhs_axes = [&](){
            if constexpr (meta::is_tuple_v<axes_t>) {
                return nmtools::get<0>(axes);
            } else {
                return axes;
            }
        }();
        auto rhs_axes = [&](){
            if constexpr (meta::is_tuple_v<axes_t>) {
                return nmtools::get<1>(axes);
            } else {
                return axes;
            }
        }();
        auto sum_dim = [&](){
            if constexpr (meta::is_tuple_v<axes_t>) {
                return size<true>(lhs_axes);
            } else {
                return axes;
            }
        }();
        auto sum_axis = [&](){
            if constexpr (meta::is_constant_index_v<decltype(sum_dim)>) {
                constexpr auto N = meta::to_value_v<decltype(sum_dim)>;
                return meta::template_reduce<N>([&](auto init, auto I){
                    constexpr auto i = decltype(I)::value;
                    using init_t = meta::remove_cvref_t<decltype(init)>;
                    using type = meta::append_type_t<init_t,meta::ct<-int(i+1)>>;
                    return type{};
                }, nmtools_tuple{});
            } else {
                // TODO: support small vector
                using result_t = nmtools_list<nm_index_t>;
                auto result = result_t {};
                result.resize(sum_dim);
                for (nm_size_t i=0; i<(nm_size_t)len(result); i++) {
                    at(result,i) = -(i+1);
                }
                return result;
            }
        }();

        // auto lhs_shape = shape<true>(lhs);
        auto lhs_dim = dim<true>(lhs);
        auto lhs_transpose_axes = index::tensordot_lhs_transpose(lhs_dim,lhs_axes);

        auto rhs_shape = shape<true>(rhs);
        auto rhs_dim = dim<true>(rhs);
        auto rhs_transpose_axes = index::tensordot_rhs_transpose(rhs_dim,rhs_axes);

        auto aliased = view::aliased(lhs,rhs);
        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);

        auto a = view::transpose(a_lhs,lhs_transpose_axes);
        
        auto lhs_dst_shape = index::tensordot_lhs_reshape(shape<true>(a),rhs_shape,sum_axis);

        auto b = view::reshape(a,lhs_dst_shape);
        auto c = view::transpose(a_rhs,rhs_transpose_axes);
        auto d = view::multiply(b,c);

        auto dtype    = None;
        auto initial  = None;
        auto keepdims = False;
        auto e = view::sum(d,sum_axis,dtype,initial,keepdims);

        return e;
    } // tensordot
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_TENSORDOT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TENSORDOT_HPP
#define NMTOOLS_ARRAY_ARRAY_TENSORDOT_HPP

#include "nmtools/array/tensordot.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename lhs_t, typename rhs_t, typename axes_t=meta::ct<2>>
    constexpr auto tensordot(const lhs_t& lhs, const rhs_t& rhs, axes_t axes=axes_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::tensordot(lhs,rhs,axes);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // tensordot
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TENSORDOT_HPP