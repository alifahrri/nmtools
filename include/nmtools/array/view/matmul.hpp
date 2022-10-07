#ifndef NMTOOLS_ARRAY_VIEW_MATMUL_HPP
#define NMTOOLS_ARRAY_VIEW_MATMUL_HPP

#include "nmtools/array/index/matmul.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view
{
    /**
     * @brief Matmul view type constructor.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct matmul_t
    {
        using operands_type = detail::get_operands_type_t<lhs_t,rhs_t>;
        using array_type    = operands_type;
        using lhs_elem_type = meta::get_element_type_t<lhs_t>;
        using rhs_elem_type = meta::get_element_type_t<rhs_t>;
        using result_type   = meta::common_type_t<lhs_elem_type,rhs_elem_type>;
        using lhs_shape_type = decltype(nmtools::shape<true>(meta::declval<lhs_t>()));
        using rhs_shape_type = decltype(nmtools::shape<true>(meta::declval<rhs_t>()));
        using dst_shape_type = meta::resolve_optype_t<index::shape_matmul_t,lhs_shape_type,rhs_shape_type>;

        operands_type operands;
        dst_shape_type shape_;

        // the following is needed because cant use view::initialize<...>
        // can't handle tuple yet
        static constexpr auto initialize_operands(const lhs_t& lhs, const rhs_t& rhs)
        {
            using op_lhs_t = meta::at_t<operands_type,0>;
            using op_rhs_t = meta::at_t<operands_type,1>;
            if constexpr (meta::is_pointer_v<op_lhs_t> && meta::is_pointer_v<op_rhs_t>) {
                return operands_type{&lhs,&rhs};
            } else if constexpr (meta::is_pointer_v<op_lhs_t>) {
                return operands_type{&lhs,rhs};
            } else if constexpr (meta::is_pointer_v<op_rhs_t>) {
                return operands_type{lhs,&rhs};
            } else {
                return operands_type{lhs,rhs};
            }
        } // initialize_operands

        constexpr matmul_t(const lhs_t& lhs, const rhs_t& rhs)
            : operands(initialize_operands(lhs,rhs))
            , shape_(*index::shape_matmul(
                nmtools::shape<true>(lhs),
                nmtools::shape<true>(rhs))
            )
        {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto view_at(const size_types&...indices) const
        {
            const auto& lhs = nmtools::get<0>(operands);
            const auto& rhs = nmtools::get<1>(operands);
            using lhs_type  = meta::remove_cvref_t<decltype(lhs)>;
            using rhs_type  = meta::remove_cvref_t<decltype(rhs)>;

            const auto packed_indices = pack_indices(indices...);
            const auto ashape   = detail::shape(lhs);
            const auto bshape   = detail::shape(rhs);
            auto indices_       = detail::matmul(packed_indices,ashape,bshape,shape());
            auto l_slice_indices = at(indices_,meta::ct_v<0>);
            auto r_slice_indices = at(indices_,meta::ct_v<1>);

            auto l_slice = [&](){
                if constexpr (meta::is_pointer_v<lhs_type>) {
                    return apply_slice(*lhs, l_slice_indices);
                } else {
                    return apply_slice(lhs, l_slice_indices);
                }
            }();
            auto r_slice = [&](){
                if constexpr (meta::is_pointer_v<rhs_type>) {
                    return apply_slice(*rhs, r_slice_indices);
                } else {
                    return apply_slice(rhs, r_slice_indices);
                }
            }();
            // element multiplication with broadcasting
            auto multiplied = multiply(l_slice,r_slice);
            auto reduced    = reduce_add(multiplied,/*axis=*/None);
            return reduced;
        } // view_at

        template <typename...size_types>
        constexpr auto operator()(const size_types&...indices) const
        {
            auto reduced = view_at(indices...);
            // reduced must be num type
            // the return must be result_type
            return static_cast<result_type>(reduced);
        } // operator()
    }; // matmul_t

    /**
     * @brief Create a view representing matrix product of two arrays.
     * 
     * This view should behave like numpy's matmul,
     * The axis -2..0 are broadcasted.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename lhs_t, typename rhs_t>
    constexpr auto matmul(const lhs_t& lhs, const rhs_t& rhs)
    {
        // TODO: support ufunc datatype promotions
        using view_t = decorator_t<matmul_t, lhs_t, rhs_t>;
        return view_t{{lhs,rhs}};
    } // matmul
} // nmtools::view

namespace nmtools::meta
{

    /**
     * @brief Infer return type of matmul
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct get_element_type<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        using type = typename view::matmul_t<lhs_t,rhs_t>::result_type;
    }; // get_element_type

    template <typename lhs_t, typename rhs_t>
    struct is_ndarray<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_t> && is_ndarray_v<rhs_t>;
    }; // is_ndarray

    /**
     * @brief Infer the maximum size of the resulting matmul, at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct bounded_size<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_bounded_size_v<lhs_t> && is_bounded_size_v<rhs_t>) {
                // worst case maximum value
                return bounded_size_v<lhs_t> * bounded_size_v<rhs_t>;
            } else if constexpr (is_fixed_shape_v<lhs_t> && is_bounded_size_v<rhs_t>) {
                constexpr auto shape = fixed_shape_v<lhs_t>;
                return index::product(shape) * bounded_size_v<rhs_t>;
            } else if constexpr (is_bounded_size_v<lhs_t> && is_fixed_shape_v<rhs_t>) {
                constexpr auto shape = fixed_shape_v<rhs_t>;
                return index::product(shape) * bounded_size_v<lhs_t>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view::decorator_t< view::matmul_t, lhs_t, rhs_t >>{};
            }
        }();
    }; // bounded_size

    template <typename lhs_t, typename rhs_t>
    struct fixed_size<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        using view_type  = view::decorator_t< view::matmul_t, lhs_t, rhs_t >;
        using shape_type = typename view_type::dst_shape_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_array_v<shape_type>) {
                return index::product(shape_type{});
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_MATMUL_HPP