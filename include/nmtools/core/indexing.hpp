#ifndef NMTOOLS_ARRAY_VIEW_INDEXING_HPP
#define NMTOOLS_ARRAY_VIEW_INDEXING_HPP

#include "nmtools/meta.hpp"
#include "nmtools/index/product.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/as_static.hpp"

namespace nmtools::args
{
    template <typename indexer_t>
    struct indexing
    {
        using indexer_type = indexer_t;

        indexer_type indexer;

        template <typename...args_t>
        constexpr auto operator==(const indexing<args_t...>& other) const
        {
            return indexer == other.indexer;
        }
    }; // indexing

    template <typename...args_t>
    indexing(args_t...) -> indexing<args_t...>;
} // namespace nmtools::args

namespace nmtools
{
    template <typename indexer_t, auto max_dim>
    struct as_static_t<
        args::indexing<indexer_t>, max_dim
    > {
        using attribute_type = args::indexing<indexer_t>;

        attribute_type attribute;

        auto operator()() const
        {
            auto indexer = as_static<max_dim>(attribute.indexer);
            // TODO: handle errors
            return args::indexing{indexer};
        }
    };
}

namespace nmtools::meta
{
    template <typename indexer_t>
    struct is_attribute<args::indexing<indexer_t>> : true_type {};
} // namespace nmtools::meta

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename indexer_t, auto...fmt_args>
    struct to_string_t<args::indexing<indexer_t>,fmt_string_t<fmt_args...>>
    {
        using formatter_type = fmt_string_t<fmt_args...>;
        using result_type = nmtools_string;
        auto operator()(const args::indexing<indexer_t>& indexing) const noexcept
        {
            nmtools_string str;
            str += "{";
            str += ".indexer=";

            nmtools_string indexer_str;
            indexer_str = NMTOOLS_TYPENAME_TO_STRING(indexer_t);
            using str_mapper_t = to_string_t<indexer_t,formatter_type>;
            if constexpr (meta::has_result_type_v<str_mapper_t>) {
                if constexpr (!meta::is_fail_v<typename str_mapper_t::result_type>) {
                    indexer_str = to_string(indexing.indexer,formatter_type{});
                }
            }
            str += indexer_str;
            str += "}";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

/*===============================================================================*/

namespace nmtools::view
{
    template <typename indexer_t>
    struct base_indexer_t
    {
        constexpr indexer_t* self()
        {
            return static_cast<indexer_t*>(this);
        }

        constexpr const indexer_t* self() const
        {
            return static_cast<const indexer_t*>(this);
        }

        constexpr auto shape() const
        {
            return unwrap(self()->dst_shape);
        }

        constexpr auto dim() const
        {
            return len(shape());
        }

        constexpr auto size() const
        {
            // prefer dst_size since it may be fixed/bounded size
            using self_type = decltype(*self());
            if constexpr (meta::has_dst_size_v<self_type>) {
                return self()->dst_size;
            } else {
                return index::product(shape());
            }
        }

        constexpr operator bool() const noexcept
        {
            using dst_shape_type = decltype(self()->dst_shape);
            if constexpr (meta::is_maybe_v<dst_shape_type>) {
                return static_cast<bool>(self()->dst_shape);
            } else {
                return true;
            }
        }
    }; // base_indexer_t

    template <typename indices_t>
    struct tagged_indices_t
    {
        enum Tag {LEFT, RIGHT};

        Tag tag;
        indices_t indices;

        constexpr tagged_indices_t(Tag tag, const indices_t& indices)
            : tag(tag)
            , indices(indices)
        {}
    };

    template <typename T>
    struct is_tagged_indices : meta::false_type {};

    template <typename T>
    struct is_tagged_indices<tagged_indices_t<T>> : meta::true_type {};

    template <typename T>
    constexpr inline auto is_tagged_indices_v = is_tagged_indices<T>::value;

    template <typename T>
    struct is_tagged_indices<const T> : is_tagged_indices<T> {};

    template <typename T>
    struct is_tagged_indices<T&> : is_tagged_indices<T> {};

    template <typename array_t, typename indexer_t>
    struct indexing_t
    {
        using operand_type = meta::fwd_operand_t<array_t>;
        using array_type   = operand_type;
        using indexer_type = indexer_t;
        using dst_shape_type = typename indexer_type::dst_shape_type;
        using src_shape_type = typename indexer_type::src_shape_type;

        // when shape maybe non-fixed, but size may be fixed, depending on the indexer kind
        using dst_size_type = decltype(meta::declval<indexer_t>().size());

        using attributes_type = args::indexing<indexer_type>;

        operand_type array;
        indexer_type indexer;

        constexpr indexing_t(const array_t& array, const indexer_t& indexer)
            : array(fwd_operand(array))
            , indexer(indexer)
        {}

        #if 0
        nmtools_func_attribute
        ~indexing_t() = default;
        #endif

        constexpr auto operands() const noexcept
        {
            if constexpr (meta::is_tuple_v<array_type>) {
                return array;
            } else {
                return nmtools_tuple<array_type>{array};
            }
        } // operands

        constexpr auto attributes() const noexcept
        {
            return attributes_type{indexer};
        }

        constexpr auto shape() const
        {
            return indexer.shape();
        }

        constexpr auto dim() const
        {
            return indexer.dim();
        }

        constexpr auto size() const
        {
            return indexer.size();
        }

        template <typename m_array_type, typename indices_type>
        static constexpr auto get_element(const m_array_type& array, [[maybe_unused]] const indices_type& indices)
        {
            if constexpr (meta::is_pointer_v<m_array_type>) {
                return apply_at(*array,indices);
            } else if constexpr (is_none_v<indices_type>) {
                static_assert( meta::is_num_v<m_array_type>
                    , "invalid source array for indexing view" );
                return array;
            } else {
                return apply_at(array,indices);
            }
        }

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto dst_indices = pack_indices(indices...);
            auto src_indices = indexer.indices(dst_indices);

            using src_indices_type   = decltype(src_indices);
            using nocvptr_array_type = meta::remove_cvref_pointer_t<array_type>;
            static_assert(
                (meta::is_index_array_v<src_indices_type> && meta::is_ndarray_v<nocvptr_array_type>)
                || (meta::is_tuple_v<nocvptr_array_type> && meta::is_either_v<src_indices_type>)
                || (is_none_v<src_indices_type> && meta::is_num_v<array_type>)
                || (meta::is_tuple_v<nocvptr_array_type> && is_tagged_indices_v<src_indices_type>)
            );

            using element_t [[maybe_unused]] = meta::get_element_type_t<view::decorator_t<indexing_t,array_t,indexer_t>>;

            if constexpr (meta::is_tuple_v<nocvptr_array_type> && meta::is_either_v<src_indices_type>) {
                using left_t  = meta::get_either_left_t<src_indices_type>;
                using right_t = meta::get_either_right_t<src_indices_type>;
                static_assert( meta::len_v<nocvptr_array_type> == 2 );
                if (auto l_ptr = nmtools::get_if<left_t>(&src_indices)) {
                    const auto& left = nmtools::get<0>(array);
                    return static_cast<element_t>(get_element(left,*l_ptr));
                } else {
                    auto r_ptr = nmtools::get_if<right_t>(&src_indices);
                    const auto& right = nmtools::get<1>(array);
                    return static_cast<element_t>(get_element(right,*r_ptr));
                }
            } else if constexpr (meta::is_tuple_v<nocvptr_array_type> && is_tagged_indices_v<src_indices_type>) {
                if (src_indices.tag == decltype(src_indices)::Tag::LEFT) {
                    const auto& left = nmtools::get<0>(array);
                    return static_cast<element_t>(get_element(left,src_indices.indices));
                } else {
                    const auto& right = nmtools::get<1>(array);
                    return static_cast<element_t>(get_element(right,src_indices.indices));
                }
            } else {
                return get_element(array,src_indices);
            }
        }

        template <typename T, meta::enable_if_t<meta::is_num_v<T> && meta::is_num_v<array_t> && is_none_v<decltype(indexer.shape())>,int> =0>
        constexpr operator T() const noexcept
        {
            return static_cast<T>(array);
        }
    }; // indexing_t

    template <typename array_t, typename indexer_t>
    constexpr auto indexing(const array_t& array, const indexer_t& indexer)
    {
        if constexpr (meta::is_fail_v<indexer_t>) {
            return indexer;
        // TODO: simplify with this version, fix segfault
        #if 0
        } else if constexpr (meta::is_maybe_v<array_t> || meta::is_maybe_v<indexer_t>) {
            using result_t = decltype(indexing(unwrap(array),unwrap(indexer)));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return ((has_value(array) && has_value(indexer))
                ? return_t{indexing(unwrap(array),unwrap(indexer))}
                : return_t{meta::Nothing}
            );
        #else
        } else if constexpr (meta::is_maybe_v<array_t>) {
            using array_type = meta::get_maybe_type_t<array_t>;
            using result_t = decltype(indexing(meta::declval<array_type>(),indexer));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (array
                ? return_t{indexing(unwrap(array),indexer)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<indexer_t>) {
            using indexer_type = meta::get_maybe_type_t<indexer_t>;
            using result_t = decltype(indexing(array,meta::declval<indexer_type>()));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            static_assert( !meta::is_maybe_v<typename indexer_type::dst_shape_type> );
            return (indexer ? return_t{indexing(array,*indexer)}
                : return_t{meta::Nothing}
            );
        #endif
        } else if constexpr (meta::is_maybe_v<typename indexer_t::dst_shape_type>) {
            using view_type = decorator_t<indexing_t,array_t,indexer_t>;
            using result_t  = nmtools_maybe<view_type>;
            // TODO: remove, invalid indexer configuration handled by returning maybe(indexer)
            return (indexer ? result_t{view_type{{array,indexer}}}
                : result_t{meta::Nothing}
            );
        } else {
            using result_t = decorator_t<indexing_t,array_t,indexer_t>;
            return result_t{{array,indexer}};
        }
    } // indexing

    template <typename array_t, typename indexer_t>
    constexpr auto indexing(const array_t& array, const args::indexing<indexer_t>& kwargs)
    {
        return indexing(array,kwargs.indexer);
    }

    template <typename F, typename array_t, typename...args_t>
    constexpr auto lift_indexing(F&& f, const array_t& array, const args_t&...args)
    {
        // TODO: simplify with this version, fix segfault
        #if 0
        if constexpr (meta::is_maybe_v<array_t> || (meta::is_maybe_v<args_t> || ...)) {
            using result_t   = decltype(f(unwrap(array),unwrap(args)...));
            // f(...) may results in maybe type (e.g. because of invalid args.. configuration)
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(array) && (has_value(args) && ...)
                ? return_t{f(unwrap(array),unwrap(args)...)}
                : return_t{meta::Nothing}
            );
        #else
        if constexpr (meta::is_maybe_v<array_t>) {
            using array_type = meta::get_maybe_type_t<array_t>;
            using result_t   = decltype(f(meta::declval<array_type>(),args...));
            // f(...) may results in maybe type (e.g. because of invalid args.. configuration)
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            if (static_cast<bool>(array)) {
                auto result = f(*array,args...);
                if constexpr (meta::is_maybe_v<result_t>) {
                    return (result ? return_t{*result}
                        : return_t{meta::Nothing}
                    );
                } else {
                    return return_t{result};
                }
            } else {
                return return_t{meta::Nothing};
            }
        #endif
        } else if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using left_res_t  = decltype(f(meta::declval<left_t>(),args...));
            using right_res_t = decltype(f(meta::declval<right_t>(),args...));
            using result_t = meta::replace_either_t<array_t,left_res_t,right_res_t>;
            if (auto l_ptr = nmtools::get_if<left_t>(&array)) {
                return result_t{f(*l_ptr,args...)};
            } else {
                auto r_ptr = nmtools::get_if<right_t>(&array);
                return result_t{f(*r_ptr,args...)};
            }
        } else {
            return f(array,args...);
        }
    } // lift_indexing

    template <typename F, typename lhs_t, typename rhs_t, typename...args_t>
    constexpr auto lift_binary_indexing(F&& f, const lhs_t& lhs, const rhs_t& rhs, const args_t&...args)
    {
        if constexpr (meta::is_maybe_v<lhs_t> || meta::is_maybe_v<rhs_t>) {
            // TODO: recurse to handle maybe<either<...>>
            using result_t = decltype(f(unwrap(lhs),unwrap(rhs),args...));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(lhs) && has_value(rhs)
                ? return_t{f(unwrap(lhs),unwrap(rhs),args...)}
                : return_t{meta::Nothing}
            );
        }
        // TODO: handle either type
        else {
            return f(lhs,rhs,args...);
        }
    }
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename indexer_t>
    struct is_ndarray<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    > {
        using view_type  = view::decorator_t<view::indexing_t,array_t,indexer_t>;
        using shape_type = decltype(meta::declval<view_type>().shape());

        static constexpr auto value = [](){
            if constexpr (is_tuple_v<array_t>) {
                #if 0
                constexpr auto N = len_v<array_t>;
                return meta::template_reduce<N>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using tuple_element_t = decltype(nmtools::get<I>(meta::declval<array_t>()));
                    using type = remove_cvref_pointer_t<tuple_element_t>;
                    return init && (is_ndarray_v<type> || is_num_v<type>);
                }, is_index_array_v<shape_type>);
                #else
                return is_index_array_v<shape_type>;
                #endif
            } else {
                return is_ndarray_v<array_t> || (is_num_v<array_t> && is_index_array_v<shape_type>);
            }
        }();
    };

    template <typename array_t, typename indexer_t>
    struct is_num<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    > {
        using view_type  = view::decorator_t<view::indexing_t,array_t,indexer_t>;
        using shape_type = decltype(meta::declval<view_type>().shape());

        static constexpr auto value = (is_num_v<array_t> || is_tuple_v<array_t>) && is_none_v<shape_type>;
    };

    template <typename array_t, typename indexer_t>
    struct get_element_type<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    > {
        static constexpr auto vtype = [](){
            if constexpr (is_tuple_v<array_t>) {
                constexpr auto N = len_v<array_t>;
                return template_reduce<N>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    using tuple_element_t = decltype(nmtools::get<I>(meta::declval<array_t>()));
                    using element_t = get_element_type_t<remove_pointer_t<remove_cvref_t<tuple_element_t>>>;

                    using init_t = type_t<decltype(init)>;
                    if constexpr (is_none_v<init_t>) {
                        using type = element_t;
                        return as_value_v<type>;
                    } else {
                        static_assert( !is_ndarray_v<init_t> );
                        using type = common_type_t<init_t,element_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<none_t>);
            } else {
                using type = get_element_type_t<array_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
        static_assert( !is_fail_v<type> );
    };

    template <typename array_t, typename indexer_t>
    struct fixed_shape<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    >{
        using view_type = view::decorator_t<view::indexing_t,array_t,indexer_t>;
        using indexing_type  = view::indexing_t<array_t,indexer_t>;
        using dst_shape_type = typename indexing_type::dst_shape_type;
        using dst_size_type  = typename indexing_type::dst_size_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return to_value_v<dst_shape_type>;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_shape

    template <typename array_t, typename indexer_t>
    struct fixed_size<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    >{
        using view_type = view::decorator_t<view::indexing_t,array_t,indexer_t>;
        using indexing_type  = view::indexing_t<array_t,indexer_t>;
        using dst_shape_type = typename indexing_type::dst_shape_type;
        using dst_size_type  = typename indexing_type::dst_size_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_v<dst_size_type>) {
                return to_value_v<dst_size_type>;
            } else if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(to_value_v<dst_shape_type>);
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    template <typename array_t, typename indexer_t>
    struct bounded_size<
        view::decorator_t<view::indexing_t,array_t,indexer_t>
    >{
        using view_type      = view::decorator_t<view::indexing_t,array_t,indexer_t>;
        using indexing_type  = view::indexing_t<array_t,indexer_t>;
        using dst_shape_type = typename indexing_type::dst_shape_type;
        using dst_size_type  = typename indexing_type::dst_size_type;

        static constexpr auto value = [](){
            constexpr auto fixed_size = fixed_size_v<view_type>;
            if constexpr (!is_fail_v<decltype(fixed_size)>) {
                return fixed_size;
            } else if constexpr (is_clipped_integer_v<dst_size_type> || is_constant_index_v<dst_size_type>) {
                return to_value_v<dst_size_type>;
            } else if constexpr (is_clipped_index_array_v<dst_shape_type>) {
                return index::product(to_value_v<dst_shape_type>);
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // bounded_size
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_INDEXING_HPP