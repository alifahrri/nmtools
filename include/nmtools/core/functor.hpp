#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP

#include "nmtools/meta.hpp"
#include "nmtools/core/fmap.hpp"
#include "nmtools/core/decorator.hpp"
#include "nmtools/core/alias.hpp"
#include "nmtools/utility/ct_map.hpp"
#include "nmtools/utility/ct_digraph.hpp"
#include "nmtools/utility/tuple_slice.hpp"
#include "nmtools/utility/isequal/isequal.hpp"
#include "nmtools/utility/isclose/isclose.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/unwrap.hpp"

// TODO: remove, use utility/fwd
namespace nmtools::meta
{
    using view::resolve_attribute_type;
    using view::resolve_attribute_type_t;

    template <typename F, typename operands_t, typename...new_operands_t>
    struct pack_operands_type;

    template <typename F, typename...new_operands_t>
    struct pack_operands_type<F,empty_operands_t,new_operands_t...>
    {
        using type = nmtools_tuple<fwd_operand_t<new_operands_t>...>;
    }; // pack_operands_type

    template <typename F, template<typename...>typename operand_tuple, typename...operands_t, typename...new_operands_t>
    struct pack_operands_type<F,operand_tuple<operands_t...>,new_operands_t...>
    {
        using type = nmtools_tuple<operands_t...,fwd_operand_t<new_operands_t>...>;
    }; // pack_operands_type

    template <typename F, typename operands_t, typename...new_operands_t>
    using pack_operands_type_t = type_t<pack_operands_type<F,operands_t,new_operands_t...>>;
} // namespace nmtools::meta

// TODO: move to meta/bits/traits (?)
namespace nmtools::meta
{
    template <typename,typename>
    struct is_same_functor : false_type {};

    template <typename F, typename rhs_t>
    constexpr inline auto is_same_functor_v = is_same_functor<F,rhs_t>::value;
}

namespace nmtools::functional
{
    // TODO: refactor to not use empty_operands_t & empty_attributes_t
    constexpr inline auto EmptyOperands   = meta::empty_operands_t{};
    constexpr inline auto EmptyAttributes = meta::empty_attributes_t{};

    template <typename operand_pack_t, typename...operands_t>
    constexpr auto initialize_operands(meta::empty_operands_t,const operands_t&...operands)
    {
        return operand_pack_t{fwd_operand(operands)...};
    }

    template <typename operand_pack_t, template<typename...>typename operand_tuple, typename...operands_t, template<auto...>typename sequence, auto...Is, typename...new_operands_t>
    constexpr auto initialize_operands(sequence<Is...>,const operand_tuple<operands_t...>& operands,const new_operands_t&...new_operands)
    {
        return operand_pack_t{nmtools::get<Is>(operands)...,fwd_operand(new_operands)...};
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

    template <typename F>
    struct apply_function_t;

    template <typename F, template<typename...>typename tuple, typename...new_operands_t>
    constexpr auto apply_function(const F& function, const tuple<new_operands_t...>& new_operands)
    {
        // TODO: better error handling
        if constexpr (meta::is_maybe_v<F>) {
            return apply_function(*function, new_operands);
        } else {
            // Triggers gcc error:
            // error: initializations for multiple members of 'std::_Optional_payload_base
            #if defined(__clang__)
            auto result = apply_function_t<F>{function}.apply(new_operands);
            if constexpr (meta::is_tuple_v<decltype(result)>) {
                meta::template_for<meta::len_v<decltype(result)>>([&](auto index){
                    using value_t = meta::at_t<decltype(result),decltype(index)::value>;
                    static_assert( !meta::is_fail_v<value_t>
                        , "the return of apply function is invalid!" );
                });
            } else {
                static_assert( !meta::is_fail_v<decltype(result)>
                    , "the return of apply function is invalid!" );
            }
            return result;
            #else
            return apply_function_t<F>{function}.apply(new_operands);
            #endif
        }
    } // apply_function

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

        static constexpr auto stack_inference_result = [](){
            using functors = meta::type_list<functors_t...>;
            constexpr auto n_functors = sizeof...(functors_t);
            nm_index_t arity = 0;
            nm_index_t stack = 0;
            meta::template_for<n_functors>([&](auto index){
                constexpr auto I = (n_functors-1) - decltype(index)::value;
                using functor_t = meta::at_t<functors,I>;
                if constexpr (index == 0) {
                    // first
                    arity = functor_t::arity;
                    stack = functor_t::n_outputs;
                } else {
                    auto m_arity = functor_t::arity;
                    auto n_outputs = functor_t::n_outputs;
                    if ((nm_index_t)stack < (nm_index_t)m_arity) {
                        arity += (m_arity - stack);
                    }
                    if ((nm_index_t)stack < (nm_index_t)m_arity) {
                        // overwrite
                        stack = n_outputs;
                    } else {
                        stack += (n_outputs - m_arity);
                    }
                }
            });
            return nmtools_array{arity,stack};
        }();
        static constexpr auto arity     = stack_inference_result[0];
        static constexpr auto n_outputs = stack_inference_result[1];

        // NOTE: after composing functor, specifying attribute not supported anymore

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const noexcept
        {
            auto operand_pack = pack_operands(new_operands...);
            using operand_pack_t = decltype(operand_pack);
            if constexpr (meta::is_maybe_v<operand_pack_t>) {
                using result_t = decltype(apply_function(*this,unwrap(operand_pack)));
                using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
                return (operand_pack
                    ? return_t{apply_function(*this,unwrap(operand_pack))}
                    : return_t{meta::Nothing}
                );
            } else {
                return apply_function(*this,operand_pack);
            }
        } // operator()
    }; // functor_composition_t

    template <template<typename...>typename tuple, typename...functors_t, typename operands_t, typename other_t>
    constexpr auto operator*(const nmtools_maybe<functor_composition_t<tuple<functors_t...>,operands_t>>& maybe_functor, const other_t& other)
    {
        if constexpr (meta::is_functor_v<decltype(unwrap(other))>) {
            using result_t = decltype(unwrap(maybe_functor) * other);
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(maybe_functor)
                ? return_t{unwrap(maybe_functor) * other}
                : return_t{meta::Nothing}
            );
        } else {
            // quick implementation to allow chaining maybe functor with operand
            // since operator() can't be defined as non-member, use operator*
            // TODO: generalize to unify functor chaining with application
            using result_t = decltype(unwrap(maybe_functor)(other));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(maybe_functor)
                ? return_t{unwrap(maybe_functor)(other)}
                : return_t{meta::Nothing}
            );
        }
    }

    template <template<typename...>typename tuple, typename...functors_t>
    nmtools_func_attribute
    functor_composition_t(const tuple<functors_t...>&) -> functor_composition_t<tuple<functors_t...>>;

    namespace detail
    {
        template <typename F, typename operands_t, typename attributes_t>
        struct default_constructible_functor_t
        {
            using fmap_type       = const F;
            using operands_type   = const operands_t;
            using attributes_type = const attributes_t;

            // TODO: also consider number of output, now that support multiple return
            static constexpr auto arity = [](){
                if constexpr (meta::is_same_v<operands_t,meta::empty_operands_t>) {
                    return F::arity;
                } else {
                    return F::arity - meta::len_v<operands_t>;
                }
            }();
            static constexpr auto n_outputs = F::n_outputs;

            static_assert(
                meta::is_default_constructible_v<F>
                && meta::is_default_constructible_v<operands_t>
                && meta::is_default_constructible_v<attributes_t>
            );

            fmap_type       fmap;
            operands_type   operands;
            attributes_type attributes;

            // error on clang but fine on gcc
            // constexpr functor_t() = default;

            // error on gcc but fine on clang
            // constexpr functor_t() {}

            constexpr default_constructible_functor_t()
                : fmap{}
                , operands{}
                , attributes{}
            {}

            constexpr default_constructible_functor_t(const default_constructible_functor_t& other)
                : fmap{other.fmap}
                , operands{other.operands}
                , attributes{other.attributes}
            {}

            constexpr default_constructible_functor_t(const F& fmap)
                : fmap(fmap)
                , operands{}
                , attributes{}
            {}
            
            constexpr default_constructible_functor_t(const F& fmap, const operands_t& operands, const attributes_t& attributes)
                : fmap(fmap)
                , operands(operands)
                , attributes(attributes)
            {}
        };

        template <typename F, typename operands_t, typename attributes_t>
        struct non_default_constructible_functor_t
        {
            using fmap_type       = const F;
            using operands_type   = const operands_t;
            using attributes_type = const attributes_t;

            // TODO: also consider number of output, now that support multiple return
            static constexpr auto arity = [](){
                if constexpr (meta::is_same_v<operands_t,meta::empty_operands_t>) {
                    return F::arity;
                } else {
                    return F::arity - meta::len_v<operands_t>;
                }
            }();
            static constexpr auto n_outputs = F::n_outputs;

            fmap_type       fmap;
            operands_type   operands;
            attributes_type attributes;

            // error on clang but fine on gcc
            // constexpr functor_t() = default;

            // error on gcc but fine on clang
            // constexpr functor_t() {}

            constexpr non_default_constructible_functor_t(const non_default_constructible_functor_t& other)
                : fmap{other.fmap}
                , operands{other.operands}
                , attributes{other.attributes}
            {}

            constexpr non_default_constructible_functor_t(const F& fmap)
                : fmap(fmap)
                , operands{}
                , attributes{}
            {}
            
            constexpr non_default_constructible_functor_t(const F& fmap, const operands_t& operands, const attributes_t& attributes)
                : fmap(fmap)
                , operands(operands)
                , attributes(attributes)
            {}
        };

        template <typename F, typename operands_t, typename attributes_t>
        using functor_base_t = meta::conditional_t<
            (
                meta::is_default_constructible_v<F>
                && meta::is_default_constructible_v<operands_t>
                && meta::is_default_constructible_v<attributes_t>
            )
            , default_constructible_functor_t<F,operands_t,attributes_t>
            , non_default_constructible_functor_t<F,operands_t,attributes_t>
        >;
    }

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
    struct functor_t : detail::functor_base_t<F,operands_t,attributes_t>
    {
        using base = detail::functor_base_t<F,operands_t,attributes_t>;

        using base::fmap, base::operands, base::attributes;

        using base::arity, base::n_outputs;

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
            auto functors = utility::tuple_cat(nmtools_tuple{*this},other.functors);
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
                // TODO: use fwd_attribute
                using new_attribute_t = view::resolve_attribute_type_t<m_attribute_t>;
                using function_t = functor_t<F,operands_t,nmtools_tuple<new_attribute_t>>;
                return function_t{{fmap,operands,nmtools_tuple{view::init_attribute<new_attribute_t>(new_attribute)}}};
            } else {
                using new_attribute_t = view::resolve_attribute_type_t<m_attribute_t>;
                auto new_attributes = utility::tuple_append(attributes,view::init_attribute<new_attribute_t>(new_attribute));
                using new_attributes_t = decltype(new_attributes);
                using function_t = functor_t<F,operands_t,new_attributes_t>;
                return function_t{{fmap,operands,new_attributes}};
            }
        } // operator[]

        template <typename...m_operands_t>
        constexpr auto operator()(const m_operands_t&...new_operands) const noexcept
        {
            return apply_function(*this,pack_operands(new_operands...));
        } // operator()
    }; // functor_t

    template <typename F>
    nmtools_func_attribute
    functor_t(const F) -> functor_t<F,meta::empty_operands_t,meta::empty_attributes_t>;

    template <template<typename...>typename left_tp, typename...left_functors_t, typename left_operands_t
        , template<typename...>typename right_tp, typename...right_functors_t, typename right_operands_t>
    constexpr auto operator*(const functor_composition_t<left_tp<left_functors_t...>,left_operands_t>& left
        , const functor_composition_t<right_tp<right_functors_t...>,right_operands_t>& right) noexcept
    {
        // NOTE: no need to check arity, assume will be applied if operands is complete
        auto joined_functors = utility::tuple_cat(left.functors,right.functors);
        return functor_composition_t{joined_functors};
    } // operator*

    template <template<typename...>typename left_tp, typename...left_functors_t, typename left_operands_t
        , typename F, typename operands_t, typename attributes_t>
    constexpr auto operator*(const functor_composition_t<left_tp<left_functors_t...>,left_operands_t>& left
        , const functor_t<F,operands_t,attributes_t>& right) noexcept
    {
        auto joined_functors = utility::tuple_append(left.functors,right);
        return functor_composition_t{joined_functors};
    } // operator*

    namespace fun
    {
        struct alias_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::alias(args...);
            }
        };
    }

    constexpr inline auto alias = functor_t{unary_fmap_t<fun::alias_t>{}};
} // namespace nmtools::functional

namespace nmtools::utils
{
    template <
        typename F, typename lhs_operands_t, typename lhs_attributes_t
        , typename G, typename rhs_operands_t, typename rhs_attributes_t>
    struct isequal_t<
        functional::functor_t<F,lhs_operands_t,lhs_attributes_t>
        , functional::functor_t<G,rhs_operands_t,rhs_attributes_t>
    > {
        constexpr auto operator()(
            const functional::functor_t<F,lhs_operands_t,lhs_attributes_t>& lhs
            , const functional::functor_t<G,rhs_operands_t,rhs_attributes_t>& rhs
        ) {
            if constexpr ( !meta::is_same_v<F,G> || 
                !meta::is_same_v<lhs_operands_t,rhs_operands_t>
            ) {
                // TODO: also check the values of operands
                return false;
            } else if constexpr (
                !meta::is_same_v<lhs_attributes_t,meta::empty_attributes_t>
                && !meta::is_same_v<rhs_attributes_t,meta::empty_attributes_t>
            ) {
                constexpr auto M = meta::len_v<lhs_attributes_t>;
                constexpr auto N = meta::len_v<rhs_attributes_t>;
                if constexpr (M != N) {
                    return false;
                } else {
                    auto equal = true;
                    meta::template_for<M>([&](auto index){
                        auto equal_attribute = [&](){
                            auto lhs_attribute = at(lhs.attributes,index);
                            auto rhs_attribute = at(rhs.attributes,index);
                            if constexpr (meta::is_floating_point_v<decltype(lhs_attribute)>
                                && meta::is_floating_point_v<decltype(rhs_attribute)>)
                            {
                                return isclose(lhs_attribute,rhs_attribute);
                            } else {
                                return isequal(lhs_attribute,rhs_attribute);
                            }
                        }();
                        equal = equal && equal_attribute;
                    });
                    return equal;
                }
            } else if constexpr ( meta::is_same_v<F,G>
                && meta::is_same_v<lhs_attributes_t,meta::empty_attributes_t>
                && meta::is_same_v<rhs_attributes_t,meta::empty_attributes_t>
            ) {
                return true;
            } else {
                return false;
            }
        }
    };

    template <
        template<typename...>typename lhs_tuple, typename...lhs_functors_t, typename lhs_operands_t,
        template<typename...>typename rhs_tuple, typename...rhs_functors_t, typename rhs_operands_t
    >
    struct isequal_t
    <
        functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>
        , functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>
    >
    {
        constexpr auto operator()(
            const functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>& lhs
            , const functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>& rhs
        ) {
            constexpr auto N_LHS = meta::len_v<decltype(lhs.functors)>;
            constexpr auto N_RHS = meta::len_v<decltype(rhs.functors)>;

            auto equal = N_LHS == N_RHS;
            constexpr auto N = (N_LHS < N_RHS) ? N_LHS : N_RHS;
            meta::template_for<N>([&](auto index){
                equal = equal && isequal(at(lhs.functors,index),at(rhs.functors,index));
            });
            return equal;
        }
    };

    template <
        typename F, typename lhs_operands_t, typename lhs_attributes_t
        , template<typename...>typename rhs_tuple, typename...rhs_functors_t, typename rhs_operands_t
    >
    struct isequal_t<
        functional::functor_t<F,lhs_operands_t,lhs_attributes_t>
        , functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>
    > {
        constexpr auto operator()(
            const functional::functor_t<F,lhs_operands_t,lhs_attributes_t>& lhs
            , const functional::functor_composition_t<rhs_tuple<rhs_functors_t...>,rhs_operands_t>& rhs
        ) {
            if constexpr (sizeof...(rhs_functors_t) == 1) {
                return isequal(lhs,at(rhs.functors,meta::ct_v<0>));
            } else {
                return false;
            }
        }
    };

    template <
        template<typename...>typename lhs_tuple, typename...lhs_functors_t, typename lhs_operands_t
        , typename G, typename rhs_operands_t, typename rhs_attributes_t
    >
    struct isequal_t<
        functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>
        , functional::functor_t<G,rhs_operands_t,rhs_attributes_t>
    >
    {
        constexpr auto operator()(
            const functional::functor_composition_t<lhs_tuple<lhs_functors_t...>,lhs_operands_t>& lhs
            , const functional::functor_t<G,rhs_operands_t,rhs_attributes_t>& rhs
        ) {
            if constexpr (sizeof...(lhs_functors_t) == 1) {
                return isequal(at(lhs.functors,meta::ct_v<0>),rhs);
            } else {
                return false;
            }
        }
    };
}

namespace nmtools::meta
{
    template <
        typename F
        , typename G, typename rhs_operands_t, typename rhs_attributes_t>
    struct is_same_functor<
        F, functional::functor_t<G,rhs_operands_t,rhs_attributes_t> 
    > :
        is_same<
            functional::functor_t<F,rhs_operands_t,rhs_attributes_t>
            , functional::functor_t<G,rhs_operands_t,rhs_attributes_t>
        > 
    {};
}

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FUNCTOR_HPP

#include "nmtools/core/compute_graph.hpp"
#include "nmtools/core/function_composition.hpp"

// some definition in apply relies on some struct in functor
// TODO: fix dependency
#include "nmtools/core/apply.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/core/functional/accumulate.hpp"
#include "nmtools/core/functional/outer.hpp"
#include "nmtools/core/functional/ufunc.hpp"
#include "nmtools/core/functional/reduce.hpp"
#include "nmtools/core/functional/indexing.hpp"