#ifndef NMTOOLS_CORE_FMAP_HPP
#define NMTOOLS_CORE_FMAP_HPP

#include "nmtools/meta.hpp"

namespace nmtools::functional
{
    // helper function to "erase" pointer
    template <typename operand_t>
    static constexpr auto get_operand(const operand_t& operand)
        -> meta::conditional_t<
            meta::is_pointer_v<operand_t>
            , const meta::remove_pointer_t<operand_t>&
            , const operand_t&
        >
    {
        if constexpr (meta::is_pointer_v<operand_t>) {
            return *operand;
        } else {
            return operand;
        }
    }

    namespace detail
    {
        template <typename F, nm_size_t Arity, nm_size_t N_OUT=1>
        struct default_constructible_fmap_t
        {
            static constexpr auto arity = Arity;
            static constexpr auto n_outputs = N_OUT;
            using arity_type = meta::integral_constant<nm_size_t,arity>;
            using n_outputs_type = meta::integral_constant<nm_size_t,n_outputs>;

            const F fn = {};
            arity_type m_arity = arity_type{};
        };

        template <typename F, nm_size_t Arity, nm_size_t N_OUT=1>
        struct non_default_constructible_fmap_t
        {
            static constexpr auto arity = Arity;
            static constexpr auto n_outputs = N_OUT;
            using arity_type = meta::integral_constant<nm_size_t,arity>;
            using n_outputs_type = meta::integral_constant<nm_size_t,n_outputs>;

            const F fn;
            arity_type m_arity = arity_type{};
        };

        template <typename F, nm_size_t Arity, nm_size_t N_OUT=1>
        using base_fmap_t = meta::conditional_t<
            meta::is_default_constructible_v<F>
            , default_constructible_fmap_t<F,Arity,N_OUT>
            , non_default_constructible_fmap_t<F,Arity,N_OUT>
        >;
    }

    template <typename F, nm_size_t Arity, nm_size_t N_OUT=1>
    struct fmap_t : detail::base_fmap_t<F,Arity,N_OUT>
    {
        using base = detail::base_fmap_t<F,Arity,N_OUT>;
        using base::fn, base::arity, base::n_outputs;

        template<
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename operand_tuple, typename...operands_t,
            typename...attributes_t
        >
        constexpr auto expand_operands(sequence<Is...>, const operand_tuple<operands_t...>& operands, const attributes_t&...attributes) const
        {
            // TODO: propagate error handling
            if constexpr (meta::is_maybe_v<operand_tuple<operands_t...>>) {
                return fn(get_operand(nmtools::get<Is>(unwrap(operands)))...,attributes...);
            } else {
                return fn(get_operand(nmtools::get<Is>(operands))...,attributes...);
            }
        }

        template<
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...operands_t
        >
        constexpr auto expand_attributes(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, const operand_tuple<operands_t...>& operands) const
        {
            auto operands_sequence = meta::make_index_sequence_v<sizeof...(operands_t)>;
            return expand_operands(operands_sequence,operands,nmtools::get<Is>(attributes)...);
        }

        template <
            template<typename...>typename attr_tuple, typename...attributes_t,
            template<typename...>typename operand_tuple, typename...operands_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, const operand_tuple<operands_t...>& operands) const
        {
            auto attributes_sequence = meta::make_index_sequence_v<sizeof...(attributes_t)>;
            return expand_attributes(attributes_sequence, attributes, operands);
        } // operator()
    };

    template <typename F, nm_size_t Arity>
    fmap_t(F&&,meta::integral_constant<nm_size_t,Arity>) -> fmap_t<F,Arity>;

    template <typename F>
    struct fmap_t<F,0>
    {
        static constexpr auto arity = 0;
        using arity_type = meta::integral_constant<nm_size_t,arity>;
        using n_outputs_type = meta::integral_constant<nm_size_t,1>;

        F fn;
        static constexpr auto m_arity = arity_type{};
        static constexpr auto n_outputs = n_outputs_type{};

        template <
            template<auto...>typename sequence, auto...Is,
            template<typename...>typename attr_tuple, typename...attributes_t
        >
        constexpr auto operator()(sequence<Is...>, const attr_tuple<attributes_t...>& attributes, meta::empty_operands_t) const
        {
            return fn(nmtools::get<Is>(attributes)...);
        } // operator()

        template <
            template<typename...>typename attr_tuple, typename...attributes_t
        >
        constexpr auto operator()(const attr_tuple<attributes_t...>& attributes, meta::empty_operands_t operands) const
        {
            return (*this)(meta::make_index_sequence_v<sizeof...(attributes_t)>, attributes, operands);
        } // operator()
    };

    /**
     * @brief Type constructor for binary fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using binary_fmap_t = fmap_t<F,2>;

    template <typename F>
    using nullary_fmap_t = fmap_t<F,0>;

    /**
     * @brief Type constructor for unary fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using unary_fmap_t = fmap_t<F,1>;

    /**
     * @brief Type constructor for ternary (arity of 3) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using ternary_fmap_t = fmap_t<F,3>;

    /**
     * @brief Type constructor for quaternary (arity of 4) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using quaternary_fmap_t = fmap_t<F,4>;

    /**
     * @brief Type constructor for quinary (arity of 5) fmap.
     * 
     * @tparam F 
     */
    template <typename F>
    using quinary_fmap_t = fmap_t<F,5>;
}

#endif // NMTOOLS_CORE_FMAP_HPP