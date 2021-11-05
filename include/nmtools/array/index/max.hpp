#ifndef NMTOOLS_ARRAY_INDEX_MAX_HPP
#define NMTOOLS_ARRAY_INDEX_MAX_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"

namespace nmtools::index
{
    struct max_t {};

    // TODO: cleanup index functions
    template <typename array_t>
    constexpr auto max(const array_t& array)
    {
        auto reduce = [](auto& f, auto initial, const auto& array){
            auto ret = initial;
            using array_type = meta::remove_cvref_t<decltype(array)>;
            if constexpr (meta::is_fixed_index_array_v<array_type>) {
                constexpr auto N = meta::len_v<array_type>;
                meta::template_for<N>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    ret = f(ret, at<i>(array));
                });
            }
            else {
                for (const auto& a : array)
                    ret = f(ret, a);
            }
            return ret;
        };

        //  max
        auto f = [](auto i, auto a) {
            using i_t = decltype(i);
            using a_t = decltype(a);
            using c_t = meta::promote_index_t<i_t,a_t>;
            if ((c_t)i > (c_t)a) {
                return i;
            } else {
                return a;
            }
        };

        using namespace ::nmtools::literals;
        using return_t = meta::resolve_optype_t<max_t,array_t>;
        auto initial = static_cast<return_t>(at(array, 0_ct));

        return reduce(f,initial,array);
    } // max
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct INDEX_MAX_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename array_t>
    struct resolve_optype<
        void, index::max_t, array_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_index_array_v<array_t>) {
                using type = get_element_or_common_type_t<array_t>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::INDEX_MAX_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_MAX_HPP