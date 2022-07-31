#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/gather.hpp"
#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/logical_not.hpp"
#include "nmtools/array/index/nonzero.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve op type
     * 
     */
    struct shape_broadcast_to_t {};

    // TODO: cleanup index functions
    /**
     * @brief Overloaded version of shape_broadcast_to where the src shape is None (from num type).
     * 
     * @tparam bshape_t 
     * @param bshape    target shape
     * @return constexpr auto 
     */
    template <typename bshape_t>
    constexpr auto shape_broadcast_to(const none_t&, const bshape_t& bshape)
    {
        // TODO: create specific type resolver
        // TODO: only call transform array when necessary
        using result_t = meta::tuple_to_array_t<
            meta::transform_bounded_array_t<bshape_t>
        >;

        auto ret = result_t {};
        auto dim = len(bshape);

        if constexpr (meta::is_tuple_v<bshape_t>) {
            constexpr auto N = meta::len_v<bshape_t>;
            meta::template_for<N>([&](auto index){
                constexpr auto i = decltype(index)::value;
                at(ret,i) = at(bshape,meta::ct_v<i>);
            });
        } else {
            for (size_t i=0; i<(size_t)dim; i++)
                at(ret,i) = at(bshape,i);
        }

        using return_t = meta::make_tuple_type_t<bool,result_t,none_t>;
        return return_t{true,ret,None};
    } // shape_broadcast_to

    // TODO: refactor free_axes
    /**
     * @brief check if ashape can be broadcasted to bshape.
     *
     * Unidirectional broadcast from shape a to shape b.
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t>
    constexpr auto shape_broadcast_to(const ashape_t& ashape, const bshape_t& bshape)
    {
        using result_t = meta::resolve_optype_t<shape_broadcast_to_t,ashape_t,bshape_t>;
        using free_axes_t = meta::replace_element_type_t<result_t,bool>;

        auto res = result_t{};

        auto adim = len(ashape);
        auto bdim = len(bshape);

        // also track free axes
        auto free_axes = free_axes_t{};
        bool success = bdim >= adim;

        // for shape_broadcast_to, the dimension will follow input shape (bshape)
        // in numpy, the following will raises error
        // np.shape_broadcast_to(np.array([[1],[2],[3]]), (3,))
        // ValueError: input operand has more dimensions than allowed by the axis remapping
        // TODO: error handling for unsupported shape_broadcast_to dimension
        if constexpr (meta::is_resizeable_v<result_t>) {
            res.resize(bdim);
            free_axes.resize(bdim);
        }
        
        auto shape_broadcast_to_impl = [&](auto i){
            using idx_t = meta::make_signed_t<decltype(adim-i-1)>;
            idx_t ai = adim - i - 1;
            idx_t bi = bdim - i - 1;
            // handle bshape if constant index array;
            // TODO: move constant index handling at higher level, see remove_dims for example
            auto get_b = [&](){
                if constexpr (meta::is_constant_index_array_v<bshape_t>)
                    return at(meta::to_value_v<bshape_t>,bi);
                else return tuple_at(bshape,bi);
            };
            if (ai<0) {
                at(res,bi) = get_b();
                at(free_axes,bi) = true;
            }
            // unlike broadcast_shape, we dont do this here
            // else if (bi < 0)
            //     at(res,si) = tuple_at(ashape,ai);
            else {
                // prefer get_element_type over decltype(a),
                // to avoid weird deduction, such as vector of bool
                using a_t = meta::get_element_or_common_type_t<ashape_t>;
                using b_t = meta::get_element_or_common_type_t<bshape_t>;
                // TODO: do not use tuple at
                auto a = tuple_at(ashape,ai);
                auto b = get_b();
                using common_t = meta::promote_index_t<a_t,b_t>;
                if (static_cast<common_t>(a)==static_cast<common_t>(b)) {
                    at(res,bi) = a;
                    at(free_axes,bi) = false;
                }
                else if (a==1) {
                    at(res,bi) = b;
                    at(free_axes,bi) = true;
                }
                else
                    success = false;
            }
        }; // shape_broadcast_to_impl

        for (size_t i=0; i<(size_t)len(res); i++) {
            if (!success)
                break;
            shape_broadcast_to_impl(i);
        }

        // - res will have dimension same with bshape, which is the target shape,
        // - free_axes has same len with res,
        // - free_axes value indicates wether the corresponding indices are free (either empty or 1).
        // - free_axes is useful to perform the reverse operation.
        // TODO: use optional instead
        return nmtools_tuple{success, res, free_axes};
    } // shape_broadcast_to

    /**
     * @brief Specialization for shape_broadcast_to function.
     * 
     * Shape of Num type is represented as None,
     * broadcasting num to None should always be successful.
     * 
     * @tparam  
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template<>
    constexpr auto shape_broadcast_to<none_t,none_t>(const none_t&, const none_t&)
    {
        // TODO: use optional instead
        return nmtools_tuple{true,None,None};
    } // shape_broadcast_to

    template <typename indices_t, typename src_shape_t, typename dst_shape_t, typename origin_axes_t>
    constexpr auto broadcast_to(const indices_t& indices, const src_shape_t& src_shape, const dst_shape_t& dst_shape, const origin_axes_t& origin_axes)
    {
        // compute the offset while ignoring "broadcasted axes"
        // which is either 1 or empty according to the broadcasting rules
        // then transform back the offset to with respect to original shape (src_shape).

        // NOTE: the following are suspect to be hot-spot
        // since broadcasting is almost used everywhere
        // TODO: measure and inspect if this can be optimized

        auto origin_shape   = gather(dst_shape,origin_axes);
        auto origin_strides = compute_strides(origin_shape);
        auto origin_indices = gather(indices,origin_axes);

        auto offset = compute_offset(origin_indices,origin_strides);
        return compute_indices(offset,src_shape);
    } // broadcast_to

    /**
     * @brief Overloaded version of broadcast_to that takes no origin_axes.
     * 
     * @tparam indices_t 
     * @tparam src_shape_t 
     * @tparam dst_shape_t 
     * @param indices 
     * @param src_shape 
     * @param dst_shape 
     * @return constexpr auto 
     */
    template <typename indices_t, typename src_shape_t, typename dst_shape_t>
    constexpr auto broadcast_to(const indices_t& indices, const src_shape_t& src_shape, const dst_shape_t& dst_shape)
    {
        const auto [success, shape_, free] = shape_broadcast_to(src_shape,dst_shape);
        auto not_free    = logical_not(free);
        auto origin_axes = nonzero(not_free);

        return broadcast_to(indices,src_shape,dst_shape,origin_axes);
    } // broadcast_to
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type of index::shape_shape_broadcast_to
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    template <typename ashape_t, typename bshape_t>
    struct resolve_optype <
        void, index::shape_broadcast_to_t, ashape_t, bshape_t
    >
    {
        static constexpr auto vtype = [](){
            // bshape_t (target shape) may be raw or tuple
            using type = tuple_to_array_t<transform_bounded_array_t<bshape_t>>;
            using element_t = remove_cvref_t<get_element_type_t<type>>;
            // specialize when both lhs and rhs is constant index array
            // also make sure the resulting type's element type is not constant index
            if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                constexpr auto M = len_v<bshape_t>;
                using new_type_t = element_t;
                if constexpr (is_constant_index_v<new_type_t>) {
                    using result_t = make_array_type_t<typename new_type_t::value_type,M>;
                    return as_value_v<result_t>;
                }
                else {
                    // TODO: when does this happen?
                    using result_t = make_array_type_t<new_type_t,M>;
                    return as_value_v<result_t>;
                }
            }
            // TODO: enable this, make maybe type, if at runtime doesn't match then nothing
            // else if constexpr (is_constant_index_array_v<bshape_t>) {
            //     return as_value_v<bshape_t>;
            // }
            else if constexpr (is_constant_index_array_v<ashape_t>) {
                // simply recurse on value
                using type = resolve_optype_t<index::shape_broadcast_to_t,remove_cvref_t<decltype(to_value_v<ashape_t>)>,bshape_t>;
                return as_value_v<type>;
            }
            // make sure the resulting type's element type is not constant index
            else if constexpr (is_fixed_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                // src's shape type may be raw or tuple
                constexpr auto N = len_v<bshape_t>;
                using ashape_type = tuple_to_array_t<transform_bounded_array_t<ashape_t>>;
                using shape_type  = resize_fixed_index_array_t<ashape_type,N>;
                if constexpr (is_constant_index_v<element_t>) {
                    using type  = replace_element_type_t<shape_type,typename element_t::value_type>;
                    return as_value_v<type>;
                }
                else {
                    using type  = replace_element_type_t<shape_type,element_t>;
                    return as_value_v<type>;
                }
            }
            else if constexpr (is_fixed_size_v<ashape_t> && is_bounded_size_v<bshape_t>) {
                constexpr auto fixed_size = fixed_size_v<bshape_t>;
                if constexpr (!is_fail_v<decltype(fixed_size)>) {
                    using type = resize_size_t<ashape_t,fixed_size>;
                    return as_value_v<type>;
                } else {
                    using type = replace_element_type_t<bshape_t,get_element_or_common_type_t<ashape_t>>;
                    return as_value_v<type>;
                }
            }
            else if constexpr (is_bounded_size_v<ashape_t> && is_bounded_size_v<bshape_t>) {
                // for "unidirectional broadcasting": prefer rhs size
                [[maybe_unused]] constexpr auto bounded_a_size = bounded_size_v<ashape_t>;
                [[maybe_unused]] constexpr auto bounded_b_size = bounded_size_v<bshape_t>;
                // still can't be sure at compile-time since size can be smaller at runtime
                // TODO: resize instead of make new type
                using type = resize_bounded_size_t<ashape_t,bounded_b_size>;
                return as_value_v<type>;
            }
            // make sure the resulting type's element type is not constant index
            else if constexpr (is_constant_index_array_v<bshape_t>) {
                using ashape_type = tuple_to_array_t<transform_bounded_array_t<ashape_t>>;
                if constexpr (is_constant_index_v<element_t>) {
                    using type  = replace_element_type_t<ashape_type,typename element_t::value_type>;
                    return as_value_v<type>;
                }
                else {
                    using type  = replace_element_type_t<ashape_type,element_t>;
                    return as_value_v<type>;
                }
            }
            else return as_value_v<type>;
        }();
        // unlike broadcast_shape,
        // for shape_broadcast_to, the resulting shape will follow bshape
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP