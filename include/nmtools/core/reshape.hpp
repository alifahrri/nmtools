#ifndef NMTOOLS_ARRAY_VIEW_RESHAPE_HPP
#define NMTOOLS_ARRAY_VIEW_RESHAPE_HPP

#include "nmtools/meta.hpp"

#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/utility/as_static.hpp"

#include "nmtools/index/product.hpp"
#include "nmtools/index/ref.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/index/compute_offset.hpp"
#include "nmtools/index/compute_strides.hpp"

#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/unwrap.hpp"

/*************************************************************************** */

namespace nmtools::index
{
    struct shape_reshape_t {};
    
    template <typename dst_shape_t>
    constexpr auto count_negative_reshape(const dst_shape_t& dst_shape)
    {
        auto minus_1_count = 0;
        auto dst_numel = (size_t)0;
        using index_t = get_index_element_type_t<dst_shape_t>;
        for (size_t i=0; i<(size_t)len(dst_shape); i++) {
            const auto d_i = at(dst_shape,i);
            if (i==0) {
                dst_numel = 1;
            }
            if ((index_t)d_i == index_t(-1)) {
                minus_1_count++;
            } else {
                dst_numel *= (size_t)d_i;
            }
        }
        return nmtools_tuple{minus_1_count,dst_numel};
    }

    /**
     * @brief Compute the resulting shape of reshape op.
     * Following numpy, allow -1 shape value.
     * 
     * @tparam src_shape_t 
     * @tparam dst_shape_t 
     * @param src_shape 
     * @param dst_shape 
     * @return constexpr auto 
     */
    template <typename src_shape_t, typename dst_shape_t>
    constexpr auto shape_reshape(const src_shape_t& src_shape, const dst_shape_t& dst_shape)
    {
        using result_t [[maybe_unused]] = resolve_optype_t<shape_reshape_t,src_shape_t,dst_shape_t>;
        using m_result_t [[maybe_unused]] = get_maybe_type_t<result_t>;

        // TODO: try to provide common function-lifting utility
        if constexpr (is_maybe_v<src_shape_t>) {
            // when src_shape is maybe, then assume the result_t is maybe
            if (static_cast<bool>(src_shape)) {
                auto result = shape_reshape(*src_shape,dst_shape);
                #if 0
                // even if we unwrap the src_shape, the result may be maybe type
                // since dst_shape may be different shape with src
                // because std::optional<std::optional<int>> is actually allowed
                // TODO: support get_if for optional, or add unwrap_if
                if constexpr (is_maybe_v<decltype(result)>) {
                    // assume get_maybe_type_t of result == m_result_t
                    if (static_cast<bool>(result)) {
                        return result_t{*result};
                    } else {
                        return result_t{Nothing};
                    }
                } else {
                    return result_t{result};
                }
                #else
                using return_t = result_t;
                return (has_value(result)
                    ? return_t{unwrap(result)}
                    : return_t{Nothing}
                );
                #endif
            } else {
                return result_t{Nothing};
            }
        } else if constexpr (is_maybe_v<dst_shape_t>) {
            using dst_shape_type = get_maybe_type_t<dst_shape_t>;
            using result_t = resolve_optype_t<shape_reshape_t,src_shape_t,dst_shape_type>;
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (static_cast<bool>(dst_shape)
                ? return_t{shape_reshape(src_shape,*dst_shape)}
                : return_t{Nothing}
            );
        } else if constexpr (is_fail_v<result_t>) {
            // let the caller decides what to do
            return result_t {};
        } else if constexpr (is_constant_index_array_v<m_result_t>) {
            // already computed, but need to validate at runtime.
            // this maybe path is useful to determine constant dst shape, but runtime shape
            // simply make sure the numel is same
            auto src_numel = index::product(src_shape);
            auto dst_numel = index::product(m_result_t{});
            using idx_t = promote_index_t<decltype(src_numel),decltype(dst_numel)>;
            if ((idx_t)src_numel == (idx_t)dst_numel) {
                return result_t{m_result_t{}};
            } else {
                return result_t{Nothing};
            }
        } else if constexpr (is_constant_index_array_v<result_t>) {
            // already computed
            return result_t {};
        } else {
            auto result = result_t {};
            using return_t = nmtools_maybe<result_t>;
            using element_t = get_index_element_type_t<result_t>;
            using index_t = make_signed_t<element_t>; // for comparison

            // number of "-1" in dst_shape
            #if 0
            const auto [minus_1_count, dst_numel] = count_negative_reshape(dst_shape);
            #else
            const auto neg_reshape_count = count_negative_reshape(dst_shape);
            const auto minus_1_count = nmtools::get<0>(neg_reshape_count);
            const auto dst_numel = nmtools::get<1>(neg_reshape_count);
            #endif

            if (minus_1_count > 1) {
                return return_t{Nothing};
            }

            auto src_numel = (size_t)product(src_shape);

            if ((minus_1_count == 0) && (src_numel != dst_numel)) {
                return return_t{Nothing};
            } else if (static_cast<bool>(src_numel % dst_numel)) {
                return return_t{Nothing};
            }

            if constexpr (is_resizable_v<result_t>) {
                result.resize(len(dst_shape));
            }

            auto shape_reshape_impl = [&,dst_numel=dst_numel](auto i){
                auto d_i = at(dst_shape,i);
                if ((index_t)d_i == index_t(-1)) {
                    at(result,i) = src_numel / dst_numel;
                } else {
                    at(result,i) = at(dst_shape,i);
                }
            };
            if constexpr (is_tuple_v<result_t>) {
                constexpr auto N = len_v<result_t>;
                template_for<N>(shape_reshape_impl);
            } else {              
                for (size_t i=0; i<(size_t)len(dst_shape); i++) {
                    shape_reshape_impl(i);
                }
            }

            return return_t{result};
        }
    } // shape_reshape
} // namespace nmtools::index

/*************************************************************************** */

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_RESHAPE_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct SHAPE_RESHAPE_INVALID : detail::fail_t {};
    } // namespace error
    
    template <typename src_shape_t, typename dst_shape_t>
    struct resolve_optype<void, index::shape_reshape_t, src_shape_t, dst_shape_t>
    {
        static constexpr auto vtype = [](){
            if constexpr (is_maybe_v<src_shape_t>) {
                using src_shape_type = remove_cvref_t<get_maybe_type_t<src_shape_t>>;
                using result_type = resolve_optype_t<index::shape_reshape_t, src_shape_type, dst_shape_t>;
                if constexpr (is_maybe_v<result_type>) {
                    return as_value_v<result_type>;
                } else {
                    using type = nmtools_maybe<result_type>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                is_none_v<src_shape_t>
                && is_constant_index_array_v<dst_shape_t>
            ) {
                constexpr auto numel = index::product(to_value_v<dst_shape_t>);
                if constexpr (numel == 1) {
                    using type = dst_shape_t;
                    return as_value_v<type>;
                } else {
                    using type = error::SHAPE_RESHAPE_INVALID<src_shape_t,dst_shape_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                is_constant_index_array_v<src_shape_t>
                && (is_constant_index_array_v<dst_shape_t> || is_clipped_index_array_v<dst_shape_t>)
            ) {
                constexpr auto src_shape = to_value_v<src_shape_t>;
                constexpr auto dst_shape = to_value_v<dst_shape_t>;
                constexpr auto result = index::shape_reshape(src_shape,dst_shape);
                if constexpr (!static_cast<bool>(result) && is_constant_index_array_v<dst_shape_t>) {
                    // only if both are constant index should trigger compile-time error
                    // since clipped shape value may be valid at runtime
                    using type = error::SHAPE_RESHAPE_INVALID<src_shape_t,dst_shape_t,decltype(src_shape),decltype(dst_shape),decltype(result)>;
                    return as_value_v<type>;
                } else if constexpr (!static_cast<bool>(result)) {
                    // to avoid dereference the result
                    // retry without constant_index_array
                    using type = resolve_optype_t<index::shape_reshape_t,decltype(src_shape),dst_shape_t>;
                    return as_value_v<type>;
                } else {
                    constexpr auto res = *result;
                    using nmtools::at, nmtools::len;
                    return template_reduce<len(res)>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        constexpr auto I = at(res,index);
                        if constexpr (is_constant_index_array_v<dst_shape_t>) {
                            return as_value_v<append_type_t<init_type,ct<I>>>;
                        } else {
                            return as_value_v<append_type_t<init_type,clipped_size_t<I>>>;
                        }
                    }, as_value_v<nmtools_tuple<>>);
                }
            } else if constexpr (is_constant_index_array_v<dst_shape_t>) {
                constexpr auto dst_shape = to_value_v<dst_shape_t>;
                constexpr auto all_pos_int = [&](){
                    auto all_pos_int = true;
                    for (const auto& shape_ : dst_shape) {
                        all_pos_int &= (shape_ > 0);
                    }
                    return all_pos_int;
                }();
                if constexpr (!all_pos_int && is_constant_index_array_v<src_shape_t>) {
                    constexpr auto src_shape = to_value_v<src_shape_t>;
                    constexpr auto result = index::shape_reshape(src_shape,dst_shape);
                    // assume maybe type (see above)
                    if constexpr (static_cast<bool>(result)) {
                        constexpr auto DIM = nmtools::len(*result);
                        return template_reduce<DIM>([&](auto init, auto index_){
                            using init_t = type_t<decltype(init)>;
                            if constexpr (is_same_v<init_t,none_t>) {
                                using type = nmtools_tuple<ct<at(*result,index_)>>;
                                return as_value_v<type>;
                            } else {
                                using type = append_type_t<init_t,ct<at(*result,index_)>>;
                                return as_value_v<type>;
                            }
                        }, as_value_v<none_t>);
                    } else {
                        using type = error::SHAPE_RESHAPE_INVALID<src_shape_t,dst_shape_t,decltype(result)>;
                        return as_value_v<type>;
                    }
                } else if constexpr (!all_pos_int) {
                    using m_dst_shape_t = remove_cvref_t<decltype(dst_shape)>;
                    return as_value_v<resolve_optype_t<index::shape_reshape_t,src_shape_t,m_dst_shape_t>>;
                } else if constexpr (is_constant_index_array_v<src_shape_t>) {
                    constexpr auto src_shape = to_value_v<src_shape_t>;
                    constexpr auto src_numel = index::product(src_shape);
                    constexpr auto dst_numel = index::product(dst_shape);
                    if constexpr (src_numel == dst_numel) {
                        return as_value_v<dst_shape_t>;
                    } else {
                        using type = error::SHAPE_RESHAPE_INVALID<src_shape_t,dst_shape_t>;
                        return as_value_v<type>;
                    }
                } else {
                    return as_value_v<nmtools_maybe<dst_shape_t>>;
                }
            } else if constexpr (is_index_array_v<src_shape_t> && is_constant_index_array_v<dst_shape_t>) {
                constexpr auto dst_shape = to_value_v<dst_shape_t>;
                // NOTE: return the runtime type to not confuse the computation (make sure not skip)
                using m_dst_shape_t = remove_cvref_t<decltype(dst_shape)>;
                return as_value_v<resolve_optype_t<index::shape_reshape_t,src_shape_t,m_dst_shape_t>>;
            } else if constexpr (is_index_array_v<src_shape_t> && is_clipped_index_array_v<dst_shape_t>) {
                constexpr auto clipped_min = clipped_min_v<dst_shape_t>;
                constexpr auto clipped_max = clipped_max_v<dst_shape_t>;
                constexpr auto N = len_v<dst_shape_t>;
                constexpr auto dst_shape = [&](){
                    auto dst_shape = nmtools_array<int,N>{};
                    for (nm_index_t i=0; i<(nm_index_t)N; i++) {
                        dst_shape[i] = (clipped_min[i] < 0 ? clipped_min[i] : clipped_max[i]);
                    }
                    return dst_shape;
                }();
                // number of "-1" in dst_shape
                constexpr auto result = index::count_negative_reshape(dst_shape);
                constexpr auto minus_1_count = nmtools::get<0>(result);
                if constexpr (minus_1_count > 1) {
                    return as_value_v<error::SHAPE_RESHAPE_INVALID<src_shape_t,dst_shape_t>>;
                } else {
                    using nmtools::at;
                    constexpr auto negative_shape = nmtools::get<1>(result);
                    return template_reduce<N>([&](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto min = at(clipped_min,index);
                        constexpr auto max = at(clipped_max,index);
                        if constexpr (min < 0) {
                            return as_value_v<append_type_t<init_t,clipped_size_t<negative_shape>>>;
                        } else {
                            return as_value_v<append_type_t<init_t,clipped_size_t<max>>>;
                        }
                    }, as_value_v<nmtools_tuple<>>);
                }
            } else if constexpr (is_index_array_v<src_shape_t> && is_index_array_v<dst_shape_t>) {
                using element_t = get_index_element_type_t<dst_shape_t>;
                constexpr auto DST_DIM = len_v<dst_shape_t>;
                [[maybe_unused]] constexpr auto DST_B_DIM = bounded_size_v<dst_shape_t>;
                if constexpr (DST_DIM > 0) {
                    using type = nmtools_array<element_t,DST_DIM>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(DST_B_DIM)>) {
                    using type = nmtools_static_vector<element_t,DST_B_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::SHAPE_RESHAPE_UNSUPPORTED<src_shape_t,dst_shape_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

} // namespace nmtools::meta

/*************************************************************************** */

namespace nmtools::view
{
    template <typename src_shape_t, typename dst_shape_t, typename src_size_t>
    struct reshape_t
        : base_indexer_t<reshape_t<src_shape_t,dst_shape_t,src_size_t>>
    {
        // TODO: currently there is meta::fwd_attribute_t, and nmtools::fwd_attribute_t, fix
        using src_shape_type = meta::fwd_attribute_t<decltype(unwrap(meta::declval<src_shape_t>()))>;
        using src_size_type  = meta::fwd_attribute_t<decltype(unwrap(meta::declval<src_size_t>()))>;

        // TODO: refactor index::shape_reshape so that the result can be easily deduced
        // using dst_shape_type = resolve_optype_t<
        //     index::shape_reshape_t, src_shape_type, dst_shape_t
        // >;
        // avoid storing maybe type here since it is not constexpr-friendly (at least for maybe static_vector)
        using dst_shape_type   = decltype(unwrap(index::shape_reshape(declval<src_shape_type>(),declval<dst_shape_t>())));
        using dst_strides_type = resolve_optype_t<unwrap_t,resolve_optype_t<
            index::compute_strides_t, dst_shape_type
        >>;
        // reshape doesn't change the number of elements
        using dst_size_type = src_size_type;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type   src_shape;
        const dst_shape_type   dst_shape;
        const src_size_type    src_size;
        const dst_size_type    dst_size;
        const dst_strides_type dst_strides;

        constexpr reshape_t(const src_shape_t& src_shape_
            , const dst_shape_t& dst_shape_
            , src_size_t src_size_
        )
            : src_shape(fwd_attribute(unwrap(src_shape_)))
            , dst_shape(unwrap(index::shape_reshape(src_shape,dst_shape_)))
            , src_size(fwd_attribute(unwrap(src_size_)))
            , dst_size(fwd_attribute(unwrap(src_size_)))
            , dst_strides(unwrap(index::compute_strides(dst_shape)))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            if constexpr (is_none_v<src_shape_type>) {
                return None;
            } else {
                auto dst_offset  = index::compute_offset(indices,unwrap(dst_strides));
                auto src_indices = index::compute_indices(dst_offset,src_shape);
                return unwrap(src_indices);
            }
        }

        template <typename...args_t>
        constexpr auto operator==(reshape_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
            ;
        }
    };

    template <typename src_shape_t, typename dst_shape_t, typename src_size_t>
    constexpr auto reshaper(const src_shape_t& src_shape, const dst_shape_t& dst_shape, const src_size_t& src_size)
    {
        if constexpr (is_maybe_v<src_shape_t> || is_maybe_v<dst_shape_t> || is_maybe_v<src_size_t>) {
            using result_t = decltype(reshaper(unwrap(src_shape),unwrap(dst_shape),unwrap(src_size)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(src_shape) && has_value(dst_shape) && has_value(src_size)
                ? return_t{reshaper(unwrap(src_shape),unwrap(dst_shape),unwrap(src_size))}
                : return_t{Nothing}
            );
        } else {
            auto m_dst_shape = index::shape_reshape(src_shape,dst_shape);
            using result_t = reshape_t<src_shape_t,dst_shape_t,src_size_t>;
            if constexpr (is_maybe_v<decltype(m_dst_shape)>) {
                using return_t = nmtools_maybe<result_t>;
                return (has_value(m_dst_shape)
                    ? return_t{result_t{src_shape,dst_shape,src_size}}
                    : return_t{Nothing}
                );
            } else {
                return result_t{src_shape,dst_shape,src_size};
            }
        }
    }

    template <typename array_t, typename dst_shape_t>
    constexpr auto reshape(const array_t& array, const dst_shape_t& dst_shape)
    {
        auto f = [](const auto& array, const auto& dst_shape){
            auto src_shape = [&](){
                if constexpr (is_pointer_v<array_t>) {
                    return shape<true>(*array);
                } else {
                    return shape<true>(array);
                }
            }();
            auto src_size  = [&](){
                if constexpr (is_pointer_v<array_t>) {
                    return size<true>(*array);
                } else {
                    return size<true>(array);
                }
            }();
            auto indexer = reshaper(src_shape,dst_shape,src_size);
            return indexing(array,indexer);
        };
        return lift_indexing(f,array,dst_shape);
    }

} // namespace nmtools::view

/*************************************************************************** */

namespace nmtools
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::reshape_t<args_t...>, max_dim
    > {
        using attribute_type = view::reshape_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto dst_shape = as_static<max_dim>(attribute.dst_shape);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::reshaper(src_shape,dst_shape,src_size);
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::reshape_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::reshape_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "reshape";
            str += "{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ",.dst_shape=";
            str += to_string(kwargs.dst_shape,Compact);
            str += ",.src_size=";
            str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

/*************************************************************************** */

#endif // NMTOOLS_ARRAY_VIEW_RESHAPE_HPP