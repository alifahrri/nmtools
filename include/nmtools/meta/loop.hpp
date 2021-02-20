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
} // namespace nmtools::meta

#endif // NMTOOLS_META_LOOP_HPP