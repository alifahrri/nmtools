#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"

namespace nmtools::meta
{
    struct empty_operands_t {};
    struct empty_attributes_t {};

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

    /**
     * @brief Type constructor to compose functors.
     * 
     * Note that after composing, functor's attributes can't be specified.
     * Can only specify operands, or further composing with another functor/composition.
     * 
     * @tparam tuple 
     * @tparam functors_t 
     * @tparam operands_t 
     */
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

        nmtools_func_attribute
        ~functor_composition_t() = default;

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

    /**
     * @brief Type constructor for functor type.
     * 
     * Takes fmap, can curry operands and compose with another functors.
     * 
     * @tparam F 
     * @tparam operands_t 
     * @tparam attributes_t 
     */
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

    /**
     * @brief Type constructor for binary fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    struct binary_fmap_t
    {
        static constexpr auto arity = 2;
        
        F fn;

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename lhs_t, typename rhs_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<lhs_t,rhs_t>& operands) const
        {
            const auto& [lhs, rhs] = operands;
            if constexpr (meta::is_pointer_v<lhs_t> && meta::is_pointer_v<rhs_t>) {
                return fn(*lhs,*rhs,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<lhs_t>) {
                return fn(*lhs,rhs,nmtools::get<Is>(attributes)...);
            } else if constexpr (meta::is_pointer_v<rhs_t>) {
                return fn(lhs,*rhs,nmtools::get<Is>(attributes)...);
            } else {
                return fn(lhs,rhs,nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...arrays_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<arrays_t...>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    }; // binary_fmap_t

    /**
     * @brief Type constructor for unary fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    struct unary_fmap_t
    {
        static constexpr auto arity = 1;

        F fn;

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename array_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<array_t>& operands) const
        {
            if constexpr (meta::is_pointer_v<array_t>) {
                return fn(*nmtools::get<0>(operands),nmtools::get<Is>(attributes)...);
            } else {
                return fn(nmtools::get<0>(operands),nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...arrays_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<arrays_t...>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    }; // unary_fmap_t

    /**
     * @brief Type constructor for ternary (arity of 3) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    struct ternary_fmap_t
    {
        static constexpr auto arity = 3;

        F fn;

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename a_t, typename b_t, typename c_t>
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<a_t,b_t,c_t>& operands) const
        {
            using meta::is_pointer_v;

            const auto& [a, b, c] = operands;
            if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<c_t>) {
                return fn(*a, *b, *c,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<c_t>) {
                return fn(a,*b,*c,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t>) {
                return fn(*a, *b, c,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<c_t>) {
                return fn(*a, b, *c,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t>) {
                return fn(*a, b, c,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t>) {
                return fn(a, *b, c,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<c_t>) {
                return fn(a, b, *c,nmtools::get<Is>(attributes)...);
            } else {
                return fn(a, b, c,nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...arrays_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<arrays_t...>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    }; // ternary_fmap_t

    /**
     * @brief Type constructor for quaternary (arity of 4) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    struct quaternary_fmap_t
    {
        static constexpr auto arity = 4;

        F fn;

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename a_t, typename b_t, typename c_t, typename d_t>
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<a_t,b_t,c_t,d_t>& operands) const
        {
            using meta::is_pointer_v;

            const auto& [a, b, c, d] = operands;
            if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(*a, *b, *c, *d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(a,*b,*c,*d,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<d_t>) {
                return fn(*a, *b, c, *d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(*a, b, *c, *d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<d_t>) {
                return fn(*a, b, c, *d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<d_t>) {
                return fn(a, *b, c, *d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(a, b, *c, *d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<c_t>) {
                return fn(*a, *b, *c, d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<c_t>) {
                return fn(a,*b,*c, d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t>) {
                return fn(*a, *b, c, d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<c_t>) {
                return fn(*a, b, *c, d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t>) {
                return fn(*a, b, c, d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t>) {
                return fn(a, *b, c, d, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<c_t>) {
                return fn(a, b, *c, d, nmtools::get<Is>(attributes)...);
            } else {
                return fn(a, b, c, d, nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...arrays_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<arrays_t...>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    }; // quaternary_fmap_t

    /**
     * @brief Type constructor for quinary (arity of 5) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    struct quinary_fmap_t
    {
        static constexpr auto arity = 5;

        F fn;

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename a_t, typename b_t, typename c_t, typename d_t, typename e_t>
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<a_t,b_t,c_t,d_t,e_t>& operands) const
        {
            using meta::is_pointer_v;

            const auto& [a, b, c, d, e] = operands;
            if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<d_t> && is_pointer_v<e_t>) {
                return fn(*a, *b, *c, *d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<d_t> && is_pointer_v<e_t>) {
                return fn(a,*b,*c,*d,*e,nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<d_t> && is_pointer_v<e_t>) {
                return fn(*a, *b, c, *d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<c_t> && is_pointer_v<d_t> && is_pointer_v<e_t>) {
                return fn(*a, b, *c, *d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<d_t> && is_pointer_v<e_t>) {
                return fn(*a, b, c, *d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<d_t> && is_pointer_v<e_t>) {
                return fn(a, *b, c, *d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<c_t> && is_pointer_v<d_t> && is_pointer_v<e_t>) {
                return fn(a, b, *c, *d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<e_t>) {
                return fn(*a, *b, *c, d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<e_t>) {
                return fn(a,*b,*c, d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<e_t>) {
                return fn(*a, *b, c, d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<c_t> && is_pointer_v<e_t>) {
                return fn(*a, b, *c, d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<e_t>) {
                return fn(*a, b, c, d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<e_t>) {
                return fn(a, *b, c, d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<c_t> && is_pointer_v<e_t>) {
                return fn(a, b, *c, d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(*a, *b, *c, *d, *e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(a,*b,*c,*d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<d_t>) {
                return fn(*a, *b, c, *d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(*a, b, *c, *d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<d_t>) {
                return fn(*a, b, c, *d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<d_t>) {
                return fn(a, *b, c, *d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<c_t> && is_pointer_v<d_t>) {
                return fn(a, b, *c, *d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t> && is_pointer_v<c_t>) {
                return fn(*a, *b, *c, d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t> && is_pointer_v<c_t>) {
                return fn(a,*b,*c, d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<b_t>) {
                return fn(*a, *b, c, d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t> && is_pointer_v<c_t>) {
                return fn(*a, b, *c, d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<a_t>) {
                return fn(*a, b, c, d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<b_t>) {
                return fn(a, *b, c, d, e, nmtools::get<Is>(attributes)...);
            } else if constexpr (is_pointer_v<c_t>) {
                return fn(a, b, *c, d, e, nmtools::get<Is>(attributes)...);
            } else {
                return fn(a, b, c, d, e, nmtools::get<Is>(attributes)...);
            }
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...arrays_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<arrays_t...>& operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    }; // quinary_fmap_t

    template <typename F>
    binary_fmap_t(F&&) -> binary_fmap_t<F>;

    template <typename F>
    unary_fmap_t(F&&) -> unary_fmap_t<F>;

    template <typename F>
    ternary_fmap_t(F&&) -> ternary_fmap_t<F>;

    template <typename F>
    quaternary_fmap_t(F&&) -> quaternary_fmap_t<F>;

    template <typename F>
    quinary_fmap_t(F&&) -> quinary_fmap_t<F>;

    namespace error
    {
        template <typename...>
        struct GET_FUNCTION_UNSUPPORTED : meta::detail::fail_t {};
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
        using array_type = typename view_type::array_type;
        auto get_fn = get_function_t<view_type>{view};
        if constexpr (view::is_view_v<array_type>) {
            return get_fn() * get_function(view.array);
        #if 0
        } else if constexpr (meta::is_tuple_v<array_type>) {
            const auto& array_pack = view.array;
            constexpr auto N = meta::len_v<decltype(array_pack)>;
            return meta::template_reduce<N>([&](auto init, auto index){
                const auto& array = nmtools::get<index>(array_pack);
                using array_type = meta::remove_cvref_pointer_t<decltype(array)>;
                constexpr auto is_view = view::is_view_v<array_type>;
                if constexpr (is_view && meta::is_pointer_v<decltype(array)>) {
                    return init * get_function(*array);
                } else if constexpr (is_view) {
                    return init * get_function(array);
                } else {
                    return init;
                }
            }, get_fn());
        #endif
        } else {;
            return get_fn();
        }
    } // get_function
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP