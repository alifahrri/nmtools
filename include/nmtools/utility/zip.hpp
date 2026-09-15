#ifndef NMTOOLS_UTILITY_ZIP_HPP
#define NMTOOLS_UTILITY_ZIP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/error.hpp"
#include "nmtools/stl.hpp"
#include "nmtools/utility/forward.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools
{
    template <typename first_t, typename second_t>
    struct zip_t
    {
        using first_type  = first_t;
        using second_type = second_t;

        first_type first;
        second_type second;

        constexpr auto size() const noexcept
        {
            return len(first);
        }

        constexpr auto operator[](nm_size_t i) const
        {
            using fst_t = decltype(at(first,i));
            using snd_t = decltype(at(second,i));
            using res_t = nmtools_tuple<fst_t,snd_t>;

            return res_t{at(first,i),at(second,i)};
        }

        constexpr auto operator[](nm_size_t i)
        {
            using fst_t = decltype(at(first,i));
            using snd_t = decltype(at(second,i));
            using res_t = nmtools_tuple<fst_t,snd_t>;

            return res_t{at(first,i),at(second,i)};
        }
    };

    template <typename first_t, typename second_t>
    constexpr auto zip(first_t&& first, second_t&& second)
    {
        auto fst_size = len(first);
        auto snd_size = len(second);
        nmtools_panic( (nm_size_t)fst_size == (nm_size_t)snd_size
            , "invalid length for zip"
        );

        // TODO: detect operand or attribute
        using first_type = decltype(nmtools::forward<first_t>(first));
        using second_type = remove_cvref_t<second_t>;
        // using second_type = decltype(nmtools::forward<second_t>(second));
        return zip_t<first_type,second_type>{nmtools::forward<first_t>(first),nmtools::forward<second_t>(second)};
    }
}

#endif // NMTOOLS_UTILITY_ZIP_HPP