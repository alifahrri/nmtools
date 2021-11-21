#include "nmtools/meta.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace meta = nm::meta;

TEST_CASE("integral_constant" * doctest::test_suite("meta"))
{
    {
        using int_t = meta::integral_constant<int,-2>;
        constexpr auto int_v = int_t{};
        constexpr auto res_s = (int)int_v;
        constexpr auto cmp_v = (int_v < 0);
        constexpr auto add_v = int_v + 2;
        NMTOOLS_ASSERT_EQUAL( res_s, -2 );
        NMTOOLS_ASSERT_EQUAL( cmp_v, true );
        NMTOOLS_ASSERT_EQUAL( add_v, 0 );
        CHECK( res_s == -2 );
        CHECK( cmp_v == true );
        CHECK( add_v == 0 );
    }
    {
        using int_t = meta::integral_constant<int,-2>;
        auto N = int_t{};
        size_t dim = 2;
        auto axis = dim;
        axis = (N<0) ? (dim+N) : N;
        NMTOOLS_ASSERT_EQUAL( axis, 0 );
    }
    {
        using int_t = meta::integral_constant<int,-2>;
        auto N = int_t{};
        int dim = 2;
        auto axis = dim;
        axis = (N<0) ? (dim+N) : N;
        NMTOOLS_ASSERT_EQUAL( axis, 0 );
        static_assert( meta::is_signed_v<int_t> );
    }
}