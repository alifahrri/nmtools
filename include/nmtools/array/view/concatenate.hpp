#ifndef NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP
#define NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP

#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/concatenate.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    template <typename lhs_array_t, typename rhs_array_t, typename axis_t>
    struct concatenate_t
    {
        using lhs_type = const lhs_array_t&;
        using rhs_type = const rhs_array_t&;
        using lhs_value_type = meta::get_element_type_t<lhs_array_t>;
        using rhs_value_type = meta::get_element_type_t<rhs_array_t>;
        using value_type = meta::common_type_t<lhs_value_type,rhs_value_type>;
        using array_type = meta::make_tuple_type_t<lhs_type,rhs_type>;
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
            const auto [success, shape] = index::shape_concatenate(ashape,bshape,axis);
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
            auto indices_ = pack_indices(indices...);
            const auto& [lhs, rhs] = array;
            // @todo do not always request shape! e.g. for fixed size array, or provide options to turn this off
            auto ashape = ::nmtools::shape(lhs);
            auto bshape = ::nmtools::shape(rhs);
            const auto [aflag, bflag, a_idx, b_idx] = index::concatenate(ashape,bshape,indices_,axis);
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
            auto indices_ = pack_indices(indices...);
            const auto& [lhs, rhs] = array;
            // @todo do not always request shape! e.g. for fixed size array, or provide options to turn this off
            const auto ashape = ::nmtools::shape(lhs);
            const auto bshape = ::nmtools::shape(rhs);
            const auto [aflag, bflag, a_idx, b_idx] = index::concatenate(ashape,bshape,indices_,axis);
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
        const auto [success, shape] = index::shape_concatenate(ashape,bshape,axis);
        // TODO: use nmtools_assert macro
        assert (success
            // , "unsupported concatenate, mismatched shape"
        );
        using array_t = meta::make_tuple_type_t<const lhs_array_t&,const rhs_array_t&>;
        auto array = array_t{lhs,rhs};
        return decorator_t<concatenate_t,lhs_array_t,rhs_array_t,axis_t>{{array,axis}};
    } // concatenate
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Infer the element type of concatenate view.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @tparam axis_t 
     */
    template <typename lhs_t, typename rhs_t, typename axis_t>
    struct get_element_type< view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t > >
    {
        // by default, get_element_type should accept type with value_type
        // but fail on this case.
        using view_type = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using type = typename view_type::value_type;
    }; // get_element_type

    /**
     * @brief Infer the shape of concatenate view at compile-time.
     * 
     * Return Fail when the shape is only known at runtime.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @tparam axis_t 
     */
    template <typename lhs_t, typename rhs_t, typename axis_t>
    struct fixed_ndarray_shape<
        view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (
                    is_fixed_size_ndarray_v<lhs_t>
                &&  is_fixed_size_ndarray_v<rhs_t>
                && (is_constant_index_v<axis_t> || is_none_v<axis_t>)
            ) {
                constexpr auto ashape  = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto bshape  = fixed_ndarray_shape_v<rhs_t>;
                constexpr auto axis    = axis_t{};
                constexpr auto result  = index::shape_concatenate(ashape,bshape,axis);
                constexpr auto success = nmtools::get<0>(result);
                if constexpr (success) {
                    constexpr auto shape = nmtools::get<1>(result);
                    return shape;
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the dimension of concatenate view at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @tparam axis_t 
     */
    template <typename lhs_t, typename rhs_t, typename axis_t>
    struct fixed_dim<
        view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >
    >
    {
        static constexpr auto value = [](){
            using view_t = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
            if constexpr (is_fixed_size_ndarray_v<view_t>) {
                return nmtools::len(fixed_ndarray_shape_v<view_t>);
            } else if constexpr (is_none_v<axis_t>) {
                return 1;
            } else if constexpr (
                   is_fixed_dim_ndarray_v<lhs_t>
                && is_fixed_dim_ndarray_v<rhs_t>
            ) {
                // concatenate doesn't create new axis
                // just check if the dimension is the same
                constexpr auto ldim = fixed_dim_v<lhs_t>;
                constexpr auto rdim = fixed_dim_v<rhs_t>;
                if constexpr (ldim == rdim) {
                    return ldim;
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_dim

    /**
     * @brief Infer the shape of hybrid ndarray maximum size at compile-time.
     * Successful call will make the view considered hybrid_ndarray.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @tparam axis_t 
     */
    template <typename lhs_t, typename rhs_t, typename axis_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (
                   is_hybrid_ndarray_v<lhs_t>
                && is_hybrid_ndarray_v<rhs_t>
            ) {
                return hybrid_ndarray_max_size_v<lhs_t> + hybrid_ndarray_max_size_v<rhs_t>;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: fix either use value_type or type for deducing a valid value
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = remove_cvref_t<decltype(value)>;
    }; // hybrid_ndarray_max_size

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