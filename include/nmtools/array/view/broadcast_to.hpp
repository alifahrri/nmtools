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
    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t=none_t>
    struct broadcast_to_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        // NOTE: do not take ref if the array is another view
        // since it makes composing view not possible.
        using array_type = resolve_array_type_t<array_t>;
        using shape_type = resolve_attribute_type_t<shape_t>;
        using origin_axes_type = resolve_attribute_type_t<origin_axes_t>;
        using broadcast_size_type = bsize_t;

        array_type array;
        shape_type shape_; // broadcasted shape
        origin_axes_type origin_axes; // origin axes axes
        broadcast_size_type broadcast_size; // the resulting size from broadcast_arrays
        
        constexpr broadcast_to_t(const array_t& array, const shape_t& shape, origin_axes_type origin_axes, [[maybe_unused]] bsize_t bsize=bsize_t{})
            : array(initialize<array_type>(array))
            , shape_(init_attribute<shape_type>(shape))
            , origin_axes(init_attribute<origin_axes_type>(origin_axes))
            , broadcast_size(bsize)
        {}
        
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

        constexpr auto size() const noexcept
        {
            if constexpr (is_none_v<broadcast_size_type>) {
                return index::product(shape_);
            } else {
                return broadcast_size;
            }
        }

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // while broadcast_to is purely indexing view
            // (transform one (dst) indices to another (src) indices),
            // we also need to handle Num type here,
            // so for now use "operator()" instead of "index" member fn.
            // TODO: consider to move Num type handling to decorator_t

            if constexpr (meta::is_num_v<array_t>) {
                return array;
            } else {
                auto indices_  = pack_indices(indices...);
                auto src_shape = detail::shape(array);

                // TODO: refactor free_axes/origin_axes
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
    template <typename array_t, typename origin_axes_t, typename bsize_t>
    struct broadcast_to_t<array_t,none_t,origin_axes_t,bsize_t>
    {
        static_assert( meta::is_num_v<array_t>
            , "when shape is None, only accepts scalar array");
        using value_type = array_t;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;
        using shape_type = none_t;
        // ignored:
        using origin_axes_type = origin_axes_t;
        using broadcast_size_type = meta::ct<1ul>;

        array_type array;
        shape_type shape_; // broadcasted shape (destination)
        origin_axes_type origin_axes; // origin axes axes

        constexpr broadcast_to_t(array_type array, shape_type shape, origin_axes_type origin_axes, [[maybe_unused]] bsize_t bsize=bsize_t{})
            : array(array), shape_(shape), origin_axes(origin_axes) {}
        
        constexpr auto shape() const noexcept
        {
            return None;
        } // shape

        constexpr auto dim() const noexcept
        {
            return 0;
        } // shape

        constexpr auto size() const noexcept
        {
            return meta::ct_v<1ul>;
        } // shape

        constexpr operator value_type() const noexcept
        {
            static_assert( !meta::is_ndarray_v<meta::remove_cvref_pointer_t<array_type>>);
            return static_cast<value_type>(array);
        } // operator value_type()
    }; // broadcast_to_t

    // TODO: refactor free_axes
    /**
     * @brief broadcast array to a new shape
     * 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array The array to be broadcasted
     * @param shape The desired shape of the array
     * @return constexpr auto 
     */
    template <typename array_t, typename shape_t, typename bsize_t=none_t>
    constexpr auto broadcast_to(const array_t& array, shape_t shape, [[maybe_unused]] bsize_t bsize=bsize_t{})
    {
        if constexpr (meta::is_either_v<array_t>) {
            using left_t  = meta::get_either_left_t<array_t>;
            using right_t = meta::get_either_right_t<array_t>;
            using ret_left_t  = decltype(broadcast_to(meta::declval<left_t>(),shape,bsize));
            using ret_right_t = decltype(broadcast_to(meta::declval<right_t>(),shape,bsize));
            using either_t = meta::replace_either_t<array_t,ret_left_t,ret_right_t>;
            if (auto l_ptr = nmtools::get_if<left_t>(&array)) {
                return either_t{broadcast_to(*l_ptr,shape,bsize)};
            } else /* if (auto r_ptr = nmtools::get_if<right_t>(&array)) */ {
                auto r_ptr = nmtools::get_if<right_t>(&array);
                return either_t{broadcast_to(*r_ptr,shape,bsize)};
            }
        }
        // bypass broadcasting index logic if array_t is simply scalar type
        else if constexpr (meta::is_num_v<array_t>) {
            using view_t = decorator_t<broadcast_to_t,array_t,shape_t,none_t,bsize_t>;
            return view_t{{array, shape, None,bsize}};
        }
        // assume array_t is ndarray
        else {
            auto ashape = ::nmtools::shape</*force_constant_index*/true>(array);
            // somehow decomposing this is broken on c++ for opencl (clang-10)
            // error: cannot decompose class type 'tuple<__private bool, __private ... have non-static data members
            #if 0
            // NOTE: must declare as const since utl::tuple takes reference (?)
            // TODO: revisit this case
            const auto [success, shape_, free] = index::shape_broadcast_to(ashape,shape);
            #else
            const auto result = index::shape_broadcast_to(ashape,shape);
            const auto& success = nmtools::get<0>(result);
            const auto& shape_  = nmtools::get<1>(result);
            const auto& free    = nmtools::get<2>(result);
            #endif
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
            using array_type = meta::remove_address_space_t<array_t>;
            using view_t = decorator_t<broadcast_to_t,array_type,shape_t,origin_axes_t,bsize_t>;
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
            return return_t{view_t{{array,shape,origin_axes,bsize}}};
        }
    } // broadcast_to

} // namespace nmtools::view

namespace nmtools::meta
{
    // TODO: remove
    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct is_dynamic_ndarray< 
        view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t>
    >
    {
        static constexpr auto value = [](){
            if (is_fixed_index_array_v<shape_t> || is_constant_index_array_v<shape_t> || is_hybrid_index_array_v<shape_t>) {
                return false;
            } else /* if (is_index_array_v<shape_t>) */ {
                return true;
            }
        }();
    }; // is_dynamic_ndarray

    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct fixed_size<
        view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t>
    >
    {
        using view_type  = view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t >;
        using shape_type = decltype(declval<view_type>().shape());
        using size_type  = decltype(declval<view_type>().size());

        static constexpr auto value = [](){
            // broadcast may change shape, so change size
            if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else if constexpr (is_constant_index_v<size_type>) {
                return size_type::value;
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct bounded_size<
        view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t>
    >
    {
        using view_type  = view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t >;
        using shape_type = decltype(declval<view_type>().shape());
        using size_type  = decltype(declval<view_type>().size());

        static constexpr auto value = [](){
            // broadcast may change shape, so change size
            if constexpr (is_constant_index_array_v<shape_type> || is_clipped_index_array_v<shape_type>) {
                return index::product(to_value_v<shape_type>);
            } else if constexpr (is_constant_index_v<size_type> || is_clipped_integer_v<size_type>) {
                constexpr auto size = to_value_v<size_type>;
                return size;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    };

    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct fixed_dim<
        view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t>
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

    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct is_ndarray< view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t >>
    {
        static constexpr auto value = (is_ndarray_v<array_t> || is_num_v<array_t>) && is_index_array_v<shape_t>;
    };

    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct is_num< view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t >>
    {
        static constexpr auto value = is_num_v<array_t> && is_none_v<shape_t>;
    };

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_BROADCAST_TO_HPP