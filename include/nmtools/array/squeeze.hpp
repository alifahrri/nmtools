#ifndef NMTOOLS_ARRAY_SQUEEZE_HPP
#define NMTOOLS_ARRAY_SQUEEZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/utility/shape.hpp"

/*************************************************************************** */

namespace nmtools::index
{
    struct shape_squeeze_t {};

    template <typename shape_t>
    constexpr auto shape_squeeze(const shape_t& shape)
    {
        using result_t = resolve_optype_t<shape_squeeze_t,shape_t>;

        auto result = result_t {};

        if constexpr (!is_constant_index_array_v<result_t>) {
            if constexpr (is_resizable_v<result_t>) {
                auto non_single_count = 0;
                for (size_t i=0; i<(size_t)len(shape); i++) {
                    if (at(shape,i)>1) {
                        non_single_count++;
                    }
                }
                result.resize(non_single_count);
            }
            if constexpr (is_tuple_v<result_t>) {
                constexpr auto DIM = len_v<result_t>;
                auto offset = 0ul;
                template_for<DIM>([&](auto index){
                    auto s_i = 0ul;
                    for (size_t i=index; i<len(shape); i++) {
                        s_i = at(shape,index+offset);
                        if (s_i != 1ul) {
                            break;
                        } else {
                            offset++;
                        }
                    }
                    at(result,index) = s_i;
                });
            } else {
                auto r_i = 0;
                for (size_t i=0; i<(size_t)len(shape); i++) {
                    if (at(shape,i)!=1) {
                        at(result,r_i++) = at(shape,i);
                    }
                }
            }
        }

        return result;
    }
} // nmtools::index

/*************************************************************************** */

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_SQUEEZE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t>
    struct resolve_optype<
        void, index::shape_squeeze_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                is_constant_index_array_v<shape_t>
                || is_clipped_index_array_v<shape_t>
            ) {
                constexpr auto src_shape = to_value_v<shape_t>;
                constexpr auto dst_shape = index::shape_squeeze(src_shape);
                using nmtools::len, nmtools::at;
                return template_reduce<len(dst_shape)>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = at(dst_shape,index);
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        using type   = append_type_t<init_t,ct<I>>;
                        return as_value_v<type>;
                    } else {
                        using type   = append_type_t<init_t,clipped_size_t<I>>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_index_array_v<shape_t>) {
                constexpr auto N = [](){
                    constexpr auto bound = bounded_size_v<shape_t>;
                    if constexpr (!is_fail_v<decltype(bound)>) {
                        return bound;
                    } else {
                        constexpr auto fixed = len_v<shape_t>;
                        return fixed; // maybe 0
                    }
                }();
                // TODO: try to resize & replace element type
                if constexpr (N>0) {
                    using type = nmtools_static_vector<size_t,N>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<size_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::SHAPE_SQUEEZE_UNSUPPORTED<shape_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

/*************************************************************************** */

namespace nmtools::view
{
    /**
     * @brief remove single dimensional entry from array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto squeeze(const array_t& array)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_squeeze(src_shape);
        return view::reshape(array,dst_shape);
    } // squeeze
} // namespace nmtools::view

/*************************************************************************** */

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct squeeze_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::squeeze(args...);
            }
        };
    }

    constexpr inline auto squeeze = functor_t{unary_fmap_t<fun::squeeze_t>{}};
} // namespace nmtools::functional

/*************************************************************************** */

#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly squeeze an arrray. Removes single dimensions from the array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=default_context_t<>,
        typename array_t>
    constexpr auto squeeze(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto squeezed = view::squeeze(array);
        return eval(squeezed
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // reshape
} // namespace nmtools

/*************************************************************************** */

#endif // NMTOOLS_ARRAY_SQUEEZE_HPP