#ifndef NMTOOLS_ARRAY_INDEX_COUNT_HPP
#define NMTOOLS_ARRAY_INDEX_COUNT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::index
{
    struct count_t {};

    template <typename F, typename array_t>
    constexpr auto count(const F& f, const array_t& array)
    {
        using return_t = meta::resolve_optype_t<count_t,F,array_t>;

        auto res = return_t {0};

        auto count_impl = [&](auto i){
            res += static_cast<bool>(f(at(array,i))) ? 1 : 0;
        };

        if constexpr (meta::has_tuple_size_v<array_t>) {
            constexpr auto N = std::tuple_size_v<array_t>;
            meta::template_for<N>(count_impl);
        }
        else {
            auto n = len(array);
            for (size_t i=0; i<n; i++)
                count_impl(i);
        }

        return res;
    } // count
} // namespace nmtools::index

namespace nmtools::meta
{
    template <typename F, typename array_t>
    struct resolve_optype<
        void, index::count_t, F, array_t
    >
    {
        using type = size_t;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COUNT_HPP