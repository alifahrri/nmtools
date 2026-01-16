#ifndef NMTOOLS_ARRAY_VIEW_FULL_HPP
#define NMTOOLS_ARRAY_VIEW_FULL_HPP

#include "nmtools/core/decorator.hpp"
#include "nmtools/utility/shape.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    /**
     * @brief view object to represent array with fill_value.
     * 
     * @tparam shape_t 
     * @tparam fill_value_t 
     */
    template <typename shape_t, typename fill_value_t>
    struct full_t
    {
        using shape_type      = resolve_attribute_type_t<shape_t>;
        using fill_value_type = const fill_value_t;
        using element_type    = fill_value_type;
        // TODO: rename array_type to operand_type
        using array_type = nmtools_tuple<>;

        shape_type shape_;
        fill_value_type fill_value;
        // to make get_array works
        array_type array{};

        constexpr full_t(const shape_t& shape, fill_value_type fill_value)
            : shape_(init_attribute<shape_type>(shape))
            , fill_value(fill_value)
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple{};
        }

        constexpr auto attributes() const
        {
            return nmtools_tuple{shape_,fill_value};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape_);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...) const
        {
            // TODO: assert if indices < shape

            return fill_value;
        } // operator()
    }; // full_t

    /**
     * @brief Creates a view that returns specified fill_value with given shape.
     * 
     * @tparam shape_t 
     * @tparam fill_value_t 
     * @param shape 
     * @param fill_value fill value
     * @return constexpr auto 
     */
    template <typename shape_t, typename fill_value_t>
    constexpr auto full(const shape_t& shape, fill_value_t fill_value)
    {
        using view_t = decorator_t<full_t, shape_t, fill_value_t>;
        return view_t{{shape, fill_value}};
    } // full
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename shape_t, typename fill_value_t>
    struct get_element_type< view::decorator_t<view::full_t, shape_t, fill_value_t> >
    {
        using type = fill_value_t;
    };

    template <typename shape_t, typename T>
    struct fixed_size<
        view::decorator_t<view::full_t,shape_t,T>
    > {
        using view_type  = view::decorator_t<view::full_t,shape_t,T>;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                constexpr auto shape = to_value_v<shape_type>;
                return index::product(shape);
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename shape_t, typename T>
    struct fixed_shape<
        view::decorator_t<view::full_t,shape_t,T>
    > {
        using view_type  = view::decorator_t<view::full_t,shape_t,T>;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                constexpr auto shape = to_value_v<shape_type>;
                return shape;
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename shape_t, typename T>
    struct bounded_size<
        view::decorator_t<view::full_t,shape_t,T>
    > {
        using view_type  = view::decorator_t<view::full_t,shape_t,T>;
        using shape_type = typename view_type::shape_type;

        static constexpr auto value = [](){
            constexpr auto shape = to_value_v<shape_type>;
            if constexpr (is_constant_index_array_v<decltype(shape)>) {
                return index::product(shape);
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename shape_t, typename fill_value_t>
    struct is_ndarray< view::decorator_t< view::full_t, shape_t, fill_value_t >>
    {
        static constexpr auto value = is_num_v<fill_value_t> && is_index_array_v<shape_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_FULL_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FULL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FULL_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/full.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct full_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::full(args...);
            }
        };
    }

    constexpr inline auto full = functor_t{nullary_fmap_t<fun::full_t>{}};

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::full_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::full_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            const auto& attributes = view.attributes();
            constexpr auto N = meta::len_v<decltype(attributes)>;
            return meta::template_reduce<N>([&](auto init, auto index){
                return init[nmtools::at(attributes,index)];
            },full);
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FULL_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FULL_HPP
#define NMTOOLS_ARRAY_ARRAY_FULL_HPP

#include "nmtools/array/full.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute full.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam shape_t 
     * @tparam fill_value_t 
     * @param shape      Desired shape
     * @param fill_value Fill value
     * @param context    Evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename shape_t, typename fill_value_t>
    constexpr auto full(const shape_t& shape, fill_value_t fill_value,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::full(shape,fill_value);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // full
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_FULL_HPP