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
#include "nmtools/array/index/ufunc.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/as_static.hpp"

#include "nmtools/array/view/ufunc/detail.hpp"

namespace nmtools::args
{
    template <typename op_t=none_t>
    struct ufunc
    {
        using op_type = op_t;

        op_type op = {};

        template <typename other_op_t>
        constexpr auto operator==(const ufunc<other_op_t>& other) const
        {
            if constexpr (meta::expression_check_v<meta::expr::equal,op_type,other_op_t>) {
                return op == other.op;   
            } else {
                return meta::is_same_v<op_type,op_t>;
            }
        }
    };

    template <typename...args_t>
    ufunc(args_t...) -> ufunc<args_t...>;
} // namespace nmtools::args

namespace nmtools::array
{
    template <auto max_dim, typename...args_t>
    struct as_static_t<
        args::ufunc<args_t...>, max_dim
    >
    {
        using attribute_type = args::ufunc<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            return attribute;
        }
    };
} // nmtools::array

namespace nmtools::meta
{
    template <typename op_t>
    struct is_attribute<
        args::ufunc<op_t>
    > : true_type {};
} // namespace nmtools::meta

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
        // dont take reference for the array, a Num type should be copied
        // and view type should be cheap to copy
        using operands_type = nmtools_tuple<arrays_t...>;
        using array_type    = operands_type;
        using op_type       = op_t;
        using result_type   = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;

        op_type op;
        operands_type array;

        constexpr scalar_ufunc_t(op_type op, const arrays_t&...arrays)
            : op(op), array{arrays...} {}
        
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
        static constexpr auto apply_at(op_type op, const operands_type& array, meta::index_sequence<Is...>)
        {
            return op(nmtools::get<Is>(array)...);
        } // apply_at

        constexpr operator result_type() const
        {
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, array, meta::make_index_sequence<N>{});
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
        using operands_type = decltype(pack_operands(meta::declval<arrays_t>()...));
        using array_type    = operands_type;
        using op_type       = op_t;
        using result_type = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;
        using shape_type  = const meta::resolve_optype_t<index::shape_ufunc_t,decltype(nmtools::shape<true>(meta::declval<arrays_t>()))...>;
        using size_type   = const meta::resolve_optype_t<index::size_ufunc_t,shape_type,decltype(nmtools::size<true>(meta::declval<arrays_t>()))...>;

        op_type op;
        operands_type array;
        shape_type shape_;
        size_type  size_;

        constexpr ufunc_t(op_type op, const arrays_t&...array)
            : op(op)
            , array(pack_operands(array...))
            , shape_(unwrap(index::shape_ufunc(nmtools::shape<true>(array)...)))
            , size_(index::size_ufunc(shape_,nmtools::size<true>(array)...))
        {}

        constexpr auto operands() const noexcept
        {
            return array;
        }

        constexpr auto attributes() const noexcept
        {
            return args::ufunc<op_t>{op};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        constexpr auto size() const
        {
            return size_;
        } // size

        template <typename operand_t, typename indices_t>
        static constexpr auto apply_at(const operand_t& operand, const indices_t& indices)
        {
            static_assert( !meta::is_maybe_v<operand_t> && meta::is_ndarray_v<meta::remove_cvref_pointer_t<operand_t>> );
            if constexpr (meta::is_pointer_v<operand_t>) {
                return nmtools::apply_at(*operand,indices);
            } else {
                return nmtools::apply_at(operand,indices);
            }
        }

        template <typename indices_t, size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& array, const indices_t& indices, meta::index_sequence<Is...>)
        {
            using view::detail::apply_at;
            return op(ufunc_t::apply_at(nmtools::get<Is>(array),indices)...);
        } // apply_at

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, array, indices_, meta::make_index_sequence<N>{});
        } // operator()
    }; // ufunc_t
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename...>
    struct UFUNC_ARITY_UNKNOWN : detail::fail_t {};

    template <typename view_type>
    struct ufunc_arity
    {
        static constexpr auto value = -1;
    };

    template <typename op_t, typename...arrays_t>
    struct ufunc_arity<
        view::decorator_t< view::ufunc_t, op_t, arrays_t... >
    >
    {
        static constexpr auto value = sizeof...(arrays_t);
    };
    
    template <typename T>
    struct ufunc_arity<const T> : ufunc_arity<T> {};

    template <typename T>
    struct ufunc_arity<T&> : ufunc_arity<T> {};

    template <typename T>
    constexpr inline auto ufunc_arity_v = ufunc_arity<T>::value;


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

    template <typename op_t, typename...arrays_t>
    struct is_ndarray< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {
        static constexpr auto value = (is_ndarray_v<arrays_t> && ...);
    };

    // TODO: remove, move to main decorator_t
    template <typename op_t, typename...arrays_t>
    struct fixed_size< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {
        using view_type  = view::decorator_t< view::ufunc_t, op_t, arrays_t... >;
        using ufunc_type = typename view_type::view_type;
        using shape_type = typename ufunc_type::shape_type;
        using type_list  = meta::type_list<arrays_t...>;
        using size_type  = typename ufunc_type::size_type;

        static constexpr auto value = [](){
            if constexpr (is_constant_index_v<size_type>) {
                return size_type::value;
            } else {
                return error::FIXED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    // TODO: remove, move to main decorator_t
    template <typename op_t, typename...arrays_t>
    struct bounded_size< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {
        using view_type  = view::decorator_t< view::ufunc_t, op_t, arrays_t... >;
        using shape_type = typename view_type::shape_type;
        using type_list  = meta::type_list<arrays_t...>;
        using size_type  = typename view_type::size_type;

        static constexpr auto value = [](){
            #if 0
            // NOTE: in this commit, the following code breaks (arduino uno) avr-gcc
            // complains about:
            //  error: non-type template parameters of class type only available with '-std=c++2a' or '-std=gnu++2a'
            //  struct to_value <const T> : to_value<T> {};
            constexpr auto c_size = to_value_v<size_type>;
            if constexpr (!is_fail_v<decltype(c_size)>) {
                return size_t(c_size);
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
            #else
            if constexpr (is_constant_index_v<size_type>) {
                return size_type::value;
            } else if constexpr (is_clipped_integer_v<size_type>) {
                return size_type::max;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
            #endif
        }();
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