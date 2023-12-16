#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ARANGE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ARANGE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/arange.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct arange_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::arange(args...);
            }
        };
    }

    constexpr inline auto arange = functor_t(nullary_fmap_t<fun::arange_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::arange_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::arange_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            const auto& attributes = view.attributes();
            constexpr auto N = meta::len_v<decltype(attributes)>;
            return meta::template_reduce<N>([&](auto init, auto index){
                return init[nmtools::at(attributes,index)];
            },arange);
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ARANGE_HPP