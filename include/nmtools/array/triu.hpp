#ifndef NMTOOLS_ARRAY_VIEW_TRIU_HPP
#define NMTOOLS_ARRAY_VIEW_TRIU_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct shape_triu_t {};

    template <typename src_shape_t>
    constexpr auto shape_triu([[maybe_unused]] const src_shape_t& src_shape)
    {
        using result_t = meta::resolve_optype_t<shape_triu_t,src_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>
            && !meta::is_fail_v<result_t>
        ) {
            auto src_dim = len(src_shape);

            [[maybe_unused]]
            auto dst_dim = src_dim == 1 ? 2 : src_dim;

            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(dst_dim);
            }

            if (src_dim == 1) {
                at(result,0) = at(src_shape,0);
                at(result,1) = at(src_shape,0);
            } else {
                for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                    at(result,i) = at(src_shape,i);
                }
            }
        }

        return result;
    } // shape_triu

    struct triu_t {};

    template <typename src_shape_t, typename indices_t, typename k_t>
    constexpr auto triu(const src_shape_t& src_shape, const indices_t& indices, k_t k)
    {
        using result_t = meta::resolve_optype_t<triu_t,src_shape_t,indices_t,k_t>;
        using return_t = nmtools_maybe<result_t>;

        auto result = result_t {};

        auto src_dim = len(src_shape);
        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(src_dim);
        }

        if (src_dim > 1) {
            for (nm_size_t i=0; i<(nm_size_t)src_dim; i++) {
                at(result,i) = at(indices,i);
            }
        } else {
            at(result,0) = at(indices,meta::ct_v<-1>);
        }

        nm_index_t index_0 = at(indices,meta::ct_v<-2>);
        nm_index_t index_1 = at(indices,meta::ct_v<-1>);

        if ((nm_index_t)index_0 > nm_index_t(index_1 - k)) {
            return return_t{meta::Nothing};
        } else {
            return return_t{result};
        }
    } // triu
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_TRIU_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct TRIU_UNSUPPORTED : detail::fail_t {};
    }

    template <typename src_shape_t>
    struct resolve_optype<
        void, index::shape_triu_t, src_shape_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<src_shape_t>) {
                using type = error::SHAPE_TRIU_UNSUPPORTED<src_shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<src_shape_t>) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto result = index::shape_triu(src_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(result)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using type   = append_type_t<init_t,ct<at(result,index)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                if constexpr (DIM > 0) {
                    constexpr auto DST_DIM = DIM == 1 ? 2 : DIM;
                    using type = nmtools_array<nm_size_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    constexpr auto DST_B_DIM = B_DIM == 1 ? 2 : B_DIM;
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
    }; // shape_triu_t

    template <typename src_shape_t, typename indices_t, typename k_t>
    struct resolve_optype<
        void, index::triu_t, src_shape_t, indices_t, k_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (
                !is_index_array_v<src_shape_t>
                || !is_index_array_v<indices_t>
                || !is_index_v<k_t>
            ) {
                using type = error::TRIU_UNSUPPORTED<src_shape_t,indices_t,k_t>;
                return as_value_v<type>;
            } else {
                constexpr auto DIM = len_v<src_shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<src_shape_t>;
                using index_t = get_index_element_type_t<indices_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<index_t,DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(B_DIM)>) {
                    using type = nmtools_static_vector<index_t,B_DIM>;
                    return as_value_v<type>;
                } else {
                    // TODO: support small vector
                    using type = nmtools_list<index_t>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

/*=======================================================================*/

#include "nmtools/core/decorator.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/isclose/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename k_t, typename src_size_t>
    struct triu_t
        : base_indexer_t<triu_t<src_shape_t,k_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<src_shape_t>;
        using src_size_type  = meta::fwd_attribute_t<src_size_t>;
 
        using k_type = meta::fwd_attribute_t<k_t>;

        using dst_shape_type = meta::resolve_optype_t<index::shape_triu_t,src_shape_type>;
        using dst_size_type  = decltype(index::product(meta::declval<dst_shape_type>()));

        static constexpr auto n_inputs  = 2;
        static constexpr auto n_outputs = 1;

        const src_shape_type src_shape;
        const k_type k;
        const dst_shape_type dst_shape;
        const src_size_type  src_size;
        const dst_size_type  dst_size;

        constexpr triu_t(const src_shape_t& src_shape
            , k_t k
            , src_size_t src_size
        )
            : src_shape(fwd_attribute(src_shape))
            , k(fwd_attribute(k))
            , dst_shape(index::shape_triu(src_shape))
            , src_size(src_size)
            , dst_size(index::product(dst_shape))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::triu(src_shape,indices,k);
            using src_indices_t = meta::get_maybe_type_t<decltype(src_indices)>;
            // TODO: chane index::triu to return either<indices,None>
            using result_t = nmtools_either<src_indices_t,none_t>;
            if (src_indices) {
                return result_t{unwrap(src_indices)};
            } else {
                return result_t{None};
            }
        }

        template <typename...args_t>
        constexpr auto operator==(triu_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(k,other.k)
            ;
        }
    };

    template <typename src_shape_t, typename k_t, typename src_size_t>
    constexpr auto triu_indexer(const src_shape_t& src_shape, k_t k, src_size_t src_size)
    {
        if constexpr (meta::is_maybe_v<src_shape_t>) {
            using result_t = decltype(triu_indexer(unwrap(src_shape),k,src_size));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (src_shape
                ? return_t{triu_indexer(unwrap(src_shape),k,src_size)}
                : return_t{meta::Nothing}
            );
        } else {
            return triu_t{src_shape,k,unwrap(src_size)};
        }
    } // triu_indexer

    template <typename array_t, typename k_t=nm_size_t>
    constexpr auto triu(const array_t& array, k_t k=k_t{0})
    {
        auto f = [](const auto& array, auto k){
            using element_t = meta::get_element_type_t<meta::remove_cvref_t<decltype(array)>>;
            auto src_shape  = shape<true>(array);
            auto src_size   = size<true>(array);
            auto indexer    = triu_indexer(src_shape,k,src_size);
            auto operands   = pack_operands(array,static_cast<element_t>(0));
            return indexing(operands,indexer);
        };
        return lift_indexing(f,array,k);
    } // triu
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_TRIU_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TRIU_HPP
#define NMTOOLS_ARRAY_ARRAY_TRIU_HPP

#include "nmtools/array/triu.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename k_t=nm_size_t>
    constexpr auto triu(const array_t& array, k_t k=k_t{0}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>
    ) {
        auto a = view::triu(array,k);
        return eval(a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // triu
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TRIU_HPP