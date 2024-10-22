#ifndef NTMOOLS_ARRAY_VIEW_KRON_HPP
#define NTMOOLS_ARRAY_VIEW_KRON_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::index
{
    struct kron_dst_transpose_t {};

    template <typename lhs_dim_t, typename rhs_dim_t>
    constexpr auto kron_dst_transpose(const lhs_dim_t& lhs_dim, const rhs_dim_t& rhs_dim)
        -> meta::resolve_optype_t<kron_dst_transpose_t,lhs_dim_t,rhs_dim_t>
    {
        using result_t = meta::resolve_optype_t<kron_dst_transpose_t,lhs_dim_t,rhs_dim_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto dst_dim = (nm_size_t)lhs_dim + (nm_size_t)rhs_dim;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                at(result,i) = i;
            }

            if ((nm_size_t)lhs_dim == (nm_size_t)rhs_dim) {
                for (nm_size_t i=0; i<(nm_size_t)dst_dim/2; i++) {
                    at(result,i*2) = i;
                }
                for (nm_size_t i=0; i<(nm_size_t)dst_dim/2; i++) {
                    at(result,i*2+1) = i + (dst_dim/2);
                }
            } else if (lhs_dim < rhs_dim) {
                auto rhs_dim_i = [&](){
                    if constexpr (meta::is_constant_index_v<rhs_dim_t>) {
                        return meta::ct_v<rhs_dim_t::value-1>;
                    } else if constexpr (meta::is_clipped_integer_v<rhs_dim_t>) {
                        constexpr auto max_i = meta::max_value_v<rhs_dim_t>;
                        return clipped_size_t<max_i>{rhs_dim-1};
                    } else {
                        return rhs_dim-1;
                    }
                }();
                auto initial_axes = kron_dst_transpose(lhs_dim,rhs_dim_i);
                for (nm_size_t i=0; i<(nm_size_t)(dst_dim-1); i++) {
                    at(result,i) = at(initial_axes,i);
                }
                for (nm_size_t i=0; i<(nm_size_t)lhs_dim; i++) {
                    nm_index_t idx = -(i+1) * 2;
                    auto tmp = at(result,idx);
                    at(result,idx) = at(result,idx-1);
                    at(result,idx-1) = tmp;
                }
            } else {
                auto rhs_dim_i = [&](){
                    if constexpr (meta::is_constant_index_v<rhs_dim_t>) {
                        return meta::ct_v<rhs_dim_t::value+1>;
                    } else if constexpr (meta::is_clipped_integer_v<rhs_dim_t>) {
                        constexpr auto max_rdim = meta::max_value_v<rhs_dim_t>;
                        constexpr auto max_ldim = meta::max_value_v<lhs_dim_t>;

                        // avoid calling the function recursively at compile-time
                        if constexpr (!meta::is_fail_v<decltype(max_ldim)>) {
                            if constexpr (max_rdim <= max_ldim) {
                                constexpr auto max_i = max_rdim + 1;
                                return clipped_size_t<max_i>(rhs_dim+1);
                            } else {
                                // unreachable
                                return rhs_dim + 1;
                            }
                        } else {
                            return rhs_dim + 1;
                        }
                    } else {
                        return rhs_dim+1;
                    }
                }();
                auto initial_axes = kron_dst_transpose(lhs_dim,rhs_dim_i);
                for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                    at(result,i) = at(initial_axes,i);
                }
                for (nm_size_t i=0; i<(nm_size_t)rhs_dim; i++) {
                    nm_index_t idx = -(i*2+1);
                    auto tmp = at(result,idx);
                    at(result,idx) = at(result,idx-1);
                    at(result,idx-1) = tmp;
                }
            }
        }
        
        return result;
    } // kron_dst_transpose

    struct kron_lhs_reshape_t {};

    template <typename lhs_shape_t, typename rhs_dim_t>
    constexpr auto kron_lhs_reshape([[maybe_unused]] const lhs_shape_t& lhs_shape, [[maybe_unused]] rhs_dim_t rhs_dim)
    {
        using result_t = meta::resolve_optype_t<kron_lhs_reshape_t,lhs_shape_t,rhs_dim_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto lhs_dim = len(lhs_shape);
            auto dst_dim = lhs_dim + rhs_dim;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            for (nm_size_t i=0; i<(nm_size_t)dst_dim; i++) {
                at(result,i) = 1;
            }
            for (nm_size_t i=0; i<(nm_size_t)lhs_dim; i++) {
                at(result,i) = at(lhs_shape,i);
            }
        }

        return result;
    } // kron_lhs_reshape

    struct kron_dst_reshape_t {};

    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto kron_dst_reshape(const lhs_shape_t& lhs_shape, const rhs_shape_t& rhs_shape)
    {
        using result_t = meta::resolve_optype_t<kron_dst_reshape_t,lhs_shape_t,rhs_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>
        ) {
            auto lhs_dim = len(lhs_shape);
            auto rhs_dim = len(rhs_shape);

            auto dst_dim = (lhs_dim > rhs_dim ? lhs_dim : rhs_dim);

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            for (nm_index_t i=1; i<=(nm_index_t)dst_dim; i++) {
                auto n_i_lhs = -i + lhs_dim;
                auto n_i_rhs = -i + rhs_dim;
                if (   (n_i_lhs < lhs_dim)
                    && (n_i_rhs < rhs_dim)
                    && (n_i_lhs >= 0)
                    && (n_i_rhs >= 0)
                ) {
                    at(result,-i) = at(lhs_shape,-i) * at(rhs_shape,-i);
                } else if (
                    (n_i_lhs < lhs_dim)
                    && (n_i_lhs >= 0)
                ) {
                    at(result,-i) = at(lhs_shape,-i);
                } else {
                    at(result,-i) = at(rhs_shape,-i);
                }
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
        struct KRON_DST_TRANSPOSE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct KRON_LHS_RESHAPE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct KRON_DST_RESHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename lhs_dim_t, typename rhs_dim_t>
    struct resolve_optype<
        void, index::kron_dst_transpose_t, lhs_dim_t, rhs_dim_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<lhs_dim_t>
                || !is_index_v<rhs_dim_t>
            ) {
                using type = error::KRON_DST_TRANSPOSE_UNSUPPORTED<lhs_dim_t,rhs_dim_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<lhs_dim_t>
                && is_constant_index_v<rhs_dim_t>
            ) {
                constexpr auto lhs_dim = to_value_v<lhs_dim_t>;
                constexpr auto rhs_dim = to_value_v<rhs_dim_t>;
                constexpr auto result = index::kron_dst_transpose(clipped_size_t<lhs_dim>(lhs_dim),clipped_size_t<rhs_dim>(rhs_dim));
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]] constexpr auto LHS_MAX = max_value_v<lhs_dim_t>;
                [[maybe_unused]] constexpr auto RHS_MAX = max_value_v<rhs_dim_t>;
                if constexpr (is_constant_index_v<lhs_dim_t> && is_constant_index_v<rhs_dim_t>) {
                    constexpr auto DST_DIM = lhs_dim_t::value + rhs_dim_t::value;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_MAX)>
                    && !is_fail_v<decltype(RHS_MAX)>
                ) {
                    constexpr auto DST_B_DIM = LHS_MAX + RHS_MAX;
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
    }; // index::kron_dst_transpose_t

    template <typename lhs_shape_t, typename rhs_dim_t>
    struct resolve_optype<
        void, index::kron_lhs_reshape_t, lhs_shape_t, rhs_dim_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<rhs_dim_t>
                || !is_index_array_v<lhs_shape_t>
            ) {
                using type = error::KRON_LHS_RESHAPE_UNSUPPORTED<lhs_shape_t,rhs_dim_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_v<rhs_dim_t>
                && is_constant_index_array_v<lhs_shape_t>
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto result = index::kron_lhs_reshape(lhs_shape,rhs_dim_t{});
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto LHS_B_DIM = bounded_size_v<lhs_shape_t>;
                [[maybe_unused]]
                constexpr auto RHS_MAX = max_value_v<rhs_dim_t>;
                constexpr auto LHS_DIM = len_v<lhs_shape_t>;
                if constexpr ((LHS_DIM > 0) && is_constant_index_v<rhs_dim_t>) {
                    constexpr auto DST_DIM = LHS_DIM + rhs_dim_t::value;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)>
                    && !is_fail_v<decltype(RHS_MAX)>
                ) {
                    constexpr auto DST_B_DIM = LHS_B_DIM + RHS_MAX;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: small vector optimization
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::kron_lhs_reshape_t

    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype<
        void, index::kron_dst_reshape_t, lhs_shape_t, rhs_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_array_v<lhs_shape_t>
                || !is_index_array_v<rhs_shape_t>
            ) {
                using type = error::KRON_DST_RESHAPE_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<lhs_shape_t>
                && is_constant_index_array_v<rhs_shape_t>
            ) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::kron_dst_reshape(lhs_shape,rhs_shape);
                using nmtools::at, nmtools::len;
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
                if constexpr ((LHS_DIM > 0) && (RHS_DIM > 0)) {
                    constexpr auto DST_DIM = (LHS_DIM > RHS_DIM ? LHS_DIM : RHS_DIM);
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(LHS_B_DIM)>
                    && !is_fail_v<decltype(RHS_B_DIM)>
                ) {
                    constexpr auto DST_B_DIM = (LHS_B_DIM > RHS_B_DIM ? LHS_B_DIM : RHS_B_DIM);
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: small vector optimization
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::kron_dst_reshape_t
} // nmtools::meta

/*******************************************************************************/

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/alias.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t>
    constexpr auto kron(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto lhs_shape = shape<true>(lhs);
        auto rhs_shape = shape<true>(rhs);
        auto lhs_dim   = dim<true>(lhs);
        auto rhs_dim   = dim<true>(rhs);

        auto aliased = view::aliased(lhs,rhs);

        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);

        auto lhs_dst_shape = index::kron_lhs_reshape(lhs_shape,rhs_dim);
        auto dst_axes  = index::kron_dst_transpose(lhs_dim,rhs_dim);
        auto dst_shape = index::kron_dst_reshape(lhs_shape,rhs_shape);

        auto a = view::reshape(a_lhs,lhs_dst_shape);
        auto b = view::tile(a,rhs_shape);
        auto c = view::multiply(b,a_rhs);
        auto d = view::transpose(c,dst_axes);
        auto e = view::reshape(d,dst_shape);
        return e;
    } // kron
} // nmtools::view

#endif // NTMOOLS_ARRAY_VIEW_KRON_HPP