#ifndef NMTOOLS_ARRAY_VIEW_TAKE_HPP
#define NMTOOLS_ARRAY_VIEW_TAKE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/index/take.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::view
{
    template <typename array_t, typename indices_t, typename axis_t>
    struct take_t
    {
        using array_type   = resolve_array_type_t<array_t>;
        using indices_type = resolve_attribute_type_t<indices_t>;
        using axis_type    = resolve_attribute_type_t<axis_t>;
        using src_shape_type = decltype(nmtools::shape</*force_constant_index*/true>(meta::declval<array_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_take_t,src_shape_type,indices_t,axis_t>;

        array_type     array;
        indices_type   indices;
        axis_type      axis;
        dst_shape_type shape_;

        constexpr take_t(const array_t& array_, const indices_t& indices_, const axis_t& axis)
            : array(initialize<array_type>(array_))
            , indices(init_attribute<indices_type>(indices_))
            , axis(init_attribute<axis_type>(axis))
            , shape_(index::shape_take(nmtools::shape</*force_constant_index*/true>(array_),indices_,axis))
        {}

        constexpr auto operands() const noexcept
        {
            return nmtools_tuple<array_type>{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{indices,axis};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            auto shape_ = detail::shape(array);
            return ::nmtools::index::take(indices_,shape_,this->indices,axis);
        } // index
    }; // take_t

    /**
     * @brief Take elements from an array along an axis.
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @param array The source array.
     * @param indices The indices of elements to be extracted.
     * @param axis Which axis to take elements.
     * @return constexpr auto 
     */
    template <typename array_t, typename indices_t, typename axis_t>
    constexpr auto take(const array_t& array, const indices_t& indices, axis_t axis)
    {
        // TODO: error handling for index error, e.g. any elements of "indices" is greater than "shape" at "axis"
        return decorator_t<take_t,array_t,indices_t,axis_t>{{array,indices,axis}};
    } // take
} // namespace nmtools::view


namespace nmtools::meta
{
    template <typename array_t, typename indices_t, typename axis_t>
    struct fixed_size<
        view::decorator_t< view::take_t, array_t, indices_t, axis_t >
    >
    {
        using view_type  = view::decorator_t< view::take_t, array_t, indices_t, axis_t >;
        using dst_shape_type = typename view_type::dst_shape_type;

        static constexpr auto value = [](){
            // indices and axis contributes to shape changes, may decrease/increase number of elements
            if constexpr (is_constant_index_array_v<dst_shape_type>) {
                return index::product(dst_shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    // NOTE: we can not know the size bound with only src array shape,
    // indices and axis contributes to shape changes, may decrease/increase number of elements
    template <typename array_t, typename indices_t, typename axis_t>
    struct bounded_size<
        view::decorator_t< view::take_t, array_t, indices_t, axis_t >
    > : fixed_size<
        view::decorator_t< view::take_t, array_t, indices_t, axis_t >
    > {};

    template <typename array_t, typename indices_t, typename axis_t>
    struct is_ndarray< view::decorator_t< view::take_t, array_t, indices_t, axis_t >>
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_TAKE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TAKE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TAKE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/take.hpp"

namespace nmtools::functional
{
    constexpr inline auto take_fun = [](const auto&...args){
        return view::take(args...);
    };

    constexpr inline auto take = functor_t{unary_fmap_t<decltype(take_fun)>{take_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TAKE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TAKE_HPP
#define NMTOOLS_ARRAY_ARRAY_TAKE_HPP

#include "nmtools/array/take.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate take op.
     * 
     * Take elements from an array along an axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @param array     input array
     * @param indices   the indices of elements to be extracted
     * @param axis      which axis to take element
     * @param context   evaluation context
     * @param output    optional outptu
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename indices_t, typename axis_t>
    constexpr auto take(const array_t& array, const indices_t& indices, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto array_ = view::take(array,indices,axis);
        return eval(array_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // take
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TAKE_HPP