#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardtanh.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct hardtanh_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::hardtanh(args...);
            }
        };
    }

    constexpr inline auto hardtanh = functor_t(unary_fmap_t<fun::hardtanh_t>{});

    template <typename min_val_t, typename max_val_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::hardtanh_t<min_val_t,max_val_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::hardtanh_t<min_val_t,max_val_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return hardtanh[view.op.min_val][view.op.max_val];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP