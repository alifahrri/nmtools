#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// NOTE: need to include utility for std::array fixed_size specialization
#include "nmtools/array/utility.hpp"
#include "testing/testing.hpp"

#include "doctest/doctest.h"
#include <boost/type_index.hpp>
#include <array>

namespace meta = nmtools::meta;
namespace meta = nmtools::meta;

TEST_CASE("get_container_value_type_t" * doctest::test_suite("meta"))
{
    using vvector_t  = std::vector<double>;
    using varray_t   = std::array<double,3>;
    using fvector_t  = nmtools::array::fixed_vector<double,3>;
    using dvector_t  = nmtools::array::dynamic_vector<double>;

    {
        using lhs_t = double[3];
        using result_t = meta::get_container_value_type_t<lhs_t>;
        LOG_TYPEINFO(lhs_t);
        LOG_TYPEINFO(result_t);
        STATIC_CHECK_IS_SAME( result_t, double );
    }
}