#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_UFUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/index/outer.hpp"
#include "nmtools/array/index/remove_dims.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/array/view/ufunc/detail.hpp"

namespace nmtools::view
{
    /**
     * @brief An ufunc type constructor to specialize handling on scalar type.
     * 
     * Note: since using sfinae on decorator_t with ufunc_t is rather painful,
     * make specific class instead. The decision logic on which type constructor
     * to be called (ufunc_t or scalar_ufunc_t) is performed from ufunc function instead.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename...arrays_t>
    struct scalar_ufunc_t
    {
        // dont take reference for the operands, a Num type should be copied
        // and view type should be cheap to copy
        using operands_type = meta::make_tuple_type_t<arrays_t...>;
        using array_type    = operands_type;
        using op_type       = op_t;
        using result_type   = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;

        op_type op;
        operands_type operands;

        constexpr scalar_ufunc_t(op_type op, const arrays_t&...arrays)
            : op(op), operands{arrays...} {}
        
        constexpr auto dim() const noexcept
        {
            // TODO: use constant index
            return 0;
        } // dim

        constexpr auto shape() const noexcept
        {
            return None;
        } // shape

        constexpr auto size() const noexcept
        {
            return meta::ct_v<1ul>;
        }

        template <size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, meta::index_sequence<Is...>)
        {
            return op(nmtools::get<Is>(operands)...);
        } // apply_at

        constexpr operator result_type() const
        {
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, operands, meta::make_index_sequence<N>{});
        } // operator result_type()
    }; // scalar_ufunc_t

    /**
     * @brief A type constructor for actual ufuncs.
     *
     * The number of arrays passed must be matched with op's arity.
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct ufunc_t
    {
        using operands_type = detail::get_operands_type_t<arrays_t...>;
        using array_type = operands_type;
        using op_type = op_t;
        using result_type = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;

        op_type op;
        operands_type operands;

        // the following is needed because cant use view::initialize<...>
        // can't handle tuple yet
        static constexpr auto initialize_operands(const arrays_t&...arrays)
        {
            if constexpr (sizeof...(arrays) > 1) {
                // take the original referenced array as const ref,
                // may be transformed to pointer later
                using tuple_t = meta::make_tuple_type_t<const arrays_t&...>;
                auto tuple = tuple_t{arrays...};
                // the following may transform to tuple of pointer / tuple of value
                return meta::template_reduce<sizeof...(arrays)>([&](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    using arg_t  = meta::at_t<operands_type,i>;
                    using init_t = meta::remove_cvref_t<decltype(init)>;
                    // for each element in operands,
                    // dispatch based on take ref or not
                    auto arg = [&]() -> arg_t {
                        if constexpr (meta::is_pointer_v<arg_t>) {
                            return &nmtools::get<i>(tuple);
                        } else {
                            return nmtools::get<i>(tuple);
                        }
                    }();
                    if constexpr (is_none_v<init_t>) {
                        using tuple = meta::make_tuple_type_t<arg_t>;
                        return tuple{arg};
                    } else {
                        using tuple = meta::make_tuple_type_t<arg_t>;
                        return detail::tuple_cat(init,tuple{arg});
                    }
                }, None);
            } else {
                using array_t = meta::at_t<operands_type,0>;
                if constexpr (meta::is_pointer_v<array_t>) {
                    return operands_type{&arrays...};
                } else {
                    return operands_type{arrays...};
                }
            }
        } // initialize_operands

        constexpr ufunc_t(op_type op, const arrays_t&...operands)
            : op(op), operands(initialize_operands(operands...)) {}
        
        constexpr auto shape() const
        {
            // assume arrays is already broadcasted together
            return detail::shape<true>(nmtools::get<0>(operands));
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return detail::dim(nmtools::get<0>(operands));
        } // dim

        template <typename indices_t, size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, const indices_t& indices, meta::index_sequence<Is...>)
        {
            using view::detail::apply_at;
            return op(detail::apply_at(nmtools::get<Is>(operands),indices)...);
        } // apply_at

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, operands, indices_, meta::make_index_sequence<N>{});
        } // operator()
    }; // ufunc_t
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Scalar ufunc is num
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct is_num<
        view::decorator_t< view::scalar_ufunc_t, op_t, arrays_t... >
    >
    {
        static constexpr auto value = true;
    }; // is_num

    /**
     * @brief Element type deduction for scalar_ufunc_t
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct get_element_type<
        view::decorator_t< view::scalar_ufunc_t, op_t, arrays_t... >
    >
    {
        using view_t = view::decorator_t< view::scalar_ufunc_t, op_t, arrays_t... >;
        using type = typename view_t::result_type;
    }; // is_num

    /**
     * @brief Specialization of hybrid_ndarray_max_size for ufunc view.
     *
     * Note that when this meta fn returns not Fail results,
     * is_hybrid_ndarray concept should be true.
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct hybrid_ndarray_max_size< view::decorator_t<view::ufunc_t, op_t,arrays_t...> >
    {
        static inline constexpr auto value = [](){
            if constexpr ((is_hybrid_ndarray_v<arrays_t> && ...)) {
                using types = meta::make_tuple_type_t<arrays_t...>;
                return template_reduce<sizeof...(arrays_t)>([](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    using type = at_t<types,i>;
                    constexpr auto s = hybrid_ndarray_max_size_v<type>;
                    return (init > s ? init : s);
                }, 0ul);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // hybrid_ndarray_max_size

    /**
     * @brief Infer the dimension of ufunc at compile-time.
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct fixed_dim< view::decorator_t<view::ufunc_t, op_t,arrays_t...> >
    {
        static inline constexpr auto value = [](){
            if constexpr ((is_fixed_dim_ndarray_v<arrays_t> && ...)) {
                constexpr auto all_same_dim = (fixed_dim_v<arrays_t> == ...);
                if constexpr (static_cast<bool>(all_same_dim)) {
                    using types = meta::make_tuple_type_t<arrays_t...>;
                    auto ref_dim  = fixed_dim_v<at_t<types,0>>;
                    return ref_dim;
                }
                else return detail::Fail;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: consider to use fail type to indicate fail instead of void
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    }; // fixed_dim

    /**
     * @brief Specialization of fixed_ndarray_shape for ufunc view,
     * Infer the shape of ufunc at compile-time.
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct fixed_ndarray_shape< view::ufunc_t<op_t,arrays_t...> >
    {
        static inline constexpr auto value = [](){
            using array_types = type_list<arrays_t...>;
            // check if all arrays is fixed shape
            // NOTE: somehow if constexpr with fold expression doesnt work, use template_for instead
            constexpr auto all_fixed_shape = [](){
                auto all_fixed = true;
                template_for<sizeof...(arrays_t)>([&all_fixed](auto index){
                    constexpr auto I = decltype(index)::value;
                    using type = type_list_at_t<I,array_types>;
                    all_fixed = all_fixed && is_fixed_size_ndarray_v<type>;
                });
                return all_fixed;
            }();
            // if all array is fixed shape, check if all array shapes can be broadcasted together
            // note that broadcast_shape doesn't support unary
            if constexpr (all_fixed_shape && (sizeof...(arrays_t) > 1)) {
                constexpr auto broadcasted_shape = index::broadcast_shape(fixed_ndarray_shape_v<arrays_t>...);
                constexpr auto success = at(broadcasted_shape,ct_v<0>);
                if constexpr (success) {
                    return at(broadcasted_shape,ct_v<1>);
                } else {
                    return detail::Fail;
                }
            } else if constexpr (all_fixed_shape) {
                // unary ufunc
                return fixed_ndarray_shape_v<type_list_at_t<0,array_types>>;
            } else {
                // otherwise return fail
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename op_t, typename...arrays_t>
    struct is_ndarray< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {
        static constexpr auto value = (is_ndarray_v<arrays_t> && ...);
    };

    template <typename op_t, typename...arrays_t>
    struct get_element_type<
        view::decorator_t< view::ufunc_t, op_t, arrays_t... >
    >
    {
        using type = typename view::ufunc_t<op_t, arrays_t...>::result_type;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_UFUNC_UFUNC_HPP