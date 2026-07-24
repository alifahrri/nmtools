#ifndef NMTOOLS_ARRAY_UNSQUEEZE_HPP
#define NMTOOLS_ARRAY_UNSQUEEZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/eval.hpp"
#include "nmtools/core/functor.hpp"

/*************************************************************************** */

namespace nmtools::index
{
    struct shape_unsqueeze_t {};

    template <typename shape_t, typename axis_t>
    constexpr auto shape_unsqueeze([[maybe_unused]] const shape_t& shape, [[maybe_unused]] const axis_t axis)
    {
        using result_t = resolve_optype_t<shape_unsqueeze_t,shape_t,axis_t>;

        auto result = result_t {};

        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_array_v<result_t>
        ) {
            [[maybe_unused]]
            auto src_dim = len(shape);
            if constexpr (is_resizable_v<result_t>) {
                result.resize(src_dim+1);
            }

            constexpr auto DIM = len_v<result_t>;
            if constexpr (DIM > 0) {
                template_reduce<DIM>([&](auto shape_i, auto i){
                    if constexpr (!is_constant_index_v<decltype(at(result,i))>) {
                        if constexpr (!is_constant_index_v<axis_t>) {
                            if (i == axis) {
                                at(result,i) = 1;
                            } else {
                                if (has_value(at(shape,shape_i))) {
                                    at(result,i) = at(shape,shape_i);
                                }
                            }
                        } else {
                            if constexpr (decltype(i)::value == axis_t::value) {
                                at(result,i) = 1;
                            } else {
                                if (has_value(at(shape,shape_i))) {
                                    at(result,i) = at(shape,shape_i);
                                }
                            }
                        }
                    }
                    if constexpr (!is_constant_index_v<axis_t>) {
                        if (i == axis) {
                            return (nm_size_t)shape_i;
                        } else {
                            return (nm_size_t)shape_i + 1;
                        }
                    } else {
                        if constexpr (decltype(i)::value == axis_t::value) {
                            return shape_i;
                        } else {
                            return shape_i + ct_v<1>;
                        }
                    }
                }, ct_v<0>);
            } else {
                auto dim = len(result);
                auto shape_i = 0;
                for (nm_size_t i=0; i<(nm_size_t)dim; i++) {
                    if (i == (nm_size_t)axis) {
                        at(result,i) = 1;
                    } else {
                        if (has_value(at(shape,shape_i))) {
                            at(result,i) = at(shape,shape_i);
                        }
                        shape_i = shape_i + 1;
                    }
                }
            }
        }

        return result;
    }
}

/*************************************************************************** */

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_UNSQUEEZE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_unsqueeze_t, shape_t, axis_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_array_v<shape_t>
                && !is_index_v<axis_t>
            ) {
                using type = error::SHAPE_UNSQUEEZE_UNSUPPORTED<shape_t,axis_t>;
                return as_value_v<type>;
            } else if constexpr (
                (is_constant_index_array_v<shape_t> || is_mixed_index_array_v<shape_t> || is_clipped_index_array_v<shape_t>)
                && is_constant_index_v<axis_t>
            ) {
                constexpr auto shape  = to_value_v<shape_t>;
                constexpr auto axis   = axis_t{};
                constexpr auto result = index::shape_unsqueeze(shape,axis);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = decltype(index)::value;
                    if constexpr (!has_value(at(result,I))) {
                        using type = append_type_t<init_t,nm_size_t>;
                        return as_value_v<type>;
                    } else if constexpr (is_clipped_index_array_v<shape_t>) {
                        using type = append_type_t<init_t,clipped_size_t<at(result,I)>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,ct<(nm_size_t)at(result,I)>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<shape_t>;
                [[maybe_unused]]
                constexpr auto MAX_DIM = max_len_v<shape_t>;

                using index_t = conditional_t<is_nullable_index_array_v<shape_t>
                    , null_size_t
                    , nm_size_t
                >;

                if constexpr (DIM > 0) {
                    using type = nmtools_array<index_t,DIM+1>;
                    return as_value_v<type>;
                } else if constexpr (MAX_DIM > 0) {
                    using type = nmtools_static_vector<index_t,MAX_DIM+1>;
                    return as_value_v<type>;
                } else {
                    // TODO: use small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

/*************************************************************************** */

namespace nmtools::view
{
    template <typename array_t, typename axis_t>
    constexpr auto unsqueeze(const array_t& array, const axis_t axis)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_unsqueeze(src_shape,axis);
        return view::reshape(array,dst_shape);
    }
}

/*************************************************************************** */

// TODO: add functional

/*************************************************************************** */

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=default_context_t<>
        , typename array_t, typename axis_t>
    constexpr auto unsqueeze(const array_t& array, const axis_t axis
        , context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto unsqueezed = view::unsqueeze(array,axis);
        return eval(unsqueezed
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
        );
    }
}

/*************************************************************************** */

#endif // NMTOOLS_ARRAY_UNSQUEEZE_HPP