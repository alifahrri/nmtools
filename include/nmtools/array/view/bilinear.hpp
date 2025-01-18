#ifndef NMTOOLS_ARRAY_VIEW_BILINEAR_HPP
#define NMTOOLS_ARRAY_VIEW_BILINEAR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    struct bilinear_result_transpose_t {};

    template <typename res_dim_t>
    constexpr auto bilinear_result_transpose([[maybe_unused]] res_dim_t res_dim)
    {
        if constexpr (meta::is_maybe_v<res_dim_t>) {
            using result_t = decltype(bilinear_result_transpose(unwrap(res_dim)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(res_dim)
                ? return_t{bilinear_result_transpose(unwrap(res_dim))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<bilinear_result_transpose_t,res_dim_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(res_dim);
                }

                for (nm_size_t i=0; i<(nm_size_t)res_dim; i++) {
                    at(result,i) = i;
                }

                if (res_dim >= 2) {
                    auto tmp = at(result,-1);
                    at(result,-1) = at(result,-2);
                    at(result,-2) = tmp;
                }
            }

            return result;
        }
    } // bilinear_result_transpose

    struct bilinear_input_reshape_t {};

    template <typename input_shape_t>
    constexpr auto bilinear_input_reshape([[maybe_unused]] const input_shape_t& input_shape)
    {
        if constexpr (meta::is_maybe_v<input_shape_t>) {
            using result_t = decltype(bilinear_input_reshape(unwrap(input_shape)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(input_shape)
                ? return_t{bilinear_input_reshape(unwrap(input_shape))}
                : return_t{meta::Nothing}
            );
        } else {
            using result_t = meta::resolve_optype_t<bilinear_input_reshape_t,input_shape_t>;

            auto result = result_t {};

            if constexpr (!meta::is_fail_v<result_t>
                && !meta::is_constant_index_array_v<result_t>
            ) {
                auto src_dim = len(input_shape);
                auto dst_dim = src_dim > 2 ? src_dim + 1 : src_dim;
                if constexpr (meta::is_resizable_v<result_t>) {
                    result.resize(dst_dim);
                }

                auto extra_dim = dst_dim - src_dim;

                at(result,0) = at(input_shape,0);

                for (nm_size_t i=1; i<(nm_size_t)dst_dim; i++) {
                    at(result,i) = 1;
                }

                for (nm_size_t i=1+extra_dim; i<(nm_size_t)dst_dim; i++) {
                    at(result,i) = at(input_shape,i-extra_dim);
                }
            }

            return result;
        }
    } // bilinear_input_reshape
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct BILINEAR_RESULT_TRANSPOSE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct BILINEAR_INPUT_RESHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename res_dim_t>
    struct resolve_optype<
        void, index::bilinear_result_transpose_t, res_dim_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<res_dim_t>) {
                using type = error::BILINEAR_RESULT_TRANSPOSE_UNSUPPORTED<res_dim_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<res_dim_t>) {
                constexpr auto res_dim = to_value_v<res_dim_t>;
                constexpr auto result = index::bilinear_result_transpose(clipped_size_t<(nm_size_t)res_dim>(res_dim));
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                if constexpr (is_clipped_index_v<res_dim_t>) {
                    constexpr auto max_value = max_value_v<res_dim_t>;
                    using type = nmtools_static_vector<nm_size_t,max_value>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    template <typename input_shape_t>
    struct resolve_optype<
        void, index::bilinear_input_reshape_t, input_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<input_shape_t>) {
                using type = error::BILINEAR_INPUT_RESHAPE_UNSUPPORTED<input_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<input_shape_t>) {
                constexpr auto input_shape = to_value_v<input_shape_t>;
                constexpr auto result = index::bilinear_input_reshape(input_shape);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<input_shape_t>;
                constexpr auto DIM = len_v<input_shape_t>;
                if constexpr (DIM > 0) {
                    constexpr auto DST_DIM = DIM > 2 ? DIM + 1 : DIM;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    constexpr auto DST_B_DIM = B_DIM > 2 ? B_DIM + 1 : B_DIM;
                    using type = nmtools_static_vector<nm_size_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

/*==============================================================================*/

#include "nmtools/array/core/alias.hpp"
#include "nmtools/array/view/matmul.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/transpose.hpp"
#include "nmtools/array/view/sum.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename weight_t, typename bias_t=none_t>
    constexpr auto bilinear(const lhs_t& lhs, const rhs_t& rhs, const weight_t& weight, const bias_t& bias=bias_t{})
    {
        auto aliased = [&](){
            if constexpr (is_none_v<bias_t>) {
                return view::aliased(lhs,rhs,weight);
            } else {
                return view::aliased(lhs,rhs,weight,bias);
            }
        }();

        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);
        auto a_weight = nmtools::get<2>(aliased);

        auto lhs_shape = shape<true>(lhs);
        auto rhs_shape = shape<true>(rhs);

        auto axis = meta::ct_v<-1>;

        auto a = view::matmulv2(
            view::reshape(a_lhs,index::bilinear_input_reshape(lhs_shape))
            , a_weight
        );
        auto b = view::multiply(a,view::reshape(a_rhs,index::bilinear_input_reshape(rhs_shape)));
        auto c = view::sum(b,axis);
        auto d = view::transpose(c,index::bilinear_result_transpose(dim<true>(c)));

        if constexpr (is_none_v<bias_t>) {
            return d;
        } else {
            auto a_bias = nmtools::get<3>(aliased);
            return view::add(d,a_bias);
        }
    } // bilinear
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_BILINEAR_HPP