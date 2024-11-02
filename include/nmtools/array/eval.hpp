#ifndef NMTOOLS_ARRAY_EVAL_HPP
#define NMTOOLS_ARRAY_EVAL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/utility/get.hpp"

#include "nmtools/array/ndarray.hpp"

#include "nmtools/utility/isequal.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/apply_resize.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::array
{
    template <typename ctx_t>
    struct context_t : ctx_t {};

    using no_context_t = context_t<none_t>;

    // TODO: make this default context
    constexpr inline auto NoContext = no_context_t {};

    // NOTE: old version
    // TODO: remove
    // special tag to resolve eval return type
    struct eval_t {};

    // special tag to resolve eval return type
    template <auto BufferLayout=LayoutKind::ROW_MAJOR>
    struct default_type_resolver_t {};

    template <typename resolver_t>
    struct eval_type_resolver_t : resolver_t {};

    template <auto BufferLayout=LayoutKind::ROW_MAJOR>
    using eval_result_t = eval_type_resolver_t<default_type_resolver_t<BufferLayout>>;

    constexpr inline auto RowMajorResolver = meta::as_value_v<eval_result_t<LayoutKind::ROW_MAJOR>>;
    constexpr inline auto ColumnMajorResolver = meta::as_value_v<eval_result_t<LayoutKind::COLUMN_MAJOR>>;
}

namespace nmtools::meta
{
    template <typename T>
    struct is_eval_context : false_type {};

    template <typename T>
    struct is_eval_context<array::context_t<T>> : true_type {};

    template <typename T>
    struct is_eval_type_resolver : false_type {};
    
    template <typename T>
    struct is_eval_type_resolver<array::eval_type_resolver_t<T>> : true_type {};

    template <typename T>
    constexpr inline auto is_eval_context_v = is_eval_context<T>::value;

    template <typename T>
    constexpr inline auto is_eval_type_resolver_v = is_eval_type_resolver<T>::value;
}

namespace nmtools::array
{
    template <typename array_t>
    decltype(auto) get_array(const array_t& array);

    template <typename array_t>
    struct get_array_t
    {
        constexpr inline auto operator()(const array_t& array) const
        {
            if constexpr (meta::is_view_v<array_t>) {
                return get_array(array.array);
            } else if constexpr (meta::is_tuple_v<array_t>) {
                constexpr auto N = meta::len_v<array_t>;
                if constexpr (N == 1) {
                    return get_array(nmtools::get<0>(array));
                } else {
                    return meta::template_reduce<N>([&](auto init, auto index){
                        constexpr auto I = decltype(index)::value;
                        return utility::tuple_append(init,get_array(nmtools::get<I>(array)));
                    }, nmtools_tuple<>{});
                }
            } else if constexpr (meta::is_pointer_v<array_t>) {
                return array;
            } else if constexpr (meta::is_ndarray_v<array_t>) {
                return &array;
            } else if constexpr (meta::is_num_v<array_t>) {
                // return copy
                return array;
            } else {
                static_assert(
                    meta::is_view_v<array_t>
                    || meta::is_pointer_v<array_t>
                    || meta::is_ndarray_v<array_t>
                    || meta::is_tuple_v<array_t>
                    || meta::is_num_v<array_t>
                    , "unsupported array type"
                );
            }
        }
    }; // get_array_t

    template <typename array_t>
    decltype(auto) get_array(const array_t& array)
    {
        constexpr auto f_obj = get_array_t<array_t>{};
        // should return pointer or tuple of pointer
        return f_obj(array);
    }

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
    template <typename view_t, typename context_t, typename resolver_t=eval_t, typename=void>
    struct evaluator_t;

    template <typename view_t, typename resolver_t>
    struct evaluator_t<view_t,none_t,resolver_t>
    {
        using view_type    = const view_t&;
        using context_type = const none_t&;
        // TODO: move output type as template params
        using output_type  = meta::resolve_optype_t<resolver_t,view_t,none_t>;

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
            if constexpr (meta::is_resizable_v<result_t>) {
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

    template <typename resolver_t=eval_t,typename view_t, typename context_t>
    constexpr auto evaluator(const view_t& view, context_t&& context)
    {
        // TODO: perfect forwarding for context
        using ctx_t = meta::remove_cvref_t<context_t>;
        using evaluator_type = evaluator_t<view_t,ctx_t,resolver_t>;
        return evaluator_type{view,nmtools::forward<context_t>(context)};
    } // evaluator

    namespace detail
    {

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_t, typename view_t>
    constexpr auto eval(const view_t& view, context_t&& context=context_t{}, output_t&& output=output_t{}, [[maybe_unused]] meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        if constexpr (meta::is_either_v<view_t>) {
            using left_t   = meta::get_either_left_t<view_t>;
            using right_t  = meta::get_either_right_t<view_t>;
            // deduce return type for each type
            using rleft_t  = decltype(detail::eval(
                meta::declval<left_t>()
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver));
            using rright_t = decltype(detail::eval(
                meta::declval<right_t>()
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver));
            constexpr auto vtype = [](){
                if constexpr (meta::is_same_v<rleft_t,rright_t>) {
                    return meta::as_value_v<rleft_t>;
                } else {
                    using either_t = meta::replace_either_t<view_t,rleft_t,rright_t>;
                    return meta::as_value_v<either_t>;
                }
            }();
            using return_t = meta::type_t<decltype(vtype)>;
            // match either type at runtime
            if (auto view_ptr = nmtools::get_if<left_t>(&view)) {
                return return_t{detail::eval(*view_ptr
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver)};
            } else /* if (auto view_ptr = get_if<right_t>(&view)) */ {
                auto view_rptr = nmtools::get_if<right_t>(&view);
                return return_t{detail::eval(*view_rptr
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver)};
            }
        } else if constexpr (meta::is_maybe_v<view_t>) {
            using view_type   = meta::get_maybe_type_t<view_t>;
            using result_type = decltype(detail::eval(meta::declval<view_type>()
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver));
            static_assert(!meta::is_maybe_v<result_type>);
            using return_type = nmtools_maybe<result_type>;
            return (view
                ? return_type{detail::eval(*view
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver)}
                : return_type{meta::Nothing}
            );
        } else /* if constexpr (meta::is_ndarray_v<view_t> || meta::is_num_v<view_t>) */ {
            static_assert( !meta::is_maybe_v<view_t> && !meta::is_either_v<view_t> );
            auto evaluator_ = evaluator<resolver_t>(view,nmtools::forward<context_t>(context));
            return evaluator_(nmtools::forward<output_t>(output));
        }
    } // eval

    }

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
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_t, typename view_t>
    constexpr auto eval(const view_t& view, context_t&& context=context_t{}, output_t&& output=output_t{}, meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        return detail::eval(view
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }

    namespace detail
    {
        /**
         * @brief Helper function apply eval on tuple of views
         * 
         * @tparam output_t 
         * @tparam context_t 
         * @tparam views_t 
         * @tparam index_sequence 
         * @tparam Is 
         * @param views     tuple of view
         * @param context   eval context
         * @param output 
         * @return constexpr auto 
         */
        template <typename output_t, typename context_t, typename resolver_t, typename views_t, template<auto...>typename index_sequence, auto...Is>
        constexpr auto apply_eval(const views_t& views, context_t&& context, output_t&& output, [[maybe_unused]] resolver_t resolver, index_sequence<Is...>)
        {
            return nmtools_tuple{array::eval(nmtools::get<Is>(views)
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver)
                ...
            };
        } // apply_eval
    } // namespace detail

    /**
     * @brief Helper function to apply eval for each tuple on tuple of views
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam views_t 
     * @param views     tuple of view
     * @param context   eval context
     * @param output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename views_t>
    constexpr auto apply_eval(const views_t& views
        , context_t&& context=context_t{}, output_t&& output=output_t{}
        , meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        if constexpr (meta::is_maybe_v<views_t>) {
            using views_type  = meta::get_maybe_type_t<views_t>;
            using result_type = decltype(apply_eval(
                  meta::declval<views_type>()
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver
            ));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>,result_type,nmtools_maybe<result_type>>;
            if (static_cast<bool>(views)) {
                return return_type{apply_eval(*views
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                )};
            } else {
                return return_type{meta::Nothing};
            }
        } else if constexpr (meta::is_list_v<views_t>) {
            using eval_t = decltype(eval(at(views,0)
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver
            ));
            using result_t = meta::replace_value_type_t<views_t,eval_t>;
            auto res = result_t {};
            auto n = len(views);
            for (size_t i=0; i<n; i++) {
                auto view_i = at(views,i);
                res.push_back(eval(view_i
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver
                ));
            }
            return res;
        } else {
            constexpr auto N = meta::len_v<views_t>;
            return detail::apply_eval(views
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver
                , meta::make_index_sequence_v<N>
            );
        }
    } // apply_eval

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

        template <typename...>
        struct EVAL_RESULT_UNSUPPORTED : detail::fail_t {};
    } // namespace error::eval

    // TODO: remove
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
            using type = meta::type_t<make_dynamic_ndarray<element_t>>;
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
                    using type = nmtools_tuple<stype>;
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
            /* && (is_ndarray_v<array_t>) */
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
            using type = type_t<make_dynamic_ndarray<element_t>>;
            return as_value_v<type>;
        } else if constexpr (
               is_num_v<array_t>
            && is_fixed_size_ndarray_v<view_type>
        ) {
            constexpr auto shape = fixed_ndarray_shape_v<view_type>;
            constexpr auto dim   = fixed_ndarray_dim_v<view_type>;
            constexpr auto vshape = template_reduce<dim>([&](auto init, auto index){
                constexpr auto s = at(shape,index);
                using type = type_t<decltype(init)>;
                // default impl of make_fixed_ndarray only support integral constant for now
                using stype = ct<s>;
                if constexpr (is_void_v<type>) {
                    using type = nmtools_tuple<stype>;
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
                using type = type_t<make_dynamic_ndarray<element_t>>;
                return as_value_v<type>;
                // return as_value_v<error::EVAL_MISMATCHED_DIM>;
            }
        } else if constexpr (
               is_dynamic_ndarray_v<view_type>
            && is_dynamic_ndarray_v<array_t>
        ) {
            // here, either view_type or array_t is fixed-dim, but not both,
            // for now use default dynamic ndarray
            using type = type_t<make_dynamic_ndarray<element_t>>;
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
            using type = type_t<make_dynamic_ndarray<element_t>>;
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

    // TODO: remove
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
    constexpr auto resolve_binary_array_type(
        [[maybe_unused]] as_value<lhs_t> lhs,
        [[maybe_unused]] as_value<rhs_t> rhs,
        [[maybe_unused]] as_value<view_type> view)
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
            using type = type_t<make_dynamic_ndarray<element_t>>;
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

    // TODO: make this the default eval type resolver
    template <array::LayoutKind BufferLayout, typename view_t>
    struct resolve_optype<
        void, array::eval_type_resolver_t<array::default_type_resolver_t<BufferLayout>>, view_t, none_t
    >
    {
        template <typename buffer_t, typename shape_buffer_t>
        static constexpr auto make_ndarray(as_value<buffer_t>, as_value<shape_buffer_t>)
        {
            if constexpr (BufferLayout == array::LayoutKind::ROW_MAJOR) {
                using type = array::row_major_ndarray_t<buffer_t,shape_buffer_t>;
                return as_value_v<type>;
            } else if constexpr (BufferLayout == array::LayoutKind::COLUMN_MAJOR) {
                using type = array::column_major_ndarray_t<buffer_t,shape_buffer_t>;
                return as_value_v<type>;
            } else {
                using type = error::EVAL_RESULT_UNSUPPORTED<view_t,none_t,as_type<BufferLayout>>;
                return as_value_v<type>;
            }
        }

        static constexpr auto vtype = [](){
            using element_type = get_element_type_t<view_t>;
            using error_type [[maybe_unused]] = error::EVAL_RESULT_UNSUPPORTED<view_t,none_t,as_type<BufferLayout>>;
            // TODO: remove, try to read from `nmtools::shape(declval<view_t>())` instead
            // the following is kept for temporary backward compatibility
            constexpr auto shape  = fixed_shape_v<view_t>;
            constexpr auto dim    = fixed_dim_v<view_t>;
            constexpr auto size   = fixed_size_v<view_t>;
            constexpr auto b_dim  = bounded_dim_v<view_t>;
            constexpr auto b_size = bounded_size_v<view_t>;
            using shape_type  = decltype(shape);
            using dim_type    = decltype(dim);
            using size_type   = decltype(size);
            using b_dim_type  = decltype(b_dim);
            using b_size_type = decltype(b_size);
            using nmtools::len, nmtools::at;
            // constant shape
            constexpr auto c_shape_vtype = [&](){
                if constexpr (!is_fail_v<shape_type>) {
                    return template_reduce<len(shape)-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        return as_value_v<append_type_t<init_type,ct<(size_t)at(shape,ct_v<decltype(index)::value+1>)>>>;
                    }, as_value_v<nmtools_tuple<ct<(size_t)at(shape,ct_v<0>)>>>);
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // clipped shape
            constexpr auto cl_shape_vtype = [&](){
                using shape_t = decltype(nmtools::shape(declval<view_t>()));
                if constexpr (is_clipped_index_array_v<shape_t>) {
                    return as_value_v<shape_t>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // fixed shape
            constexpr auto f_shape_vtype = [&](){
                if constexpr (!is_fail_v<dim_type>) {
                    using type = nmtools_array<size_t,dim>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // bounded shape (for bounded dim)
            constexpr auto b_shape_vtype = [&](){
                if constexpr (!is_fail_v<b_dim_type>) {
                    using type = array::static_vector<size_t,b_dim>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // fixed buffer
            constexpr auto f_buffer_vtype = [&](){
                if constexpr (!is_fail_v<size_type>) {
                    using type = nmtools_array<element_type,size>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();
            // bounded buffer
            constexpr auto b_buffer_vtype = [&](){
                if constexpr (!is_fail_v<type_t<decltype(cl_shape_vtype)>>) {
                    constexpr auto size = index::product(to_value_v<type_t<decltype(cl_shape_vtype)>>);
                    using type = array::static_vector<element_type,size>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<b_size_type>) {
                    using type = array::static_vector<element_type,b_size>;
                    return as_value_v<type>;
                } else {
                    return as_value_v<error_type>;
                }
            }();

            using c_shape_type  [[maybe_unused]] = type_t<decltype(c_shape_vtype)>;
            using l_shape_type  [[maybe_unused]] = type_t<decltype(cl_shape_vtype)>;
            using f_shape_type  [[maybe_unused]] = type_t<decltype(f_shape_vtype)>;
            using b_shape_type  [[maybe_unused]] = type_t<decltype(b_shape_vtype)>;
            using f_buffer_type [[maybe_unused]] = type_t<decltype(f_buffer_vtype)>;
            using b_buffer_type [[maybe_unused]] = type_t<decltype(b_buffer_vtype)>;
            // dynamic buffer
            using d_buffer_type [[maybe_unused]] = nmtools_list<element_type>;
            // TODO: add small vector optimization fo shape
            using d_shape_type  [[maybe_unused]] = nmtools_list<size_t>;

            if constexpr (is_num_v<view_t>) {
                return as_value_v<element_type>;
            // prefer constant-shape, no-dynamic allocation
            } else if constexpr (
                !is_fail_v<c_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<c_shape_type>);
            } else if constexpr (
                !is_fail_v<c_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<c_shape_type>);
            } else if constexpr (
                !is_fail_v<l_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<l_shape_type>);
            } else if constexpr (
                !is_fail_v<l_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<l_shape_type>);
            } else if constexpr (
                !is_fail_v<f_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<f_shape_type>);
            } else if constexpr (
                !is_fail_v<f_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<f_shape_type>);
            }
            // bounded shape
            else if constexpr (
                !is_fail_v<b_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<b_shape_type>);
            } else if constexpr (
                !is_fail_v<b_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<b_shape_type>);
            }
            // dynamic shape
            else if constexpr (
                !is_fail_v<d_shape_type>
                && !is_fail_v<f_buffer_type>
            ) {
                return make_ndarray(as_value_v<f_buffer_type>,as_value_v<d_shape_type>);
            } else if constexpr (
                !is_fail_v<d_shape_type>
                && !is_fail_v<b_buffer_type>
            ) {
                return make_ndarray(as_value_v<b_buffer_type>,as_value_v<d_shape_type>);
            } else if constexpr (
                !is_fail_v<c_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<c_shape_type>);
            } else if constexpr (
                !is_fail_v<l_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<l_shape_type>);
            } else if constexpr (
                !is_fail_v<f_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<f_shape_type>);
            } else if constexpr (
                !is_fail_v<b_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<b_shape_type>);
            } else if constexpr (
                !is_fail_v<d_shape_type>
                && !is_fail_v<d_buffer_type>
            ) {
                return make_ndarray(as_value_v<d_buffer_type>,as_value_v<d_shape_type>);
            } else {
                return as_value_v<error_type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };

    /**
     * @brief Old implementation of type resolver for eval op with None execution.
     * 
     * At the moment the implementation should be working for various view type
     * such as ufuncs, outer_ufuncs, accumulate_ufuncs, arange, atleast_1d, full, ones, zeros, flip.
     * Some views are known to have its own specialization, such as reduce_ufuncs, atleast_2d, broadcast_to.
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