#ifndef NMTOOLS_ARRAY_VIEW_ARANGE_HPP
#define NMTOOLS_ARRAY_VIEW_ARANGE_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    namespace detail
    {
        // workaround for clang
        // since gcc has constexpr ceil while clang doesn't :|
        constexpr size_t ceil_(float num)
        {
            return (static_cast<float>(static_cast<size_t>(num)) == num)
                ? static_cast<size_t>(num)
                : static_cast<size_t>(num) + ((num > 0) ? 1 : 0);
        }

        template <typename start_t, typename stop_t, typename step_t>
        constexpr auto arange_shape(start_t start, stop_t stop, step_t step)
        {
            size_t d = ceil_(float(stop - start) / step);
            return std::array{d};
        } // arange_shape
    } // namespace detail

    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct arange_t
    {
        using start_type = const start_t;
        using stop_type  = const stop_t;
        // step can be none, represent 1
        using step_type  = const step_t;
        using element_type = T;
        using array_type = none_t;

        start_type start;
        stop_type stop;
        step_type step;

        constexpr arange_t(start_type start, stop_type stop, step_type step)
            : start(start), stop(stop), step(step) {}

        constexpr auto shape() const
        {
            if constexpr (is_none_v<step_t>)
                return detail::arange_shape(start,stop,1);
            else
                return detail::arange_shape(start,stop,step);
        } // shape

        constexpr auto dim() const
        {
            return 1;
        } // dim

        template <typename size_type>
        constexpr auto operator()(size_type index) const
        {
            if constexpr (is_none_v<step_t>)
                return static_cast<element_type>(start + index);
            else
                return static_cast<element_type>(start + index * step);
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
    constexpr auto arange(start_t start, stop_t stop, step_t step, dtype_t<T> dtype=float32)
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
    struct fixed_ndarray_shape< view::arange_t<start_t, stop_t, step_t, T> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_integral_constant_v<start_t> && is_integral_constant_v<stop_t> && is_integral_constant_v<step_t>) {
                return view::detail::arange_shape(start_t{}, stop_t{}, step_t{});
            } else if constexpr (is_integral_constant_v<start_t> && is_integral_constant_v<stop_t> && is_none_v<step_t>) {
                return view::detail::arange_shape(start_t{}, stop_t{}, 1);
            } else if constexpr (is_none_v<start_t> && is_integral_constant_v<stop_t> && is_none_v<step_t>) {
                return view::detail::arange_shape(0, stop_t{}, 1);
            }
            else return detail::fail_t{};
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename start_t, typename stop_t, typename step_t, typename T>
    struct is_ndarray< view::decorator_t< view::arange_t, start_t, stop_t, step_t, T >>
    {
        static constexpr auto value = std::is_arithmetic_v<T> && is_index_v<start_t>
            && is_index_v<stop_t> && is_index_v<step_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_ARANGE_HPP