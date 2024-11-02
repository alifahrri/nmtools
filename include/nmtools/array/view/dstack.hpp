#ifndef NMTOOLS_ARRAY_VIEW_DSTACK_HPP
#define NMTOOLS_ARRAY_VIEW_DSTACK_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct dstack_reshape_t {};

    template <typename src_shape_t>
    constexpr auto dstack_reshape(const src_shape_t& src_shape)
    {
        using result_t = meta::resolve_optype_t<dstack_reshape_t,src_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_fail_v<result_t>
            && !meta::is_constant_index_array_v<result_t>)
        {
            auto src_dim = len(src_shape);

            [[maybe_unused]]
            auto dst_dim = src_dim < 3 ? 3 : src_dim;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            if (src_dim == 1) {
                at(result,meta::ct_v<0>) = 1;
                at(result,meta::ct_v<1>) = at(src_shape,meta::ct_v<0>);
                at(result,meta::ct_v<2>) = 1;
            } else if (src_dim == 2) {
                at(result,meta::ct_v<0>) = at(src_shape,meta::ct_v<0>);
                at(result,meta::ct_v<1>) = at(src_shape,1); // avoid triggering static_assert
                at(result,meta::ct_v<2>) = 1;
            } else {
                for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                    at(result,i) = at(src_shape,i);
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
        struct DSTACK_RESHAPE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t>
    struct resolve_optype<
        void, index::dstack_reshape_t, src_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>) {
                using type = error::DSTACK_RESHAPE_UNSUPPORTED<src_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<src_shape_t>) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto result = index::dstack_reshape(src_shape);
                using nmtools::at, nmtools::len;
                return template_reduce<len(result)>([&](auto init, auto I){
                    using init_t = type_t<decltype(init)>;
                    using type = append_type_t<init_t,ct<at(result,I)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                constexpr auto DIM   = len_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<nm_size_t,(DIM < 3 ? 3 : DIM)>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<nm_size_t,(B_DIM < 3 ? 3 : B_DIM)>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<nm_size_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // index::dstack_reshape_t
} // nmtools::meta

#include "nmtools/array/view/alias.hpp"
#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/view/concatenate.hpp"

namespace nmtools::view
{
    template <typename a_t, typename b_t>
    constexpr auto dstack(const a_t& a, const b_t& b)
    {
        auto aliased = view::aliased(a,b);
        auto a_src_shape = shape<true>(a);
        auto a_dst_shape = index::dstack_reshape(a_src_shape);
        auto b_src_shape = shape<true>(b);
        auto b_dst_shape = index::dstack_reshape(b_src_shape);

        auto a_reshaped = view::reshape(nmtools::get<0>(aliased),a_dst_shape);
        auto b_reshaped = view::reshape(nmtools::get<1>(aliased),b_dst_shape);

        auto axis = meta::ct_v<2>;

        return view::concatenate(a_reshaped,b_reshaped,axis);
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_DSTACK_HPP