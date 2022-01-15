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
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"

#include "nmtools/constants.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::view::detail::fn
{
    /**
     * @brief Index broadcast_to, compile-time version.
     * 
     * This is useful when one wants to check broadcasting at compile time,
     * but it is desired that the results is to be type instead of value.
     * For instance, broadcast_to type constructor requires the shape_t argument
     * to be type template parameter.
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @return constexpr auto 
     */
    template <typename array_t, typename shape_t>
    constexpr auto shape_broadcast_to(meta::as_value<array_t>, meta::as_value<shape_t>)
    {
        // map type to value
        constexpr auto src_shape = meta::fixed_ndarray_shape_v<array_t>;
        constexpr auto dst_shape = meta::to_value_v<shape_t>;
        // actually call broadcast to
        constexpr auto result    = index::shape_broadcast_to(src_shape,dst_shape);
        // TODO: use optional
        constexpr auto success   = nmtools::get<0>(result);
        if constexpr (success) {
            constexpr auto shape_ = nmtools::get<1>(result);
            constexpr auto free   = nmtools::get<2>(result);
            constexpr auto not_free    = index::logical_not(free);
            constexpr auto origin_axes = index::nonzero(not_free);
            using mshape_t = decltype(shape_);
            using origin_t = decltype(origin_axes);
            using return_t = meta::make_tuple_type_t<mshape_t,origin_t>;
            // not really need to pass value since they are "value-less" type?
            return return_t{shape_, origin_axes};
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
        // NOTE: do not take ref if the array is another view
        // since it makes composing view not possible.
        using array_type = resolve_array_type_t<array_t>;
        using shape_type = shape_t;
        using origin_axes_type = origin_axes_t;

        array_type array;
        shape_type shape_; // broadcasted shape
        origin_axes_type origin_axes; // origin axes axes
        
        constexpr broadcast_to_t(const array_t& array, shape_type shape, origin_axes_type origin_axes)
            : array(initialize<array_type>(array)), shape_(shape), origin_axes(origin_axes) {}
        
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
            // while broadcast_to is purely indexing view
            // (transform one (dst) indices to another (src) indices),
            // we also need to handle Num type here,
            // so for now use "operator()" instead of "index" member fn.
            // TODO: consider to move Num type handling to decorator_t

            if constexpr (meta::is_num_v<array_t>)
                return array;
            else {
                auto indices_  = pack_indices(indices...);
                auto src_shape = detail::shape(array);

                auto tf_indices = ::nmtools::index::broadcast_to(indices_,src_shape,shape_,origin_axes);
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_at(*array,tf_indices);
                } else {
                    return apply_at(array,tf_indices);
                }
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
        shape_type shape_; // broadcasted shape (destination)
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
        if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using ret_left_t  = decltype(broadcast_to(meta::declval<left_t>(),shape));
            using ret_right_t = decltype(broadcast_to(meta::declval<right_t>(),shape));
            using either_t = meta::replace_either_t<array_t,ret_left_t,ret_right_t>;
            if (auto l_ptr = nmtools::get_if<left_t>(&array)) {
                return either_t{broadcast_to(*l_ptr,shape)};
            } else /* if (auto r_ptr = nmtools::get_if<right_t>(&array)) */ {
                auto r_ptr = nmtools::get_if<right_t>(&array);
                return either_t{broadcast_to(*r_ptr,shape)};
            }
        }
        // bypass broadcasting index logic if array_t is simply scalar type
        else if constexpr (meta::is_num_v<array_t>) {
            using view_t = decorator_t<broadcast_to_t,array_t,shape_t,none_t>;
            return view_t{{array, shape, None}};
        }
        // both shape is known at compile time, checks at compile time
        else if constexpr (meta::is_fixed_size_ndarray_v<array_t> && meta::is_constant_index_array_v<shape_t>) {
            constexpr auto array_v = meta::as_value_v<array_t>;
            constexpr auto shape_v = meta::as_value_v<shape_t>;
            constexpr auto result  = detail::fn::shape_broadcast_to(array_v,shape_v);
            using result_t = decltype(result);
            if constexpr (!meta::is_fail_v<result_t>) {
                constexpr auto origin_axes = nmtools::get<1>(result);
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
            // NOTE: must declare as const since utl::tuple takes reference (?)
            // TODO: revisit this case
            const auto [success, shape_, free] = index::shape_broadcast_to(ashape,shape);
            auto origin_axes = [](auto free){
                // NOTE: can't use capture because clang complains something local binding

                using free_t  = decltype(free);
                // free axes can be none when num type is broadcasted to some shape,
                // avoid call any further logic when free axes is none.
                // when it is none, that means the array is num type and view::broadcast_to_t won't complain
                if constexpr (meta::is_ndarray_v<free_t>) {
                    auto not_free    = index::logical_not(free);
                    auto origin_axes = index::nonzero(not_free);
                    return origin_axes;
                } else /* if constexpr (is_none_v<free_t>) */ {
                    return None;
                }
            }(free);
            using origin_axes_t = decltype(origin_axes);
            using view_t = decorator_t<broadcast_to_t,array_t,shape_t,origin_axes_t>;
            // prepare_type: may declare return_t as optional type
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
    struct fixed_dim<
        view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_fixed_index_array_v<shape_t> || is_constant_index_array_v<shape_t>) {
                return fixed_index_array_size_v<shape_t>;
            } else /* if (is_index_array_v<shape_t> || is_hybrid_index_array_v<shape_t>) */ {
                return detail::Fail;
            }
        }();
        // TODO: use fail type instead of void
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_dim

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
                // by constructing the view itself,
                // it should be known already if src and dst is broadcastable
                // hence it is actually redundant to check here
                // TODO: skip checking)
                constexpr auto result = index::shape_broadcast_to(src_shape,dst_shape);
                constexpr auto success = nmtools::get<0>(result);
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