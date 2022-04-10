#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"

namespace nmtools::meta
{
    struct empty_operands_t {};
    struct empty_attributes_t {};

    // validate attributes is permissive
    template <typename F, typename...attributes_t>
    struct validate_attributes : meta::true_type {};

    template <typename F, typename...attributes_t>
    constexpr inline auto validate_attributes_v = validate_attributes<F,attributes_t...>::value;

    template <typename F, typename...operands_t>
    struct validate_operands
    {
        static constexpr auto value = [](){
            // assume has arity
            constexpr auto arity   = F::arity;
            constexpr auto n_attrs = sizeof...(operands_t);
            return (arity <= n_attrs && static_cast<bool>(n_attrs));
        }();
    };

    template <typename F, typename...operands_t>
    constexpr inline auto validate_operands_v = validate_operands<F,operands_t...>::value;

    using view::resolve_array_type;
    using view::resolve_array_type_t;

    using view::resolve_attribute_type;
    using view::resolve_attribute_type_t;

    template <typename F, typename operands_t, typename...new_operands_t>
    struct pack_operands_type;

    template <typename F, typename...new_operands_t>
    struct pack_operands_type<F,empty_operands_t,new_operands_t...>
    {
        using type = nmtools_tuple<resolve_array_type_t<new_operands_t>...>;
    }; // pack_operands_type

    template <typename F, template<typename...>typename operand_tuple, typename...operands_t, typename...new_operands_t>
    struct pack_operands_type<F,operand_tuple<operands_t...>,new_operands_t...>
    {
        using type = nmtools_tuple<operands_t...,resolve_array_type_t<new_operands_t>...>;
    }; // pack_operands_type

    template <typename F, typename operands_t, typename...new_operands_t>
    using pack_operands_type_t = type_t<pack_operands_type<F,operands_t,new_operands_t...>>;

    template <typename F, typename...attributes_t>
    struct pack_attribute_type
    {
        using type = nmtools_tuple<resolve_attribute_type_t<attributes_t>...>;
    }; // pack_operands_type

    template <typename F, typename...attributes_t>
    using pack_attribute_type_t = type_t<pack_attribute_type<F,attributes_t...>>;

    template <typename T>
    struct is_functor_composition : false_type {};

    template <typename T>
    struct is_functor : false_type {};

    template <typename T>
    constexpr inline auto is_functor_composition_v = is_functor_composition<T>::value;

    template <typename T>
    constexpr inline auto is_functor_v = is_functor<T>::value;
} // namespace nmtools::meta

namespace nmtools::functional
{
    constexpr inline auto EmptyOperands   = meta::empty_operands_t{};
    constexpr inline auto EmptyAttributes = meta::empty_attributes_t{};

    template <typename operand_pack_t, typename...operands_t>
    constexpr auto initialize_operands(meta::empty_operands_t,const operands_t&...operands)
    {
        return operand_pack_t{view::initialize<view::resolve_array_type_t<operands_t>>(operands)...};
    }

    template <typename operand_pack_t, template<typename...>typename operand_tuple, typename...operands_t, template<auto...>typename sequence, auto...Is, typename...new_operands_t>
    constexpr auto initialize_operands(sequence<Is...>,const operand_tuple<operands_t...>& operands,const new_operands_t&...new_operands)
    {
        return operand_pack_t{nmtools::get<Is>(operands)...,view::initialize<view::resolve_array_type_t<new_operands_t>>(new_operands)...};
    }

    template <typename operand_pack_t, template<typename...>typename operand_tuple, typename...operands_t, typename...new_operands_t>
    constexpr auto initialize_operands(const operand_tuple<operands_t...>& operands,const new_operands_t&...new_operands)
    {
        return initialize_operands<operand_pack_t>(meta::make_index_sequence_v<sizeof...(operands_t)>, operands, new_operands...);
    }

    template <typename F, typename operands_t=meta::empty_operands_t, typename attributes_t=meta::empty_attributes_t>
    struct functor_t;

    template <typename functors_t, typename operands_t=meta::empty_operands_t>
    struct functor_composition_t;

    template <template<typename...>typename tuple, typename...functors_t, typename operands_t>
    struct functor_composition_t<tuple<functors_t...>,operands_t>
    {
        using functors_type = const tuple<functors_t...>;
        using operands_type = const operands_t;

        functors_type functors;
        operands_type operands;

        constexpr functor_composition_t()
            : functors{}
            , operands{}
        {}

