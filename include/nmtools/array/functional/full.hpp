#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FULL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FULL_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/full.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct full_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::full(args...);
            }
        };
    }

    constexpr inline auto full = functor_t{nullary_fmap_t<fun::full_t>{}};

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::full_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::full_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            const auto& attributes = view.attributes();
            constexpr auto N = meta::len_v<decltype(attributes)>;
            return meta::template_reduce<N>([&](auto init, auto index){
                return init[nmtools::at(attributes,index)];
            },full);
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FULL_HPP