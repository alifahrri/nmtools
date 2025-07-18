#ifndef NMTOOLS_ARRAY_VIEW_TRI_HPP
#define NMTOOLS_ARRAY_VIEW_TRI_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct tri_t {};

    template <typename dst_shape_t, typename indices_t, typename k_t>
    constexpr auto tri(const dst_shape_t& dst_shape, const indices_t& indices, k_t k)
    {
        using result_t = meta::resolve_optype_t<tri_t,dst_shape_t,indices_t,k_t>;
        // TODO: change to tagged L/R value instead, support indexing w/ all num
        using return_t = nmtools_maybe<result_t>;

        auto result = result_t {};

        auto src_dim = len(dst_shape);
        if constexpr (meta::is_resizable_v<result_t>) {
            result.resize(src_dim);
        }

        for (nm_size_t i=0; i<src_dim; i++) {
            at(result,i) = at(indices,i);
        }

        nm_index_t index_0 = at(indices,meta::ct_v<-2>);
        nm_index_t index_1 = at(indices,meta::ct_v<-1>);

        if (index_1 <= nm_index_t(index_0 + k)) {
            return return_t{meta::Nothing}; 
        } else {
            return return_t{result};
        }
    } // tri
} // nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TRI_UNSUPPORTED : detail::fail_t {};
    }

    template <typename dst_shape_t, typename indices_t, typename k_t>
    struct resolve_optype<
        void, index::tri_t, dst_shape_t, indices_t, k_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t>
                || !is_index_array_v<dst_shape_t>
                || !is_index_v<k_t>
            ) {
                using type = error::TRI_UNSUPPORTED<dst_shape_t,indices_t,k_t>;
                return as_value_v<type>;
            } else {
                constexpr auto DIM = len_v<indices_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = bounded_size_v<indices_t>;
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
    }; // tri_t
} // nmtools::meta

/*===========================================================================*/

#include "nmtools/core/decorator.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/zeros.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/isclose/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::view
{
    template <typename dst_shape_t, typename k_t>
    struct tri_t
        : base_indexer_t<tri_t<dst_shape_t,k_t>>
    {
        using src_shape_type = none_t;
        using src_size_type  = none_t;
        using dst_shape_type = meta::fwd_attribute_t<dst_shape_t>;
        using dst_size_type  = decltype(index::product(meta::declval<dst_shape_type>()));
        using k_type = meta::fwd_attribute_t<k_t>;

        inline static constexpr auto n_inputs  = 2;
        inline static constexpr auto n_outputs = 1;

        const dst_shape_type dst_shape;
        const k_type k;

        constexpr tri_t(const dst_shape_t& dst_shape
            , k_t k
        )
            : dst_shape(fwd_attribute(dst_shape))
            , k(fwd_attribute(k))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            auto src_indices = index::tri(dst_shape,indices,k);
            using src_indices_t = meta::get_maybe_type_t<decltype(src_indices)>;
            // TODO: change index::tri to return either, or tagged L/R value
            using result_t = nmtools_either<src_indices_t,none_t>;
            if (src_indices) {
                return result_t{unwrap(src_indices)};
            } else {
                return result_t{None};
            }
        }

        template <typename...args_t>
        constexpr auto operator==(tri_t<args_t...> other) const
        {
            return utils::isequal(dst_shape,other.dst_shape)
                && utils::isequal(k,other.k)

            ;
        }
    }; // tri_t

    template <typename n_t, typename m_t=none_t, typename k_t=nm_index_t, typename T=float>
    constexpr auto tri(n_t N, m_t M=m_t{}, k_t k=k_t{0}, dtype_t<T> dtype=dtype_t<T>{})
    {
        auto dst_shape = [&](){
            if constexpr (is_none_v<m_t>) {
                if constexpr (meta::is_constant_index_v<n_t>) {
                    return nmtools_tuple{N,N};
                } else {
                    return nmtools_array{(nm_size_t)N,(nm_size_t)N};
                }
            } else if constexpr (meta::is_constant_index_v<n_t> && meta::is_constant_index_v<m_t>) {
                return nmtools_tuple{N,M};
            } else {
                return nmtools_array{(nm_size_t)N,(nm_size_t)M};
            }
        }();
        auto indexer  = tri_t{dst_shape,k};
        auto operands = pack_operands(view::zeros(dst_shape,dtype),static_cast<T>(1));
        return indexing(operands,indexer);
    } // tri
} // nmtools::view

namespace nmtools
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::tri_t<args_t...>, max_dim
    > {
        using attribute_type = view::tri_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto dst_shape = as_static<max_dim>(attribute.dst_shape);
            auto k = attribute.k;
            return view::tri_t{dst_shape,k};
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::tri_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::tri_t<args_t...>& kwargs) const
        {
            nmtools_string str;
            str += "tri";
            str += "{";
            str += ".dst_shape="; str+= to_string(kwargs.dst_shape,Compact);
            str += ",.k="; str += to_string(kwargs.k,Compact);
            str += "}";
            return str;
        }
    };
}

#endif

#endif // NMTOOLS_ARRAY_VIEW_TRI_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TRI_HPP
#define NMTOOLS_ARRAY_ARRAY_TRI_HPP

#include "nmtools/array/tri.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename n_t, typename m_t=none_t, typename k_t=nm_index_t, typename T=float>
    constexpr auto tri(n_t N, m_t M=m_t{}, k_t k=k_t{0}, dtype_t<T> dtype=dtype_t<T>{}
        , context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::tri(N,M,k,dtype);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // tri
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_TRI_HPP