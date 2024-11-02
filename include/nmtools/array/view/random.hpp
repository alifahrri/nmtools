#ifndef NMTOOLS_ARRAY_VIEW_RANDOM_HPP
#define NMTOOLS_ARRAY_VIEW_RANDOM_HPP

#include "nmtools/meta.hpp"

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/dtypes.hpp"

namespace nmtools::view
{
    template <typename shape_t, typename dtype_t, typename generator_t>
    struct random_t
    {
        using shape_type     = resolve_attribute_type_t<shape_t>;
        using element_type   = dtype_t;
        using generator_type = generator_t;

        using array_type = none_t;

        shape_type     shape_;
        generator_type generator_;

        constexpr random_t(const shape_t& shape, generator_t generator)
            : shape_(init_attribute<shape_type>(shape))
            , generator_(generator)
        {}

        constexpr auto shape() const
        {
            return shape_;
        } // shape

        template <typename...size_types>
        constexpr auto operator()(size_types.../*indices*/) const
        {
            // TODO: try to remove const cast
            return static_cast<element_type>(const_cast<generator_t&>(generator_)());
        } // operator()

        template <typename...size_types>
        constexpr auto operator()(size_types.../*indices*/)
        {
            return static_cast<element_type>(generator_());
        } // operator()

    }; // random_t

    template <typename shape_t, typename T, typename generator_t>
    constexpr auto random(const shape_t& shape, dtype_t<T>, generator_t generator)
    {
        using view_t = decorator_t<random_t, shape_t, T, generator_t>;
        return view_t{{shape,generator}};
    } // random
} // namespace nmtools::array

namespace nmtools::meta
{
    template <typename shape_t, typename dtype_t, typename generator_t>
    struct get_element_type< view::decorator_t<view::random_t, shape_t, dtype_t, generator_t> >
    {
        using type = dtype_t;
    };

    template <typename shape_t, typename dtype_t, typename generator_t>
    struct is_ndarray< view::decorator_t< view::random_t, shape_t, dtype_t, generator_t >>
    {
        static constexpr auto value = is_num_v<dtype_t> && is_index_array_v<shape_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_RANDOM_HPP