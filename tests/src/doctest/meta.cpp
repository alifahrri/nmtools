#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "doctest/doctest.h"
#include <array>

namespace meta = nmtools::meta;
namespace traits = nmtools::traits;

/**
 * @test compile-time tests
 * @note that meta::get_element_type call/use the following traits/metafunctions:
 * - nmtools::traits::is_array1d_v
 * - nmtools::traits::is_array2d_v
 * - nmtools::meta::get_matrix_value_type_t
 * - nmtools::meta::get_vector_value_type_t
 * 
 */
TEST_CASE("meta::get_element_type")
{
    using array_t = std::array<std::array<double,5>,2>;
    using value_t = meta::get_matrix_value_type_t<array_t>;
    using element_t = meta::get_element_type_t<array_t>;
    /**
     * @note that nmtools::traits::is_array1d_v and nmtools::traits::is_array2d_v may not mutually exclusive!
     * 
     */
    // static_assert(!traits::is_array1d_v<array_t>);
    static_assert( traits::is_array2d_v<array_t>);
    static_assert(std::is_same_v<value_t,double>);
    static_assert(std::is_same_v<element_t,double>);
}