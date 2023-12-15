#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ones.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct ones_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::ones(args...);
            }
        };
    }

    constexpr inline auto ones = functor_t(nullary_fmap_t<fun::ones_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::ones_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::ones_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            const auto& attributes = view.attributes();
            constexpr auto N = meta::len_v<decltype(attributes)>;
            return meta::template_reduce<N>([&](auto init, auto index){
                return init[nmtools::at(attributes,index)];
            },ones);
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP