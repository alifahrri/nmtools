#ifndef NMTOOLS_ARRAY_INDEX_UFUNC_HPP
#define NMTOOLS_ARRAY_INDEX_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    struct shape_ufunc_t {};

    template <typename shape_t, typename...shapes_t>
    constexpr auto shape_ufunc(const shape_t& shape, const shapes_t&...shapes)
    {
        using result_t = meta::resolve_optype_t<shape_ufunc_t,shape_t,shapes_t...>;
        using return_t = nmtools_maybe<result_t>;

        using shapes_type = nmtools_tuple<const shapes_t&...>;
        auto shapes_tuple = shapes_type{shapes...};

        auto valid = true;
        meta::template_for<sizeof...(shapes)>([&](auto index){
            const auto shape_I = at(shapes_tuple,index);
            if (len(shape) != len(shape_I)) {
                valid = false;
                return;
            } else {
                for (size_t i=0; i<(size_t)len(shape_I); i++) {
                    if (at(shape,i) != at(shape_I,i)) {
                        valid = false;
                        return;
                    }
                }
            }
        });

        if (!valid) {
            return return_t{result_t{}};
        }

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            if constexpr (meta::is_resizable_v<result_t>) {
                result.resize(len(shape));
            }
            if constexpr (meta::is_tuple_v<result_t>) {
                constexpr auto N = meta::len_v<result_t>;
                meta::template_for<N>([&](auto i){
                    at(result,i) = at(shape,i);
                });
            } else {
                for (size_t i=0; i<(size_t)len(shape); i++) {
                    at(result,i) = at(shape,i);
                }
            }
        }

        return return_t{result};
    } // shape_ufunc

    struct size_ufunc_t {};

    template <typename dst_shape_t, typename a_size_t, typename...sizes_t>
    constexpr auto size_ufunc(const dst_shape_t& dst_shape, [[maybe_unused]] a_size_t a_size, sizes_t...)
    {
        using result_t = meta::resolve_optype_t<size_ufunc_t,dst_shape_t,a_size_t,sizes_t...>;
        if constexpr (meta::is_maybe_v<result_t>) {
            // assume a_size is maybe type when result_t is maybe
            // TODO: handle other sizes & dst_shape
            if (static_cast<bool>(a_size)) {
                auto res = product(unwrap(dst_shape));
                return result_t{res};
            } else {
                return result_t{meta::Nothing};
            }
        } else {
            auto res = result_t {};

            if constexpr (!meta::is_constant_index_v<result_t>) {
                res = product(dst_shape);
            }

            return res;
        }
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_UFUNC_UNSUPPORTED : detail::fail_t {};

        template <typename...>
        struct SIZE_UFUNC_UNSUPPORTED : detail::fail_t {};
    }

    template <typename...shapes_t>
    struct resolve_optype<
        void, index::shape_ufunc_t, shapes_t...
    >
    {
        using shapes_type = type_list<shapes_t...>;

        static constexpr auto vtype = [](){
            if constexpr ((is_index_array_v<shapes_t> && ...)) {
                return template_reduce<sizeof...(shapes_t)-1>([](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using i_type_t [[maybe_unused]] = at_t<shapes_type,index + 1>;
                    if constexpr (is_constant_index_array_v<init_type>) {
                        return init;
                    } else if constexpr (is_constant_index_array_v<i_type_t>) {
                        return as_value_v<i_type_t>;
                    } else if constexpr (is_fixed_size_v<init_type>) {
                        return init;
                    } else if constexpr (is_fixed_size_v<i_type_t>) {
                        return as_value_v<i_type_t>;
                    } else if constexpr (is_bounded_size_v<init_type>) {
                        return init;
                    } else if constexpr (is_bounded_size_v<i_type_t>) {
                        return as_value_v<i_type_t>;
                    } else {
                        return init;
                    }
                }, as_value_v<at_t<shapes_type,0>>);
            } else {
                using type = error::SHAPE_UFUNC_UNSUPPORTED<shapes_t...>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // shape_ufunc_t

    template <typename dst_shape_t, typename a_size_t, typename...sizes_t>
    struct resolve_optype<
        void, index::size_ufunc_t, dst_shape_t, a_size_t, sizes_t...
    >
    {
        using size_types = type_list<sizes_t...>;

        static constexpr auto vtype = [](){
            if constexpr (is_maybe_v<a_size_t>) {
                using size_type = get_maybe_type_t<a_size_t>;
                using result_type = nmtools_maybe<size_type>;
                // TODO: consider deduction from dst_shape and other sizes
                return as_value_v<result_type>;
            } else if constexpr (is_index_array_v<dst_shape_t> && is_index_v<a_size_t> && (is_index_v<sizes_t> && ...)) {
                [[maybe_unused]] constexpr auto c_dst_shape = to_value_v<dst_shape_t>;
                if constexpr (is_constant_index_array_v<dst_shape_t>) {
                    constexpr auto numel = (size_t)index::product(c_dst_shape);
                    using type = ct<numel>;
                    return as_value_v<type>;   
                } else if constexpr (is_clipped_index_array_v<dst_shape_t>) {
                    constexpr auto numel = (size_t)index::product(c_dst_shape);
                    using type = clipped_size_t<numel>;
                    return as_value_v<type>;
                } else {
                    auto init_vtype = [](){
                        if constexpr (is_constant_index_v<a_size_t>) {
                            using type = ct<a_size_t::value>;
                            return as_value_v<type>;
                        } else if constexpr (is_clipped_integer_v<a_size_t>) {
                            using type = clipped_size_t<a_size_t::max>;
                            return as_value_v<type>;
                        } else {
                            return as_value_v<a_size_t>;
                        }
                    }();
                    return template_reduce<sizeof...(sizes_t)>([](auto init, auto index){
                        using init_t = type_t<decltype(init)>;
                        constexpr auto I = decltype(index)::value;
                        using type_i = at_t<size_types,I>;
                        if constexpr (is_none_v<init_t>) {
                            return as_value_v<type_i>;
                        } else if constexpr (is_none_v<type_i>) {
                            return init;
                        } else {
                            using type = promote_index_t<init_t,type_i>;
                            return as_value_v<type>;
                        }
                    }, init_vtype);
                }
            } else {
                using type = error::SIZE_UFUNC_UNSUPPORTED<dst_shape_t,a_size_t,sizes_t...>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_UFUNC_HPP