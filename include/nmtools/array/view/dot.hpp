#ifndef NMTOOLS_ARRAY_VIEW_DOT_HPP
#define NMTOOLS_ARRAY_VIEW_DOT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct dot_rhs_transpose_t {};

    template <typename rhs_shape_t>
    constexpr auto dot_rhs_transpose(const rhs_shape_t& rhs_shape)
    {
        using result_t = meta::resolve_optype_t<dot_rhs_transpose_t,rhs_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto rhs_dim = len(rhs_shape);

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(rhs_dim);
            }

            for (nm_size_t i=0; i<rhs_dim; i++) {
                at(result,i) = i;
            }
            if (rhs_dim > 1) {
                auto axis1 = at(result,-1);
                at(result,-1) = at(result,-2);
                at(result,-2) = axis1;
            }
        }

        return result;
    }

    struct dot_lhs_tile_t {};

    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto dot_lhs_tile(const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using result_t = meta::resolve_optype_t<dot_lhs_tile_t,lhs_shape_t,rhs_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto lhs_dim = len(lhs_shape);
            auto rhs_dim = len(rhs_shape);

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(lhs_dim);
            }

            for (nm_size_t i=0; i<lhs_dim; i++) {
                at(result,i) = 1;
            }

            if (rhs_dim > 1) {
                at(result,-1) = at(rhs_shape,-1);
            }
        }

        return result;
    }

    struct dot_lhs_reshape_t {};

    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto dot_lhs_reshape(const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using result_t = meta::resolve_optype_t<dot_lhs_reshape_t,lhs_shape_t,rhs_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto lhs_dim = len(lhs_shape);
            auto rhs_dim = len(rhs_shape);

            nm_index_t dst_dim = lhs_dim + rhs_dim - 2;
            dst_dim = (nm_index_t)dst_dim < (nm_index_t)lhs_dim ? lhs_dim : dst_dim;
            dst_dim = rhs_dim > 1 ? dst_dim + 1 : dst_dim;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                at(result,i) = 1;
            }

            nm_size_t r_i = 0;
            for (nm_size_t i=0; i<(nm_size_t)lhs_dim-1; i++) {
                at(result,r_i++) = at(lhs_shape,i);
            }
            if (rhs_dim > 1) {
                at(result,-2) = at(rhs_shape,-1);
                at(result,-1) = at(rhs_shape,-2);
            } else {
                at(result,-1) = at(rhs_shape,-1);
            }
        }

        return result;
    }
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct DOT_RHS_TRANSPOSE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct DOT_LHS_TILE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct DOT_LHS_RESHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename rhs_shape_t>
    struct resolve_optype<
        void, index::dot_rhs_transpose_t, rhs_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<rhs_shape_t>) {
                using type = error::DOT_RHS_TRANSPOSE_UNSUPPORTED<rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<rhs_shape_t>) {
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::dot_rhs_transpose(rhs_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<rhs_shape_t>;
                constexpr auto DIM   = len_v<rhs_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM>;
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

    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype<
        void, index::dot_lhs_tile_t, lhs_shape_t, rhs_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_shape_t>
                || !is_index_array_v<rhs_shape_t>
            ) {
                using type = error::DOT_LHS_TILE_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<lhs_shape_t>
                && is_constant_index_array_v<rhs_shape_t>
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::dot_lhs_tile(lhs_shape,rhs_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<lhs_shape_t>;
                constexpr auto DIM   = len_v<lhs_shape_t>; 

                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,B_DIM>;
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

    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype<
        void, index::dot_lhs_reshape_t, lhs_shape_t, rhs_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<lhs_shape_t>
                || !is_index_array_v<rhs_shape_t>
            ) {
                using type = error::DOT_LHS_RESHAPE_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<lhs_shape_t>
                && is_constant_index_array_v<rhs_shape_t>
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::dot_lhs_reshape(lhs_shape,rhs_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]] constexpr auto LHS_B_DIM = bounded_size_v<lhs_shape_t>;
                [[maybe_unused]] constexpr auto RHS_B_DIM = bounded_size_v<rhs_shape_t>;
                constexpr auto LHS_DIM = len_v<lhs_shape_t>;
                constexpr auto RHS_DIM = len_v<rhs_shape_t>;
                if constexpr (
                    (LHS_DIM > 0) && (RHS_DIM > 0)
                ) {
                    constexpr nm_index_t TMP_DIM1 = LHS_DIM + RHS_DIM - 2;
                    constexpr nm_index_t TMP_DIM2 = TMP_DIM1 > LHS_DIM ? TMP_DIM1 : LHS_DIM;
                    constexpr auto DST_DIM = RHS_DIM > 1 ? (TMP_DIM2 + 1) : TMP_DIM2;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (
                    !is_fail_v<decltype(LHS_B_DIM)>
                    && !is_fail_v<decltype(RHS_B_DIM)>
                ) {
                    constexpr nm_index_t TMP_DIM1 = LHS_B_DIM + RHS_B_DIM - 2;
                    constexpr nm_index_t TMP_DIM2 = TMP_DIM1 > LHS_B_DIM ? TMP_DIM1 : LHS_B_DIM;
                    constexpr auto DST_DIM = RHS_B_DIM > 1 ? (TMP_DIM2 + 1) : TMP_DIM2;
                    using type = nmtools_static_vector<nm_size_t,DST_DIM>;
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

/******************************************************************************/

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/alias.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t>
    constexpr auto dot(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto lhs_shape = shape<true>(lhs);
        auto rhs_shape = shape<true>(rhs);

        auto reps = index::dot_lhs_tile(lhs_shape,rhs_shape);
        auto dst_shape = index::dot_lhs_reshape(lhs_shape,rhs_shape);
        auto axes = index::dot_rhs_transpose(rhs_shape);

        auto aliased = view::aliased(lhs,rhs);
        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);

        auto tf_lhs = view::reshape(view::tile(a_lhs,reps),dst_shape);
        auto tf_rhs = view::transpose(a_rhs,axes);

        return view::sum(view::multiply(tf_lhs,tf_rhs),meta::ct_v<-1>);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_DOT_HPP