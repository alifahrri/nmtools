#ifndef NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP

#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/array/index/logical_not.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_offset.hpp"

// to get make_dynamic_ndarray & make_fixed_ndarray defn.
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/eval.hpp"

#include "nmtools/constants.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::view::detail::fn
{
    /**
     * @brief Index broadcast_to, compile-time version.
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @return constexpr auto 
     */
    template <typename array_t, typename shape_t>
    constexpr auto broadcast_to(meta::as_value<array_t>, meta::as_value<shape_t>)
    {
        // map type to value
        constexpr auto src_shape = meta::fixed_ndarray_shape_v<array_t>;
        constexpr auto dst_shape = meta::constant_to_value_v<shape_t>;
        // actually call broadcast to
        constexpr auto result    = index::broadcast_to(src_shape,dst_shape);
        // TODO: use optional
        constexpr auto success   = std::get<0>(result);
        if constexpr (success) {
            constexpr auto shape_ = std::get<1>(result);
            constexpr auto free   = std::get<2>(result);
            constexpr auto not_free    = index::logical_not(free);
            constexpr auto origin_axes = index::nonzero(not_free);
            return std::tuple{shape_, origin_axes};
        }
        else return meta::detail::Fail;
    }
} // nmtools::view::detail::fn

namespace nmtools::view
{
    /**
     * @brief View object for broadcast_to.
     *
     * Broadcast given array to desired shape.
     * 
     * @tparam array_t src array type
     * @tparam shape_t desired shape type
     * @tparam origin_axes_t the type of origin_axes which is used
     * for gather the original (src) shape from desired (dst) shape.
     */
    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct broadcast_to_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;
        using shape_type = shape_t;
        using origin_axes_type = origin_axes_t;

        array_type array;
        shape_type shape_; // broadcasted shape
        origin_axes_type origin_axes; // origin axes axes

        constexpr broadcast_to_t(array_type array, shape_type shape, origin_axes_type origin_axes)
            : array(array), shape_(shape), origin_axes(origin_axes) {}
        
        constexpr decltype(auto) shape() const noexcept
        {
            return shape_;
        } // shape

        constexpr decltype(auto) dim() const noexcept
        {
            if constexpr (is_none_v<shape_t>)
                return 0;
            else return len(shape_);
        } // shape

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