        constexpr functor_composition_t(functors_type& functors)
            : functors(functors)
            , operands{}
        {}

        constexpr functor_composition_t(functors_type& functors, const operands_t& operands)
            : functors(functors)
            , operands{operands}
        {}

        static constexpr auto arity = [](){
            using functors = meta::type_list<functors_t...>;
            constexpr auto n_functors = sizeof...(functors_t);
            auto arity = 0;
            meta::template_for<n_functors>([&](auto index){
                constexpr auto I = decltype(index)::value;
                auto arity_i = meta::type_list_at_t<I,functors>::arity;
                // NOTE: the result from one functor will be passed to the following functor, so -1 except the right-most
                arity += (I == n_functors - 1 ? arity_i : (arity_i-1));
            });
            return arity;
        }();

        // NOTE: after composing functor, specifying attribute not supported anymore

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const noexcept
        {
            using operands_pack_t = meta::pack_operands_type_t<void,operands_t,m_operands_t...>;
            auto operands_ = initialize_operands<operands_pack_t>(operands,new_operands...);
            // TODO: constraint number of operands to be <= arity
            if constexpr ((arity - meta::len_v<operands_pack_t>) > 0) {
                // currying
                using function_t = functor_composition_t< tuple<functors_t...>,operands_pack_t>;
                auto function    = function_t{functors,operands_};
                return function;
            } else {
                // apply
                // TODO: starting from right-most functor, apply N operands then use the result to the next functor
                // where N = arity_i for the right-most functor, and N-1 for the rest
                using namespace literals;
                constexpr auto N = meta::len_v<functors_type>;
                const auto& [result, idx] = meta::template_reduce<N>([&](const auto& init, auto index){
                    constexpr auto I = (N-1) - decltype(index)::value;
                    const auto& functor = nmtools::get<I>(functors);
                    const auto& [prev_result, operand_idx] = init;
                    using functor_t      = meta::remove_cvref_t<decltype(functor)>;
                    using prev_result_t  = meta::remove_cvref_t<decltype(prev_result)>;
                    constexpr auto arity_ = functor_t::arity;
                    [[maybe_unused]] constexpr auto op_idx = decltype(operand_idx)::value;
                    [[maybe_unused]] auto next_op_idx = meta::ct_v<op_idx+arity_>;

                    if constexpr ((arity_ == 1) && meta::is_same_v<prev_result_t,meta::empty_operands_t>) {
                        return nmtools_tuple{functor(nmtools::get<op_idx>(operands_)),next_op_idx};
                    } else if constexpr (arity_ == 1) {
                        // no need to retrieve operands, just keep operand_idx
                        return nmtools_tuple{functor(prev_result),operand_idx};
                    } else if constexpr (meta::is_same_v<prev_result_t,meta::empty_operands_t>) {
                        // NOTE: this case may be encountered at the first apply when arity > 1
                        auto result_ = meta::template_reduce<arity_-1>([&](auto f, auto index){
                            constexpr auto II = decltype(index)::value + 1;
                            return f(nmtools::get<op_idx+II>(operands_));
                        }, functor(nmtools::get<op_idx>(operands_)));
                        return nmtools_tuple{result_, next_op_idx};
                    } else {
                        // NOTE: similar to above but use prev result as init
                        auto result_ = meta::template_reduce<arity_-1>([&](auto f, auto index){
                            constexpr auto II = decltype(index)::value;
                            return f(nmtools::get<op_idx+II>(operands_));
                        }, functor(prev_result));
                        return nmtools_tuple{result_, next_op_idx};
                    }
                }, nmtools_tuple{EmptyOperands,0_ct});
                return result;
            }
        } // operator()
    }; // functor_composition_t

    template <template<typename...>typename tuple, typename...functors_t>
    functor_composition_t(const tuple<functors_t...>&) -> functor_composition_t<tuple<functors_t...>>;

    template <typename F, typename operands_t, typename attributes_t>
    struct functor_t
    {
        using fmap_type       = const F;
        using operands_type   = const operands_t;
        using attributes_type = const attributes_t;

        static constexpr auto arity = [](){
            if constexpr (meta::is_same_v<operands_t,meta::empty_operands_t>) {
                return F::arity;
            } else {
                return F::arity - meta::len_v<operands_t>;
            }
        }();

        fmap_type       fmap;
        operands_type   operands;
        attributes_type attributes;

        // error on clang but fine on gcc
        // constexpr functor_t() = default;

        // error on gcc but fine on clang
        // constexpr functor_t() {}

        constexpr functor_t()
            : fmap{}
            , operands{}
            , attributes{}
        {}

        constexpr functor_t(const F& fmap)
            : fmap(fmap)
            , operands{}
            , attributes{}
        {}
        
        constexpr functor_t(const F& fmap, const operands_t& operands, const attributes_t& attributes)
            : fmap(fmap)
            , operands(operands)
            , attributes(attributes)
        {}

        template <typename other_f, typename other_operands, typename other_attributes>
        constexpr auto operator*(const functor_t<other_f,other_operands,other_attributes>& other) const noexcept
        {
            // TODO: check arity, only compose if there's enough arity left
            using other_functor_t = functor_t<other_f,other_operands,other_attributes>;
            using composition_t   = functor_composition_t<nmtools_tuple<functor_t,other_functor_t>>;
            return composition_t{{*this,other}};
        } // operator*

        template <template<typename...>typename tuple, typename...functors_t, typename m_operands_t>
        constexpr auto operator*(const functor_composition_t<tuple<functors_t...>,m_operands_t>& other) const noexcept
        {
            // TODO: check arity, only compose if there's enough arity left
            auto functors = view::detail::tuple_append(other.functors,*this);
            return functor_composition_t{functors};
        }

        template <typename m_attribute_t>
        constexpr auto operator[](const m_attribute_t& new_attribute) const noexcept
        {
            // NOTE: since operator[] can only takes SINGLE argument,
            // use nested operator[] to allow specifying multiple attributes.
            if constexpr (meta::is_same_v<attributes_t,meta::empty_attributes_t>) {
                // prefer to make functor copy-able and not taking ref/address
                // so it is safe to return local copy
                using new_attribute_t = view::resolve_attribute_type_t<m_attribute_t>;
                using function_t = functor_t<F,operands_t,nmtools_tuple<new_attribute_t>>;
                return function_t{fmap,operands,nmtools_tuple{view::init_attribute<new_attribute_t>(new_attribute)}};
            } else {
                using new_attribute_t = view::resolve_attribute_type_t<m_attribute_t>;
                auto new_attributes = view::detail::tuple_append(attributes,view::init_attribute<new_attribute_t>(new_attribute));
                using new_attributes_t = decltype(new_attributes);
                using function_t = functor_t<F,operands_t,new_attributes_t>;
                return function_t{fmap,operands,new_attributes};
            }
        } // operator[]

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const noexcept
        {
            using operands_pack_t = meta::pack_operands_type_t<F,operands_t,m_operands_t...>;
            using function_t = functor_t<F,operands_pack_t,attributes_t>;
            auto function = function_t{fmap,initialize_operands<operands_pack_t>(operands,new_operands...),attributes};
            if constexpr (sizeof...(m_operands_t) < arity) {
                // currying
                return function;
            } else {
                // apply
                if constexpr (meta::is_same_v<attributes_t,meta::empty_attributes_t>) {
                    // NOTE: avoid passing empty_attribute_t to fmap, use empty tuple instead
                    return function.fmap(nmtools_tuple<>{},function.operands);
                } else {
                    return function.fmap(function.attributes,function.operands);
                }
            }
        } // operator()
    }; // functor_t

    template <typename F>
    functor_t(const F) -> functor_t<F,meta::empty_operands_t,meta::empty_attributes_t>;

    template <template<typename...>typename left_tp, typename...left_functors_t, typename left_operands_t
        , template<typename...>typename right_tp, typename...right_functors_t, typename right_operands_t>
    constexpr auto operator*(const functor_composition_t<left_tp<left_functors_t...>,left_operands_t>& left
        , const functor_composition_t<right_tp<right_functors_t...>,right_operands_t>& right) noexcept
    {
        // NOTE: no need to check arity, assume will be applied if operands is complete
        auto joined_functors = view::detail::tuple_cat(left.functors,right.functors);
        return functor_composition_t{joined_functors};
    } // operator*

    template <template<typename...>typename left_tp, typename...left_functors_t, typename left_operands_t
        , typename F, typename operands_t, typename attributes_t>
    constexpr auto operator*(const functor_composition_t<left_tp<left_functors_t...>,left_operands_t>& left
        , const functor_t<F,operands_t,attributes_t>& right) noexcept
    {
        auto joined_functors = view::detail::tuple_append(left.functors,right);
        return functor_composition_t{joined_functors};
    } // operator*

} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP