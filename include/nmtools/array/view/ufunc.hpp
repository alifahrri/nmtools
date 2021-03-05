#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"

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
        using result_type = std::common_type_t<meta::get_element_type_t<arrays_t>...>;

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
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_HPP