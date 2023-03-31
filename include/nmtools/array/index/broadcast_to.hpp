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

    struct shape_broadcast_to_free_axes_t {};

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
        if constexpr (is_none_v<bshape_t>) {
            #if 1
            return nmtools_tuple<bool,none_t,none_t>{true,None,None};
            #else
            // broken on c++ for opencl 😭
            // error: field may not be qualified with an address space
            return nmtools_tuple{true,None,None};
            #endif
        } else {
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
        }
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
        using result_t    = meta::resolve_optype_t<shape_broadcast_to_t,ashape_t,bshape_t>;
        using free_axes_t = meta::resolve_optype_t<shape_broadcast_to_free_axes_t,result_t>;

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
        if constexpr (meta::is_resizable_v<result_t>) {
            res.resize(bdim);
        }
        if constexpr (meta::is_resizable_v<free_axes_t>) {
            free_axes.resize(bdim);
        }
        
        auto shape_broadcast_to_impl = [&](auto i){
            using idx_t [[maybe_unused]] = meta::make_signed_t<decltype(adim-i-1)>;
            auto ai = [&](){
                constexpr auto LEN_A = meta::len_v<ashape_t>;
                if constexpr (meta::is_constant_index_v<decltype(i)> && (LEN_A > 0)) {
                    return meta::ct_v<(int)LEN_A-(int)decltype(i)::value-1>;
                } else {
                    return idx_t(adim - i - 1);
                }
            }();
            auto bi = [&](){
                constexpr auto LEN_B = meta::len_v<bshape_t>;
                if constexpr (meta::is_constant_index_v<decltype(i)> && (LEN_B > 0)) {
                    return meta::ct_v<(int)LEN_B-i-1>;
                } else {   
                    return idx_t(bdim - i - 1);
                }
            }();
            // handle bshape if constant index array;
            // TODO: move constant index handling at higher level, see remove_dims for example
            [[maybe_unused]]
            auto get_b = [&](){
                if constexpr (meta::is_constant_index_array_v<bshape_t>)
                    return at(meta::to_value_v<bshape_t>,bi);
                else return tuple_at(bshape,bi);
            };
            // Use ai and bi as param, to make call to (at) depends on type
            // which in turn allowing to avoid instantiation of runtime version
            [[maybe_unused]]
            auto non_free_axes_impl = [&](auto ai, auto bi){
                // prefer get_element_type over decltype(a),
                // to avoid weird deduction, such as vector of bool
                using a_t = meta::get_element_or_common_type_t<ashape_t>;
                using b_t = meta::get_element_or_common_type_t<bshape_t>;
                auto a = at(ashape,ai);
                auto b = at(bshape,bi);
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
            };
            [[maybe_unused]]
            auto free_axes_impl = [&](){
                at(res,bi) = at(bshape,bi);
                at(free_axes,bi) = true;
            };

            // To avoid instantiating runtime version of non_free_axes_impl
            // when using template_for
            if constexpr (meta::is_constant_index_v<decltype(ai)>) {
                constexpr auto AI = decltype(ai)::value;
                if constexpr (AI < 0) {
                    free_axes_impl();
                } else {
                    non_free_axes_impl(ai,bi);
                }
            } else {
                if (ai<0) {
                    free_axes_impl();
                }
                // unlike broadcast_shape, we dont do this here
                // else if (bi < 0)
                //     at(res,si) = tuple_at(ashape,ai);
                else {
                    non_free_axes_impl(ai,bi);
                }
            }
        }; // shape_broadcast_to_impl

        if constexpr (meta::is_tuple_v<result_t>) {
            constexpr auto N = meta::len_v<result_t>;
            meta::template_for<N>([&](auto i){
                if (!success)
                    return;
                shape_broadcast_to_impl(i);
            });
        } else {
            for (size_t i=0; i<(size_t)len(res); i++) {
                if (!success)
                    break;
                shape_broadcast_to_impl(i);
            }
        }

        // - res will have dimension same with bshape, which is the target shape,
        // - free_axes has same len with res,
        // - free_axes value indicates wether the corresponding indices are free (either empty or 1).
        // - free_axes is useful to perform the reverse operation.
        // TODO: use optional instead
        return nmtools_tuple{success, res, free_axes};
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
    namespace error
    {
        template<typename...>
        struct SHAPE_BROADCAST_TO_UNSUPPORTED : detail::fail_t {};

        template<typename...>
        struct SHAPE_BROADCAST_TO_FREE_AXES_UNSUPPORTED : detail::fail_t {};
    }

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
            using element_t = remove_cvref_t<get_index_element_type_t<bshape_t>>;
            // specialize when both lhs and rhs is constant index array
            // also make sure the resulting type's element type is not constant index
            if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                constexpr auto M = len_v<bshape_t>;
                using result_t = nmtools_array<element_t,M>;
                return as_value_v<result_t>;
            }
            else if constexpr (
                is_index_array_v<ashape_t>
                && is_clipped_index_array_v<bshape_t>
            ) {
                return as_value_v<bshape_t>;
            }
            else if constexpr (
                is_clipped_index_array_v<ashape_t> // TODO: relax this requirement to just is_index_array
                && is_constant_index_array_v<bshape_t>
            ) {
                // return as clipped shape:
                // keep info about max size
                // but still compatible with current runtime impl
                constexpr auto bshape = to_value_v<bshape_t>;
                using nmtools::len, nmtools::at;
                return template_reduce<len(bshape)-1>([&](auto init, auto index){
                    using init_type = type_t<decltype(init)>;
                    using type = append_type_t<init_type,clipped_size_t<at(bshape,index+1)>>;
                    return as_value_v<type>;
                }, as_value_v<nmtools_tuple<clipped_size_t<at(bshape,0)>>>);
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
            else if constexpr (is_index_array_v<ashape_t> && is_index_array_v<bshape_t>) {
                constexpr auto fixed_size = len_v<bshape_t>;
                [[maybe_unused]]
                constexpr auto bounded_size = bounded_size_v<bshape_t>;
                if constexpr (fixed_size > 0) {
                    using type = nmtools_array<element_t,fixed_size>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(bounded_size)>) {
                    using type = array::static_vector<element_t,bounded_size>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<element_t>;
                    return as_value_v<type>;
                }
            }
            else {
                using type = error::SHAPE_BROADCAST_TO_UNSUPPORTED<ashape_t,bshape_t>;
                return as_value_v<type>;
            }
        }();
        // unlike broadcast_shape,
        // for shape_broadcast_to, the resulting shape will follow bshape
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    template <typename shape_result_t>
    struct resolve_optype<
        void, index::shape_broadcast_to_free_axes_t, shape_result_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_index_array_v<shape_result_t>) {
                // TODO: try to replace element type instead
                constexpr auto N = len_v<shape_result_t>;
                constexpr auto b_dim = bounded_size_v<shape_result_t>;
                if constexpr (N>0) {
                    using type = array::static_vector<bool,N>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_dim)>) {
                    using type = array::static_vector<bool,b_dim>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<bool>;
                    return as_value_v<type>;
                }
            } else {
                return as_value_v<error::SHAPE_BROADCAST_TO_FREE_AXES_UNSUPPORTED<shape_result_t>>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP