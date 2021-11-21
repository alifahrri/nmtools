#ifndef NMTOOLS_ARRAY_EVAL_HPP
#define NMTOOLS_ARRAY_EVAL_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/utils/isequal.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/utility/apply_resize.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::array
{
    // special tag to resolve eval return type
    struct eval_t {};

    // TODO: consider to change signature to evaluator_<view_c,context_t,output_t,void>
    // hence performing eval resolver outside the struct, allowing to easily specialize evaluator_t
    // based on specific output_t
    /**
     * @brief View evaluator, actually computes the view.
     * 
     * @tparam view_t view to compute
     * @tparam context_t evaluation context
     * @tparam typename sfinae point
     */
    template <typename view_t, typename context_t, typename=void>
    struct evaluator_t;

    template <typename view_t>
    struct evaluator_t<view_t,none_t>
    {
        using view_type    = const view_t&;
        using context_type = const none_t&;
        using output_type  = meta::resolve_optype_t<eval_t,view_t,none_t>;

        view_type view;
        context_type context;

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
            -> meta::enable_if_t<meta::is_ndarray_v<output_t>>
        {
            auto out_shape = ::nmtools::shape(output);
            auto inp_shape = ::nmtools::shape(view);

            // must be same shape
            // nmtools_assert must return, atm returning from this mem fn is
            // not supported, for now skip if mismatch
            // nmtools_assert( ::nmtools::utils::isequal(out_shape,inp_shape),
            //     "mismatched shape for evaluator call"
            // );

            if (!::nmtools::utils::isequal(out_shape,inp_shape))
                return;

            using ::nmtools::index::ndindex;
            auto out_index = ndindex(out_shape);
            auto inp_index = ndindex(inp_shape);

            auto n = inp_index.size();
            for (size_t i=0; i<n; i++) {
                // while the shape is the same,
                // the underlying type of indexing may be not
                auto inp_idx = inp_index[i];
                auto out_idx = out_index[i];
                apply_at(output,out_idx) = apply_at(view,inp_idx);
            }
        } // operator()

        template <typename output_t>
        constexpr auto operator()(output_t& output) const
            -> meta::enable_if_t<meta::is_num_v<output_t>>
        {
            output = static_cast<output_t>(view);
        } // operator()

        template <typename output_t=output_type, meta::enable_if_t<!meta::is_void_v<output_t>,int> = 0>
        constexpr auto operator()() const
        {
            using result_t = meta::transform_bounded_array_t<output_t>;
            auto output = result_t{};
            if constexpr (meta::is_resizeable_v<result_t>) {
                auto inp_shape = ::nmtools::shape(view);
                ::nmtools::detail::apply_resize(output,inp_shape);
            }

            (*this)(output);

            return output;
        } // operator()

        template <typename output_t>
        constexpr auto operator()(meta::as_value<output_t>) const
        {
            return (*this).template operator()<output_t>();
        } // operator()

        constexpr auto operator()(none_t) const
        {
            return (*this)();
        } // operator()
    }; // evaluator_t

    template <typename view_t, typename context_t>
    constexpr auto evaluator(const view_t& view, context_t&& context)
    {
        using ctx_t = meta::remove_cvref_t<context_t>;
        using evaluator_type = evaluator_t<view_t,ctx_t>;
        return evaluator_type{view,context};
    } // evaluator

    /**
     * @brief Evaluate a view, given context and optional output.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam view_t 
     * @param view 
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename view_t>
    constexpr auto eval(const view_t& view, context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        // TODO: support maybe type
        if constexpr (meta::is_either_v<view_t>) {
            using left_t   = meta::get_either_left_t<view_t>;
            using right_t  = meta::get_either_right_t<view_t>;
            // deduce return type for each type
            using rleft_t  = decltype(eval(meta::declval<left_t>(),context,output));
            using rright_t = decltype(eval(meta::declval<right_t>(),context,output));
            // TODO: make default either type configurable
            using either_t = meta::make_either_type_t<rleft_t,rright_t>;
            // match either type at runtime
            if (auto view_ptr = nmtools::get_if<left_t>(&view)) {
                return either_t{eval(*view_ptr,context,output)};
            } else /* if (auto view_ptr = get_if<right_t>(&view)) */ {
                auto view_rptr = nmtools::get_if<right_t>(&view);
                return either_t{eval(*view_rptr,context,output)};
            }
        } else /* if constexpr (meta::is_ndarray_v<view_t> || meta::is_num_v<view_t>) */ {
            auto evaluator_ = evaluator(view,context);
            return evaluator_(output);
        }
    } // eval

} // namespace nmtools::array

namespace nmtools::meta
{
    namespace error
    {
        // error type for eval type resolver
        struct EVAL_MISMATCHED_DIM : detail::fail_t {};
        struct EVAL_UNHANDLED_CASE : detail::fail_t {};
        struct EVAL_UNHANDLED_UNARY_CASE : detail::fail_t {};
        struct EVAL_UNHANDLED_BINARY_CASE : detail::fail_t {};
    } // namespace error::eval

    /**
     * @brief Infer array type when the underlying array of the view type is just single array.
     * 
     * @tparam array_t      underlying array type
     * @tparam view_type    view type in which its eval type to be resolved
     * @return constexpr auto 
     */
    template <typename array_t, typename view_type>
    constexpr auto resolve_unary_array_type(as_value<array_t>, as_value<view_type>)
    {
        using element_t = get_element_type_t<view_type>;
        if constexpr (
               is_none_v<array_t>
            && is_hybrid_ndarray_v<view_type>
        ) {
            constexpr auto max_size = hybrid_ndarray_max_size_v<view_type>;
            constexpr auto dim = fixed_dim_v<view_type>;
            using type = make_hybrid_ndarray_t<element_t,max_size,dim>;
            return as_value_v<type>;
        } else if constexpr (
               is_none_v<array_t>
            && is_dynamic_ndarray_v<view_type>
        ) {
            using type = make_dynamic_ndarray_t<element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_none_v<array_t>
            && is_fixed_size_ndarray_v<view_type>            
        ) {
            // None array type can be encountered for creation routine
            // such as view::zeros,ones...
            constexpr auto shape = fixed_ndarray_shape_v<view_type>;
            constexpr auto dim   = fixed_ndarray_dim_v<view_type>;
            // convert to tuple of integral constant
            // since default impl of make_fixed_ndarray (defined in ndarray/fixed.hpp)
            // only support such type
            constexpr auto vshape = template_reduce<dim>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                // shape may be constant index_array,
                // integral constant can be casted to value
                constexpr auto s = static_cast<size_t>(at(shape,i));
                using type = type_t<decltype(init)>;
                // default impl of make_fixed_ndarray only support integral constant for now
                using stype = ct<s>;
                if constexpr (is_void_v<type>) {
                    using type = make_tuple_type_t<stype>;
                    return as_value_v<type>;
                } else {
                    using type = append_type_t<type,stype>;
                    return as_value_v<type>;
                }
            }, as_value_v<void>);
            using shape_t = type_t<decltype(vshape)>;
            using type = make_fixed_ndarray_t<element_t,shape_t>;
            return as_value_v<type>;
        } else if constexpr (
                is_num_v<view_type>
            && (is_ndarray_v<array_t>)
        ) {
            // no matter what the array type is,
            // if the resulting view is num then return num
            return as_value_v<element_t>;
        } else if constexpr (
               is_num_v<array_t>
            && is_hybrid_ndarray_v<view_type>
        ) {
            // num array type can be the result of reducer such as view::reduce_t
            constexpr auto max_size = hybrid_ndarray_max_size_v<view_type>;
            constexpr auto dim = fixed_dim_v<view_type>;
            using type = make_hybrid_ndarray_t<element_t,max_size,dim>;
            return as_value_v<type>;
        } else if constexpr (
               is_num_v<array_t>
            && is_dynamic_ndarray_v<view_type>
        ) {
            using type = make_dynamic_ndarray_t<element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_num_v<array_t>
            && is_fixed_size_ndarray_v<view_type>
        ) {
            constexpr auto shape = fixed_ndarray_shape_v<view_type>;
            constexpr auto dim   = fixed_ndarray_dim_v<view_type>;
            constexpr auto vshape = template_reduce<dim>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                constexpr auto s = at(shape,i);
                using type = type_t<decltype(init)>;
                // default impl of make_fixed_ndarray only support integral constant for now
                using stype = ct<s>;
                if constexpr (is_void_v<type>) {
                    using type = make_tuple_type_t<stype>;
                    return as_value_v<type>;
                } else {
                    using type = append_type_t<type,stype>;
                    return as_value_v<type>;
                }
            }, as_value_v<void>);
            using shape_t = type_t<decltype(vshape)>;
            using type = make_fixed_ndarray_t<element_t,shape_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_hybrid_ndarray_v<view_type>
            && is_hybrid_ndarray_v<array_t>
        ) {
            constexpr auto N   = hybrid_ndarray_max_size_v<view_type>;
            constexpr auto DIM = fixed_dim_v<view_type>;
            using resized_max_t = resize_hybrid_ndarray_max_size_t<array_t,N>;
            using resized_t = resize_hybrid_ndarray_dim_t<resized_max_t,DIM>;
            using type = replace_element_type_t<resized_t,element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_dynamic_ndarray_v<view_type>
            && is_dynamic_ndarray_v<array_t>
            && !is_fixed_dim_ndarray_v<view_type>
            && !is_fixed_dim_ndarray_v<array_t>
        ) {
            // dynamic-size fixed-dim ndarray should be treated 
            // differently with its dynamic-dim counterpart
            // at the moment, there is no clear differentiation for such cases
            // and fixed-dim ndarray is pretty much ignored
            // note that for fixed-dim ndarray,
            // it is possible to have dynamic-size or hybrid-size
            // TODO: improve fixed-dim handling
            using type = replace_element_type_t<array_t,element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_dynamic_ndarray_v<view_type>
            && is_dynamic_ndarray_v<array_t>
            && is_fixed_dim_ndarray_v<view_type>
            && is_fixed_dim_ndarray_v<array_t>
        ) {
            constexpr auto view_dim  = fixed_dim_v<view_type>;
            constexpr auto array_dim = fixed_dim_v<array_t>;
            if constexpr (view_dim == array_dim) {
                using type = replace_element_type_t<array_t,element_t>;
                return as_value_v<type>;
            } else {
                using type = make_dynamic_ndarray_t<element_t>;
                return as_value_v<type>;
                // return as_value_v<error::EVAL_MISMATCHED_DIM>;
            }
        } else if constexpr (
               is_dynamic_ndarray_v<view_type>
            && is_dynamic_ndarray_v<array_t>
        ) {
            // here, either view_type or array_t is fixed-dim, but not both,
            // for now use default dynamic ndarray
            using type = make_dynamic_ndarray_t<element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_fixed_size_ndarray_v<view_type>
            && is_fixed_size_ndarray_v<array_t>
        ) {
            using resized_t = resize_fixed_ndarray_t<
                transform_bounded_array_t<array_t>,view_type>;
            using type = replace_element_type_t<resized_t,element_t>;
            return as_value_v<type>;
        } else if constexpr (
                is_dynamic_ndarray_v<view_type>
            && (is_hybrid_ndarray_v<array_t> || is_fixed_size_ndarray_v<array_t>)
        ) {
            using type = make_dynamic_ndarray_t<element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_hybrid_ndarray_v<view_type>
            && is_fixed_size_ndarray_v<array_t>
        ) {
            constexpr auto max_elements = hybrid_ndarray_max_size_v<view_type>;
            constexpr auto dim = fixed_dim_v<view_type>;
            using type = make_hybrid_ndarray_t<element_t,max_elements,dim>;
            return as_value_v<type>;
        } else {
            // fail
            using fail_t = error::EVAL_UNHANDLED_UNARY_CASE;
            return as_value_v<fail_t>;
        }
    } // resolve_unary_array_type

    /**
     * @brief Infer array type when the underlying array of the view type is two array.
     * 
     * @tparam lhs_t     underlying left-hand-side array type
     * @tparam rhs_t     underlying right-hand-side array type
     * @tparam view_type view type in which its eval type is to be resolved
     * @param lhs 
     * @param rhs 
     * @param view 
     * @return constexpr auto 
     */
    template <typename lhs_t, typename rhs_t, typename view_type>
    constexpr auto resolve_binary_array_type([[maybe_unused]] as_value<lhs_t> lhs, [[maybe_unused]] as_value<rhs_t> rhs, [[maybe_unused]] as_value<view_type> view)
    {
        using element_t = get_element_type_t<view_type>;
        if constexpr (
            is_num_v<view_type>
        ) {
            // no matter what lhs and rhs types are,
            // return num type
            return as_value_v<element_t>;
        } else if constexpr (
               is_num_v<lhs_t>
            && is_ndarray_v<rhs_t>
            && is_ndarray_v<view_type>
        ) {
            // ignore num if the resulting view type is ndarray
            // may contain num because of broadcasting
            return resolve_unary_array_type(rhs,view);
        } else if constexpr (
               is_num_v<rhs_t>
            && is_ndarray_v<lhs_t>
            && is_ndarray_v<view_type>
        ) {
            return resolve_unary_array_type(lhs,view);
        } else if constexpr (
               is_hybrid_ndarray_v<lhs_t>
            && is_hybrid_ndarray_v<rhs_t>
            && is_hybrid_ndarray_v<view_type>
        ) {
            return resolve_unary_array_type(lhs,view);
        } else if constexpr (
               is_dynamic_ndarray_v<lhs_t>
            && is_dynamic_ndarray_v<rhs_t>
            && is_dynamic_ndarray_v<view_type>
        ) {
            using type = replace_element_type_t<lhs_t,element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_fixed_size_ndarray_v<lhs_t>
            && is_fixed_size_ndarray_v<rhs_t>
            && is_fixed_size_ndarray_v<view_type>
        ) {
            // prefer lhs type
            using array_t = transform_bounded_array_t<lhs_t>;
            using resized_t = resize_fixed_ndarray_t<array_t,view_type>;
            using type = replace_element_type_t<resized_t,element_t>;
            return as_value_v<type>;
        } else if constexpr(
               (is_hybrid_ndarray_v<lhs_t> || is_fixed_size_ndarray_v<lhs_t>)
            && (is_hybrid_ndarray_v<rhs_t> || is_fixed_size_ndarray_v<rhs_t>)
            && is_dynamic_ndarray_v<view_type>
        ) {
            using type = make_dynamic_ndarray_t<element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_dynamic_ndarray_v<lhs_t>
            && is_dynamic_ndarray_v<view_type>
        ) {
            using type = replace_element_type_t<lhs_t,element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_dynamic_ndarray_v<rhs_t>
            && is_dynamic_ndarray_v<view_type>
        ) {
            using type = replace_element_type_t<rhs_t,element_t>;
            return as_value_v<type>;
        } else if constexpr (
               is_hybrid_ndarray_v<lhs_t>
            && is_hybrid_ndarray_v<view_type>
        ) {
            // may occur when lhs is hybrid, rhs is fixed,
            // and the view type is deduced as hybrid
            return resolve_unary_array_type(lhs,view);
        } else if constexpr (
               is_hybrid_ndarray_v<rhs_t>
            && is_hybrid_ndarray_v<view_type>
        ) {
            return resolve_unary_array_type(rhs,view);
        } else {
            return as_value_v<error::EVAL_UNHANDLED_BINARY_CASE>;
        }
    } // resolve_binary_array_type

    /**
     * @brief Default implementation of type resolver for eval op with None execution.
     * 
     * At the moment the implementation should be working for various view type
     * such as ufuncs, outer_ufuncs, accumulate_ufuncs, arange, atleast_1d, full, ones, zeros, flip.
     * Some views are known to have its own specialization, such as reduce_ufuncs, atleast_2d, atleast_3d, broadcast_to.
     * 
     * Note that this resolver doesn't handle either type,
     * the resolution of either type should be handled at the caller site.
     *
     * @tparam view_t view type in which its eval type is to be resolved.
     * @todo generalize to accommodate other specialized resolver
     */
    template <typename view_t>
    struct resolve_optype<
        void, array::eval_t, view_t, none_t
    >
    {
        using element_t = get_element_type_t<view_t>;

        // entrypoint to deduce array type for eval:
        static constexpr auto vtype = [](){
            // underlying array may have multiple arrays
            using arrays_t = get_underlying_array_type_t<view_t>;
            // NOTE: now the underlying array may be reference, pointer, or value (for none or scalar num).
            using nocv_arrays_t = remove_cvref_pointer_t<arrays_t>;
            if constexpr (is_ndarray_v<nocv_arrays_t> || is_none_v<nocv_arrays_t> || is_num_v<nocv_arrays_t>) {
                // single array
                using array_t = remove_cvref_pointer_t<arrays_t>;
                return resolve_unary_array_type(as_value_v<array_t>, as_value_v<view_t>);
            } else if constexpr (is_tuple_v<nocv_arrays_t> && len_v<arrays_t> == 1) {
                // packed single array, can be found in views that accepts variadic such as ufunc
                using array_t = remove_cvref_pointer_t<at_t<arrays_t,0>>;
                return resolve_unary_array_type(as_value_v<array_t>, as_value_v<view_t>);
            } else if constexpr (is_tuple_v<nocv_arrays_t> && len_v<arrays_t> == 2) {
                // binary array
                using lhs_t = remove_cvref_pointer_t<at_t<arrays_t,0>>;
                using rhs_t = remove_cvref_pointer_t<at_t<arrays_t,1>>;
                return resolve_binary_array_type(as_value_v<lhs_t>, as_value_v<rhs_t>, as_value_v<view_t>);
            } else if constexpr (is_tuple_v<nocv_arrays_t> && len_v<arrays_t> > 2) {
                // more than 2 array, simply perform reduction using binary case resolver
                constexpr auto N = len_v<arrays_t>;
                return template_reduce<N-1>([](auto init, auto index){
                    constexpr auto i = decltype(index)::value;
                    using init_t = type_t<decltype(init)>;
                    using lhs_t = remove_cvref_pointer_t<at_t<arrays_t,i>>;
                    using rhs_t = remove_cvref_pointer_t<at_t<arrays_t,i+1>>;
                    // we start from void type
                    if constexpr (is_void_v<init_t>) {
                        return resolve_binary_array_type(as_value_v<lhs_t>, as_value_v<rhs_t>, as_value_v<view_t>);
                    } else {
                        return resolve_binary_array_type(as_value_v<init_t>, as_value_v<rhs_t>, as_value_v<view_t>);
                    }
                }, as_value_v<void>);
            } else {
                // unknown for now
                return as_value_v<error::EVAL_UNHANDLED_CASE>;
            }
        }();
        using type = type_t<remove_cvref_pointer_t<decltype(vtype)>>;
    }; // eval_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_EVAL_HPP