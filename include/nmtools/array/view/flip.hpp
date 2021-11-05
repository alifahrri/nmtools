#ifndef NMTOOLS_ARRAY_VIEW_FLIP_HPP
#define NMTOOLS_ARRAY_VIEW_FLIP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/slice.hpp"
#include "nmtools/array/index/count.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"

namespace nmtools::view
{
    namespace detail
    {
        /**
         * @brief Helper fn to prepare axis for flip view
         *
         * Transform None and int to array.
         * 
         * @tparam axis_type 
         * @tparam shape_t 
         * @tparam axis_t 
         * @param shape original array shape
         * @param axis axis param
         * @return constexpr auto 
         */
        template <typename axis_type, typename shape_t, typename axis_t>
        constexpr auto compute_flip_axis(const shape_t& shape, const axis_t& axis)
        {
            auto flip_axis = axis_type{};
            if constexpr (is_none_v<axis_t>) {
                // following numpy, when axis is none flip all axes
                auto n = len(shape);
                if constexpr (meta::is_resizeable_v<axis_type>)
                    flip_axis.resize(n);
                // for fixed vector, assume the length aleady match
                // TODO: error handling
                for (size_t i=0; i<n; i++)
                    at(flip_axis,i) = i;
            }
            else if constexpr (meta::is_index_v<axis_t>) {
                if constexpr (meta::is_resizeable_v<axis_type>)
                    flip_axis.resize(1);
                at(flip_axis,0) = axis;
            }
            else /* if constexpr (meta::is_index_array<axis_t>) */ {
                // cast to axis_type
                auto n = len(axis);
                if constexpr (meta::is_resizeable_v<axis_type>)
                    flip_axis.resize(n);
                for (size_t i=0; i<n; i++)
                    at(flip_axis,i) = at(axis,i);
            }
            return flip_axis;
        } // compute_flip_axis

        template <size_t DIM, typename axes_t>
        constexpr auto get_flip_slices(const axes_t& axes)
        {
            using slices_type = std::array<std::tuple<none_t,none_t,int>,DIM>;
            auto slices = slices_type {};

            for (size_t i=0; i<DIM; i++) {
                auto in_axis = static_cast<bool>(
                    index::count([&](const auto ii){
                        using common_t = meta::promote_index_t<decltype(ii),size_t>;
                        return (common_t)ii == (common_t)i;
                    }, axes)
                );
                // note that None is not assignable (yet?)
                // at(slices,i) = {None,None, in_axis ? -1 : 1};
                std::get<2>(at(slices,i)) = in_axis ? -1 : 1;
            }
            
            return slices;
        } // get_flip_slices

        /**
         * @brief Helper fn to prepare slice param.
         * 
         * Note that flip is implemented using slice,
         * this fn prepare the slices, called at view construction.
         * 
         * @tparam array_t 
         * @tparam axes_t 
         * @param axes 
         * @return constexpr auto 
         */
        template <typename array_t, typename axes_t>
        constexpr auto get_flip_slices(const axes_t& axes)
        {
            constexpr auto DIM = meta::fixed_dim_v<array_t>;
            return get_flip_slices<DIM>(axes);
        } // get_flip_slices
    } // namespace detail

    /**
     * @brief view object for flip
     * 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename axis_t>
    struct flip_t
    {
        using array_type = const array_t&;
        // axis_type is simply given axis (as parameter)
        // assume axis_t can be integer, none, or index array
        using axis_type = const axis_t&;
        // deduce shape_type from fn call
        using shape_type = meta::tuple_to_array_t<
            meta::remove_cvref_t<decltype(::nmtools::shape(std::declval<array_t>()))>
        >;
        // axes_type should be index_array
        static constexpr auto axes_vtype = [](){
            if constexpr (meta::is_index_array_v<axis_t>)
                return meta::as_value<axis_t>{};
            else if constexpr (meta::is_index_v<axis_t>)
                return meta::as_value<std::array<axis_t,1>>{};
            // for none type, simply use array shape type
            else if constexpr (is_none_v<axis_t>)
                return meta::as_value<shape_type>{};
        }();
        using axes_type = meta::transform_bounded_array_t<
            meta::type_t<meta::remove_cvref_t<decltype(axes_vtype)>>
        >;
        // deduce slice type from fn call
        using slices_type = meta::remove_cvref_t<decltype(detail::get_flip_slices<array_t>(std::declval<axes_type>()))>;

        // the underlying array
        array_type array;
        // the underlying array's shape
        shape_type shape_;
        // axes represents underlying array's axes to be flipped
        axes_type axes;
        // under the hood, this view uses index' slice to compute indices
        // for example flip(a) is the same as a[::-1] where a is 1D array
        slices_type slices;

        constexpr flip_t(array_type array, axis_type axis) : array(array)
            , shape_(::nmtools::shape(array))
            , axes(detail::compute_flip_axis<axes_type>(shape_,axis))
            , slices(detail::get_flip_slices<array_t>(axes))
        {}
        
        constexpr auto shape() const
        {
            // note that flipping doesn't change the shape at all
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto flip_indices = pack_indices(indices...);

            auto indices_ = index::apply_slice(flip_indices,shape_,slices);
            return indices_;
        } // operator()
    }; // flip_t

    /**
     * @brief Reverse the order of elements of given array according to specified axis.
     *
     * Axis can be None, a single integer, or index_array.
     * For None axis, reverse all original axis.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array array in which its elements are to be reversed
     * @param axis axis to operate
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t>
    constexpr inline auto flip(const array_t& array, const axis_t& axis)
    {
        using view_t = decorator_t<flip_t,array_t,axis_t>;
        return view_t{{array,axis}};
    } // flip
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Specialization of fixed_ndarray_shape for view::flip.
     *
     * Flip doesn't change shape, simply call fixed_ndarray_shape_v
     * on the underlying array type.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename axis_t>
    struct fixed_ndarray_shape< view::flip_t<array_t,axis_t> >
    {
        static inline constexpr auto value = fixed_ndarray_shape_v<array_t>;
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename array_t, typename axis_t>
    struct is_ndarray< view::decorator_t< view::flip_t, array_t, axis_t >>
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_FLIP_HPP