            if constexpr (std::is_arithmetic_v<array_t>)
                return array;
            else {
                auto origin_shape   = index::gather(shape_,origin_axes);
                auto origin_strides = index::compute_strides(origin_shape);
                auto origin_indices = index::gather(indices_,origin_axes);
                auto offset = index::compute_offset(origin_indices,origin_strides);

                auto tf_indices = index::compute_indices(offset,::nmtools::shape(array));
                return apply_at(array,tf_indices);
            }
        } // operator()
    }; // broadcast_to_t

    /**
     * @brief Specialization of broadcast_to_t for None shape.
     *
     * array_t must be scalar type. Doesn't have member operator().
     * This view is considered as scalar type.
     * 
     * @tparam array_t 
     * @tparam origin_axes_t 
     */
    template <typename array_t, typename origin_axes_t>
    struct broadcast_to_t<array_t,none_t,origin_axes_t>
    {
        // conversion can't have trailing return type
        static_assert( meta::is_num_v<array_t>
            , "when shape is None, only accepts scalar array");
        using value_type = array_t;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;
        using shape_type = none_t;
        // ignored:
        using origin_axes_type = origin_axes_t;

        array_type array;
        shape_type shape_; // broadcasted shape
        origin_axes_type origin_axes; // origin axes axes

        constexpr broadcast_to_t(array_type array, shape_type shape, origin_axes_type origin_axes)
            : array(array), shape_(shape), origin_axes(origin_axes) {}
        
        constexpr auto shape() const noexcept
        {
            return None;
        } // shape

        constexpr auto dim() const noexcept
        {
            return 0;
        } // shape

        constexpr operator value_type() const noexcept
        {
            return static_cast<value_type>(array);
        } // operator value_type()
    }; // broadcast_to_t

    /**
     * @brief broadcast array to a new shape
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array The array to be broadcasted
     * @param shape The desired shape of the array
     * @return constexpr auto 
     */
    template <typename array_t, typename shape_t>
    constexpr auto broadcast_to(const array_t& array, shape_t shape)
    {
        // bypass broadcasting index logic if array_t is simply scalar type
        if constexpr (std::is_arithmetic_v<array_t>) {
            using view_t = decorator_t<broadcast_to_t,array_t,shape_t,none_t>;
            return view_t{{array, shape, None}};
        }
        // both shape is known at compile time, checks at compile time
        else if constexpr (meta::is_fixed_size_ndarray_v<array_t> && meta::is_constant_index_array_v<shape_t>) {
            constexpr auto array_v = meta::as_value_v<array_t>;
            constexpr auto shape_v = meta::as_value_v<shape_t>;
            constexpr auto result  = detail::fn::broadcast_to(array_v,shape_v);
            using result_t = decltype(result);
            if constexpr (!meta::is_fail_v<result_t>) {
                constexpr auto shape_ = std::get<0>(result);
                constexpr auto origin_axes = std::get<1>(result);
                using origin_axes_t = meta::remove_cvref_t<decltype(origin_axes)>;
                using view_t = decorator_t<broadcast_to_t,array_t,shape_t,origin_axes_t>;
                return view_t{{array,shape,origin_axes}};
            }
            else static_assert( !meta::is_fail_v<result_t>
                , "unsupported broadcast_to" );
        }
        // assume array_t is ndarray
        else {
            auto ashape = ::nmtools::shape(array);
            auto [success, shape_, free] = index::broadcast_to(ashape,shape);
            auto not_free    = index::logical_not(free);
            auto origin_axes = index::nonzero(not_free);
            using origin_axes_t = decltype(origin_axes);
            using view_t = decorator_t<broadcast_to_t,array_t,shape_t,origin_axes_t>;
            // maybe declare return_t as optional type
            nmtools_assert_prepare_type (return_t, view_t);
            nmtools_assert (success, "cannot broadcast shape", return_t);
            // NOTE:
            // the array view itself cannot be called with constexpr directly (because it use reference)
            // but can be evaluated in constexpr
            // see also https://en.cppreference.com/w/cpp/language/constant_expression
            // Seems like constexpr variable can't hold reference.
            // clang complains with:
            //      note: reference to 'x' is not a constant expression
            // where 'x' is array
            // but this function itself (and the broadcast_to_t constructor) are still marked as constexpr
            // to let the view evaluated in constexpr context.
            return return_t{view_t{{array,shape,origin_axes}}};
        }
    } // broadcast_to

} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct is_dynamic_ndarray< 
        view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t >
    >
    {
        static constexpr auto value = [](){
            if (is_fixed_index_array_v<shape_t> || is_constant_index_array_v<shape_t> || is_hybrid_index_array_v<shape_t>) {
                return false;
            } else if (is_index_array_v<shape_t>) {
                return true;
            }
        }();
    }; // is_dynamic_ndarray

    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct is_fixed_dim_ndarray<
        view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t >
    >
    {
        static constexpr auto value = [](){
            if (is_fixed_index_array_v<shape_t> || is_constant_index_array_v<shape_t>) {
                return true;
            } else /* if (is_index_array_v<shape_t> || is_hybrid_index_array_v<shape_t>) */ {
                return false;
            }
        }();
    }; // is_fixed_dim_ndarray

    /**
     * @brief Specialization of fixed_ndarray_shape for broadcast_to view.
     *
     * Return the fixed shape if array_t is fixed size
     * and shape_t is known at compile time (constant index array).
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @tparam origin_axes_t 
     */
    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct fixed_ndarray_shape< view::broadcast_to_t<array_t, shape_t, origin_axes_t> >
    {
        static constexpr auto value = [](){
            // for now, only deduce broadcast_to view as fixed-size
            // whenever BOTH the shape and referenced array's shape is known at compile-time
            // TODO: consider to deduce as fixed-size when 
            // shape is known at compile time regardless the type of ref array
            if constexpr (is_constant_index_array_v<shape_t> && is_fixed_size_ndarray_v<array_t>) {
                constexpr auto src_shape = fixed_ndarray_shape_v<array_t>;
                // assume the shape is default constructible
                // and the shape information is embedded to the type
                constexpr auto dst_shape = shape_t{};
                constexpr auto dim = fixed_index_array_size_v<shape_t>;
                // by constructing the view itself,
                // it should be known already if src and dst is broadcastable
                // hence it is actually redundant to check here
                // TODO: skip checking)
                constexpr auto result = index::broadcast_to(src_shape,dst_shape);
                constexpr auto success = std::get<0>(result);
                if constexpr (success)
                    return dst_shape;
                else return detail::fail_t{};
            } else if constexpr (is_constant_index_array_v<shape_t> && is_num_v<array_t>) {
                // constant index array should be default-constructible;
                return shape_t{};
            }
            else return detail::fail_t{};
        }();
        using value_type = meta::remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct is_ndarray< view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t >>
    {
        static constexpr auto value = (is_ndarray_v<array_t> || is_num_v<array_t>) && is_index_array_v<shape_t>;
    };

    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct is_num< view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t >>
    {
        static constexpr auto value = is_num_v<array_t> && is_none_v<shape_t>;
    };

    /**
     * @brief Resolve optype for broadcast_to view evaluation.
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @tparam origin_axes_t 
     */
    template <typename array_t, typename shape_t, typename origin_axes_t>
    struct resolve_optype<
        void, array::eval_t, view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t >, none_t
    >
    {
        static constexpr auto vtype = [](){
            using element_t = get_element_type_t<array_t>;
            if constexpr (is_constant_index_array_v<shape_t>) {
                using ref_array_t = make_fixed_ndarray_t<element_t,shape_t>;
                using type = resize_fixed_ndarray_t<array_t,ref_array_t>;
                return as_value_v<type>;
            } else /* if constexpr (is_dynamic_index_array_v<shape_t> */ {
                using type = make_dynamic_ndarray_t<element_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP