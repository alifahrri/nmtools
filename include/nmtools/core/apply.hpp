#ifndef NMTOOLS_CORE_APPLY_HPP
#define NMTOOLS_CORE_APPLY_HPP

namespace nmtools::functional
{
    template <typename F, typename operands_t, typename attributes_t>
    struct apply_function_t<
        functor_t<F,operands_t,attributes_t>
    > {
        using functor_type = functor_t<F,operands_t,attributes_t>;

        static constexpr auto arity = functor_type::arity;

        functor_type functor;

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const
        {
            if constexpr (arity == 0 && sizeof...(m_operands_t) == 0) {
                // assume operands is empty_operands_t
                static_assert( meta::is_same_v<operands_t,meta::empty_operands_t>
                    , "internal error: expect operands is empty for arity 0" );
                return functor.fmap(functor.attributes,functor.operands);
            } else if constexpr (arity > 0 && sizeof...(m_operands_t) == 0) {
                return (*this);
            } else if constexpr (sizeof...(m_operands_t) > arity) {
                // split operands, in which operand's size match arity
                auto m_new_operands = pack_operands(new_operands...);
                auto operand = utility::tuple_slice(m_new_operands,None,meta::ct_v<arity>);
                auto curried_operands = utility::tuple_slice(m_new_operands,meta::ct_v<arity>);
                static_assert( meta::len_v<decltype(operand)> == arity );

                // apply on matched arity
                auto result = apply(operand);

                auto result_operands = [&](){
                    if constexpr (meta::is_tuple_v<decltype(result)>) {
                        return cat_operands(result,curried_operands);
                    } else {
                        return push_operands(result,curried_operands);
                    }
                }();
                return result_operands;
            } else {
                using operands_pack_t = meta::pack_operands_type_t<F,operands_t,m_operands_t...>;
                using function_t = functor_t<F,operands_pack_t,attributes_t>;
                [[maybe_unused]] auto function = function_t{{functor.fmap
                    ,initialize_operands<operands_pack_t>(functor.operands,new_operands...)
                    ,functor.attributes
                }};
                if constexpr (sizeof...(m_operands_t) < arity) {
                    // currying
                    return function;
                } else {
                    // apply
                    if constexpr (meta::is_same_v<attributes_t,meta::empty_attributes_t>) {
                        // NOTE: avoid passing empty_attributes_t to fmap, use empty tuple instead
                        return function.fmap(nmtools_tuple{},function.operands);
                    } else {
                        return function.fmap(function.attributes,function.operands);
                    }
                }
            }
        }

        template <template<typename...>typename m_tuple, typename...m_operands_t, auto...Is>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands, meta::index_sequence<Is...>) const
        {
            // TODO: propagate error handling
            if constexpr (meta::is_maybe_v<m_tuple<m_operands_t...>>) {
                return (*this)(nmtools::get<Is>(unwrap(new_operands))...);
            } else {
                return (*this)(nmtools::get<Is>(new_operands)...);
            }
        }

        template <template<typename...>typename m_tuple, typename...m_operands_t>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands) const
        {
            return apply(new_operands,meta::make_index_sequence_v<sizeof...(m_operands_t)>);
        }
    }; // apply_function_t<functor_t<...>>

    template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
    struct apply_function_t<
        functor_composition_t<tuple<functors_t...>,operands_t>
    > {
        using composition_type = functor_composition_t<tuple<functors_t...>,operands_t>;
        using functors_type = const tuple<functors_t...>;

        static constexpr auto arity = composition_type::arity;

        composition_type functors;

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const
        {
            if constexpr ((meta::is_maybe_v<m_operands_t> || ...)) {
                using result_t = decltype((*this)(unwrap(new_operands)...));
                using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
                return ((has_value(new_operands) && ...)
                    ? return_t{(*this)(unwrap(new_operands)...)}
                    : return_t{meta::Nothing}
                );
            } else {
                using operands_pack_t = meta::pack_operands_type_t<void,operands_t,m_operands_t...>;
                // TODO: rename initialize_operands to forward_array/forward_operand
                auto operands_ = initialize_operands<operands_pack_t>(functors.operands,new_operands...);
                constexpr auto n_operands = meta::len_v<operands_pack_t>;

                auto functor = at(functors.functors,meta::ct_v<-1>);
                using functor_type = meta::remove_cvref_t<decltype(functor)>;
                constexpr auto functor_arity = functor_type::arity;

                if constexpr (n_operands >= functor_arity) {
                    auto curried_operands = utility::tuple_slice(operands_,meta::ct_v<functor_arity>);
                    [[maybe_unused]]
                    constexpr auto n_curried_ops = meta::len_v<decltype(curried_operands)>;
                    auto curried_functors = utility::tuple_slice(functors.functors,None,meta::ct_v<-1>);
                    using curried_functors_t = meta::remove_cvref_t<decltype(curried_functors)>;
                    constexpr auto n_curried_functors = meta::len_v<curried_functors_t>;

                    auto operand = utility::tuple_slice(operands_,None,meta::ct_v<functor_arity>);
                    auto result  = apply_function_t<functor_type>{functor}.apply(operand);

                    auto result_operands = [&](){
                        if constexpr (meta::is_tuple_v<decltype(result)>) {
                            return cat_operands(result,curried_operands);
                        } else {
                            return push_operands(result,curried_operands);
                        }
                    }();

                    if constexpr (n_curried_functors > 0) {
                        return apply_function(functor_composition_t{curried_functors},result_operands);
                    } else if constexpr (n_curried_ops > 0) {
                        return result_operands;
                    } else {
                        #if 1
                        auto operand = utility::tuple_slice(operands_,None,meta::ct_v<functor_arity>);
                        return apply_function_t<functor_type>{functor}.apply(operand);
                        #else
                        // breaks on gcc:
                        return result;
                        #endif
                    }
                } else if constexpr ((arity - n_operands) > 0) {
                    // currying
                    using function_t = functor_composition_t< tuple<functors_t...>,operands_pack_t>;
                    auto function = function_t(functors.functors,operands_);
                    return function;
                }
            }
        } // operator()

        template <template<typename...>typename m_tuple, typename...m_operands_t, auto...Is>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands, meta::index_sequence<Is...>) const
        {
            // TODO: propagate error handling
            if constexpr (meta::is_maybe_v<m_tuple<m_operands_t...>>) {
                return (*this)(nmtools::get<Is>(unwrap(new_operands))...);
            } else {
                return (*this)(nmtools::get<Is>(new_operands)...);
            }
        }

        template <template<typename...>typename m_tuple, typename...m_operands_t>
        constexpr auto apply(const m_tuple<m_operands_t...>& new_operands) const
        {
            return apply(new_operands,meta::make_index_sequence_v<sizeof...(m_operands_t)>);
        }
    }; // apply_function_t<functor_composition_t<...>>

    template <typename F>
    nmtools_func_attribute // host device
    apply_function_t(const F&) -> apply_function_t<F>;

    namespace error
    {
        template <typename...>
        struct GET_FUNCTION_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_FUNCTION_COMPOSITION_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_OPERANDS_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_FUNCTION_OPERANDS_UNSUPPORTED : meta::detail::fail_t {};

        template <typename...>
        struct GET_GRAPH_UNSUPPORTED : meta::detail::fail_t {};
    }

    template <typename view_t>
    struct get_function_t
    {
        view_t view;

        constexpr auto operator()() const noexcept 
        {
            return error::GET_FUNCTION_UNSUPPORTED<view_t>{};
        }
    }; // get_function_t

    template <template<typename...> typename view_t, typename...Ts>
    constexpr auto get_function(const view::decorator_t<view_t,Ts...>& view)
    {
        using view_type = view::decorator_t<view_t,Ts...>;
        auto get_fn = get_function_t<view_type>{view};
        return get_fn();
    } // get_function

    template <typename view_t>
    struct get_operands_t
    {
        view_t view;

        constexpr auto operator()() const noexcept
        {
            if constexpr (meta::has_operands_fn_v<view_t>) {
                return view.operands();
            } else {
                return error::GET_OPERANDS_UNSUPPORTED<view_t>{};
            }
        }
    };

    template <typename view_t, meta::enable_if_t<meta::is_view_v<meta::remove_cvref_pointer_t<decltype(unwrap(meta::declval<view_t>()))>>,int> = 0>
    constexpr auto get_operands(const view_t& view)
    {
        if constexpr (meta::is_maybe_v<view_t>) {
            using view_type   = meta::get_maybe_type_t<view_t>;
            using result_type = decltype(get_operands(meta::declval<view_type>()));
            using return_type = nmtools_maybe<result_type>;
            return (view
                ? return_type{get_operands(*view)}
                : return_type{meta::Nothing}
            );
        } else {
            using view_type = view_t;
            auto get_operands = get_operands_t<view_type>{view};
            return get_operands();
        }
    }

    template <typename view_t>
    struct get_function_operands_t;

    template <typename view_type>
    constexpr auto get_function_operands(const view_type& view)
    {
        if constexpr (meta::is_maybe_v<view_type>) {
            using result_type = decltype(get_function_operands(*view));
            using return_type = nmtools_maybe<result_type>;
            return (view
                ? return_type{get_function_operands(*view)}
                : return_type{meta::Nothing}
            );
        } else {
            auto get_op = get_function_operands_t<view_type>{view};
            return get_op();
        }
    } // get_function_operands

    template <template<typename...>typename view_t, typename...args_t>
    struct get_function_operands_t<
        view::decorator_t<view_t,args_t...>
    > {
        using view_type = view::decorator_t<view_t,args_t...>;
        view_type view;

        constexpr auto operator()() const noexcept
        {
            auto operands = get_operands(view);
            static_assert( !meta::is_fail_v<decltype(operands)>);
            constexpr auto N = view_type::arity;
            auto all_operands = meta::template_reduce<N>([&](auto init, auto index){
                const auto& operand = nmtools::at(operands,index);
                using operand_t = meta::remove_pointer_t<meta::remove_cvref_t<decltype(operand)>>;
                static_assert(
                    (meta::is_view_v<operand_t>)
                    || ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                        && !meta::is_view_v<operand_t>
                    )
                );
                if constexpr (meta::is_view_v<operand_t>) {
                    return utility::tuple_cat(init, get_function_operands(operand));
                } else if constexpr ((meta::is_num_v<operand_t> || meta::is_ndarray_v<operand_t>)
                    && !meta::is_view_v<operand_t>
                ) {
                    if constexpr ( meta::is_num_v<operand_t> || meta::is_pointer_v<meta::remove_cvref_t<decltype(operand)>> ) {
                        return utility::tuple_append(init, operand);
                    } else /* if constexpr (meta::is_bounded_array_v<operand_t>) */ {
                        return utility::tuple_append<const operand_t&>(init, operand);
                    }
                }
            }, nmtools_tuple{});
            return all_operands;
        }
    }; // get_function_operands_t

    template <typename function_t, typename operands_t>
    nmtools_func_attribute
    constexpr auto apply(const function_t& function, const operands_t& operands)
    {
        if constexpr (meta::is_maybe_v<function_t>) {
            using result_type = meta::remove_cvref_t<decltype(apply(*function,operands))>;
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>,result_type,nmtools_maybe<result_type>>;
            return (function
                ? return_type{apply(*function,operands)}
                : return_type{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<operands_t>) {
            using result_type = decltype(apply(function,*operands));
            using return_type = meta::conditional_t<meta::is_maybe_v<result_type>,result_type,nmtools_maybe<result_type>>;
            return (operands
                ? return_type{apply(function,*operands)}
                : return_type{meta::Nothing}
            );
        } else {
            constexpr auto arity = function_t::arity;
            constexpr auto n_operands = meta::len_v<operands_t>;
            static_assert( arity == n_operands );
            return meta::template_reduce<n_operands>([&](auto init, auto index){
                if constexpr (meta::is_maybe_v<decltype(init)>) {
                    using result_t = decltype(unwrap(init)(nmtools::at(operands,index)));
                    using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
                    return (init
                        ? return_t{unwrap(init)(nmtools::at(operands,index))}
                        : return_t{meta::Nothing}
                    );
                } else {
                    return init (nmtools::at(operands,index));
                }
            }, function());
        }
    } // apply
}

#endif // NMTOOLS_CORE_APPLY_HPP