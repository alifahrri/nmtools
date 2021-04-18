#ifndef NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP
#define NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP

#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/concatenate.hpp"
#include "nmtools/array/shape.hpp"

#include <tuple>
#include <functional>

namespace nmtools::view
{
    template <typename lhs_array_t, typename rhs_array_t, typename axis_t>
    struct concatenate_t
    {
        using lhs_type = const lhs_array_t&;
        using rhs_type = const rhs_array_t&;
        using lhs_value_type = meta::get_element_type_t<lhs_array_t>;
        using rhs_value_type = meta::get_element_type_t<rhs_array_t>;
        using value_type = std::common_type_t<lhs_value_type,rhs_value_type>;
        using array_type = std::tuple<lhs_type,rhs_type>;
        using axis_type  = axis_t;

        // lhs_type  lhs;
        // rhs_type  rhs;
        array_type array;
        axis_type axis;

        // constexpr concatenate_t(lhs_type lhs, rhs_type rhs, axis_type axis)
        //     : lhs(lhs), rhs(rhs), axis(axis) {}

        constexpr concatenate_t(array_type array, axis_type axis)
            : array(array), axis(axis) {}
        
        constexpr auto shape() const
        {
            const auto& [lhs, rhs] = array;
            auto ashape = ::nmtools::shape(lhs);
            auto bshape = ::nmtools::shape(rhs);
            // @todo deal with dynamically changing array
            auto [success, shape] = index::shape_concatenate(ashape,bshape,axis);
            return shape;
        } // shape

        constexpr auto dim() const
        {
            const auto& [lhs, rhs] = array;
            auto ashape = ::nmtools::shape(lhs);
            auto bshape = ::nmtools::shape(rhs);
            // @todo deal with dynamically changing array
            auto [success, shape] = index::shape_concatenate(ashape,bshape,axis);
            return len(shape);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices)
        {
            auto indices_ = [&](){
                using index::make_array;
                using common_t = std::common_type_t<size_types...>;
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for transpose view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            const auto& [lhs, rhs] = array;
            // @todo do not always request shape! e.g. for fixed size array, or provide options to turn this off
            auto ashape = ::nmtools::shape(lhs);
            auto bshape = ::nmtools::shape(rhs);
            auto [aflag, bflag, a_idx, b_idx] = index::concatenate(ashape,bshape,indices_,axis);
            // @todo better error handling
            assert ( aflag || bflag
                // , "out of bound access"
            );
            // @todo maybe provide options/customization to select type casting
            using common_t = value_type;
            if (aflag)
                return static_cast<common_t>(apply_at(lhs,a_idx));
            else
                return static_cast<common_t>(apply_at(rhs,b_idx));
        } // operator()

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto indices_ = [&](){
                using index::make_array;
                using common_t = std::common_type_t<size_types...>;
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for transpose view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();
            const auto& [lhs, rhs] = array;
            // @todo do not always request shape! e.g. for fixed size array, or provide options to turn this off
            auto ashape = ::nmtools::shape(lhs);
            auto bshape = ::nmtools::shape(rhs);
            auto [aflag, bflag, a_idx, b_idx] = index::concatenate(ashape,bshape,indices_,axis);
            // @todo better error handling
            assert ( aflag || bflag
                // , "out of bound access"
            );
            // @todo maybe provide options/customization to select type casting
            using common_t = value_type;
            if (aflag)
                return static_cast<common_t>(apply_at(lhs,a_idx));
            else
                return static_cast<common_t>(apply_at(rhs,b_idx));
        } // operator()
    }; // concatenate_t

    /**
     * @brief Join two arrays along existing axis.
     * 
     * @tparam lhs_array_t 
     * @tparam rhs_array_t 
     * @tparam axis_t 
     * @param lhs lhs array
     * @param rhs rhs array
     * @param axis The axis along which the arrays will be joined. If axis is None, arrays are flattened before use.
     * @return constexpr auto 
     */
    template <typename lhs_array_t, typename rhs_array_t, typename axis_t>
    constexpr auto concatenate(const lhs_array_t& lhs, const rhs_array_t& rhs, axis_t axis)
    {
        auto ashape = shape(lhs);
        auto bshape = shape(rhs);
        auto [success, shape] = index::shape_concatenate(ashape,bshape,axis);
        assert (success
            // , "unsupported concatenate, mismatched shape"
        );
        // note must pass as cref to make tuple properly deduce to const ref
        auto array = std::tuple{std::cref(lhs),std::cref(rhs)};
        return decorator_t<concatenate_t,lhs_array_t,rhs_array_t,axis_t>{{array,axis}};
    } // concatenate
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename lhs_array_t, typename rhs_array_t, typename axis_t>
    struct is_ndarray< 
        view::decorator_t<
            view::concatenate_t, lhs_array_t, rhs_array_t, axis_t
        >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_array_t> && is_ndarray_v<rhs_array_t>;
    }; // is_ndarray
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP