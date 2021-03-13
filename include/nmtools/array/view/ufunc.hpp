#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/index/remove_dims.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/dtypes.hpp"

#include <tuple>

// clang doesn't support constexpr math while gcc does
#if defined(__GNUC__) && !defined(__clang__) && !defined(NMTOOLS_UFUNC_CONSTEXPR)
#define NMTOOLS_UFUNC_CONSTEXPR constexpr
#else
#define NMTOOLS_UFUNC_CONSTEXPR
#endif

namespace nmtools::view
{
    namespace detail
    {
        /**
         * @brief helper metafunction to deduce the operand types for ufunc,
         * dont take reference for 'view' objects/
         * 
         * @tparam always_void 
         * @tparam arrays_t 
         */
        template <typename always_void,typename...arrays_t>
        struct get_operands_type
        {
            using type = std::tuple<const arrays_t&...>;
        }; // get_operands_type

        template <typename...arrays_t>
        struct get_operands_type<
            std::enable_if_t<(meta::is_view_v<arrays_t> || ...)>
            , arrays_t...
        >
        {
            // TODO: note that array may be mixed with view and non-view,
            // only copy those view while keep reference for non-view arrays
            using type = std::tuple<arrays_t...>;
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
        struct get_result_type
        {
            using type = decltype(std::declval<op_t>()(std::declval<args_t>()...));
        }; // get_result_type

        template <typename op_t, typename...args_t>
        struct get_result_type<
            std::void_t<typename op_t::result_type>,
            op_t, args_t...
        >
        {
            using type = typename op_t::result_type;
        }; // get_result_type

        template <typename op_t, typename...args_t>
        using get_result_type_t = typename get_result_type<void,op_t,args_t...>::type;

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
        
    } // namespace detail

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
        using result_type = detail::get_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;

        op_type op;
        operands_type operands;

        constexpr ufunc_t(op_type op, operands_type operands)
            : op(op), operands(operands) {}
        
        constexpr auto shape() const
        {
            // assume arrays is already broadcasted together
            return ::nmtools::shape(std::get<0>(operands));
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return ::nmtools::dim(std::get<0>(operands));
        } // dim

        template <typename indices_t, size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, const indices_t& indices, std::index_sequence<Is...>)
        {
            using ::nmtools::apply_at;
            return op(apply_at(std::get<Is>(operands),indices)...);
        } // apply_at

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
            auto initial = static_cast<result_t>(at(array,0));
            auto size = len(array);
            for (size_t i=1; i<size; i++)
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
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t>
    struct reduce_t
    {
        // if given array is a view, just use value instead of reference
        using operands_type = std::conditional_t<is_view_v<array_t>,array_t,const array_t&>;
        using array_type    = operands_type;
        // use reference for now since raw array decays to pointer
        using axis_type     = const axis_t&;
        using op_type       = op_t;
        using initial_type  = initial_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;

        template <typename element_t>
        struct get_result_type
        {
            static constexpr auto vtype = [](){
                if constexpr (detail::has_result_type_v<op_type>) {
                    using result_t = typename op_type::result_type;
                    return detail::type_wrapper<result_t>{};
                }
                else return detail::type_wrapper<element_t>{};
            }();
            using type = meta::type_t<meta::remove_cvref_t<decltype(vtype)>>;
        };
        using result_type = meta::type_t<get_result_type<element_type>>;

        array_type array;
        axis_type axis;
        op_type op;
        initial_type initial;
        reducer_type reducer;

        constexpr reduce_t(op_type op, array_type array, axis_type axis, initial_type initial)
            : op(op), array(array), axis(axis), initial(initial), reducer{op} {}
        
        constexpr auto shape() const
        {
            // TODO: support keepdims
            return index::remove_dims(::nmtools::shape(array), axis);
        } // shape

        constexpr auto dim() const
        {
            // assume arrays is already broadcasted together
            return len(shape());
        } // dim

        /**
         * @brief compute element at given indices, effectively perform reduction.
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
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
            auto shape_ = ::nmtools::shape(array);
            // indices and the referenced array may have different dim,
            // this variable track index for indices_
            auto ii = size_t{0};
            // helper lambda to check if axis i is in the specified axis for reduction
            auto in_axis = [&](auto i){
                if constexpr (std::is_integral_v<axis_t>)
                    return i==axis;
                else {
                    auto f_predicate = [i](auto axis){
                        return i==axis;
                    };
                    auto found = index::where(f_predicate, axis);
                    return static_cast<bool>(len(found));
                }
            };
            for (size_t i=0; i<len(slices); i++) {
                // take all elements at given axis
                if (in_axis(i))
                    at(slices,i) = {0,at(shape_,i)};
                // use indices otherwise, just slice with index:index+1
                else {
                    auto s = at(indices_,ii++);
                    at(slices,i) = {s,s+1};
                }
            }
            // apply slice only works with fixed dim ndarray for now
            // TODO: support dynamic dim ndarray
            auto sliced = apply_slice(array, slices);
            auto flattened = flatten(sliced);
            return [&](){
                if constexpr (is_none_v<initial_type>)
                    return reducer.template operator()<result_type>(flattened);
                else return reducer.template operator()<result_type>(flattened,initial);
            }();
        } // operator()
    }; // reduce_t

    // provide user defined CTAD with tuple of arrays as args
    template <typename op_t, typename...arrays_t>
    ufunc_t(op_t, std::tuple<arrays_t...>) -> ufunc_t<op_t,arrays_t...>;

    template <typename op_t, typename...arrays_t>
    constexpr auto _ufunc(ufunc_t<op_t,arrays_t...> func)
    {
        // help deduction
        return decorator_t<ufunc_t,op_t,arrays_t...>{func};
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
        if constexpr (sizeof...(arrays) > 0) {
            auto b_arrays = broadcast_arrays(array, arrays...);
            auto func = ufunc_t{op, b_arrays};
            // NOTE: deduction failed
            // return decorator_t{func};
            return _ufunc(func);
        }
        else {
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
     * @return constexpr auto 
     */
    template <typename op_t, typename array_t, typename axis_t, typename initial_t>
    constexpr auto reduce(op_t op, const array_t& array, const axis_t& axis, initial_t initial)
    {
        // note: axis as reference to prevent array decays
        using view_t = decorator_t<reduce_t,op_t,array_t,axis_t,initial_t>;
        return view_t{{op,array,axis,initial}};
    } // reduce
} // namespace nmtools::view

namespace nmtools::meta
{
    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename...arrays_t>
    struct fixed_matrix_size< view::ufunc_t<op_t,arrays_t...> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename...arrays_t>
    struct fixed_vector_size< view::ufunc_t<op_t,arrays_t...> >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename...arrays_t>
    struct fixed_ndarray_shape< view::ufunc_t<op_t,arrays_t...> >
    {
        static inline constexpr auto value = detail::fail_t{};
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

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename array_t, typename axis_t, typename initial_t>
    struct fixed_matrix_size<
        view::reduce_t< op_t, array_t, axis_t, initial_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename array_t, typename axis_t, typename initial_t>
    struct fixed_vector_size<
        view::reduce_t< op_t, array_t, axis_t, initial_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    };

    // NOTE: dont support fixed size for now
    // TODO: fix for fixed size
    template <typename op_t, typename array_t, typename axis_t, typename initial_t>
    struct fixed_ndarray_shape<
        view::reduce_t< op_t, array_t, axis_t, initial_t >
    >
    {
        static inline constexpr auto value = detail::fail_t{};
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename op_t, typename array_t, typename axis_t, typename initial_t>
    struct is_ndarray< 
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t >
    >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t, typename initial_t>
    struct get_element_type<
        view::decorator_t< view::reduce_t, op_t, array_t, axis_t, initial_t >
    >
    {
        using type = typename view::reduce_t<op_t, array_t, axis_t, initial_t>::result_type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_HPP