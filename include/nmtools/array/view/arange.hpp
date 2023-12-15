#ifndef NMTOOLS_ARRAY_VIEW_ARANGE_HPP
#define NMTOOLS_ARRAY_VIEW_ARANGE_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/index/arange.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    namespace detail
    {
        using index::arange_shape, index::ceil_;
    } // namespace detail

    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct arange_t
    {
        using start_type = const start_t;
        using stop_type  = const stop_t;
        // step can be none, represent 1
        using step_type  = const step_t;
        using element_type = T;
        // TODO: rename array_type to operand_type
        using array_type = nmtools_tuple<>;
        using shape_type = meta::resolve_optype_t<index::arange_shape_t,start_t,stop_t,step_t>;

        start_type start;
        stop_type stop;
        step_type step;
        shape_type shape_;
        // to make get_array works
        array_type array{};

        constexpr arange_t(start_type start, stop_type stop, step_type step)
            : start(start)
            , stop(stop)
            , step(step)
            , shape_(index::arange_shape(start,stop,step))
        {}

        constexpr auto attributes() const
        {
            return nmtools_tuple{start,stop,step,dtype_t<element_type>{}};
        }

        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            using namespace literals;
            return 1_ct;
        } // dim

        template <typename size_type>
        constexpr auto operator()(size_type index) const
        {
            if constexpr (is_none_v<step_t>)
                return static_cast<element_type>(start) + index;
            else
                return static_cast<element_type>(start) + (index * step);
        } // operator()
    }; // arange_t
    
    /**
     * @brief Creates arange_t view.
     *
     * An arange_t view is 1-dimensional array
     * which its values are evenly spaced within a given interval.
     * 
     * @tparam start_t 
     * @tparam stop_t 
     * @tparam step_t 
     * @tparam T 
     * @param start start of the interval
     * @param stop end of the interval
     * @param step spacing between interval
     * @param dtype desired data type
     * @return constexpr auto 
     */
    template <typename start_t, typename stop_t, typename step_t, typename T=float>
    constexpr auto arange(start_t start, stop_t stop, step_t step, dtype_t<T> = float32)
    {
        using view_t = decorator_t<arange_t,start_t,stop_t,step_t,T>;
        return view_t{{start,stop,step}};
    } // arange

    template <typename start_t, typename stop_t, typename T=float>
    constexpr auto arange(start_t start, stop_t stop, dtype_t<T> dtype=float32)
    {
        using namespace literals;
        return arange(start,stop,1_ct,dtype);
    } // arange

    template <typename stop_t, typename T=float>
    constexpr auto arange(stop_t stop, dtype_t<T> dtype=float32)
    {
        using namespace literals;
        return arange(0_ct,stop,1_ct,dtype);
    } // arange

} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct get_element_type< view::decorator_t<view::arange_t, start_t, stop_t, step_t, T> >
    {
        using type = T;
    };

    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct fixed_size<
        view::decorator_t<view::arange_t, start_t, stop_t, step_t, T>
    > {
        using view_type  = view::decorator_t<view::arange_t, start_t, stop_t, step_t, T>;
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

    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct fixed_shape<
        view::decorator_t<view::arange_t, start_t, stop_t, step_t, T>
    > {
        using view_type  = view::decorator_t<view::arange_t, start_t, stop_t, step_t, T>;
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

    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct bounded_size<
        view::decorator_t<view::arange_t, start_t, stop_t, step_t, T>
    > : fixed_size<
        view::decorator_t<view::arange_t, start_t, stop_t, step_t, T>
    > {};

    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct is_ndarray< view::decorator_t< view::arange_t, start_t, stop_t, step_t, T >>
    {
        static constexpr auto value = is_num_v<T> && is_index_v<start_t>
            && is_index_v<stop_t> && (is_index_v<step_t> || is_none_v<step_t>);
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ARANGE_HPP