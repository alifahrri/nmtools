#ifndef NMTOOLS_META_LOOP_HPP
#define NMTOOLS_META_LOOP_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/utility/get.hpp"
#include "nmtools/meta/bits/transform/add_reference.hpp"

namespace nmtools::meta
{
    /**
     * @brief helper alias template for integral_constant<size_t,...>
     * 
     * @tparam N 
     */
    template <size_t N>
    using index_constant = integral_constant<size_t,N>;

    template <typename,typename,typename=void>
    struct merge_ranges {};

    template <size_t...left, size_t...right>
    struct merge_ranges<integer_sequence<size_t,left...>,integer_sequence<size_t,right...>>
    {
        using type = integer_sequence<size_t,left...,right...>;
    }; // merge_ranges

    template <size_t start, size_t stop, typename=void>
    struct range {}; // range

    template <size_t start, size_t stop>
    struct range<start,stop,enable_if_t<(start+1)==stop>>
    {
        using left  = integer_sequence<size_t,start>;
        using type  = left;
    }; // range

    template <size_t start, size_t stop>
    struct range<start,stop,enable_if_t<((start+1)<stop)>>
    {
        using left  = integer_sequence<size_t,start>;
        using right = typename range<start+1,stop>::type;
        using type  = typename merge_ranges<left,right>::type;
    }; // range

    /**
     * @brief call f N times with compile-time index.
     *
     * Call f with each compile-time index using fold expression.
     * 
     * @tparam F 
     * @tparam Is index sequence
     * @param f callable
     * @return constexpr auto 
     */
    template <typename F, size_t...Is>
    constexpr auto template_for(F&& f, index_sequence<Is...>)
    {
        (f(index_constant<Is>{}),...);
    } // template_for

    /**
     * @brief call f N times with compile-time index.
     *
     * N index sequence will be generated at compile-time to call f.
     * 
     * @tparam N number of calls
     * @tparam F 
     * @param f callable
     * @return constexpr auto 
     * @todo check if f match the required signature
     */
    template <nm_index_t N, typename F>
    constexpr auto template_for(F&& f)
    {
        if constexpr (N > 0) {
            using index_t = make_index_sequence<N>;
            template_for(f,index_t{});
        }
    } // template_for

    template <typename F, typename args_pack_t, typename initial_t, size_t I, size_t...Is>
    constexpr auto template_reduce(F&& f, const initial_t& init, const args_pack_t& args_pack, integer_sequence<size_t,I,Is...>)
    {
        auto init_ = f(init, get<I>(args_pack), integral_constant<size_t,I>{});
        if constexpr (static_cast<bool>(sizeof...(Is))) {
            using indices_t = integer_sequence<size_t,Is...>;
            return template_reduce(f,init_,args_pack,indices_t{});
        }
        else
            return init_;
    } // template_reduce

    /**
     * @brief Perform reduce-like operator f on args_pack typelist with initial value.
     * 
     * @tparam F 
     * @tparam args_t 
     * @tparam initial_t 
     * @param f         reduce-like operation
     * @param init      initial value
     * @param args_pack typelist to operate on
     * @return constexpr auto 
     */
    template <typename F, template<typename...> typename tuple, typename...args_t, typename initial_t>
    constexpr auto template_reduce(F&& f, const initial_t& init, const tuple<args_t...>& args_pack)
    {
        constexpr auto N = sizeof...(args_t);
        using indices_t  = make_index_sequence<N>;
        return template_reduce(f,init,args_pack,indices_t{});
    } // template_reduce

    /**
     * @brief Perform reduce-like operator f on args_pack typelist
     * with initial value and explicit number of recursion (N).
     * 
     * @tparam N 
     * @tparam F 
     * @tparam args_pack_t 
     * @tparam initial_t 
     * @param f 
     * @param init 
     * @param args_pack 
     * @return constexpr auto 
     */
    template <size_t N, typename F, typename args_pack_t, typename initial_t>
    constexpr auto template_reduce(F&& f, const initial_t& init, const args_pack_t& args_pack)
    {
        using indices_t  = make_index_sequence<N>;
        return template_reduce(f,init,args_pack,indices_t{});
    } // template_reduce

    /**
     * @brief Entrypoint for template_reduce. Perform reduce-like operator f on typelist args_pack.
     *
     * This can be helpful when one wants to operate on the whole type-list.
     * For example transforming tuple{1_ct,3_ct,2_ct} to int[1][3][2];
     * 
     * @tparam F 
     * @tparam args_t 
     * @param f         reduce-like operation
     * @param args_pack type list to operate on
     * @return constexpr auto 
     */
    template <typename F, template<typename...> typename tuple, typename...args_t>
    constexpr auto template_reduce(F&& f, const tuple<args_t...>& args_pack)
    {
        constexpr auto N = sizeof...(args_t);
        using indices_t  = typename range<1,N>::type;
        auto init = get<0>(args_pack);
        return template_reduce(f,init,args_pack,indices_t{});
    } // template_reduce

    template <typename F, typename init_t, size_t I, size_t...Is>
    constexpr auto template_reduce(F&& f, const init_t& init, integer_sequence<size_t,I,Is...>)
    {
        auto result = f(init, integral_constant<size_t,I>{});
        if constexpr (static_cast<bool>(sizeof...(Is))) {
            using indices_t = integer_sequence<size_t,Is...>;
            return template_reduce(f,result,indices_t{});
        } else {
            return result;
        }
    } // template_reduce

    /**
     * @brief Simplified version of template_reduce that doesn't take the tuple to "iterate".
     * 
     * @tparam N number of desired iteration
     * @tparam F reducer with "f(init,index) -> init_k" signature
     * @tparam init_t 
     * @param f reducer
     * @param init initial value for k=0
     * @return constexpr auto 
     */
    template <size_t N, typename F, typename init_t>
    constexpr auto template_reduce(F&& f, const init_t& init)
    {
        // range<0,0> not defined to have type
        if constexpr (N>0) {
            using indices_t = typename range<0,N>::type;
            return template_reduce(f, init, indices_t{});
        } else {
            return init;
        }
    } // template_reduce
} // namespace nmtools::meta

#endif // NMTOOLS_META_LOOP_HPP