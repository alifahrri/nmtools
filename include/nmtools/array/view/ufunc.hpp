#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_HPP

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
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"

#include <tuple>
#include <variant>

// seems like constexpr math is in the library level,
// TODO: deduce std library implementation instead of compiler to decide constexpr
// clang doesn't support constexpr math while gcc does
#if defined(__GNUC__) && !defined(__clang__) && !defined(NMTOOLS_UFUNC_CONSTEXPR)
#define NMTOOLS_UFUNC_CONSTEXPR constexpr
#else
#define NMTOOLS_UFUNC_CONSTEXPR
#endif

namespace nmtools::view::detail
{
    /**
     * @brief helper metafunction to deduce the operand types for ufunc,
     * dont take reference for 'view' objects/simple number.
     * 
     * @tparam always_void 
     * @tparam arrays_t 
     */
    template <typename always_void, typename...arrays_t>
    struct get_operands_type
    {
        static_assert( sizeof...(arrays_t) > 0, "nmtools internal error" );
        static constexpr auto vtype = [](){
            using arrays_type = std::tuple<arrays_t...>;
            // for view / num type: simply copy (take value),
            // otherwise take reference
            return meta::template_reduce<sizeof...(arrays_t)>([](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                using array_t    = meta::at_t<arrays_type,i>;
                using operand_t  = view::resolve_array_type_t<array_t>;
                using init_t = meta::type_t<decltype(init)>; 
                if constexpr (std::is_void_v<init_t>) {
                    return meta::as_value_v<std::tuple<operand_t>>;
                } else {
                    return meta::as_value_v<meta::append_type_t<init_t,operand_t>>;
                }
            }, meta::as_value_v<void>);
        }();
        using type = meta::type_t<decltype(vtype)>;
    }; // get_operands_type

    template <typename...arrays_t>
    using get_operands_type_t = meta::type_t<get_operands_type<void,arrays_t...>>;

    /**
     * @brief Helper trait to check if type T has member type `result_type`
     * 
     * @tparam T type to check
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct has_result_type : std::false_type {};

    template <typename T>
    struct has_result_type<T,std::void_t<typename T::result_type>> : std::true_type {};

    template <typename T>
    constexpr inline auto has_result_type_v = has_result_type<T>::value;

    /**
     * @brief Helper metafunction to deduce the return type from op an args for ufuncs.
     * 
     * @tparam always_void 
     * @tparam op_t 
     * @tparam args_t 
     */
    template <typename always_void, typename op_t, typename...args_t>
    struct get_ufunc_result_type
    {
        using type = decltype(std::declval<op_t>()(std::declval<args_t>()...));
    }; // get_ufunc_result_type

    template <typename op_t, typename...args_t>
    struct get_ufunc_result_type<
        std::void_t<typename op_t::result_type>,
        op_t, args_t...
    >
    {
        using type = typename op_t::result_type;
    }; // get_ufunc_result_type

    template <typename op_t, typename...args_t>
    using get_ufunc_result_type_t = typename get_ufunc_result_type<void,op_t,args_t...>::type;

    /**
     * @brief Helper metafunction to deduce the type of reduce operations.
     * 
     * @tparam reducer_t 
     * @tparam element_t 
     * @tparam typename 
     */
    template <typename reducer_t, typename element_t, typename=void>
    struct get_reducer_result_type
    {
        using type = element_t;
    }; // get_reducer_result_type

    template <typename reducer_t, typename element_t>
    struct get_reducer_result_type< reducer_t, element_t,
        std::void_t<typename reducer_t::result_type>
    >
    {
        using type = typename reducer_t::result_type;
    }; // get_reducer_result_type

    template <typename reducer_t, typename element_t>
    using get_reducer_result_type_t = typename get_reducer_result_type<reducer_t,element_t>::type;

    /**
     * @brief helper type that wrapps type `T`, avoid constructing the actual type.
     * 
     * @tparam T 
     */
    template <typename T>
    struct type_wrapper
    {
        using type = T;
    }; // type_wrapper
        
    /**
     * @brief Get the result type of given op_type
     *
     * Prefer op_type::result_type when available, use element_t otherwise.
     * 
     * @tparam element_t 
     * @tparam op_type 
     */
    template <typename element_t, typename op_type>
    struct get_result_type
    {
        // for op type with explicit result_type member type, prefer that type
        // other wise use referenced array's element type
        static constexpr auto vtype = [](){
            if constexpr (detail::has_result_type_v<op_type>) {
                using result_t = typename op_type::result_type;
                return meta::as_value<result_t>{};
            }
            else return meta::as_value<element_t>{};
        }();
        using type = meta::type_t<meta::remove_cvref_t<decltype(vtype)>>;
    };
} // namespace::view::detail

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
        using operands_type = std::tuple<arrays_t...>;
        using array_type    = operands_type;
        using op_type       = op_t;
        using result_type   = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;

        op_type op;
        operands_type operands;

        constexpr scalar_ufunc_t(op_type op, const arrays_t&...arrays)
            : op(op), operands({arrays...}) {}
        
        constexpr auto dim() const
        {
            return 0;
        } // dim

        constexpr auto shape() const
        {
            return None;
        } // shape

        template <size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, std::index_sequence<Is...>)
        {
            return op(std::get<Is>(operands)...);
        } // apply_at

        constexpr operator result_type() const
        {
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, operands, std::make_index_sequence<N>{});
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
                auto tuple = std::tuple{std::cref(arrays)...};
                return meta::template_reduce<sizeof...(arrays)>([&](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    using arg_t  = meta::at_t<operands_type,i>;
                    using init_t = meta::remove_cvref_t<decltype(init)>;
                    // for each element in operands,
                    // dispatch based on take ref or not
                    auto arg = [&]() -> arg_t {
                        if constexpr (std::is_pointer_v<arg_t>) {
                            return &std::get<i>(tuple);
                        } else {
                            return std::get<i>(tuple);
                        }
                    }();
                    if constexpr (is_none_v<init_t>) {
                        return std::tuple{arg};
                    } else {
                        return std::tuple_cat(init,std::tuple<arg_t>{arg});
                    }
                }, None);
            } else {
                using array_t = meta::at_t<operands_type,0>;
                if constexpr (std::is_pointer_v<array_t>) {
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
            return detail::shape(std::get<0>(operands));
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return detail::dim(std::get<0>(operands));
        } // dim

        template <typename indices_t, size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, const indices_t& indices, std::index_sequence<Is...>)
        {
            using view::detail::apply_at;
            return op(apply_at(std::get<Is>(operands),indices)...);
        } // apply_at

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, operands, indices_, std::make_index_sequence<N>{});
        } // operator()
    }; // ufunc_t

    /**
     * @brief Type constructor to reduce single array given op.
     * 
     * @tparam op_t 
     */
    template <typename op_t>
    struct reducer_t
    {
        using op_type = op_t;

        op_type op;

        /**
         * @brief Perform reduction on single 1D array.
         * 
         * @tparam result_t 
         * @tparam array_t 
         * @param array 
         * @return constexpr auto 
         */
        template <typename result_t, typename array_t>
        constexpr auto operator()(const array_t& array) const
        {
            using index_t = meta::get_index_type_t<array_t>;
            auto initial = static_cast<result_t>(at(array,0));
            auto size = len(array);
            for (index_t i=1; i<size; i++)
                initial = op(initial,at(array,i));
            return initial;
        } // operator()

        /**
         * @brief perform reduction on single 1D array with given initial value
         * 
         * @tparam result_t 
         * @tparam array_t 
         * @tparam initial_t 
         * @param array 
         * @param init 
         * @return constexpr auto 
         */
        template <typename result_t, typename array_t, typename initial_t>
        constexpr auto operator()(const array_t& array, initial_t init) const
        {
            auto initial = static_cast<result_t>(init);
            auto size = len(array);
            for (size_t i=0; i<size; i++)
                initial = op(initial,at(array,i));
            return initial;
        } // operator()
    }; // reducer_t

    /**
     * @brief Type constructor for reduction ufuncs, given op, axis and initial value.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct reduce_t
    {
        // if given array is a view, just use value instead of reference
        using operands_type = resolve_array_type_t<array_t>;
        using array_type    = operands_type;
        using axis_type     = resolve_array_type_t<axis_t>;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        array_type    array;
        axis_type     axis;
        op_type       op;
        initial_type  initial;
        reducer_type  reducer;
        keepdims_type keepdims;

        constexpr reduce_t(op_type op, const array_t& array, const axis_t& axis, initial_type initial, keepdims_type keepdims)
            : op(op), array(initialize<array_type>(array)), axis(initialize<axis_type>(axis)), initial(initial), reducer{op}, keepdims(keepdims) {}

        constexpr auto shape() const
        {
            auto shape_ = detail::shape(array);
            // NOTE: can't provide convinience function
            // without causing bounded array to decay to pointer
            if constexpr (std::is_pointer_v<axis_type>) {
                return index::remove_dims(shape_,*axis,keepdims);
            } else {
                return index::remove_dims(shape_,axis,keepdims);
            }
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return len(shape());
        } // dim

        /**
         * @brief compute element at given indices, effectively perform reduction.
         * 
         * Computing such element only available if not reducing the whole array
         * (axis_t is not None).
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // TODO: consider to call eval on slices instead of putting all the code here

            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            
            auto indices_ = pack_indices(indices...);

            // for now, assume axis is int and array is fixed_dim
            // TODO: support reduce on dynamic dim array
            constexpr auto DIM = meta::fixed_dim_v<array_t>;
            // type for slicing is DIMx2 where 2 represent start and stop
            using slices_type = std::array<std::array<size_t,2>,DIM>;
            auto slices = slices_type {};
            auto shape_ = detail::shape(array);

            // helper lambda to check if axis i is in the specified axis for reduction
            auto in_axis = [&](auto i){
                if constexpr (meta::is_index_v<axis_t> && std::is_pointer_v<axis_type>) {
                    return i==*axis;
                } else if constexpr (meta::is_index_v<axis_t>) {
                    return i==axis;
                } else {
                    auto f_predicate = [i](auto axis){
                        return i==axis;
                    };
                    // axis is index array (reducing on multiple axes),
                    // axis may be pointer, but can't provide convinience function
                    // since may decay bounded array to pointer
                    if constexpr (std::is_pointer_v<axis_type>) {
                        auto found = index::where(f_predicate, *axis);
                        return static_cast<bool>(len(found));
                    } else {
                        auto found = index::where(f_predicate, axis);
                        return static_cast<bool>(len(found));
                    }
                }
            };

            // use the same type as axis_t for loop index
            constexpr auto idx_vtype = [](){
                if constexpr (meta::is_index_array_v<axis_t>) {
                    using type = meta::get_element_type_t<axis_t>;
                    return meta::as_value_v<type>;
                } else if constexpr (meta::is_integer_v<axis_t>) {
                    return meta::as_value_v<axis_t>;
                } else {
                    return meta::as_value_v<size_t>;
                }
            }();
            using index_t = meta::get_index_type_t<array_t>;
            using idx_t   = std::common_type_t<index_t,meta::type_t<decltype(idx_vtype)>>;

            // indices and the referenced array may have different dim,
            // this variable track index for indices_
            auto ii = idx_t{0};
            // here, len(slices) already matched the dimension of source array
            for (idx_t i=0; i<len(slices); i++) {
                // take all elements at given axis
                if (in_axis(i)) {
                    at(slices,i) = {static_cast<idx_t>(0),at(shape_,i)};
                    // if keepdims is true, also increment indices index
                    if (keepdims)
                        ii++;
                }
                // use indices otherwise, just slice with index:index+1
                else {
                    auto s = at(indices_,ii++);
                    at(slices,i) = {s,s+1};
                }
            }
            // apply slice only works with fixed dim ndarray for now
            // TODO: support dynamic dim ndarray
            auto sliced = [&](){
                // this slice operates directly with the underlying array
                // which may be pointer
                if constexpr (std::is_pointer_v<array_type>) {
                    return apply_slice(*array,slices);
                } else {
                    return apply_slice(array, slices);
                }
            }();
            auto flattened = flatten(sliced);
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }();
        } // operator()
    }; // reduce_t

    /**
     * @brief Specialization of reduce_t for None axis.
     *
     * Following numpy, when axis is None, perform reduction on flattened array.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename initial_t, typename keepdims_t>
    struct reduce_t<op_t,array_t,none_t,initial_t,keepdims_t>
    {
        using array_type    = resolve_array_type_t<array_t>;
        // use reference for now since raw array decays to pointer
        using axis_type     = none_t;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;
        using keepdims_type = keepdims_t;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        array_type    array;
        axis_type     axis;
        op_type       op;
        initial_type  initial;
        reducer_type  reducer;
        keepdims_type keepdims;

        constexpr reduce_t(op_type op, const array_t& array, axis_type axis, initial_type initial, keepdims_type keepdims)
            : op(op), array(initialize<array_type>(array)), axis(axis), initial(initial), reducer{op}, keepdims(keepdims) {}
        
        constexpr auto shape() const
        {
            // just get the original shape and then fill with one
            auto f_shape = [&](){
                auto shape_ = detail::shape(array);
                for (size_t i=0; i<len(shape_); i++)
                    at(shape_,i) = 1;
                return shape_;
            };
            if constexpr (meta::is_integral_constant_v<keepdims_t>) {
                if constexpr (static_cast<bool>(keepdims_t::value))
                    return f_shape();
                else return None;
            }
            // use variant since it can be none or the shape
            // else if constexpr (meta::is_boolean_v<keepdims_t>) {
            //     using shape_t  = decltype(nmtools::shape(array));
            //     // use none_t as first alternative, since it is must be defautl construtctibel
            //     using return_t = std::variant<none_t,shape_t>;
            //     return (keepdims ? return_t{f_shape()} : return_t{None});
            // }
            else // if (is_none_v<keepdims_t>)
                return None;
        } // shape

        constexpr auto dim() const
        {
            if constexpr (meta::is_integral_constant_v<keepdims_t>) {
                if constexpr (!static_cast<bool>(keepdims_t::value))
                    return 0;
                else return detail::dim(array);
            }
            else return 0;
        } // dim

        operator result_type() const
        {
            // reduce the whole array
            // must check if array is pointer or not since
            // flatten (and view in general) doesn't accept pointer
            auto flattened = [&](){
                if constexpr (std::is_pointer_v<array_type>) {
                    return flatten(*array);
                } else {
                    return flatten(array);
                }
            }();
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }(); 
        } // operator result_type()

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // reduce the whole array
            auto flattened = [&](){
                if constexpr (std::is_pointer_v<array_type>) {
                    return flatten(*array);
                } else {
                    return flatten(array);
                }
            }();
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }(); 
        } // operator()
    }; // reduce_t

    /**
     * @brief Type constructor for accumulate ufuncs.
     *
     * Accumulate the result on given axis.
     * 
     * @tparam op_t operator type
     * @tparam array_t array type
     * @tparam axis_t axis type
     */
    template <typename op_t, typename array_t, typename axis_t>
    struct accumulate_t
    {
        // if given array is a view, just use value instead of reference
        using operands_type = std::conditional_t<is_view_v<array_t>,array_t,const array_t&>;
        using array_type    = operands_type;
        using axis_type     = axis_t;
        using op_type       = op_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        array_type array;
        axis_type axis;
        op_type op;
        reducer_type reducer;

        constexpr accumulate_t(op_type op, array_type array, axis_type axis)
            : op(op), array(array), axis(axis), reducer{op} {}

        constexpr auto shape() const
        {
            return ::nmtools::shape(array);
        } // shape

        constexpr auto dim() const
        {
            return ::nmtools::dim(array);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
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
            // for now, assume axis is int and array is fixed_dim
            constexpr auto DIM = meta::fixed_dim_v<array_t>;
            // type for slicing is DIMx2 where 2 represent start and stop
            using slices_type = std::array<std::array<size_t,2>,DIM>;
            auto slices = slices_type {};
            // here, len(slices) already matched the dimension of source array
            auto dim = len(slices);
            for (size_t i=0; i<dim; i++) {
                // index at axis i
                auto s = at(indices_,i);
                auto start = i==axis ? 0 : s;
                auto stop  = s + 1;
                at(slices,i) = {start,stop};
            }
            // apply slice only works with fixed dim ndarray for now
            // TODO: support dynamic dim ndarray
            auto sliced = apply_slice(array, slices);
            auto flattened = flatten(sliced);
            return reducer.template operator()<result_type>(flattened);
        } // operator()
    }; // accumulate_t

    /**
     * @brief Type constructor for outer ufuncs.
     * 
     * Apply op to pairs of element of lhs and rhs.
     *
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct outer_t
    {
        using operands_type = detail::get_operands_type_t<lhs_t,rhs_t>;
        using array_type = operands_type;
        using op_type = op_t;
        using lhs_element_type = meta::get_element_type_t<lhs_t>;
        using rhs_element_type = meta::get_element_type_t<rhs_t>;
        using result_type = detail::get_ufunc_result_type_t<op_t,lhs_element_type,rhs_element_type>;

        op_type op;
        operands_type operands;

        // the following is needed because cant use view::initialize<...>
        // can't handle tuple yet
        static constexpr auto initialize_operands(const lhs_t& lhs, const rhs_t& rhs)
        {
            using op_lhs_t = meta::at_t<operands_type,0>;
            using op_rhs_t = meta::at_t<operands_type,1>;
            if constexpr (std::is_pointer_v<op_lhs_t> && std::is_pointer_v<op_rhs_t>) {
                return operands_type{&lhs,&rhs};
            } else if constexpr (std::is_pointer_v<op_lhs_t>) {
                return operands_type{&lhs,rhs};
            } else if constexpr (std::is_pointer_v<op_rhs_t>) {
                return operands_type{lhs,&rhs};
            } else {
                return operands_type{lhs,rhs};
            }
        } // initialize_operands

        constexpr outer_t(op_type op, const lhs_t& lhs, const rhs_t& rhs)
            : op(op), operands(initialize_operands(lhs,rhs)) {}
        
        constexpr auto shape() const
        {
            auto ashape = detail::shape(std::get<0>(operands));
            auto bshape = detail::shape(std::get<1>(operands));
            return index::shape_outer(ashape,bshape);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
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
            const auto& a = std::get<0>(operands);
            const auto& b = std::get<1>(operands);
            auto ashape = detail::shape(a);
            auto bshape = detail::shape(b);
            auto [aidx, bidx] = index::outer(indices_,ashape,bshape);
            return op(view::detail::apply_at(a,aidx),view::detail::apply_at(b,bidx));
        } // operator()
    }; // outer_t

    // provide user defined CTAD with tuple of arrays as args
    // here, expect the second arg (tuple{arrays...}) to be view (from broadcasting)
    // NOTE: somehow doesn't work, deduce using _ufunc for now
    template <typename op_t, typename...arrays_t>
    ufunc_t(op_t, std::tuple<arrays_t...>) -> ufunc_t<op_t,arrays_t...>;

    template <typename op_t, template<typename...> typename tuple, typename...arrays_t, size_t...Is>
    constexpr auto _ufunc(op_t op, const tuple<arrays_t...>& func, std::index_sequence<Is...>)
    {
        // help deduction
        return decorator_t<ufunc_t,op_t,arrays_t...>{{op, std::get<Is>(func)...}};
    }; // _ufunc

    template <typename op_t, template<typename...> typename tuple, typename...arrays_t>
    constexpr auto _ufunc(op_t op, const tuple<arrays_t...>& func)
    {
        return _ufunc(op,func,std::make_index_sequence<sizeof...(arrays_t)>{});
    }; // _ufunc

    /**
     * @brief Creates unfunc_t object, given op and arrays.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam arrays_t 
     * @param op 
     * @param array 
     * @param arrays 
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename...arrays_t>
    constexpr auto ufunc(op_t op, const array_t& array, const arrays_t&...arrays)
    {
        if constexpr (meta::is_either_v<array_t>) {
            // handle if array is either type,
            // such case can happen for reduce ufunc with runtime keepdims.
            // TODO: also handle any either type in arrays...
            // TODO: generalize get_if, declval
            using std::get_if; // assume either type is variant
            using lhs_t = meta::get_either_left_t<array_t>;
            using rhs_t = meta::get_either_right_t<array_t>;
            using lhs_ufunc_t = decltype(ufunc(op,std::declval<lhs_t>(),arrays...));
            using rhs_ufunc_t = decltype(ufunc(op,std::declval<rhs_t>(),arrays...));
            using result_t = meta::replace_either_t<array_t,lhs_ufunc_t,rhs_ufunc_t>;
            if (auto lptr = get_if<lhs_t>(&array)) {
                return result_t{ufunc(op,*lptr,arrays...)};
            } else /* if (auto rptr = get_if<rhs_t>(&array)) */ {
                // must be true,
                // use else to avoid warnings
                auto rptr = get_if<rhs_t>(&array);
                return result_t{ufunc(op,*rptr,arrays...)};
            }
        } else if constexpr (meta::is_num_v<array_t> && (meta::is_num_v<arrays_t> && ...)) {
            // all arrays are numeric, use scalar_ufunc instead
            using view_t = decorator_t<scalar_ufunc_t,op_t,array_t,arrays_t...>;
            return view_t{{op,array,arrays...}};
        } else if constexpr (sizeof...(arrays) > 0) {
            // enable broadcasting if operands >= 2
            // here, broadcasted array should be view
            auto b_arrays = broadcast_arrays(array, arrays...);
            using b_arrays_t = decltype(b_arrays);
            constexpr auto n_args = meta::len_v<b_arrays_t>;
            static_assert ( n_args == (sizeof...(arrays)+1)
                , "nmtools internal error" );
            return _ufunc(op, b_arrays);
        } else {
            // single argument ufunc, skip broadcasting
            using view_t = decorator_t<ufunc_t,op_t,array_t>;
            return view_t{{op,{array}}};
        }
    } // ufunc

    /**
     * @brief Create reduce_t object given op, array, axis and initial value.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @param op operation to perform, must be binary op
     * @param array array in which reduction to be performed
     * @param axis axis to reduce
     * @param initial inital value, can be None
     * @param keepdims keep reduced axes in the result as dimensions with size one.
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t=std::false_type>
    constexpr auto reduce(op_t op, const array_t& array, const axis_t& axis, initial_t initial, keepdims_t keepdims=keepdims_t{})
    {
        // note: here, axis as reference to prevent array decays
        // the view type may decide wether to take ref or copy

        // when axis is None, reduce can return scalar or ndarray depends on keepdims type
        // use variant to tell that the return value may be scalar or ndarray,
        // depending on the value of keepdims at runtime
        if constexpr (is_none_v<axis_t> && meta::is_boolean_v<keepdims_t>) {
            using scalar_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,std::false_type>;
            using ndarray_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,std::true_type>;
            // TODO: make default either type configurable
            using either_t = std::variant<scalar_t,ndarray_t>;
            return (keepdims ?
                    either_t{ndarray_t{{op,array,axis,initial,True}}}
                : either_t{scalar_t{{op,array,axis,initial,False}}});
        }
        // otherwise simply use as it is
        else {
            using view_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t,keepdims_t>;
            return view_t{{op,array,axis,initial,keepdims}};
        }
    } // reduce

    /**
     * @brief Create accumulate_t object given op, array and axis.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param op 
     * @param array 
     * @param axis 
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename axis_t>
    constexpr auto accumulate(op_t op, const array_t& array, axis_t axis)
    {
        // note: axis as reference to prevent array decays
        using view_t = decorator_t<accumulate_t,op_t,array_t,axis_t>;
        return view_t{{op,array,axis}};
    } // accumulate

    /**
     * @brief Create outer_t object given op, lhs array and rhs array.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param op operation to perform for each pair of lhs and rhs
     * @param lhs lhs array
     * @param rhs rhs array
     * @return constexpr auto 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    constexpr auto outer(op_t op, const lhs_t& lhs, const rhs_t& rhs)
    {
        using view_t = decorator_t<outer_t,op_t,lhs_t,rhs_t>;
        return view_t{{op,lhs,rhs}};
    }
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
                using types = std::tuple<arrays_t...>;
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
                using types = std::tuple<arrays_t...>;
                auto ref_dim  = fixed_dim_v<at_t<types,0>>;
                if constexpr (static_cast<bool>((fixed_dim_v<arrays_t> == ...)))
                    return ref_dim;
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
            // if all array is fixed shape, check if all array has same shape
            if constexpr (all_fixed_shape) {
                // assume at least 1 array is provided
                using array0_t = type_list_at_t<0,array_types>;
                constexpr auto shape0 = fixed_ndarray_shape_v<array0_t>;
                // actual checking
                constexpr auto shame_shape = [=](){
                    auto same = true;
                    template_for<sizeof...(arrays_t)>([&same,&shape0](auto index){
                        constexpr auto I = decltype(index)::value;
                        using type = type_list_at_t<I,array_types>;
                        static_assert( !std::is_void_v<type>
                            , "internal error: fixed_ndarray_shape< view::ufunc_t<op_t,arrays_t...> >"
                        );
                        static_assert( is_fixed_size_ndarray_v<type>
                            , "internal error: fixed_ndarray_shape< view::ufunc_t<op_t,arrays_t...> >"
                        );
                        same = same && utils::isequal(fixed_ndarray_shape_v<type>,shape0);
                    });
                    return same;
                }();
                // if all arrays have the same shape, return the shape
                // otherwise return fail
                if constexpr (shame_shape)
                    return shape0;
                else return detail::Fail;
            }
            // otherwise return fail
            else return detail::Fail;
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
    
    /**
     * @brief Compile-time shape inference for reduce ufuncs.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct fixed_ndarray_shape<
        view::reduce_t< op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static inline constexpr auto value = [](){
            // the shape of the reduction can only be known at compile time
            // if axis and keepdims is integral constant
            if constexpr (
                    is_fixed_size_ndarray_v<array_t>
                && (is_integral_constant_v<axis_t> || is_none_v<axis_t>)
                && (is_integral_constant_v<keepdims_t> || is_none_v<keepdims_t>)
            ) {
                constexpr auto keepdims = [](){
                    if constexpr (is_integral_constant_v<keepdims_t>)
                        return keepdims_t::value;
                    else /* if constexpr (is_none_v) */ return false;
                }();
                if constexpr (!keepdims && is_none_v<axis_t>) {
                    // reduce on all axis and not keep dimensions,
                    // this is not considered as fixed shape ndarray, but should be num type instead
                    return detail::Fail;
                } else {
                    constexpr auto shape  = fixed_ndarray_shape_v<array_t>;
                    constexpr auto axes   = [&](){
                        if constexpr (is_none_v<axis_t>) {
                            // reduce on all axis and keepdims.
                            // use std array for now
                            constexpr auto dim = ::nmtools::len(shape);
                            using axis_type = std::array<size_t,dim>;
                            auto axes = axis_type{};
                            for (size_t i=0; i<dim; i++)
                                at(axes,i) = i; // on all axis
                            return axes;
                        } else {
                            return axis_t::value;
                        }
                    }();
                    constexpr auto shape_ = index::remove_dims(shape, axes, keepdims);
                    constexpr auto dim_   = ::nmtools::len(shape_);
                    // here, shape_ may be hybrid index array
                    // convert to something that makes std::tuple_size_v is well-formed
                    // as needed by resize_fixed_ndarray on std::array.
                    // convert to std::array
                    // TODO: consider to add make_fixed_index_array metafunction
                    using result_t = std::array<size_t,dim_>;
                    auto result = result_t{};
                    for (size_t i=0; i<dim_; i++)
                        at(result,i) = at(shape_,i);
                    return result;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the dimension of reduce ufunc view at compile time.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct fixed_dim< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (is_none_v<axis_t>) {
                return 0;
            } else if constexpr (
                   is_fixed_dim_ndarray_v<array_t>
                && is_integral_constant_v<keepdims_t>)
            {
                constexpr auto keepdims = keepdims_t {};
                if constexpr (static_cast<bool>(keepdims)) {
                    return fixed_dim_v<array_t>;
                } else if constexpr (is_index_v<axis_t>) {
                    return fixed_dim_v<array_t> - 1;
                } else if constexpr (is_fixed_index_array_v<axis_t>) {
                    return fixed_dim_v<array_t> - fixed_index_array_size_v<axis_t>;
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        // TODO: consider to use fail type to indicate fail instead of void
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    }; // fixed_dim

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct is_ndarray< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static constexpr auto value_ = [](){
            if constexpr (is_none_v<axis_t> && is_none_v<keepdims_t>)
                return false;
            else if constexpr (is_none_v<axis_t> && is_integral_constant_v<keepdims_t>)
                return static_cast<bool>(keepdims_t::value);
            else return true;
        }();
        static constexpr auto value = is_ndarray_v<array_t> && value_;
    };

    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct is_num< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        static constexpr auto value_ = [](){
            if constexpr (is_none_v<keepdims_t>)
                return true;
            else if constexpr (is_integral_constant_v<keepdims_t>)
                return !static_cast<bool>(keepdims_t::value);
            else return false;
        }();
        static constexpr auto value = is_ndarray_v<array_t> && is_none_v<axis_t> && value_;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct get_element_type<
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t >
    >
    {
        using type = typename view::reduce_t<op_t, array_t, axis_t, initial_t, keepdims_t>::result_type;
    };

    /**
     * @brief Specialization of eval return type resolver for reduce ufunc.
     *
     * Need to specialize eval resolver because reducer may produce num, ndarray, or either.
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t, typename keepdims_t>
    struct resolve_optype<
        void, array::eval_t, view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t>, none_t
    >
    {
        static constexpr auto vtype = [](){
            using view_t = view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t, keepdims_t>;
            if constexpr (is_fixed_size_ndarray_v<view_t>) {
                // NOTE: resolve_unary_array_type defined in eval.hpp
                // only call on fixed_size_ndarray because axis_t may be runtime value otherwise
                return resolve_unary_array_type(as_value_v<array_t>, as_value_v<view_t>);
            } else if constexpr (is_num_v<view_t>) {
                using type = get_element_type_t<view_t>;
                return as_value_v<type>;
            } else /* if constexpr (is_ndarray_v<view_t>) */ {
                using element_t = get_element_type_t<view_t>;
                using type = make_dynamic_ndarray_t<element_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    /**
     * @brief Compile-time shape inference for accumulate ufunc
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename op_t, typename array_t, typename axis_t>
    struct fixed_ndarray_shape<
        view::accumulate_t< op_t, array_t, axis_t >
    >
    {
        // accumulate ufunc doesnt change the shape
        static inline constexpr auto value = fixed_ndarray_shape_v<array_t>;
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename op_t, typename array_t, typename axis_t>
    struct is_ndarray< 
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t >
    >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t>
    struct get_element_type<
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t >
    >
    {
        using type = typename view::accumulate_t<op_t, array_t, axis_t>::result_type;
    };

    /**
     * @brief Compile-time shape inference for outer ufunc.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_ndarray_shape<
        view::outer_t< op_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<lhs_t> && is_fixed_size_ndarray_v<rhs_t>) {
                constexpr auto lhs_shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto rhs_shape = fixed_ndarray_shape_v<rhs_t>;
                return index::shape_outer(lhs_shape,rhs_shape);
            } else {
                return detail::fail_t{};
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the fixed dim for outer view.
     *
     * Return Fail when dimension of the view is not known at compile-time.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_dim<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = [](){
            using view_t = view::outer_t< op_t, lhs_t, rhs_t >;
            if constexpr (
                   is_fixed_dim_ndarray_v<lhs_t>
                && is_fixed_dim_ndarray_v<rhs_t>
            ) {
                return fixed_dim_v<lhs_t> + fixed_dim_v<rhs_t>;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    };

    /**
     * @brief Infer maximum size (of hybrid ndarray) for outer view.
     * 
     * Return Fail when the view is not hybrid ndarray.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (
                   is_hybrid_ndarray_v<lhs_t>
                && is_hybrid_ndarray_v<rhs_t>
            ) {
                return hybrid_ndarray_max_size_v<lhs_t> * hybrid_ndarray_max_size_v<rhs_t>;
            } else if constexpr (
                   is_fixed_size_ndarray_v<lhs_t>
                && is_hybrid_ndarray_v<rhs_t>
            ) {
                constexpr auto shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto lhs = index::sum(shape);
                constexpr auto rhs = hybrid_ndarray_max_size_v<rhs_t>;
                return lhs * rhs;
            }  else if constexpr (
                   is_hybrid_ndarray_v<lhs_t>
                && is_fixed_size_ndarray_v<rhs_t>
            ) {
                constexpr auto lhs = hybrid_ndarray_max_size_v<lhs_t>;
                constexpr auto shape = fixed_ndarray_shape_v<rhs_t>;
                constexpr auto rhs = index::sum(shape);
                return lhs * rhs;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    };

    template <typename op_t, typename lhs_t, typename rhs_t>
    struct is_ndarray< 
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_t> && is_ndarray_v<rhs_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct get_element_type<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        using type = typename view::outer_t<op_t, lhs_t, rhs_t>::result_type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_HPP
