#ifndef NMTOOLS_META_LOOP_HPP
#define NMTOOLS_META_LOOP_HPP

#include <type_traits>
#include <tuple>
#include <utility>
#include <functional>

namespace nmtools::meta
{
    /**
     * @brief helper alias template for std::integral_constant<size_t,...>
     * 
     * @tparam N 
     */
    template <size_t N>
    using index_constant = std::integral_constant<size_t,N>;

    template <typename,typename,typename=void>
    struct merge_ranges {};

    template <size_t...left, size_t...right>
    struct merge_ranges<std::integer_sequence<size_t,left...>,std::integer_sequence<size_t,right...>>
    {
        using type = std::integer_sequence<size_t,left...,right...>;
    }; // merge_ranges

    template <size_t start, size_t stop, typename=void>
    struct range {}; // range

    template <size_t start, size_t stop>
    struct range<start,stop,std::enable_if_t<(start+1)==stop>>
    {
        using left  = std::integer_sequence<size_t,start>;
        using type  = left;
    }; // range

    template <size_t start, size_t stop>
    struct range<start,stop,std::enable_if_t<((start+1)<stop)>>
    {
        using left  = std::integer_sequence<size_t,start>;
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
    constexpr auto template_for(F&& f, std::index_sequence<Is...>)
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
    template <size_t N, typename F>
    constexpr auto template_for(F&& f)
    {
        using index_t = std::make_index_sequence<N>;
        template_for(f,index_t{});
    } // template_for

    template <typename F, typename...args_t>
    constexpr auto template_map(F&& f, const std::tuple<args_t...>& args_pack)
    {
        using return_type = std::tuple<decltype(std::declval<F>()(std::declval<const args_t&>()))...>;
        auto ret = return_type {};

        auto f_impl = [&](auto idx){
            constexpr auto i = decltype(idx)::value;
            std::get<i>(ret) = f(std::get<i>(args_pack));
        };
        constexpr auto N = sizeof...(args_t);
        template_for<N>(f_impl);
        return ret;
    }; // template_map

    template <typename F, size_t...Is>
    constexpr auto template_map(F&& f, std::index_sequence<Is...>)
    {
        return std::tuple{f(index_constant<Is>{})...};
    } // template_map

    /**
     * @brief Compile time mapping. Useful to convert constexpr value back to type.
     * 
     * @tparam N number of iteration
     * @tparam F function to call, must return something
     * @param f function to call, e.g. lambda capturing constexpr value, then map to type.
     * @return constexpr auto 
     */
    template <size_t N, typename F>
    constexpr auto template_map(F&& f)
    {
        using index_t = std::make_index_sequence<N>;
        return template_map(f,index_t{});
    }

    template <typename F, typename...args_t, typename initial_t, size_t I, size_t...Is>
    constexpr auto template_reduce(F&& f, const initial_t& init, const std::tuple<args_t...>& args_pack, std::integer_sequence<size_t,I,Is...>)
    {
        auto init_ = f(init, std::get<I>(args_pack), std::integral_constant<size_t,I>{});
        if constexpr (static_cast<bool>(sizeof...(Is))) {
            using indices_t = std::integer_sequence<size_t,Is...>;
            return template_reduce(f,init_,args_pack,indices_t{});
        }
        else
            return init_;
    } // template_reduce

    template <typename F, typename...args_t, typename initial_t>
    constexpr auto template_reduce(F&& f, const initial_t& init, const std::tuple<args_t...>& args_pack)
    {
        constexpr auto N = sizeof...(args_t);
        using indices_t  = std::make_index_sequence<N>;
        return template_reduce(f,init,args_pack,indices_t{});
    } // template_reduce

    template <typename F, typename...args_t>
    constexpr auto template_reduce(F&& f, const std::tuple<args_t...>& args_pack)
    {
        constexpr auto N = sizeof...(args_t);
        using indices_t  = typename range<1,N>::type;
        auto init = std::get<0>(args_pack);
        return template_reduce(f,init,args_pack,indices_t{});
    } // template_reduce
} // namespace nmtools::meta

#endif // NMTOOLS_META_LOOP_HPP