#ifndef NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve op type
     * 
     */
    struct broadcast_to_t {};

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
    constexpr auto broadcast_to(const ashape_t& ashape, const bshape_t& bshape)
    {
        using return_t = meta::resolve_optype_t<broadcast_to_t,ashape_t,bshape_t>;
        using free_axes_t = meta::replace_element_type_t<return_t,bool>;

        auto res = return_t{};

        auto adim = tuple_size(ashape);
        auto bdim = tuple_size(bshape);

        // also track free axes
        auto free_axes = free_axes_t{};
        bool success = bdim >= adim;

        // for broadcast_to, the dimension will follow input shape (bshape)
        // in numpy, the following will raises error
        // np.broadcast_to(np.array([[1],[2],[3]]), (3,))
        // ValueError: input operand has more dimensions than allowed by the axis remapping
        if constexpr (meta::is_resizeable_v<return_t>) {
            res.resize(bdim);
            free_axes.resize(bdim);
        }
        
        auto broadcast_to_impl = [&](auto i){
            using idx_t = std::make_signed_t<decltype(adim-i-1)>;
            idx_t ai = adim - i - 1;
            idx_t bi = bdim - i - 1;
            // handle bshape if constant index array;
            // TODO: find out better way
            auto get_b = [&](){
                if constexpr (meta::is_constant_index_array_v<bshape_t>)
                    return tuple_at(meta::constant_to_value_v<bshape_t>,bi);
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
                auto a = tuple_at(ashape,ai);
                auto b = get_b();
                if (a==b) {
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
        }; // broadcast_to_impl

        for (int i=0; i<size(res); i++) {
            if (!success)
                break;
            broadcast_to_impl(i);
        }

        // - res will have dimension same with bshape, which is the target shape,
        // - free_axes has same len with res,
        // - free_axes value indicates wether the corresponding indices are free (either empty or 1).
        // - free_axes is useful to perform the reverse operation.
        return std::tuple{success, res, free_axes};
    } // broadcast_to

    /**
     * @brief Specialization for broadcast_to function.
     * 
     * Shape of Num type is represented as None,
     * broadcasting num to None should always be successfull.
     * 
     * @tparam  
     * @param ashape 
     * @param bshape 
     * @return constexpr auto 
     */
    template<>
    constexpr auto broadcast_to<none_t,none_t>(const none_t& ashape, const none_t& bshape)
    {
        return std::tuple{true,None,None};
    } // broadcast_to
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type of index::broadcast_to
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     */
    template <typename ashape_t, typename bshape_t>
    struct resolve_optype <
        void, index::broadcast_to_t, ashape_t, bshape_t
    >
    {
        static constexpr auto vtype = [](){
            // bshape_t (target shape) may be raw or tuple
            using type = tuple_to_array_t<transform_bounded_array_t<bshape_t>>;
            using element_t = get_element_type_t<type>;
            // specialize when both lhs and rhs is constant index array
            // also make sure the resulting type's element type is not contant index
            if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                constexpr auto N = len_v<ashape_t>;
                constexpr auto M = len_v<bshape_t>;
                using new_type_t = element_t;
                if constexpr (is_constant_index_v<new_type_t>) {
                    using return_t = std::array<typename new_type_t::value_type,M>;
                    return as_value_v<return_t>;
                }
                else {
                    using return_t = std::array<new_type_t,M>;
                    return as_value_v<return_t>;
                }
            }
            // make sure the resulting type's element type is not contant index
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
            // make sure the resulting type's element type is not contant index
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
        // for broadcast_to, the resulting shape will follow bshape
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_BROADCAST_TO_HPP