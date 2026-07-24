#ifndef NMTOOLS_ARRAY_ITEM_HPP
#define NMTOOLS_ARRAY_ITEM_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/array/flatten.hpp"

namespace nmtools::args
{
    template <typename args_t>
    struct item
    {
        using args_type = args_t;

        args_type args;

        template <typename...other_args_t>
        constexpr auto operator==(const item<other_args_t...>& other) const noexcept
        {
            return utils::isequal(args,other.args);
        }
    };

    template <typename...other_args_t>
    item(other_args_t...) -> item<other_args_t...>;
}

namespace nmtools
{
    template <typename args_t, auto max_dim>
    struct as_static_t<
        args::item<args_t>, max_dim
    > {
        using attribute_type = args::item<args_t>;

        attribute_type attribute;

        auto operator()() const
        {
            auto args = as_static<max_dim>(attribute.args);
            // TODO: handle errors
            return args::item{args};
        }
    };
}

namespace nmtools::meta
{
    // TODO: make this automatically detected by providing base class (similar to fail_t)
    template <typename args_t>
    struct is_attribute<args::item<args_t>> : true_type {};
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename args_t, auto...fmt_args>
    struct to_string_t<args::item<args_t>,fmt_string_t<fmt_args...>>
    {
        using formatter_type = fmt_string_t<fmt_args...>;
        using result_type = nmtools_string;

        auto operator()(const args::item<args_t>& item) const noexcept
        {
            nmtools_string str;
            str += "{";
            str += ".args=";
            str += to_string(item.args,formatter_type{});
            str += "}";
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename array_t, typename args_t>
    struct item_t
    {
        using operand_type = meta::fwd_operand_t<array_t>;
        using array_type   = operand_type;
        using args_type    = meta::fwd_attribute_t<args_t>;

        using attributes_type = args::item<args_type>;
        
        operand_type array;
        args_type    args;

        constexpr item_t(const array_t& array, const args_t& args)
            : array(fwd_operand(array))
            , args(fwd_attribute(args))
        {}

        constexpr auto operands() const noexcept
        {
            if constexpr (is_tuple_v<array_type>) {
                return array;
            } else {
                return nmtools_tuple<array_type>{array};
            }
        }

        constexpr auto attributes() const noexcept
        {
            return attributes_type{args};
        }

        constexpr auto shape() const noexcept
        {
            return None;
        }

        constexpr auto dim() const noexcept
        {
            return None;
        }

        constexpr auto size() const noexcept
        {
            return ct_v<1>;
        }

        template <typename T, enable_if_t<is_num_v<T> && !is_view_v<T>,int> = 0>
        constexpr operator T() const noexcept
        {
            if constexpr (is_num_v<array_type>) {
                return array;
            } else {
                [[maybe_unused]]
                auto flat = [&](){
                    if constexpr (is_num_v<array_type>) {
                        return array;
                    } else if constexpr (is_pointer_v<array_type>) {
                        auto flat = unwrap(view::flatten(*array));
                        return flat;
                    } else {
                        auto flat = unwrap(view::flatten(array));
                        return flat;
                    }
                }();
                if constexpr (is_none_v<args_type>) {
                    return static_cast<T>(at(flat,ct_v<0>));
                } else if constexpr (is_index_v<args_type>) {
                    return static_cast<T>(at(flat,args));
                } else {
                    if constexpr (is_pointer_v<array_type>) {
                        return static_cast<T>(apply_at(*array,args));
                    } else {
                        return static_cast<T>(apply_at(array,args));
                    }
                }
            }
        }
    };

    template <typename array_t, typename args_t=none_t>
    constexpr auto item(const array_t& array, const args_t& args=args_t{})
    {
        if constexpr (is_maybe_v<array_t> || is_maybe_v<args_t>) {
            using result_t = decltype(item(unwrap(array),unwrap(args)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(array) && has_value(args)
                ? return_t{item(unwrap(array),unwrap(args))}
                : return_t{Nothing}
            );
            // TODO: handle is_either_v
        } if constexpr (is_either_v<array_t>) {
            using left_t   = decltype(item(*get_left(&array),args));
            using right_t  = decltype(item(*get_right(&array),args));
            // assume not nested
            using return_t = conditional_t<!is_same_v<left_t,right_t>,nmtools_either<left_t,right_t>,left_t>;
            if (auto l_ptr = get_left(&array)) {
                return return_t{item(*l_ptr,args)};
            } else {
                auto r_ptr = get_right(&array);
                return return_t{item(*r_ptr,args)};
            }
        } else {
            // make sure array size is one
            auto size = nmtools::size<true>(array);
            auto dim  = nmtools::dim<true>(array);
            using result_t = decorator_t<item_t,array_t,args_t>;
            using return_t [[maybe_unused]] = nmtools_maybe<result_t>;
            auto n = [&](){
                if constexpr (is_none_v<args_t> || is_index_v<args_t>) {
                    return dim;
                } else if constexpr (len_v<args_t> > 0) {
                    return ct_v<len_v<args_t>>;
                } else {
                    return len(args);
                }
            }();
            auto idx = [&](){
                if constexpr (is_none_v<args_t>) {
                    return ct_v<0>;
                } else if constexpr (is_index_v<args_t>) {
                    return args;
                } else /* if constexpr (is_index_array_v<args_t>) */ {
                    // TODO: infer validation at compile time
                    using result_t = nm_size_t;
                    using return_t = nmtools_maybe<result_t>;
                    if (n != dim) {
                        return return_t{Nothing};
                    } else {
                        auto shape = nmtools::shape<true>(array);
                        auto strides = index::compute_strides(shape);
                        return return_t{index::compute_offset(args,strides)};
                    }
                }
            }();
            if constexpr (is_constant_index_v<decltype(size)>
                && is_constant_index_v<decltype(idx)>
                && is_constant_index_v<decltype(dim)>
                && is_constant_index_v<decltype(n)>
            ) {
                constexpr auto SIZE = decltype(size)::value;
                constexpr auto IDX  = decltype(idx)::value;
                constexpr auto DIM  = decltype(dim)::value;
                constexpr auto N    = decltype(n)::value;
                static_assert( IDX < SIZE, "invalid size or args for item" );
                static_assert( N == DIM, "invalid number of dims for item" );
                return result_t{{array,args}};
            } else if (!has_value(idx)) {
                return return_t{Nothing};
            } else if (((nm_size_t)n == (nm_size_t)dim)
                && ((nm_size_t)unwrap(idx) < (nm_size_t)size)
            ) {
                return return_t{result_t{{array,args}}};
            } else {
                return return_t{Nothing};
            }
        }
    }
}

namespace nmtools::meta
{
    template <typename array_t, typename args_t>
    struct is_ndarray<
        view::decorator_t< view::item_t, array_t, args_t >
    > : false_type {};

    template <typename array_t, typename args_t>
    struct is_num<
        view::decorator_t< view::item_t, array_t, args_t >
    > : true_type {};

    template <typename array_t, typename args_t>
    struct get_element_type<
        view::decorator_t< view::item_t, array_t, args_t >
    > : get_element_type<array_t> {};
}

namespace nmtools::functional
{
    namespace fun
    {
        struct item_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::item(args...);
            }
        };
    }

    constexpr inline auto item = functor_t{unary_fmap_t<fun::item_t>{}};

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<view::item_t,args_t...>
    > {
        using view_type = view::decorator_t<view::item_t,args_t...>;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return item;
        }
    };
}

#endif // NMTOOLS_ARRAY_ITEM_HPP