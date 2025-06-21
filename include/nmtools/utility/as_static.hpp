#ifndef NMTOOLS_ARRAY_AS_STATIC_HPP
#define NMTOOLS_ARRAY_AS_STATIC_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/fwd.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/forward.hpp"
// #include "nmtools/ndarray.hpp" // for nmtools_static_vector
#include "nmtools/utl/static_vector.hpp"

namespace nmtools
{
    template <typename attribute_t, auto max_dim=8>
    struct as_static_t
    {
        using attribute_type = attribute_t;

        attribute_type attribute;

        auto operator()() const noexcept
        {
            // TODO: return maybe when size > max_dim
            if constexpr (meta::is_resizable_v<attribute_type>) {
                using element_type = meta::get_element_type_t<attribute_t>;
                using result_type  = utl::static_vector<element_type,max_dim>;
                auto result = result_type{};
                result.resize(nmtools::size(attribute));
                for (size_t i=0; i<len(result); i++) {
                    at(result,i) = at(attribute,i);
                }
                return result;
            } else {
                return fwd_attribute(attribute);
            }
        }
    };

    template <auto max_dim=8, typename attribute_t>
    auto as_static(const attribute_t& attribute, meta::ct<max_dim> = meta::ct<max_dim>{})
    {
        auto mapper = as_static_t<attribute_t,max_dim>{attribute};
        return mapper();
    } // as_static
} // namespace nmtools

#endif // NMTOOLS_ARRAY_AS_STATIC_HPP