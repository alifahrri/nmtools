#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

using namespace nm::literals;

TEST_CASE("to_value(case1)" * doctest::test_suite("meta::to_value"))
{
    {
        using type = decltype(nmtools_tuple{1_ct,2_ct,6_ct});
        constexpr auto value = meta::to_value_v<type>;
        NMTOOLS_ASSERT_EQUAL( value, (nmtools_array{1,2,6}) );
    }
}