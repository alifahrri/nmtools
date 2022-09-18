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

        operands_type operands;

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
            : operands(initialize_operands(lhs,rhs)) {}
        
        constexpr auto shape() const
        {
            const auto ashape = detail::shape(nmtools::get<0>(operands));
            const auto bshape = detail::shape(nmtools::get<1>(operands));
            // must has value
            return *detail::shape_matmul(ashape,bshape);
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
            auto lslice_indices = at(indices_,meta::ct_v<0>);
            auto rslice_indices = at(indices_,meta::ct_v<1>);

            auto lslice = [&](){
                if constexpr (meta::is_pointer_v<lhs_type>) {
                    return apply_slice(*lhs, lslice_indices);
                } else {
                    return apply_slice(lhs, lslice_indices);
                }
            }();
            auto rslice = [&](){
                if constexpr (meta::is_pointer_v<rhs_type>) {
                    return apply_slice(*rhs, rslice_indices);
                } else {
                    return apply_slice(rhs, rslice_indices);
                }
            }();
            // element multiplication with broadcasting
            auto multiplied = multiply(lslice,rslice);
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
     * @brief Infre return type of matmul
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
     * @brief Infer the resulting shape of matmul at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct fixed_ndarray_shape<
        view::matmul_t< lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<lhs_t> && is_fixed_size_ndarray_v<rhs_t>) {
                constexpr auto lhs_shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto rhs_shape = fixed_ndarray_shape_v<rhs_t>;
                constexpr auto shape = view::detail::shape_matmul(lhs_shape,rhs_shape);
                if constexpr (static_cast<bool>(shape)) {
                    return shape.value();
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the maximum size of the resulting matmul, at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_hybrid_ndarray_v<lhs_t> && is_hybrid_ndarray_v<rhs_t>) {
                // worst case maximum value
                return hybrid_ndarray_max_size_v<lhs_t> * hybrid_ndarray_max_size_v<rhs_t>;
            } else if constexpr (is_fixed_size_ndarray_v<lhs_t> && is_hybrid_ndarray_v<rhs_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<lhs_t>;
                return index::product(shape) * hybrid_ndarray_max_size_v<rhs_t>;
            } else if constexpr (is_hybrid_ndarray_v<lhs_t> && is_fixed_size_ndarray_v<rhs_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<rhs_t>;
                return index::product(shape) * hybrid_ndarray_max_size_v<lhs_t>;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: simplify is_ndarray default deduction
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // hybrid_ndarray_max_size

    /**
     * @brief Infer the resulting dimension of matmul, at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct fixed_dim<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_dim_ndarray_v<lhs_t> && is_fixed_dim_ndarray_v<rhs_t>) {
                // simply take maximum
                constexpr auto ldim = fixed_dim_v<lhs_t>;
                constexpr auto rdim = fixed_dim_v<rhs_t>;
                return (ldim > rdim ? ldim : rdim); 
            } else {
                return detail::Fail;
            }
        }();
        // TODO: consider to use fail type to indicate fail instead of void
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    }; // fixed_dim
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_MATMUL_HPP