#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_OUTER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_OUTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ref.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/core/flatten.hpp"
#include "nmtools/index/outer.hpp"
#include "nmtools/index/remove_dims.hpp"
#include "nmtools/index/where.hpp"
#include "nmtools/index/sum.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/core/eval.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/utility/as_static.hpp"

#include "nmtools/core/ufunc/detail.hpp"
#include "nmtools/utility/to_string/to_string.hpp"

namespace nmtools::args
{
    template <typename dtype_t, typename op_t=none_t>
    struct outer
    {
        using op_type = op_t;
        using dtype_type = dtype_t;

        dtype_type dtype = {};
        op_type op = {};

        constexpr auto operator==(const outer<dtype_t,op_t>&) const
        {
            return true;
        }
    };

    template <typename...args_t>
    outer(args_t...) -> outer<args_t...>;
} // namespace nmtools::args

namespace nmtools
{
    template <auto max_dim, typename...args_t>
    struct as_static_t<
        args::outer<args_t...>, max_dim
    >
    {
        using attribute_type = args::outer<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            return attribute;
        }
    };
} // nmtools

namespace nmtools::meta
{
    template <typename dtype_t, typename op_t>
    struct is_attribute<args::outer<dtype_t,op_t>> : true_type {};
} // namespace nmtools::meta

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename op_t
        , typename dtype_t
        , typename formatter_t
    >
    struct to_string_t<
        args::outer<op_t,dtype_t>
        , formatter_t
    >
    {
        using attribute_type = args::outer<op_t,dtype_t>;
        using formatter_type = formatter_t;

        auto operator()(const attribute_type& attribute) const noexcept
        {
            nmtools_string str;

            auto op_str = to_string(attribute.op,formatter_type{});
            if (op_str.empty()) {
                op_str = NMTOOLS_TYPENAME_TO_STRING(op_t);
            }

            str += "{";

            str += ".op=";
            str += op_str;
            str += ",.dtype=";
            str += to_string(attribute.dtype,formatter_type{});

            str += "}";
            
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    /**
     * @brief Type constructor for outer ufuncs.
     * 
     * Apply op to pairs of element of lhs and rhs.
     *
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t, typename dtype_t=none_t>
    struct outer_t
    {
        using operands_type = detail::get_operands_type_t<lhs_t,rhs_t>;
        using array_type = operands_type;
        using op_type = op_t;
        using lhs_element_type = meta::get_element_type_t<lhs_t>;
        using rhs_element_type = meta::get_element_type_t<rhs_t>;
        using result_type = detail::get_ufunc_result_type_t<op_t,lhs_element_type,rhs_element_type>;
        using dtype_type  = dtype_t;

        using attributes_type = args::outer<dtype_type,op_type>;

        using lhs_shape_type = decltype(nmtools::shape<true>(meta::declval<lhs_t>()));
        using rhs_shape_type = decltype(nmtools::shape<true>(meta::declval<rhs_t>()));
        using lhs_size_type  = decltype(nmtools::size<true>(meta::declval<lhs_t>()));
        using rhs_size_type  = decltype(nmtools::size<true>(meta::declval<rhs_t>()));
        using dst_shape_type = const meta::resolve_optype_t<index::shape_outer_t,lhs_shape_type,rhs_shape_type>;
        using dst_size_type  = const meta::resolve_optype_t<index::size_outer_t,dst_shape_type,lhs_size_type,rhs_size_type>;

        op_type op;
        array_type array;

        dst_shape_type shape_;
        dst_size_type  size_;
        dtype_type dtype;

        // TODO: move to common decorator.hpp
        // the following is needed because cant use view::initialize<...>
        // can't handle tuple yet
        static constexpr auto initialize_array(const lhs_t& lhs, const rhs_t& rhs)
        {
            using op_lhs_t = meta::at_t<array_type,0>;
            using op_rhs_t = meta::at_t<array_type,1>;
            if constexpr (meta::is_pointer_v<op_lhs_t> && meta::is_pointer_v<op_rhs_t>) {
                return array_type{&lhs,&rhs};
            } else if constexpr (meta::is_pointer_v<op_lhs_t>) {
                return array_type{&lhs,rhs};
            } else if constexpr (meta::is_pointer_v<op_rhs_t>) {
                return array_type{lhs,&rhs};
            } else {
                return array_type{lhs,rhs};
            }
        } // initialize_array

        constexpr outer_t(op_t op, const lhs_t& lhs, const rhs_t& rhs, dtype_t dtype)
            : op(op)
            , array(initialize_array(lhs,rhs))
            , shape_(index::shape_outer(nmtools::shape<true>(lhs),nmtools::shape<true>(rhs)))
            , size_(index::size_outer(shape_,nmtools::size<true>(lhs),nmtools::size<true>(rhs)))
            , dtype(dtype)
        {}

        constexpr outer_t(const lhs_t& lhs, const rhs_t& rhs, const args::outer<dtype_t,op_t>& attributes)
            : outer_t(
                attributes.op
                , lhs
                , rhs
                , attributes.dtype
            )
        {}

        constexpr auto operands() const noexcept
        {
            return array_type{array};
        }

        constexpr auto attributes() const noexcept
        {
            return attributes_type{dtype,op};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            // TODO: make sure to return compile time index whenever possible
            return len(shape());
        } // dim

        constexpr auto size() const noexcept
        {
            return size_;
        }

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            const auto& a = nmtools::get<0>(array);
            const auto& b = nmtools::get<1>(array);
            auto ashape = detail::shape(a);
            auto bshape = detail::shape(b);
            const auto [a_idx, b_idx] = index::outer(indices_,ashape,bshape);
            return op(view::detail::apply_at(a,a_idx),view::detail::apply_at(b,b_idx));
        } // operator()
    }; // outer_t
} // namespace nmtools::view

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct OUTER_BOUNDED_SIZE_UNSUPPORTED : detail::fail_t {};
    }

    template <typename op_t, typename lhs_t, typename rhs_t, typename dtype_t>
    struct is_outer<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t, dtype_t >
    > : true_type {};

    template <typename op_t, typename lhs_t, typename rhs_t, typename dtype_t>
    struct bounded_size<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t, dtype_t >
    >
    {
        using view_type = view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t, dtype_t >;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<lhs_t> && is_bounded_size_v<rhs_t>) {
                return bounded_size_v<lhs_t> * bounded_size_v<rhs_t>;
            } else {
                return error::OUTER_BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // bounded_size

    template <typename op_t, typename lhs_t, typename rhs_t, typename dtype_t>
    struct is_ndarray< 
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t, dtype_t >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_t> && is_ndarray_v<rhs_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename lhs_t, typename rhs_t, typename dtype_t>
    struct get_element_type<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t, dtype_t >
    >
    {
        using type = typename view::outer_t<op_t, lhs_t, rhs_t, dtype_t>::result_type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_OUTER_HPP