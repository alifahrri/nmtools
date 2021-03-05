#ifndef NMTOOLS_ARRAY_VIEW_WHERE_HPP
#define NMTOOLS_ARRAY_VIEW_WHERE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"

namespace nmtools::view
{
    template <typename condition_t, typename x_t, typename y_t>
    struct where_t
    {
        using condition_type = condition_t;
        using x_type = x_t;
        using y_type = y_t;
        // TODO: make decorator to be independent from array_type
        using array_type = condition_t;

        condition_type condition;
        x_type x;
        y_type y;

        constexpr where_t(condition_type condition, x_type x, y_type y)
            : condition(condition), x(x), y(y) {}
        
        constexpr auto shape() const
        {
            return ::nmtools::shape(condition);
        } // shape

        constexpr auto dim() const
        {
            return ::nmtools::dim(condition);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            using ::nmtools::detail::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for broadcast_to view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            auto c  = apply_at(condition, indices_);
            auto x_ = apply_at(x, indices_);
            auto y_ = apply_at(y, indices_);
            return c ? x_ : y_;
        } // operator()
    }; // where_t

    /**
     * @brief Return elements chosen from x or y depending on condition.
     * 
     * @tparam condition_t 
     * @tparam x_t 
     * @tparam y_t 
     * @param condition 
     * @param x Array in which its elements are to be selected if corresponding condition is true.
     * @param y Array in which its elements are to be selected if corresponding condition is false.
     * @return constexpr auto 
     */
    template <typename condition_t, typename x_t, typename y_t>
    constexpr auto where(const condition_t& condition, const x_t& x, const y_t& y)
    {
        // broadcast condition, x, y together
        // TODO: better error handling
        auto [condition_, x_, y_] = broadcast_arrays(condition, x, y);
        using bcondition_t = decltype(condition_);
        using bx_t = decltype(x_);
        using by_t = decltype(y_);

        return decorator_t<where_t,bcondition_t,bx_t,by_t>{{condition_,x_,y_}};
    } // where
} // namespace nmtools::view

namespace nmtools::meta
{
    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename condition_t, typename x_t, typename y_t>
    struct fixed_matrix_size< view::where_t<condition_t,x_t,y_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename condition_t, typename x_t, typename y_t>
    struct fixed_vector_size< view::where_t<condition_t,x_t,y_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename condition_t, typename x_t, typename y_t>
    struct fixed_ndarray_shape< view::where_t<condition_t,x_t,y_t> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename condition_t, typename x_t, typename y_t>
    struct is_ndarray< view::decorator_t< view::where_t, condition_t, x_t, y_t >>
    {
        static constexpr auto value = is_ndarray_v<condition_t> && is_ndarray_v<x_t> && is_ndarray_v<y_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_WHERE_HPP