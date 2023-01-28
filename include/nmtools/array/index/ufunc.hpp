#ifndef NMTOOLS_ARRAY_INDEX_UFUNC_HPP
#define NMTOOLS_ARRAY_INDEX_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/shape.hpp"

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
    }
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_UFUNC_UNSUPPORTED : detail::fail_t {};
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
    };
}

#endif // NMTOOLS_ARRAY_INDEX_UFUNC_HPP